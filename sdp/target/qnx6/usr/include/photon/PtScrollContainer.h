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
 *	PtScrollContainer.h
 *		Header file for the PtScrollContainer widget class
 *

 */

#ifndef __PT_SCROLLCONTAINER_H_INCLUDED
#define __PT_SCROLLCONTAINER_H_INCLUDED

#ifndef __PT_SCROLLAREA_H_INCLUDED
 #include <photon/PtScrollArea.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtScrollContainer public
 */

extern PtWidgetClassRef_t *PtScrollContainer;

/* Resources */

#define Pt_ARG_SCROLLCONT_FLAGS			Pt_RESOURCE( 70, 0 )
#define Pt_ARG_SCROLLCONT_RESIZE_FLAGS	Pt_RESOURCE( 70, 1 )


/*
 * PtScrollContainer flags
 */

#define Pt_SCROLLCONT_TRACK_FOCUS 	0x0001	/* pan to accomodate focused child */

#define Pt_SCROLLCONT_RO_FLAGS		0

/*
 * PtScrollContainer private 
 */

/* Widget structure */

typedef struct Pt_scroll_container_widget
{
	PtScrollAreaWidget_t scrollarea;

	uint16_t flags;
	uint16_t padding;
	
	uint16_t max_x;
	uint16_t max_y;
	
	long	world_resize;

	PtWidget_t *viewport;
	PtWidget_t *world;

} PtScrollContainerWidget_t;

/* Widget union */

typedef union Pt_scroll_container_union
{
	PtWidget_t core;
	PtBasicWidget_t basic;
	PtContainerWidget_t container;
	PtScrollAreaWidget_t scrollarea;
	PtScrollContainerWidget_t scrollcont;

} PtScrollContainerUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtScrollContainer.h $ $Rev: 219996 $" )
#endif
