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
 *  keyboard.h
 *

 */

#ifndef _SYS_KEYBOARD_H_INCLUDED
#define _SYS_KEYBOARD_H_INCLUDED

#ifndef _SYS_INTERACT_H_INCLUDED
#include <photon/interact.h>
#endif

#ifndef _TIME_H_INCLUDED
 #include <time.h>
#endif

#ifndef __KEYCODES_H_INCLUDED
#include <photon/keycodes.h>
#endif

#include <photon/PhPack.h>

struct _keyboard_data {
    unsigned long           modifiers;
    unsigned long           flags;
    unsigned long           key_cap;
    unsigned long           key_sym;
    unsigned long           key_scan;
};

struct _keyboard_packet {                   /* start of struct returned from read() */
    struct timespec         time;
    struct _keyboard_data   data;
};

#define _KEYBOARD_MODE_SCAN      0x0000     /* single byte scancodes are returned */
#define _KEYBOARD_MODE_PACKET    0x0001     /* _keyboard_packets are returned */
#define _KEYBOARD_MODE_UNICODE	 0x0002		/* unicode (16 bit quantities) are returned */
#define _KEYBOARD_MODE_MASK      0x0003
#define _KEYBOARD_MODE_SCREEN	 0x1000		/* display screen keyboard */

struct _keyboard_ctrl {
    struct _interact_device type;           /* Device type */
    unsigned long           flags;          /* Device type flags */
    unsigned long           mode;           /* Mode of currently read packets */
	unsigned short			rate;
	unsigned short			delay;
	unsigned long			zero[9];
};

#include <photon/PhPackPop.h>

#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/keyboard.h $ $Rev: 219996 $" )
