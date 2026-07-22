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

#ifndef _SH_CPUINLINE_INCLUDED
#define _SH_CPUINLINE_INCLUDED

#if defined(__GNUC__) || defined(__INTEL_COMPILER)

# define __cpu_membarrier() __extension__ ({ __asm__ __volatile__ ("nop" : : : "memory"); })
# define __cpu_bus_backoff() __cpu_membarrier()

#else
# error compiler not supported
#endif

#if defined(__GNUC__)

# define __CPU_ENDIAN_RET16
# define __cpu_endian_ret16(__x)                                        \
    (__builtin_constant_p(__x)                                          \
     ? ((((__x) >> 8) & 0xFF) | (((__x) & 0xFF) << 8))                  \
     : __extension__ ({                                                 \
             _Uint16t __reg;                                            \
             __asm__ __volatile__ (                                     \
                   "swap.b %0, %0;"                                     \
                   : "=r" (__reg)                                       \
                   : "0" (__x)                                          \
                 );                                                     \
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
             _Uint32t __reg;                                            \
             __asm__ __volatile__ (                                     \
                   "swap.b %0, %0;"                                     \
                   "swap.w %0, %0;"                                     \
                   "swap.b %0, %0;"                                     \
                   : "=r" (__reg)                                       \
                   : "0" (__x)                                          \
                 );                                                     \
             __reg;                                                     \
         }))

# define __CPU_ENDIAN_RET64
# define __cpu_endian_ret64(__x)                                        \
    (__builtin_constant_p(__x)                                          \
     ? ((((__x) >> 56) & 0xFF)                                          \
        | (((__x) >> 40) & 0xFF00)                                      \
        | (((__x) >> 24) & 0xFF0000)                                    \
        | (((__x) >>  8) & 0xFF000000)                                  \
        | (((__x) & 0xFF000000) <<  8)                                  \
        | (((__x) & 0xFF0000) << 24)                                    \
        | (((__x) & 0xFF00) << 40)                                      \
        | (((__x) & 0xFF) << 56))                                       \
     : __extension__ ({                                                 \
             _Uint64t __value = (__x);                                  \
             _Uint64t *__vp = &(__value);                               \
             _Uint64t __rv;                                             \
             _Uint64t *__rp = &__rv;                                    \
             _Uint32t __gpr = (__gpr);                                  \
             __asm__ __volatile__ (                                     \
                   "mov.l @(4,%1),%2;"                                  \
                   "swap.b %2, %2;"                                     \
                   "swap.w %2, %2;"                                     \
                   "swap.b %2, %2;"                                     \
                   "mov.l %2, @(0,%0);"                                 \
                   "mov.l @(0,%1), %2;"                                 \
                   "swap.b %2, %2;"                                     \
                   "swap.w %2, %2;"                                     \
                   "swap.b %2, %2;"                                     \
                   "mov.l %2, @(4,%0);"                                 \
                   :                                                    \
                   : "r" (__rp), "r" (__vp), "r" (__gpr)                \
                   : "memory"                                           \
                 );                                                     \
             __rv;                                                      \
         }))

#endif

#endif


__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/c/public/sh/cpuinline.h $ $Rev: 238846 $" )
