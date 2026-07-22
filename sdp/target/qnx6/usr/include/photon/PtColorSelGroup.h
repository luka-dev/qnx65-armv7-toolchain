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
 *	PtColorSelGroup.h
 *		Header file for the PtColorSelGroup widget class
 *

 */
 
#ifndef __PT_COLORSELGROUP_H_INCLUDED
#define __PT_COLORSELGROUP_H_INCLUDED

#include <photon/PtColorSel.h>
#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

extern PtWidgetClassRef_t *PtColorSelGroup;

/* Resources */

#define Pt_ARG_CSGROUP_FLAGS		Pt_RESOURCE( 156, 0 )

#define Pt_CSGROUP_ALL_AT_ONCE		0x1

#define Pt_CSGROUP_HAS_CHILDREN		0x8000	/* read-only */
#define Pt_CSGROUP_RO_FLAGS			0xf000

/* Widget structure */

typedef struct pt_colorselgroup_widget
{
	PtColorSelWidget_t colorsel;

	uint16_t flags;
	uint16_t padding;

	PtWidget_t *cpanel;
	PtWidget_t *group;
		
} PtColorSelGroupWidget_t;


/* Widget union */

typedef union pt_colorselgroup_union
{
	PtWidget_t						core;
	PtBasicWidget_t					basic;
	PtContainerWidget_t				container;
	PtCompoundWidget_t				compound;
	PtColorSelWidget_t				colorsel;
	PtColorSelGroupWidget_t			colorselgroup;

} PtColorSelGroupUnion_t;


#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtColorSelGroup.h $ $Rev: 219996 $" )
#endif
