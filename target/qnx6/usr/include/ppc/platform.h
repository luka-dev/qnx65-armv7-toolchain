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

#ifndef _PPC_PLATFORM_H_INCLUDED
#define _PPC_PLATFORM_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#error ppc/platform.h should not be included directly.
#endif

/* The Book E spec renamed the "sync" opcode to "msync" so if the assembler
   is invoked with -mbooke, it won't recognize "sync", if assembling for
   non-book E, it won't recognize "msync" :-(. Solution, hand encode the
   operation so that people are always happy.
*/   
#define __PPC_SYNC_OPCODE	".long 0x7c0004ac"

#if defined(__QNXNTO__)

__BEGIN_DECLS

# define __JMPBUFSIZE    64
typedef double __jmpbufalign;

#else
# error Not configured for target
#endif

__END_DECLS

#endif


__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/c/public/ppc/platform.h $ $Rev: 273413 $" )
