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
 * PhWm.h	
 *		Contains all structures and manifests for window manager
 *		interactions.
 *

 */
#ifndef __PH_WM_H_INCLUDED
#define __PH_WM_H_INCLUDED

#include <photon/PhMsg.h>

#ifdef __cplusplus
extern "C" {
#endif

/* event subtypes */
#define	Ph_EV_WM_OPEN		_Ph_REGION_OPEN
#define Ph_EV_WM_SET		_Ph_REGION_SET
#define Ph_EV_WM_CLOSE		_Ph_REGION_CLOSE
#define	Ph_EV_WM_EVENT		(_Ph_REGION_WM_BASE+0)
#define	Ph_EV_WM_VISIBLE	(_Ph_REGION_WM_BASE+1)
#define Ph_EV_WM_TRANSPORT	(_Ph_REGION_WM_BASE+2)
#define Ph_EV_WM_CONFIG		(_Ph_REGION_WM_BASE+3)
#define Ph_EV_WM_TASKEVENT	(_Ph_REGION_WM_BASE+4)
#define Ph_EV_WM_CONSWITCH	(_Ph_REGION_WM_BASE+5)
#define Ph_EV_WM_MENUREAD	(_Ph_REGION_WM_BASE+6)

#define	_Ph_WINDOW_OPEN			Ph_EV_WM_OPEN
#define _Ph_WINDOW_SET			Ph_EV_WM_SET
#define _Ph_WINDOW_CLOSE		Ph_EV_WM_CLOSE
#define	_Ph_WINDOW_EVENT		Ph_EV_WM_EVENT
#define _Ph_WINDOW_VISIBLE		Ph_EV_WM_VISIBLE
#define _Ph_WINDOW_CONFIG		Ph_EV_WM_CONFIG
#define _Ph_WINDOW_TASKEVENT	Ph_EV_WM_TASKEVENT
#define _Ph_WINDOW_CONSWITCH    Ph_EV_WM_CONSWITCH
#define _Ph_WINDOW_MENUREAD		Ph_EV_WM_MENUREAD

/* _Ph_REGION subtype _Ph_WINDOW_VISIBLE */
struct _Ph_msg_query_visible {
	struct _Ph_msg_hdr	hdr;
	unsigned short		flags;
	unsigned short		input_group;
	PhRid_t				rid;
};

struct _Ph_msg_query_visible_reply {
	struct _Ph_msg_hdr_reply	hdr;
	PhRect_t					rect;
};

/* _Ph_REGION subtype _Ph_WINDOW_EVENT */
typedef struct _Ph_window_event {
	ulong_t				event_f;		/* same manifests as managed and notify */
	ulong_t				state_f;		/* current window state */
	PhRid_t				rid;			/* target of event */
	PhPoint_t			pos;
	PhDim_t				size;
	ushort_t			event_state;
	ushort_t			input_group;
	ulong_t				rsvd[4];
} PhWindowEvent_t;

/* _Ph_WINDOW_CONSWITCH	message */
#define WM_CONSWITCH_CONSOLE	0
#define WM_CONSWITCH_BACK		1
#define WM_CONSWITCH_FWD		2
#define WM_CONSWITCH_RID		3
typedef struct {
	short	action;
	short	value;
} PhWindowConsoleEvent_t;

#define Ph_WM_EVSTATE_PERFORM			0
#define Ph_WM_EVSTATE_INVERSE			1
#define Ph_WM_EVSTATE_HIDE				0
#define Ph_WM_EVSTATE_UNHIDE			1
#define Ph_WM_EVSTATE_ICONIFY			0
#define Ph_WM_EVSTATE_DEICONIFY			1
#define Ph_WM_EVSTATE_FOCUS				0
#define Ph_WM_EVSTATE_FOCUSLOST			1
#define Ph_WM_EVSTATE_FFRONT			0
#define Ph_WM_EVSTATE_FFRONT_DISABLE	1
#define Ph_WM_EVSTATE_MENU				0
#define Ph_WM_EVSTATE_MENU_FINISH		1
#define Ph_WM_EVSTATE_FORCE				0x2

typedef struct _Ph_window_info {
	PhRegionDataHdr_t	rhdr;
	ulong_t				fields;
	ulong_t				managed_f;		/* WM preforms action */
	ulong_t				notify_f;		/* App is informed about action */
	ulong_t				state_f;		/* current/initial window state */
	ulong_t				render_f;		/* how window looks */
	PhPoint_t			icon_size;
	PhPoint_t			icon_pos;
	PhRid_t				link;			/* icon link to parent */
	PhRid_t				parent_rid;		/* link to parent region */
	char				title[64];
	char				title_font[Ph_MAX_FONT_LEN];
	char				icon_title[32];
	PhDim_t				dim_min;
	PhDim_t				dim_max;
	PgColor_t			frame_active_color;
	PgColor_t			frame_inactive_color;
	unsigned short		child_count;
	long				win_in_front;
	PgColor_t			title_color;
	short				version;
	short				ig_maxed_on;
	PgColor_t			inline_color;
} PhWindowInfo_t;

#define WM_VERSION		7
typedef struct {
	char				drag;
	char				focus_cursor;
	char				click_front;
	char				keyboard;
	char				auto_raise;
	char				text_align;
	PgColor_t			base_color;
	char				task_bar;
	char				task_bar_front;
	unsigned short		placement;
	char				border_active;
	char				task_bar_rows;
	char				task_bar_hide;
	PgColor_t			active_color;
	PgColor_t			inactive_color;
	PgColor_t			title_color;
	PgColor_t			cursor_color;
	unsigned short		cursor_type;
	unsigned short		spare2;
	int titlebar_height;
	PhRect_t borders;
} WmConfig_t;

#define	Ph_WM_SET_FLAGS				0x0001		
	/* set managed_f and notify_f */
	
#define	Ph_WM_SET_STATE				0x0002		
	/* set state_f */
	
#define	Ph_WM_SET_RENDER			0x0004
	/* set render_f */
	
#define	Ph_WM_SET_TITLE				0x0008		
	/* title_offset indicates offset from start of PhWindowInfo_t structure in message 
	 * if title_font_offset is not 0, set use this font for the title */
	
#define	Ph_WM_SET_ICON_TITLE		0x0010
	/* icon_title_offset points to icon title, otherwise title_offset will title icon */
	
#define	Ph_WM_SET_ICON_SIZE			0x0020
	/* icon_size overrides default WM's icon size */
	
#define	Ph_WM_SET_ICON_POS			0x0040
	/* icon_pos overrides WM's icon placement */
	
#define	Ph_WM_SET_LINK				0x0080
	/* un-minify and restore focus to LINK window when this window is closed */

#define Ph_WM_SET_RELATION			0x0100
	/* parent region id */

#define Ph_WM_SET_CHILD_COUNT		0x0200
	/* number of children */

#define Ph_WM_SET_FRAME_ATTRIB		0x0400
	/* set frame attributes */

#define Ph_WM_SET_FRONT_WINDOW		0x0800
	/* set window position in hierarchy */

#define	Ph_WM_SET_CONVERSE_LINK		0x8000
	/* this will cause the window that this window is linked to, to be linked back 
	 * no data is associated with the flag */
	

/* STATE Flags */

#define	Ph_WM_STATE_ISMASK			0x0000FFFF
#define Ph_WM_STATE_ISNORMAL		0x00000000  /* window is normal (takes the long bus) */
#define	Ph_WM_STATE_ISHIDDEN		0x00000001	/* window is hidden (minimised) */
#define	Ph_WM_STATE_ISMAX			0x00000002	/* window is maximized */
#define	Ph_WM_STATE_ISBACKDROP		0x00000004	/* window is a backdrop  */
#define	Ph_WM_STATE_ISBLOCKED		0x00000008	/* window is blocked */
#define	Ph_WM_STATE_ISTASKBAR		0x00000010	/* reserved for pwm */
#define	Ph_WM_STATE_ISPDM			0x00000020	/* reserved for pwm/pdm */
#define	Ph_WM_STATE_ISICONIFIED		0x00000040	/* window is iconified (same as hidden now) */
#define	Ph_WM_STATE_ISICON			0x00000080	/* window is an icon (deprecated) */
#define	Ph_WM_STATE_ISFRONT			0x00000100	/* window is front most in family */
#define Ph_WM_STATE_ISALTKEY		0x00000200  /* window wants the ALT-Fx keys */
#define Ph_WM_STATE_ISREMOTE		0x00000400	/* window is on remote GUI */
#define Ph_WM_STATE_ISCOLLAPSE		0x00000800  /* window is Collapsed */
#define	Ph_WM_STATE_ISFOCUS			0x00008000	/* window has focus */
#define Ph_WM_STATE_ISMAXING		0x00004000  /* window is MAXING (internal PtWindow) */

/* RENDER Flags */

#define	Ph_WM_RENDER_ASMASK			0x0000000F
#define	Ph_WM_RENDER_ASAPP			0x00000000	/* standard window */
#define	Ph_WM_RENDER_ASICON			0x00000001	/* icon style window */
#define	Ph_WM_RENDER_ASDIALOG		0x00000002	/* dialog style window */
#define	Ph_WM_RENDER_ASPALETTE		0x00000004	/* palette style window */

#define	Ph_WM_RENDER_BORDER			0x00000010		
	/* draw frame around window */
#define	Ph_WM_RENDER_RESIZE			0x00000020
	/* if RENDER_RESIZE, draw resize handles in frame */
#define	Ph_WM_RENDER_MOVE			0x00000040
	/* internal use by WindowFrame, allows moves */
#define	Ph_WM_RENDER_TITLE			0x00000080
	/* if RENDER_TITLE, draw title bar in frame */
#define	Ph_WM_RENDER_MENU			0x00000100
	/* if RENDER_MENU, add menu button to left of title */
#define	Ph_WM_RENDER_CLOSE			0x00000200
	/* if RENDER_CLOSE, add close button to right of title */
#define	Ph_WM_RENDER_HELP			0x00000400
	/* if RENDER_HELP, add help button to right of title */
#define	Ph_WM_RENDER_MIN			0x00001000
	/* if RENDER_MIN, add min button to right of title */
#define	Ph_WM_RENDER_MAX			0x00002000
	/* if RENDER_COLLAPSE, add collapse button to right of title */
#define Ph_WM_RENDER_COLLAPSE		0x00004000
	/* if RENDER_MAX, add max button to right of title */
#define Ph_WM_RENDER_RETURN			0x00008000
	/* if RENDER_INLINE, add a black border just inside standard borders */
#define Ph_WM_RENDER_INLINE			0x00010000

/* MANAGED and NOTIFY Flags */

#define	Ph_WM_CLOSE					0x00000001	
	/* managed_f		N/A */
	/* notify_f			WM triggers WINDOW CLOSE to app */
	
#define	Ph_WM_TERMINATE				0x00000002
	/* notify_f			triggers TERMINATE window event */
	/* managed_f		WM won't terminate until app responds to TERMINATE event */
	
#define	Ph_WM_FOCUS					0x00000004
	/* managed_f		WM grants or steals focus */
	/* notify_f			trigger FOCUS window event */
	
#define	Ph_WM_MENU					0x00000008
	/* managed_f		WM builds and controls window menu */
	/* notify_f			trigger MENU window event */
	
#define	Ph_WM_TOFRONT				0x00000010
	/* managed_f		WM moves app to the front */
	/* notify_f			triggers TOFRONT window event */
	
#define	Ph_WM_TOBACK				0x00000020
	/* managed_f		WM moves app th the back */
	/* notify_f			triggers TOBACK window event */

#define	Ph_WM_HIDE					0x00000040
	/* managed_f		WM hides the app */
	/* notify_f			triggers HIDE window event */
	
#define	Ph_WM_CONSWITCH				0x00000080
	/* managed_f		WM moves app to new screen */
	/* notify_f			triggers CONSWITCH window event */

#define	Ph_WM_RESIZE				0x00000100
	/* managed_f		WM resizes app */
	/* notify_f			trigger RESIZE window event */
	
#define	Ph_WM_MOVE					0x00000200
	/* managed_f		WM moves app */
	/* notify_f			trigger MOVE window event */
	
#define	Ph_WM_ICON					0x00000400
	/* managed_f		WM hides application */
	/* notify_f			trigger ICON window event */

#define	Ph_WM_MAX					0x00000800
	/* managed_f		WM resizes app */
	/* notify_f			triggers MAX window event */
	
#define	Ph_WM_BACKDROP				0x00001000
	/* managed_f		WM resizes app */
	/* notify_f			triggers BACKDROP window event */
	
#define	Ph_WM_TASKBAR				0x00004000
	
#define	Ph_WM_RESTORE				0x00008000
	/* managed_f		WM resizes app */
	/* notify_f			handled as a  unICON, unMAX or unBACKDROP window event */

#define	Ph_WM_HELP					0x00002000
	/* managed_f		N/A */
	/* notify_f			triggers HELP window event */

#define	Ph_WM_FFRONT				0x00010000
	/* managed_f		WM makes window force front/not force front */
	/* notify_f			N/A */

#define	Ph_WM_NO_FOCUS_LIST			0x00020000
	/* managed_f		this window will not be in the focus list */
	/* notify_f			N/A */

#define	Ph_WM_COLLAPSE				0x00040000

#define Ph_WM_SUPERSELECT			~0
	/* {conswitch, tofront, focus} as required */

#define Ph_WM_USER_BUTTON			0x0002000
	/* managed			will invoke window frame action indicated by button. */
	/* notify			triggers user button window event */

#define Ph_WM_ALL_FLAGS				0x00007F3D

#define	Ph_WM_APP_DEF_MANAGED	( Ph_WM_CLOSE | Ph_WM_FOCUS | Ph_WM_MENU | Ph_WM_TOFRONT | Ph_WM_TOBACK | 		\
									Ph_WM_RESIZE | Ph_WM_MOVE | Ph_WM_HIDE | Ph_WM_MAX | Ph_WM_RESTORE  | Ph_WM_TASKBAR | Ph_WM_COLLAPSE)
#define	Ph_WM_APP_DEF_NOTIFY	( 0 )
#define	Ph_WM_APP_DEF_RENDER	( Ph_WM_RENDER_ASAPP | Ph_WM_RENDER_BORDER | \
									Ph_WM_RENDER_RESIZE | Ph_WM_RENDER_MOVE | Ph_WM_RENDER_CLOSE | \
									Ph_WM_RENDER_TITLE | Ph_WM_RENDER_MENU | \
									Ph_WM_RENDER_MIN | Ph_WM_RENDER_MAX | Ph_WM_RENDER_COLLAPSE)
									
#define	Ph_WM_ICON_DEF_MANAGED	( Ph_WM_CLOSE | Ph_WM_FOCUS | Ph_WM_MENU | Ph_WM_TOFRONT | Ph_WM_TOBACK | Ph_WM_MOVE | Ph_WM_ICON | Ph_WM_RESTORE )
#define	Ph_WM_ICON_DEF_NOTIFY	( 0 )
#define	Ph_WM_ICON_DEF_RENDER	( Ph_WM_RENDER_ASICON | Ph_WM_RENDER_BORDER )


/* connection stuff */
#define WM_CONNECTION_NAME "pwm"

#define Ph_WM_REQUEST_FRAME_SIZE 1

typedef struct ph_wm_frame_size_request
{
    PhRid_t rid;
} PhWMFrameSizeRequest_t;

typedef struct ph_wm_frame_size_reply
{
    int status;
    PhRect_t        borders;
} PhWMFrameSizeReply_t;


#ifdef __cplusplus
};
#endif

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PhWm.h $ $Rev: 219996 $" )
#endif
