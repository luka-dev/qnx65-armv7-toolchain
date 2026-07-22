/* Copyright 2009, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to 
 * QNX Software Systems before you may reproduce, modify or distribute this 
 * software, or any work that includes all or part of this software.  Free 
 * development licenses are available for evaluation and non-commercial purposes.  
 * For more information visit http://licensing.qnx.com or email licensing@qnx.com.
 * 
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 */
#ifndef _GF_GF_ERRNO_H_INCLUDED
#define _GF_GF_ERRNO_H_INCLUDED

#define GF_ERR_OK			0x00000000	/* no error */
#define GF_ERR_MEM			0x00000001	/* memory allocation error */
#define GF_ERR_IODISPLAY	0x00000002	/* error accessing io-display */
#define GF_ERR_DEVICE		0x00000003	/* error accessing device */
#define GF_ERR_SHMEM		0x00000004	/* error accessing shared memory */
#define GF_ERR_DLL			0x00000005	/* error accessing dll/entrypoints */
#define GF_ERR_THREAD		0x00000006	/* thread registration failure */
#define GF_ERR_PARM			0x00000007	/* invalid parameter */
#define GF_ERR_INUSE		0x00000008	/* resource in use */
#define GF_ERR_NOSUPPORT	0x00000009	/* unsupported operation */
#define GF_ERR_CFG			0x0000000a	/* bad configuration */
#define GF_ERR_NOLOCK		0x0000000b	/* h/w not locked */
#define GF_ERR_IO			0x0000000c	/* h/w level I/O error */
#define GF_ERR_DEADLOCK		0x0000000d	/* h/w locked; deadlock avoided */
#define GF_ERR_SURFDESTROYED	0x0000000e	/* target surface destroyed, due to modeswitch or power management */
#define GF_ERR_TOOBIG		0x0000000f	/* Requested operation exceeded internal limits */

#ifdef __QNXNTO__
#include<sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/gf/public/gf/gf_errno.h $ $Rev: 244324 $" )
#endif
#endif
