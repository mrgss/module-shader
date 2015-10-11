/* 
 * File:   mrgss_shader.h
 * Author: manuel
 *
 * Created on 8 de octubre de 2015, 23:07
 */

#ifndef MRGSS_SHADER_H
#define	MRGSS_SHADER_H

#include <mruby.h>


#ifdef	__cplusplus
extern "C" {
#endif
    void mrgss_shader_init(mrb_state *mrb);
    void mrgss_create_shader(mrb_state *mrb);

    typedef struct shader {
        GLuint sid;
    } mrgss_shader;


#ifdef	__cplusplus
}
#endif

#endif	/* MRGSS_SHADER_H */

