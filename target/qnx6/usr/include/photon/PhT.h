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
 * PhT.h	
 *		Regions, events, graphics contexts, etc.
 *		This header file contains the majority of the non-Pg Photon
 *		manifests and structure definitions
 *

 */
#ifndef __PHT_H_INCLUDED
#define __PHT_H_INCLUDED

#include <semaphore.h>
#include <time.h>
#include <sys/types.h>
#include <inttypes.h>

#if defined(__QNXNTO__)
	#include <unistd.h>
#elif defined(__SOLARIS__)
#elif !defined(__linux__) && !defined(__CYGWIN__)
	/* QNX4 */
	#include <sys/sendmx.h>
	typedef struct _mxfer_entry iov_t;
	#define SETIOV( iov, addr, len )                     _setmx( iov, addr, len )
#endif

#if defined(__SOLARIS__) || defined(__linux__)
typedef short mpid_t;

#elif defined(__CYGWIN__)
#if !NATIVE_WINSOCK
#include <fixerrno.h>
#endif

typedef short mpid_t;
typedef long nid_t;
#ifndef _CYGWIN_SIGNAL_H
union sigval {
	int sigval_int;
	void	*sigval_ptr;
};
struct sigevent {
	int sigev_signo;
	union sigval sigev_value;
};
#endif

#define __min(a,b) ((a)<(b)?(a):(b))
#define __max(a,b) ((a)>(b)?(a):(b))
#if !defined(min) && !defined(__cplusplus)
#define min(a,b)  (((a) < (b)) ? (a) : (b))
#endif
#if !defined(max) && !defined(__cplusplus)
#define max(a,b)  (((a) > (b)) ? (a) : (b))
#endif
#endif

#ifndef _LIMITS_H_INCLUDED
 #include <limits.h>
#endif

#if !defined(PATH_MAX)
	#define PATH_MAX _POSIX_PATH_MAX
#endif

#if !defined(NAME_MAX)
	#define NAME_MAX 48
#endif

#include <utf8.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *
 * Manifests for use in PhEvent_t
 *
 */
#if !defined (__QNXNTO__)
#define SETIOV( iov, addr, len )	_setmx( iov, addr, len )
#endif

/*
 * Event type bit definitions
 */
#define Ph_EV_KEY					0x00000001
#define Ph_EV_BUT_PRESS				0x00000002
#define Ph_EV_BUT_RELEASE			0x00000004
#define Ph_EV_PTR_MOTION_NOBUTTON	0x00000008
#define Ph_EV_PTR_MOTION_BUTTON		0x00000010
#define Ph_EV_BOUNDARY				0x00000020
#define Ph_EV_EXPOSE				0x00000040
#define Ph_EV_DRAW					0x00000080
#define Ph_EV_INPUT_OTHER			0x00000100
#define Ph_EV_DRAG					0x00000200
#define Ph_EV_COVERED				0x00000400
#define Ph_EV_BLIT					0x00000800
#define	Ph_EV_SYSTEM				0x00001000
#define	Ph_EV_WM					0x00002000
#define Ph_EV_BUT_REPEAT			0x00004000
#define Ph_EV_RAW					0x00008000
#define Ph_EV_TIMER					0x00010000
#define	Ph_EV_LB_SYSTEM				0x00020000
#define Ph_EV_SERVICE				0x00040000
#define Ph_EV_INFO					0x00080000
#define	Ph_EV_AUDIO					0x00100000
#define	Ph_EV_DNDROP				0x00200000
#define	Ph_EV_USER					0x80000000

/* Some useful combinations of event bits */

#define Ph_EV_PTR_MOTION		( Ph_EV_PTR_MOTION_NOBUTTON | Ph_EV_PTR_MOTION_BUTTON )
#define Ph_EV_PTR_ALL			( Ph_EV_BUT_PRESS | Ph_EV_BUT_RELEASE | Ph_EV_PTR_MOTION | Ph_EV_BUT_REPEAT  )
#define Ph_EV_WIN_SENSE			( Ph_EV_KEY | Ph_EV_BUT_PRESS | Ph_EV_BUT_RELEASE | Ph_EV_EXPOSE | Ph_EV_DRAG | Ph_EV_TIMER | Ph_EV_DNDROP )
#define Ph_EV_WIN_OPAQUE		( Ph_EV_WIN_SENSE | Ph_EV_PTR_ALL | Ph_EV_BOUNDARY | Ph_EV_DRAW | Ph_EV_COVERED | Ph_EV_KEY | Ph_EV_BUT_REPEAT | Ph_EV_BLIT )
#define Ph_EV_WIDGET_OPAQUE		( Ph_EV_WIDGET_SENSE | Ph_EV_PTR_ALL | Ph_EV_KEY )
#define Ph_EV_WIDGET_SENSE		( Ph_EV_KEY | Ph_EV_BUT_PRESS | Ph_EV_BUT_RELEASE | Ph_EV_DRAG | Ph_EV_BOUNDARY | Ph_EV_DNDROP )
#define Ph_EV_ICON_SENSE		( Ph_EV_WM | Ph_EV_EXPOSE )
#define Ph_EV_ICON_OPAQUE		( Ph_EV_WM | Ph_EV_EXPOSE | Ph_EV_DRAW )

/*
 * Event subtypes
 */

/* of Ph_EV_BOUNDARY: */
#define Ph_EV_PTR_ENTER_FROM_PARENT	0
#define Ph_EV_PTR_ENTER				0
#define	Ph_EV_PTR_LEAVE_TO_PARENT	1
#define	Ph_EV_PTR_LEAVE				1
#define Ph_EV_PTR_STEADY			2
#define Ph_EV_PTR_UNSTEADY			3
#define Ph_EV_PTR_ENTER_FROM_CHILD	4
#define Ph_EV_PTR_LEAVE_TO_CHILD	5
#define Ph_EV_PTR_TRANSIENT_ENTER	8
#define Ph_EV_PTR_TRANSIENT_LEAVE	9
#define Ph_EV_PTR_RECT_ENTER		0x10
#define Ph_EV_PTR_RECT_LEAVE		0x11


/* of Ph_EV_RAW */
#define Ph_EV_RAW_KEY			0
#define Ph_EV_RAW_PTR			1
#define Ph_EV_RAW_AUXPTR		2
#define Ph_EV_RAW_OTHER			3

/* of Ph_EV_BUT_RELEASE */
#define Ph_EV_RELEASE_REAL		0
#define Ph_EV_RELEASE_PHANTOM	1
#define Ph_EV_RELEASE_ENDCLICK	2
#define Ph_EV_RELEASE_OUTBOUND	3

/* of Ph_EV_INPUT_OTHER -- defined in a separate header */

/* of Ph_EV_DRAG */             
#define Ph_EV_DRAG_INIT			0
#define Ph_EV_DRAG_MOVE			1
#define Ph_EV_DRAG_COMPLETE		2
#define Ph_EV_DRAG_KEY_EVENT	3
#define Ph_EV_DRAG_MOTION_EVENT	4
#define Ph_EV_DRAG_BOUNDARY		5
#define Ph_EV_DRAG_START		6

/* of Ph_EV_EXPOSE: */					
#define	Ph_NORMAL_EXPOSE		0
#define	Ph_PRINTER_EXPOSE		1
#define	Ph_GRAPHIC_EXPOSE		2
#define	Ph_CAPTURE_EXPOSE		4

/* of Ph_EV_DRAW: */
#define Ph_NORMAL_DRAW			0x0000
#define	Ph_START_DRAW			0x4000u
#define	Ph_DONE_DRAW			0x8000u

/* of Ph_EV_BLIT: */
#define Ph_SINGLE_BLIT				0
#define Ph_MULTI_BLIT				2

/* of Ph_EV_MOTION_BUTTON and Ph_EV_MOTION_NOBUTTON */
#define Ph_EV_MOTION_NORMAL		0
#define Ph_EV_MOTION_STEADY		1

/* of Ph_EV_KEY */
#define Ph_EV_KEY_NORMAL		0

/* of Ph_EV_WM */
/* see PhWM.h */

/* of Ph_EV_AMIN */
#define Ph_EV_ADMIN_SEND_FILE		0
#define Ph_EV_ADMIN_FILE_SENT		1

/* service subtypes */
#define Ph_INVALIDATE_SYSINFO		0
#define Ph_EV_INVALIDATE_SYSINFO	0
#define Ph_REMOTE_WM			1
#define Ph_EV_REMOTE_WM			1
#define Ph_POINTER_CTRL			2
#define Ph_EV_POINTER_CTRL		2
#define Ph_KEYBOARD_CTRL		3
#define Ph_EV_KEYBOARD_CTRL		3
#define Ph_FEP				4
#define Ph_EV_FEP			4
#define Ph_PRINTER			5
#define Ph_EV_PRINTER			5
/*#define Ph_SPARE			6 */
#define Ph_OFFSCREEN_INVALID		7
/* flag types for offscreen invalid data */
#define Pg_VIDEO_MODE_SWITCHED		0x00000001
#define Pg_ENTERED_BYPASS		0x00000002
#define Pg_ENTERED_DIRECT		Pg_ENTERED_BYPASS
#define Pg_EXITED_BYPASS		0x00000004
#define Pg_EXITED_DIRECT		Pg_EXITED_BYPASS
#define Pg_DRIVER_STARTED		0x00000008
#define Pg_POWERED_UP			0x00000010
#define Pg_POWERED_DOWN			0x00000020

/* Subtypes of Ph_EV_INFO */
/* 		Ph_EV_INVALIDATE_SYSINFO	0 pre-defined above */
#define Ph_EV_INVALIDATE_FONTINFO	1
#define Ph_EV_NEW_TIMEZONE		2
#define Ph_EV_CONFIG			3
/*      Ph_EV_FEP                       4         pre-defined above */
/*		Ph_EV_PARCEL				6	pre-defined above */
/* 		Ph_OFFSCREEN_INVALID		7   pre-defined above */
/* #define Ph_EV_CLIPBOARD_CHANGED	8 UNDEFINED TO PREVENT USE FOR NOW. */

/* Subtypes of Ph_EV_DNDROP */
#define Ph_EV_DND_INIT			0
#define Ph_EV_DND_CANCEL		1
#define Ph_EV_DND_ENTER			2
#define Ph_EV_DND_LEAVE			3
#define Ph_EV_DND_ACK			4
#define Ph_EV_DND_NAK			5
#define Ph_EV_DND_MOTION		6
#define Ph_EV_DND_DROP			7
#define Ph_EV_DND_COMPLETE		8
#define Ph_EV_DND_DELIVERED		9
#define Ph_EV_DND_REPEAT		10

/*
 * Event flags
 */
#define Ph_EMIT_TOWARD			0x0001
#define Ph_EVENT_NO_RECT		0x0002
#define Ph_EVENT_ABSOLUTE		0x0004
#define Ph_EVENT_INCLUSIVE		0x0008
#define Ph_EVENT_DIRECT			0x0010
#define Ph_EVENT_REDIRECTED		0x0020
#define Ph_EVENT_ODD			0x0040
#define Ph_EVENT_RSRV1			0x8000		/* Reserved by server */

/*
 *
 * Manifests for use in PhRegion_t 
 *
 */

/*
 * Region flags
 */
#define Ph_WINDOW_REGION		0x00000001
#define Ph_WND_MGR_REGION		0x00000002
#define Ph_GRAFX_REGION			0x00000004
#define Ph_PTR_REGION			0x00000008
#define Ph_KBD_REGION			0x00000010
#define Ph_PRINT_REGION			0x00000020
#define Ph_INPUTGROUP_REGION		0x00000040
#define Ph_AUXPTR_REGION		0x00000080
#define Ph_AUDIO_REGION			0x00000100
#define Ph_NOTIFY_REGION        	0x00080000
#define Ph_FORCE_FRONT			0x00100000
#define Ph_FOLLOW_IG_SIZE		0x00200000
#define Ph_FORCE_BOUNDARY		0x00400000
#define Ph_NO_COMPRESSION		0x00800000
#define Ph_CURSOR_SET			0x01000000
#define Ph_RECT_BOUNDARY		0x02000000
#define	Ph_AUXGRAFX_REGION		0x04000000

#define Ph_REGION_TYPE_MASK		0x000FFFFF
#define Ph_INPUT_GROUP_MASK		(Ph_GRAFX_REGION|Ph_PTR_REGION|Ph_AUXPTR_REGION|Ph_KBD_REGION|Ph_INPUTGROUP_REGION)

/* 
 *	Region state 
 */
#define Ph_ESCAPE_COUNT_MASK		0x00FF

/*
 * Query Rids flags
 */
#define Ph_RIDQUERY_IG_POINTER		0x1000		/* Use input_groups pointer point as rect */
#define Ph_RIDQUERY_TOWARD		0x2000

/*
 * Query visible flags
 */
#define Ph_QUERY_GRAPHICS		0x0004		/* Return graphics driver rectangle */
#define Ph_QUERY_INPUT_GROUP		0x0040		/* Return input group rectangle */
#define Ph_QUERY_CONSOLE		0x0000		/* Equivalent to either GRAPHICS or INPUT_GROUP */
#define Ph_QUERY_WORKSPACE		0x0002		/* Return console's "unreserved" rectangle */
#define Ph_QUERY_EXACT			0x0100		/* Must match input group and rid, otherwise it is a hint */
#define Ph_QUERY_IG_POINTER		0x1000		/* Use point of current location of input_group pointer */
#define Ph_QUERY_IG_REGION		0x2000		/* Use input_group rect */

/* 
 * RID's of the system regions
 */
#define Ph_ROOT_RID				0
#define Ph_DEV_RID				1

/* 
 * Bits used to define valid fields in a region change or open
 */
#define Ph_REGION_OWNER			0x00000001
#define Ph_REGION_HANDLE		0x00000002
#define Ph_REGION_FLAGS			0x00000004
#define Ph_REGION_EV_OPAQUE		0x00000008
#define Ph_REGION_EV_SENSE		0x00000010
#define Ph_REGION_STATE			0x00000020
#define Ph_REGION_ORIGIN		0x00000040
#define Ph_REGION_PARENT		0x00000080
#define Ph_REGION_IN_FRONT		0x00000100
#define Ph_REGION_BEHIND		0x00000200
#define Ph_REGION_RECT			0x00000400
#define Ph_REGION_DATA			0x00000800
#define Ph_REGION_CURSOR		0x00001000
#define Ph_REGION_NUM_RECTS		0x00002000
#define Ph_REGION_INPUT_GROUP		0x00008000

/* 
 * Bits used to define operations on opacity and sensitivity in a region change
 */
#define Ph_REGION_EV_OPAQUE_SET	0x00000008
#define Ph_REGION_EV_SENSE_SET	0x00000010
#define Ph_REGION_EV_OPAQUE_AND	0x00010000
#define Ph_REGION_EV_SENSE_AND	0x00020000
#define Ph_REGION_EV_OPAQUE_OR	0x00040000
#define Ph_REGION_EV_SENSE_OR	0x00080000


/* Only valid during a RegionChange */
#define Ph_EXPOSE_FAMILY		0x00002000
#define Ph_EXPOSE_REGION		0x00004000
#define Ph_BLIT_REGION			0x00008000

/* Region data types */
#define Ph_RDATA_WINDOW			0x0001
#define Ph_RDATA_CURSOR			0x0002
#define Ph_RDATA_IG			0x0003
#define Ph_RDATA_GFXINFO		0x0004
#define Ph_RDATA_KBDINFO		0x0005
#define Ph_RDATA_PTRINFO		0x0006
#define Ph_RDATA_WMCONFIG		0x0007
#define Ph_RDATA_GFXDETAIL		0x0008
#define Ph_RDATA_INPMGRINFO		0x0009
#define Ph_RDATA_CLIPBOARD		0x000A
#define Ph_RDATA_DNDINFO		0x000B
#define Ph_RDATA_USER			0xFFFF


/* Region data contained types */
/* Ph_RDATA_CURSOR */
#define Ph_CURSOR_FRONT 1
#define Ph_CURSOR_BACK 	2


/* Info defines */
#define Ph_INFO_CTRL_FD 		0
#if !defined(__QNXNTO__)
	#define Ph_INFO_CTRL_PROXY 	1
	#define Ph_INFO_CTRL_REM_PROXY 	2 
#endif
#define Ph_INFO_CTRL_GIN 		3
#define Ph_INFO_CTRL_GC 		4
#define Ph_INFO_CTRL_DFLT_GC 		5
#define Ph_INFO_CTRL_BUF_GC 		6

/* Flags returned by PhRegion/WindowChange/Close() and PhEmit...() */

#define Ph_NO_EVENT              1
#define Ph_EVENT_INVALIDATE_EVEN 2
#define Ph_EVENT_INVALIDATE_ODD  4

/*
 *
 * Structure and type definitions
 *
 */

/*
 * Miscellaneous useful types
 */

#ifndef PgColor_t
typedef unsigned long PgColor_t;
#endif
typedef long PhRid_t;

#include <photon/PhGeom.h>

typedef struct Ph_point  PhPoint_t;
typedef struct Ph_dim    PhDim_t;
typedef struct Ph_lpoint PhLpoint_t;
typedef struct Ph_rgb    PhRgb_t;
typedef struct Ph_prect  PhPrect_t;		
#ifndef Ph_OLD_TYPES
typedef struct Ph_rect   PhRect_t;
typedef struct Ph_area   PhArea_t;
typedef struct Ph_extent PhExtent_t;
#else
typedef struct Ph_rectold   PhRect_t;
typedef struct Ph_areaold   PhArea_t;
typedef struct Ph_extentold PhExtent_t;
#endif
typedef struct Ph_point_16dot16  PhPoint16dot16_t;
typedef struct Ph_rect_16dot16   PhRect16dot16_t;

#if defined(__QNXNTO__)
	typedef long PhConnectId_t;
#else
	typedef short PhConnectId_t;
#endif

typedef long PhConnectorId_t;

typedef struct Ph_tile { PhRect_t rect; struct Ph_tile *next; } PhTile_t;

/*
 * The region structure
 */
typedef struct Ph_region {
	PhRid_t				rid;
	long				handle;
	PhConnectId_t		owner;
	ulong_t				flags;
	ushort_t			state;
	#ifdef __QNXNTO__
		ushort_t		zero1;
	#endif
	unsigned long		events_sense;
	unsigned long		events_opaque;
	PhPoint_t			origin;
	PhRid_t				parent,
						child,
						bro_in_front,
						bro_behind;
	PgColor_t			cursor_color;
	ushort_t			input_group;
	ushort_t			data_len;
	unsigned long		zero2[2];
	ushort_t			cursor_type;
	ushort_t			num_rects;
} PhRegion_t;

typedef struct Ph_region_data_hdr {
	unsigned short		len;
	unsigned short		type;
} PhRegionDataHdr_t;

/*
 * The structure of an event
 */
 
/* Region id/handle combo */
typedef struct Ph_event_region {
	PhRid_t			rid;
	long			handle;
} PhEventRegion_t;

/* The header for PhEvent_t */
typedef struct Ph_event_hdr {
	unsigned long 		type;		
	unsigned short 		subtype;	
	unsigned short		processing_flags;
	PhEventRegion_t		emitter;
	PhEventRegion_t		collector;
	unsigned short		input_group;
	unsigned short 		flags;		
	unsigned long		timestamp;
	PhPoint_t			translation;
} PhEventHdr_t;

/* Event Processing flags */
#define Ph_FAKE_EVENT		0x0001
#define Ph_BACK_EVENT		0x0002
#define Ph_CONSUMED			0x0004
#define Ph_DIRECTED_FOCUS	0x0010
#define Ph_FOCUS_BRANCH		0x0020
#define Ph_TYPE_SPECIFIC	0x0FF0
#define Ph_USER_RSRVD_BITS	0xF000

/*
 * Event type specific processing flags 
 */
	/*
	 * Ph_EV_KEY processing flags 
	 */
	#define Ph_NOT_CUAKEY			0x10  
		/* force PtContainer NOT to use the key for traversal (CUA) */
	#define Ph_NOT_HOTKEY		0x20  
		/* force PtContainer NOT to treated the key as a hotkey */


/* THE event structure */
typedef struct Ph_event {
	unsigned long 		type;		
	unsigned short 		subtype;	
	unsigned short		processing_flags;
	PhEventRegion_t		emitter;
	PhEventRegion_t		collector;
	unsigned short		input_group;
	unsigned short 		flags;	
	unsigned long		timestamp;
	PhPoint_t			translation;
	unsigned short		num_rects;
	unsigned short		data_len;
} PhEvent_t;

/*
 * Ph_EV_DRAW
 */
#define		_Pg_DRAW_EVENT_VERSION		2
typedef struct Ph_ev_draw_data {
	unsigned short	cmd_buffer_size; /* bytes */
	unsigned short	draw_event_version; 
	unsigned long	id;
} PhDrawEvent_t;

/*
 * Ph_EV_RAW subtype Ph_EV_RAW_PTR
 */
#define		Ph_PTR_FLAG_Z_NONE		0x00
#define		Ph_PTR_FLAG_Z_REL		0x01
#define		Ph_PTR_FLAG_Z_ABS		0x02
#define		Ph_PTR_FLAG_Z_PRESSURE	0x03
#define		Ph_PTR_FLAG_Z_MASK		0x03
#define		Ph_PTR_FLAG_PROG  		0x04
#define		Ph_PTR_FLAG_Z_ONLY 		0x08
#define		Ph_PTR_FLAG_ABS_DEV		0x10

#define	Ph_PTR_RAW_FLAG_NO_BUTTONS	0x01	/* Buttons are not valid */
#define	Ph_PTR_RAW_FLAG_XY_REL		0x02	/* XY coords are relative (not absolute)  */

typedef struct Ph_ev_raw_ptr_coord {
	short				x;
	short				y;
	short				z;
	unsigned short		dmsec;
} PhRawPtrCoord_t;

typedef struct Ph_ev_raw_ptr_data {
	unsigned long		msec;
	unsigned short		button_state;
	unsigned char		flags;
	unsigned char		raw_flags;
	unsigned short		num_coord;
	unsigned short		zero;			/* reserved for future */
	PhRawPtrCoord_t		coord[1];
} PhRawPtrEvent_t;

#ifdef _SYS_POINTER_H_INCLUDED
typedef struct Ph_ev_raw_auxptr_data {
	unsigned short				num_packets;
	unsigned short				zero;
	struct _pointer_packet		packet;
} PhRawAuxPtrEvent_t;
#endif

typedef struct Ph_ev_raw_other_data {
	unsigned subtype;
	/* More data follows... */
} PhRawOtherEvent_t;

/*
 * Ph_EV_PTR_ALL
 */
typedef struct Ph_ev_ptr_data {
	PhPoint_t			pos;			/* Always mouse position */
	unsigned short		buttons;		/* The button that was pressed/released */
	unsigned short		button_state;	/* same as in PhRawPtrEvent_t */
	unsigned char		click_count;
	unsigned char		flags;			/* same as in PhRawPtrEvent_t */
	short				z;
	unsigned long		key_mods;		/* same as in PhKeyEvent_t */
	unsigned long		zero;			/* reserved; */
} PhPointerEvent_t;

/* Mouse buttons */
#define Ph_BUTTON_SELECT	0x0004L 
#define Ph_BUTTON_MENU		0x0001L
#define Ph_BUTTON_ADJUST	0x0002L

#define Ph_BUTTON_3			Ph_BUTTON_SELECT 	/* left button default */
#define Ph_BUTTON_1			Ph_BUTTON_MENU		/* right button default */
#define Ph_BUTTON_2			Ph_BUTTON_ADJUST	/* middle button */

/*
 * Ph_EV_INPUT_OTHER
 */
typedef struct Ph_ev_input_other_data {
	unsigned long		key_mods;		/* same as in PhKeyEvent_t */
	PhPoint_t			pos;			/* Always mouse position */
	unsigned short		button_state;	/* same as in PhRawPtrEvent_t */
	unsigned short		reserved[3];
} PhInputOtherEvent_t;

/*
 * Ph_EV_DRAG
 */
typedef struct Ph_ev_drag_data {
	PhRect_t			rect;
	PhRid_t				rid;
	PhRect_t			boundary;
	PhDim_t				min;
	PhDim_t				max;
	PhDim_t				step;
	PhPoint_t			pos;
	unsigned long		key_mods;		/* same as in PhKeyEvent_t */
	long				zero[2];
	ushort_t			flags;
	unsigned short		button_state;	/* same as in PhRawPtrEvent_t */
} PhDragEvent_t;

/* drag event flags */
#define Ph_TRACK_LEFT  				0x0001
#define Ph_TRACK_RIGHT				0x0002
#define Ph_TRACK_TOP				0x0004
#define Ph_TRACK_BOTTOM				0x0008
#define Ph_TRACK_DRAG				(Ph_TRACK_LEFT|Ph_TRACK_RIGHT|Ph_TRACK_TOP|Ph_TRACK_BOTTOM)
#define Ph_DRAG_TRACK				0x0010		/* Emit Drag events to track drag, and dont draw an outline */
#define Ph_DRAG_KEY_MOTION			0x0020		/* Emit Ph_KEY and Ph_MOTION_* events while draging (with DRAG subtype) */
#define Ph_DRAG_NOBUTTON			0x0040		/* Drag will start even if no buttons are held down */
#define Ph_DRAG_ABSOLUTE			0x0080
#define Ph_DRAG_DRAW_RECT 			0x0100
#define Ph_DRAG_DRAW_RECT_INITIAL 	0x0200
#define Ph_DRAG_CURSOR_EXACT		0x0400
#define Ph_DRAG_CURSOR_POS			0x0800
#define Ph_DRAG_CURSOR_DEF			0x1000

/*
 * Ph_EV_BLIT subtype Ph_SINGLE_BLIT
 */
typedef struct Ph_ev_single_blit_data {
	PhRid_t				rid;
	PhRect_t			rect;
	PhPoint_t			offset;
	unsigned long		plane_mask;
} PhBlitEvent_t, PhSingleBlitEvent_t;

/*
 * Ph_EV_BLIT subtype Ph_MULTI_BLIT
 */
typedef struct Ph_ev_multi_blit_data {
	PhRid_t				rid;
	PhPoint_t			offset;
	unsigned long		plane_mask;
	unsigned short		nrects;
	unsigned short		reserved;
} PhMultiBlitEvent_t;

/*
 * Ph_EV_BOUNDARY
 */
typedef struct Ph_ev_boundary_data {
	PhEventRegion_t			entered;
	PhEventRegion_t			left;
} PhBoundaryEvent_t;

/*
 * Ph_EV_KEY
 */
typedef struct Ph_ev_raw_key_data {
	unsigned long			key_mods;		/* same as in PhPointerEvent_t */
	unsigned long			key_flags;
	unsigned long			key_cap;
	unsigned long			key_sym;
	unsigned short			key_scan;
	unsigned short			key_zero;		/* reserved for future */
} PhRawKeyEvent_t;

/*
 * Ph_EV_KEY
 */
typedef struct Ph_ev_key_data {
	unsigned long			key_mods;		/* same as in PhPointerEvent_t */
	unsigned long			key_flags;
	unsigned long			key_cap;
	unsigned long			key_sym;
	unsigned short			key_scan;
	unsigned short			key_zero;		/* reserved for future */
	PhPoint_t				pos;			/* Always mouse position */
	unsigned short			button_state;	/* same as in PhRawPtrEvent_t */
} PhKeyEvent_t;

/*
 * Ph_EV_TIMER
 */
typedef struct Ph_ev_timer_data {
	unsigned				msec;
	unsigned				zero;
	PhEventRegion_t			region;
} PhTimerEvent_t;

/*
 * Ph_EV_INFO, Ph_EV_NEW_TIMEZONE
 */
typedef struct Ph_ev_new_timezone_info 
{
	char tz[128];
	long spare[2];
} PhTimeZoneInfoEvent_t;

/*
 * Ph_EV_INFO, Ph_EV_CONFIG
 */
typedef struct ph_info_config {
        long    type;
        long    subtype;
        long    len;
} PhConfigInfo_t;


/*
 * Ph_EV_DNDROP
 */
typedef struct Ph_ev_dndrop_data {
	PhPoint_t			pos;
	unsigned short		flags;
	unsigned short		data_format;
	unsigned long		handle;
	PhRid_t				sender;
	PhRid_t				receiver;
	unsigned short		buttons;		/* Buttons that cause a drop */
	unsigned short		button_state;	/* Initial state of the buttons */
	unsigned long		key_mods;		/* same as in PhKeyEvent_t */
} PhDndEvent_t;

/* drag&drop event flags */
#define Ph_DND_SILENT  				0x0001
#define Ph_DND_FAILED  				0x0002

/* drag&drop data formats */
#define Ph_DNDFMT_DFLT 				0
#define Ph_DNDFMT_USER 				0x1000

/* CHANNEL event structure */
typedef struct Ph_channel_ev {
	unsigned long 		type;		
	unsigned short 		subtype;	
	unsigned short		flags;
	PhConnectId_t		emitter;
	PhConnectId_t		collector;
	unsigned long		timestamp;
	unsigned 	 		data_len;	
} PhChannelEv_t;


typedef struct Ph_ev_cursor_descr {
	unsigned short type;
	unsigned short length;
	/* More data here... */
} PhCursorDescription_t;

typedef struct Ph_character_cursor_data {
	PhCursorDescription_t hdr;
	PgColor_t color;
} PhCharacterCursorDescription_t;

typedef struct Ph_bitmap_cursor_data {
	PhPoint_t			size1;
	PhPoint_t			offset1;
	PgColor_t			color1;
	char				bytesperline1;
	#ifdef __QNXNTO__
		char			zero1[3];
	#endif
	PhPoint_t			size2;
	PhPoint_t			offset2;
	PgColor_t			color2;
	char				bytesperline2;
	char				Spare[14];
	char				images[1];
} PhBitmapCursorData_t;

typedef struct Ph_bitmap_cursor_descr {
	PhCursorDescription_t hdr;
	PhBitmapCursorData_t bmp;
} PhBitmapCursorDescription_t;

typedef struct Ph_ev_dndrop_cursors {
	const PhCursorDescription_t *active, *inactive, *unknown;
} PhDndCursors_t;

/*
 *  System info (used with PhQuerySystemInfo() )
 */
typedef struct Ph_grafx_info
{
	ulong_t valid_fields;
	ulong_t reserved1;
	ulong_t	bandwidth;
	ulong_t capabilities;
	uchar_t	color_bits;
	uchar_t reserved2[3];
	ulong_t possibilities;
} PhGrafxInfo_t;

#define Ph_GFX_BANDWIDTH		0x00000001
#define Ph_GFX_CAPABILITIES		0x00000002
#define Ph_GFX_COLOR_BITS		0x00000004
#define Ph_GFX_POSSIBILITIES	0x00000008

typedef struct Ph_grafx_region_data
{
	PhRegionDataHdr_t	hdr;
	PhGrafxInfo_t		info;
} PhGrafxRegionData_t;

typedef struct Ph_kbd_info
{
	ulong_t valid_fields;
	ulong_t capabilities;
	ulong_t reserved1;
	ulong_t	reserved2[16];
} PhKbdInfo_t;

#define Ph_KBD_CAPABILITIES		0x00000001

typedef struct Ph_kbd_region_data
{
	PhRegionDataHdr_t	hdr;
	PhKbdInfo_t			info;
} PhKbdRegionData_t;

typedef struct Ph_ptr_info
{
	ulong_t valid_fields;
	ulong_t capabilities;
	ulong_t reserved1;
	ulong_t	reserved2[16];
} PhPtrInfo_t;

#define Ph_PTR_CAPABILITIES		0x00000001

typedef struct Ph_ptr_region_data
{
	PhRegionDataHdr_t	hdr;
	PhPtrInfo_t		info;
}PhPtrRegionData_t;

typedef struct Ph_ig_info
{
	ulong_t valid_fields;
	ulong_t reserved1;
} PhIgInfo_t;

typedef struct Ph_ig_region_data
{
	PhRegionDataHdr_t	hdr;
	unsigned short		click_msec;		/* maximum release time to be concidered double click */
	unsigned short		delay_msec;		/* delay before repeating */
	unsigned short		rate_msec;		/* interval between repeat clicks */
	unsigned short		click_threshold;/* drag threshold, and also multi-click threshold (diamond where multi click is still valid */
	unsigned short		steady_msec;	/* Number of msec before emiting a MOTION_STEADY event */
	unsigned short		press_release_threshold; /* See Photon -U option */
	unsigned short		nobutton_click_threshold; /* optional larger multi-click threshold when no buttons pressed (i.e. not trying to initiate a drag) */
	unsigned short		Reserved;
}PhIgRegionData_t;

typedef struct Ph_general_sys_info
{
	ulong_t			valid_fields;
	ulong_t			reserved1;
	ushort_t		version;
	ushort_t		reserved2;
	ulong_t 		bandwidth;
	ulong_t 		capabilities;
	ushort_t		num_gfx;		
	ushort_t		num_kbd;		
	ushort_t		num_ptr;		
	ushort_t		num_ig;		
} PhGeneralSysInfo_t;

#define Ph_GEN_INFO_BANDWIDTH		0x000000001 /* flags for valid_fields */
#define Ph_GEN_INFO_CAPABILITIES	0x000000002
#define Ph_GEN_INFO_NUM_GFX			0x000000004
#define Ph_GEN_INFO_NUM_KBD			0x000000008
#define Ph_GEN_INFO_NUM_PTR			0x000000010
#define Ph_GEN_INFO_NUM_IG			0x000000020


typedef struct Ph_sys_info {
	PhGeneralSysInfo_t	gen;
	PhGrafxInfo_t		gfx;
	PhKbdInfo_t		kbd;
	PhPtrInfo_t		ptr;
	PhIgInfo_t		ig;
} PhSysInfo_t;

/* bandwidths */
#define Ph_BAUD_MAX		2147483647
#define Ph_BAUD_CONSOLE 100000000
#define Ph_BAUD_NETWORK	10000000
#define Ph_BAUD_SLOW	100000
#define Ph_BAUD_MIN		1

/* system capabilities (sysinfo->capabilities)*/

/* graphic capabilities (sysinfo->gfx) */
#define Ph_GCAP_BLIT			0x00000001
#define Ph_GCAP_MASKED_BLIT		0x00000002
#define Ph_GCAP_SHMEM			0x00000004
#define Ph_GCAP_PALETTE			0x00000008
#define Ph_GCAP_RELAY  			0x00000010
#define Ph_GCAP_PHINDOWS		0x00000020
#define	Ph_GCAP_LOCALHW			0x00000040
#define Ph_GCAP_DIRECTCOLOR		0x00000100
#define	Ph_GCAP_VIDEO_READABLE	0x00000200
#define	Ph_GCAP_NONINTERLACED	0x00000400
#define	Ph_GCAP_TEXT_AREA		0x00000800
#define Ph_GCAP_FRAME_READ		0x00001000
#define Ph_GCAP_SHMEM_FLUSH		0x00002000
#define Ph_GCAP_DRAW_OFFSCREEN	0x00004000
#define Ph_GCAP_DRAW_ALPHA			0x00008000
#define Ph_GCAP_DRAW_CHROMA		0x00010000
#define Ph_GCAP_DRAW_TERN_ROPS	0x00020000
#define Ph_GCAP_DRAW_GRADIENTS	0x00040000
#define Ph_GCAP_OVERLAY				0x00080000
#define Ph_GCAP_DIRECT				0x00100000	/* Non Direct mode service messages need to check this flag */
#define	Ph_GCAP_FutureSupported	0xFF000000	

/*
 * Clipboard stuff
 */
typedef char PhClipType[8];
typedef struct {
	PhClipType		type;
	unsigned short	length;
	#ifdef __QNXNTO__
		ushort_t		zero;
	#endif
	void			*data;
} PhClipHeader;
typedef struct
{
	PhClipType	type;
	uint32_t length;
	void *data;
} PhClipboardHdr;
#define Ph_CLIPBOARD_TYPE_TEXT	"TEXT"
#define Ph_CLIPBOARD_MAX_TYPES	5

/*
 *  Cursor info (used with PhQueryCursor() )
 */

typedef struct Ph_cursor_info {
	PhPoint_t		pos;			/*	Last position (absolute) */
	PhRid_t			region;			/*	Region currently containing cursor */
	PhRid_t			ig_region;		/*	Region representing input group */
	PgColor_t		color;			/*	Cursor color */
	PhPoint_t		last_press;		/*	Location of last Ph_EV_BUT_PRESS */
	unsigned long	msec;			/*	msec of last press */
	PhPoint_t		steady;			/*	Last steady base point */
	PhRid_t			dragger;		/*	Region currently dragging */
	PhRect_t		drag_boundary;	/*	Area to restrict dragging to */
	PhRid_t			phantom_rid;	/*	Rid to deliver phantom to. */
	unsigned short	type;			/*	Cursor type (from cursor font) */
	unsigned short	ig;				/*	Input group number */
	unsigned short	button_state;	/*	same as in PhRawPtrEvent_t */
	unsigned char	click_count;
	unsigned char	zero1;		/*	reserved */
	unsigned long	key_mods;		/*	same as in PhKeyEvent_t */
	unsigned long	zero2;			/*	reserved */
} PhCursorInfo_t;

/*
 *
 * Data maintained by the Photon client
 *
 */

/* Limits */
#define Ph_MAX_FONT_LEN		16
#define _Ph_MAX_DATA_MX		63

/*
 * Parameters to the Photon channel 
 */

/* channel parms flags */
#define Ph_BLOCK_OVERFLOW		0x00000001
#define Ph_TERM_OVERFLOW		0x00000002
#define Ph_NO_PROXY				0x00000004
#define Ph_NO_HOLD				0x00000008
#define Ph_DYNAMIC_BUFFER		0x00000010
#define Ph_COMPOUND_REPLY		0x00000020
#define Ph_SYSTEM_PROCESS		0x00000040
#define Ph_DITTO_CHANNEL		0x00000080

typedef struct Ph_channel_parms {
	#ifndef __QNXNTO__
		mpid_t		proxy;
	#endif
	unsigned long	max_q_entries;
	unsigned long	flags;
} PhChannelParms_t;

/* Photon channel info */
typedef struct _Ph_psinfo {
	unsigned long				flags;
	PhChannelParms_t			parms;
	PhConnectId_t				block;
	unsigned					num_q_entries;
	unsigned					buf_len;

	PhConnectId_t				id;
	int							nid;
	pid_t						pid;
	unsigned long				chev_sense;
	int							reserved[ 7 ];
} PhConnectInfo_t;


#define Ph_PROC_VIRTUAL		0x0001	/* Proc is internal Photon handler */
#define Ph_PROC_ARMED		0x0002	/* If event occurs, trigger proc's proxy */
#define Ph_PROC_BLOCKED		0x0004	/* Proc is "reply-blocked" on a server */
#define Ph_PROC_HELD		0x0008	/* Proc is held on someone else's queue */
#define Ph_PROC_CATCH_UP	0x0010	/* Proc is catching up on its event queue */
#define Ph_PROC_DYNAMIC_BUF	0x0020	/* Proc's wishes to match buffer size */

/*
 * Region Data
 */

typedef struct Ph_cursor_def {
	/* Type = Ph_RDATA_CURSOR */
	PhRegionDataHdr_t	hdr;
	PhPoint_t			size1;
	PhPoint_t			offset1;
	PgColor_t			color1;
	char				bytesperline1;
	#ifdef __QNXNTO__
		char			zero1[3];
	#endif
	PhPoint_t			size2;
	PhPoint_t			offset2;
	PgColor_t			color2;
	char				bytesperline2;
	char				Spare[14];
	char				images[1];
} PhCursorDef_t;

typedef struct Ph_bitmap_cursor_rdata {
	/* Type = Ph_RDATA_CURSOR */
	PhRegionDataHdr_t		hdr;
	PhBitmapCursorData_t	bmp;
} PhBitmapCursorRData_t;

typedef struct Ph_dnd_rdata {
	/* Type = Ph_RDATA_DNDINFO */
	PhRegionDataHdr_t		hdr;
	unsigned				dflt_subtype;
	PhCursorDescription_t	cursor;
} PhDndRegionData_t;

#define Ph_LIB_VERSION 205

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#ifndef __PH_MACROS_H_INCLUDED
#include <photon/PhMacros.h>
#endif

#endif


#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PhT.h $ $Rev: 219996 $" )
#endif
