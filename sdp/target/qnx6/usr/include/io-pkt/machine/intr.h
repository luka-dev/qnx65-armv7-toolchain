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





#ifndef _MACHINE_INTR_H_
#define _MACHINE_INTR_H_

#define splimp()            0
#define splx(s)             ((s) = (s))
#define splraise(s)         ((void)0)
#define spllower(s)         ((void)0)
#define setsoftnet()        ((void)0)
#define spl0()              0
#define splbio()            0
#define splclock()          0
#define splhigh()           0
#define splimp()            0
#define splnet()            0
#define splsoftclock()      0
#define splsofttty()        0
#define splstatclock()      0
#define spltty()            0
#define splvm()             0
#define spllowersoftclock() 0
#define splsoftnet()        0
#define splsoftserial()     0
#define splsched()          0

#define IPL_NET 5

#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/io-pkt/sys/machine/intr.h $ $Rev: 241309 $" )
#endif
