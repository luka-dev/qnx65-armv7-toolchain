/*
 * $QNXLicenseC:
 * Copyright 2007,2009 QNX Software Systems. All Rights Reserved.
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

#ifndef _ARM_CPUINLINE_INCLUDED
#define _ARM_CPUINLINE_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

__BEGIN_DECLS

extern unsigned __cpu_flags;

#if defined(__GNUC__) || defined(__INTEL_COMPILER)

# define __cpu_membarrier()                                             \
    __extension__ ({                                                    \
            /* check for ARM_CPU_FLAG_SMP */                            \
            if (__cpu_flags & (1<<3)) {                                 \
                /* Data Memory Barrier */                               \
                __asm__ __volatile__("mcr p15, 0, %0, c7, c10, 5" : : "r"(0) : "memory"); \
            } else {                                                    \
                __asm__ __volatile__ ("nop" : : : "memory");            \
            }                                                           \
        })

#define __cpu_bus_backoff() __cpu_membarrier()

#else
# error compiler not supported
#endif

__END_DECLS

#endif


__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/c/public/arm/cpuinline.h $ $Rev: 249886 $" )
