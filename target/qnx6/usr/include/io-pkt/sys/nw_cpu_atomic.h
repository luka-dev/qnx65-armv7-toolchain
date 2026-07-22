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





#ifndef __NW_CPU_ATOMIC_H_INCLUDED
#define __NW_CPU_ATOMIC_H_INCLUDED

#include <atomic.h>

/* Note:  These cpu_ variants may not be interrupt safe. */


#if defined(__X86__)
#include "target/x86/nw_cpu_atomic.h"
#elif defined(__PPC__)
#include "target/ppc/nw_cpu_atomic.h"
#elif defined(__ARM__)
#include "target/arm/nw_cpu_atomic.h"
#elif defined(__SH__)
#include "target/sh/nw_cpu_atomic.h"
#elif defined(__MIPS__)
#include "target/mips/nw_cpu_atomic.h"
#else
#error nw_cpu_misc.h not defined for cpu
#endif

#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/io-pkt/sys/sys/nw_cpu_atomic.h $ $Rev: 233581 $" )
