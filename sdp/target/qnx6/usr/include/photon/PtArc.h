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
 *	PtArc.h
 *		Header file for the PtArc widget class
 *

 */
#ifndef __PT_ARC_H_INCLUDED
#define __PT_ARC_H_INCLUDED

#ifndef __PT_GRAPHIC_H_INCLUDED
 #include <photon/PtGraphic.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtArc public
 */

extern PtWidgetClassRef_t *PtArc;

#define Pt_ARC_ID	26

/* Resources */
#define Pt_ARG_ARC_END					Pt_RESOURCE( 26, 0 )
#define Pt_ARG_ARC_START				Pt_RESOURCE( 26, 1 )
#define Pt_ARG_ARC_TYPE					Pt_RESOURCE( 26, 2 )


#define Pt_ARC_CURVE		Pg_ARC
#define Pt_ARC_PIE			Pg_ARC_PIE
#define Pt_ARC_CHORD		Pg_ARC_CHORD
/*
 * PtArc private
 */

/* Widget structure */
typedef struct Pt_arc_widget {
	PtGraphicWidget_t			graphic;
	ushort_t					start;
	ushort_t					end;
	ushort_t					type;
} PtArcWidget_t;

/* Widget union */
typedef union Pt_arc_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtGraphicWidget_t			graphic;
	PtArcWidget_t				arc;
} PtArcUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtArc.h $ $Rev: 219996 $" )
#endif
