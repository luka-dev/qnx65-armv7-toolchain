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
 *	PtColorSelStandard.h
 *		Header file for the PtColorSelStandard widget class
 *

 */
 
#ifndef __PT_COLORSLIDER_H_INCLUDED
#define __PT_COLORSLIDER_H_INCLUDED

#include <photon/PtColorSel.h>
#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


extern PtWidgetClassRef_t *PtColorSlider;


/* Widget structure */

typedef struct pt_colorslider_widget
{
	PtColorSelWidget_t colorsel;

	ushort_t axis_length;	
	ushort_t padding;
		
	uchar_t *image;				/* precomputed color image */
	
	PtWidget_t **sliders;		/* Sliders */
	PtWidget_t **labels;		/* labels for sliders */
	long *crc;					/* crc tags for bands */
} PtColorSliderWidget_t;


/* Widget union */

typedef union pt_colorsel_standard_union
{
	PtWidget_t						core;
	PtBasicWidget_t					basic;
	PtContainerWidget_t				container;
	PtCompoundWidget_t				compound;
	PtColorSelWidget_t				colorsel;
	PtColorSelStandardWidget_t		colorsel_standard;

} PtColorSelStandardUnion_t;


#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtColorSlider.h $ $Rev: 219996 $" )
