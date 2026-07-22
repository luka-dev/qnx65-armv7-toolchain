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
 *	PtWindow.h
 *		Header file for the PtWindow widget class
 *

 */
#ifndef __PT_WINDOW_H_INCLUDED
#define __PT_WINDOW_H_INCLUDED

#ifndef __PT_DISJOINT_H_INCLUDED
 #include <photon/PtDisjoint.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

#define Pt_WINDOW_ID  18

/*
 * PtWindow public
 */

extern PtWidgetClassRef_t *PtWindow;

/* Resources */
#define Pt_ARG_DEFAULT_ACTION			Pt_RESOURCE( 18, 0 )
#define Pt_ARG_ICON_FLAGS				Pt_RESOURCE( 18, 1 )
#define Pt_ARG_ICON_POS					Pt_RESOURCE( 18, 2 )
#define Pt_ARG_ICON_WINDOW				Pt_RESOURCE( 18, 3 )
#define Pt_ARG_MAX_HEIGHT				Pt_RESOURCE( 18, 4 )
#define Pt_ARG_MAX_WIDTH				Pt_RESOURCE( 18, 5 )
#define Pt_ARG_MIN_HEIGHT				Pt_RESOURCE( 18, 6 )
#define Pt_ARG_MIN_WIDTH				Pt_RESOURCE( 18, 7 )
#define Pt_ARG_WIN_PARENT				Pt_RESOURCE( 18, 8 )
#define Pt_ARG_WINDOW_CURSOR_OVERRIDE	Pt_ARG_CURSOR_OVERRIDE
#define Pt_ARG_WINDOW_FORCE_FRONT		Pt_RESOURCE( 18, 10 )
#define Pt_ARG_WINDOW_MANAGED_FLAGS		Pt_RESOURCE( 18, 11 )
#define Pt_ARG_WINDOW_NOTIFY_FLAGS		Pt_RESOURCE( 18, 12 )
#define Pt_ARG_WINDOW_RENDER_FLAGS		Pt_RESOURCE( 18, 13 )
#define Pt_ARG_WINDOW_STATE				Pt_RESOURCE( 18, 14 )
#define Pt_ARG_WINDOW_TITLE				Pt_RESOURCE( 18, 15 )
#define Pt_ARG_WINDOW_TITLE_COLOR		Pt_RESOURCE( 18, 16 )
#define Pt_CB_WINDOW					Pt_RESOURCE( 18, 17 )
#define Pt_ARG_WINDOW_ACTIVE_COLOR		Pt_RESOURCE( 18, 18 )
#define Pt_ARG_WINDOW_INACTIVE_COLOR	Pt_RESOURCE( 18, 19 )
#define Pt_ARG_WINDOW_HELP_ROOT			Pt_RESOURCE( 18, 20 )
#define Pt_CB_WINDOW_TRANSPORT			Pt_RESOURCE( 18, 21 )
#define Pt_ARG_WINDOW_FRONT_WINDOW		Pt_RESOURCE( 18, 22 )
#define Pt_CB_WINDOW_OPENING			Pt_RESOURCE( 18, 23 )
#define Pt_CB_WINDOW_CLOSING			Pt_RESOURCE( 18, 24 )
#define Pt_ARG_WINDOW_FLAGS				Pt_RESOURCE( 18, 26 )

/* Window key array element */
typedef struct Pt_window_key {
	unsigned long				state;
	ushort_t					code;
	PtWidget_t					*widget;
} PtWindowKey_t;


/* 
 * PtWindow private
 */

/* Widget structure */
typedef struct Pt_window_widget {
	PtDisjointWidget_t			disjoint;
	ulong_t						set_flags;
	ulong_t						render_flags;
	ulong_t						managed_flags;
	ulong_t						notify_flags;
	char						*title;
	char						*sender;
	PtWidget_t					*dflt_action;
/*	PtCallbackList_t			*window_cb; */
	PtWindowKey_t				*keys;
/*	PhRid_t						override_rid; */
	PtWidget_t					*icon;
	ushort_t					state;
	ushort_t					win_flags;
	ushort_t					key_count;

	ushort_t					max_height;
	ushort_t					min_height;
	ushort_t					max_width;
	ushort_t					min_width;
	PgColor_t					frame_active_color;
	PgColor_t					frame_inactive_color;
	char 						*help_root;
/*	PtCallbackList_t			*window_transport_cb; */
	PhRid_t						win_in_front;
/*	PtCallbackList_t			*window_opening; */
	PgColor_t					title_color;
/*	PtCallbackList_t			*window_closing; */
} PtWindowWidget_t;

/* Widget union */
typedef union Pt_window_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtContainerWidget_t			container;
	PtDisjointWidget_t			disjoint;
	PtWindowWidget_t			window;
} PtWindowUnion_t;

#define Pt_WINDOW_MAXING				0x8000
#define Pt_WINDOW_FORCE_FRONT			0x0001
#define Pt_WINDOW_FRAME_BLOCKABLE		0x0002
#define Pt_WINDOW_TASKBAR				0x0004
#define Pt_WINDOW_EXTENTING				0x0008
#define Pt_WINDOW_SETTING				0x0010
#define Pt_WINDOW_AREA_SET			0x0020
extern int PtWindowGetFrameSize( PtWidget_t *window, PhRect_t *rect );
#define PtWindowFrameSize( null, widget, rect ) ( (void)(null), PtWindowGetFrameSize( widget, rect ) )

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtWindow.h $ $Rev: 219996 $" )
#endif
