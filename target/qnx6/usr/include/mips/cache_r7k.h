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


/*------------------------------------------------------------------
 * cache_r7k.h
 *
 * MIPS R7K cache control declarations.
 *
 *------------------------------------------------------------------
 */

#ifndef __CACHE_R7K_H__
#define __CACHE_R7K_H__

#define COP(op,cache)   (((op)<<2)+(cache))

#define MIPS_CONFIG_R7K_TCACHE_SIZE_MASK 0x00300000
#define MIPS_CONFIG_R7K_TCACHE_SIZE_SHIFT 20

#define MIPS_R7K_SCACHE_SIZE_LINES (256*1024)/32
        
#define MIPS_R7K_TCACHE_LINES_PER_PAGE 128
#define MIPS_R7K_TCACHE_LINE_SIZE 32
#define MIPS_R7K_TCACHE_LINE_SIZE_LOG2  0x5


#ifndef __ASM__
void r7k_inv_secondary_cache(void);
void r7k_inv_tertiary_cache(void);
void r7k_inv_secondary_cache_asm(void);
void r7k_inv_tertiary_cache_asm(unsigned int size);
void r7k_enable_secondary_cache(void);
void r7k_enable_tertiary_cache(void);
unsigned int r7k_level2_cache_detect (void);
unsigned int r7k_level3_cache_detect (void);

void r7k_cache_mem_blocking_mode_enable(void);
void r7k_cache_mem_blocking_mode_disable(void);

extern struct callout_rtn cache_mipsl1d_r7k;
extern struct callout_rtn cache_mips_l3_r7k;

#endif /* ! __ASM__ */

#endif /* __CACHE_R7K_H__ */
