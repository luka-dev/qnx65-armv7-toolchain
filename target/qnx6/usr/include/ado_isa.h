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
 *      ado_isa.c
 *	    - Manifests for audio isa bus access.
 */

#ifndef _ADO_ISA_H_INCLUDED_
#define _ADO_ISA_H_INCLUDED_

#if defined(__X86__)

/***** defines *******/
#define ISADMA_MODE_READ		0x44
#define ISADMA_MODE_WRITE		0x48
#define ISADMA_MODE_AUTOINIT	0x10

/***** type definitions ***********/
typedef struct ado_isadma ado_isadma_t;

/***** structures ***********/
struct ado_isadma {
	uint32_t channel;
	uint32_t mode;
	ado_pcm_dmabuf_t *buf;
	uint32_t	spare[8];
};


/*** function prototypes ****/
void ado_isadma_configure (ado_isadma_t *isadma);
void ado_isadma_release (ado_isadma_t *isadma);
uint32_t ado_isadma_remainder (ado_isadma_t *isadma);

#endif /* __X86__ */
#endif /* _ADO_ISA_H_INCLUDED_ */

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/services/audio/public/include/ado_isa.h $ $Rev: 219613 $" )
