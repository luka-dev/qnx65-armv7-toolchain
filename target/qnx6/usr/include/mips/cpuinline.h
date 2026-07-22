/*
 * $QNXLicenseC:
 * Copyright 2007, 2009, QNX Software Systems. All Rights Reserved.
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

#ifndef _MIPS_CPUINLINE_INCLUDED
#define _MIPS_CPUINLINE_INCLUDED

#if defined(__GNUC__) || defined(__INTEL_COMPILER)

# define __cpu_membarrier() __extension__ ({ __asm__ __volatile__ ("sync" : : : "memory"); })

#elif defined(__MWERKS__)

asm static /*inline*/ void __cpu_membarrier(void) {
    sync
    jr na
    nop /* branch delay slot */
}

#else
# error compiler not supported
#endif

#define __cpu_bus_backoff() __cpu_membarrier()

#endif


__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/c/public/mips/cpuinline.h $ $Rev: 238846 $" )
