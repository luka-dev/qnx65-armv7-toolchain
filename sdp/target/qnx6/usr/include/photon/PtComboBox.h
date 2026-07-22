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
 *	PtComboBox.h
 *		Header file for the PtComboBox widget class
 *

 */
#ifndef __PT_COMBOBOX_H_INCLUDED
#define __PT_COMBOBOX_H_INCLUDED

#ifndef __PT_COMPOUND_H_INCLUDED
#include <photon/PtCompound.h>
#endif

#ifndef __PT_TEXT_H_INCLUDED
#include <photon/PtText.h>
#endif

#ifndef __PT_LIST_H_INCLUDED
#include <photon/PtList.h>
#endif

#ifndef __PT_RAW_H_INCLUDED
#include <photon/PtRaw.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif
/*
 * PtComboBox Convenience Functions
 */

extern int PtComboBoxListOpen( PtWidget_t * );
extern int PtComboBoxListClose( PtWidget_t * );

/*
 * PtComboBox public
 */
extern PtWidgetClassRef_t *PtComboBox;

#define Pt_COMBOBOX_ID		31

#define Pt_ARG_CBOX_FLAGS						Pt_RESOURCE( 31, 0 )
#define Pt_ARG_CBOX_SEL_ITEM					Pt_RESOURCE( 31, 1 )
#define Pt_ARG_CBOX_SELECTION_ITEM				Pt_RESOURCE( 31, 1 )

#define Pt_ARG_CBOX_BUTTON_BORDER_WIDTH			Pt_RESOURCE( 31, 15 )
#define Pt_ARG_CBOX_BUTTON_TOP_BORDER_COLOR		Pt_RESOURCE( 31, 16 )
#define Pt_ARG_CBOX_BUTTON_BOT_BORDER_COLOR		Pt_RESOURCE( 31, 17 )
#define Pt_ARG_CBOX_BUTTON_COLOR				Pt_RESOURCE( 31, 18 )
#define Pt_ARG_CBOX_MAX_VISIBLE_COUNT			Pt_RESOURCE( 31, 19)
#define Pt_ARG_CBOX_BUTTON_WIDTH				Pt_RESOURCE( 31, 6 )
#define Pt_CB_CBOX_ACTIVATE						Pt_RESOURCE( 31, 14 )
#define Pt_CB_CBOX_CLOSE						Pt_RESOURCE( 31, 20 )
#define Pt_ARG_CBOX_TEXT_FILL_COLOR				Pt_RESOURCE( 31, 21 )

/* Old Manifests */
#define Pt_ARG_CBOX_ITEMS					Pt_ARG_ITEMS
#define Pt_ARG_CBOX_SPACING					Pt_ARG_LIST_SPACING
#define Pt_ARG_CBOX_SEL_MODE				Pt_ARG_SELECTION_MODE
#define Pt_ARG_CBOX_SELECTION_MODE			Pt_ARG_SELECTION_MODE
#define Pt_ARG_CBOX_VISIBLE_COUNT			Pt_ARG_VISIBLE_COUNT
#define Pt_ARG_CBOX_SELECTION_FILL_COLOR 	Pt_ARG_SELECTION_FILL_COLOR
#define Pt_ARG_CBOX_SELECTION_TEXT_COLOR    Pt_ARG_SELECTION_TEXT_COLOR

#define Pt_ARG_CBOX_MAX_LENGTH				Pt_ARG_MAX_LENGTH
#define Pt_ARG_CBOX_CURSOR_POSITION			Pt_ARG_CURSOR_POSITION
#define Pt_ARG_CBOX_EDIT_MASK				Pt_ARG_EDIT_MASK
#define Pt_ARG_CBOX_TEXT_FONT				Pt_ARG_TEXT_FONT
#define Pt_ARG_CBOX_TEXT_STRING				Pt_ARG_TEXT_STRING


/* ComboBox flags */
#define Pt_COMBOBOX_STATIC				0x00000020
#define Pt_COMBOBOX_TOP					0x00000040
#define Pt_COMBOBOX_MAX_WIDTH			0x00000080
#define Pt_COMBOBOX_ALT_DOWN			0x00000100

#define Pt_COMBOBOX_DRAW_FOCUS			0x08000000 /* private */
#define Pt_COMBOBOX_DAMAGE_BUTTON		0x10000000 /* ( r/o ) */
#define Pt_COMBOBOX_EXTENTING			0x20000000 /* ( r/o ) */
#define Pt_COMBOBOX_ON_BOTTOM			0x40000000 /* ( r/o ) */
#define	Pt_COMBOBOX_OPEN				0x80000000 /* ( r/o ) */
#define Pt_COMBOBOX_RO_FLAGS			0xf0000000

/* Callback structure */
typedef PtTextCallback_t PtComboBoxTextCallback_t;
typedef PtListCallback_t PtComboBoxListCallback_t;

#define Pt_COMBOBOX_LIST_ACTION		0

/*
 * PtComboBox private
 */

/* Widget structure */
typedef struct Pt_combobox_widget {
	PtCompoundWidget_t		compound;
	ulong_t		           	flags;
	unsigned short			reserved;
	unsigned short			ig;
	short					sel_item;
	ushort_t				butn_border_width;
	PhDim_t					butn_size;
	PgColor_t				butn_bot_border_color;
	PgColor_t				butn_top_border_color;
	PgColor_t				butn_color;
	ushort_t				border_width;
	short					max_visible;
	PtWidget_t				*text_wgt;
	PtWidget_t				*list_wgt;
	PtWidget_t				*list_region_ff;
	PtWidget_t				*list_region;
} PtComboBoxWidget_t;

/* Widget union */
typedef union Pt_combobox_union {
	PtWidget_t				core;
	PtBasicWidget_t			basic;
	PtContainerWidget_t		container;
	PtCompoundWidget_t		compound;
	PtComboBoxWidget_t		combobox;
} PtComboBoxUnion_t;

/* macros */

#define PtComboBoxIsOpen(w)		(((PtComboBoxWidget_t*)(w))->flags & Pt_COMBOBOX_OPEN)
#define PtComboBoxIsClosed(w)	(!PtComboBoxIsOpen(w))

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtComboBox.h $ $Rev: 219996 $" )
#endif
