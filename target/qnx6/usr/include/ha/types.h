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





#ifndef _HA_TYPES_H_INCLUDED
#define _HA_TYPES_H_INCLUDED

#ifndef _STDIO_H_INCLUDED
#include <stdio.h>
#endif

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#define HAREPLACERECOVERYFN 0x0001

#define HA_RECOVERY_ACOUNT          0x0001
#define HA_RECOVERY_ICOUNT          0x0002
#define HA_RECOVERY_SUSPEND         0x0003
#define HA_RECOVERY_ENABLE          0x0004
#define HA_RECOVERY_RESET_ICOUNT    0x0005
#define HA_RECOVERY_RESET_ACOUNT    0x0006

__BEGIN_DECLS

typedef int (*RFp)(int, void *);

__END_DECLS

#endif


__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ha/public/ha/types.h $ $Rev: 219996 $" )
