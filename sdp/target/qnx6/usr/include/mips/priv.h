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



/*
 * Privledged instructions for kernel
 *

 *
 */
#ifndef __MIPS_PRIV_H_INCLUDED
#define __MIPS_PRIV_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

#include <mips/cpu.h>

#if defined(__GNUC__)

#define SSNOP()	asm volatile("sll $0,$0,1")

#define CP0REG_GET(regno)			\
	({ _Uint32t	__val;				\
		__asm__ __volatile__ (		\
			".set noreorder		;"	\
			"mfc0 	%0, $%1 	;"	\
			"sll	$0,$0,1		;"	\
			".set reorder		;"	\
			: "=r" (__val)			\
			: "i" (regno));			\
			__val;					\
	})

#define CP0REG_SET(regno, val)		\
	(void) ({ __asm__ __volatile__ (		\
			".set noreorder		;"	\
			"mtc0 	%0, $%1 	;"	\
			"sll	$0,$0,1		;"	\
			".set reorder		;"	\
			: 						\
			: "r" (val), "i" (regno));\
	})

/*Revisit once assembler supports 'sel' operand for m[tf]c0 opcode.*/
#define CP0REG_SEL_GET(regno,sel)	\
	({ _Uint32t	__val;				\
		__asm__ __volatile__ (				\
			".set noreorder		;"	\
			".set noat			;"	\
			".word (0x40000000 | ((1)<<16) | ((%1)<<11) | (%2));" \
			"nop				;"	\
			"move  %0,$1		;"	\
			".set reorder		;"	\
			".set at			;"	\
			: "=r" (__val)			\
			: "i" (regno), "i" (sel));	\
			__val;					\
	})

/*Revisit once assembler supports 'sel' operand for m[tf]c0 opcode.*/
#define CP0REG_SEL_SET(regno, sel, val)	\
	(void) ({ __asm__ __volatile__ (			\
			".set noreorder		;"	\
			".set noat			;"	\
			"move  $1,%0		;"	\
			".word (0x40800000 | ((1)<<16) | ((%1)<<11) | (%2));" \
			"nop				;"	\
			".set reorder		;"	\
			".set at			;"	\
			: 						\
			: "r" (val), "i" (regno), "i" (sel));\
	})

static inline _Uint32t __attribute__((__unused__))
getcp0_prid(void) {
	return CP0REG_GET(15);
}

/*
 * setcp0_config()
 *	Program the R4K config register.
 */
static inline void __attribute__((__unused__))
setcp0_config(_Uint32t __config) {
	CP0REG_SET(16, __config);
}

/*
 * getcp0_sreg()
 *	Return the R4K status register
 */
static inline _Uint32t __attribute__((__unused__))
getcp0_sreg(void) {
	return CP0REG_GET(12);
}

/*
 * setcp0_sreg()
 *	Set the R4K status register
 */
static inline void __attribute__((__unused__))
setcp0_sreg(_Uint32t __status) {
	CP0REG_SET(12, __status);
}

/*
 * getcp0_wired()
 *	Return the R4K wired register
 */
static inline _Uint32t __attribute__((__unused__))
getcp0_wired(void) {
	return CP0REG_GET(6);
}

/*
 * setcp0_wired()
 *	Set the R4K wired register
 */
static inline void __attribute__((__unused__))
setcp0_wired(_Uint32t __wired) {
	CP0REG_SET(6, __wired);
}

/*
 * getcp0_pagemask()
 *	Return the R4K page mask register
 */
static inline _Uint32t __attribute__((__unused__))
getcp0_pagemask(void) {
	return CP0REG_GET(5);
}

/*
 * setcp0_pagemask()
 *	Set the R4K page mask register
 */
static inline void __attribute__((__unused__))
setcp0_pagemask(_Uint32t __pagemask) {
	CP0REG_SET(5, __pagemask);
}

/*
 * getcp0_tlb_hi()
 *	Return the R4K TLB high register
 */
static inline _Uint32t __attribute__((__unused__))
getcp0_tlb_hi(void) {
	return CP0REG_GET(10);
}

/*
 * setcp0_tlb_hi()
 *	Set the R4K TLB high register
 */
static inline void __attribute__((__unused__))
setcp0_tlb_hi(_Uint32t __tlbhi) {
	CP0REG_SET(10, __tlbhi);
}

/*
 * getcp0_epc()
 *  Get CP0 epc register
 */
inline static unsigned long __attribute__((__unused__))
getcp0_epc(void) {
  return CP0REG_GET(14);
}

inline static _Uint32t __attribute__((__unused__))
getcp0_cerr_dpa(void) {
  return CP0REG_SEL_GET(27,3);
}

/*
 * r4k_settlb_inline:
 *	Write a tlb entry into a specific index
 */
static inline void __attribute__((__unused__))
r4k_settlb_inline(_Uint32t __hi, _Uint32t __lo0, _Uint32t __lo1, _Uint32t __idx) {
	int __tmp1, __tmp2, __tmp3;

	__asm__ __volatile__ (
		".set noreorder		;"
		"mfc0 	%0, $12; 	;" /* read status register */
		"li	%1, ~1		;" /* ~MIPS_SREG_IE */
		"and	%1,%1,%0	;" /* disable interrupts */
		"mtc0	%1, $12		;"
		"mfc0 	%2, $10;	;" /* save asid in entryhi */
		"nop			;"
		"mtc0	%3, $10		;" /* write entryhi */
		"nop			;"
		"mtc0	%4, $2		;" /* write entrylo0 */
		"nop			;"
		"mtc0	%5, $3		;" /* write entrylo1 */
		"nop			;"
		"mtc0	%6, $0		;" /* write index register */
		"nop			;" /* 4 nops needed for R7K hazard */
		"nop			;"
		"nop			;"
		"nop			;"
		"tlbwi			;" /* write indexed tlb */
		"nop			;"
		"nop			;"
		"nop			;"
		"mtc0	%2, $10		;" /* restore entryhi */
		"mtc0	%0, $12		;" /* restore status register */
		" nop			;"
		".set	reorder		;"
		: "=&r" (__tmp1), "=&r" (__tmp2), "=&r" (__tmp3)
		: "r" (__hi), "r" (__lo0), "r" (__lo1), "r" (__idx));
}

/*
 * getcp0_count()
 *
 * Return the value of the count register.
 */
inline static unsigned long __attribute__((__unused__))
getcp0_count(void) {
	return CP0REG_GET(9);
}

/*
 * setcp0_count()
 *	Write value to CP0 count register
 */
inline static void __attribute__((__unused__))
setcp0_count(unsigned long __count) {
	CP0REG_SET(9, __count);
}

/*
 * getcp0_compare()
 *	Get current value of the CP0 compare register
 */
inline static unsigned long __attribute__((__unused__))
getcp0_compare(void) {
	return CP0REG_GET(11);
}

/*
 * setcp0_compare()
 *	Set value of CP0 compare register
 */
inline static void __attribute__((__unused__))
setcp0_compare(unsigned long __val) {
	CP0REG_SET(11, __val);
}

/*
 * getcp0_config()
 *	Get CP0 configuration register
 */
inline static unsigned long __attribute__((__unused__))
getcp0_config(void) {
	return CP0REG_GET(16);
}

/*
 * getcp0_cause()
 *	Get CP0 cause register
 */
inline static unsigned long __attribute__((__unused__))
getcp0_cause(void) {
	return CP0REG_GET(13);
}

/*
 * getcp0_err_epc()
 *	Get CP0 err_epc register
 */
inline static unsigned long __attribute__((__unused__))
getcp0_err_epc(void) {
	return CP0REG_GET(30);
}

/*
 * getcp0_taglo()
 *	Get CP0 taglo register
 */
inline static unsigned long __attribute__((__unused__))
getcp0_taglo(void) {
	return CP0REG_GET(28);
}

/*
 * setcp0_taglo()
 *	Set value of CP0 taglo register
 */
inline static void __attribute__((__unused__))
setcp0_taglo(unsigned long __val) {
	CP0REG_SET(28, __val);
}

/*
 * getcp0_cerr()
 *	Get CP0 cache_err register
 */
inline static _Uint32t __attribute__((__unused__))
getcp0_cerr(void) {
	return CP0REG_GET(27);
}

/*
 * getcp0_lladdr()
 *	Return the R4K load linked address register
 */
static inline _Uint32t __attribute__((__unused__))
getcp0_lladdr(void) {
	return CP0REG_GET(17);
}

/*
 * setcp0_lladdr()
 *	Set the R4K load linked address register
 */
static inline void __attribute__((__unused__))
setcp0_lladdr(_Uint32t __lladdr) {
	CP0REG_SET(17, __lladdr);
}

static inline void __attribute__((__unused__))
setcp0_sel0_config(_Uint32t __config) {
  CP0REG_SEL_SET(16, 0, __config);
}

static inline void __attribute__((__unused__))
setcp0_sel1_config(_Uint32t __config) {
  CP0REG_SEL_SET(16, 1, __config);
}

static inline void __attribute__((__unused__))
setcp0_sel2_config(_Uint32t __config) {
  CP0REG_SEL_SET(16, 2, __config);
}
inline static unsigned long __attribute__((__unused__))
getcp0_sel0_config(void) {
	return CP0REG_SEL_GET(16, 0);
}

inline static unsigned long __attribute__((__unused__))
getcp0_sel1_config(void) {
	return CP0REG_SEL_GET(16, 1);
}

inline static unsigned long __attribute__((__unused__))
getcp0_sel2_config(void) {
	return CP0REG_SEL_GET(16, 2);
}

/*
 * r7k_getcp0_perf_reg()
 *    Return the R7K performance register
 */
static inline _Uint32t __attribute__((__unused__))
r7k_getcp0_perf_reg(void) {
	return CP0REG_GET(22);
}

/*
 * r7k_setcp0_perf_reg()
 *    Set the R7K performance register
 */
static inline void __attribute__((__unused__))
r7k_setcp0_perf_reg(_Uint32t __val) {
	CP0REG_SET(22, __val);
}
#elif defined(__MWERKS__)

#define __MWINL inline __declspec(naked)
#define __MWRGET asm static /*inline*/ _Uint32t
#define __MWRSET asm static /*inline*/ void

#define CP0REG_GET(regno) \
		.set noreorder		;\
		mfc0 v0, $regno		;\
		jr ra			;\
		nop			/* branch delay slot */

#define CP0REG_SET(regno) \
		.set noreorder		;\
		mtc0 $regno, a0		;\
		jr ra			;\
		nop			/* branch delay slot */


asm static /*inline*/ void 
SSNOP(void) {
	sll zero,zero,1
}

__MWRGET
getcp0_prid(void) {
	CP0REG_GET(15);
}

/*
 * setcp0_config()
 *	Program the R4K config register.
 */
__MWRSET
setcp0_config(_Uint32t __config) {
	CP0REG_SET(16);
}

/*
 * getcp0_sreg()
 *	Return the R4K status register
 */
__MWRGET
getcp0_sreg(void) {
	CP0REG_GET(12);
}

/*
 * setcp0_sreg()
 *	Set the R4K status register
 */
__MWRSET
setcp0_sreg(_Uint32t __status) {
	CP0REG_SET(12);
}

/*
 * getcp0_wired()
 *	Return the R4K wired register
 */
__MWRGET
getcp0_wired(void) {
	CP0REG_GET(6);
}

/*
 * setcp0_wired()
 *	Set the R4K wired register
 */
__MWRSET
setcp0_wired(_Uint32t __wired) {
	CP0REG_SET(6);
}

/*
 * getcp0_pagemask()
 *	Return the R4K page mask register
 */
__MWRGET
getcp0_pagemask(void) {
	CP0REG_GET(5);
}

/*
 * setcp0_pagemask()
 *	Set the R4K page mask register
 */
__MWRSET
setcp0_pagemask(_Uint32t __pagemask) {
	CP0REG_SET(5);
}

/*
 * getcp0_tlb_hi()
 *	Return the R4K TLB high register
 */
__MWRGET
getcp0_tlb_hi(void) {
	CP0REG_GET(10);
}

/*
 * setcp0_tlb_hi()
 *	Set the R4K TLB high register
 */
__MWRSET
setcp0_tlb_hi(_Uint32t __tlbhi) {
	CP0REG_SET(10);
}

/*
 * r4k_settlb_inline:
 *	Write a tlb entry into a specific index
 */
asm static /*inline*/ void
r4k_settlb_inline(_Uint32t __hi, _Uint32t __lo0, _Uint32t __lo1, _Uint32t __idx) {
	/*
		t0 = tmp1, t1 = tmp2, t2 = tmp3
		a0 = __hi, a1 = __lo0, a2 = __lo1, a3 = __idx
	 */
	.set noreorder
	mfc0	t0, $12		/* read status register */
	li	t1, ~1		/* ~MIPS_SREG_IE */
	and	t1, t1, zero	/* disable interrupts */
	mtc0	t1, $12
	mfc0	t2, $10
	nop
	mtc0	a0, $10		/* write entryhi */
	nop
	mtc0	a1, $2		/* write entrylo0 */
	nop
	mtc0	a2, $3		/* write entrylo1 */
	nop
	mtc0	a3, $0		/* write index register */
	nop
	tlbwi
	nop
	nop
	nop
	mtc0	t2, $10		/* restore entryhi */
	mtc0	t0, $12		/* restore status register */
	nop
	jr ra
	nop
}

/*
 * getcp0_count()
 *
 * Return the value of the count register.
 */
__MWRGET
getcp0_count(void) {
	CP0REG_GET(9);
}

/*
 * setcp0_count()
 *	Write value to CP0 count register
 */
__MWRSET
setcp0_count(unsigned long __count) {
	CP0REG_SET(9);
}

/*
 * getcp0_compare()
 *	Get current value of the CP0 compare register
 */
__MWRGET
getcp0_compare(void) {
	CP0REG_GET(11);
}

/*
 * setcp0_compare()
 *	Set value of CP0 compare register
 */
__MWRSET
setcp0_compare(unsigned long __val) {
	CP0REG_SET(11);
}

/*
 * getcp0_config()
 *	Get CP0 configuration register
 */
__MWRGET
getcp0_config(void) {
	CP0REG_GET(16);
}

/*
 * getcp0_cause()
 *	Get CP0 cause register
 */
__MWRGET
getcp0_cause(void) {
	CP0REG_GET(13);
}

/*
 * getcp0_err_epc()
 *	Get CP0 err_epc register
 */
__MWRGET
getcp0_err_epc(void) {
	CP0REG_GET(30);
}

/*
 * getcp0_taglo()
 *	Get CP0 taglo register
 */
__MWRGET
getcp0_taglo(void) {
	CP0REG_GET(28);
}

/*
 * setcp0_taglo()
 *	Set value of CP0 taglo register
 */
__MWRSET
setcp0_taglo(unsigned long __val) {
	CP0REG_SET(28);
}

/*
 * getcp0_cerr()
 *	Get CP0 cache_err register
 */
__MWRGET
getcp0_cerr(void) {
	CP0REG_GET(27);
}

/*
 * getcp0_lladdr()
 *	Return the R4K load linked address register
 */
__MWRGET
getcp0_lladdr(void) {
	CP0REG_GET(17);
}

/*
 * setcp0_lladdr()
 *	Set the R4K load linked address register
 */
__MWRSET
setcp0_lladdr(_Uint32t __lladdr) {
	CP0REG_SET(17);
}

#endif

#endif /* __MIPS_PRIV_H_INCLUDED */

/* __SRCVERSION("priv.h $Rev: 161180 $"); */
