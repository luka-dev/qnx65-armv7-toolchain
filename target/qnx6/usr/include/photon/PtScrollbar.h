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
 *	PtScrollbar.h
 *		Header file for the PtScrollbar widget class
 *

 */
#ifndef __PT_SCROLLBAR_H_INCLUDED
#define __PT_SCROLLBAR_H_INCLUDED

#ifndef __PT_GAUGE_H_INCLUDED
#include <photon/PtGauge.h>
#endif

#ifndef __PT_GENLIST_H_INCLUDED
#include <photon/PtGenList.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtScrollbar public
 */

extern PtWidgetClassRef_t *PtScrollbar;


/* resources */

#define Pt_ARG_INCREMENT			Pt_RESOURCE( 29, 1 )
#define Pt_ARG_PAGE_INCREMENT		Pt_RESOURCE( 29, 5 )
#define Pt_ARG_SLIDER_SIZE			Pt_RESOURCE( 29, 7 )
#define Pt_ARG_SCROLLBAR_FLAGS		Pt_RESOURCE( 29, 9 )
#define Pt_CB_SCROLLBAR_MOVE		Pt_RESOURCE( 29, 10 )
#define Pt_ARG_MIN_SLIDER_SIZE		Pt_RESOURCE( 29, 11 )
#define Pt_ARG_SB_TROUGH_COLOR		Pt_RESOURCE( 29, 12 )

/* deprecated resources */

#define Pt_ARG_SCROLL_POSITION	Pt_ARG_GAUGE_VALUE
#define Pt_ARG_SCROLLBAR_POSITION	Pt_ARG_GAUGE_VALUE

/* Scrollbar flag bits */

#define Pt_SCROLLBAR_SHOW_ARROWS		0x0002
#define Pt_SCROLLBAR_FIXED_SLIDER_SIZE	0x0008
#define Pt_SCROLLBAR_FOCUSED			0x0080 

#define Pt_SCROLLBAR_SLIDER_MIN_SIZE	0x0200
#define Pt_SCROLLBAR_HI_BANDWIDTH		0x0400
#define Pt_SCROLLBAR_RESYNC				0x0800
#define Pt_SCROLLBAR_DAMAGE_SLIDER		0x1000
#define Pt_SCROLLBAR_DAMAGE_PGINCDEC	0x2000
#define Pt_SCROLLBAR_DAMAGE_INCDEC		0x4000
#define Pt_SCROLLBAR_DRAGGING			0x8000
#define Pt_SCROLLBAR_RO_FLAGS			0xfe00

#define Pt_SCROLLBAR_EX_RESOURCES	1
typedef struct scrollbar_ex_resources {
	PgColor_t background;
	} PtScrollbarExResources_t;

/* Callback structure */

typedef struct Pt_scrollbar_callback
{
	unsigned	action;
	int			position;

} PtScrollbarCallback_t;


/* manifests for widget actions */

enum
{
	Pt_SCROLLBAR_INCREMENT_ACTION = 0,
	Pt_SCROLLBAR_DECREMENT_ACTION,
	Pt_SCROLLBAR_PAGE_INCREMENT_ACTION,
	Pt_SCROLLBAR_PAGE_DECREMENT_ACTION,
	Pt_SCROLLBAR_DRAG_ACTION,
	Pt_SCROLLBAR_POSITION_ACTION
};

/* Widget structure */

typedef struct Pt_scrollbar_widget
{
	PtGaugeWidget_t	gauge;

	ushort_t			flags;
	ushort_t			min_slider_size;

	int					increment;
	int					page_increment;
	int					slider_size;

	short				tl_damage_fringe;
	short				br_damage_fringe;
	
/*	PtCallbackList_t	*moved; */
	long				band_threshold;

	int					drag_unit_pos;
	short				drag_pixel_pos;
	ushort_t			trough_length;
	PgColor_t			trough_color;
	
} PtScrollbarWidget_t;

/* Widget union */
typedef union Pt_scrollbar_union
{
	PtWidget_t			core;
	PtBasicWidget_t		basic;
	PtGaugeWidget_t		gauge;
	PtScrollbarWidget_t	scrollbar;

} PtScrollbarUnion_t;


extern void PtSyncScrollbar( PtWidget_t * );
extern int PtScrollbarSliderSize(PtWidget_t * );
extern int PtScrollbarToUnits(PtWidget_t * ,int );
extern void PtScrollbarToPixels(PtWidget_t *, int * ,int );
extern void PtScrollbarAction(PtWidget_t *, uchar_t, int, PhEvent_t * );

/* macros to check scrollbar states */

#define PtScrollbarAtMinimum(w)		(PtGaugeValue(w) <= PtGaugeMinimum(w))
#define PtScrollbarAtMaximum(w)		(PtGaugeValue(w) >= (PtGaugeMaximum(w) - PtScrollbarSliderSize(w) + 1))

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtScrollbar.h $ $Rev: 219996 $" )
#endif
