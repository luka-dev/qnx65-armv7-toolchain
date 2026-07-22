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
 *	PtBitmap.h
 *		Header file for the PtBitmap widget class
 *

 */
#ifndef __PT_BITMAP_H_INCLUDED
#define __PT_BITMAP_H_INCLUDED

#ifndef __PT_BASIC_H_INCLUDED
 #include <photon/PtBasic.h>
#endif

#ifndef __PT_CONTAINER_H_INCLUDED
 #include <photon/PtContainer.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtBitmap public
 */

extern PtWidgetClassRef_t *PtBitmap;

#define Pt_BITMAP_ID	20

/* Resources */
#define Pt_ARG_BITMAP_COLORS			Pt_RESOURCE( 20, 0 )
#define Pt_ARG_BITMAP_DATA				Pt_RESOURCE( 20, 1 )
#define Pt_ARG_BITMAP_TEXT				Pt_RESOURCE( 20, 2 )
#define Pt_ARG_BMP_SET_BG_COLOR			Pt_RESOURCE( 20, 3 )
#define Pt_ARG_BMP_SET_BG_FILL			Pt_RESOURCE( 20, 4 )
#define Pt_ARG_SET_BITMAP_COLORS		Pt_RESOURCE( 20, 5 )
#define Pt_ARG_SET_BITMAP_DATA			Pt_RESOURCE( 20, 6 )

#define Pt_ARG_BITMAP_FLAGS				Pt_RESOURCE( 20, 7 )
#define Pt_ARG_BITMAP_BALLOON_POSITION	Pt_RESOURCE( 20, 8 )
#define Pt_ARG_BITMAP_BALLOON			Pt_RESOURCE( 20, 9 )
#define Pt_ARG_BITMAP_BALLOON_FILL_COLOR	Pt_RESOURCE( 20, 10 )
#define Pt_ARG_BITMAP_BALLOON_COLOR			Pt_RESOURCE( 20, 11 )

#define Pt_BITMAP_SHOW_BALLOON			0x04

/* Balloon Positions */
#define Pt_BITMAP_BALLOON_RIGHT		0
#define Pt_BITMAP_BALLOON_LEFT 		1
#define Pt_BITMAP_BALLOON_TOP		2
#define Pt_BITMAP_BALLOON_BOTTOM	3
#define Pt_BITMAP_BALLOON_INPLACE	4

/*
 * PtBitmap private
 */

/* Widget structure */
typedef struct Pt_bitmap_widget {
	PtBasicWidget_t				basic;
	ushort_t					nplanes;
	ushort_t					balloon_pos;
	PgColor_t					*colors;	
	char						**data;
	unsigned short				splanes;
	PgColor_t					*set_colors;	
	char						**set_data;
	PgColor_t					set_bg_color;
	char *						text;
/*	PtCallbackList_t			*activate; */
	PtWidget_t					*balloon_widget;
	const char					*font;
	uchar_t						set_bg_fill;
	char						flags;
	PgColor_t					balloon_fill_color;
	PgColor_t					balloon_color;
	PtWidget_t					*(*inflate_f)();
} PtBitmapWidget_t;

/* Widget union */
typedef struct Pt_bitmap_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtBitmapWidget_t			bitmap;
} PtBitmapUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtBitmap.h $ $Rev: 219996 $" )
#endif
