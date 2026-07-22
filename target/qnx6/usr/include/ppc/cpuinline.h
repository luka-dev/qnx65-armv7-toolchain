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

#ifndef _PPC_CPUINLINE_INCLUDED
#define _PPC_CPUINLINE_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#if defined(__GNUC__) || defined(__INTEL_COMPILER)

# define __cpu_membarrier() __extension__ ({ __asm__ __volatile__ (__PPC_SYNC_OPCODE : : : "memory"); })
# define __cpu_bus_backoff() __cpu_membarrier()

#else
# error compiler not supported
#endif

#if (defined (__GNUC__) && (__GNUC__ >= 3))

# define __CPU_ENDIAN_RET16
# define __cpu_endian_ret16(__x)                                        \
    (__builtin_constant_p(__x)                                          \
     ? (((((__x) >> 8) & 0xFF) | (((__x) & 0xFF) << 8)))                \
     : __extension__ ({                                                 \
             _Uint16t __reg = (__x);                                    \
             __asm__ __volatile__ (                                     \
                   "lhbrx %0, 0, %1"                                    \
                   : "=r" (__reg)                                       \
                   : "r" (&__reg), "m" (__reg));                        \
             __reg;                                                     \
         }))

# define __CPU_ENDIAN_RET32
# define __cpu_endian_ret32(__x)                                        \
    (__builtin_constant_p(__x)                                          \
     ? ((((__x) >> 24) & 0xFF)                                          \
        | (((__x) >> 8) & 0xFF00)                                       \
        | (((__x) & 0xFF00) << 8)                                       \
        | (((__x) & 0xFF) << 24))                                       \
     : __extension__ ({                                                 \
             _Uint32t __reg = (__x);                                    \
             __asm__ __volatile__ (                                     \
                   "lwbrx %0, 0, %1"                                    \
                   : "=r" (__reg)                                       \
                   : "r" (&__reg), "m" (__reg));                        \
             __reg;                                                     \
         }))

#endif

#endif


__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/c/public/ppc/cpuinline.h $ $Rev: 238846 $" )
