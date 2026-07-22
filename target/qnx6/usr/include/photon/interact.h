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
 *  interact.h
 *

 */

#ifndef _SYS_INTERACT_H_INCLUDED
#define _SYS_INTERACT_H_INCLUDED

#include <photon/PhPack.h>

#define _INTERACT_TYPE_POINTER       0x0000          /* pointer packet */
#define _INTERACT_TYPE_KEY           0x0001          /* keyboard packet */
#define _INTERACT_TYPE_FEEDBACK      0x0001          /* keyboard packet */

struct _interact_device {
    unsigned short          type;
    unsigned short          reserved;
};

#define _INTERACT_FEEDBACK_LED       0x00000001      /* LED displays */
#define _INTERACT_FEEDBACK_BELL      0x00000002      /* Freq, vol, dur */
#define _INTERACT_FEEDBACK_INTEGER   0x00000004      /* Integer display */
#define _INTERACT_FEEDBACK_STRING    0x00000008      /* string display */

#include <photon/PhPackPop.h>

#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/interact.h $ $Rev: 219996 $" )
