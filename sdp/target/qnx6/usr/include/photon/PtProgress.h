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
 *	PtProgress.h
 *		Header file for the PtProgress (formerly RtProgress) widget class
 *

 */

#ifndef __PT_PROGRESS_H_INCLUDED
#define __PT_PROGRESS_H_INCLUDED

#include <photon/PtGauge.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtProgress public
 */

extern PtWidgetClassRef_t *PtProgress;

/* Resources */
#define Pt_ARG_PROGRESS_SPACING		Pt_RESOURCE( Pt_RTIME(2), 4 )
#define Pt_ARG_PROGRESS_DIVISIONS	Pt_RESOURCE( Pt_RTIME(2), 5 )
#define Pt_ARG_PROGRESS_BAR_COLOR	Pt_RESOURCE( Pt_RTIME(2), 6 )
#define Pt_ARG_PROGRESS_GAP			Pt_RESOURCE( Pt_RTIME(2), 7 )

#define Pt_PROGRESS_NO_MORE_SEGMENTS	-1

typedef struct pt_progress_Widget
{
	PtGaugeWidget_t gauge;

	ushort_t spacing;		/* space between divisions */
	ushort_t divisions;		/* number of divisions */
	ushort_t gap;			/* gap between text and bar */
	ushort_t segment_spacing;
	long segment_count;

	ushort_t image_offset;
	ushort_t padding;

	PgColor_t bar_color;	/* fill color of bar */

} PtProgressWidget_t;

extern int PtProgressFirstSegment(PtWidget_t * ,short *, short * );
extern int PtProgressNextSegment(PtWidget_t * ,short *, short * );
extern int PtProgressEntireSegment(PtWidget_t * ,short *, short * );
extern void PtProgressTextRect(PtWidget_t *, PhRect_t * );

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtProgress.h $ $Rev: 219996 $" )
#endif
