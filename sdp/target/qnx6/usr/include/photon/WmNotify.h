/* Copyright 2009, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to 
 * QNX Software Systems before you may reproduce, modify or distribute this 
 * software, or any work that includes all or part of this software.  Free 
 * development licenses are available for evaluation and non-commercial purposes.  
 * For more information visit http://licensing.qnx.com or email licensing@qnx.com.
 * 
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 */
#ifndef __WM_NOTIFY_INCLUDED
#define __WM_NOTIFY_INCLUDED

#define WM_CONNECTION_NAME 	"pwm"

/* window manager event notification types */
#define WM_NOTIFY_WIN_FOCUS_CHANGE  0x1
#define WM_NOTIFY_WIN_MINIMIZE      0x2
#define WM_NOTIFY_WIN_MAXIMIZE      0x4
#define WM_NOTIFY_WIN_RESTORE      	0x8
#define WM_NOTIFY_WIN_SIZE      	0x10
#define WM_NOTIFY_WIN_MOVE      	0x20
#define WM_NOTIFY_WIN_CLOSE         0x40
#define WM_NOTIFY_WIN_CREATE        0x80
#define WM_NOTIFY_CONSWITCH			0x100
#define WM_NOTIFY_WIN_BACKDROP		0x200
#define WM_NOTIFY_WIN_MENU			0x400
#define WM_NOTIFY_WIN_TOFRONT		0x800
#define WM_NOTIFY_WIN_TOBACK		0x1000
#define WM_NOTIFY_WIN_ICON			0x2000
#define WM_NOTIFY_WIN_HELP			0x4000
#define WM_NOTIFY_MENU_ITEM			0x8000
#define WM_NOTIFY_WIN_FFRONT		0x10000
#define WM_NOTIFY_WIN_INFO_CHANGE	0x20000
#define WM_NOTIFY_CONSOLE_SIZE		0x40000
#define WM_NOTIFY_SCREEN_RESERVE	0x80000
#define WM_NOTIFY_WIN_COLLAPSE		0x100000

/* states for focus change events */
#define FOCUS_GIVE  1
#define FOCUS_LOSE  2

typedef union
{
	PhWindowEvent_t	wevent;
	PhWindowInfo_t	info;
} WmNotifyUnion_t;

/* event notification structure */
typedef struct wm_notify
{
    int     		type;	/* type of event */
    PhRid_t 		rid;	/* rid of window being changed */
    int     		state;	/* state if applicable to event */
    WmNotifyUnion_t	data;
} WmNotify_t;

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/WmNotify.h $ $Rev: 224590 $" )
#endif
