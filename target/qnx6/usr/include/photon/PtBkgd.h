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
 *	PtBkgd.h
 *		Header file for the PtBkgd widget class
 *

 */
#ifndef __PT_BKGD_H_INCLUDED
#define __PT_BKGD_H_INCLUDED

#ifndef __PT_CONTAINER_H_INCLUDED
 #include <photon/PtContainer.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtBkgd public
 */

extern PtWidgetClassRef_t *PtBkgd;

#define Pt_BKGD_ID	14

/* Resources */
#define Pt_ARG_BKGD_TILE			Pt_RESOURCE( 14, 13 )
#define Pt_ARG_BKGD_IMAGE			Pt_RESOURCE( 14, 15 )
#define Pt_ARG_BKGD_SPACING_X		Pt_RESOURCE( 14, 17 )
#define Pt_ARG_BKGD_SPACING_Y		Pt_RESOURCE( 14, 18 )

/* pixmap tile flags */

#define Pt_BKGD_NONE				0
#define Pt_BKGD_GRID				1
#define Pt_BKGD_CENTER				2
#define Pt_BKGD_CENTER_GRID			3

/*
 * PtBkgd private
 */

/* Widget structure */
typedef struct Pt_bkgd_widget
{
	PtContainerWidget_t			container;

	uint8_t						tile;
	uint8_t						padding[3];
	
	PhPoint_t					spacing;
	PhPoint_t					rep;
	PhPoint_t					pos;

	PhImage_t					*image;

} PtBkgdWidget_t;

/* Widget union */
typedef union Pt_bkgd_union
{
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtContainerWidget_t			container;
	PtBkgdWidget_t				bkgd;

} PtBkgdUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtBkgd.h $ $Rev: 219996 $" )
#endif
