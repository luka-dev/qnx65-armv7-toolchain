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
#ifndef __PT_TOOLBAR_H_INCLUDED
#define __PT_TOOLBAR_H_INCLUDED

#ifndef __PT_CONTAINER_H_INCLUDED
#include <photon/PtContainer.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtToolbar public
 */
extern PtWidgetClassRef_t *PtToolbar;

#define Pt_ARG_TOOLBAR_FLAGS				Pt_RESOURCE( 61, 0 )
#define Pt_ARG_TOOLBAR_SPACING				Pt_RESOURCE( 61, 1 )
#define Pt_ARG_TOOLBAR_LAYOUT_FLAGS			Pt_RESOURCE( 61, 2 )

/* toolbar flags */

#define Pt_TOOLBAR_DRAGGABLE			0x0001	/* this enables/disables drag operation */
#define Pt_TOOLBAR_REVERSE_LAST_ITEM	0x0002	/* right/bottom align frontmost item */
#define Pt_TOOLBAR_FOLLOW_FOCUS			0x0004	/* pan toolbar to accomodate focused child */
#define Pt_TOOLBAR_LOCK_ORIENTATION		0x0010	/* do not permit orientation to change */
#define Pt_TOOLBAR_ITEM_SEPARATORS		0x0020	/* render separators between all items */
#define Pt_TOOLBAR_END_SEPARATOR		0x0040	/* render separator after last item */

#define Pt_TOOLBAR_HORIZONTAL			0x1000	/* read-only */
#define Pt_TOOLBAR_DAMAGE_PANNING		0x2000	/* read-only */
#define Pt_TOOLBAR_DAMAGE_HANDLE		0x4000	/* read-only */
#define Pt_TOOLBAR_USE_PANNING			0x8000	/* read-only */
#define Pt_TOOLBAR_RO_FLAGS				0xf000

/* toolbar layout flags */

#define Pt_TOOLBAR_FROM_LINE_START		0x01	/* start toolbar on new line */
#define Pt_TOOLBAR_TO_LINE_END			0x02	/* run toolbar to end of line */
#define Pt_TOOLBAR_MINIMIZED			0x80	/* toolbar in minimized state */
#define Pt_TOOLBAR_RO_LAYOUT_FLAGS		0x80

#define Pt_TOOLBAR_PAN_BY_PIXEL			1		/* pixel-based panning */
#define Pt_TOOLBAR_PAN_BY_ITEM			2		/* pan one item at a time */
#define Pt_TOOLBAR_PAN_BY_ROW			3		/* pan entire row at a time */


/* Widget structure */
typedef struct Pt_toolbar_widget
{
	PtContainerWidget_t container;

	PtWidget_t *view;
	
	uint16_t flags;
	uint8_t spacing;
	uint8_t speed;

	uint16_t dragged_width;		/* width forced by toolbar drag operations */
	uint8_t layout_flags;
	int8_t padding;

	PhRect_t drag_handle;
	
} PtToolbarWidget_t;


/* manifests for widget actions */

enum
{
	Pt_TOOLBAR_PAN_UL_ACTION = 0,
	Pt_TOOLBAR_PAN_DR_ACTION
};


/* Widget union */
typedef union Pt_toolbar_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtContainerWidget_t			container;
	PtToolbarWidget_t			toolbar;

} PtToolbarUnion_t;

/* macros */

#define PtToolbarIsHorizontal(w)		(((PtToolbarWidget_t*)(w))->flags & Pt_TOOLBAR_HORIZONTAL)
#define PtToolbarIsVertical(w)			(!PtToolbarIsHorizontal(w))
#define PtToolbarOrientationLocked(w)	(((PtToolbarWidget_t*)(w))->flags & Pt_TOOLBAR_LOCK_ORIENTATION)

#if defined(__GNUC__)
 #define PtToolbarDragHandleRect(w,r)	({ PhRect_t  *res; if((int)(r)!=0) *(res=(r))=((PtToolbarWidget_t*)(w))->drag_handle; else res=&((PtToolbarWidget_t*)(w))->drag_handle; res; })
#else
 #define PtToolbarDragHandleRect(w,r)	((r) ? (PhRect_t*)(memcpy((void*)(r),(void*)(&((PtToolbarWidget_t*)(w))->drag_handle),sizeof(PhRect_t))) : &((PtToolbarWidget_t*)(w))->drag_handle)
#endif

extern int PtToolbarAtMaximum(void const *);
extern int PtToolbarAtMinimum(void const *);

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtToolbar.h $ $Rev: 227171 $" )
#endif
