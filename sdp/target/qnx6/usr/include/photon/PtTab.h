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
 *	PtTab.h
 *		Header file for the PtTab widget class
 *

 */
#ifndef __PT_TAB_H_INCLUDED
#define __PT_TAB_H_INCLUDED

#include <photon/PtLabel.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtTab public
 */

extern PtWidgetClassRef_t *const PtTab;


/* PtTab Resources */

#define	Pt_ARG_TAB_FLAGS				Pt_RESOURCE( 58, 0 )
#define	Pt_ARG_TAB_UNSELECTED_COLOR		Pt_RESOURCE( 58, 1 )


/* PtTab Flag Manifests */

#define Pt_TAB_UPSIDE_DOWN		0x1
#define Pt_TAB_RIGHTSIDE_LEFT	0x2
#define Pt_TAB_DRAG_HANDLE		0x4		/* render drag handle if set */
#define Pt_TAB_MULTI			0x8		/* tab represents multiple items */

/* Widget structure */

typedef struct pt_tab_widget
{
	PtLabelWidget_t label;
	PgColor_t unselected_color;
	PgColor_t unselected_top,unselected_bot;
	unsigned long flags;
	PhRect_t drag_handle;
	
} PtTabWidget_t;


/* Widget union */

typedef union pt_tab_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtLabelWidget_t				label;
	PtTabWidget_t				tab;
	
} PtTabUnion_t;


/* macros to check tab states */

#define PtTabIsUpsideDown(w)		(((PtTabWidget_t*)(w))->flags & Pt_TAB_UPSIDE_DOWN)
#define PtTabIsRightsideUp(w)		(!PtTabIsUpsideDown(w))
#define PtTabIsRightsideLeft(w)		(((PtTabWidget_t*)(w))->flags & Pt_TAB_RIGHTSIDE_LEFT)
#define PtTabIsRightsideRight(w)	(!PtTabIsRightsideLeft(w))
#define PtTabIsDraggable(w)			(((PtTabWidget_t*)(w))->flags & Pt_TAB_DRAG_HANDLE)
#define PtTabIsMulti(w)				(((PtTabWidget_t*)(w))->flags & Pt_TAB_MULTI)
#define PtTabDragHandleRect(w,r)	((r) ? (PhRect_t*)(memcpy((void*)(r),(void*)(&((PtTabWidget_t*)(w))->drag_handle),sizeof(PhRect_t))) : &((PtTabWidget_t*)(w))->drag_handle)

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtTab.h $ $Rev: 219996 $" )
#endif
