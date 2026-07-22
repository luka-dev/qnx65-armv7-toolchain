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
 *  ppc/cache.h
 *

 */
 
#ifndef _PPC_CACHE_H_INCLUDED
#define _PPC_CACHE_H_INCLUDED

#ifndef __CACHE_H_INCLUDED
#include <sys/cache.h>
#endif

#define __CPU_CACHE_FLUSH

static __inline__ void __attribute__((__unused__))
__cpu_cache_flush(struct cache_ctrl *cinfo,
    void *vaddr, uint64_t paddr, size_t len)
{
	unsigned linesize = cinfo->cache_line_size;
	unsigned __dst = (unsigned)vaddr & ~(linesize-1);
	int __nlines = (((unsigned)vaddr + len + linesize-1)-__dst)/linesize;

	while(__nlines) {	
		__asm__ __volatile__( "dcbf 0,%0;" : : "r" (__dst));
		__dst+=linesize;
		__nlines--;
	}
	__asm__ __volatile__(__PPC_SYNC_OPCODE);
}

#define __CPU_CACHE_INVAL

static __inline__ void __attribute__((__unused__))
__cpu_cache_inval(struct cache_ctrl *cinfo,
    void *vaddr, uint64_t paddr, size_t len)
{
	unsigned linesize = cinfo->cache_line_size;
	unsigned __dst = (unsigned)vaddr & ~(linesize-1);
	int __nlines = (((unsigned)vaddr + len + linesize-1)-__dst)/linesize;

	while(__nlines) {	
		__asm__ __volatile__("dcbi 0,%0;" : : "r" (__dst));
		__dst+=linesize;
		__nlines--;
	}
	__asm__ __volatile__(__PPC_SYNC_OPCODE);
}

#endif /* _PPC_CACHE_H_INCLUDED */

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/cache/public/ppc/cache.h $ $Rev: 231036 $" )
