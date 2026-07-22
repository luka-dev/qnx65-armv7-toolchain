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





#ifndef _MACHINE_PARAM_H_
#define _MACHINE_PARAM_H_

#include <machine/cpu.h>

#define DELAY(_x) (((_x) >= 1000) ? (delay)(((_x) / 1000) + 1) : nanospin_ns((_x) * 1000L))

#define NMBCLUSTERS 8192  // was 1024

#ifndef __QNXNTO__
#ifndef MCLSHIFT
#define MCLSHIFT	11
#endif

#define MCLBYTES	(1 << MCLSHIFT)
#else
#define MCLSHIFT_NTOMIN	11
/* We make these variable where MCLSHIFT_NTOMIN is the minimum */
#define MCLSHIFT	(mclshift)
#define MCLBYTES	(mclbytes)
#endif

#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/io-pkt/sys/machine/param.h $ $Rev: 233581 $" )
