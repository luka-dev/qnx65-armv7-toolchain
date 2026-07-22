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
 * cache_sr7100.h
 *
 * MIPS SR7100 cache control declarations.
 *
 *------------------------------------------------------------------
 */

#ifndef __CACHE_SR7100_H__
#define __CACHE_SR7100_H__

/*
#define COP(op,cache)   (((op)<<2)+(cache))
*/

#define MIPS_SR7100_TCACHE_ENABLE 0x10000000
#define MIPS_SR7100_SCACHE_ENABLE 0x00001000

#define MIPS_SR7100_TCACHE_FLASH_INVALIDATE 0x20000000
#define MIPS_SR7100_SCACHE_FLASH_INVALIDATE 0x00002000

#define MIPS_SR7100_TCACHE_SIZE_MASK 0x00F00000
#define MIPS_SR7100_TCACHE_SIZE_SHIFT 20

#ifndef __ASM__
void sr7100_inv_secondary_cache(void);
void sr7100_inv_tertiary_cache(void);
void sr7100_inv_secondary_cache_asm(void);
void sr7100_inv_tertiary_cache_asm(unsigned int size);
void sr7100_enable_secondary_cache(void);
void sr7100_enable_tertiary_cache(void);
unsigned int sr7100_level2_cache_detect (void);
unsigned int sr7100_level3_cache_detect (void);
#endif /* ! __ASM__ */

#endif /* __CACHE_SR7100_H__ */
