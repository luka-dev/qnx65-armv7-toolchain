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
 *	PtToggleButton.h
 *		Header file for the PtToggleButton widget class
 *

 */
#ifndef __PT_TOGGLE_BUTTON_H_INCLUDED
#define __PT_TOGGLE_BUTTON_H_INCLUDED

#ifndef __PT_BUTTON_H_INCLUDED
#include <photon/PtButton.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtToggleButton public
 */

extern PtWidgetClassRef_t *PtToggleButton;

#define Pt_TOGGLEBUTTON_ID	9

/* Resources */
#define Pt_ARG_INDICATOR_COLOR		Pt_RESOURCE( 9, 0 )
#define Pt_ARG_TBUTTON_FLAGS		Pt_RESOURCE( 9, 1 )
#define Pt_ARG_INDICATOR_TYPE		Pt_RESOURCE( 9, 2 )
#define	Pt_ARG_TEXT_OFFSET			Pt_RESOURCE( 9, 3 )	/* Read Only */

/* deprecated resources */

#define Pt_ARG_SPACING				Pt_ARG_TEXT_IMAGE_SPACING
#define Pt_ARG_SET_COLOR			Pt_ARG_ARM_COLOR
#define Pt_ARG_INDICATOR_DEPTH		Pt_RESOURCE( 9, 6 )
#define Pt_ARG_INDICATOR_WIDTH		Pt_RESOURCE( 9, 7 )
#define Pt_ARG_INDICATOR_HEIGHT		Pt_RESOURCE( 9, 8 )

/* Indicator types */

#define	Pt_TOGGLE_RADIO				2
#define	Pt_TOGGLE_CHECK				5
#define Pt_TOGGLE_OUTLINE			6

/* deprecated types */

#define	Pt_N_OF_MANY				0
#define	Pt_ONE_OF_MANY				1
#define Pt_RADIO					Pt_TOGGLE_RADIO
#define	Pt_ROUND					3
#define	Pt_TICK						4
#define Pt_CHECK					Pt_TOGGLE_CHECK

/*
 * PtToggleButton private
 */

/* Widget structure */
typedef struct Pt_toggle_button_widget
{
	PtButtonWidget_t		button;

	PgColor_t				indicator_color;

	ushort_t flags;
	uchar_t 				indicator_type;
	uchar_t					padding;

} PtToggleButtonWidget_t;

/* Widget union */
typedef union Pt_toggle_button_union
{
	PtWidget_t				core;
	PtBasicWidget_t			basic;
	PtLabelWidget_t			label;
	PtButtonWidget_t		button;
	PtToggleButtonWidget_t	toggle;
} PtToggleButtonUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtToggleButton.h $ $Rev: 219996 $" )
#endif
