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





#ifndef _HA_COVER_H_INCLUDED
#define _HA_COVER_H_INCLUDED

#ifndef _STDIO_H_INCLUDED
#include <stdio.h>
#endif

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef _HA_TYPES_INCLUDED
#include <ha/types.h>
#endif

#ifndef _HA_STDIO_H_INCLUDED
#include <ha/stdio.h>
#endif

#ifndef _HA_FCNTL_H_INCLUDED
#include <ha/fcntl.h>
#endif

#ifndef _HA_UNISTD_H_INCLUDED
#include <ha/unistd.h>
#endif

#ifndef _HA_NEUTRINO_H_INCLUDED
#include <ha/neutrino.h>
#endif

__BEGIN_DECLS

int ha_attach(int __coid, RFp __rfn, void *__rhdl, unsigned __flags);
int ha_detach(int __coid);
int ha_connection_ctrl(int __coid, int __command, void *__args);

__END_DECLS

#endif


__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ha/public/ha/cover.h $ $Rev: 219996 $" )
