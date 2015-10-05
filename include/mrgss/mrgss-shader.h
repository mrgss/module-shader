/* 
 * File:   mrgss-shader.h
 * Author: manuel
 *
 * Created on 3 de octubre de 2015, 00:16
 */

#ifndef MRGSS_SHADER_H
#define	MRGSS_SHADER_H

#include <mruby.h>
#include <GL/gl.h>

#ifdef	__cplusplus
extern "C" {
#endif
	void mrb_mrgss_shader_gem_init(mrb_state *mrb);

    void mrgss_init_shader(mrb_state *mrb);
    
    typedef struct shader {
        GLuint sid;
    } mrgss_shader;

#ifdef	__cplusplus
}
#endif

#endif	/* MRGSS_TEXTURE_H */

