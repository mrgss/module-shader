#include <mruby.h>
#include <mrgss/mrgss.h>
#include <mrgss/mrgss_shader.h>

void
mrb_mrgss_shader_gem_init(mrb_state *mrb) {
    mrgss_shader_init(mrb);
}

void
mrb_mrgss_shader_gem_final(mrb_state* mrb) {
    /* finalizer */
}
