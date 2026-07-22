/* Copyright 2009, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to 
 * QNX Software Systems before you may reproduce, modify or distribute this 
 * software, or any work that includes all or part of this software.  Free 
 * development licenses are available for evaluation and non-commercial purposes.  
 * For more information visit http://licensing.qnx.com or email licensing@qnx.com.
 * 
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 */
#ifndef _GF_GF3D_H_INCLUDED
#define _GF_GF3D_H_INCLUDED

#ifndef _GLES_EGL_H_INCLUDED
#include <GLES/egl.h>
#endif

#ifndef _GF_GF_H_INCLUDED
#include <gf/gf.h>
#endif

__BEGIN_DECLS

typedef struct _gf_3d_target *		gf_3d_target_t;

#ifndef _WIN32
#include <_pack1.h>
#endif

typedef struct {
	gf_format_t	format;
	_uint32		create_flags;
} gf_3d_config_info_t;

#ifndef _WIN32
#include <_packpop.h>
#endif

extern int gf_3d_target_create(gf_3d_target_t *ptarget, gf_layer_t layer,
    gf_surface_t *surfaces, int nsurfaces, int width, int height, gf_format_t format);
extern void gf_3d_target_free(gf_3d_target_t target);
extern int gf_3d_query_config(gf_3d_config_info_t *info, gf_dev_t dev,
    EGLDisplay display, EGLConfig cfg);
extern int gf_context_set_surface_3d(gf_context_t context, EGLSurface surface);

__END_DECLS

#endif  /* _GF_GF3D_H_INCLUDED */

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/gf/public/gf/gf3d.h $ $Rev: 224586 $" )
