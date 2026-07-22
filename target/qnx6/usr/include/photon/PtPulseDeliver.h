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

#ifndef __PT_PULSE_DELIVER_H_INCLUDED
#define __PT_PULSE_DELIVER_H_INCLUDED

#if defined(__QNXNTO__)
	#include <sys/neutrino.h>
#else
	#include <sys/types.h>
	#include <sys/kernel.h>
#endif

#if defined(__QNXNTO__)
	#ifndef __PT_T_H_INCLUDED
   	 	typedef struct sigevent PtPulseMsg_t;
	#endif
	#define PtPulseDeliver( rcvid, pulse ) MsgDeliverEvent( rcvid, pulse )
#else
	#ifndef __PT_T_H_INCLUDED
	typedef pid_t PtPulseMsg_t;
	#endif
	#define PtPulseDeliver( rcvid, pulse ) ( (void)(rcvid), Trigger( *(pulse) ) )
#endif

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtPulseDeliver.h $ $Rev: 224590 $" )
#endif
