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
 *	PtColorWell.h
 *		Header file for the PtColorWell widget class
 *

 */
 
#ifndef __PT_COLORWELL_H_INCLUDED
#define __PT_COLORWELL_H_INCLUDED

#include <photon/PtColorSel.h>
#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

extern PtWidgetClassRef_t *PtColorWell;

/* Resources */

#define Pt_ARG_CWELL_FLAGS			Pt_RESOURCE( 154, 0 )
#define Pt_ARG_CWELL_SWATCH_DIM		Pt_RESOURCE( 154, 1 )

/* flags */

#define Pt_CWELL_POPUP_ON_SELECT	0x1
#define Pt_CWELL_POPUP_ON_MENU		0x2

/* Widget structure */

typedef struct pt_colorwell_widget
{
	PtColorSelWidget_t colorsel;
	PhDim_t swatch_dim;
	ushort_t flags;
	ushort_t padding;
	
} PtColorWellWidget_t;


/* Widget union */

typedef union pt_colorwell_union
{
	PtWidget_t						core;
	PtBasicWidget_t					basic;
	PtContainerWidget_t				container;
	PtCompoundWidget_t				compound;
	PtColorSelWidget_t				colorsel;
	PtColorWellWidget_t				colorwell;

} PtColorWellUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtColorWell.h $ $Rev: 219996 $" )
#endif
