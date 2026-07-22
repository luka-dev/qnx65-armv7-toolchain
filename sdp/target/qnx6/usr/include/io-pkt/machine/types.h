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





#ifndef _MACHINE_TYPES_H_INCLUDED
#define _MACHINE_TYPES_H_INCLUDED

#ifndef _INTTPYES_H_INCLUIDED
#include <inttypes.h>
#endif

#if defined(__X86__) || defined(__PPC__) || defined (__MIPS__) || defined(__SH__) || defined(__ARM__)
typedef uint32_t register_t;
#else
#error register_t not defined for cpu
#endif

#if defined(__X86__) || defined(__PPC__) || defined (__MIPS__) || defined(__SH__) || defined(__ARM__)
typedef uint32_t vaddr_t;
#else
#error vaddr_t not defined for cpu
#endif


#if defined(__X86__)
#define __NO_STRICT_ALIGNMENT
#elif defined(__PPC__) || defined(__ARM__) || defined(__SH__) || defined(__MIPS__)
/* Nothing */
#else
#error __NO_STRICT_ALIGNMENT not defined for cpu
#endif

#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/io-pkt/sys/machine/types.h $ $Rev: 233581 $" )
