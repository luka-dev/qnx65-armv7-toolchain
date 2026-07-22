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
#error Do not include this file directly.  Include sys/nw_cpu_atomic.h.
#endif

#ifndef _MIPS_NW_CPU_ATOMIC_H_INCLUDED
#define _MIPS_NW_CPU_ATOMIC_H_INCLUDED

static __inline unsigned cpu_atomic_dec_value(volatile unsigned *p);
static __inline void cpu_atomic_inc(volatile unsigned *p);
static __inline void cpu_atomic_dec(volatile unsigned *p);


static __inline unsigned
cpu_atomic_dec_value(volatile unsigned *p)
{

	return atomic_sub_value(p, 1);
}

static __inline void
cpu_atomic_inc(volatile unsigned *p)
{
	return atomic_add(p, 1);
}

static __inline void
cpu_atomic_dec(volatile unsigned *p)
{
	return atomic_sub(p, 1);
}



#endif /* !_MIPS_NW_CPU_ATOMIC_H_INCLUDED */

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/io-pkt/sys/target/mips/nw_cpu_atomic.h $ $Rev: 233581 $" )
