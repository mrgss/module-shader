#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <stdlib.h>
#include <stdio.h>
#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include <mruby/string.h>
#include <mruby/variable.h>
#include <mrgss/mrgss.h>
#include <mrgss/mrgss_shader.h>

const static GLchar* default_vertex = "#version 130\n"
        "attribute vec2 position;\n"
        "attribute vec2 texture_coord;\n"
        "varying vec2 texcoord;\n"
        "uniform mat4 Model;\n"
        "uniform mat4 View;\n"
        "uniform mat4 Projection;\n"
        "void main() {\n"
        "gl_Position = Projection * View * Model * vec4(position, 0.0, 1.0);\n"
        "texcoord = texture_coord;\n"
        "}\n";

const static GLchar* default_fragment = "#version 130\n"
        "varying vec2 texcoord;\n"
        "uniform sampler2D tex;\n"
        "void main() {\n"
        "	gl_FragColor = texture2D(tex, texcoord);\n"
        "}";

/**
 * mruby instance data free
 */
static void shader_free(mrb_state *mrb, void *p) {
    if (p) {
        mrgss_shader *shader = (mrgss_shader*) p;
        glDeleteProgram(shader->sid);
        mrb_free(mrb, shader);
    }
}

struct mrb_data_type const mrbal_shader_data_type = {"Shader", shader_free};

GLuint compile_shader_program(GLuint vertexShader, GLuint fragmentShader) {
//    GLint bufflen;
//    GLchar* log;

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    /* Uncoment this to see shader program infolog*/
//    glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &bufflen);
//    log = malloc(sizeof (GLchar) * bufflen);
//    glGetProgramInfoLog(shaderProgram, bufflen, 0, log);
//    printf(log);
//    free(log);
    return shaderProgram;
}

GLuint compile_shader(const char *shader, int type) {
//    GLint bufflen;
//    GLchar* log;

    const char* shade = shader;
    GLuint shaderid = glCreateShader(type);
    glShaderSource(shaderid, 1, &shade, NULL);
    glCompileShader(shaderid);
    /* Uncoment this to see shader infolog*/
//    glGetShaderiv(shaderid, GL_INFO_LOG_LENGTH, &bufflen);
//    log = malloc(sizeof (GLchar) * bufflen);
//    glGetShaderInfoLog(shaderid, bufflen, 0, log);
//    printf(log);
//    free(log);
    return shaderid;
}

static mrb_value init(mrb_state *mrb, mrb_value self) {
    mrgss_shader *shader;
    const char *vertex, *fragment;
    mrb_int count;
    count = mrb_get_args(mrb, "|zz", &vertex, &fragment);
    shader = mrb_malloc(mrb, sizeof (mrgss_shader));
    mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@vertex"), mrb_str_new_cstr(mrb, vertex));
    mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "@fragment"), mrb_str_new_cstr(mrb, fragment));
    if (count == 0) {
        return mrb_gv_get(mrb, mrb_intern_lit(mrb, "default_shader"));
    } else if (count == 2) {
        shader->sid = compile_shader_program(compile_shader(vertex, GL_VERTEX_SHADER), compile_shader(fragment, GL_FRAGMENT_SHADER));
    }
    DATA_TYPE(self) = &mrbal_shader_data_type;
    DATA_PTR(self) = shader;
    return self;
}

/**
 * Initialize mruby class
 */
void mrgss_shader_init(mrb_state *mrb) {

    struct RClass *class = mrb_define_class_under(mrb, mrgss_module(), "Shader", mrb->object_class);
    mrb_define_method(mrb, class, "initialize", init, MRB_ARGS_REQ(0) | MRB_ARGS_OPT(2));
    MRB_SET_INSTANCE_TT(class, MRB_TT_DATA);
}

void mrgss_create_shader(mrb_state *mrb) {
    mrb_value params[2];
    mrb_value default_shader;
    struct RClass *class = mrb_class_get_under(mrb, mrgss_module(), "Shader");
    params[0] = mrb_str_new_cstr(mrb, default_vertex);
    params[1] = mrb_str_new_cstr(mrb, default_fragment);
    default_shader = mrb_obj_new(mrb, class, 2, params);
    mrb_gv_set(mrb, mrb_intern_lit(mrb, "default_shader"), default_shader);
}
