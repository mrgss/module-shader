#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>
#include <mruby.h>
#include <mruby/data.h>
#include <mruby/string.h>
#include <mruby/class.h>
#include <mrgss.h>
#include <mrgss/mrgss-shader.h>

static void
shader_free(mrb_state *mrb, void *data) {
    mrgss_shader *tex = data;
    if (tex) {
        mrb_free(mrb, tex);
    };
}

struct mrb_data_type const mrbal_shader_data_type = {"Texture", shader_free};

GLuint compile_shader(const char *shader, int type) {
    const char* shade = shader;
    GLuint shaderid = glCreateShader(type);
    glShaderSource(shaderid, 1, &shade, NULL);
    glCompileShader(shaderid);
    return shaderid;
}

GLuint
compile_shader_program(GLuint vertexShader, GLuint fragmentShader) {
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    return shaderProgram;
}

static mrb_value initialize(mrb_state *mrb, mrb_value self) {
    mrgss_shader *shader;
    char *vs, *fs;
    GLuint vertex, fragment;
    mrb_get_args(mrb, "zz", &vs, &fs);
    shader = mrb_malloc(mrb, sizeof (mrgss_shader));
    vertex = compile_shader(vs, GL_VERTEX_SHADER);
    fragment = compile_shader(fs, GL_FRAGMENT_SHADER);
    shader->sid = compile_shader_program(vertex, fragment);
    DATA_TYPE(self) = &mrbal_shader_data_type;
    DATA_PTR(self) = shader;
    return self;
}

/**
 * Type initializer
 * @param mrb
 */
void mrgss_init_shader(mrb_state *mrb) {
    struct RClass *type = mrgss_create_class(mrb, "Shader");
    mrb_define_method(mrb, type, "initialize", initialize, MRB_ARGS_REQ(2));
    MRB_SET_INSTANCE_TT(type, MRB_TT_DATA);
}
