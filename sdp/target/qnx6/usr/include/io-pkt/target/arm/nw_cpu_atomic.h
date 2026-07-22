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

#ifndef _ARM_NW_CPU_ATOMIC_H_INCLUDED
#define _ARM_NW_CPU_ATOMIC_H_INCLUDED

#ifndef __atomic_fool_gcc
struct __gcc_fool { int __fool[100]; };
#define __atomic_fool_gcc(__x) (*(volatile struct __gcc_fool *)__x)
#endif

/* These aren't interrupt safe. */
static __inline unsigned cpu_atomic_dec_value(volatile unsigned *p);
static __inline void cpu_atomic_inc(volatile unsigned *p);
static __inline void cpu_atomic_dec(volatile unsigned *p);

#ifdef VARIANT_sig
static __inline unsigned
cpu_atomic_dec_value(volatile unsigned *p)
{
	unsigned oldval, newval;

	__asm__ __volatile__ (
	    "stmdb sp!, {ip, lr};"

	    "adr ip, 1f;"	/* Start of critical section */
	    "adr lr, 2f;"	/* End of critical section */

	    "sub sp, sp, #1;"	/* Tell kernel (and ourselves) we're in a critical section */
	    "1:;"
	    "ldr %0, %3;"
	    "sub %1, %0, #1;"
	    "str %1, %2;"
	    "2:;"
	    "add sp, sp, #1;"	/* Done critical. */
	    "ldmia sp!, {ip, lr};"
	    : "=r&" (oldval), "=r&" (newval), "=m" (__atomic_fool_gcc(p)) : "m" (__atomic_fool_gcc(p)) : "memory");

	return oldval;
}

static __inline void
cpu_atomic_inc(volatile unsigned *p)
{
	unsigned val;

	__asm__ __volatile__ (
	    "stmdb sp!, {ip, lr};"

	    "adr ip, 1f;"	/* Start of critical section */
	    "adr lr, 2f;"	/* End of critical section */

	    "sub sp, sp, #1;"	/* Tell kernel (and ourselves) we're in a critical section */
	    "1:;"
	    "ldr %0, %2;"
	    "add %0, %0, #1;"
	    "str %0, %1;"
	    "2:;"
	    "add sp, sp, #1;"	/* Done critical. */
	    "ldmia sp!, {ip, lr};"
	    : "=r&" (val), "=m" (__atomic_fool_gcc(p)) : "m" (__atomic_fool_gcc(p)) : "memory");

	return;
}

static __inline void
cpu_atomic_dec(volatile unsigned *p)
{
	unsigned val;

	__asm__ __volatile__ (
	    "stmdb sp!, {ip, lr};"

	    "adr ip, 1f;"	/* Start of critical section */
	    "adr lr, 2f;"	/* End of critical section */

	    "sub sp, sp, #1;"	/* Tell kernel (and ourselves) we're in a critical section */
	    "1:;"
	    "ldr %0, %2;"
	    "sub %0, %0, #1;"
	    "str %0, %1;"
	    "2:;"
	    "add sp, sp, #1;"	/* Done critical. */
	    "ldmia sp!, {ip, lr};"
	    : "=r&" (val), "=m" (__atomic_fool_gcc(p)) : "m" (__atomic_fool_gcc(p)) : "memory");

	return;
}
#else /* !VARIANT_sig */
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
#endif /* !VARIANT_sig */

#endif /* !_ARM_NW_CPU_ATOMIC_H_INCLUDED */

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/io-pkt/sys/target/arm/nw_cpu_atomic.h $ $Rev: 233581 $" )
