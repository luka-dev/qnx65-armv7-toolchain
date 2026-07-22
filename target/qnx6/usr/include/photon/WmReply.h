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
#ifndef __WM_REPLY_INCLUDED
#define __WM_REPLY_INCLUDED

/****************************************************
 	Window Manager Reply Structures

 ****************************************************/

/* frame size message reply */
typedef struct wm_frame_size_reply
{
	PhRect_t borders;
} WmFrameSizeReply_t;

/* current window message reply */
typedef struct wm_window_definition
{
    PhRid_t         rid;
    PhWindowInfo_t  info;
} WmWindowDefinition_t;

/* focus list message reply */
typedef struct wm_focus_list_reply
{
	int 						max;
	int							num;
	WmWindowDefinition_t		items[1];
} WmFocusListReply_t;

/* reply header */
typedef struct wm_reply_hdr
{
	int	status;
} WmReplyHeader_t;

typedef struct wm_screen_reserve_reply
{
    PhRect_t    rect;
} WmScreenReserveReply_t;

typedef union wm_reply_union
{
	WmFrameSizeReply_t		frame;
	WmWindowDefinition_t	cur_win;
	WmFocusListReply_t		focus_list;
	WmConfig_t				config;
	int						console;
	WmScreenReserveReply_t	reserve;
} WmReplyUnion_t;

typedef struct wm_reply
{
	WmReplyHeader_t hdr;
	WmReplyUnion_t	data;
} WmReply_t;

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/WmReply.h $ $Rev: 224590 $" )
#endif
