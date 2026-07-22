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
 *	PtTimer.h
 *		Header file for the PtTimer widget class
 *

 */
#ifndef __PT_TIMER_H_INCLUDED
#define __PT_TIMER_H_INCLUDED

#ifndef __PT_WIDGET_H_INCLUDED
#include <photon/PtWidget.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtTimer public
 */

extern PtWidgetClassRef_t *PtTimer;

#define Pt_ARG_TIMER_INITIAL		Pt_RESOURCE( 41, 0 )
#define Pt_ARG_TIMER_REPEAT			Pt_RESOURCE( 41, 1 )
#define Pt_CB_TIMER_ACTIVATE		Pt_RESOURCE( 41, 2 )

/*
 * PtTimer public
 */

#define Pt_TIMER_INITIAL	1
#define Pt_TIMER_REPEAT		2

/* Widget structure */
typedef struct Pt_timer_widget {
	PtWidget_t				core;
	unsigned long			msec_value;
	unsigned long			msec_repeat;
	long					state;
/*	PtCallbackList_t        *activate; */
} PtTimerWidget_t;

/* Widget union */
typedef union Pt_timer_union {
	PtWidget_t				core;
	PtTimerWidget_t			timer;
} PtTimerUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtTimer.h $ $Rev: 219996 $" )
#endif
