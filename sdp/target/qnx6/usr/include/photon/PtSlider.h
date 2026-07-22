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
 *	PtSlider.h
 *		Header file for the PtSlider widget class
 *

 */

#ifndef __PT_SLIDER_H_INCLUDED
#define __PT_SLIDER_H_INCLUDED

#ifndef __PT_BASIC_H_INCLUDED
 #include <photon/PtBasic.h>
#endif

#ifndef __PT_GAUGE_H_INCLUDED
 #include <photon/PtGauge.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtSlider public
 */

extern PtWidgetClassRef_t *PtSlider;

/* Resources */
#define Pt_ARG_SLIDER_FLAGS				Pt_RESOURCE( 22, 0 )
#define Pt_ARG_SLIDER_INCREMENT			Pt_RESOURCE( 22, 1 )
#define Pt_ARG_SLIDER_MULTIPLE			Pt_RESOURCE( 22, 6 )
#define Pt_ARG_SLIDER_THICKNESS			Pt_RESOURCE( 22, 7 )
#define Pt_ARG_SLIDER_HANDLE_WIDTH		Pt_ARG_SLIDER_THICKNESS
#define Pt_ARG_SLIDER_IMAGE				Pt_RESOURCE( 22, 9 )
#define	Pt_ARG_SLIDER_TROUGH_IMAGE1		Pt_RESOURCE( 22, 10 )
#define	Pt_ARG_SLIDER_TROUGH_IMAGE2		Pt_RESOURCE( 22, 11 )
#define Pt_ARG_SLIDER_TICK_MINOR_DIV	Pt_RESOURCE( 22, 12 )	/* not used */
#define Pt_ARG_SLIDER_TICK_MAJOR_DIV	Pt_RESOURCE( 22, 13 )
#define Pt_ARG_SLIDER_TICK_MAJOR_LEN	Pt_RESOURCE( 22, 14 )	/* not used */
#define Pt_ARG_SLIDER_TICK_MINOR_LEN	Pt_RESOURCE( 22, 15 )	/* not used */
#define Pt_CB_SLIDER_MOVE				Pt_RESOURCE( 22, 17 )
#define Pt_ARG_SLIDER_HANDLE_COLOR		Pt_RESOURCE( 22, 20 )

/* Possible flags */
#define Pt_SLIDER_IMAGE					0x80
#define	Pt_SLIDER_TROUGH_IMAGE			0x40
#define Pt_SLIDER_DAMAGE_SLIDER		0x4000
#define Pt_SLIDER_DAMAGE_INCDEC		0x8000
#define Pt_SLIDER_RO_FLAGS			0xf000

#define Pt_SLIDER_NO_MORE_TICKS		-1

/* manifests for widget actions */

enum
{
	Pt_SLIDER_INCREMENT_ACTION = 0,
	Pt_SLIDER_DECREMENT_ACTION,
	Pt_SLIDER_DRAG_ACTION,
	Pt_SLIDER_POSITION_ACTION
};

typedef struct Pt_slider_widget
{
	PtGaugeWidget_t     gauge;

	ushort_t			flags;
	ushort_t			padding;

	ushort_t			increment;
	ushort_t			multiple;

	ulong_t				tick_major_div;
	ulong_t				tick_minor_div;
	PgColor_t			tick_major_col;
	PgColor_t			tick_minor_col;
	PgColor_t			handle_color;
/*	PtCallbackList_t	*cb_move; */

	ushort_t			tick_major_len;
	ushort_t			tick_minor_len;

	ushort_t            slider_thickness;
	ushort_t			rrng;

	long				major_count,minor_count;

	PhDim_t				show_val_dim;
	PhImage_t			*image;
	PhImage_t			*trough_image1;
	PhImage_t			*trough_image2;
} PtSliderWidget_t;

/* Callback structure */
typedef struct Pt_slider_callback {
	int			position;
} PtSliderCallback_t;

/* callback reason subtypes */

#define Pt_SLIDER_INCREMENT					1
#define Pt_SLIDER_DECREMENT					2
#define Pt_SLIDER_MULTIPLE_INCREMENT		3
#define Pt_SLIDER_MULTIPLE_DECREMENT		4
#define Pt_SLIDER_DRAGGED					5
#define Pt_SLIDER_RELEASED					6
#define Pt_SLIDER_TO_MIN					7
#define Pt_SLIDER_TO_MAX					8
#define Pt_SLIDER_JUMP						9
#define Pt_SLIDER_SET						10

/* macros */

#define PtSliderUseImage(w)		((((PtSliderWidget_t*)(w))->flags & Pt_SLIDER_IMAGE) && ((PtSliderWidget_t*)(w))->image)

extern short PtSliderFirstMajorTick( PtWidget_t * );
extern short PtSliderNextMajorTick( PtWidget_t * );
extern short PtSliderFirstMinorTick( PtWidget_t * );
extern short PtSliderNextMinorTick( PtWidget_t * );
extern ushort_t PtSliderThickness( PtWidget_t * );

extern void PtSliderUnclipSlider( void );
extern int PtSliderClipSlider( PtWidget_t * );

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtSlider.h $ $Rev: 219996 $" )
#endif
