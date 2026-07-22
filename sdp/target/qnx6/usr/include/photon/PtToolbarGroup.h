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
 *	PtToolbarGroup.h
 *		Header file for the PtToolbarGroup widget class
 *

 */
 
#ifndef __PT_TOOLBARGROUP_H_INCLUDED
#define __PT_TOOLBARGROUP_H_INCLUDED

#include <photon/PtGroup.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

extern PtWidgetClassRef_t *PtToolbarGroup;

/* Resources */
#define Pt_ARG_TG_FLAGS			Pt_RESOURCE( 62, 0 )

/* Widget flags */

#define Pt_TG_COLLAPSIBLE		0x1		/* Toolbars are collapsible */
#define Pt_TG_ANIMATION			0x2		/* Animate on collapse/expand */
#define Pt_TG_RT_EXTENT			0x4		/* If animation enabled, extent with animation */
#define Pt_TG_HORIZONTAL		0x8000	/* read-only */
#define Pt_TG_RO_FLAGS			0xf000

/* Widget structure */

typedef struct pt_toolbargroup_widget
{
	PtContainerWidget_t container;		/* Super class */

	uint16_t flags;						/* PtToolbarGroup flags */
	uint16_t dz_fringe_width;			/* Width (thickness) of dropzone outer fringe */

	int16_t nchildren;					/* number of realized children */
	int16_t padding;

	PtWidget_t *drag;					/* toolbar being dnd'd */
	
} PtToolbarGroupWidget_t;


/* Widget union */

typedef union pt_toolbargroup_union
{
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtContainerWidget_t			container;
	PtToolbarGroupWidget_t		toolbargroup;

} PtToolbarGroupUnion_t;

#define PtTGIsHorizontal(w)	(((PtToolbarGroupWidget_t*)(w))->flags & Pt_TG_HORIZONTAL)
#define PtTGIsVertical(w)	(!PtTGIsHorizontal(w))

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtToolbarGroup.h $ $Rev: 219996 $" )
#endif
