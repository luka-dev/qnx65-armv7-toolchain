/* Copyright 2009, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to 
 * QNX Software Systems before you may reproduce, modify or distribute this 
 * software, or any work that includes all or part of this software.  Free 
 * development licenses are available for evaluation and non-commercial purposes.  
 * For more information visit http://licensing.qnx.com or email licensing@qnx.com.
 * 
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 */
/* PtUpDown.h - widget header file */

#ifndef __PT_UPDOWN_H_INCLUDED
#define __PT_UPDOWN_H_INCLUDED

#ifndef __PT_BASIC_H_INCLUDED
 #include <photon/PtBasic.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/* widget resources */

#define Pt_ARG_UPDOWN_ORIENTATION 			Pt_RESOURCE( 52, 1 )
#define Pt_ARG_UPDOWN_DATA_INCREMENT		Pt_RESOURCE( 52, 3 )
#define Pt_ARG_UPDOWN_DATA_DECREMENT		Pt_RESOURCE( 52, 4 )

#define Pt_ARG_UPDOWN_ARM_DATA_INCREMENT	Pt_RESOURCE( 52, 7 )
#define Pt_ARG_UPDOWN_ARM_DATA_DECREMENT	Pt_RESOURCE( 52, 8 )
#define Pt_ARG_UPDOWN_BORDER_WIDTH	 		Pt_RESOURCE( 52, 11 )

#define Pt_ARG_UPDOWN_FLAGS					Pt_RESOURCE( 52, 15 )
#define Pt_ARG_UPDOWN_INDICATOR_MARGIN 		Pt_RESOURCE( 52, 19 )

/* DEPRECATED resources as of photon 2 */

#define Pt_ARG_UPDOWN_SPACING				Pt_ARG_SPACING
#define Pt_ARG_UPDOWN_FILL_COLOR			Pt_ARG_FILL_COLOR
#define Pt_ARG_UPDOWN_DATA_TOP 				Pt_ARG_UPDOWN_DATA_INCREMENT
#define Pt_ARG_UPDOWN_DATA_BOTTOM			Pt_ARG_UPDOWN_DATA_DECREMENT
#define Pt_ARG_UPDOWN_DATA_BOT				Pt_ARG_UPDOWN_DATA_DECREMENT
#define Pt_ARG_UPDOWN_DATA_LEF 				Pt_ARG_UPDOWN_DATA_DECREMENT
#define Pt_ARG_UPDOWN_DATA_LEFT				Pt_ARG_UPDOWN_DATA_DECREMENT
#define Pt_ARG_UPDOWN_DATA_RIT 				Pt_ARG_UPDOWN_DATA_INCREMENT
#define Pt_ARG_UPDOWN_DATA_RIGHT			Pt_ARG_UPDOWN_DATA_INCREMENT
#define Pt_ARG_UPDOWN_ARM_DATA_TOP 			Pt_ARG_UPDOWN_ARM_DATA_INCREMENT
#define Pt_ARG_UPDOWN_ARM_DATA_BOTTOM 		Pt_ARG_UPDOWN_ARM_DATA_DECREMENT
#define Pt_ARG_UPDOWN_ARM_DATA_BOT	 		Pt_ARG_UPDOWN_ARM_DATA_DECREMENT
#define Pt_ARG_UPDOWN_ARM_DATA_LEF 			Pt_ARG_UPDOWN_ARM_DATA_DECREMENT
#define Pt_ARG_UPDOWN_ARM_DATA_LEFT			Pt_ARG_UPDOWN_ARM_DATA_DECREMENT
#define Pt_ARG_UPDOWN_ARM_DATA_RIT			Pt_ARG_UPDOWN_ARM_DATA_INCREMENT
#define Pt_ARG_UPDOWN_ARM_DATA_RIGHT		Pt_ARG_UPDOWN_ARM_DATA_INCREMENT
#define Pt_ARG_UPDOWN_BOT_BDR_COLOR			Pt_ARG_BOT_BORDER_COLOR
#define Pt_ARG_UPDOWN_BOTTOM_BORDER_COLOR	Pt_ARG_BOT_BORDER_COLOR
#define Pt_ARG_UPDOWN_TOP_BDR_COLOR			Pt_ARG_TOP_BORDER_COLOR
#define Pt_ARG_UPDOWN_TOP_BORDER_COLOR		Pt_ARG_TOP_BORDER_COLOR
#define Pt_ARG_UPDOWN_HIGHLGHT_ROUND		Pt_ARG_HIGHLIGHT_ROUNDNESS
#define Pt_ARG_UPDOWN_HIGHLIGHT_ROUND		Pt_ARG_HIGHLIGHT_ROUNDNESS
#define Pt_ARG_UPDOWN_FILL_COLOR			Pt_ARG_FILL_COLOR
#define Pt_ARG_UPDOWN_MARGIN_HEIGHT			Pt_ARG_MARGIN_HEIGHT
#define Pt_ARG_UPDOWN_MARGIN_WIDTH 			Pt_ARG_MARGIN_WIDTH


/* widget callback reason_subtypes */

#define Pt_UPDOWN_UP		1
#define Pt_UPDOWN_DOWN		2	
#define Pt_UPDOWN_LEFT		3
#define Pt_UPDOWN_RIGHT		4


/* renamed widget callback reason_subtypes */

#define UPDOWN_TOP			Pt_UPDOWN_UP
#define UPDOWN_BOT			Pt_UPDOWN_DOWN
#define UPDOWN_BOTTOM		Pt_UPDOWN_DOWN
#define UPDOWN_LEF			Pt_UPDOWN_LEFT
#define UPDOWN_LEFT			Pt_UPDOWN_LEFT
#define UPDOWN_RIT			Pt_UPDOWN_RIGHT
#define UPDOWN_RIGHT		Pt_UPDOWN_RIGHT


/* Pt_ARG_UPDOWN_FLAGS manifests */

#define Pt_UPDOWN_INCREMENT_IMAGE		0x1
#define Pt_UPDOWN_DECREMENT_IMAGE		0x2
#define Pt_UPDOWN_INCREMENT_ARM_IMAGE	0x4
#define Pt_UPDOWN_DECREMENT_ARM_IMAGE	0x8
#define Pt_UPDOWN_ROTATE_INDICATORS		0x10
#define Pt_UPDOWN_FILL_ON_ARM			0x20
#define Pt_UPDOWN_HORIZONTAL			0x40
#define Pt_UPDOWN_DAMAGE_INCDEC			0x8000
#define Pt_UPDOWN_RO_FLAGS				(Pt_UPDOWN_HORIZONTAL | Pt_UPDOWN_DAMAGE_INCDEC)


/* manifests for PtUpDown control surfaces */

enum
{
	Pt_UPDOWN_INCREMENT_ACTION = 0,
	Pt_UPDOWN_DECREMENT_ACTION
};


/* widget instance structure */
typedef struct pt_updown_widget
{
	PtBasicWidget_t	basic;

	PgColor_t arm_color;
	ushort_t flags;

	ushort_t spacing;

	ushort_t margin;
	ushort_t border_width;

	PhImage_t *inc_image,*dec_image;
	PhImage_t *inc_arm_image,*dec_arm_image;

} PtUpDownWidget_t;

typedef union pt_updown_union
{
	PtWidget_t core;
	PtBasicWidget_t basic;
	PtUpDownWidget_t updown;

} PtUpDownUnion_t;

extern PtWidgetClassRef_t *PtUpDown;

/* macros */

#define PtUpDownIsHorizontal(w)	(((PtUpDownWidget_t*)(w))->flags & Pt_UPDOWN_HORIZONTAL)
#define PtUpDownIsVertical(w)	(!PtUpDownIsHorizontal(w))

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtUpDown.h $ $Rev: 224590 $" )
#endif
