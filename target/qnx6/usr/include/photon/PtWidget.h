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
 *	PtWidget.h
 *		Header file for the PtWidget widget class
 *

 */
#ifndef __PT_WIDGET_H_INCLUDED
#define __PT_WIDGET_H_INCLUDED

#ifndef _STDDEF_H_INCLUDED
 #include <stddef.h>
#endif

#ifndef __PT_T_H_INCLUDED
#include <photon/PtT.h>
#endif

#include <photon/PtTransport.h>
#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtWidget public 
 */

extern PtWidgetClassRef_t *PtWidget;

#define Pt_WIDGET_ID		1

/* Resources */
#define Pt_ARG_AREA						Pt_RESOURCE( 1, 0 )
#define Pt_ARG_BEVEL_WIDTH				Pt_RESOURCE( 1, 1 )
#define Pt_ARG_BORDER_WIDTH				Pt_RESOURCE( 1, 1 )
#define Pt_ARG_CURSOR_TYPE				Pt_RESOURCE( 1, 2 )
#define Pt_ARG_CURSOR_COLOR				Pt_RESOURCE( 1, 3 )
#define Pt_ARG_DATA						Pt_RESOURCE( 1, 4 )
#define Pt_ARG_DIM						Pt_RESOURCE( 1, 5 )
#define Pt_ARG_FLAGS					Pt_RESOURCE( 1, 6 )
#define Pt_ARG_POS						Pt_RESOURCE( 1, 7 )
#define Pt_ARG_RESIZE_FLAGS				Pt_RESOURCE( 1, 8 )

#define Pt_CB_DESTROYED					Pt_RESOURCE( 1, 9 )
#define Pt_CB_HOTKEY					Pt_RESOURCE( 1, 10)

#define Pt_CB_RAW						Pt_RESOURCE( 1, 11 )
#define Pt_CB_RAW_EVENT 				Pt_RESOURCE( 1, 11 )
#define Pt_ARG_RAW_CALLBACKS			Pt_RESOURCE( 1, 11 )

#define Pt_CB_REALIZED					Pt_RESOURCE( 1, 12 )
#define Pt_CB_UNREALIZED				Pt_RESOURCE( 1, 13 )

#define Pt_ARG_USER_DATA				Pt_RESOURCE( 1, 14 )
#define Pt_ARG_HELP_TOPIC				Pt_RESOURCE( 1, 15 )
#define Pt_CB_BLOCKED					Pt_RESOURCE( 1, 16 )
#define Pt_ARG_BITMAP_CURSOR			Pt_RESOURCE( 1, 17 )
#define Pt_ARG_EFLAGS					Pt_RESOURCE( 1, 18 )
#define Pt_CB_IS_DESTROYED				Pt_RESOURCE( 1, 19 )
#define Pt_CB_DND						Pt_RESOURCE( 1, 20 )
#define Pt_ARG_EXTENT					Pt_RESOURCE( 1, 21 )
#define Pt_CB_OUTBOUND					Pt_RESOURCE( 1, 22 )
#define Pt_ARG_WIDTH					Pt_RESOURCE( 1, 23 )
#define Pt_ARG_HEIGHT					Pt_RESOURCE( 1, 24 )
#define Pt_ARG_MINIMUM_DIM				Pt_RESOURCE( 1, 25 )
#define Pt_CB_FILTER					Pt_RESOURCE( 1, 26 )
#define Pt_ARG_POINTER					Pt_RESOURCE( 1, 27 )
#define Pt_ARG_MAXIMUM_DIM				Pt_RESOURCE( 1, 30 )
#define Pt_ARG_PREFERRED_DIM			Pt_RESOURCE( 1, 31 )
#define Pt_ARG_ANCHOR_OFFSETS			Pt_RESOURCE( 10, 0) /*( 1, 28 )*/
#define Pt_ARG_ANCHOR_FLAGS				Pt_RESOURCE( 10, 1) /*( 1, 29 )*/
#define	Pt_ARG_LAYOUT_DATA				Pt_RESOURCE( 1, 34 )
#define	Pt_ARG_ROW_LAYOUT_DATA			Pt_RESOURCE( 1, 35 )
#define	Pt_ARG_GRID_LAYOUT_DATA			Pt_RESOURCE( 1, 36 )

/* Flag bits (for use with Pt_ARG_FLAGS) */
#define Pt_REALIZED				0x00000001
#define Pt_SET					0x00000002
#define Pt_AUTOHIGHLIGHT		0x00000004
#define Pt_TOGGLE				0x00000008
#define Pt_CLIP_HIGHLIGHT		0x00000010
#define Pt_OPAQUE				0x00000020
#define Pt_DELAY_ACTIVATION		Pt_DELAY_REALIZE
#define Pt_DELAY_REALIZE		0x00000040
#define Pt_SELECTABLE			0x00000080
#define Pt_HIGHLIGHTED			0x00000100
#define Pt_ETCH_HIGHLIGHT		0x00000200  /* deprecated. */
#define Pt_GETS_FOCUS			0x00000400
#define Pt_MENU_BUTTON			0x00000800
#define Pt_DESTROYED			0x00001000
#define Pt_DAMAGED				0x00002000
#define Pt_OBSCURED				0x00004000
#define Pt_IN_FLUX				0x00008000
#define Pt_CLEAR				0x00010000
#define Pt_BLOCKED				0x00020000
#define Pt_DAMAGE_FAMILY		0x00040000
#define Pt_SELECT_NOREDRAW		0x00080000
#define Pt_WIDGET_REBUILD       0x00100000
#define Pt_WIDGET_RESIZE		0x00200000
#define Pt_PROCREATED			0x00400000
#define Pt_ALL_BUTTONS			0x00800000
#define Pt_GHOST				0x01000000
#define Pt_FOCUS_RENDER			0x02000000
#define Pt_CALLBACKS_ACTIVE		0x04000000
#define Pt_MENUABLE				0x08000000

#define Pt_NOREDRAW_SET		 	0x10000000
#define Pt_FREE_MEMORY			0x20000000
#define Pt_REGION				0x40000000
#define Pt_REALIZING			0x80000000

/* EFlag bits (for use with Pt_ARG_EFLAGS) */
#define Pt_CONSUME_EVENTS		0x00000001 
#define Pt_INTERNAL_HELP		0x00000002

#define Pt_DELAY_ANCHORING		0x00000004	
#define	Pt_HAS_DAMAGED_CHILDREN	0x00000008
#define	Pt_SKIP_LAYOUT			0x00000010
#define Pt_NOTIFY_REGION		0x00010000 /* (r/o) */
#define Pt_RESIZE_EXPOSE		0x00020000 /* (r/o) */
#define Pt_RESIZE_DELAY			0x00040000 /* (r/o) */	
#define Pt_TIMER_PENDING		0x00080000	/* (r/o) */
#define Pt_USER_PREFS_VALID		0x00100000	/* (r/o) */
#define Pt_WIDGET_PREFS_VALID	0x00200000	/* (r/o) */
#define Pt_RESIZE_DAMAGED		0x00400000	/* (r/o) */
#define Pt_DAMAGE_MERGED		0x00800000	/* (r/o) */
#define Pt_REPARENTING			0x01000000	/* (r/o) */
#define Pt_OPAQUE_VALID			0x02000000	/* (r/o) */
#define Pt_CANVAS_VALID			0x04000000	/* (r/o) */
#define Pt_DOOMED				0x08000000	/* (r/o) */ 
#define Pt_WIN_REQUEST			0x10000000	/* (r/o) */
#define Pt_DRAW_SKIP_CHILDREN	0x20000000	/* (r/o) */
#define Pt_PARENT_HAS_DC		0x40000000	/* (r/o) */
#define Pt_DAMAGE_ON_FOCUS		0x80000000	/* (r/o) */
#define Pt_RO_EFLAGS 			0xfffc0000

/* RESIZE MASKS  */

#define Pt_RESIZE_BITS			0x07
#define Pt_RESIZE_Y_SHIFT		20
#define Pt_RESIZE_X_SHIFT		23
#define Pt_INITIALIZED		0x04000000
#define Pt_UCLIP			0x08000000

/* Convenience resize defines */
#define Pt_RESIZE_Y_ALWAYS			(Pt_ALWAYS 		<< Pt_RESIZE_Y_SHIFT)
/* 0x00100000 */

#define Pt_RESIZE_Y_AS_REQUIRED		(Pt_AS_REQUIRED << Pt_RESIZE_Y_SHIFT)
/* 0x00200000 */

#define Pt_RESIZE_Y_INITIAL			(Pt_INITIAL 	<< Pt_RESIZE_Y_SHIFT)
/* 0x00400000 */

#define Pt_RESIZE_Y_BITS			(Pt_RESIZE_BITS	<< Pt_RESIZE_Y_SHIFT)
/* 0x00700000 */

#define Pt_RESIZE_X_ALWAYS			(Pt_ALWAYS 		<< Pt_RESIZE_X_SHIFT)
/* 0x00800000 */

#define Pt_RESIZE_X_AS_REQUIRED		(Pt_AS_REQUIRED << Pt_RESIZE_X_SHIFT)
/* 0x01000000 */

#define Pt_RESIZE_X_INITIAL			(Pt_INITIAL 	<< Pt_RESIZE_X_SHIFT)
/* 0x02000000 */

#define Pt_RESIZE_X_BITS			(Pt_RESIZE_BITS	<< Pt_RESIZE_X_SHIFT)
/* 0x03800000 */

#define Pt_RESIZE_XY_ALWAYS			(Pt_RESIZE_X_ALWAYS |Pt_RESIZE_Y_ALWAYS)
#define Pt_RESIZE_XY_AS_REQUIRED	(Pt_RESIZE_X_AS_REQUIRED|Pt_RESIZE_Y_AS_REQUIRED)
#define Pt_RESIZE_XY_INITIAL		(Pt_RESIZE_X_INITIAL |Pt_RESIZE_Y_INITIAL)
#define Pt_RESIZE_XY_BITS			(Pt_RESIZE_X_BITS |Pt_RESIZE_Y_BITS)

/*** ANCHOR FLAG MANIFESTS  ***/
#define Pt_LEFT_ANCHORED_RELATIVE		0x00000001
#define Pt_RIGHT_ANCHORED_RELATIVE		0x00000002
#define Pt_TOP_ANCHORED_RELATIVE		0x00000004
#define Pt_BOTTOM_ANCHORED_RELATIVE		0x00000008

#define Pt_LEFT_ANCHORED_RIGHT			0x00000010
#define Pt_RIGHT_ANCHORED_RIGHT			0x00000020
#define Pt_TOP_ANCHORED_BOTTOM			0x00000040
#define Pt_BOTTOM_ANCHORED_BOTTOM		0x00000080

#define Pt_LEFT_ANCHORED_LEFT			0x00000100
#define Pt_RIGHT_ANCHORED_LEFT			0x00000200
#define Pt_TOP_ANCHORED_TOP				0x00000400
#define Pt_BOTTOM_ANCHORED_TOP			0x00000800

#define Pt_ANCHOR_FLAGS_MASK			0x00000FFF

/*convenience... */
#define Pt_LEFT_IS_ANCHORED		(Pt_LEFT_ANCHORED_RIGHT|Pt_LEFT_ANCHORED_LEFT| Pt_LEFT_ANCHORED_RELATIVE)
#define Pt_TOP_IS_ANCHORED		(Pt_TOP_ANCHORED_TOP|Pt_TOP_ANCHORED_BOTTOM|Pt_TOP_ANCHORED_RELATIVE)
#define Pt_RIGHT_IS_ANCHORED	(Pt_RIGHT_ANCHORED_LEFT|Pt_RIGHT_ANCHORED_RIGHT|Pt_RIGHT_ANCHORED_RELATIVE)
#define Pt_BOTTOM_IS_ANCHORED	(Pt_BOTTOM_ANCHORED_TOP|Pt_BOTTOM_ANCHORED_BOTTOM|Pt_BOTTOM_ANCHORED_RELATIVE)
#define Pt_IS_ANCHORED (Pt_LEFT_IS_ANCHORED|Pt_RIGHT_IS_ANCHORED|Pt_TOP_IS_ANCHORED|Pt_BOTTOM_IS_ANCHORED)
#define Pt_ANCHOR_LEFT_RIGHT		(Pt_LEFT_ANCHORED_LEFT|Pt_RIGHT_ANCHORED_RIGHT)
#define Pt_ANCHOR_TOP_BOTTOM	(Pt_TOP_ANCHORED_TOP|Pt_BOTTOM_ANCHORED_BOTTOM)
#define Pt_ANCHOR_ALL					(Pt_ANCHOR_TOP_BOTTOM|Pt_ANCHOR_LEFT_RIGHT)

#define Pt_BALLOONS_ON					0x00001000

/* Private anchor flag values */
#define Pt_REGISTERED_ANCHORING	0x08000000 /* (r/o) */
#define Pt_ANCHORS_LOCKED				0x04000000 /* (r/o) */
#define Pt_BALLOONS_ACTIVE				0x02000000 /* (r/o) */
#define Pt_CONTAINER_RESIZING		0x01000000 /* (r/o) */
#define Pt_BALLOONS_LOCKED			0x80000000 /* (r/o) */
#define Pt_ANCHORS_INVALID				0x60000000 /* (r/o) */
#define Pt_X_ANCHORS_INVALID		0x40000000 /* (r/o) */
#define Pt_Y_ANCHORS_INVALID			0x20000000 /* (r/o) */
#define Pt_ANCHORING						0x10000000 /* (r/o) */


struct pt_dnd_callback_info {
	PtTransportCtrl_t	*trans_ctrl;
	int unsigned		fetch_index;
	PhTransportHdr_t	*trans_hdr;
	void 				*data;
	int unsigned		flags;
	int unsigned		handle;			/* for stream data, handle will be in next callback. */
	PhCursorDescription_t *cursor;		/* for multiple acking. */
	PtDndFetchPending_t *fetch_pending;
	void				*trans_private;
	};

/* flags for PtDndCallbackInfo_t */
#define Ph_DND_PREVENT_ACK	0x00000001

/*
 * PtWidget private
 */
/*
typedef struct pt_widget_ex_data {
	} PtWidgetExData_t;
*/

/* Subclasses can extend this area via
 *
 * typedef struct pt_mywidget_ex_data{
 *		PtWidgetExData_t	wd;
 *		int					number_member;
 *		char				*myfirst_res;
 *		PtCallbackList_t	*myforgotten_callbacks;
 *		} PtMyWidgetExData_t;
 *
 *	If using this facility, the Pt_SET_EX_STATE_LEN must be set
 *	in order for PtSet/GetResources to work automatically.
 *	All resources placed in this extended area need to be qualified as
 *	Pt_ARG_IN_EXDATA resources:
 *		i.e. Pt_ARG_IS_NUMBER( PtMyWidgetExData_t, number_member ) | Pt_ARG_IN_EXDATA, ...
 */

 
/* Base widget structure */
struct Pt_widget {
	struct Pt_widget_class	*class_rec;
	struct Pt_widget		*parent;
	struct Pt_widget		*child;
	struct Pt_widget		*brother;
	struct Pt_widget		*bro_behind;
	PhRid_t					rid;
	PhArea_t				area;
	PhArea_t				old_area;
	PhRect_t				extent;
	long					flags;
	ushort_t				extent_valid; 
	ushort_t				border_width;
	ulong_t					region_fields;
	ulong_t					resize_flags;
	PgColor_t				cursor_color;
	PhTile_t				*opaque_list;
	PhTile_t				*damage_list;
	char					*data;
	char					*user_data;
	PtCallbackLists_t		cb_lists;
	char					*exdata;
	char					*help_topic;
	int						is_immortal;
	PhBitmapCursorRData_t	*bitmap_cursor;
	PtDataHdr_t				*widget_data;
	ulong_t					eflags;
	PtSurfaceCtrl_t			surface_ctrl;
	PhRect_t				canvas;
	PtWidgetClassStyle_t 	*style;
	PhDim_t					min_dim;
	PhDim_t					pref_dim;
	PhDim_t					user_pref_dim;
	PhDim_t					max_dim;
	void					*ptr;
	uint_t					anchor_flags;
	PhRect_t				anchor_offset;
	ushort_t				cursor_type;
	ushort_t				spare;
	PhTile_t				*visible_tiles;
};


/* macros to check widget states */

#define PtWidgetIsDisabled(w)		(((PtWidget_t*)(w))->flags & (Pt_BLOCKED | Pt_GHOST))
#define PtWidgetIsArmed(w)			(((PtWidget_t*)(w))->flags & Pt_SET)
#define PtWidgetIsDisarmed(w)		(!PtWidgetIsArmed(w))
#define PtWidgetShowFocus(w)		((((PtWidget_t*)(w))->flags & Pt_FOCUS_RENDER) && PtIsFocused((PtWidget_t*)(w)))

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtWidget.h $ $Rev: 219996 $" )
#endif
