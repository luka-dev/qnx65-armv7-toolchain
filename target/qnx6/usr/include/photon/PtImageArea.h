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
 *	PtImageArea.h
 *		Header file for the PtImageArea widget class
 *

 */
#ifndef __PT_IMAGEAREA_H_INCLUDED
#define __PT_IMAGEAREA_H_INCLUDED

#ifndef __PT_CONTAINER_H_INCLUDED
 #include <photon/PtContainer.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

extern PtWidgetClassRef_t *PtImageArea;

/* Resources */
#define Pt_ARG_IMAGEAREA_IMAGE					Pt_RESOURCE( 103, 0 )
#define Pt_ARG_IMAGEAREA_TOP					Pt_RESOURCE( 103, 5 )
#define Pt_ARG_IMAGEAREA_LEFT					Pt_RESOURCE( 103, 6 )
#define Pt_ARG_IMAGEAREA_ZOOM					Pt_RESOURCE( 103, 7 )
#define Pt_ARG_IMAGEAREA_FLAGS					Pt_RESOURCE( 103, 8 )
#define Pt_ARG_IMAGEAREA_SELECTION				Pt_RESOURCE( 103, 12 )
#define Pt_ARG_IMAGEAREA_GRID_THRESHOLD			Pt_RESOURCE( 103, 13 )
#define Pt_ARG_IMAGEAREA_GRID_COLOR				Pt_RESOURCE( 103, 14 )
#define Pt_CB_IMAGEAREA_SCROLLED				Pt_RESOURCE( 103, 9 )
#define Pt_CB_IMAGEAREA_MOVEMENT				Pt_RESOURCE( 103, 10 )
#define Pt_CB_IMAGEAREA_SELECTION				Pt_RESOURCE( 103, 11 )
#define Pt_CB_IMAGEAREA_DRAG					Pt_RESOURCE( 103, 15 )

/* Image area flags */
#define Pt_IMAGEAREA_RENDERED			0x1
#define Pt_IMAGEAREA_AUTOSCALE			0x2
#define Pt_IMAGEAREA_ENABLE_SELECTION	0x4
#define Pt_IMAGEAREA_EDITABLE_SELECTION	0x8
#define Pt_IMAGEAREA_NO_MEMORY			0x10

/* Pt_CB_IMAGEAREA_SCROLLED reason subtypes */
#define Pt_IMAGEAREA_SCROLLED_X	1
#define Pt_IMAGEAREA_SCROLLED_Y	2

/* Pt_CB_IMAGEAREA_SELECTION/DRAG reason subtypes */
#define Pt_IMAGEAREA_INIT		1
#define Pt_IMAGEAREA_DRAG		2
#define Pt_IMAGEAREA_COMPLETE	3

/* Internal widget flags */
#define Pt_IMAGEAREA_IMGCRC_VALID	0x1
#define Pt_IMAGEAREA_PALCRC_VALID	0x2

/* callback structure */
typedef struct Pt_imageArea_callback
{
	PhRect_t rect;

} PtImageAreaCallback_t;

/* Widget structure */
typedef struct Pt_imagearea_widget
{
	PtContainerWidget_t container;
	PhImage_t *image;
	long zoom,gridThreshold;
	PgColor_t gridColor;
	PhPoint_t topLeft;
	PhRect_t selection;
	unsigned short scrollHorzPolicy,scrollVertPolicy;
	short scrollHorzHeight,scrollVertWidth;
	short hAlign,vAlign;
	PtWidget_t *display,*horz,*spacer,*vert;
/*	PtCallbackList_t *scrolled,*movement,*selected,*dragged; */
	PhImage_t buffer;
	short flags,iflags;
	unsigned short cursorType,lastCursorType;
	const char *errFont;
	char *errString;
	size_t shmemSize;
} PtImageAreaWidget_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtImageArea.h $ $Rev: 219996 $" )
#endif
