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
 *	PtGenList.h
 *		Header file for the PtGenList widget class
 *

 */
#ifndef __PT_GENLIST_H_INCLUDED
#define __PT_GENLIST_H_INCLUDED

#ifndef __PT_COMPOUND_H_INCLUDED
 #include <photon/PtCompound.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtGenList public
 */

extern PtWidgetClassRef_t *const PtGenList;

#define Pt_GENLIST_ID		23

/* Resources */
#define Pt_ARG_LIST_FLAGS			Pt_RESOURCE( 23,  2 )
#define Pt_ARG_LIST_FONT			Pt_RESOURCE( 23,  3 )
#define Pt_ARG_SCROLLBAR_WIDTH		Pt_RESOURCE( 23,  5 )
#define Pt_ARG_SELECTION_MODE		Pt_RESOURCE( 23,  7 )
#define Pt_ARG_TOP_ITEM_POS			Pt_RESOURCE( 23,  8 )
#define Pt_ARG_VISIBLE_COUNT		Pt_RESOURCE( 23,  9 )
#define Pt_CB_SCROLL_MOVE			Pt_RESOURCE( 29, 10 )
#define Pt_ARG_SCROLLBAR			Pt_RESOURCE( 23, 11 )
/* 		         ^^-----deprecated */
#define Pt_ARG_SELECTION_FILL_COLOR Pt_RESOURCE( 23, 12 )
#define Pt_ARG_SELECTION_TEXT_COLOR Pt_RESOURCE( 23, 13 )
#define Pt_ARG_LIST_ITEM_COUNT		Pt_RESOURCE( 23, 14 )
#define Pt_ARG_LIST_SEL_COUNT		Pt_RESOURCE( 23, 15 )
#define Pt_ARG_LIST_TOTAL_HEIGHT	Pt_RESOURCE( 23, 16 )
#define Pt_ARG_LIST_DNDSEL_COLOR	Pt_RESOURCE( 23, 17 )
#define Pt_ARG_BALLOON_FILL_COLOR	Pt_RESOURCE(  3, 19 )
#define Pt_ARG_BALLOON_COLOR		Pt_RESOURCE(  3, 20 )
#define Pt_ARG_LIST_SB_RES			Pt_RESOURCE( 23, 25 )
#define Pt_ARG_LIST_SCROLL_RATE		Pt_RESOURCE( 23, 26 )
#define Pt_ARG_LIST_COLUMN_POS		Pt_RESOURCE( 23, 27 )
#define Pt_ARG_LIST_COLUMN_ATTR		Pt_RESOURCE( 23, 28 )
#define Pt_ARG_SB_FILL_COLOR			Pt_RESOURCE( 23, 37 )
#define Pt_ARG_SB_ARROW_COLOR			Pt_RESOURCE( 23, 38 )


/* Selection Callback Subtypes */
#define	Pt_LIST_SELECTION_FINAL		0x00
#define	Pt_LIST_SELECTION_BROWSE	0x01
#define	Pt_LIST_SELECTION_CANCEL	0x02

/* Scroll Move Callback Subtypes */
#define	Pt_LIST_SCROLL_LIST			0x00	/*	The keyboard or mouse was used */
#define	Pt_LIST_SCROLL_SCROLLBAR	0x01	/*	The scrollbar was used */

/* Actions for the Scroll Move callback: */
#define Pt_SCROLL_DECREMENT			1
#define Pt_SCROLL_INCREMENT			2
#define Pt_SCROLL_PAGE_INCREMENT	3
#define Pt_SCROLL_PAGE_DECREMENT	4
#define Pt_SCROLL_TO_MAX			5
#define Pt_SCROLL_TO_MIN			6
#define Pt_SCROLL_DRAGGED			7
#define Pt_SCROLL_RELEASED			8
#define Pt_SCROLL_SET				9
#define Pt_SCROLL_JUMP				10

#define Pt_SINGLE_MODE		1
#define Pt_MULTIPLE_MODE	2
#define Pt_BROWSE_MODE		3
#define Pt_EXTENDED_MODE	4
#define Pt_RANGE_MODE		5

/* Compose selection modes */
#define Pt_SELECTION_MODE_MULTIPLE	0x8000
#define Pt_SELECTION_MODE_RANGE		0x8010
#define Pt_SELECTION_MODE_SINGLE	0x8020
#define Pt_SELECTION_MODE_NONE		0x8030

/* Compose selection mode flags */
#define Pt_SELECTION_MODE_NOSCROLL	0x8040
#define Pt_SELECTION_MODE_NOMOVE	0x8080
#define Pt_SELECTION_MODE_NOREST	0x8100
#define Pt_SELECTION_MODE_AUTO		0x8200
#define Pt_SELECTION_MODE_NOCLEAR	0x8400
#define Pt_SELECTION_MODE_TOGGLE	0x8800
#define Pt_SELECTION_MODE_NOFOCUS	0x9000

#define Pt_SELECTION_MODE_COMPOSE_FLAG	0x8000
#define Pt_SELECTION_MODE_COMPOSE_MASK	0x9FF0
/* Macros that calculate values for sel_xmode and sel_flags */
#define Pt_SELECTION_MODE( mode )	( (mode) >> 4 & 0x03 ) /* sel_xmode */
#define Pt_SELECTION_FLAGS( mode )	( (mode) >> 6 & 0xFF ) /* sel_flags */

/* List flags */
#define Pt_LIST_VSCROLLBAR_NEVER		0x0000
#define Pt_LIST_SCROLLBAR_NEVER			0x0000
#define Pt_LIST_VSCROLLBAR_ALWAYS		0x0001
#define Pt_LIST_SCROLLBAR_ALWAYS		0x0001
#define Pt_LIST_VSCROLLBAR_AS_REQUIRED	0x0002
#define Pt_LIST_SCROLLBAR_AS_REQUIRED	0x0002
#define Pt_LIST_VSCROLLBAR_MASK			0x0003
#define Pt_LIST_SCROLLBAR_MASK			0x0003
#define Pt_LIST_HSCROLLBAR_NEVER		0x0000
#define Pt_LIST_HSCROLLBAR_ALWAYS		0x0200
#define Pt_LIST_HSCROLLBAR_AS_REQUIRED	0x0004
#define Pt_LIST_HSCROLLBAR_MASK			0x0204
#define Pt_LIST_NON_SELECT				0x0008
#define Pt_LIST_SNAP					0x0010
#define Pt_LIST_BALLOON_NEVER			0x0000
#define Pt_LIST_SHOW_BALLOON			0x0020
#define Pt_LIST_BALLOON_AS_REQUIRED		0x0040
#define Pt_LIST_BALLOON_MASK			0x0060
#define Pt_LIST_BALLOON_REGISTERED		0x0080 /* RO */
#define Pt_LIST_SCROLLBAR_GETS_FOCUS	0x0100
#define Pt_LIST_HEADER_AUTORESIZE		0x0400
#define Pt_LIST_SCROLLBAR_AUTORESIZE	0x0800
#define Pt_LIST_BALLOONS_IN_COLUMNS		0x1000
#define Pt_LIST_BOUNDARY_KEY_EVENTS		0x2000
#define	Pt_LIST_NO_COLUMN_LINES			0x4000
#define	Pt_LIST_STRETCH_HEADER			0x8000

/* Column flags */
#define Pt_LIST_COLUMN_LEFT				0x1000
#define Pt_LIST_COLUMN_RIGHT			0x2000
#define Pt_LIST_COLUMN_CENTER			0x3000
#define Pt_LIST_COLUMN_ALIGNMENT		0x3000 /* Mask */
#define Pt_LIST_COLUMN_DAMAGE_ALWAYS	0x0001
#define Pt_LIST_COLUMN_NO_STRING		0x0002
#define	Pt_LIST_COLUMN_ELLIPSIS			0x0100
#define	Pt_LIST_COLUMN_ELLIPSIS_MIDDLE	0x0200
#define	Pt_LIST_COLUMN_ELLIPSIS_INVERT	0x0400

/* Balloon alignment types for PtGenListCreateTextBalloon() */
#define	Pt_LIST_BALLOON_LEFT		(-1)
#define	Pt_LIST_BALLOON_RIGHT		(-2)
#define	Pt_LIST_BALLOON_CENTER		(-3)

/* gflags */

#define Pt_GEN_LIST_NO_BACKGROUND			0x01
#define Pt_GEN_LIST_NO_CLIPPING				0x02
#define Pt_GEN_LIST_SHOW_DAMAGED			0x04
#define Pt_GEN_LIST_FULL_WIDTH				0x08
#define Pt_GEN_LIST_NO_AUTOFOCUS			0x10
#define Pt_GEN_LIST_ITEM_BACKGROUND			0x20

/* Item flags */

#define Pt_LIST_ITEM_SELECTED			0x00001
#define Pt_LIST_ITEM_CURRENT			0x00002
#define Pt_LIST_ITEM_DISABLED			0x00004
#define Pt_LIST_ITEM_DAMAGED			0x00008
#define Pt_LIST_ITEM_ABOVE				0x00010
#define Pt_LIST_ITEM_BELOW				0x00020
#define Pt_LIST_ITEM_SAVED				0x00100
#define Pt_LIST_ITEM_NOCOLUMNS			0x00200
#define Pt_LIST_ITEM_INWIDGET			0x00400
#define Pt_LIST_ITEM_DNDSELECTED_UP		0x00800
#define Pt_LIST_ITEM_DNDSELECTED_DOWN	0x01000
#define Pt_LIST_ITEM_DNDSELECTED_IN		0x02000

#define Pt_LIST_ITEM_DND_OUTSIDE_LEFT			0x8000
#define Pt_LIST_ITEM_DND_OUTSIDE_RIGHT		0x10000

#define Pt_LIST_ITEM_FLAG_USER1			0x80000000
#define Pt_LIST_ITEM_FLAG_USER2			0x40000000
#define Pt_LIST_ITEM_FLAG_USER3			0x20000000
#define Pt_LIST_ITEM_FLAG_USER4			0x10000000
#define Pt_LIST_ITEM_FLAG_USER_ALL	0xF0000000

#define Pt_LIST_ITEM_USED_FLAGS			0xF003BF3F /*	Flags defined by the GenList widget */

#define Pt_LIST_ITEM_DNDSELECTED		( Pt_LIST_ITEM_DNDSELECTED_UP | Pt_LIST_ITEM_DNDSELECTED_DOWN | Pt_LIST_ITEM_DNDSELECTED_IN )
#define Pt_LIST_ITEM_DND_OUTSIDE		(Pt_LIST_ITEM_DND_OUTSIDE_LEFT|Pt_LIST_ITEM_DND_OUTSIDE_RIGHT)

/* Columns */

typedef struct Pt_list_column {
	short from, to;
	}
		PtListColumn_t;

typedef struct Pt_list_columns_attrs {
	unsigned flags;
	unsigned reserved[ 3 ];
	}
		PtListColumnAttributes_t;

/* Callback structure */
typedef struct Pt_list_scroll_callback {
	unsigned	action;
	int			position;
	}
		PtListScrollCallback_t;

typedef struct Pt_gen_list_dnd_callback {
	PtDndCallbackInfo_t		dnd_info;
	struct Pt_genlist_item	*item;
	int						item_pos;
	unsigned long			flags;
	int						action;
	}
		PtGenListDndCallback_t;

/* List item structure */

typedef struct Pt_genlist_item {
	unsigned flags;
	PhDim_t size;
	struct Pt_genlist_item *next, *prev;
	}
		PtGenListItem_t;

typedef struct Pt_gen_list_color_set {
	PgColor_t text, fill;
	}
		PtGenListColorSet_t;

typedef struct Pt_genlist_item_attrs {
	const char *font;
	PtGenListColorSet_t unselected_colors;
	PtGenListColorSet_t selected_colors;
	unsigned flags;
	}
		PtGenListItemAttrs_t;

/*
 * PtGenList private
 */

/* Widget structure */
struct Pt_gen_list_sel_state;

typedef struct Pt_genlist_widget {
	PtCompoundWidget_t	cmpnd;

	const char			*font;				/* Pt_ARG_LIST_FONT */
	unsigned short		gflags;
	short				bloff;
	PtGenListItem_t		*first_item,		/* First item on list (NULL if list empty) */
						*last_item,			/* Last item on list (NULL if list empty) */
						*current_item,		/* NULL or the only item that has the CURRENT flag set */
						*first_displayed,	/* First of visible items (NULL if list empty) */
						*last_displayed,	/* Last of visible items (NULL if none is visible) */
						*range_item;		/* The beginning of range */
	unsigned			total_height;		/* Total height of all items */
	PgColor_t			selection_fill_color; /* Pt_ARG_SELECTION_FILL_COLOR */
	PgColor_t			selection_text_color; /* Pt_ARG_SELECTION_TEXT_COLOR */
	unsigned short		item_count,			/* Total number of items */
						displayed_count,	/* Number of visible items */
						sel_count,			/* Number of selected items */
						top_item,			/* Pt_ARG_TOP_ITEM_POS */
						rng_ndx,			/* Index of the range_item */
						cur_ndx,			/* Index of the current_item */
						max_top,			/* The maximal value of top_item */
						displayed_height,	/* Total height of visible items */
						slider_width,		/* Pt_ARG_SLIDER_WIDTH */
						sel_mode,			/* Pt_ARG_SELECTION_MODE */
						flags;				/* Pt_ARG_LIST_FLAGS */
	unsigned char		sel_xmode,			/* Selection mode */
						sel_flags;			/* Selection mode flags */
	unsigned char		scroll_rate;		/* Pt_ARG_LIST_SCROLL_RATE */
	unsigned char		scount;
	unsigned short		ncolumns;			/* Pt_ARG_COLUMN_POS.length */
	PtListColumn_t		*columns;			/* Pt_ARG_COLUMN_POS */
	PgColor_t			balloon_fg,			/* Pt_ARG_BALLOON_COLOR */
						balloon_bg;			/* Pt_ARG_BALLOON_FILL_COLOR */
	PtWidget_t			*balloon;
	PtListColumnAttributes_t *col_attrs;	/* Pt_ARG_COLUMN_ATTR */
	unsigned short		ncol_attrs;			/* Pt_ARG_COLUMN_ATTR.length */

	short				font_height;
	PtWidget_t			*divider;
	PtListColumn_t		damage;

	PtWidget_t			*scrollbar;
	PhDim_t				locked_size;
	unsigned short		top_margin;
	unsigned short		marg_height;
	unsigned short		marg_width;
	short				canvas_width;
	PtGenListItem_t		*inflated;
	short				will_damage;
	signed short		inflated_col;
	struct Pt_gen_list_sel_state
						*selst;
	PtGenListItem_t		*item_dnd_selected, *item_dnd_outside;
	PgColor_t			dnd_selection_color;
	PtGenListItem_t		*select_ignored_item;

	/* New stuff */
	PtListColumn_t		dfltcol;
	PtListColumn_t		allcols;
	PtWidget_t			*hscrollbar;
	PgColor_t			sb_fill_color,
						sb_pen_color;
	}
		PtGenListWidget_t;

/* Widget union */
typedef union Pt_genlist_union {
	PtWidget_t				core;
	PtBasicWidget_t			basic;
	PtContainerWidget_t		cntnr;
	PtCompoundWidget_t		cmpnd;
	PtGenListWidget_t		glist;
	}
		PtGenListUnion_t;

typedef void PtGenListDrawF_t(
	PtWidget_t *widget,
	PtGenListItem_t *item, unsigned index,
	unsigned nitems,
	PhRect_t *where /* Modify *where if needed */
	);

typedef int PtGenListMouseF_t(
	PtWidget_t *wgt,
	PtGenListItem_t *item,
	unsigned index,
	PhPoint_t *where, /* relative to the item, can modify */
	int column,
	PhEvent_t *ev
	);

typedef int PtGenListKeyF_t(
	PtWidget_t *wgt,
	PhEvent_t *ev, PhKeyEvent_t *kev,
	PtGenListItem_t *newcur, unsigned newpos
	);

typedef void PtGenListSelectF_t(
	PtWidget_t *wgt, PtGenListItem_t *item, int pos, int column,
	int nitems, int subtype, PhEvent_t *ev
	);

typedef PtWidget_t *PtGenListInflateF_t(
	PtWidget_t *widget, PtWidget_t *parent,
	PtGenListItem_t *item, unsigned index,
	int column, PhArea_t *area
	);

typedef void PtGenListDrawBackgroundF_t(
	PtWidget_t *widget,
	PhRect_t const *canvas, PhRect_t const *empty
	);

typedef int PtGenListDndCallbackF_t(
	PtWidget_t *widget,
	PtGenListItem_t const *item, int index, PhEvent_t *event, unsigned long *pflags, unsigned int *action
	);

typedef const PtGenListItemAttrs_t *PtGenListGetItemAttrsF_t(
	PtWidget_t *widget, PtGenListItem_t const *item
	);

typedef struct Pt_gen_list_widget_class {
    PtCompoundClass_t	compound;
	PtGenListDrawF_t	*list_draw_f;
	PtGenListMouseF_t	*list_mouse_f;
	PtGenListKeyF_t		*list_key_f;
	PtGenListSelectF_t	*list_select_f;
	PtGenListInflateF_t	*list_inflate_f;
	PtGenListDrawBackgroundF_t *list_draw_background_f;
	PtGenListDndCallbackF_t *list_dnd_callback_f;
	PtGenListGetItemAttrsF_t *list_itemattrs_f;
	}
		PtGenListClass_t;

#define Pt_SET_LIST_DRAW_F		Pt_ARG_IS_POINTER( PtGenListClass_t, list_draw_f )
#define Pt_SET_LIST_MOUSE_F		Pt_ARG_IS_POINTER( PtGenListClass_t, list_mouse_f )
#define Pt_SET_LIST_KEY_F		Pt_ARG_IS_POINTER( PtGenListClass_t, list_key_f )
#define Pt_SET_LIST_SELECT_F	Pt_ARG_IS_POINTER( PtGenListClass_t, list_select_f )
#define Pt_SET_LIST_INFLATE_F	Pt_ARG_IS_POINTER( PtGenListClass_t, list_inflate_f )
#define Pt_SET_LIST_DRAW_BACKGROUND_F	Pt_ARG_IS_POINTER( PtGenListClass_t, list_draw_background_f )
#define Pt_SET_LIST_DND_CALLBACK_F		Pt_ARG_IS_POINTER( PtGenListClass_t, list_dnd_callback_f )
#define Pt_SET_LIST_ITEMATTRS_F		Pt_ARG_IS_POINTER( PtGenListClass_t, list_itemattrs_f )

void PtSuperClassGenListDraw(
	PtWidgetClassRef_t *cref, PtWidget_t *widget,
	PtGenListItem_t *item, unsigned index,
	unsigned nitems, PhRect_t *where
	);

int PtSuperClassGenListMouse(
	PtWidgetClassRef_t *cref, PtWidget_t *wgt,
	PtGenListItem_t *item, unsigned index,
	PhPoint_t *where, int column, PhEvent_t *ev
	);

int PtSuperClassGenListKey(
	PtWidgetClassRef_t *cref, PtWidget_t *wgt,
	PhEvent_t *ev, PhKeyEvent_t *kev,
	PtGenListItem_t *newcur, unsigned newpos
	);

void PtSuperClassGenListSelect(
	PtWidgetClassRef_t *cref, PtWidget_t *wgt,
	PtGenListItem_t *item, int pos, int column,
	int nitems, int subtype, PhEvent_t *ev
	);

PtWidget_t *PtSuperClassGenListInflate(
	PtWidgetClassRef_t *cref, PtWidget_t *wgt,
	PtWidget_t *parent, PtGenListItem_t *item,
	unsigned index, int column, PhArea_t *area
	);


void PtGenListDrawBackground( 
	PtWidget_t *list, PtGenListItem_t const *item,
	unsigned nitems, PhRect_t const *where,
	int lmarg, int rmarg, int tmarg, int bmarg
	);

void PtGenListDrawString( 
	PtWidget_t *list, PtGenListItem_t const *item, const char *string,
	PhRect_t const *where, int lmarg, int rmarg
	);

unsigned PtGenListSetGflags(
	PtWidget_t *widget, unsigned gflags, unsigned mask
	);

void PtGenListHold( PtWidget_t *widget );
void PtGenListRelease( PtWidget_t *widget );

void PtGenListDamageItem( PtWidget_t *list, PtGenListItem_t *item );
void PtGenListLockItem( PtWidget_t *list, PtGenListItem_t *item );
void PtGenListUnlockItem( PtWidget_t *list, PtGenListItem_t *item );
void PtGenListResize( PtWidget_t *widget );

int PtGenListAddItems(
	PtWidget_t *list, PtGenListItem_t *items, PtGenListItem_t *after
	);

PtGenListItem_t *PtGenListRemoveItems(
	PtWidget_t *widget, PtGenListItem_t *first, PtGenListItem_t *last
	);

PtGenListItem_t *PtGenListItemRealloc(
	PtGenListItem_t *item, PtWidget_t *list, size_t size
	);

int PtGenListItemIndex(
	PtWidget_t const *list, PtGenListItem_t const *item
	);

void PtGenListShow( PtWidget_t *list, PtGenListItem_t *item );
void PtGenListGoto( PtWidget_t *list, PtGenListItem_t *item );
PtGenListItem_t *PtGenListFindItem( PtWidget_t const *widget, int index );
PtGenListItem_t *PtGenListItemAt( PtWidget_t const *widget, PhPoint_t const *pos, int *index, int *offset );

void PtGenListClearSelection( PtWidget_t *widget );

PtGenListItem_t *PtGenListGetCurrent( PtWidget_t const *widget );

void PtGenListSelect( PtWidget_t *widget, PtGenListItem_t *item );
void PtGenListUnselect( PtWidget_t *widget, PtGenListItem_t *item );

short PtGenListSelectedCount( PtWidget_t const *widget );

unsigned short *PtGenListGetSelIndexes(
	PtWidget_t *widget, unsigned short *buffer
	);

int PtGenListSetSelIndexes(
	PtWidget_t *widget, const unsigned short *buffer, int count
	);

PtGenListItem_t **PtGenListSelectedItems(
	PtWidget_t *widget, PtGenListItem_t **buffer
	);

PtGenListItem_t **PtGenListAllItems(
	PtWidget_t *widget, PtGenListItem_t **buffer
	);

PhArea_t *PtGenListSetColumnBalloon( PhArea_t *area, PtListColumn_t const *col );

PtWidget_t *PtGenListCreateTextBalloon(
	PtWidget_t *widget, PtWidget_t *parent, const PhArea_t *area,
	const char *string, int column, const char *font
	);

void PtGenListDestroyBalloon( PtWidget_t *list );

const char *PtGenListFindColumnString(
	PtWidget_t *widget, const char *string, int column, unsigned *length
	);

PtGenListItem_t *PtGenListFirstItem( PtWidget_t const *list );

PtGenListItem_t *PtGenListLastItem( PtWidget_t const *list );

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtGenList.h $ $Rev: 219996 $" )
#endif
