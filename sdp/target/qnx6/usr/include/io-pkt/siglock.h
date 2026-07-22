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



#ifndef _SIGLOCK_H_INCLUDED
#define _SIGLOCK_H_INCLUDED

#include <sys/io-pkt.h>
#include "nw_defs.h"
#include "nw_datastruct.h"
#include "nw_intr.h"
#include "nw_tls.h"


/* From "lib/c/inc/cpucfg.h" */
#if defined(__X86__)
	static __inline__ struct _thread_local_storage * __attribute__((__unused__,__const__)) LIBC_TLS(void) {
		register struct _thread_local_storage		*__p;
		__asm__ (
			"movl %%fs:0,%0"
			: "=r" (__p):);
		return __p;
	}
#elif defined(__MIPS__)
	#include <sys/syspage.h>
	#include <mips/cpu.h>
	#include <mips/priv.h>

	extern struct cpupage_entry *_cpupage_ptr;
	#define LIBC_TLS()	(_cpupage_ptr->tls)

#elif defined(__PPC__)

	#include <sys/syspage.h>
	#include <ppc/cpu.h>
	#include <ppc/inline.h>

	extern struct cpupage_entry *_cpupage_ptr;
	#define LIBC_TLS()	(_cpupage_ptr->tls)
#elif defined(__SH__)
	#include <sys/syspage.h>
	#include <sh/cpu.h>
	#include <sh/inline.h>

	extern struct cpupage_entry *_cpupage_ptr;
	#define LIBC_TLS()	(_cpupage_ptr->tls)

#elif defined(__ARM__)

	#include <sys/syspage.h>
	extern struct cpupage_entry *_cpupage_ptr;
	#define LIBC_TLS()	(_cpupage_ptr->tls)
#else

	#error not configured for system

#endif

#define LIBC_TLS_TID()	LIBC_TLS()->NW_TLS_TID


/*
 * There will be times when we are 'the stack' when we'll
 * want to defer handling an interrupt (touching queues
 * shared by stack and threads handling interrupts at process
 * time).  Since we don't go back through the kernel on
 * return from our signal handler, it doesn't do the magic
 * restart if we were blocked on a mutex so we have to check
 * for EINTR.
 *
 * Drivers can't be interrupted by a signal because signal
 * delevery isn't re-enabled until they put themselves back
 * on the intr_ctrl.ic_intr.threads Q.
 *
 * Mutexes local to the stack can't fail because the stack
 * is single threaded and therefore they are never contested
 * and therefore the kernel call is never made.
 *
 * The rule then becomes: any mutex shared between the stack
 * and a driver is a contested mutex whose lock access by the
 * stack could fail with EINTR.  Such mutexes must be wrapped
 * in a iopkt_siglock().  There is code in int_sig_handler()
 * that detects contention and logs it as a fatal event:
 * undesireable because we shouldn't have a mutex at interrupt
 * time, potentially fatal because we may recurse on the mutex
 * and end up deadlocked (if it was contested once it can happen
 * again).
 * 
 * The proper behaviour will be to wrap known contested mutexes
 * in a iopkt_siglock() / unlock(). This will eliminate
 * contention on the inner mutex plus hold off operations on
 * the interrupt until the outer unlock().  This final point is
 * important because it ensures interrupts are processed without
 * any mutexes which in turn is important as the interrupt
 * handling time is indeterminate depending on load.
 */

#ifndef VARIANT_uni
#define WTP (stk_ctl.work_threads[NW_TID_TO_TIDX(LIBC_TLS_TID())])
#else
#define WTP (stk_ctl.work_threads[0])
#endif













#if defined(VARIANT_uni)

#define NW_INTR_LK(ihp)				InterruptDisable()
#define NW_INTR_UNLK(ihp)			InterruptEnable()

#else

/* SMP or general case */

#define NW_INTR_LK(ihp)				InterruptLock(&(ihp)->spin)
#define NW_INTR_UNLK(ihp)			InterruptUnlock(&(ihp)->spin)

#endif



#define NW_EX_T		pthread_mutex_t

static __inline void NW_EX_LK(pthread_mutex_t *exp, struct _iopkt_self *iopkt);
static __inline void NW_EX_UNLK(pthread_mutex_t *exp, struct _iopkt_self *iopkt);

#if !defined(NDEBUG) || (!defined(VARIANT_uni) && !defined(VARIANT_SMP))
/* The debug or general case */
static __inline void
NW_EX_LK(pthread_mutex_t *exp, struct _iopkt_self *iopkt)
{
	(*iopkt->ex_lk)(exp);
}

static __inline void
NW_EX_UNLK(pthread_mutex_t *exp, struct _iopkt_self *iopkt)
{
	(*iopkt->ex_unlk)(exp);
}

#elif defined(VARIANT_uni)
/* Non debug uni */
static __inline void
NW_EX_LK(pthread_mutex_t *exp, struct _iopkt_self *iopkt)
{
	return;
}

static __inline void
NW_EX_UNLK(pthread_mutex_t *exp, struct _iopkt_self *iopkt)
{
	return;
}

#else /* VARIANT_smp */
/* Non debug smp */
static __inline void
NW_EX_LK(pthread_mutex_t *exp, struct _iopkt_self *iopkt)
{
	_mutex_lock(exp);
}

static __inline void
NW_EX_UNLK(pthread_mutex_t *exp, struct _iopkt_self *iopkt)
{
	_mutex_unlock(exp);
}

#endif 





/*
 * TRYLK must be matched with TRYUNLK to keep counts on mutex consistent.
 * Counts aren't addressed with inline _mutex_*lock() versions.
 */
static __inline int
NW_EX_TRYLK(pthread_mutex_t *exp)
{
#ifndef VARIANT_uni
	return pthread_mutex_trylock(exp);
#else
	/* uni doesn't initialize mutexes */
	return 0;
#endif
}

static __inline void
NW_EX_TRYUNLK(pthread_mutex_t *exp)
{
#ifndef VARIANT_uni
	pthread_mutex_unlock(exp);
#else
	/* uni doesn't initialize mutexes */
#endif
}

static __inline int
NW_EX_INIT(NW_EX_T *exp, struct _iopkt_self *iopkt)
{
	return (*iopkt->ex_init)(exp);
}

static __inline int
NW_EX_DESTROY(NW_EX_T *exp, struct _iopkt_self *iopkt)
{
	return (*iopkt->ex_destroy)(exp);
}


/*
 * SIGHOLD atomicity notes:
 * 
 * These are per thread values so we don't need protection at that level.
 * However, a particular thread can be hit by a signal which may call these
 * reentrantly.  This would seem to leave a window on risc / load-store
 * architectures; however, hold and unhold always com in pairs.  Therefore,
 * if we get hit by a signal after a load but before a store, any mod is
 * undone before the signal returns.  Recall the signal handler itself can't
 * be recursed into.
 */
#define NW_SIGHOLD_P(wtp)	\
do {				\
	(wtp)->wt_critical++;	\
} while (/* CONSTCOND */ 0)

#define NW_SIGUNHOLD_P(wtp)						\
do {									\
	if (--(wtp)->wt_critical == 0 && (wtp)->wt_intr_pending) {	\
		(wtp)->wt_intr_pending = 0;				\
		process_interrupts((wtp));				\
	}								\
} while (/* CONSTCOND */ 0)


/* As above with mutex */
#define NW_SIGLOCK_P(exp, iopkt, wtp)		\
do {						\
	NW_SIGHOLD_P((wtp));			\
	NW_EX_LK((exp), (iopkt));		\
} while (/* CONSTCOND */ 0)

#define NW_SIGUNLOCK_P(exp, iopkt, wtp)		\
do {						\
	NW_EX_UNLK((exp), (iopkt));		\
	NW_SIGUNHOLD_P((wtp));			\
} while (/* CONSTCOND */ 0)





/* Versions of above where we have to look up wtp */

#define NW_SIGHOLD		NW_SIGHOLD_P(WTP)

#define NW_SIGUNHOLD				\
do {						\
	struct nw_work_thread *wtp;		\
						\
	wtp = WTP;				\
	NW_SIGUNHOLD_P((wtp));			\
} while (/* CONSTCOND */ 0)

#define NW_SIGLOCK(exp, iopkt)		NW_SIGLOCK_P((exp), (iopkt), WTP)

#define NW_SIGUNLOCK(exp, iopkt)	NW_SIGUNLOCK_P((exp), (iopkt), WTP)


#define ISSTACK_P(wtp)		((wtp)->am_stack != 0)
#define ISSTACK			ISSTACK_P(WTP)

/*
 * Checking for stack isn't sufficient in some of the
 * layer 2 code (e.g. if reached from ipflow code in
 * a signal generated interrupt context).  Note: it's
 * possible to be processing interrupts while the stack
 * with sighot=1 if we're processing interrupts due to
 * pulse notification rather than signal.  This can
 * happen if we originated from the top of the stack
 * processing loop.  This is OK since top of loop
 * means we know we haven't jumped out in a critical
 * (but unmarked) section.
 */
#define ISIRUPT_P(wtp)		(!ISSTACK_P(wtp) || (wtp)->intr_sighot == 0)
#define ISIRUPT			ISIRUPT_P(WTP)

#define ISSTART			(LIBC_TLS()->NW_TLS_TID < NW_DEF_TID_BASE_OFF)



#endif /* !_SIGLOCK_H_INCLUDED */


__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/io-pkt/sys/siglock.h $ $Rev: 233581 $" )
