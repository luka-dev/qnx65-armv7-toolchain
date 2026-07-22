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
 *  ds.h:   Data Server Functions 
 *

 */

#ifndef _DS_H_INCLUDED
#define _DS_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef _SIGNAL_H_INCLUDED
#include <signal.h>
#endif

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

__BEGIN_DECLS

#define DS_PERM 1

typedef int ds_t;

int ds_register(void);
int ds_deregister(ds_t dsdes);
int ds_create(ds_t dsdes, const char *variable_name, char flags, struct sigevent *sigevent);
int ds_clear(ds_t dsdes, const char *variable_name);
int ds_set(ds_t dsdes, const char *variable_name, const char *variable_data, size_t data_len);
int ds_get(ds_t dsdes, const char *variable_name, const char *variable_data, size_t data_len); 
int ds_flags(ds_t dsdes, const char *variable_name, char flags);

__END_DECLS

#endif


__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/socket/public/ds.h $ $Rev: 233581 $" )
