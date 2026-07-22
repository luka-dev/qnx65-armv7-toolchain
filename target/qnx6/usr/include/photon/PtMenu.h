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
 *	PtMenu.h
 *		Header file for the PtMenu widget class
 *

 */
#ifndef __PT_MENU_H_INCLUDED
#define __PT_MENU_H_INCLUDED

#ifndef __PT_GROUP_H_INCLUDED 
#include <photon/PtGroup.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


extern PtWidgetClassRef_t *PtMenu;

 
/* Resources */
#define Pt_ARG_MENU_FLAGS			Pt_RESOURCE( 19, 0 )
#define Pt_ARG_MENU_SPACING			Pt_RESOURCE( 19, 1 )
#define Pt_ARG_MENU_TEXT_FONT		Pt_RESOURCE( 19, 2 )
#define Pt_ARG_MENU_TITLE			Pt_RESOURCE( 19, 3 )
#define Pt_ARG_MENU_TITLE_FONT		Pt_RESOURCE( 19, 4 )

#define	Pt_ARG_MENU_ITEM_FILL_COLOR				Pt_RESOURCE( 19, 5 )
#define	Pt_ARG_MENU_ITEM_HIGHLIGHT_COLOR		Pt_RESOURCE( 19, 6 )
#define	Pt_ARG_SUBMENU_PARENT_HIGHLIGHT_COLOR	Pt_RESOURCE( 19, 7 )
#define	Pt_ARG_MENU_INPUT_GROUP		Pt_RESOURCE( 19, 8 )

/* Menu Flags */
#define Pt_MENU_AUTO			0x01
#define Pt_MENU_TRANSIENT		0x02
#define Pt_MENU_TEAR_OFF		0x04
#define Pt_MENU_CHILD   		0x08
#define Pt_MENU_GRADIENT		0x10	/* Gradient-fill the highlighted item */
#define Pt_MENU_TEXT_ALIGN		0x20	/* Text alignment */
#define Pt_MENU_RO_FLAGS				0xfff00000

/* Widget structure */
typedef struct Pt_menu_widget {
	PtGroupWidget_t				group;
	ulong_t						flags;
	PtWidget_t					*ff_wgt;
	short						spacing;
	ushort_t					title_sep;
	PtWidget_t					*child_menu;
	char						*title;
	const char					*title_font;
	const char					*text_font;
	int							num_cols;
	int							base_col_num_items;
	PtWidget_t					*prev_focus;
	PgColor_t					item_fill_color,
								item_highlight_color,
								submenu_parent_highlight_color,
								saved_fill_color;
	PtWidget_t					*focused;
	short						input_group;
} PtMenuWidget_t;

/* Widget union */
typedef union Pt_menu_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtContainerWidget_t			container;
	PtGroupWidget_t				group;
	PtMenuWidget_t				menu;
} PtMenuUnion_t;


#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtMenu.h $ $Rev: 219996 $" )
#endif
