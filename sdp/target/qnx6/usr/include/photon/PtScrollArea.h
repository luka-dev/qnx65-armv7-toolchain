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
 *	PtScrollArea.h
 *		Header file for the PtScrollArea widget class
 *

 */

#ifndef __PT_SCROLLAREA_H_INCLUDED
#define __PT_SCROLLAREA_H_INCLUDED

#ifndef __PT_CONTAINER_H_INCLUDED
 #include <photon/PtContainer.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtScrollArea public
 */

extern PtWidgetClassRef_t *PtScrollArea;

#define Pt_SCROLLAREA_ID		13

/* Resources */
#define Pt_ARG_SCROLLAREA_INCREMENT_X		Pt_RESOURCE( 13, 0 )
#define Pt_ARG_SCROLLAREA_INCREMENT_Y		Pt_RESOURCE( 13, 1 )
#define Pt_ARG_SCROLLAREA_MAX_X				Pt_RESOURCE( 13, 2 )
#define Pt_ARG_SCROLLAREA_MAX_Y				Pt_RESOURCE( 13, 3 )
#define Pt_ARG_SCROLLAREA_POS_Y				Pt_RESOURCE( 13, 4 )
#define Pt_ARG_SCROLLAREA_POS_X				Pt_RESOURCE( 13, 5 )
#define Pt_ARG_SCROLL_AREA_MAX_X			Pt_RESOURCE( 13, 2 )
#define Pt_ARG_SCROLL_AREA_MAX_Y			Pt_RESOURCE( 13, 3 )
#define Pt_ARG_SCROLL_AREA_POS_Y			Pt_RESOURCE( 13, 4 )
#define Pt_ARG_SCROLL_AREA_POS_X			Pt_RESOURCE( 13, 5 )
#define Pt_ARG_SCROLLBAR_X_DISPLAY			Pt_RESOURCE( 13, 6 )
#define Pt_ARG_SCROLLBAR_X_HEIGHT			Pt_RESOURCE( 13, 7 )
#define Pt_ARG_SCROLLBAR_Y_DISPLAY			Pt_RESOURCE( 13, 8 )
#define Pt_ARG_SCROLLBAR_Y_WIDTH			Pt_RESOURCE( 13, 9 )
#define Pt_ARG_SCROLLAREA_FLAGS				Pt_RESOURCE( 13, 12 )
#define Pt_ARG_SCROLL_AREA_FLAGS			Pt_RESOURCE( 13, 12 )
#define Pt_CB_SCROLLAREA_SCROLLED			Pt_RESOURCE( 13, 13 )
#define Pt_ARG_SCROLLAREA_SCROLLBAR_COLOR	Pt_RESOURCE( 13, 14 )

/*
 * PtScrollArea flags
 */

#define Pt_SCROLLAREA_IGNORE_KEYS 	0x0001
#define Pt_SCROLLAREA_ENABLE_PAN	0x0004

#define Pt_SCROLLAREA_PAN_STARTED	0x0800	/* read-only */
#define Pt_SCROLLAREA_PANNING		0x1000	/* read-only */
#define Pt_SCROLLAREA_SCROLL_X		0x2000	/* read-only */
#define Pt_SCROLLAREA_SCROLL_Y		0x4000	/* read-only */
#define Pt_SCROLLAREA_SCROLL_XY		0x6000	/* read-only */
#define Pt_SCROLLAREA_ENABLE_BLIT	0x8000	/* read-only */
#define Pt_SCROLL_AREA_RO_FLAGS		0xf800

typedef struct pt_scroll_area_callback
{
	int32_t old_x,new_x;
	int32_t old_y,new_y;

} PtScrollAreaCallback_t;

/* callback reason subtypes */

#define Pt_SCROLLAREA_X_CHANGED		0x1
#define Pt_SCROLLAREA_Y_CHANGED		0x2
#define Pt_SCROLLAREA_XY_CHANGED	0x3

/*
 * PtScrollArea private 
 */

/* Widget structure */
typedef struct Pt_scroll_area_widget
{
	PtContainerWidget_t container;

	uint16_t flags;
	uint8_t scrollbar_x_display;
	uint8_t scrollbar_y_display;

	uint8_t scrollbar_x_height;
	uint8_t scrollbar_y_width;
	
	int32_t max_x,max_y;
	int32_t pos_x,pos_y;
	int32_t given_x,given_y;

/*	PtCallbackList_t			*scrolled; */

	PtWidget_t					*scrollbar_x;
	PtWidget_t					*scrollbar_y;

	PhPoint_t					pan_pos;

} PtScrollAreaWidget_t;

/* Widget union */

typedef union Pt_scroll_area_union
{
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtContainerWidget_t			container;
	PtScrollAreaWidget_t		scarea;

} PtScrollAreaUnion_t;

/* PtScrollArea class structure additions */

typedef struct Pt_scrollarea_widget_class
{
	PtContainerClass_t container;
	void (*scrolled_f)( PtWidget_t *, long, long , long, long, PhEvent_t * );

} PtScrollAreaClass_t;

#define Pt_SET_SCROLLED_F	(Pt_ARG_IS_POINTER(PtScrollAreaClass_t, scrolled_f))

extern int PtScrollAreaSetPos( PtWidget_t *, long, long, int, PhEvent_t * );
extern PhRect_t *PtScrollAreaCanvas( PtWidget_t *, PhRect_t * );

#define Pt_SCROLLAREA_SET_X		0x1
#define Pt_SCROLLAREA_SET_Y		0x2
#define Pt_SCROLLAREA_SET_XY	0x3

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtScrollArea.h $ $Rev: 219996 $" )
#endif
