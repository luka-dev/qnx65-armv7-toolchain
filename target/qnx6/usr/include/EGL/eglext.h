#ifndef __eglext_h_
#define __eglext_h_

#ifdef __cplusplus
extern "C" {
#endif

/*
** Copyright (c) 2007-2009 The Khronos Group Inc.
**
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and/or associated documentation files (the
** "Materials"), to deal in the Materials without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Materials, and to
** permit persons to whom the Materials are furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be included
** in all copies or substantial portions of the Materials.
**
** THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
** TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
** MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
*/

#include <EGL/eglplatform.h>

/*************************************************************/

/* Header file version number */
/* Current version at http://www.khronos.org/registry/egl/ */
/* $Revision: 222561 $ on $Date: 2009-06-03 13:24:16 -0400 (Wed, 03 Jun 2009) $ */
#define EGL_EGLEXT_VERSION 3

#ifndef EGL_KHR_config_attribs
#define EGL_KHR_config_attribs 1
#define EGL_CONFORMANT_KHR			0x3042	/* EGLConfig attribute */
#define EGL_VG_COLORSPACE_LINEAR_BIT_KHR	0x0020	/* EGL_SURFACE_TYPE bitfield */
#define EGL_VG_ALPHA_FORMAT_PRE_BIT_KHR		0x0040	/* EGL_SURFACE_TYPE bitfield */
#endif

#ifndef EGL_KHR_lock_surface
#define EGL_KHR_lock_surface 1
#define EGL_READ_SURFACE_BIT_KHR		0x0001	/* EGL_LOCK_USAGE_HINT_KHR bitfield */
#define EGL_WRITE_SURFACE_BIT_KHR		0x0002	/* EGL_LOCK_USAGE_HINT_KHR bitfield */
#define EGL_LOCK_SURFACE_BIT_KHR		0x0080	/* EGL_SURFACE_TYPE bitfield */
#define EGL_OPTIMAL_FORMAT_BIT_KHR		0x0100	/* EGL_SURFACE_TYPE bitfield */
#define EGL_MATCH_FORMAT_KHR			0x3043	/* EGLConfig attribute */
#define EGL_FORMAT_RGB_565_EXACT_KHR		0x30C0	/* EGL_MATCH_FORMAT_KHR value */
#define EGL_FORMAT_RGB_565_KHR			0x30C1	/* EGL_MATCH_FORMAT_KHR value */
#define EGL_FORMAT_RGBA_8888_EXACT_KHR		0x30C2	/* EGL_MATCH_FORMAT_KHR value */
#define EGL_FORMAT_RGBA_8888_KHR		0x30C3	/* EGL_MATCH_FORMAT_KHR value */
#define EGL_MAP_PRESERVE_PIXELS_KHR		0x30C4	/* eglLockSurfaceKHR attribute */
#define EGL_LOCK_USAGE_HINT_KHR			0x30C5	/* eglLockSurfaceKHR attribute */
#define EGL_BITMAP_POINTER_KHR			0x30C6	/* eglQuerySurface attribute */
#define EGL_BITMAP_PITCH_KHR			0x30C7	/* eglQuerySurface attribute */
#define EGL_BITMAP_ORIGIN_KHR			0x30C8	/* eglQuerySurface attribute */
#define EGL_BITMAP_PIXEL_RED_OFFSET_KHR		0x30C9	/* eglQuerySurface attribute */
#define EGL_BITMAP_PIXEL_GREEN_OFFSET_KHR	0x30CA	/* eglQuerySurface attribute */
#define EGL_BITMAP_PIXEL_BLUE_OFFSET_KHR	0x30CB	/* eglQuerySurface attribute */
#define EGL_BITMAP_PIXEL_ALPHA_OFFSET_KHR	0x30CC	/* eglQuerySurface attribute */
#define EGL_BITMAP_PIXEL_LUMINANCE_OFFSET_KHR	0x30CD	/* eglQuerySurface attribute */
#define EGL_LOWER_LEFT_KHR			0x30CE	/* EGL_BITMAP_ORIGIN_KHR value */
#define EGL_UPPER_LEFT_KHR			0x30CF	/* EGL_BITMAP_ORIGIN_KHR value */
#ifdef EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglLockSurfaceKHR (EGLDisplay display, EGLSurface surface, const EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglUnlockSurfaceKHR (EGLDisplay display, EGLSurface surface);
#endif /* EGL_EGLEXT_PROTOTYPES */
typedef EGLBoolean (EGLAPIENTRYP PFNEGLLOCKSURFACEKHRPROC) (EGLDisplay display, EGLSurface surface, const EGLint *attrib_list);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLUNLOCKSURFACEKHRPROC) (EGLDisplay display, EGLSurface surface);
#endif

#ifndef EGL_KHR_image
#define EGL_KHR_image 1
#define EGL_NATIVE_PIXMAP_KHR			0x30B0	/* eglCreateImageKHR target */
typedef void *EGLImageKHR;
#define EGL_NO_IMAGE_KHR			((EGLImageKHR)0)
#ifdef EGL_EGLEXT_PROTOTYPES
EGLAPI EGLImageKHR EGLAPIENTRY eglCreateImageKHR (EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglDestroyImageKHR (EGLDisplay dpy, EGLImageKHR image);
#endif /* EGL_EGLEXT_PROTOTYPES */
typedef EGLImageKHR (EGLAPIENTRYP PFNEGLCREATEIMAGEKHRPROC) (EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLint *attrib_list);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLDESTROYIMAGEKHRPROC) (EGLDisplay dpy, EGLImageKHR image);
#endif

#ifndef EGL_KHR_vg_parent_image
#define EGL_KHR_vg_parent_image 1
#define EGL_VG_PARENT_IMAGE_KHR			0x30BA	/* eglCreateImageKHR target */
#endif

#ifndef EGL_KHR_gl_texture_2D_image
#define EGL_KHR_gl_texture_2D_image 1
#define EGL_GL_TEXTURE_2D_KHR			0x30B1	/* eglCreateImageKHR target */
#define EGL_GL_TEXTURE_LEVEL_KHR		0x30BC	/* eglCreateImageKHR attribute */
#endif

#ifndef EGL_KHR_gl_texture_cubemap_image
#define EGL_KHR_gl_texture_cubemap_image 1
#define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_X_KHR	0x30B3	/* eglCreateImageKHR target */
#define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_X_KHR	0x30B4	/* eglCreateImageKHR target */
#define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_Y_KHR	0x30B5	/* eglCreateImageKHR target */
#define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_KHR	0x30B6	/* eglCreateImageKHR target */
#define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_Z_KHR	0x30B7	/* eglCreateImageKHR target */
#define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_KHR	0x30B8	/* eglCreateImageKHR target */
#endif

#ifndef EGL_KHR_gl_texture_3D_image
#define EGL_KHR_gl_texture_3D_image 1
#define EGL_GL_TEXTURE_3D_KHR			0x30B2	/* eglCreateImageKHR target */
#define EGL_GL_TEXTURE_ZOFFSET_KHR		0x30BD	/* eglCreateImageKHR attribute */
#endif

#ifndef EGL_KHR_gl_renderbuffer_image
#define EGL_KHR_gl_renderbuffer_image 1
#define EGL_GL_RENDERBUFFER_KHR			0x30B9	/* eglCreateImageKHR target */
#endif

#ifndef EGL_KHR_image_base
#define EGL_KHR_image_base 1
/* Most interfaces defined by EGL_KHR_image_pixmap above */
#define EGL_IMAGE_PRESERVED_KHR			0x30D2	/* eglCreateImageKHR attribute */
#endif

#ifndef EGL_KHR_image_pixmap
#define EGL_KHR_image_pixmap 1
/* Interfaces defined by EGL_KHR_image above */
#endif

#ifndef EGL_IMG_context_priority
#define EGL_IMG_context_priority 1
#define EGL_CONTEXT_PRIORITY_LEVEL_IMG			0x3100
#define EGL_CONTEXT_PRIORITY_HIGH_IMG			0x3101
#define EGL_CONTEXT_PRIORITY_MEDIUM_IMG			0x3102
#define EGL_CONTEXT_PRIORITY_LOW_IMG			0x3103
#endif

#ifndef EGL_QNX_swap_interval
#define EGL_QNX_swap_interval 1
#define EGL_SWAP_INTERVAL_QNX		0x3060  /* QuerySurface / SurfaceAttrib */
#endif

#ifndef EGL_QNX_gf_surface
#define EGL_QNX_gf_surface 1
#define EGL_GF_SURFACE_QNX			0x3061 /* QuerySurface */
#endif

#ifndef EGL_QNX_swap_pixels
#define EGL_QNX_swap_pixels 1
#ifdef EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglSwapPixelsQNX (EGLDisplay dpy, EGLSurface surface, const EGLint *rects, EGLint num_rects);
#endif /* EGL_EGLEXT_PROTOTYPES */
typedef EGLBoolean (EGLAPIENTRYP PFNEGLSWAPPIXELSQNXPROC) (EGLDisplay dpy, EGLSurface surface, const EGLint *rects, EGLint num_rects);
#endif

#ifndef EGL_QNX_blit
#define EGL_QNX_blit 1
#define EGL_BLIT_SRC_X_OFFSET_QNX		0x3062
#define EGL_BLIT_SRC_Y_OFFSET_QNX		0x3063
#define EGL_BLIT_SRC_WIDTH_QNX			0x3064
#define EGL_BLIT_SRC_HEIGHT_QNX			0x3065
#define EGL_BLIT_DST_X_OFFSET_QNX		0x3066
#define EGL_BLIT_DST_Y_OFFSET_QNX		0x3067
#define EGL_BLIT_DST_WIDTH_QNX			0x3068
#define EGL_BLIT_DST_HEIGHT_QNX			0x3069
#define EGL_BLIT_PERPIXEL_ALPHA_QNX		0x3070
#define EGL_BLIT_GLOBAL_ALPHA_QNX		0x3071
#define EGL_BLIT_FILTERING_QNX			0x3072
#define EGL_BLIT_TYPE_QNX				0x3073
#define EGL_SURFACE_WIDTH_QNX			0x3074
#define EGL_SURFACE_HEIGHT_QNX			0x3075
#define EGL_PERPIXEL_ALPHA_NONE_QNX		0x3076
#define EGL_PERPIXEL_ALPHA_SRC_QNX		0x3077
#define EGL_FILTERING_NONE_QNX			0x3078
#define EGL_FILTERING_BETTER_QNX		0x3079
#define EGL_FILTERING_FASTER_QNX		0x3080
#define EGL_BLIT_HINT_HW_QNX			0x3081
#define EGL_BLIT_HINT_SW_QNX			0x3082
#ifdef EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglBlitQNX (EGLDisplay dpy, EGLSurface src, EGLSurface dst, const EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglBlitFlushQNX (EGLDisplay dpy, EGLSurface surface);
EGLAPI EGLBoolean EGLAPIENTRY eglBlitFinishQNX (EGLDisplay dpy, EGLSurface surface);
#endif /* EGL_EGLEXT_PROTOTYPES */
typedef EGLBoolean (EGLAPIENTRYP PFNEGLBLITQNXPROC) (EGLDisplay dpy, EGLSurface src, EGLSurface dst, const EGLint *attrib_list);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLBLITFLUSHQNXPROC) (EGLDisplay dpy, EGLSurface surface);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLBLITFINISHQNXPROC) (EGLDisplay dpy, EGLSurface surface);
#endif

#ifdef __cplusplus
}
#endif

#endif
