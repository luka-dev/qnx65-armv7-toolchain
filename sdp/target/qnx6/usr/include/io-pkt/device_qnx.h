/*
 * $QNXtpLicenseC:
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

#ifndef _DEVICE_QNX_H_INCLUDED
#define _DEVICE_QNX_H_INCLUDED

struct cfattach;
struct device;

int dev_attach(char *, char *, struct cfattach *, void *, int *,
    struct device **, int (*print)(void *, const char *));
int dev_detach(struct device *, int);
int dev_detach_name(const char *, int);
void dev_remove(struct device *);

#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/io-pkt/sys/device_qnx.h $ $Rev: 241309 $" )
#endif
