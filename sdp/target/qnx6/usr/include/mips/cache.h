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
 *  mips/cache.h
 *

 */
 
#ifndef _MIPS_CACHE_H_INCLUDED
#define _MIPS_CACHE_H_INCLUDED

#ifndef __CACHE_H_INCLUDED
#include <sys/cache.h>
#endif

/*
 * Note that the meaning of the option operand to the "cache" instruction
 * is CPU dependant.  The operands used here should work on the majority
 * of MIPS CPU's.  In cases where different operands are needed, a
 * DLL can be provided for that particular platform, which supplies
 * the appropriate routines.
 */

#define __CACHE_SYNC_MULTIPLE

#define __CPU_CACHE_FLUSH

static __inline__ void __attribute__((__unused__))
__cpu_cache_flush(struct cache_ctrl *cinfo,
    void *vaddr, uint64_t paddr, size_t len)
{
	unsigned	linesize = cinfo->cache_line_size;
	unsigned	dst = (unsigned)vaddr & ~(linesize-1);
	unsigned	addr = dst;
	int		nlines, n;

	n = nlines = (((unsigned)vaddr + len + linesize-1)-addr)/linesize;

	/* Write-back lines in the primary data cache */
	while (n) {	
		__asm__ __volatile__(".set noreorder;" : : );
		__asm__ __volatile__(".set mips3;" : : );
		__asm__ __volatile__("cache 0x19,0(%0);" : : "r" (addr));
		__asm__ __volatile__(".set mips0;" : : );
		__asm__ __volatile__(".set reorder;" : : );
		addr+=linesize;
		n--;
	}
	if (cinfo->ncaches > 1) {
		/* Write-back lines in the secondary data cache */
		addr = dst;
		n = nlines;
		while (n) {	
			__asm__ __volatile__(".set noreorder;" : : );
			__asm__ __volatile__(".set mips3;" : : );
			__asm__ __volatile__("cache 0x1b,0(%0);" : : "r" (dst));
			__asm__ __volatile__(".set mips0;" : : );
			__asm__ __volatile__(".set reorder;" : : );
			dst+=linesize;
			n--;
		}
	}
	__asm__ __volatile__("sync;");
}

#define __CPU_CACHE_INVAL

static __inline__ void __attribute__((__unused__))
__cpu_cache_inval(struct cache_ctrl *cinfo,
    void *vaddr, uint64_t paddr, size_t len)
{
	unsigned	linesize = cinfo->cache_line_size;
	unsigned	dst = (unsigned)vaddr & ~(linesize-1);
	unsigned	addr = dst;
	int		nlines, n;

	n = nlines = (((unsigned)vaddr + len + linesize-1)-addr)/linesize;

	/* Invalidate lines in the primary data cache */
	while (n) {	
		__asm__ __volatile__(".set noreorder;" : : );
		__asm__ __volatile__(".set mips3;" : : );
		__asm__ __volatile__("cache 0x11,0(%0);" : : "r" (addr));
		__asm__ __volatile__(".set mips0;" : : );
		__asm__ __volatile__(".set reorder;" : : );
		addr+=linesize;
		n--;
	}
	if (cinfo->ncaches > 1) {
		/* Write-back lines in the secondary data cache */
		addr = dst;
		n = nlines;
		while (n) {	
			__asm__ __volatile__(".set noreorder;" : : );
			__asm__ __volatile__(".set mips3;" : : );
			__asm__ __volatile__("cache 0x13,0(%0);" : : "r" (dst));
			__asm__ __volatile__(".set mips0;" : : );
			__asm__ __volatile__(".set reorder;" : : );
			dst+=linesize;
			n--;
		}
	}
	__asm__ __volatile__("sync;");
}

#endif /* _MIPS_CACHE_H_INCLUDED */

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/cache/public/mips/cache.h $ $Rev: 219996 $" )
