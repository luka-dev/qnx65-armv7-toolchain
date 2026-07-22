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

#ifndef _X86_NW_CPU_ATOMIC_H_INCLUDED
#define _X86_NW_CPU_ATOMIC_H_INCLUDED

#ifndef __atomic_fool_gcc
struct __gcc_fool { int __fool[100]; };
#define __atomic_fool_gcc(__x) (*(volatile struct __gcc_fool *)__x)
#endif

static __inline unsigned cpu_atomic_dec_value(volatile unsigned *p);
static __inline void cpu_atomic_inc(volatile unsigned *p);
static __inline void cpu_atomic_dec(volatile unsigned *p);


static __inline unsigned
cpu_atomic_dec_value(volatile unsigned *p)
{

	unsigned ret, tmp1;

	__asm__ __volatile__ (
	    "movl            %2, %0\n\t"
	    "1:\n\t"
	    "movl            %0, %1\n\t"
	    "decl            %1\n\t"
	    "lock; cmpxchg   %1, %2\n\t"
	    "jnz 1b\n\t"
	    : "=&a" (ret), "=&r" (tmp1), "=m" (__atomic_fool_gcc(p)) : "m" (__atomic_fool_gcc(p)) : "memory");

	return ret;
}

static __inline void
cpu_atomic_inc(volatile unsigned *p)
{
	__asm__ __volatile__ (
	    "lock; incl %0\n\t"
	    : "=m" (__atomic_fool_gcc(p)) : "m" (__atomic_fool_gcc(p)) : "memory");
		
	return;
}


static __inline void
cpu_atomic_dec(volatile unsigned *p)
{
	__asm__ __volatile__ (
	    "lock; decl %0\n\t"
	    : "=m" (__atomic_fool_gcc(p)) : "m" (__atomic_fool_gcc(p)) : "memory");
		
	return;
}


#endif /* !_X86_NW_CPU_ATOMIC_H_INCLUDED */

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/io-pkt/sys/target/x86/nw_cpu_atomic.h $ $Rev: 233581 $" )
