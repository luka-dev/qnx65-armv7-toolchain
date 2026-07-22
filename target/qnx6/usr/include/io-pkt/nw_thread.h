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

#ifndef _NW_THREAD_H_INCLUDED
#define _NW_THREAD_H_INCLUDED
#include <pthread.h>
#include <nw_datastruct.h>

#ifndef MBUF_CACHE_MAX
#define MBUF_CACHE_MAX 32
#endif

#ifndef PKT_CACHE_MAX
#define PKT_CACHE_MAX 32
#endif

/* Per thread caches */
extern int mbuf_cache_max;
extern int pkt_cache_max;

int nw_thread_init(void);
void nw_thread_fini(void);
void nw_thread_log_noflow(void);
int nw_thread_untracked_add(void);
int nw_thread_untracked_sub(void);
struct nw_work_thread * nw_thread_istracked(void);
int nw_pthread_create(pthread_t *, pthread_attr_t *,
    void *(*)(void *), void *arg,
    int flags, int (*)(void *), void *);
int nw_pthread_reap(pthread_t);
int nw_pthread_cleanup(struct nw_work_thread *);
#endif /* !_NW_THREAD_H_INCLUDED */

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/io-pkt/sys/nw_thread.h $ $Rev: 233581 $" )
