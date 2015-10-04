#include <mruby.h>
#include <mrgss.h>
#include <mrgss/mrgss-shader.h>

void
mrb_mrgss_shader_gem_init(mrb_state *mrb) {
    mrgss_init_shader(mrb);
}

void
mrb_mrgss_shader_gem_final(mrb_state* mrb) {
    /* finalizer */
}
