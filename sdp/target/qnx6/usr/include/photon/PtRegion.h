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
 *	PtRegion.h
 **		Header file for the PtRegion widget class
 *

 */
#ifndef __PT_REGION_H_INCLUDED
#define __PT_REGION_H_INCLUDED

#ifndef __PT_CONTAINER_H_INCLUDED
 #include <photon/PtContainer.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtRegion public
 */

extern PtWidgetClassRef_t *PtRegion;

/* Resources */

/* These resources are deprecated */

#define Pt_ARG_REGION_CURSOR			Pt_RESOURCE( 1, 2 )		/* Pt_ARG_CURSOR_TYPE */
#define Pt_ARG_REGION_CURSOR_COLOR		Pt_RESOURCE( 1, 3 )		/* Pt_ARG_CURSOR_COLOR */

/* These resources are still applicable */

#define Pt_ARG_REGION_FIELDS			Pt_RESOURCE( 15, 2 )	/* Now used only knock off bits */
#define Pt_ARG_REGION_FLAGS				Pt_RESOURCE( 15, 3 )
#define Pt_ARG_REGION_HANDLE			Pt_RESOURCE( 15, 4 )
#define Pt_ARG_REGION_OPAQUE			Pt_RESOURCE( 15, 5 )
#define Pt_ARG_REGION_OWNER				Pt_RESOURCE( 15, 6 )
#define Pt_ARG_REGION_PARENT			Pt_RESOURCE( 15, 7 )
#define Pt_ARG_REGION_SENSE				Pt_RESOURCE( 15, 8 )
#define Pt_ARG_REGION_DATA				Pt_RESOURCE( 15, 9 )
#define Pt_ARG_REGION_INFRONT			Pt_RESOURCE( 15, 10 )
#define Pt_ARG_REGION_INPUT_GROUP		Pt_RESOURCE( 15, 11 )
#define Pt_ARG_REGION_RECTANGLES		Pt_RESOURCE( 15, 12 )

/*
 * PtRegion private
 */

/* Widget structure */
typedef struct Pt_region_widget {
	PtContainerWidget_t			container;
	PhRid_t						parent;
	PhConnectId_t				owner;
	#if !defined(__QNXNTO__)
		short					reserved1;
	#endif
	ulong_t						handle;
	ulong_t						fields;
	ulong_t						flags;
	ulong_t						sense;
	ulong_t						opaque;
	PhRect_t					*rects;
	PhRid_t						infront;
	ushort_t					inputgrp;
	ushort_t					nrects;
} PtRegionWidget_t;

/* Widget union */
typedef union Pt_region_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtContainerWidget_t			container;
	PtRegionWidget_t			region;
} PtRegionUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtRegion.h $ $Rev: 219996 $" )
#endif
