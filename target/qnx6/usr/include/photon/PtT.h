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
 * 	PtT.h	
 *		Manifests and structure definitions for the Photon widget lib
 *

 */

#ifndef __PT_T_H_INCLUDED
#define __PT_T_H_INCLUDED

#ifndef __PT_MACROS_H_INCLUDED
#include <photon/PtMacros.h>
#endif

#include <signal.h>
#include <stddef.h>

#if defined(__QNXNTO__)
	#define Pt_SUPPORT_THREADING 1
	#include <pthread.h>
	#include <spawn.h>
#else
	#define Pt_SUPPORT_THREADING 0
	#include <sys/qnx_glob.h>
#endif

#ifndef __PH_H_INCLUDED
 #include <Ph.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/* General-purpose constants */

#define Pt_NO_INTERSECTION		0
#define Pt_PARTIAL_INTERSECTION 1
#define Pt_FULL_INTERSECTION 	2 /* first within the second */

#define Pt_VERTICAL		0
#define Pt_HORIZONTAL	1

#define Pt_ALIGN_CENTER	0x2
#define Pt_ALIGN_TOP	0x10
#define Pt_ALIGN_BOTTOM	0x20
#define Pt_ALIGN_LEFT	0x40
#define Pt_ALIGN_RIGHT	0x80

/* Alignment types */
#define	Pt_LEFT						0
#define	Pt_TOP						0
#define Pt_RIGHT					1
#define Pt_BOTTOM					1
#define Pt_CENTER					2

typedef struct Pt_widget PtWidget_t;
typedef struct Pt_widget_class PtWidgetClass_t;
typedef struct Pt_widget_class_init PtWidgetClassInit_t;

/********************************************************/
/* Control surface API related structures and constants */

typedef uint16_t PtSurfaceId_t;
#define Pt_MAX_SURFACE_ID	65535

/* widget action structure.  Widgets that wish to employ control surfaces will
   contain an array of 1 or more PtWidgetAction_t's in its class record */

struct pt_surface;
struct pt_action_info;
typedef int (*PtAction_f)(PtWidget_t *, uchar_t, uchar_t, struct pt_action_info * );
typedef int (*PtSurfaceCallback_f)(PtWidget_t *, struct pt_surface *, PhEvent_t * );

typedef struct pt_widget_action
{
	long event_mask;
	union
	{
		PtAction_f action;
		PtSurfaceCallback_f raw;
	} event_f;

} PtWidgetAction_t;

typedef struct pt_action_info
{
	struct pt_surface *surface;
	PhEvent_t *event;
} PtActionInfo_t;

/* some general-purpose action state manifests */

#define Pt_ACTION_BEGIN			1	/* begin action (for example, a button press) */
#define Pt_ACTION_END			2	/* end action (for example, a button release) */
#define Pt_ACTION_CONTINUE		3	/* action continuing (for example, a button repeat) */
#define Pt_ACTION_PERFORM		4	/* perform action without cycling through intermediate states */
#define Pt_ACTION_ARM			5	/* action hasn't happened yet, but it could */

/* control surface instance structure */

typedef void (*PtSurfaceDraw_f)(PtWidget_t *, struct pt_surface *, PhTile_t * );
typedef void (*PtSurfaceCalc_f)(PtWidget_t *, struct pt_surface *, uchar_t );

typedef struct pt_surface
{
	PtSurfaceId_t surface_id;
	uint16_t flags;
	
	uint16_t npoints;
	int16_t padding;

	PhPoint_t *points;

	PtSurfaceDraw_f draw_f;

	PtSurfaceCalc_f calc_points_f;

	union
	{
		struct pt_widget_action *raw;
		struct
		{
			uint8_t action_id;
			uint8_t class_id;
			int16_t padding;

		} standard;

	} action;

} PtSurface_t;

/* "special" geometrical surface types */

#define Pt_SURFACE_ELLIPSE		1
#define Pt_SURFACE_RECT			2

/* surface flags */

#define Pt_SURFACE_CALC_VALIDITY		0x1		/* shared between surface and surface_ctrl */
#define Pt_SURFACE_RELEASE_POINTS		0x2
#define Pt_SURFACE_HIDDEN				0x4
#define Pt_SURFACE_CONSUME_EVENTS		0x8
#define Pt_SURFACE_DISABLED				0x10
#define Pt_SURFACE_RAW					0x20
#define Pt_SURFACE_USE_ORIGIN			0x8000
#define Pt_SURFACE_PARENT_RELATIVE		0x4000

/* surface control structure.  Instances of widgets that use control surfaces will contain a
   pointer to a valid PtSurfaceCtrl_t */
   
typedef struct pt_surface_ctrl
{
	uint16_t nsurfaces;
	uint16_t next_surface_id;

	PtSurfaceId_t active_surface;
	uint16_t flags;

	PtSurface_t *surfaces;

} PtSurfaceCtrl_t;

/* surface_ctrl flags */
/* also uses Pt_SURFACE_CALC_VALIDITY (see above) */

#define Pt_SURFACE_POST_EXTENT_CALC		0x2

/* surface API flags */

#define Pt_DAMAGE_SURFACE				0x1

/********************************************************/

typedef struct Pt_widget_class_ref{
	PtWidgetClass_t *wclass;
	PtWidgetClass_t * (*init)(void);
	int				id;
} PtWidgetClassRef_t;

/*
 * General-purpose structures
 */

typedef struct Pt_arg_entry {
	long				type;
	long				value;
	long				len;
} PtArg_t;

typedef struct {
	long		type;
	void const	*value;
} PtClassArg_t;


typedef struct Pt_callback_info {
	unsigned long		reason;
	unsigned long		reason_subtype;
	PhEvent_t 			*event;
	void				*cbdata;
} PtCallbackInfo_t;

typedef struct Pt_callback {
	int			(*event_f)( PtWidget_t *, void *, PtCallbackInfo_t * );
	void			*data;
} PtCallback_t;

typedef struct Pt_callback_list {
	struct Pt_callback_list		*next;
	PtCallback_t				cb;
} PtCallbackList_t;

typedef struct Pt_balloon_callback {
	PtWidget_t			*widget;
	void		(*event_f)( PtWidget_t *, void *, PtCallbackInfo_t * );
} PtBalloonCallback_t;

typedef int PtCallbackF_t( PtWidget_t *widget, void *data, PtCallbackInfo_t *cbinfo );

/* Reason Codes passed to callback in PtCallbackInfo_t parm. */
#define Pt_INFLATE_BALLOON	0
#define Pt_POP_BALLOON		1

typedef struct Pt_balloon_callback_list {
	struct Pt_balloon_callback_list		*next;
	PtBalloonCallback_t			cb;
} PtBalloonCallbackList_t;

typedef struct Pt_hotkey_callback {
	unsigned short		key_sym_cap;
	short				flags;
	unsigned long		key_mods;
	PtWidget_t			*widget;
	void 				*data;
	int					(*event_f)( PtWidget_t *, void *, PtCallbackInfo_t * );
} PtHotkeyCallback_t;
/* Hotkey flags... */
#define Pt_HOTKEY_SYM 					0x0001
#define Pt_HOTKEY_IGNORE_MODS 	0x0002
#define Pt_HOTKEY_CHAINED			0x8000

typedef struct Pt_hotkey_callback_list {
	struct Pt_hotkey_callback_list		*next;
	PtHotkeyCallback_t			cb;
} PtHotkeyCallbackList_t;

typedef struct Pt_raw_callback {
	unsigned long	event_mask;
	int				(*event_f)( PtWidget_t *, void *, PtCallbackInfo_t * );
	void			*data;
} PtRawCallback_t;

typedef struct Pt_raw_callback_list {
	struct Pt_raw_callback_list		*next;
	PtRawCallback_t  				cb;
} PtRawCallbackList_t;

typedef struct Pt_app_callback {
	int					(*event_f)( void *, PtCallbackInfo_t * );
	void 				*data;
} PtAppCallback_t;

typedef struct Pt_app_callback_list {
	struct Pt_app_callback_list		*next;
	PtAppCallback_t			cb;
} PtAppCallbackList_t;

typedef struct Pt_app_raw_callback {
	unsigned long	event_mask;
	int				(*event_f)( void *, PtCallbackInfo_t * );
	void			*data;
} PtAppRawCallback_t;

typedef struct Pt_app_raw_callback_list {
	struct Pt_app_raw_callback_list		*next;
	PtAppRawCallback_t  				cb;
} PtAppRawCallbackList_t;

typedef struct Pt_app_hotkey_callback {
	unsigned short		key_sym_cap;
	short				flags;
	unsigned long		key_mods;
	void 				*data;
	int					(*event_f)( void *, PtCallbackInfo_t * );
} PtAppHotkeyCallback_t;

typedef struct Pt_app_hotkey_callback_list {
	struct Pt_app_hotkey_callback_list		*next;
	PtAppHotkeyCallback_t			cb;
} PtAppHotkeyCallbackList_t;

typedef struct Pt_class_raw_callback {
	unsigned long	ev_mask;
	int				(*ev_f)( PtWidget_t *, PhEvent_t * );
	unsigned long	ev_extra;
} PtClassRawCallback_t;

typedef struct Pt_callback_lists {
	unsigned short	reserved;	/* not used */
	unsigned short	n_links;	/* number of entries in the link array */
	struct pt_callback_link {
		long	cb_type;	/* callback/resource type */
		void	*list;		/* pointer to a linked list of callbacks */
	} *link;
} PtCallbackLists_t;

typedef struct Pt_widget_list {
	struct Pt_widget_list	*next;
	PtWidget_t				*widget;
	int 					flags;
} PtWidgetList_t;

typedef struct Pt_blocked_list PtBlockedList_t;

typedef struct Pt_modal_ctrl {
	int flags;
	void *result;
	#if Pt_SUPPORT_THREADING
		pthread_cond_t *cond;
		struct Pt_modal_ctrl *next, **prevp;
	#endif
	unsigned reserved[ 2 ];
} PtModalCtrl_t;


/* Used by PtNotice(), PtPrompt(), PtAlert() and PtPassword (note that these values must
   not conflict with Pt_LEFT, Pt_CENTER or Pt_RIGHT as defined in PtLabel.h) */

#define Pt_WAIT			0x4		/* do not return until dialog is dismissed */
#define Pt_ESC_DISABLE	0x8		/* do not dismiss dlg by ESC keypress */
#define Pt_RELATIVE		0x10	/* position relative to parent if not NULL */
#define Pt_MULTITEXT	0x20	/* use multiline text widget for PtPrompt only */
#define Pt_BLOCK_PARENT	0x40	/* block parent window only */
#define Pt_BLOCK_ALL	0x80	/* block all app windows (overrides Pt_BLOCK_PARENT) */
#define Pt_MODAL		(Pt_WAIT | Pt_BLOCK_ALL)

/* return manifests for PtPassword() */

#define Pt_PWD_ACCEPT	0
#define Pt_PWD_CANCEL	1
#define Pt_PWD_RETRY	2
#define Pt_PWD_REJECT	3

typedef int PtDataRemoveF_t( const int type, const int subtype, void * const data, const unsigned int len );

typedef struct pthetdata PtDataHdr_t;
struct pthetdata 
	{
	long type, subtype;
	PtDataHdr_t *next;
	void *data;
	unsigned int len;
	PtDataRemoveF_t *remove;
	};


/*
 *
 * Interface to PtSetStruct
 *
 */
	
#define Pt_ARG_OFFSET_MASK			0x00007FFF
/*#define Pt_ARG_MODE_MASK			0x003F0000 */
#define Pt_ARG_MODE_MASK			0x000F0000
#define Pt_ARG_EXTENDED_TYPES_MASK	0x00300000
#define Pt_ARG_SIZE_MASK			0xFFC00000
#define Pt_ARG_SIZE_SHIFT			22
#define Pt_ARG_EXTENDED_SHIFT		20

#define Pt_CHANGE_INVISIBLE			NULL
#define Pt_CHANGE_REDRAW			((void(*)(PtWidget_t*,PtArg_t const*,PtResourceRec_t const*)) -1)
#define Pt_CHANGE_RESIZE			((void(*)(PtWidget_t*,PtArg_t const*,PtResourceRec_t const*)) -2)
#define Pt_CHANGE_REBUILD			((void(*)(PtWidget_t*,PtArg_t const*,PtResourceRec_t const*)) -3)
#define Pt_CHANGE_INTERIOR			((void(*)(PtWidget_t*,PtArg_t const*,PtResourceRec_t const*)) -4)
#define Pt_CHANGE_RESIZE_REDRAW		((void(*)(PtWidget_t*,PtArg_t const*,PtResourceRec_t const*)) -5)
#define Pt_CHANGE_PREVENT			((void(*)(PtWidget_t*,PtArg_t const*,PtResourceRec_t const*)) -6)
#define Pt_CHANGE_CANVAS			((void(*)(PtWidget_t*,PtArg_t const*,PtResourceRec_t const*)) -7)
#define Pt_CHANGE_CANVAS_REDRAW		((void(*)(PtWidget_t*,PtArg_t const*,PtResourceRec_t const*)) -8)
#define Pt_KEEP						((void(*)(PtWidget_t*,PtArg_t const*,PtResourceRec_t const*)) -10)
#define Pt_CHANGE_SENSITIVITY			((void(*)(PtWidget_t*,PtArg_t const*,PtResourceRec_t const*)) -10)

#define Pt_QUERY_PREVENT			((int(*)(PtWidget_t*,PtArg_t*,PtResourceRec_t const*)) -1)

#define Pt_ARG_SIZE( x )			( (long)x << Pt_ARG_SIZE_SHIFT )

#define Pt_ARG_PARM( x )			( (long)x << Pt_ARG_SIZE_SHIFT )
/* deprecated--^ use Pt_ARG_SIZE */

#define _Pt_SET_PTR( base, arg ) ( (char *)base + ( arg & Pt_ARG_OFFSET_MASK ) )
#define _Pt_GET_SIZE( type )	 ( ( type & Pt_ARG_SIZE_MASK ) >> Pt_ARG_SIZE_SHIFT )

#define _Pt_GET_EXTENDED_TYPE( arg ) (arg & Pt_ARG_EXTENDED_TYPES_MASK)

#define _Pt_GET_PARM( type )	 ( ( type & Pt_ARG_SIZE_MASK ) >> Pt_ARG_SIZE_SHIFT )
/*deprecated --^, use Pt_GET_SIZE */

#define	Pt_ARG_IN_WIDGET			0x00000000
#define Pt_ARG_IN_EXDATA			0x00100000

/*
 * Pt_ARG_MODE_CHAR, SHORT, LONG and INT:
 *	assign arg->value to structure member if arg->len == 0
 *	otherwise treat arg->len as a bitmask 
 */
#define Pt_ARG_MODE_CHAR			0x00010000
#define Pt_ARG_MODE_SHORT			0x00020000
#define Pt_ARG_MODE_LONG			0x00030000
#define Pt_ARG_MODE_INT			Pt_ARG_MODE_LONG

/*#define PtGlobalFocusPrev( a, e ) PtGlobalFocusPrevFrom( PtContainerFindFocus( a ), e ) */
/*#define PtGlobalFocusNext( a, e ) PtGlobalFocusNextFrom( PtContainerFindFocus( a ), e ) */

/*
 * Pt_ARG_MODE_CHAR_FLAGS, SHORT_FLAGS and LONG_FLAGS:
 *	assign arg->value to structure member if arg->len == 0
 *	otherwise treat arg->len as a bitmask 
 */
#define Pt_ARG_MODE_CHAR_FLAGS		0x00040000
#define Pt_ARG_MODE_SHORT_FLAGS		0x00050000
#define Pt_ARG_MODE_LONG_FLAGS		0x00060000
/*
 * Pt_ARG_MODE_PTR
 *	assign ptr to structure member
 */
#define Pt_ARG_MODE_PTR				0x00070000
/*
 * Pt_ARG_MODE_BOOLEAN
 *	assign boolean variable, length member is bit mask.
 */
#define Pt_ARG_MODE_BOOLEAN			0x00080000

/*
 * Pt_ARG_MODE_STRUCT
 *	copy SIZE bytes from (char *)arg->value into structure at offset
 */
#define Pt_ARG_MODE_STRUCT			0x00090000

#define Pt_ARG_MODE_VARIABLE		0x00090000
/*deprecated --^ */

/*
 * Pt_ARG_MODE_ALLOC
 *	allocate arg->len bytes at assign ptr to structure member
 *	copy arg->len bytes from (char *)arg->value to ptr
 */
#define Pt_ARG_MODE_ALLOC			0x000A0000

/*
 * Pt_ARG_MODE_STRALLOC
 *	same as Pt_ARG_MODE_ALLOC but length is determined by taking
 *	length of string referred to by (char *)arg->value... + 1
 */
#define Pt_ARG_MODE_STRING			0x000B0000

#define Pt_ARG_MODE_STRALLOC		0x000B0000
/*deprecated --^ */

/*
 * Pt_ARG_MODE_ARRAY
 *	alloc but with length * ARG_SIZE
 *	next unsigned receives length
 */
#define Pt_ARG_MODE_ARRAY			0x000C0000

/*
 * Pt_ARG_MODE_CALLBACK_LIST
 *	structure member is a pointer to first member of a linked list of
 *  callback
 *	first item in linked list must be ptr to next item
 *	SIZE is length of data following the "next" member.
 */
#define Pt_ARG_MODE_CALLBACK_LIST	0x000D0000
#define Pt_ARG_MODE_LINKED			Pt_ARG_MODE_CALLBACK_LIST
/*
 * Pt_ARG_MODE_CALLBACKS
 *	linked list of callbacks
 */
#define Pt_ARG_MODE_CALLBACKS		(Pt_ARG_MODE_LINKED | Pt_ARG_SIZE( sizeof( PtCallback_t ) ) )

/*
 * Pt_ARG_MODE_IMAGE
 *	structure member is a pointer to PhImage_t structure
 */
#define Pt_ARG_MODE_IMAGE			0x000E0000

/*
 * Pt_ARG_MODE_COLOR
 *	structure member is a PgColor_t
 */
#define Pt_ARG_MODE_COLOR			0x000F0000

/*
 * Pt_ARG_IN_EXDATA
 *  Modifier which indicates the resource resides
 *	in the widget extended resources block.
 *
 * defined earlier as... Pt_ARG_IN_EXDATA
 */
/*
 * length argument for Pt_ARG_MODE_LINKED
 */
#define Pt_LINK_INSERT				-1
#define Pt_LINK_DELETE				-2

typedef struct Pt_linked_list
{
	struct Pt_linked_list *next;
	char data[1];
} PtLinkedList_t;

/*
 *
 * Some Manifests to make changes to header file types less bothersome.
 * ( don't need to remember to change the widget resource definition
 *   in the class creation function if you use these :-)
 *
 */
#define Pt_STRUCT_SIZEOF( type, field ) sizeof( ( (type*) 0 ) -> field )
#define Pt_PTR_SIZEOF( type, field ) sizeof( * ( (type*) 0 ) -> field )

#define Pt_ARG_IS_NUMBER( type, field ) \
		(	(	Pt_STRUCT_SIZEOF( type, field ) == sizeof(long)			\
				?	Pt_ARG_MODE_LONG									\
				:	Pt_STRUCT_SIZEOF( type, field ) == sizeof(short)	\
					?	Pt_ARG_MODE_SHORT								\
					:	Pt_ARG_MODE_CHAR								\
				)														\
		|	offsetof( type, field ) 									\
			)

#define Pt_ARG_IS_FLAGS( type, field ) \
		(	(	Pt_STRUCT_SIZEOF( type, field ) == sizeof(long)			\
				?	Pt_ARG_MODE_LONG_FLAGS								\
				:	Pt_STRUCT_SIZEOF( type, field ) == sizeof(short)	\
					?	Pt_ARG_MODE_SHORT_FLAGS							\
					:	Pt_ARG_MODE_CHAR_FLAGS							\
				)														\
		|	offsetof( type, field ) 									\
			)

#define Pt_ARG_IS_POINTER( type, field ) \
		(	Pt_ARG_MODE_PTR				\
		|	offsetof( type, field ) 	\
			)

#define Pt_ARG_IS_ALLOC( type, field ) \
		(	Pt_ARG_MODE_ALLOC			\
		|	offsetof( type, field ) 	\
			)

#define Pt_ARG_IS_STRUCT( type, field ) \
		(	Pt_ARG_MODE_STRUCT \
		|	offsetof( type, field ) \
		|	Pt_ARG_SIZE( Pt_STRUCT_SIZEOF( type, field ) ) \
			)

#define Pt_ARG_IS_IN_CB_LISTS( type )	\
		( Pt_ARG_MODE_CALLBACK_LIST | Pt_ARG_SIZE( sizeof( type ) ) )
		
#define Pt_ARG_IS_CALLBACK_LIST( type, field ) \
		(	Pt_ARG_MODE_CALLBACK_LIST | offsetof( type, field )\
		| 	Pt_ARG_SIZE( Pt_PTR_SIZEOF( type, field ) - sizeof(void*) ) )

#define	Pt_ARG_IS_LINK	Pt_ARG_IS_CALLBACK_LIST

#define Pt_ARG_IS_ARRAY( type, field ) \
		(	Pt_ARG_MODE_ARRAY \
		|	offsetof( type, field ) \
		|	Pt_ARG_SIZE( Pt_PTR_SIZEOF( type, field ) ) \
			)

#define Pt_ARG_IS_STRING( type, field ) \
		(	Pt_ARG_MODE_STRING \
		|	offsetof( type, field ) \
			)

#define Pt_ARG_IS_BOOLEAN( type, field ) \
		(	Pt_ARG_MODE_BOOLEAN \
		|	offsetof( type, field ) \
		|	Pt_ARG_SIZE( Pt_STRUCT_SIZEOF( type, field ) ) \
			)
			
#define Pt_ARG_IS_IMAGE( type, field ) \
		(	Pt_ARG_MODE_IMAGE \
		|	offsetof( type, field ) \
			)

#define Pt_ARG_IS_COLOR( type, field ) \
		(	Pt_ARG_MODE_COLOR \
		|	offsetof( type, field ) \
			)

/*
 *
 * Miscellaneous manifests
 *
 */


/* 
 * Arg types for creating widget classes 
 */
#define Pt_SET_IN_STYLE				0x00100000
#define Pt_SET_IN_CLASSINIT			0x00200000
#define Pt_SET_VERSION				(Pt_ARG_IS_NUMBER(PtWidgetClassInit_t,version) | Pt_SET_IN_CLASSINIT)
#define Pt_SET_STATE_LEN			Pt_ARG_IS_NUMBER(PtWidgetClass_t,state_len)
#define Pt_SET_EX_STATE_LEN			(Pt_ARG_IS_NUMBER(PtWidgetClassInit_t,new_ex_len) | Pt_SET_IN_CLASSINIT)
#define Pt_SET_DFLTS_F				Pt_ARG_IS_POINTER(PtWidgetClass_t,dflts_f)
#define Pt_SET_CONNECT_F			Pt_ARG_IS_POINTER(PtWidgetClass_t,connect_f)
#define Pt_SET_EXTENT_F				(Pt_ARG_IS_POINTER(PtWidgetClassStyle_t,sizing_f) | Pt_SET_IN_STYLE )
#define Pt_SET_SIZING_F				(Pt_ARG_IS_POINTER(PtWidgetClassStyle_t,sizing_f) | Pt_SET_IN_STYLE )
#define Pt_SET_INIT_F				Pt_ARG_IS_POINTER(PtWidgetClass_t,init_f)
#define Pt_SET_DRAW_F     			(Pt_ARG_IS_POINTER(PtWidgetClassStyle_t,draw_f) | Pt_SET_IN_STYLE )
#define Pt_SET_UNREALIZE_F			Pt_ARG_IS_POINTER(PtWidgetClass_t,unrealize_f)
#define Pt_SET_REALIZED_F			Pt_ARG_IS_POINTER(PtWidgetClass_t,realized_f)
#define Pt_SET_DESTROY_F			Pt_ARG_IS_POINTER(PtWidgetClass_t,destroy_f)
#define Pt_SET_SYNC_F				Pt_ARG_IS_POINTER(PtWidgetClass_t,syncwidget_f)
#define Pt_SET_CALC_REGION_F		Pt_ARG_IS_POINTER(PtWidgetClass_t,calc_region_f)
#define Pt_SET_FLAGS				Pt_ARG_IS_FLAGS(PtWidgetClass_t,flags)
#define Pt_SET_RAW_CALLBACKS		Pt_ARG_IS_POINTER(PtWidgetClass_t,callbacks)
#define Pt_SET_NUM_CALLBACKS		Pt_ARG_IS_NUMBER(PtWidgetClass_t,num_callbacks)
#define Pt_SET_RESOURCES			(Pt_ARG_IS_POINTER(PtWidgetClassInit_t,resources) | Pt_SET_IN_CLASSINIT)
#define Pt_SET_NUM_RESOURCES		(Pt_ARG_IS_NUMBER(PtWidgetClassInit_t, num_resources) | Pt_SET_IN_CLASSINIT)
#define Pt_SET_EXTRA_RESOURCES		(Pt_ARG_IS_POINTER(PtWidgetClassInit_t,extra_resources) | Pt_SET_IN_CLASSINIT)
#define Pt_SET_NUM_EXTRA_RESOURCES	(Pt_ARG_IS_NUMBER(PtWidgetClassInit_t, num_extra_resources) | Pt_SET_IN_CLASSINIT)
#define Pt_SET_INHERITED_EX_LEN		(Pt_ARG_IS_NUMBER(PtWidgetClassInit_t,inherited_ex_len) | Pt_SET_IN_CLASSINIT)
#define Pt_SET_INHERITED_RESOURCES	(Pt_ARG_IS_POINTER(PtWidgetClassInit_t, inherited_resources) | Pt_SET_IN_CLASSINIT)
#define Pt_SET_SETRESOURCES_F		Pt_ARG_IS_POINTER(PtWidgetClass_t,setres_f)
#define Pt_SET_GETRESOURCES_F		Pt_ARG_IS_POINTER(PtWidgetClass_t,getres_f)
#define Pt_SET_DESCRIPTION			Pt_ARG_IS_POINTER(PtWidgetClass_t, description)
#define Pt_SET_ACTIONS				Pt_ARG_IS_POINTER(PtWidgetClass_t,actions)
#define Pt_SET_NUM_ACTIONS			Pt_ARG_IS_NUMBER(PtWidgetClass_t,num_actions)
#define Pt_SET_CALC_BORDER_F		(Pt_ARG_IS_POINTER(PtWidgetClassStyle_t,calc_border_f)|Pt_SET_IN_STYLE)

/*
 * Widget drawing modes (PtDrawClippedWidget)
 */
#define Pt_DRAW_DEFAULT			0x0000
#define Pt_DRAW_OVERWRITE		0x0001
#define Pt_DRAW_RAW				0x0002
#define Pt_DRAW_START			0x0003
#define Pt_DRAW_COPY_RECTS		0x0010

#define Pt_DRAW_MODE_MASK		0x000F

/*
 * Return codes for chained functions (raw callbacks,realize_f's,etc.)
 */
#define Pt_CONTINUE					0
#define Pt_HALT						1
#define Pt_END						2
#define Pt_PASS_END					3

#define Pt_PROCESS					0
#define Pt_IGNORE					1
#define Pt_CONSUME					2

#define	Pt_INIT						10
#define	Pt_MOVE						11
#define	Pt_DONE						12

/* 
 * Boolean flags 
 */
#define Pt_TRUE						-1
#define Pt_FALSE					0


/*
 * "Generally useful flags"
 */
#define Pt_NEVER					0x00
#define Pt_ALWAYS					0x01
#define Pt_AS_REQUIRED				0x02
#define Pt_INITIAL					0x04

#define Pt_DYNAMIC					0
#define Pt_BLIT						0xFFFF
#define Pt_BLIT_FORCE				0xFFFE

/*
 * for PtHasCustody()...(return values)
 */
#define Pt_IMMEDIATE_CHILD		1
#define Pt_SUBORDINATES_CHILD	2
/*
 *  Flags and values for PtWidgetTree* ( (D)irection flag )
 */
/* reserved bits            0x0000000F */
#define Pt_TRAVERSE_START	0
#define Pt_TRAVERSE_DONE	0
#define Pt_TRAVERSE_ROOT	0x00000001
#define Pt_TRAVERSE_LAST	0x00000002
#define Pt_TRAVERSE_BACK	0x00000004
#define Pt_TRAVERSE_FORCE	0x00000008 

/*
 * Widget specific colors
 */
 
#define	Pt_WINDOWACTIVECOLOR		PgRGB(0, 128, 112)
#define	Pt_BALLOONCOLOR				PgRGB( 254, 255, 177 )

#define Pt_DEFAULT_COLOR			(-3)
#define Pt_INHERIT_COLOR			(-4)

#define Pt_DEFAULT_FONT				((char *)0)
#define Pt_INHERIT_FONT				((char *)-1)


/*
 *
 * Resources
 *
 */

/* 
 * Macro to order resource number allocation
 *	Pt_RESOURCE( unsigned level, unsigned index )
 */
#define Pt_RESOURCE_RANGE		1000
#define Pt_RESOURCE( a, b )		( Pt_RESOURCE_RANGE * a + b )
#define Pt_CONTRIB( a )		( 1000 + a )
#define Pt_USER( a )		( 5000 + a )
#define Pt_RTIME( a )		( 11000 + a )

/*
 * reserved resource value for indicating widget version #
 * { Pt_VERSION, 11, 0, 0, 0} (must be first resource of widget
 * to be recognized.  If this record is present, it indicates
 * how this widget's resources are to be handled.  If absent
 * the resources are treated as Photon 1.0 release widget resources.
 */
#define Pt_VERSION			1


/*
 * The resource record 
 */
typedef struct Pt_resource_rec {
	unsigned long			type;
	void				(*mod_f)( PtWidget_t *, PtArg_t const *, struct Pt_resource_rec const * );
	int					(*query_f)( PtWidget_t *, PtArg_t *, struct Pt_resource_rec const * );
	unsigned long			arg_value;
	unsigned long			arg_len;
} PtResourceRec_t;

/*
 * The resource record, a version with no pointers
 */
typedef struct Pt_resource_rec_no_ptr {
	unsigned long			type;
	intptr_t				mod_f;
	intptr_t				query_f;
	unsigned long			arg_value;
	unsigned long			arg_len;
} PtResourceRecNoPtr_t;


#define Pt_STYLE_DRAW		0
#define Pt_STYLE_EXTENT		1
#define Pt_STYLE_ACTIVATE	2
#define Pt_STYLE_CALC_BORDER 3
#define Pt_STYLE_CALC_OPAQUE 4
#define Pt_STYLE_DEACTIVATE 5
#define Pt_STYLE_DATA	6
#define Pt_STYLE_NAME	7
#define Pt_STYLE_USAGE_COUNT	8

typedef struct {
	int method_index;
	void *func;
	} PtStyleMethods_t;

	typedef struct pt_widget_class_style 
PtWidgetClassStyle_t;
	struct pt_widget_class_style {
	char	*style_name;
	void	(*activate_f)(PtWidget_t *widget, PtWidgetClassStyle_t *old_style );
	void	(*sizing_f)( PtWidget_t * );
	void	(*calc_border_f)( PtWidget_t const *widget, PhRect_t *border );
	void	(*calc_opaque_f)(PtWidget_t *widget );
	void	(*draw_f)( PtWidget_t *widget, PhTile_t const *damage );
	void	(*deactivate_f)(PtWidget_t *widget, PtWidgetClassStyle_t *new_style );
	void	*style_data;
	int		usage_count;
	void	(*calc_dim_f)( PtWidget_t *widget, const PhDim_t *hint, PhDim_t *dim );
	int		(*set_area_f)( PtWidget_t *widget, const PhPoint_t *pos, const PhDim_t *dim );	
	};

/*
 * Base widget class structure
 */
struct Pt_resource_range;

struct Pt_widget_class_init {
	PtResourceRec_t const		*resources;
	PtResourceRecNoPtr_t const	*extra_resources;
	short						version;
	unsigned short				num_resources;
	unsigned short				num_extra_resources;
	short						reserved;
	long const					*inherited_resources;
	unsigned					new_ex_len;
	unsigned					inherited_ex_len;
	};

struct Pt_widget_class {
	char					*description;
	struct Pt_widget_class	*superclass;
	PtWidgetClassRef_t		*class_ref;
	unsigned				class_len;
	unsigned 				state_len;
	unsigned long			flags;
	void					(*dflts_f)( PtWidget_t * );
	int						(*init_f)( PtWidget_t * );
	int						(*connect_f)( PtWidget_t * );
	void					(*unrealize_f)( PtWidget_t * );
	void					(*destroy_f)( PtWidget_t * );
	void					(*realized_f)( PtWidget_t * );
	PtClassRawCallback_t const *callbacks;
	int						(*setres_f)( PtWidget_t *, int, PtArg_t const *, PtResourceRec_t const *rrec );
	int						(*getres_f)( PtWidget_t const *, int, PtArg_t * );
	unsigned int			ex_state_len;
	struct Pt_resource_range *res_ranges;
	void					(*syncwidget_f)( PtWidget_t *widget );
	int						(*calc_region_f)( PtWidget_t *, unsigned int *, PhRegion_t *, PhRect_t * );
	PtResourceRec_t const	**res_all;
	unsigned short			res_nranges;
	unsigned char			num_actions;
	unsigned char			num_callbacks;
	PtWidgetAction_t		*actions;
	unsigned short			max_style_index;
	unsigned short			res_nall;
	PtWidgetClassStyle_t	**styles;
	unsigned				reserved[ 5 ];
};


/* Flags for PtWidgetClass_t */
#define	Pt_CONTAINER				0x00000001	/* Children should be drawn within */
#define Pt_RECTANGULAR				0x00000002	/* If filled, is opaque */
#define Pt_DISCONTINUOUS			Pt_DISJOINT
#define Pt_UNUSED					0x0000313C
#define Pt_FORCE_UNREALIZE			0x00000040
#define Pt_DISJOINT					0x00000080	/* menus/windows (co-ords irrelevant) */
#define Pt_UNCLEAN_RESOURCES		0x00000200
#define Pt_NO_INHERITED_RESOURCES	0x00000400
#define Pt_HAS_DC					0x00000800
#define Pt_BASIC					0x00004000 /* indicates widget is PtBasic or subclass */
#define Pt_FORCE_SYNC				0x00008000 /* Indicates widgets must be sized (extented) */
									/*  if the Pt_WIDGET_RESIZE flag is set during a set resource */
									/* regardless of the widgets realized state. */

typedef int PtRegCallbackProcF_t(void *data, PhConnectId_t client, void *fwd_msg, size_t msg_len, int type );
typedef int PtInputCallbackProcF_t(void *, int, void *, size_t);
typedef int PtWorkProcF_t(void *);
typedef int PtSignalProcF_t(int, void *);
typedef int PtChannelEventHandlerF_t( PhChannelEv_t const *chev, void const *evdata, void *usrdata );

typedef PtRegCallbackProcF_t *PtRegCallbackProc_t;
typedef PtInputCallbackProcF_t *PtInputCallbackProc_t;
typedef PtWorkProcF_t *PtWorkProc_t;
typedef PtSignalProcF_t *PtSignalProc_t;
typedef PtChannelEventHandlerF_t *PtChannelEventHandler_t;

typedef struct Pt_reg PtRegId_t;
typedef struct Pt_input PtInputId_t;
typedef struct Pt_channel_event_handler_id PtChannelEventHandlerId_t;
typedef struct Pt_work PtWorkProcId_t;

#if defined(__QNXNTO__)
	typedef struct sigevent PtPulseMsg_t;
#else
	typedef pid_t PtPulseMsg_t;
#endif

typedef struct Pt_pulse_msg_id PtPulseMsgId_t;

typedef struct Pt_AppContext *PtAppContext_t;

#define Pt_EVENT_PROCESS_ALLOW   1
#define Pt_EVENT_PROCESS_PREVENT 2
#define Pt_DELAY_EXIT            4
#define Pt_QUIT_MAIN_LOOP        8

/* PtAppAddFd() flags */
#if defined(__QNXNTO__)
	#define Pt_FD_READ		0x10000000
	#define Pt_FD_WRITE		0x20000000
	#define Pt_FD_OBAND		0x40000000
	#define Pt_FD_NOPOLL	0x00000000
	#define Pt_FD_DRAIN		0x00000001
#else
	#define Pt_FD_READ		0x1
	#define Pt_FD_WRITE		0x2
	#define Pt_FD_OBAND		0x4
	#define Pt_FD_NOPOLL	0x8
	#define Pt_FD_DRAIN		0x0
#endif

/* typedefs for PtSpawn() */
#if defined(__QNXNTO__)
	typedef struct {
		struct inheritance options;
		int iov[ 10 ];
		unsigned reserved;
		}
			PtSpawnOptions_t;
#else
	typedef struct _qnx_spawn_globs PtSpawnOptions_t;
#endif

extern const PtSpawnOptions_t PtSpawnDefaults;

typedef void PtSpawnCbF_t( void *data, int status );

extern PtSpawnCbF_t PtSpawnNoCb;

typedef struct PtSpawnCbId PtSpawnCbId_t;

/* The widget lib control structure */
struct _Pt_sellist;
struct _Pt_evlist;
struct _Pt_class_ctrl
{
	int const	*class_id;
	int			num_class;
	void 		(*class_create_f)(int id, PtWidgetClassRef_t *, void *);
	void 		*data;		
};


/**** defines for PtCreateWidget (parent widget parm) ****/
#define Pt_NO_PARENT	((PtWidget_t *)1)
#define Pt_DEFAULT_PARENT	((PtWidget_t *)2)
#define Pt_DFLT_PARENT	Pt_DEFAULT_PARENT

typedef struct
{
	PtWidget_t *parent;			/* parent of dialog */
	PtWidget_t *pane;			/* for dialog content (will be set by function) */
	char const *title;			/* dialog title */
	char const **buttons;		/* button text */
	char const **btn_fonts;		/* button fonts */
	uint8_t nbtns;				/* number of buttons */
	uint8_t padding[3];
	int8_t def_btn;				/* default button */
	int8_t esc_btn;				/* button bound to ESC keypress */
	uint16_t width;				/* minimum width of dialog */
	int (*callback)(int,void*);	/* callback */
	void *data;					/* callback data */

} PtDialogInfo_t;

#ifdef __cplusplus
};


	inline void
	(PtSetArg)( PtArg_t *_arg, ulong_t _type, ulong_t _value, ulong_t _len )
		{
		_arg->type = _type;
		_arg->value = _value;
		_arg->len = _len;
		}
#endif

#include <photon/PhPackPop.h>

#include <photon/PtProto.h>
#include <photon/PiProto.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtT.h $ $Rev: 219996 $" )
#endif
