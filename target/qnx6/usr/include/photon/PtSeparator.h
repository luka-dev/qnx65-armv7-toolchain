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
 *	PtSeparator.h
 *		Header file for the PtSeparator widget class
 *

 */
#ifndef __PT_SEPARATOR_H_INCLUDED
#define __PT_SEPARATOR_H_INCLUDED

#ifndef __PT_BASIC_H_INCLUDED
 #include <photon/PtBasic.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtSeparator public
 */

extern PtWidgetClassRef_t *PtSeparator;

/* Resources */
#define Pt_ARG_SEP_FLAGS				Pt_RESOURCE( 30, 0 )
#define Pt_ARG_SEP_ORIENTATION			Pt_RESOURCE( 30, 1 )
/*depricated boolean --^ ... use flags. */
#define Pt_ARG_SEP_TYPE					Pt_RESOURCE( 30, 2 )
#define	Pt_ARG_SEP_DRAG_BOUNDS			Pt_RESOURCE( 30, 3 )
#define	Pt_ARG_SEP_IMAGE				Pt_RESOURCE( 30, 4 )
#define	Pt_ARG_SEP_IMAGE_H_ALIGN		Pt_RESOURCE( 30, 5 )
#define	Pt_ARG_SEP_IMAGE_V_ALIGN		Pt_RESOURCE( 30, 6 )
#define	Pt_ARG_SEP_ARM_CURSOR_TYPE		Pt_RESOURCE( 30, 7 )
#define	Pt_ARG_SEP_ARM_BITMAP_CURSOR	Pt_RESOURCE( 30, 8 )
#define	Pt_ARG_SEP_ARM_CURSOR_COLOR		Pt_RESOURCE( 30, 9 )
#define	Pt_CB_SEP_DRAG					Pt_RESOURCE( 30, 10 )

/* Separator flags bits */
#define Pt_SEP_ORIENTATION			0x0001
#define	Pt_SEP_DRAGGABLE			0x0010
#define	Pt_SEP_DRAW_DRAG_BAND		0x0020

#define	Pt_SEP_READONLY_FLAGS		0xFF00

/* Sep orientation flag bit meaning */
#define Pt_SEP_HORIZONTAL				1 /* default */
#define Pt_SEP_VERTICAL					0 

/* Separator types */
#define Pt_SINGLE_LINE					0
#define Pt_DOUBLE_LINE					1
#define Pt_SINGLE_DASH_LINE				2
#define Pt_DOUBLE_DASH_LINE				3
#define Pt_ETCHED_IN					4
#define Pt_ETCHED_OUT					5
#define	Pt_NOLINE						6
#define	Pt_DRAG_HANDLE					7

typedef struct pt_separator_callback {
	PhRect_t	rect;	/* rubber band rectangle */
} PtSeparatorCallback_t;

/*
 * PtSeparator private
 */

/* Widget structure */
typedef struct Pt_separator_widget {
	PtBasicWidget_t				basic;
	ushort_t					flags;
	ushort_t					type;
	PhImage_t					*image;
	char						image_h_align,
								image_v_align;
	PhRect_t					drag_bounds;
	unsigned short				arm_cursor_type;
	unsigned short				drag_input_group;	
	PgColor_t					arm_cursor_color;	
	PhBitmapCursorDescription_t	*arm_bitmap_cursor;
	unsigned					threshold;
} PtSeparatorWidget_t;

/* Widget union */
typedef union Pt_separator_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtSeparatorWidget_t			separator;
} PtSeparatorUnion_t;
#define Pt_SEP_HORIZONTAL_F		1


#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtSeparator.h $ $Rev: 219996 $" )
#endif
