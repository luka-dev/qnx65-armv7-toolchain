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
 *	PtPolygon.h
 *		Header file for the PtPolygon widget class
 *

 */
#ifndef __PT_POLYGON_H_INCLUDED
#define __PT_POLYGON_H_INCLUDED

#ifndef __PT_GRAPHIC_H_INCLUDED
 #include <photon/PtGraphic.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtPolygon public
 */

extern PtWidgetClassRef_t *PtPolygon;

/* Resources */
#define Pt_ARG_POLYGON_FLAGS			Pt_RESOURCE( 27, 1 )


/*
 * PtPolygon private
 */

/* Widget structure */
typedef struct Pt_polygon_widget {
	PtGraphicWidget_t			graphic;
	ushort_t					flags;
	short						reserved;
} PtPolygonWidget_t;

/* Widget union */
typedef union Pt_polygon_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtGraphicWidget_t			graphic;
	PtPolygonWidget_t			polygon;
} PtPolygonUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtPolygon.h $ $Rev: 219996 $" )
#endif
