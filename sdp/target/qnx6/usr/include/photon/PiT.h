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
 * 	PiT.h	
 *		Manifests and structure definitions for the Photon imaging lib
 *

 */

#ifndef __PI_T_H_INCLUDED
#define __PI_T_H_INCLUDED

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

#define Pi_FREE			0x1		/* Free old image */
#define Pi_CALC_PALETTE	0x2		/* Calculate optimum palette if quantizing */
#define Pi_DITHER		0x4		/* Dither image if quantizing */
#define Pi_SHMEM		0x8		/* Use shared memory for new image data */
#define Pi_USE_COLORS	0x10	/* Use current color settings */
#define Pi_CHECK_BOUNDS	0x20	/* Check boundaries of supplied rect and adjust as necessary */
#define Pi_HORIZONTAL	0x40	/* Horizontal orientation */
#define Pi_VERTICAL		0x80	/* Vertical orientation */
#define Pi_SUPPRESS_CRC	0x100	/* do not calculate CRC tags */
#ifdef __cplusplus
};
#endif


#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PiT.h $ $Rev: 219996 $" )
#endif
