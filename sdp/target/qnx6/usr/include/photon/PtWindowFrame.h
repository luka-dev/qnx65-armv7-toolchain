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
 *	PtWindowFrame.h
 *		Header file for the PtWindowFrame widget class
 *

 */
#ifndef __PT_WINDOWFRAME_H_INCLUDED
#define __PT_WINDOWFRAME_H_INCLUDED

#ifndef __PT_CONTAINER_H_INCLUDED
 #include <photon/PtContainer.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtWindowFrame public
 */

extern PtWidgetClassRef_t *PtWindowFrame;

/* Resources */
#define Pt_ARG_FRAME_ACTIVE			Pt_RESOURCE( 17, 0 )
#define Pt_ARG_FRAME_FLAGS			Pt_RESOURCE( 17, 1 )
#define Pt_ARG_FRAME_INACTIVE		Pt_RESOURCE( 17, 2 )
#define Pt_ARG_FRAME_RENDER			Pt_RESOURCE( 17, 3 )
#define Pt_ARG_FRAME_STATE			Pt_RESOURCE( 17, 4 )
#define Pt_ARG_FRAME_TITLE			Pt_RESOURCE( 17, 5 )
#define Pt_ARG_FRAME_TITLE_ALIGN	Pt_RESOURCE( 17, 6 )
#define Pt_ARG_FRAME_REGION_INFRONT	Pt_RESOURCE( 17, 7 )
#define Pt_ARG_FRAME_REGION_BEHIND	Pt_RESOURCE( 17, 8 )

/* Callbacks */
#define Pt_CB_FRAME_ACTION			Pt_RESOURCE( 17, 9 )
#define Pt_CB_FRAME_MOVE			Pt_RESOURCE( 17, 10 )
#define Pt_CB_FRAME_SIZE			Pt_RESOURCE( 17, 11 )

/* Resources */
#define Pt_ARG_FRAME_TITLE_COLOR	Pt_ARG_COLOR
#define Pt_ARG_FRAME_TITLE_FONT		Pt_RESOURCE( 17, 13 )
#define Pt_ARG_FRAME_MAX_DIM		Pt_RESOURCE( 17, 14 )
#define Pt_ARG_FRAME_MIN_DIM		Pt_RESOURCE( 17, 15 )
#define Pt_ARG_FRAME_BORDERS		Pt_RESOURCE( 17, 16 )
#define Pt_ARG_FRAME_TITLEHEIGHT	Pt_RESOURCE( 17, 17 )
#define Pt_ARG_FRAME_APP_REGION_INFO	Pt_RESOURCE( 17, 18 )
#define Pt_ARG_FRAME_APP_RID		Pt_RESOURCE( 17, 19 )

/* the offsets of the inside canvas */
#define Pt_ARG_FRAME_OFFSETS		Pt_RESOURCE( 17, 21 )

/* Callback structure */
typedef struct Pt_windowframe_callback {
	PhPoint_t					pos;
	PhRect_t					rect;
	int							action_type;
	int							action_code;
} PtWindowFrameCallback_t;


/* flags */
#define Pt_FRAME_DRAG_OPAQUE	0x01
#define Pt_FRAME_FORCE_FRONT	0x02
#define Pt_FRAME_BLOCKED		0x04
#define Pt_FRAME_MAXED			0x08
#define Pt_FRAME_BORDER_ACTIVE  0x10
#define Pt_FRAME_COLLAPSED		0x20
#define Pt_FRAME_ALL_FLAGS		0x3F

/* states */
#define Pt_FRAME_ACTIVE			1
#define Pt_FRAME_INACTIVE		2

/* action types */
#define Pt_ACTION_CLOSE			1
#define Pt_ACTION_MAX			2
#define Pt_ACTION_MIN			3
#define Pt_ACTION_HELP			4
#define Pt_ACTION_RET			5
#define Pt_ACTION_MENU			6
#define Pt_ACTION_MOVE			7
#define Pt_ACTION_MOVE_COMPLETE	8
#define Pt_ACTION_MOVE_INIT		9
#define Pt_ACTION_COLLAPSE		10

#define Pt_FRAME_RENDER_BUTTONS	\
  (Ph_WM_RENDER_MENU | Ph_WM_RENDER_CLOSE | Ph_WM_RENDER_HELP | \
   Ph_WM_RENDER_MIN | Ph_WM_RENDER_MAX | Ph_WM_RENDER_RETURN | Ph_WM_RENDER_COLLAPSE)

typedef struct frame_app_reg_info_t
{
	PhRegion_t 	region;
	ulong_t 	fields;
} PtFrameAppRegion_t;


/* manifests for control surfaces */

enum
{
	/* Buttons */
	
	Pt_WFRAME_MENU_ACTION = 0,		/* Menu button */
	Pt_WFRAME_MINIMIZE_ACTION,		/* Minimize button */
	Pt_WFRAME_MAXIMIZE_ACTION,		/* Maximize button */
	Pt_WFRAME_CLOSE_ACTION,			/* Close button */
	Pt_WFRAME_COLLAPSE_ACTION,      /* Collapse window frame */
	Pt_WFRAME_HELP_ACTION,			/* Help button */
	Pt_WFRAME_RETURN_ACTION,		/* Return button (for transported windows) */
	
	Pt_WFRAME_MOVE_ACTION,			/* Titlebar */
	
	/* Border areas */

	Pt_WFRAME_TOP_RESIZE_ACTION,	/* Top edge */
	Pt_WFRAME_BOTTOM_RESIZE_ACTION,	/* Bottom edge */
	Pt_WFRAME_LEFT_RESIZE_ACTION,	/* Left edge */
	Pt_WFRAME_RIGHT_RESIZE_ACTION,	/* Right edge */
	Pt_WFRAME_TL_RESIZE_ACTION,		/* Top-left corner */
	Pt_WFRAME_TR_RESIZE_ACTION,		/* Top-right corner */
	Pt_WFRAME_BL_RESIZE_ACTION,		/* Bottom-left corner */
	Pt_WFRAME_BR_RESIZE_ACTION		/* Bottom-right corner */
};

/*
 * PtWindowFrame private
 */

/* Widget structure */
typedef struct Pt_windowframe_widget
{
	PtContainerWidget_t			container;
	ulong_t						render_f;
	ulong_t						flags;
	PgColor_t					active;
	PgColor_t					inactive;
	char 						*title;
	const char					*font;
	ushort_t					alignment;
	ushort_t					state;
	PhDim_t						dim_min;
	PhDim_t						dim_max;
	PhRect_t					rect;
	PhRect_t					text_rect;
	ulong_t						drag_action;
	PhRect_t					drag_rect;
	PhRid_t						bro_in_front;
	PhRid_t						bro_behind;
/*	PtCallbackList_t			*move; */
/*	PtCallbackList_t			*size; */
/*	PtCallbackList_t			*action; */
	PhPoint_t					lastpos;
	PhRect_t 					borders;
	ushort_t					titlebar;
	uchar_t left_buttons[7];
	uchar_t right_buttons[8];
	PhRid_t						app_rid;
	PhRegion_t					*app_region;
	PhArea_t					old_win_area;
		
} PtWindowFrameWidget_t;

/* Widget union */
typedef union Pt_windowframe_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtContainerWidget_t			container;
	PtWindowFrameWidget_t		frame;
} PtWindowFrameUnion_t;


extern void PtWindowFrameSetDisjointMode( int );

#ifdef __cplusplus
};
#endif
#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtWindowFrame.h $ $Rev: 219996 $" )
#endif
