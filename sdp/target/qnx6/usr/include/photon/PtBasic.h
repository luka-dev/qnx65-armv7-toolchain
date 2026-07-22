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
 *	PtBasic.h
 *		Header file for the PtBasic widget class
 *

 */
#ifndef __PT_BASIC_H_INCLUDED
#define __PT_BASIC_H_INCLUDED

#ifndef __PT_WIDGET_H_INCLUDED
 #include <photon/PtWidget.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtBasic public
 */

extern PtWidgetClassRef_t *PtBasic;

#define Pt_BASIC_ID		2

/* Resources */
#define	Pt_ARG_LIGHT_BORDER_COLOR		Pt_RESOURCE( 2, 0 )
#define	Pt_ARG_LIGHT_BEVEL_COLOR		Pt_RESOURCE( 2, 0 )
#define Pt_ARG_COLOR       				Pt_RESOURCE( 2, 1 )
#define Pt_ARG_FILL_COLOR				Pt_RESOURCE( 2, 2 )
#define Pt_ARG_FILL_PATTERN				Pt_RESOURCE( 2, 3 )
#define Pt_ARG_MARGIN_HEIGHT			Pt_RESOURCE( 2, 4 )
#define Pt_ARG_MARGIN_WIDTH				Pt_RESOURCE( 2, 5 )
#define Pt_ARG_DARK_BORDER_COLOR		Pt_RESOURCE( 2, 6 )
#define Pt_ARG_DARK_BEVEL_COLOR		Pt_RESOURCE( 2, 6 )
#define Pt_CB_ARM						Pt_RESOURCE( 2, 7 )
#define Pt_CB_DISARM					Pt_RESOURCE( 2, 8 )
#define Pt_CB_ACTIVATE					Pt_RESOURCE( 2, 9 )
#define Pt_CB_GOT_FOCUS					Pt_RESOURCE( 2, 10 )
#define Pt_CB_LOST_FOCUS				Pt_RESOURCE( 2, 11 )
#define Pt_CB_REPEAT					Pt_RESOURCE( 2, 12 )
#define Pt_ARG_TRANS_PATTERN			Pt_RESOURCE( 2, 13 )
#define Pt_ARG_HIGHLIGHT_ROUNDNESS		Pt_RESOURCE( 2, 14 )
#define Pt_ARG_BASIC_FLAGS				Pt_RESOURCE( 2, 15 )
#define Pt_CB_MENU						Pt_RESOURCE( 2, 16 )
#define Pt_ARG_BANDWIDTH_THRESHOLD		Pt_RESOURCE( 2, 17 )
#define Pt_ARG_STYLE					Pt_RESOURCE( 2, 18 )
#define Pt_ARG_CONTRAST					Pt_RESOURCE( 2, 19 )
#define Pt_ARG_BORDER_CONTRAST			Pt_RESOURCE( 2, 20 )
#define Pt_ARG_BEVEL_CONTRAST			Pt_RESOURCE( 2, 20 )
#define Pt_ARG_BORDER_COLOR				Pt_RESOURCE( 2, 21 )
#define Pt_ARG_BASE_BEVEL_COLOR			Pt_RESOURCE( 2, 21 )
#define Pt_ARG_BEVEL_COLOR				Pt_RESOURCE( 2, 21 )
#define Pt_ARG_OUTLINE_COLOR			Pt_RESOURCE( 2, 22 )
#define Pt_ARG_INLINE_COLOR				Pt_RESOURCE( 2, 23 )
#define	Pt_ARG_LIGHT_FILL_COLOR			Pt_RESOURCE( 2, 24 )
#define	Pt_ARG_DARK_FILL_COLOR 		Pt_RESOURCE( 2, 25 )

#define	Pt_ARG_BOT_BORDER_COLOR			Pt_ARG_DARK_BORDER_COLOR
#define	Pt_ARG_TOP_BORDER_COLOR			Pt_ARG_LIGHT_BORDER_COLOR


/* The REAL basic flags */

#define Pt_TOP_ETCH				0x00000001
#define Pt_BOTTOM_ETCH			0x00000002
#define Pt_LEFT_ETCH			0x00000004
#define Pt_RIGHT_ETCH			0x00000008

#define Pt_TOP_OUTLINE			0x00000010
#define Pt_BOTTOM_OUTLINE		0x00000020
#define Pt_LEFT_OUTLINE			0x00000040
#define Pt_RIGHT_OUTLINE		0x00000080

#define Pt_TOP_BEVEL			0x00000100
#define Pt_BOTTOM_BEVEL			0x00000200
#define Pt_LEFT_BEVEL			0x00000400
#define Pt_RIGHT_BEVEL			0x00000800

#define Pt_TOP_INLINE			0x00001000
#define Pt_BOTTOM_INLINE		0x00002000
#define Pt_LEFT_INLINE			0x00004000
#define Pt_RIGHT_INLINE			0x00008000

#define Pt_FLAT_FILL			0x00010000
#define Pt_FULL_BORDERS			0x00020000
#define Pt_FULL_BEVELS			0x00020000
#define Pt_HORIZONTAL_GRADIENT	0x00040000
#define Pt_REVERSE_GRADIENT		0x00080000
#define Pt_STATIC_GRADIENT		0x00100000
#define Pt_STATIC_BORDERS		0x00200000
#define Pt_STATIC_BEVELS		0x00200000
#define Pt_STATIC_BORDER_COLORS	0x00400000
#define Pt_STATIC_BEVEL_COLORS	0x00400000
#define	Pt_BASIC_PREVENT_FILL	0x00800000
#define Pt_OPAQUE_ETCHES		0x01000000
#define	Pt_BLANK_ETCHES			0x02000000
#define Pt_BASIC_ARMED			0x80000000
#define Pt_BASIC_RO_FLAGS		0x80000000

#define Pt_TOP_LEFT_ETCH		(Pt_TOP_ETCH | Pt_LEFT_ETCH)
#define Pt_BOTTOM_RIGHT_ETCH	(Pt_BOTTOM_ETCH | Pt_RIGHT_ETCH)
#define Pt_ALL_ETCHED 			(Pt_TOP_LEFT_ETCH | Pt_BOTTOM_RIGHT_ETCH)
#define Pt_ALL_ETCHES			(Pt_TOP_ETCH | Pt_BOTTOM_ETCH | Pt_LEFT_ETCH | Pt_RIGHT_ETCH )

#define Pt_TOP_LEFT_OUTLINE	(Pt_TOP_OUTLINE | Pt_LEFT_OUTLINE)
#define Pt_BOTTOM_RIGHT_OUTLINE (Pt_BOTTOM_OUTLINE | Pt_RIGHT_OUTLINE )
#define	Pt_ALL_OUTLINES			(Pt_TOP_OUTLINE | Pt_BOTTOM_OUTLINE | Pt_LEFT_OUTLINE | Pt_RIGHT_OUTLINE)

#define Pt_TOP_LEFT_INLINE		(Pt_TOP_INLINE | Pt_LEFT_INLINE)
#define Pt_BOTTOM_RIGHT_INLINE (Pt_BOTTOM_INLINE | Pt_RIGHT_INLINE )
#define Pt_ALL_INLINES			(Pt_TOP_INLINE | Pt_BOTTOM_INLINE | Pt_LEFT_INLINE | Pt_RIGHT_INLINE)

#define Pt_TOP_LEFT_BEVEL		(Pt_TOP_BEVEL | Pt_LEFT_BEVEL)
#define Pt_BOTTOM_RIGHT_BEVEL (Pt_BOTTOM_BEVEL | Pt_RIGHT_BEVEL )
#define Pt_ALL_BEVELS			(Pt_TOP_BEVEL | Pt_BOTTOM_BEVEL | Pt_LEFT_BEVEL | Pt_RIGHT_BEVEL)

#define Pt_ALL_TOP				(Pt_TOP_ETCH | Pt_TOP_OUTLINE | Pt_TOP_BEVEL | Pt_TOP_INLINE)
#define Pt_ALL_BOTTOM			(Pt_BOTTOM_ETCH | Pt_BOTTOM_OUTLINE | Pt_BOTTOM_BEVEL | Pt_BOTTOM_INLINE)
#define Pt_ALL_LEFT				(Pt_LEFT_ETCH | Pt_LEFT_OUTLINE | Pt_LEFT_BEVEL | Pt_LEFT_INLINE)
#define Pt_ALL_RIGHT			(Pt_RIGHT_ETCH | Pt_RIGHT_OUTLINE | Pt_RIGHT_BEVEL | Pt_RIGHT_INLINE)
#define Pt_ALL					(Pt_ALL_TOP | Pt_ALL_BOTTOM | Pt_ALL_LEFT | Pt_ALL_RIGHT)

/* Callback structure */
typedef struct {
	int		value;
} PtBasicCallback_t;


/*
 * PtBasic private
 */

/* Widget structure */
typedef struct Pt_basic_widget {
	PtWidget_t					core;
	PgColor_t					color;
	PgColor_t					fill_color;

	char						fill_pattern[8];
	char						trans_pattern[8];

	PgColor_t					top_border_color;
	PgColor_t					top_flat_color;
	PgColor_t					bot_border_color;
	PgColor_t					bot_flat_color;
	PgColor_t					inline_color;
	PgColor_t					outline_color;
	PgColor_t					border_color;
	ushort_t					margin_height;
	ushort_t					margin_width;
	uchar_t						roundness;
	uchar_t						padding;
	uchar_t						contrast,border_contrast;

	long						flags;
/*	PtCallbackList_t			*arm; */
/*	PtCallbackList_t			*repeat; */
/*	PtCallbackList_t			*disarm; */
/*	PtCallbackList_t			*activate; */
/*	PtCallbackList_t			*menu; */
/*	PtCallbackList_t			*got_focus; */
/*	PtCallbackList_t			*lost_focus; */

} PtBasicWidget_t;

/* Widget union */
typedef union Pt_basic_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
} PtBasicUnion_t;


/*
 * PtBasic class structure additions
 */

typedef struct Pt_basic_widget_class {
	PtWidgetClass_t		core;
	void				(*got_focus_f)( PtWidget_t *, PhEvent_t * );
	int					(*lost_focus_f)( PtWidget_t *, PhEvent_t * );
	void				(*calc_opaque_f)( PtWidget_t * );
} PtBasicWidgetClass_t;

#define Pt_SET_GOT_FOCUS_F		Pt_ARG_IS_POINTER(PtBasicWidgetClass_t,got_focus_f)
#define Pt_SET_LOST_FOCUS_F		Pt_ARG_IS_POINTER(PtBasicWidgetClass_t,lost_focus_f)
#define Pt_SET_CALC_OPAQUE_F	Pt_ARG_IS_POINTER(PtBasicWidgetClass_t,calc_opaque_f)


#define PtBasicFillColor(w)		PtMember(PtBasic,w,fill_color)
/* PROTOS */
extern void PtBasicCalcHighlight( PtWidget_t * );
#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtBasic.h $ $Rev: 219996 $" )
#endif
