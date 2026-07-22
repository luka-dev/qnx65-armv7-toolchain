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
 * 	PhMsg.h	
 *		Structures for Photon-client messaging
 *

 */

#ifndef __PH_MSG_H_INCLUDED

#include <signal.h>
#include <photon/PhInternal.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Photon message types (first short of every message)
 */
#define _Ph_BASE			0x700 
#define	_Ph_EMIT			_Ph_BASE
#define _Ph_REGION			(_Ph_BASE + 1)
#define	_Ph_QUERY			(_Ph_BASE + 2)
#define	_Ph_FORWARD			(_Ph_BASE + 3)
#define _Ph_INIT			(_Ph_BASE + 4)
#define _Ph_DEV_OPEN		(_Ph_BASE + 5)
#define _Ph_DEV_CLOSE		(_Ph_BASE + 6)
#define _Ph_NOP				(_Ph_BASE + 7)
#define _Ph_REG_SERVICE		(_Ph_BASE + 8)
#define _Ph_DEREG_SERVICE	(_Ph_BASE + 9)
#define _Ph_REPLY			(_Ph_BASE + 10)
#define _Ph_CONTROL			(_Ph_BASE + 11)
#define _Ph_TIMEOUT			(_Ph_BASE + 12) /* Proxy message type */
#define _Ph_NOTIFY			(_Ph_BASE + 13)
#define _Ph_SETATTR			(_Ph_BASE + 14)
#define _PIO_DEVCTL			(_Ph_BASE + 15)
#define _PHFONT_REQUEST_v100 (_Ph_BASE + 16)
#define _Ph_VOYAGER_PLUGIN	(_Ph_BASE + 17)
#define _Ph_PRINTER_CFG		(_Ph_BASE + 18)
#define _Ph_CONNECTION		(_Ph_BASE + 19)
#define _PHFONT_REQUEST		(_Ph_BASE + 20)
#define _Ph_SERVICE_BASE	(_Ph_BASE + 32)

/* 
 * Photon message subtypes
 */

/* for _Ph_EMIT */
#define	_Ph_EMIT_NORMAL		0
#define	_Ph_EMIT_CHANNEL	1

/* for _Ph_REGION */
#define	_Ph_REGION_OPEN		0
#define _Ph_REGION_SET		1
#define _Ph_REGION_CLOSE	2
#define	_Ph_REGION_WM_BASE	8			/* reserved for window manager forwarded events */

/* for _Ph_QUERY */
#define _Ph_QUERY_RIDS					1
#define _Ph_QUERY_REGION				2
#define _Ph_QUERY_PSINFO				3
#define _Ph_QUERY_SYSINFO				4
#define _Ph_QUERY_CURSOR				5

/* for _Ph_INIT */
#define _PH_INIT_APP					0

/* for _Ph_CONTROL */
#define _Ph_CONTROL_NORMAL				0
#define _Ph_CONTROL_CHEVMASK			1

/* for _Ph_CONNECTION */
#define _Ph_CONNECTOR_CREATE			1
#define _Ph_CONNECTOR_DESTROY			2
#define _Ph_CONNECTOR_FIND				4
#define _Ph_CONNECTOR_QUERY				3

/*
 * Photon reply types (returned to clients)
 */
#define _Ph_HDR_MSG			0
#define _Ph_EVENT_MSG		1
#define _Ph_CLOSE_MSG		2
#define _Ph_RESIZE_MSG		3
#define _Ph_CHEVENT_MSG		4

#define Ph_EVENT_MSG		_Ph_EVENT_MSG
#define Ph_CHEVENT_MSG		_Ph_CHEVENT_MSG
#define Ph_RESIZE_MSG		_Ph_RESIZE_MSG

/* 
 * Photon message flags 
 */
#define _Ph_ARM				0x0001
#define _Ph_REPLY_EVENT		0x0002
#define _Ph_BLOCK			0x0004

/*
 * Photon reply flags 
 */
#define _Ph_EVENTS_PENDING	0x0001
#define _Ph_EVENTS_APPENDED	0x0002
#define _Ph_EVENTS_DITTOED	0x0004

/*
 * Message structures
 */

/* Generic Photon message header */
struct _Ph_msg_hdr {
	short unsigned	type;
	short unsigned	subtype;
	short unsigned	flags;
	short			reserved;
};

/* _Ph_EMIT subtype _Ph_EMIT_NORMAL */
struct _Ph_msg_emit {
	struct _Ph_msg_hdr	hdr;
	PhEvent_t			event;
};

/* _Ph_EMIT subtype _Ph_EMIT_CHANNEL */
struct _Ph_msg_emit_channel {
	struct _Ph_msg_hdr	hdr;
	PhChannelEv_t		event;
};

/* _Ph_CONTROL subtype _Ph_CONTROL_NORMAL */
struct _Ph_msg_control {
	struct _Ph_msg_hdr	hdr;
	unsigned long		buf_len;
};

/* _Ph_CONTROL subtype _Ph_CONTROL_CHEVMASK */
struct _Ph_msg_control_chevmask {
	struct _Ph_msg_hdr	hdr;
	unsigned long		mask;
};

/* _Ph_REGION subtype _Ph_REGION_OPEN */
struct _Ph_msg_region_open { 
	struct _Ph_msg_hdr		hdr;
	ulong_t					fields;	
	ulong_t					zero;
	PhRegion_t				info;
	/*
	 rects
	 [data]
	*/
};

/* _Ph_REGION subtype _Ph_REGION_SET */
struct _Ph_msg_region_set {
	struct _Ph_msg_hdr		hdr;
	ulong_t					fields;
	ulong_t					flags;
	PhRegion_t				info;
	/*
	 [rects]
	 [data]
	*/
};

/* _Ph_REGION subtype _Ph_REGION_CLOSE */
struct _Ph_msg_region_close {
	struct _Ph_msg_hdr	hdr;
	PhRid_t				rid;
};

/* _Ph_INIT */
struct _Ph_msg_init {
	struct _Ph_msg_hdr	hdr;
	PhChannelParms_t	parms;
	short				fd;
	char				zero[14];
};

/* _Ph_QUERY subtype _Ph_QUERY_RIDS */
struct _Ph_msg_query_rids {
	struct _Ph_msg_hdr	hdr;
	unsigned short		flags;
	unsigned short		num;
	PhRid_t				rid;
	unsigned short		input_group;
	short				reserved;
	ulong_t				type;
	unsigned long		sense;
	PhRid_t				emitter;
	PhRect_t			rect;
};

/* _Ph_QUERY subtype _Ph_QUERY_REGION */
struct _Ph_msg_query_region {
	struct _Ph_msg_hdr	hdr;
	PhRid_t				rid;
	unsigned short		nrects;
	unsigned short		reserved;
};

#define _Ph_QUERY_REGION_ABSOLUTE	0x00000001

/* _Ph_QUERY subtype _Ph_QUERY_SYSINFO */
struct _Ph_msg_query_sysinfo {
	struct _Ph_msg_hdr	hdr;
	PhRid_t				rid;
	PhRect_t			rect;
	unsigned short		flags;
	unsigned short		buflen[1]; 
};

#define _Ph_QUERY_SYSINFO_GEN	0x01	/* flags */
#define _Ph_QUERY_SYSINFO_GFX	0x02
#define _Ph_QUERY_SYSINFO_KBD	0x04
#define _Ph_QUERY_SYSINFO_PTR	0x08
#define _Ph_QUERY_SYSINFO_IG	0x10

/* _Ph_QUERY subtype _Ph_PSINFO */
struct _Ph_msg_query_psinfo {
	struct _Ph_msg_hdr	hdr;
	PhConnectId_t		pid;
};

/* _Ph_QUERY subtype _Ph_QUERY_CURSOR */
struct _Ph_msg_query_cursor {
	struct _Ph_msg_hdr	hdr;
	unsigned short		ig;
};

/*
 * Photon-managed services
 *
 *	The server will route messages from _Ph_SERV_START to
 *	_Ph_SERV_END to the appropriate manager
 */

/* Service message types */
#define	_Ph_SERV_START		_Ph_SERVICE_BASE
#define _Ph_SERV_WINDOW		(_Ph_SERV_START + 0)
#define _Ph_SERV_HELP		(_Ph_SERV_START + 1)
#define _Ph_SERV_GRAFX		(_Ph_SERV_START + 2)
#define _Ph_SERV_RELAY		(_Ph_SERV_START + 3)
#define _Ph_SERV_PRINTER	(_Ph_SERV_START + 4)
#define _Ph_SERV_INTERACT	(_Ph_SERV_START + 5)
#define _Ph_SERV_KEYBOARD	(_Ph_SERV_START + 6)
#define _Ph_SERV_POINTER	(_Ph_SERV_START + 7)
#define _Ph_SERV_DND		(_Ph_SERV_START + 8)
#define _Ph_SERV_END		(_Ph_SERV_START + 0x40)

/* _Ph_FORWARD and all _Ph_SERV-type messages */
struct _Ph_msg_forward {
	struct _Ph_msg_hdr	hdr;
	PhConnectId_t		pid;
	unsigned short		len;
	/* message-specific data follows */
};

/* _Ph_SERV_GRAFX */

#define _Ph_DRAW_EXTENT		0x0001
#define	_Ph_COLOR_MATCH		0x0002
#define _Ph_STRING_EXTENT	0x0003
/* #define _Ph_HW_GET_IMAGE		0x0004 */
#define	_Ph_SET_DPMS_MODE	0x0005
#define _Ph_SYNC_FRAME_READ		0x0006
#define _Ph_FLUSH_FRAME_SHMEM	0x0007
#define _Ph_REQUEST_OFFSCREEN	0x0008
#define _Ph_HW_SYNC				0x0009
#define _Ph_BYPASS_MODE			0x000A

#define _Ph_DESTROY_OFFSCREEN   0x000B  /* Frees an Offscreen area */
#define _Ph_GET_HW_CAPS         0x000C  /* Gets the HW Capabilites of the driver */
#define _Ph_GET_VIDEO_MODE_LIST 0x000D  /* Gets the list of mode numbers available */
#define _Ph_GET_VIDEO_MODE_INFO 0x000E  /* Gets the information on a specific mode */
#define _Ph_SET_VIDEO_MODE      0x000F  /* Set the display to a specific mode */
#define _Ph_GET_VIDEO_MODE      0x001D  /* Get display information about the current mode */
#define _Ph_PLUGIN_OPEN			0x0010	/* Open up a DLL into the drivers address space */
#define	_Ph_GET_ADDRESS			0x0011	/* Get the address of an Offscreen area, must be
										   in bypassmode.  This returns an address so
										   to map it in and use it the app has to be
										   root. */
#define _Ph_DUP_OFFSCREEN		0x0012	/* Duplicate a tag */
#define _Ph_TRANSLATE_PALETTE	0x001A	/* Creates a "native" palette based on the current
										   video mode pixel format (ie: palette 
										   indexes on a palette based driver, 16 color values
										   for a 16 bit mode driver, etc) */
#define _Ph_GET_OFFSCREEN_SHMEM 0x001B  /* Get a shared memory name representing an 
										   offscreen context. */
#define _Ph_QUERY_OFFSCREEN		0x001C  /* Query for surfaces or surface information */
#define _Ph_PLUGIN_SERVICE		0x001E  /* Issue a service message meant for a rendering plugin */

/* Scaled Video output and Video Capture Service Messages */
#define _Ph_VID_CREATE_CHANNEL		0x0013
#define _Ph_VID_DESTROY_CHANNEL		0x0014
#define _Ph_SCALER_GET_CAPS			0x0015
#define _Ph_CAPTURE_GET_CAPS		0x0016	/* n/a */
#define _Ph_SCALER_CONFIG_CHANNEL	0x0017
#define _Ph_CAPTURE_CONFIG_CHANNEL	0x0019	/* n/a */
#define _Ph_VID_NEXT_FRAME			0x0018
#define _Ph_CAPTURE_GET_STATUS		0x0020	/* n/a */

#define _Ph_GET_OFFSCREEN_LOCK		0x0021	/* Register a surface lock with io-graphics */
#define _Ph_REMOVE_OFFSCREEN_LOCK	0x0022 /* Remove the lock */

/* Layers */
#define _Ph_CREATE_DRIVER_REGION    0x0023
#define _Ph_LAYER_GET_CAPS          0x0024
#define _Ph_LAYER_SET_ARGS          0x0025 /* not currently used (v6.2.1) */
#define _Ph_LAYER_SET_ARG           0x0026
#define _Ph_LAYER_CREATE_SURFACE    0x0027
#define _Ph_LAYER_SET_SURFACE       0x0028
#define _Ph_LAYER_LOCK              0x0029
#define _Ph_LAYER_UNLOCK            0x002A

/* Surface */
#define _Ph_QUERY_SURF				0x002B	/* Not currently in use */
#define _Ph_REQUEST_SURFACE_GFSID	0x002C  /* Get the gf surface id from a offscreen id */

/* PHOOK */
#define	_Ph_PHOOK_REGISTER			0x0030

/* Video Control */
#define	_Ph_HW_ZOOM			0x0040	/* Not currently in use */
#define	_Ph_HW_GAMMA		0x0041	/* Not currently in use */
#define	_Ph_OVERSCAN_CTRL	0x0042	/* Not currently in use */

#define _Ph_PRINTER_CTRL	0x00A0  /* shutdown driver [subtype = 0] */
                                    /* or query status [subtype = 1] */

/* Mode switch and miscellaneous */
#define	_Ph_GRAFX_GET_MODE	0x0077
#define	_Ph_GRAFX_RESTART	0x0078
#define _Ph_GRAFX_SYNC_FLUSH	0x0079

#define	_Ph_FONT_METRICS	0x0080	/* Not currently in use */


/* 0xE0 through 0xFF reserved for graphics driver<-->modeswitcher interactions */
/* 0x0000 through 0x0FFF are reserved by QNX for future expansion */
/* 0x1000 through 0x10FF reserved for Philips (Randy) */
/* 0x1100 through 0x11FF reserved for WTTF (Marcel) */
/* 0x1200 through 0x12FF reserved for Neon Tech (Larry )*/
/* 0x1300 through 0x13FF reserved for Grundig (becom, pk) */
/* 0x1400 through 0x14ff reserved for C&T 65554 expansion: Company AIS (see gcarr/randy) */
/* 0x1500 through 0x15ff reserved for Matrox Genesis (Linda) */

#define	_Ph_HITACHI_Q2SD_SERVICE	0x1600	/* Hitachi Q2SD/Amanda extended functionality */

/* _Ph_SERV_GRAFX type _Ph_GRAFX_GET_MODE */
struct _Ph_msg_grafx_get_mode {
	unsigned long		flags;
	char				config_name[ PATH_MAX ];
};

struct _Ph_msg_grafx_get_mode_reply {
	long				manual_mode;
};

/* _Ph_SERV_GRAFX type _Ph_GRAFX_RESTART */
struct _Ph_msg_grafx_restart {
	unsigned long		flags;
};

struct _Ph_msg_grafx_restart_reply {
	long				status;
	int					n_devices;
	struct {
		long			vid, did, deviceindex, status;
	} devices[64]; 
};

/* _Ph_SERV_GRAFX type _Ph_DRAW_EXTENT */
struct _Ph_msg_draw_extent {
	struct _Ph_msg_hdr	hdr;
	PhDrawEvent_t		event;
};

/* _Ph_SERV_GRAFX type _Ph_COLOR_MATCH */
struct _Ph_msg_color_match {
	struct _Ph_msg_hdr	hdr;
	long				num;
	PgColor_t			c[1];	
};

/* _Ph_SERV_GRAFX type _Ph_STRING_EXTENT */
struct _Ph_msg_string_extent {
	struct _Ph_msg_hdr	hdr;
	ushort_t			tflags;
	ushort_t			tlen;
	char				font[_Pg_MAX_FONT_LEN];
	long				spare[8];
	char				s[1];
};

/* _Ph_SERV_GRAFX type _Ph_SET_DPMS_MODE */
struct _Ph_msg_set_dpms_mode {
	struct _Ph_msg_hdr	hdr;
	ushort_t			mode;
};

/* _Ph_SERV_GRAFX type _Ph_HW_ZOOM */
struct _Ph_msg_hw_zoom {
	struct _Ph_msg_hdr	hdr;
	long				zoom_factor;
};

/* _Ph_SERV_GRAFX type _Ph_HW_GAMMA */
struct _Ph_msg_hw_gamma {
	struct _Ph_msg_hdr	hdr;
	unsigned long		DataValid;
/*	long				F[3];		 gamma factor	####.#### 
	long				W[3];		 white level	####.#### 
	long				B[3];		 black level	####.#### */
};

/* _Ph_SERV_GRAFX type _Ph_FONT_METRICS */
struct _Ph_msg_font_metrics {
	struct _Ph_msg_hdr	hdr;
	/*
	char fontname[0];
	*/
};

/* _Ph_SERV_GRAFX type _Ph_SYNC_FRAME_READ */
struct _Ph_msg_image_read {
	struct _Ph_msg_hdr	hdr;
	PhRect_t			where;
	_PgShmemRefStruct	mem_block;
};

/* _Ph_SERV_GRAFX type _Ph_FRAME_FLUSH */
struct _Ph_msg_frame_flush {
	struct _Ph_msg_hdr	hdr;
	_PgShmemRefStruct	mem_block;
};

/* _Ph_SERV_GRAFX type _Ph_REQUEST_OFFSCREEN */
typedef struct _Ph_Video_Request
{
	struct _Ph_msg_hdr	hdr;
	unsigned long 		width,height,bpp,flags;
} PhVideoRequest_t;

typedef union _Ph_Offscreen_msg
{
	struct {
		struct _Ph_msg_forward	forward;
		PhVideoRequest_t data;
	} send;
	
	struct {
		struct _Ph_msg_hdr hdr;
		PgVidMem_t data;
	} reply;
} PhOffScreenMsg_t;

/* _Ph_SERV_GRAFX type _Ph_BYPASS_MODE */
typedef struct _Ph_Bypass_Request
{
	struct _Ph_msg_hdr	hdr;
	pid_t				bypass_pid;
	#if defined ( __QNXNTO__ )
		pid_t	bypass_chid;
	#endif
	unsigned long		flags;
} PhBypassRequest_t;


#define PHOOK_DFLT	""
#define PHOOK_ROTATE90	"ph-rotate-90.so"
#define PHOOK_ROTATE180	"ph-rotate-180.so"
#define PHOOK_ROTATE270	"ph-rotate-270.so"

/* _Ph_SERV_GRAFX type _Ph_PHOOK_REGISTER */
#define	PHOOK_PATH_MAX	32

typedef struct _Ph_PHook_Register
{
	struct _Ph_msg_hdr	hdr;
	char				phook_path[PHOOK_PATH_MAX];
} PhPHookRegister_t;

typedef union _Ph_Bypass_msg
{
	struct 
	{
		struct _Ph_msg_forward	forward;
		PhBypassRequest_t		data;
	} send;
	
	struct
	{	
#if defined( __QNXNTO__ )
		struct _Ph_msg_hdr	hdr;
#endif
		struct 
		{
			pid_t	driver_pid;
		} data;
	} reply;
} PhBypassModeMsg_t;

/* _Ph_NOTIFY */
struct _ph_notify {
  msg_t               type;
  short int			  fd;
  struct sigevent     event;
};


/*
 * Photon replies
 */

/* Generic reply header */
struct _Ph_msg_hdr_reply {
	unsigned short	status;
	unsigned short	type;
	unsigned short	n_events;
	unsigned short	flags;
};

/*
 * Dequeued reply types
 */

/* _Ph_EVENT_MSG */
struct _Ph_msg_event_reply {
	struct _Ph_msg_hdr_reply	hdr;
	PhEvent_t					event;
};

/* _Ph_CHEVENT_MSG */
struct _Ph_msg_chevent_reply {
	struct _Ph_msg_hdr_reply	hdr;
	PhChannelEv_t				event;
};

/* _Ph_CLOSE_MSG */
struct _Ph_msg_close_reply {
	struct _Ph_msg_hdr_reply 	hdr;
	PhConnectId_t				coid;
};

/* _Ph_RESIZE_MSG */
struct _Ph_msg_resize_reply {
	struct _Ph_msg_hdr_reply	hdr;
	unsigned long				buf_len;
};

/*
 * Regular synchronous message replies
 */

/* _Ph_INIT reply */
struct _Ph_msg_init_reply {
	struct _Ph_msg_hdr_reply	hdr;
	long						id;
};

/* _Ph_REGION subtype _Ph_REGION_OPEN */
struct _Ph_msg_region_open_reply {
	struct _Ph_msg_hdr_reply	hdr;
	PhRid_t						rid;
};

/* _Ph_QUERY subtype _Ph_QUERY_RIDS reply */
struct _Ph_msg_query_rids_reply {
	struct _Ph_msg_hdr_reply	hdr;
	unsigned long				num;
	/* PhMsg_t			rids[] */
};

/* _Ph_QUERY subtype _Ph_QUERY_REGION reply */
struct _Ph_msg_query_region_reply {
	struct _Ph_msg_hdr_reply	hdr;
	PhRegion_t					info;
	/*
	 rects
	 [data]
	*/
};

/* _Ph_QUERY subtype _Ph_QUERY_PSINFO reply */
struct _Ph_msg_query_psinfo_reply {
	struct _Ph_msg_hdr_reply	hdr;
	struct _Ph_psinfo			psinfo;
};

/* _Ph_QUERY subtype _Ph_QUERY_SYSINFO reply */
struct _Ph_msg_query_sysinfo_reply {
	struct _Ph_msg_hdr_reply	hdr;
	PhSysInfo_t					info;
	/*	The actual reply can be different from the PhSysInfo_t structure
		-- it depends of the message */
};

/* _Ph_QUERY subtype _Ph_QUERY_CURSOR reply */
struct _Ph_msg_query_cursor_reply {
	struct _Ph_msg_hdr_reply	hdr;
	PhCursorInfo_t				info;
};

/* _Ph_SERV_GRAFX type _Ph_DRAW_EXTENT reply */
struct _Ph_msg_draw_extent_reply {
	struct _Ph_msg_hdr_reply	hdr;
	PhRect_t					extent;
	ushort_t					valid;
};

/* _Ph_SERV_GRAFX type _Ph_COLOR_MATCH reply */
struct _Ph_msg_color_match_reply {
	struct _Ph_msg_hdr_reply	hdr;
	PgColor_t					c[1];	
};

/* _Ph_SERV_GRAFX type _Ph_STRING_EXTENT reply */
struct _Ph_msg_string_extent_reply {
	struct _Ph_msg_hdr_reply	hdr;
	PhRect_t					extent;
	long						spare[4];
};

/* _Ph_SERV_GRAFX type _Ph_SET_DPMS_MODE reply */
struct _Ph_msg_set_dpms_mode_reply {
	struct _Ph_msg_hdr_reply	hdr;
	ushort_t			status;
};


/* _Ph_SERV_GRAFX type _Ph_HW_ZOOM reply */
struct _Ph_msg_hw_zoom_reply {
	struct _Ph_msg_hdr_reply	hdr;
};

/* _Ph_SERV_GRAFX type _Ph_HW_GAMMA reply */
struct _Ph_msg_hw_gamma_reply {
	struct _Ph_msg_hdr_reply	hdr;
};

/* _Ph_SERV_GRAFX type _Ph_FONT_METRICS reply */
struct _Ph_msg_font_metrics_reply {
	struct _Ph_msg_hdr_reply	hdr;
	PhRect_t					extent;
	ushort_t					valid;
	char						widths[256];
};

/*
 * LAYERS
 */
/* _Ph_CREATE_DRIVER_REGION */
struct _Ph_msg_create_driver_region {
    PgVidMemTag_t target;
    PhPoint_t   origin;
    PhRect_t    rect;
    PhRid_t     parent;
    unsigned    fields;
};
struct _Ph_msg_create_driver_region_reply {
    PhRid_t     rid;
};

/* _Ph_LAYER_GET_CAPS */
struct _Ph_msg_get_layer_caps {
    int     device_rid;
    int     layer;
    int     format_index;
};
struct _Ph_msg_get_layer_caps_reply {
    PgLayerCaps_t   caps;
};

/* _Ph_LAYER_SET_ARG */
struct _Ph_msg_set_layer_arg {
    int     device_rid;
    int     layer;
    int     arg;
    int     len;
};

/* _Ph_LAYER_CREATE_SURFACE */
struct _Ph_msg_create_layer_surface {
    int     device_rid;
    int     layer;
    int     surface;
    unsigned    format;
    unsigned    width;
    unsigned    height;
    unsigned    flags;
};
struct _Ph_msg_create_layer_surface_reply {
    PgVidMemDesc_t  desc;
    PhRid_t         rid;
};

/* _Ph_LAYER_SET_SURFACE */
struct _Ph_msg_set_layer_surface {
    int     device_rid;
    int     layer;
    int     surface;
    PgVidMemTag_t   tag;
    unsigned flags; /* no flags defined */
};

/* _Ph_LAYER_LOCK */
struct _Ph_msg_lock_layer {
    int     device_rid;
    int     layer;
};

/* _Ph_LAYER_UNLOCK */
struct _Ph_msg_unlock_layer {
    int     device_rid;
    int     layer;
};

struct _Ph_printer_spec {
	short pr_id;    /* printer descriptor number */
	unsigned short p_num;
	unsigned short paper_size_x,paper_size_y;
	unsigned int top_border;
	unsigned int bottom_border;
	unsigned int left_border;
	unsigned int right_border;
	unsigned int scale;
	int flags;
};

#define _Ph_LIST_PRINTERS	72
#define _Ph_QUERY_PRINTER	73
#define _Ph_START_PRINT		74
#define _Ph_FLUSH_PAGE		75
#define _Ph_END_PRINT		76
#define _Ph_OPEN_DIALOG		78

struct _Ph_msg_printer {
	struct _Ph_msg_hdr		hdr;
	struct _Ph_printer_spec	ps;
	PhRid_t					rid;
};

struct _Ph_msg_printer_reply {
	struct _Ph_msg_hdr_reply 	hdr;
	struct _Ph_printer_spec		ps;
	};

struct _Ph_msg_printer_query {
	struct _Ph_msg_hdr_reply 	hdr;
	struct _Ph_printer_spec		ps;
	char   printer_name[25];
	};


/* _Ph_NOTIFY reply */

struct _ph_notify_reply {
  msg_t               status;
};

/* _Ph_CONNECTION */
struct _Ph_msg_connection {
	struct _Ph_msg_hdr		hdr;
	unsigned long			handle;
	long					id;
	unsigned long			flags;
	char					name[ 64 ];
	};

/* _Ph_CONNECTION reply */
struct _Ph_msg_connection_reply {
	struct _Ph_msg_hdr_reply	hdr;
	long						id;
	PhConnectId_t				coid;
	int							nid;
	pid_t						pid;
	int							chid;
	unsigned long				handle;
	unsigned long				flags;
	char						name[ 64 ];
	};

/* Photon message unions */
typedef union _Ph_msg_union {
	struct _Ph_msg_hdr					hdr;
	struct _Ph_msg_emit					emit;
	struct _Ph_msg_region_open			ropen;
	struct _Ph_msg_region_set			rset;
	struct _Ph_msg_region_close			rclose;
	struct _Ph_msg_query_rids 			query_rids;
	struct _Ph_msg_query_region			query_region;
	struct _Ph_msg_forward				forward;
	struct _Ph_msg_init					init;
	struct _Ph_msg_connection			connection;
} PhMsgUnion_t;

typedef union _Ph_msg_reply_union {
	struct _Ph_msg_hdr_reply					hdr;
	struct _Ph_msg_region_open_reply			ropen;
	struct _Ph_msg_event_reply					event;
	struct _Ph_msg_query_rids_reply				query_rids;
	struct _Ph_msg_query_region_reply			query_region;
	struct _Ph_msg_connection_reply				connection;
	char byte_data[512];
} PhMsgReplyUnion_t;

#ifndef __QNXNTO__
/*
 * Message of _IO_DEVCTL
 */
struct _io_devctl {
	msg_t			type;
	unsigned short	combine_len;
	long			dcmd;
	long			nbytes;
	long			zero;
/*	char			data[nbytes]; */
};

/* struct _io_devctl combine_len */
#define _IO_DEVCTL_COMBINE_LEN	sizeof(struct _io_devctl)

struct _io_devctl_reply {
	msg_t			status;
	unsigned short	zero;
	long			ret_val;
	long			nbytes;
	long			zero2;
/*	char			data[nbytes]; */
    } ;

typedef union {
	struct _io_devctl			i;
	struct _io_devctl_reply		o;
} io_devctl_t;

#endif

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#define __PH_MSG_H_INCLUDED
#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PhMsg.h $ $Rev: 236523 $" )
#endif
