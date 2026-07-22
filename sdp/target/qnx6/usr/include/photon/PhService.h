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
/* it's a drag!
 * Application --> service event --> Service Provider(s)
 * Application(s) <-- info event <-- Service Provider 
 *	( info events are direct to the applications rid if in response to 
 *	a service message (request) )
 */
#ifndef _PHSERVICE_H_
#define _PHSERVICE_H_

#ifndef __QNXNTO__
#ifndef _SYS_INTERACT_H_INCLUDED
#include <sys/interact.h>
#endif

/*
 * We don't want inclusion of the following two include files to be attempted
 * on Windows.
 */
#define _DEVCTL_H_INCLUDED
#define __DCMD_MISC_H_INCLUDED

#endif

#ifndef _DCMD_INPUT_H_INCLUDED
 #include <sys/dcmd_input.h>
#endif

#include <limits.h>

#include <photon/PhPack.h>

/* info/service subtypes */
/* see PhT.h */

/* remote window manager event subtypes */
#define REMOTE_WM_WINDOW		1
#define REMOTE_WM_TITLE			2

/* remote window manager flags */
#define REMOTE_FLAG_FIXED		0x0001
#define REMOTE_FLAG_INITIAL		0x0002
#define REMOTE_FLAG_IS_ORIGIN	0x0004
#define REMOTE_FLAG_NO_DIM		0x0008

typedef struct remote_wm_event {
	short			type;
	short			len;
	union remote_wm_info {
		struct remote_wm_window {
			ushort_t		xpos;
			ushort_t		ypos;
			ushort_t		height;
			ushort_t		width;
			short			flags;
			} window;
		struct remote_wm_title {
			char			text[64];
			} title;
		} info;
	} PhRemoteWMEvent_t;

#define DEV_CTRL_TYPE_MASK			0x000000ff
#define DEV_CTRL_LAYER_MASK			0xf0000000
#define DEV_CTRL_SWITCH_MASK		0x0f000000
#define DEV_CTRL_DEVICE_LAYER		1
#define DEV_CTRL_PROTOCOL_LAYER		2
#define DEV_CTRL_INPUT				1
#define DEV_CTRL_OUTPUT				2
#define DEV_CTRL_TRANSLATE			4
#define DEV_CTRL_LAYER(a)			((a & DEV_CTRL_LAYER_MASK) >> 28)
#define DEV_CTRL_SWITCH(a)			((a & DEV_CTRL_SWITCH_MASK) >> 24)
#define _CTRL_FILTER				1
#define _CTRL_DEVICE				2

/* Ph_EV_POINTER_CTRLs  PhPointerCtrlEvent_t types */
#define POINTER_CTRL_FILTER			_CTRL_FILTER
#define POINTER_CTRL_DEVICE			_CTRL_DEVICE

/* Ph_EV_POINTER_CTRLs  PhPointerCtrlEvent_t filter flags */
#define POINTER_CTRL_GETCTRL		0x00000000 /* included for completeness */
#define POINTER_CTRL_ON				0x00000001
#define POINTER_CTRL_OFF			0x00000002
#define POINTER_CTRL_GAIN			0x00000004
#define POINTER_CTRL_THRESHOLD		0x00000008
#define POINTER_CTRL_BUTTONS		0x00000010
#define POINTER_CTRL_SETMATRIX		0x00000020
#define POINTER_CTRL_GETMATRIX		0x00000040
#define POINTER_CTRL_FILENAME		0x00000080
#define POINTER_CTRL_TYPE_MASK		DEV_CTRL_TYPE_MASK
#define POINTER_CTRL_LAYER_MASK		DEV_CTRL_LAYER_MASK
#define POINTER_CTRL_SWITCH_MASK	DEV_CTRL_SWITCH_MASK

#define POINTER_CTRL_SWAP			0x00000100
#define POINTER_CTRL_DEVMATRIX	 	0x00000200
#define POINTER_CTRL_SCRNMATRIX		0x00000400
#define POINTER_CTRL_LAYER			0x00000800
#define POINTER_CTRL_THREEPTMATRIX 0x00001000
#define POINTER_CTRL_ATTR_MASK		0x00001f00

#define POINTER_CTRL_LAYER_SET(a)	((a << 28) & POINTER_CTRL_LAYER_MASK)
#define POINTER_CTRL_SWITCH_SET(a)	((a << 24) & POINTER_CTRL_SWITCH_MASK)

typedef struct pointer_ctrl_event {
	short			type;
	short			len;
	union pointer_ctrl {
		struct _pointer_ctrl dev;
		struct {
			unsigned flags;
			struct _pointer_matrix scrn;
			struct _pointer_matrix coord;  
			int					   threshold;
			int					   gain;
			char				   file[PATH_MAX+1];
		} filter;
	} ctrl;
	void			*device;
	struct _three_point_calib_matrix three_pt_matrix;
} PhPointerCtrlEvent_t;

/* Ph_EV_KEYBOARD_CTRLs PhKeyboardCtrlEvent_t types */
#define KEYBOARD_CTRL_FILTER		_CTRL_FILTER
#define KEYBOARD_CTRL_DEVICE		_CTRL_DEVICE

/* Ph_EV_KEYBOARD_CTRLs PhKeyboardCtrlEvent_t filter flags */
#define KEYBOARD_CTRL_ON			0x00000100
#define KEYBOARD_CTRL_OFF			0x00000200
#define KEYBOARD_CTRL_DISPLAY	 	0x00000400
#define KEYBOARD_CTRL_RATE			0x00000800
#define KEYBOARD_CTRL_DELAY			0x00001000
#define KEYBOARD_CTRL_FILENAME		0x00002000
#define KEYBOARD_CTRL_TYPE_MASK		(DEV_CTRL_TYPE_MASK << 8)
#define KEYBOARD_CTRL_LAYER_MASK	DEV_CTRL_LAYER_MASK
#define KEYBOARD_CTRL_SWITCH_MASK	DEV_CTRL_SWITCH_MASK

#define KEYBOARD_CTRL_DISPLAY_ON	0x00010000
#define KEYBOARD_CTRL_DISPLAY_OFF	0x00020000
#define KEYBOARD_CTRL_LAYER			0x00040000
#define KEYBOARD_CTRL_ATTR_MASK		0x000f0000

#define KEYBOARD_CTRL_LAYER_SET		POINTER_CTRL_LAYER_SET
#define KEYBOARD_CTRL_SWITCH_SET	POINTER_CTRL_SWITCH_SET

typedef struct keyboard_ctrl_event {
	short			type;
	short			len;
	union keyboard_ctrl {
		struct _keyboard_ctrl dev;
		struct {
			unsigned 	 flags;
			char		 file[PATH_MAX+1];
		} filter;
	} ctrl;
	void 			*device;
} PhKeyboardCtrlEvent_t;


/* Ph_EV_FEP subtype of Ph_EV_SERVICE */
typedef struct ph_service_fep {
	long	type;
	long	len;
	PhRect_t rect;
	long	num_rids;
	char	font[MAX_FONT_TAG];
} PhFEPService_t;
/* valid 'type's for PhFEPService_t */
#define Ph_FEP_BROADCAST	0x00000000 /* request a broadcast from FEP service */
#define Ph_FEP_RECT			0x00000001 /* give rect to FEP services */
#define Ph_FEP_NORECT		0x00000002 /* invalidate rect in FEP service */
#define Ph_FEP_ACTIVATE		0x00000003 /* request activation of FEP filter */
#define Ph_FEP_DEACTIVATE	0x00000004 /* request deactivation of FEP filter */

/* Commands (type) for PhFEPService_t */
#define Ph_FEP_CHANGE_MODE  0x00000005 /* cmd */
#define Ph_FEP_TOGGLE_1		0x00000006 /* cmd */
#define Ph_FEP_HELP			0x00000007 /* cmd */

/* Ph_EV_INFO_FEP subtype of Ph_EV_INFO */
typedef struct ph_info_fep {
	long	type;
	long	subtype;
	long	len;
	char	data[1];
} PhFEPInfo_t;

/* type meanings for PhFEPInfo struct */
#define Ph_FEP_REGISTER		0
#define Ph_FEP_DEREGISTER   1

/* subtype meanings for PhFEPInfo struct */
#define Ph_FEP_JAPANESE	0x00000001
#define Ph_FEP_CHINESE	0x00000002
#define Ph_FEP_KOREAN	0x00000003

/* Ph_EV_PRINTER subtype of Ph_EV_INFO */
typedef struct ph_info_printer
	{
	int		type;
	pid_t	pid;
	void 	*handle;
	int		status;
	int		page_num;
	} PhInfoPrinter_t;

/* types for Ph_EV_PRINTER info events */
#define		Pp_DOCUMENT_COMPLETE	0x00000001
#define		Pp_PAGE_COMPLETE		0x00000002

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PhService.h $ $Rev: 224590 $" )
#endif
