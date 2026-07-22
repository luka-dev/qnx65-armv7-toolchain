/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to QNX 
 * Software Systems before you may reproduce, modify or distribute this software, 
 * or any work that includes all or part of this software.   Free development 
 * licenses are available for evaluation and non-commercial purposes.  For more 
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *  
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/ 
 * for other information.
 * $
 */



/*
 * PhInternal.h	
 *
 *		Photon library control structure
 *

 */
#ifndef __PHCTRL_H_INCLUDED
#define __PHCTRL_H_INCLUDED

#ifndef _LIMITS_H_INCLUDED
 #include <limits.h>
#endif

/*#ifndef __MOUSE_H_INCLUDED
 #include <sys/mouse.h>
#endif */

#ifndef __PH_GLIB_H_INCLUDED
#include <photon/Pg.h>
#endif

#include <photon/Pf.h>

#include <photon/PhPack.h>

#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __PH_GLIB_H_INCLUDED
/* Simple font metrics */
/* This is also defined in Pg.h ??? */
struct _Ph_font_widths {
	char			face[20];
	PhRect_t		extent;
	ushort_t		valid;
	ushort_t		ascii_offset;
	ushort_t		ascii_length;
	char			widths[256];
};
#endif

struct Ph_soul_entry {
	void					*next;
	unsigned short			 hold_count;
	unsigned short			 num_souls;
	unsigned short			 size;
	unsigned short			 min;
	unsigned				 reserved[2];
};

struct _Ph_Draw_Context
{
    	int		(*flush)( PhDrawContext_t *dc, int subtype );
    	int		(*modify)( PhDrawContext_t *dc, int acquire, void *data );
    	int32_t	type;
	long    flags;
	void	*dc_exp;
	PhGC_t	*dflt_gc, *gc, *buf_gc;
	struct _Ph_g_info gin;
	PhTile_t	*event_clip_tiles;
};

/* Draw context flags */
#define Ph_INLINE_SHMEM_OBJECTS	0x00000001
#define Ph_TEXT_EXTENTS		0x00000002
#define Ph_SUPRESS_PARENT_CLIP	0x00000004
#define Ph_SYNC_GCS		0x00000008 /* swaps gc-> bug_gc of activating gc. */
#define Ph_LOCAL_RENDERER	0x00000010 /* the renderer for this context is in the same address space as the
						  Context.*/
#define Ph_RESIZE_DRAW_BUFFERS  0x00000020 /* Draw buffer of the dc will automatically attempt to resize itself
                                              if full, up to the maximum size of a draw buffer */								
#define Ph_DIRECT_EVENTS	0x00000040

/* modify acquire values. */
#define Ph_QUERY_DC_GRAFX_INFO	0x80000000

/* Draw target manifests for PhCreateDC ( Draw context TYPEs ) */
#define Ph_DRAW_TO_PHOTON			0
#define Ph_DRAW_TO_PRINT_CONTEXT	1
#define Ph_DRAW_TO_MEMORY_CONTEXT	2
#define Ph_DRAW_TO_OFFSCREEN_MEMORY	4
#define	Ph_DRAW_DIRECT				5
#define Ph_DRAW_TO_OPENGL			6
/* Not yet supported */
#define Ph_DRAW_TO_SERVICE			300000

/* The channel control structure */
struct _Ph_ctrl {
#if defined(__linux__) || defined(__CYGWIN__)
	COID_T                      phipc;
#else
	int							fd;
	int							channel;
	int							connection;
	int							pulse_code;
	int							pulse_value;
#endif
	long						id;
	unsigned					reserved[ 8 ];
	char						*device;
	struct _Pf_ctrl				*font;
	pthread_mutex_t 			draw_context_lock;	 /* lock for the draw_context */
	PhDrawContext_t				*draw_context;
	pthread_mutex_t 			dflt_draw_context_lock; /* lock for the dflt_draw_context, for flush functions that must use this */
	PhDrawContext_t				*dflt_draw_context;
	void						*data;
};
/* manifests for use in draw context modify functions
   modify state */
#define Ph_CREATED_DC		3
#define Ph_ACTIVATE_DC		0
#define Ph_DEACTIVATE_DC	1
#define Ph_DESTROYING_DC	2
#define Ph_REACTIVATE_DC	4
#define Ph_MODFLAGS_DC		5
/* Context specific >1 */

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PhInternal.h $ $Rev: 219996 $" )
#endif
