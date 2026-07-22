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
/* PtNumeric.h - widget header file */

#ifndef __PT_NUMERIC_H_INCLUDED
#define __PT_NUMERIC_H_INCLUDED

#include <photon/PtT.h>
#include <photon/PhT.h>
#include <photon/PtGauge.h>
#include <photon/PtCompound.h>
#include <photon/PtText.h>
#include <photon/PtUpDown.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/* widget resources */
#define Pt_ARG_NUMERIC_FLAGS					Pt_RESOURCE( 53, 1 )
#define Pt_ARG_NUMERIC_UPDOWN_WIDTH				Pt_RESOURCE( 53, 2 )
#define Pt_ARG_NUMERIC_INCREMENT 				Pt_RESOURCE( 53, 3 )
#define Pt_ARG_NUMERIC_VALUE					Pt_RESOURCE( 53, 4 )
#define Pt_ARG_NUMERIC_MIN						Pt_RESOURCE( 53, 5 )
#define Pt_ARG_NUMERIC_MAX						Pt_RESOURCE( 53, 6 )
#define Pt_ARG_NUMERIC_PREFIX					Pt_RESOURCE( 53, 7 )
#define Pt_ARG_NUMERIC_SUFFIX					Pt_RESOURCE( 53, 8 )
#define Pt_ARG_NUMERIC_TEXT_COLOR				Pt_RESOURCE( 53, 11 )	/* deprecated */
#define Pt_ARG_NUMERIC_PRECISION				Pt_RESOURCE( 53, 16 )
#define Pt_ARG_NUMERIC_SPACING					Pt_RESOURCE( 53, 17 )
#define Pt_CB_NUMERIC_CHANGED					Pt_RESOURCE( 53, 15 )

/* PtNumeric Flags */
#define Pt_NUMERIC_ENABLE_UPDOWN		0x01   
#define Pt_NUMERIC_USE_SEPARATORS 		0x02
#define Pt_NUMERIC_WRAP					0x04
#define Pt_NUMERIC_AUTO_HIGHLIGHT		0x08
#define Pt_NUMERIC_HEXADECIMAL			0x10
#define Pt_NUMERIC_VALUE_CHANGED		0x8000	/* read-only */
#define Pt_NUMERIC_RO_FLAGS				0x8000

#define NUMERIC_BUF				40

/* widget instance structure */
typedef struct numeric_widget{
	PtCompoundWidget_t	compound;
	ushort_t		updown_width;
	ushort_t		numeric_flags;
	ushort_t		spacing;
	ushort_t 		orientation;
	char			*prefix, *suffix;
	PtWidget_t		*text_wgt;
	PtWidget_t		*updown_wgt;
	int sep_flag;
	int text_flags;
	ushort_t 		right_margin;
}	PtNumericWidget_t;

/* callback subtypes */
#define Pt_NUMERIC_CHANGED 			0x1
#define Pt_NUMERIC_ACTIVATE			0x2
#define Pt_NUMERIC_UPDOWN_REPEAT 	0x4
#define Pt_NUMERIC_UPDOWN_ACTIVATE 	0x8
#define Pt_NUMERIC_SET			 	0x10

extern PtWidgetClassRef_t *PtNumeric;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtNumeric.h $ $Rev: 224590 $" )
#endif
