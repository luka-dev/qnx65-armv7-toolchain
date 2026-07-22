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

#ifndef _QUIESCE_H_INCLUDED
#define _QUIESCE_H_INCLUDED

#include <nw_datastruct.h>

int  quiesce_init(void);
void quiesce_fini(void);

void quiesce_all(void);
void quiesce_all_arg(int, int);
void unquiesce_all(void);
int  quiesce_force_exit(int, struct nw_work_thread **);


void quiesce_block(int);

#endif /* !_QUIESCE_H_INCLUDED */

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/io-pkt/sys/quiesce.h $ $Rev: 233581 $" )
