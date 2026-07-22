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
 *	PtGauge.h
 *		Header file for the PtGauge widget class
 *

 */

#ifndef __PT_GAUGE_H_INCLUDED
#define __PT_GAUGE_H_INCLUDED

#ifndef __PT_BASIC_H_INCLUDED
 #include <photon/PtBasic.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtGauge public
 */

extern PtWidgetClassRef_t *PtGauge;

#define Pt_GAUGE_ID		21

/* Resources */
#define Pt_ARG_GAUGE_FLAGS			Pt_RESOURCE( 21, 0 )
#define Pt_ARG_GAUGE_FONT			Pt_RESOURCE( 21, 1 )
#define Pt_ARG_MINIMUM				Pt_RESOURCE( 21, 2 )
#define Pt_ARG_GAUGE_MINIMUM		Pt_ARG_MINIMUM
#define Pt_ARG_MAXIMUM				Pt_RESOURCE( 21, 3 )
#define Pt_ARG_GAUGE_MAXIMUM		Pt_ARG_MAXIMUM
#define Pt_ARG_GAUGE_VALUE			Pt_RESOURCE( 21, 4 )
#define Pt_ARG_ORIENTATION			Pt_RESOURCE( 21, 5 )
#define Pt_ARG_GAUGE_ORIENTATION	Pt_ARG_ORIENTATION
#define Pt_ARG_GAUGE_VALUE_PREFIX	Pt_RESOURCE( 21, 6 )
#define Pt_ARG_GAUGE_VALUE_SUFFIX	Pt_RESOURCE( 21, 7 )
#define Pt_ARG_GAUGE_H_ALIGN		Pt_RESOURCE( 21, 8 )
#define Pt_ARG_GAUGE_V_ALIGN		Pt_RESOURCE( 21, 9 )
#define Pt_CB_GAUGE_VALUE_CHANGED	Pt_RESOURCE( 21, 10 )

/* Possible flags */
/* direction related */
#define Pt_GAUGE_MAX_ON_TOP			0x1
#define Pt_GAUGE_MAX_ON_LEFT		0x2
#define Pt_GAUGE_SHOW_VALUE			0x10
#define Pt_GAUGE_VALUE_XOR			0x20
#define Pt_GAUGE_LIVE				0x40
#define Pt_GAUGE_INDETERMINATE		0x80
#define Pt_GAUGE_INTERACTIVE		0x100

#define Pt_GAUGE_HORIZONTAL			0x8000	/* read-only */
#define Pt_GAUGE_RO_FLAGS			0xf000

typedef struct pt_gauge_callback
{
	long value;
	
} PtGaugeCallback_t;

/* reason_subtypes describing in detail the nature of the change */

#define Pt_GAUGE_DECREMENT				1
#define Pt_GAUGE_INCREMENT				2
#define Pt_GAUGE_MULTIPLE_INCREMENT		3
#define Pt_GAUGE_MULTIPLE_DECREMENT		4
#define Pt_GAUGE_TO_MAX					5
#define Pt_GAUGE_TO_MIN					6
#define Pt_GAUGE_DRAGGED				7
#define Pt_GAUGE_RELEASED				8
#define Pt_GAUGE_JUMP					9

typedef struct Pt_gauge_widget
{
	PtBasicWidget_t     basic;
	long                value;
	long                maximum;
	long                minimum;

	const char			*font;
	char				*suffix;
	char				*prefix;

	ushort_t			twidth;
	ushort_t			theight;

	ushort_t			flags;
	uchar_t				h_alignment;
	uchar_t				v_alignment;

/*	PtCallbackList_t	*value_changed; */

} PtGaugeWidget_t;

/* macros */

#define PtGaugeIsHorizontal(__w)	(((PtGaugeWidget_t *)(__w))->flags & Pt_GAUGE_HORIZONTAL)
#define PtGaugeIsVertical(__w)		(!PtGaugeIsHorizontal(__w))
#define PtGaugeMinimum(__w)			(((PtGaugeWidget_t *)(__w))->minimum)
#define PtGaugeMaximum(__w)			(((PtGaugeWidget_t *)(__w))->maximum)
#define PtGaugeValue(__w)			(((PtGaugeWidget_t *)(__w))->value)
#define PtGaugeFixValue(__w,__v)	( min(max(__v,((PtGaugeWidget_t*)(__w))->minimum),((PtGaugeWidget_t*)(__w))->maximum) )
#define PtGaugeIsShowingValue(__w)	(((PtGaugeWidget_t *)(__w))->flags & Pt_GAUGE_SHOW_VALUE)
#define PtGaugeValuePrefix(__w)		(((PtGaugeWidget_t *)(__w))->prefix ? ((PtGaugeWidget_t*)(__w))->prefix : "")
#define PtGaugeValueSuffix(__w)		(((PtGaugeWidget_t *)(__w))->suffix ? ((PtGaugeWidget_t*)(__w))->suffix : "")
#define PtGaugeMaxIsLeft(__w)		(((PtGaugeWidget_t *)(__w))->flags & Pt_GAUGE_MAX_ON_LEFT)
#define PtGaugeMaxIsTop(__w)		(((PtGaugeWidget_t *)(__w))->flags & Pt_GAUGE_MAX_ON_TOP)
#define PtGaugeMaxIsBottom(__w)		(!PtGaugeMaxIsTop(__w))
#define PtGaugeMaxIsRight(__w)		(!PtGaugeMaxIsLeft(__w))
#define PtGaugeIsInverted(__w)		((PtGaugeIsHorizontal(__w) && PtGaugeMaxIsLeft(__w)) || (PtGaugeIsVertical(__w) && PtGaugeMaxIsTop(__w)))
#define PtGaugeRange(__w)			( PtGaugeMaximum(__w) - PtGaugeMinimum(__w) + 1 )

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtGauge.h $ $Rev: 219996 $" )
#endif
