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





#ifndef _NW_DEFS_H_INCLUDED
#define _NW_DEFS_H_INCLUDED

#ifndef __IOMSG_H_INCLUDED
#include <sys/iomsg.h>
#endif

/* Stacks must be a byte aligned */
#define NW_STK_ALIGN 8

#define NW_DEF_MSG_DEAD    ((_IO_MAX << 1) + 0)
#define NW_DEF_MSG_OOBNEW  ((_IO_MAX << 1) + 1)


#define NW_DEF_INTR_STACKSIZE   8192
#define NW_DEF_STACK_CALLSPACE  (8 * NW_STK_ALIGN)

#define NW_DEF_PULSE_CODE_IRUPT_CORE	(_PULSE_CODE_MINAVAIL + 0)
#define NW_DEF_PULSE_CODE_IRUPT_OOB	(_PULSE_CODE_MINAVAIL + 1)
#define NW_DEF_PULSE_CODE_DODIE		(_PULSE_CODE_MINAVAIL + 2)
#define NW_DEF_PULSE_CODE_PROGMGR_EVENT	(_PULSE_CODE_MINAVAIL + 3)
#define NW_DEF_PULSE_CODE_DEAD_IRUPT	(_PULSE_CODE_MINAVAIL + 4)
#define NW_DEF_PULSE_CODE_POKE_PKT	(_PULSE_CODE_MINAVAIL + 5)
#define NW_DEF_PULSE_CODE_CALLBACK	(_PULSE_CODE_MINAVAIL + 6)

#define NW_DEF_CONFSTR_PRIO 21
/*
 * Assume we can process this many input packets
 * through the stack per tick.
 */
#define NW_DEF_SOFTCLOCK_PKT_LIM 100


#define NW_DEF_THREADS_MAX 100

/*
 * Thread ids always start at 1 while our thread 1 only does
 * init / shutdown currently.  Therefore our tidx offset is 2.
 */
#define NW_DEF_TID_BASE_OFF 2
#define NW_TIDX_TO_TID(tidx) ((tidx) + NW_DEF_TID_BASE_OFF)
#define NW_TID_TO_TIDX(tid)  ((tid)  - NW_DEF_TID_BASE_OFF)



/* Reserve for ip / udp headers on write */

/*
 * We need 28 bytes for proto headers (20 ip + 8 udp).
 * sizeof(io_write_t) == 16 (sendto() and sendmsg() headers >= sizeof(io_write_t))
 * therefor we need 28 - 16 = 12 filler bytes.
 */
#define NW_DEF_HDR_LEN 12

#define NW_DEF_OOB_PRIO_LOW 18
#define NW_DEF_OOB_PRIO_HIGH 22

#endif /* !_NW_DEFS_H_INCLUDED */

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/io-pkt/sys/nw_defs.h $ $Rev: 233581 $" )
