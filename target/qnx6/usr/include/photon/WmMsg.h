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
#ifndef __WM_MESSAGE_INCLUDED
#define __WM_MESSAGE_INCLUDED
/*****************************************************
	Window Manager Messages
	- some request information
	- some set information
 *****************************************************/

/* message types */
#define WM_REQUEST_FRAME_SIZE   	1
#define WM_REQUEST_MENU_DISPLAY 	2
#define WM_REQUEST_WIN_ACTION   	3
#define WM_REQUEST_CUR_WINDOW   	4
#define WM_REQUEST_FOCUS_LIST   	5
#define WM_REQUEST_WINDOW_CONFIG   	6
#define WM_REQUEST_CONSOLE 	  		7
#define WM_REQUEST_WIN_MENU_ENTRY	8
#define WM_SET_CONNECTION_EVENT_MASK	9
#define WM_REQUEST_SCREEN_RESERVE	10
#define WM_REQUEST_END_CONNECTION	11

/* message subtypes */
#define WM_REQUEST_SET		1
#define WM_REQUEST_GET		2
#define WM_REQUEST_CANCEL	3

#define Pt_ACTION_CLOSE                 1
#define Pt_ACTION_MAX                   2
#define Pt_ACTION_MIN                   3
#define Pt_ACTION_HELP                  4
#define Pt_ACTION_RET                   5
#define Pt_ACTION_MENU                  6
#define Pt_ACTION_MOVE                  7
#define Pt_ACTION_MOVE_COMPLETE 8
#define Pt_ACTION_MOVE_INIT             9
#define Pt_ACTION_COLLAPSE              10

/* request the display of a menu */
/* menu point locations */
#define MENU_POINT_UL 1
#define MENU_POINT_UR 2
#define MENU_POINT_LL 3
#define MENU_POINT_LR 4
typedef struct wm_menu_display_request
{
    int 		location;
    PhPoint_t 	pos;
} WmMenuDisplayRequest_t;

/* request the focus list for a window */
#define ALL_CONSOLES -1
typedef struct wm_focus_list_request
{
    int num;
} WmFocusListRequest_t;

/* request the shifting of a console */
typedef struct wm_console_request
{
	unsigned long 	flags;
	int				console;
} WmConsoleRequest_t;

/* request the addition of a window manager menu item */
typedef struct wm_menu_entry_request
{
	char text[128];
	int value;
	char accel_text[6];
	char hotkey[6];
} WmMenuEntryRequest_t;

/* request a reserved area of the screen */
#define WM_RESERVE_ALL	0
#define WM_RESERVE_LEFT	1
#define WM_RESERVE_RIGHT	2
#define WM_RESERVE_TOP	3
#define WM_RESERVE_BOT	4
typedef struct wm_screen_reserve
{
	int location;
	int	size;
	PhRect_t allsizes;
} WmScreenReserve_t;

/* window manager message header */
typedef struct wm_request_hdr
{
	int		type;
	int 	subtype;
    int 	input_group;
	PhRid_t	rid;
} WmMsgHeader_t;

typedef union wm_msg_union
{
	WmMenuDisplayRequest_t	menu;
	WmFocusListRequest_t	focus_list;
	WmConfig_t				config;
	WmConsoleRequest_t		console;
	WmMenuEntryRequest_t	entry;
	WmScreenReserve_t		reserve;
} WmMsgUnion_t;

typedef struct wm_request
{
	WmMsgHeader_t 	hdr;
	WmMsgUnion_t	data;
} WmMsg_t;

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/WmMsg.h $ $Rev: 224590 $" )
#endif
