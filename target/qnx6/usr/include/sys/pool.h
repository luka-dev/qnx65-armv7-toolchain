/*
 * $QNXtpLicenseC:
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



/*	$NetBSD: pool.h,v 1.54 2006/08/20 09:35:25 yamt Exp $	*/

/*-
 * Copyright (c) 1997, 1998, 1999, 2000 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Paul Kranenburg; by Jason R. Thorpe of the Numerical Aerospace
 * Simulation Facility, NASA Ames Research Center.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the NetBSD
 *	Foundation, Inc. and its contributors.
 * 4. Neither the name of The NetBSD Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __POOL_H_INCLUDED
#define __POOL_H_INCLUDED

#ifdef _KERNEL
#define	__POOL_EXPOSE
#endif

#if defined(_KERNEL_OPT)
#include "opt_pool.h"
#endif

#ifdef __POOL_EXPOSE

#ifndef __QUEUE_H_INCLUDED
#include <sys/queue.h>
#endif

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

#ifndef __TIME_H_INCLUDED
#include <sys/time.h>
#endif

#ifndef __TREE_H_INCLUDED
#include <sys/tree.h>
#endif
#if defined(_KERNEL) && !defined(__QNXNTO__)
#include <sys/callback.h>
#endif /* defined(_KERNEL) */

#endif

#define	PCG_NOBJECTS		16

#define	POOL_PADDR_INVALID	((paddr_t) -1)

#ifdef __POOL_EXPOSE

#ifdef __QNXNTO__
struct page_extra {
	off64_t		pg_phys;
	caddr_t		pg_page;
	void		*pg_extra;
};
#endif

/* The pool cache group. */
struct pool_cache_group {
	LIST_ENTRY(pool_cache_group)
		pcg_list;	/* link in the pool cache's group list */
	u_int	pcg_avail;	/* # available objects */
				/* pointers to the objects */
	struct {
		void *pcgo_va;	/* cache object virtual address */
#ifndef __QNXNTO__
		paddr_t pcgo_pa;/* cache object physical address */
#endif
	} pcg_objects[PCG_NOBJECTS];
#ifdef __QNXNTO__
	struct	pool_item_header *pcg_pool_hd;
#endif
};

LIST_HEAD(pool_cache_grouplist,pool_cache_group);
struct pool_cache {
	LIST_ENTRY(pool_cache)
			pc_poollist;	/* entry on pool's group list */
	struct pool_cache_grouplist
			pc_emptygroups;	/* list of empty cache groups */
	struct pool_cache_grouplist
			pc_fullgroups;	/* list of full cache groups */
	struct pool_cache_grouplist
			pc_partgroups;	/* list of partial cache groups */
	struct pool	*pc_pool;	/* parent pool */
#ifndef __QNXNTO__
	struct simplelock pc_slock;	/* mutex */
#else
	pthread_mutex_t pc_slock;
#endif

	int		(*pc_ctor)(void *, void *, int);
	void		(*pc_dtor)(void *, void *);
	void		*pc_arg;

	/* Statistics. */
	unsigned long	pc_hits;	/* cache hits */
	unsigned long	pc_misses;	/* cache misses */

	unsigned long	pc_ngroups;	/* # cache groups */

	unsigned long	pc_nitems;	/* # objects currently in cache */
};

struct pool_allocator {
	void		*(*pa_alloc)(struct pool *, int);
	void		(*pa_free)(struct pool *, void *);
	unsigned int	pa_pagesz;

	/* The following fields are for internal use only. */
#ifndef __QNXNTO__
	struct simplelock pa_slock;
#endif
	TAILQ_HEAD(, pool) pa_list;	/* list of pools using this allocator */
	int		pa_flags;
#define	PA_INITIALIZED	0x01
#define	PA_WANT		0x02		/* wakeup any sleeping pools on free */
	int		pa_pagemask;
	int		pa_pageshift;
};

LIST_HEAD(pool_pagelist,pool_item_header);

struct pool {
	LIST_ENTRY(pool)
			pr_poollist;
	struct pool_pagelist
			pr_emptypages;	/* Empty pages */
	struct pool_pagelist
			pr_fullpages;	/* Full pages */
	struct pool_pagelist
			pr_partpages;	/* Partially-allocated pages */
	struct pool_item_header	*pr_curpage;
	struct pool	*pr_phpool;	/* Pool item header pool */
	LIST_HEAD(,pool_cache)
			pr_cachelist;	/* Caches for this pool */
	unsigned int	pr_size;	/* Size of item */
	unsigned int	pr_align;	/* Requested alignment, must be 2^n */
	unsigned int	pr_itemoffset;	/* Align this offset in item */
	unsigned int	pr_minitems;	/* minimum # of items to keep */
	unsigned int	pr_minpages;	/* same in page units */
	unsigned int	pr_maxpages;	/* maximum # of pages to keep */
	unsigned int	pr_npages;	/* # of pages allocated */
	unsigned int	pr_itemsperpage;/* # items that fit in a page */
	unsigned int	pr_typed_mem_fd;
	unsigned int	pr_nitems;	/* number of available items in pool */
	unsigned int	pr_nout;	/* # items currently allocated */
	unsigned int	pr_hardlimit;	/* hard limit to number of allocated
					   items */
	struct pool_allocator *pr_alloc;/* back-end allocator */
	TAILQ_ENTRY(pool) pr_alloc_list;/* link on allocator's pool list */

	/* Drain hook. */
	void		(*pr_drain_hook)(void *, int);
	void		*pr_drain_hook_arg;

	const char	*pr_wchan;	/* tsleep(9) identifier */
	unsigned int	pr_flags;	/* r/w flags */
	unsigned int	pr_roflags;	/* r/o flags */
#define	PR_NOWAIT	0x00000000		/* for symmetry */
#define PR_WAITOK	0x00000002
#define PR_WANTED	0x00000004
#define PR_PHINPAGE	0x00000040
#define PR_LOGGING	0x00000080
#define PR_LIMITFAIL	0x00000100	/* even if waiting, fail if we hit limit */
#define PR_RECURSIVE	0x00000200	/* pool contains pools, for vmstat(8) */
#define PR_NOTOUCH	0x00000400	/* don't use free items to keep internal state*/
#define PR_NOALIGN	0x00000800	/* don't assume backend alignment */
#ifdef __QNXNTO__
#define PR_PROTECT	0x80000000
#define PR_PHYS		0x40000000
#define PR_NOCACHE	0x20000000
#define PR_EXTRA	0x10000000
#define PR_BIGPAGE	0x08000000
#define PR_PG_ARG	0x04000000
#endif

	/*
	 * `pr_slock' protects the pool's data structures when removing
	 * items from or returning items to the pool, or when reading
	 * or updating read/write fields in the pool descriptor.
	 *
	 * We assume back-end page allocators provide their own locking
	 * scheme.  They will be called with the pool descriptor _unlocked_,
	 * since the page allocators may block.
	 */
#ifndef __QNXNTO__
	struct simplelock	pr_slock;
#else
	pthread_mutex_t		pr_slock;
#endif

	SPLAY_HEAD(phtree, pool_item_header) pr_phtree;

	int		pr_maxcolor;	/* Cache colouring */
	int		pr_curcolor;
	int		pr_phoffset;	/* Offset in page of page header */

	/*
	 * Warning message to be issued, and a per-time-delta rate cap,
	 * if the hard limit is reached.
	 */
	const char	*pr_hardlimit_warning;
	struct timeval	pr_hardlimit_ratecap;
	struct timeval	pr_hardlimit_warning_last;

	/*
	 * Instrumentation
	 */
	unsigned long	pr_nget;	/* # of successful requests */
	unsigned long	pr_nfail;	/* # of unsuccessful requests */
	unsigned long	pr_nput;	/* # of releases */
	unsigned long	pr_npagealloc;	/* # of pages allocated */
	unsigned long	pr_npagefree;	/* # of pages released */
	unsigned int	pr_hiwat;	/* max # of pages in pool */
	unsigned long	pr_nidle;	/* # of idle pages */

	/*
	 * Diagnostic aides.
	 */
	struct pool_log	*pr_log;
	int		pr_curlogentry;
	int		pr_logsize;

	const char	*pr_entered_file; /* reentrancy check */
	long		pr_entered_line;

#if defined(_KERNEL) && !defined(__QNXNTO__)
	struct callback_entry pr_reclaimerentry;
#endif
};
#endif /* __POOL_EXPOSE */

#ifdef _KERNEL
#ifdef __QNXNTO__
struct nw_work_thread;
#endif
/*
 * pool_allocator_kmem is the default that all pools get unless
 * otherwise specified.  pool_allocator_nointr is provided for
 * pools that know they will never be accessed in interrupt
 * context.
 */
extern struct pool_allocator pool_allocator_kmem;
extern struct pool_allocator pool_allocator_nointr;
#ifdef POOL_SUBPAGE
/* The above are subpage allocators in this case. */
extern struct pool_allocator pool_allocator_kmem_fullpage;
extern struct pool_allocator pool_allocator_nointr_fullpage;
#endif

struct link_pool_init {	/* same as args to pool_init() */
	struct pool *pp;
	size_t size;
	u_int align;
	u_int align_offset;
	int flags;
	const char *wchan;
	struct pool_allocator *palloc;
};
#define	POOL_INIT(pp, size, align, align_offset, flags, wchan, palloc)	\
struct pool pp;								\
static const struct link_pool_init _link_ ## pp[1] = {			\
	{ &pp, size, align, align_offset, flags, wchan, palloc }	\
};									\
__link_set_add_rodata(pools, _link_ ## pp)

void		pool_subsystem_init(void);

void		pool_init(struct pool *, size_t, u_int, u_int,
		    int, const char *, struct pool_allocator *);
#ifdef __QNXNTO__
void		pool_subsystem_birth(void *);
void		pool_init_extra(struct pool *, size_t, u_int, u_int,
		    int, const char *, struct pool_allocator *,
		    size_t, int);
#endif
void		pool_destroy(struct pool *);

void		pool_set_drain_hook(struct pool *,
		    void (*)(void *, int), void *);

void		*pool_get_header(struct pool *, int, struct page_extra**);
void		pool_put_header(struct pool *, void *, struct page_extra *);
int		pool_reclaim(struct pool *);

#ifdef POOL_DIAGNOSTIC
/*
 * These versions do reentrancy checking.
 */
void		*_pool_get_header(struct pool *, int, struct page_extra *, const char *, long);
void		_pool_put_header(struct pool *, void *, struct page_extra *, const char *, long);
int		_pool_reclaim(struct pool *, const char *, long);
#define		pool_get(h, f)	_pool_get_header((h), (f), NULL,  __FILE__, __LINE__)
#define		pool_put(h, v)	_pool_put_header((h), (v), NULL, __FILE__, __LINE__)
#define		pool_reclaim(h)	_pool_reclaim((h), __FILE__, __LINE__)
#else
#define		pool_get(h, f)	pool_get_header((h), (f), NULL)
#define		pool_put(h, v)	pool_put_header((h), (v), NULL)
#endif /* POOL_DIAGNOSTIC */

static __inline off64_t		pool_phys(void *v, struct page_extra *ph);
int		pool_prime(struct pool *, int);
void		pool_setlowat(struct pool *, int);
void		pool_sethiwat(struct pool *, int);
void		pool_sethardlimit(struct pool *, int, const char *, int);
void		pool_drain(void *);

/*
 * Debugging and diagnostic aides.
 */
void		pool_print(struct pool *, const char *);
void		pool_printit(struct pool *, const char *,
		    int (*)(const char *, ...));
void		pool_printall(const char *, int (*)(const char *, ...));
int		pool_chk(struct pool *, const char *);

/*
 * Pool cache routines.
 */
void		pool_cache_init(struct pool_cache *, struct pool *,
		    int (*)(void *, void *, int),
		    void (*)(void *, void *),
		    void *);
void		pool_cache_destroy(struct pool_cache *);
void		*pool_cache_get_header(struct pool_cache *, int, struct page_extra **, struct nw_work_thread **);
void		pool_cache_put_header(struct pool_cache *, void *, struct page_extra *, struct nw_work_thread *);
void		pool_cache_destruct_object_header(struct pool_cache *, void *, struct pool_item_header *);
void		pool_cache_destruct_object(struct pool_cache *, void *);
void		pool_cache_invalidate(struct pool_cache *);


static __inline off64_t
pool_phys(void *v, struct page_extra *pg)
{
	return (pg->pg_phys + ((char *)v - (char *)pg->pg_page));
}
#endif /* _KERNEL */

#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/socket/public/sys/pool.h $ $Rev: 261817 $" )
#endif /* !__POOL_H_INCLUDED */
