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





#ifndef _HA_FCNTL_H_INCLUDED
#define _HA_FCNTL_H_INCLUDED

#ifndef _STDIO_H_INCLUDED
#include <stdio.h>
#endif

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

#ifndef __STAT_H_INCLUDED
#include <sys/stat.h>
#endif

#ifndef _FCNTL_H_INCLUDED
#include <fcntl.h>
#endif

#ifndef _HA_TYPES_INCLUDED
#include <ha/types.h>
#endif

__BEGIN_DECLS

int ha_open(__const char *__path, int __oflag, RFp __rfn, void *__rhdl, 
            unsigned __haflags, ...);
int ha_open64(__const char *__path, int __oflag, RFp __rfn, void *__rhdl, 
            unsigned __haflags, ...);
int ha_reopen(int oldfd, __const char *__path, int __oflag, ...);
int ha_creat(__const char *__path, mode_t __mode, RFp __rfn, void *__rhdl, 
             unsigned __haflags);
int ha_creat64(__const char *__path, mode_t __mode, RFp __rfn, void *__rhdl, 
               unsigned __haflags);

__END_DECLS

#endif


__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ha/public/ha/fcntl.h $ $Rev: 219996 $" )
