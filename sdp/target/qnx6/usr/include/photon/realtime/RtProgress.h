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
 *	RtProgress.h
 *		Header file for the RtProgress (now PtProgress) widget class
 *

 */

#ifndef __RT_PROGRESS_H_INCLUDED
#define __RT_PROGRESS_H_INCLUDED

#ifndef __PT_PROGRESS_H_INCLUDED
#include <photon/PtProgress.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

extern PtWidgetClassRef_t *RtProgress;

typedef PtProgressWidget_t	RtProgressWidget_t;

/* Resources */

#define Rt_ARG_PROGRESS_SPACING		Pt_ARG_PROGRESS_SPACING
#define Rt_ARG_PROGRESS_DIVISIONS	Pt_ARG_PROGRESS_DIVISIONS
#define Rt_ARG_PROGRESS_BAR_COLOR	Pt_ARG_PROGRESS_BAR_COLOR
#define Rt_ARG_PROGRESS_GAP			Pt_ARG_PROGRESS_GAP


#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/realtime/RtProgress.h $ $Rev: 219996 $" )
