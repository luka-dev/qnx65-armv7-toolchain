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
 *	PtContainer.h
 *		Header file for the PtContainer widget class
 *

 */
#ifndef __PT_CONTAINER_H_INCLUDED
#define __PT_CONTAINER_H_INCLUDED

#ifndef __PT_BASIC_H_INCLUDED
 #include <photon/PtBasic.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtContainer public
 */

extern PtWidgetClassRef_t *PtContainer;

#define Pt_CONTAINER_ID	10

/* Resources */
#define Pt_ARG_FOCUS			Pt_RESOURCE( 10, 2 )
#define Pt_CB_RESIZE			Pt_RESOURCE( 10, 3 )
#define Pt_CB_BALLOONS			Pt_RESOURCE( 10, 4 )
#define Pt_ARG_CONTAINER_FLAGS  Pt_RESOURCE( 10, 5 )
#define Pt_ARG_TITLE			Pt_RESOURCE( 10, 7 )
#define Pt_ARG_TITLE_FONT			Pt_RESOURCE( 10, 8 )
#define Pt_CB_CHILD_ADDED_REMOVED	Pt_RESOURCE( 10, 9 )
#define Pt_ARG_CURSOR_OVERRIDE		Pt_RESOURCE( 10, 10 )
#define Pt_ARG_LAYOUT				Pt_RESOURCE( 10, 11 )
#define	Pt_ARG_LAYOUT_INFO			Pt_RESOURCE( 10, 12 )
#define Pt_ARG_GET_CHILD_F			Pt_RESOURCE( 10, 13 )
#define	Pt_CB_LAYOUT				Pt_RESOURCE( 10, 14 )
#define	Pt_ARG_LAYOUT_TYPE			Pt_RESOURCE( 10, 15 )
#define	Pt_ARG_FILL_LAYOUT_INFO		Pt_RESOURCE( 10, 16 )
#define	Pt_ARG_ROW_LAYOUT_INFO		Pt_RESOURCE( 10, 17 )
#define	Pt_ARG_GRID_LAYOUT_INFO		Pt_RESOURCE( 10, 18 )
#define	Pt_CB_CHILD_GETTING_FOCUS	Pt_RESOURCE( 10, 19 )
#define	Pt_CB_CHILD_LOSING_FOCUS	Pt_RESOURCE( 10, 20 )

#define Pt_CONTAINER_FLAGS_MASK			0x00001fff

/* FLAG MANIFESTS */
#define Pt_BLOCK_CUA_FOCUS					0x00000001
#define Pt_AUTO_EXTENT							0x00000002
#define Pt_HOTKEY_TERMINATOR				0x00000004
#define Pt_DISABLE_BALLOONS					0x00000008
#define Pt_ENABLE_CUA								0x00000010
#define Pt_ENABLE_CUA_ARROWS				0x00000020
#define Pt_BALLOON_PROPAGATE				0x00000040
#define Pt_HOTKEYS_FIRST							0x00000080

#define Pt_SHOW_TITLE								0x00000100	
#define Pt_ETCH_TITLE_AREA						0x00000200
#define Pt_GRADIENT_TITLE_AREA				0x00000400
#define	Pt_TITLE_BITS								0x00000700

#define Pt_SUPER_CONSTRAINER				0x00000800 /* (r/o) */
#define Pt_SUPER_CONSTRAINTS				Pt_SUPER_CONSTRAINER /* (r/o) */
#define Pt_CURSOR_IN_CONTAINER				0x00001000 /* (r/o) */
#define Pt_SYSINFO_VALID					0x00002000 /* (r/o) */
#define Pt_CANVAS_INVALID					0x00004000 /* (r/o) */
#define Pt_IGNORE_CONSTRAINTS				0x00008000 /* (r/o) */
#define Pt_CURSOR_OVERRIDE					0x00010000 /* (r/o) */
#define Pt_ANCHOR_CHILD_HORIZONTAL			0x00020000 /* (r/o) */
#define Pt_ANCHOR_CHILD_VERTICAL			0x00040000 /* (r/o) */
#define Pt_SUPER_REDIRECTOR					0x00080000 /* (r/o) */

#define Pt_CHILD_UNREALIZING				0x00100000 /* (r/o) */
#define Pt_CHILD_REALIZING					0x00200000 /* (r/o) */
#define Pt_CHILD_REDIRECTOR					0x00400000 /* (r/o) */
#define Pt_CHILD_DESTROYED					0x00800000 /* (r/o) */
#define Pt_CHILD_CREATED					0x01000000 /* (r/o) */
#define Pt_CHILD_REALIZED					0x02000000 /* (r/o) */
#define Pt_CHILD_UNREALIZED					0x04000000 /* (r/o) */
#define Pt_CHILD_MOVED_RESIZED				0x08000000 /* (r/o) */
#define Pt_CHILD_GETTING_FOCUS				0x10000000 /* (r/o) */
#define Pt_CHILD_LOST_FOCUS					0x20000000 /* (r/o) */
#define Pt_CHILD_LOSING_FOCUS				0x20000000 /* (r/o) */
#define Pt_CHILD_SETTING_RESOURCE			0x40000000 /* (r/o) */
#define Pt_CHILD_GETTING_RESOURCE			0x80000000 /* (r/o) */

#define Pt_CONTAINER_CONSTRAINT_BITS		0xFFFF0000
#define Pt_CONTAINER_RO_FLAGS				0xFFFFF800

#define Pt_CHILD_ADDED					1
#define Pt_CHILD_REMOVED				2

enum PtLayoutTypes { 
	Pt_ANCHOR_LAYOUT = 0, Pt_FILL_LAYOUT, Pt_ROW_LAYOUT, Pt_GRID_LAYOUT 
};

enum PtLayoutCallbackSubReason {
	Pt_LAYOUT_INIT, Pt_LAYOUT_DONE
};

typedef struct pt_focus_info {
	PtWidget_t	*child;
	PtWidget_t	*src;
	PtWidget_t	*dst;
} PtFocusInfo_t;

typedef struct pt_container_callback {
	PhRect_t new_size;
	PhRect_t old_size;
	PhDim_t new_dim;
	PhDim_t old_dim;
} PtContainerCallback_t;

typedef struct pt_balloon_callback_info {
	PtWidget_t	*balloon_widget;	
} PtBalloonCallbackInfo_t;

typedef struct pt_layout_def {
	unsigned	flags;
	void		(*calc_dim_f)( PtWidget_t *widget, const PhDim_t *hint, PhDim_t *dim );
	int			(*layout_f)( PtWidget_t *widget );
	int			info_len;
	int			data_len;
} PtLayoutDefinition_t;

typedef PtWidget_t *(PtGetChildF_t)(PtWidget_t*,PtWidget_t*);

/*
 * PtContainer private
 */

/* Widget structure */
typedef struct Pt_container_widget
{
	PtBasicWidget_t				basic;
	PhTile_t					*damage_visible;
	PhTile_t					*damage_list;
	PtWidget_t					*balloon_widget;
	PtWidget_t					*focus;
	PtWidget_t					*child_front;
	PhRect_t					old_extent;
	PtBalloonCallback_t			*current_balloon;
	short						balloon_count;
	uint8_t						flux_count;
	uint8_t						padding;
	PtWidgetList_t				*ctnrs;
	uint32_t					flags;
	PtWidget_t 					*last_focus;
	PtLayoutDefinition_t		*layout;
	char						*title;
	const char					*title_font;
	PhDim_t						title_dim;
	PhRid_t						override_rid;
} PtContainerWidget_t;

/* Widget union */
typedef struct Pt_container_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtContainerWidget_t			container;
} PtContainerUnion_t;

/* Event types redirected by PtContainer */
#define Pt_EV_REDIRECTED	(Ph_EV_BUT_PRESS|Ph_EV_BUT_RELEASE|Ph_EV_KEY|Ph_EV_BUT_REPEAT)

typedef struct Pt_container_widget_class {
    PtBasicWidgetClass_t	basic;
	void					(*child_created_f)( PtWidget_t *widget, PtWidget_t *child );
	int						(*child_settingresource_f)(PtWidget_t *widget, PtWidget_t *child, PtArg_t const *argt);
	int						(*child_gettingresource_f)(PtWidget_t *widget, PtWidget_t *child, PtArg_t *argt );
	int						(*child_realizing_f)( PtWidget_t *widget, PtWidget_t *child );
	void					(*child_realized_f)( PtWidget_t *widget, PtWidget_t *child );
	void					(*child_unrealizing_f)( PtWidget_t *widget, PtWidget_t *child );
	void					(*child_unrealized_f)( PtWidget_t *widget, PtWidget_t *child );
	void					(*child_destroyed_f)( PtWidget_t *widget, PtWidget_t *child );
	void					(*child_move_resize_f)( PtWidget_t *widget, PtWidget_t *child, PhArea_t *current_area, PhRect_t *current_extent, PhArea_t *old_area, PhRect_t *old_extent );
	int						(*child_getting_focus_f)( PtWidget_t *widget, PtWidget_t *child, PhEvent_t *event );
	int						(*child_losing_focus_f)( PtWidget_t *widget, PtWidget_t *child, PhEvent_t *event );
	PtWidget_t *			(*child_redirect_f)( PtWidget_t *, PtWidgetClassRef_t *);
} PtContainerClass_t;

#define Pt_SET_CHILD_SETTINGRESOURCE_F (Pt_ARG_MODE_PTR|offsetof(PtContainerClass_t, child_settingresource_f))
#define Pt_SET_CHILD_GETTINGRESOURCE_F (Pt_ARG_MODE_PTR|offsetof(PtContainerClass_t, child_gettingresource_f))
#define Pt_SET_CHILD_REALIZING_F  (Pt_ARG_MODE_PTR|offsetof(PtContainerClass_t, child_realizing_f))
#define Pt_SET_CHILD_REALIZED_F  (Pt_ARG_MODE_PTR|offsetof(PtContainerClass_t, child_realized_f))
#define Pt_SET_CHILD_UNREALIZING_F  (Pt_ARG_MODE_PTR|offsetof(PtContainerClass_t, child_unrealizing_f)) 
#define Pt_SET_CHILD_UNREALIZED_F  (Pt_ARG_MODE_PTR|offsetof(PtContainerClass_t, child_unrealized_f)) 
#define Pt_SET_CHILD_CREATED_F  (Pt_ARG_MODE_PTR|offsetof(PtContainerClass_t, child_created_f)) 
#define Pt_SET_CHILD_DESTROYED_F  (Pt_ARG_MODE_PTR|offsetof(PtContainerClass_t, child_destroyed_f)) 
#define Pt_SET_CHILD_MOVED_RESIZED_F  (Pt_ARG_MODE_PTR|offsetof(PtContainerClass_t, child_move_resize_f)) 
#define Pt_SET_CHILD_GETTING_FOCUS_F  (Pt_ARG_MODE_PTR|offsetof(PtContainerClass_t, child_getting_focus_f)) 
#define Pt_SET_CHILD_LOSING_FOCUS_F  (Pt_ARG_MODE_PTR|offsetof(PtContainerClass_t, child_losing_focus_f)) 
#define Pt_SET_CHILD_REDIRECT_F  (Pt_ARG_MODE_PTR|offsetof(PtContainerClass_t, child_redirect_f))

#define PtIsLayoutCandidate(w,c)	((!(c->class_rec->flags & Pt_DISJOINT)) && !(c->eflags & Pt_SKIP_LAYOUT) && (((PtWidgetFlags(w) & (Pt_REALIZED | Pt_REALIZING)) && (PtWidgetFlags(c) & (Pt_REALIZED | Pt_REALIZING))) ||	\
									 !((PtWidgetFlags(w) & (Pt_REALIZED | Pt_REALIZING)) || (PtWidgetFlags(c) & Pt_DELAY_REALIZE))))

extern PtWidget_t *PtNextLayoutCandidate(PtWidget_t *,PtWidget_t *);
extern PtWidget_t *PtLastLayoutCandidate(PtWidget_t *,PtWidget_t *);
extern void PtAnchorChildren(PtContainerWidget_t *widget);
extern PtWidget_t **PtLayoutGetChildren( PtWidget_t *container, int *n, PtGetChildF_t **get_child_f );
extern void *PtLayoutGetChildrenData( const PtLayoutDefinition_t *def, 
						 PtWidget_t **children, int n_children, 
						 const void *dflt_data );
extern void *PtLayoutGetInfo( PtWidget_t *widget, const PtLayoutDefinition_t *def, void *dflt_info );
extern PtWidget_t *PtLayoutGetNext(PtWidget_t *parent,PtWidget_t *widget,PtGetChildF_t **get_child_f);
extern int PtLayoutCountChildren(PtWidget_t *widget,PtGetChildF_t **get_child_f);
extern int PtContainerReInflateBalloon( PtWidget_t *, PhEvent_t * );

#define PtContainerTitle(w)	PtMember(PtContainer,w,title)

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtContainer.h $ $Rev: 219996 $" )
#endif
