/* Copyright 2009, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to 
 * QNX Software Systems before you may reproduce, modify or distribute this 
 * software, or any work that includes all or part of this software.  Free 
 * development licenses are available for evaluation and non-commercial purposes.  
 * For more information visit http://licensing.qnx.com or email licensing@qnx.com.
 * 
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 */
#ifndef __RTTIMER_H_INCLUDED
#define __RTTIMER_H_INCLUDED

#include <signal.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Rt_timer RtTimer_t;

typedef int RtTimerCbF_t( RtTimer_t *timer, void *data );

RtTimer_t *RtTimerCreate( clockid_t clock_id, int prio, RtTimerCbF_t *cb, void *data );
void RtTimerDelete( RtTimer_t *timer );
int RtTimerGetTime( RtTimer_t *timer, struct itimerspec *value );
int RtTimerSetTime( RtTimer_t *timer, int flags,
	struct itimerspec *value, struct itimerspec *ovalue );

#ifdef __cplusplus
}
#endif

#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/realtime/RtTimer.h $ $Rev: 224590 $" )
