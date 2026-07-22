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
 *      ado_memory.c
 *	    - Manifests to assist in the debugging of the ado drivers.
 */

#ifndef _ADO_MEMORY_H_INCLUDED_
#define _ADO_MEMORY_H_INCLUDED_


#define	ADO_BUF_DMA_SAFE			(1<<0)
#define	ADO_BUF_DMA_ISA				(1<<1)
#define	ADO_BUF_DMA_16M				(1<<2)
#define	ADO_BUF_CACHE				(1<<20)	/* DO cache the buffer */
#define	ADO_BUF_CACHE_NOPS			(1<<21)	/* DON'T Flush OR Invalidate the buffer cache */

#define	ADO_SHM_DMA_SAFE			ADO_BUF_DMA_SAFE
#define	ADO_SHM_DMA_ISA				ADO_BUF_DMA_ISA
#define	ADO_SHM_DMA_16M				ADO_BUF_DMA_16M


#ifdef ADO_DEBUG

#define		ado_malloc(s)		ado_malloc_debug(s, __FILE__, __LINE__)
#define		ado_calloc(n,s)		ado_calloc_debug(n, s, __FILE__, __LINE__)				
#define		ado_realloc(p,s)	ado_realloc_debug(p, s, __FILE__, __LINE__)	
#define		ado_strdup(s)		ado_strdup_debug(s, __FILE__, __LINE__)		
#define		ado_free(p)			ado_free_debug(p, __FILE__, __LINE__)			

#else

#define		ado_malloc			malloc
#define		ado_calloc			calloc
#define		ado_realloc			realloc
#define		ado_strdup			strdup
#define		ado_free			free

#endif


struct ado_pcm_config;


/*** function prototypes ****/

/* memory.c */
void ado_memory_dump ( void );
void *ado_malloc_debug ( size_t size , const char *filename , int line );
void *ado_calloc_debug ( size_t n , size_t size , const char *filename , int line );
void *ado_realloc_debug ( void *ptr , size_t size , const char *filename , int line );
char *ado_strdup_debug ( const char *src , const char *filename , int line );
void ado_free_debug ( void *ptr , const char *filename , int line );
void ado_memory_dump ( void );
void *ado_device_mmap ( unsigned long addr , unsigned long size );
int ado_device_munmap ( void *addr , unsigned long size );
void *ado_pcm_buf_alloc ( struct ado_pcm_config *config , size_t size , uint32_t flags );
void *ado_pcm_buf_map ( struct ado_pcm_config *config , off64_t phys_addr , size_t size , uint32_t flags );
void ado_pcm_buf_free ( struct ado_pcm_config *config );
int ado_dma_pool_shmem_map ( char *name );
int ado_dma_pool_create ( size_t size );
int ado_dma_pool_info (size_t *size, size_t *free, int *chunks, int nchunks);
int ado_dma_pool_unmap ( char *name );
void *ado_shm_alloc ( size_t size , char *name , uint32_t flags , off64_t *phys_addr );
void *ado_shm_map ( off64_t phys_addr , size_t size , char *name , uint32_t flags );
void ado_shm_free ( void *ptr , size_t size , char *name );

#endif /* _ADO_MEMORY_H_INCLUDED_ */

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/services/audio/public/include/ado_memory.h $ $Rev: 219613 $" )
