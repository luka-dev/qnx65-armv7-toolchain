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
 *	PtColorPalette.h
 *		Header file for the PtColorPalette widget class
 *

 */
 
#ifndef __PT_COLORPALETTE_H_INCLUDED
#define __PT_COLORPALETTE_H_INCLUDED

#include <photon/PtColorSel.h>
#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

extern PtWidgetClassRef_t *PtColorPalette;

/* Resources */

#define Pt_ARG_CPALETTE_FLAGS			Pt_RESOURCE( 153, 0 )
#define Pt_ARG_CPALETTE_COLUMNS			Pt_RESOURCE( 153, 1 )
#define Pt_ARG_CPALETTE_ROWS			Pt_RESOURCE( 153, 2 )
#define Pt_ARG_CPALETTE_CURRENT_X		Pt_RESOURCE( 153, 3 )
#define Pt_ARG_CPALETTE_CURRENT_Y		Pt_RESOURCE( 153, 4 )
#define Pt_ARG_CPALETTE_CELL_DIM		Pt_RESOURCE( 153, 5 )
#define Pt_CB_CPALETTE_CHANGED			Pt_RESOURCE( 153, 6 )

#define Pt_CPALETTE_SHOW_NAME			0x1		/* show palette name */
#define Pt_CPALETTE_VARIABLE_COLUMNS	0x2		/* variable # columns */
#define Pt_CPALETTE_VARIABLE_ROWS		0x4		/* varialbe # rows */
#define Pt_CPALETTE_EDITABLE			0x8		/* palette can be editted */
#define Pt_CPALETTE_PACK_COLORS			0x10	/* pack colors in table */
#define Pt_CPALETTE_ENABLE_POPUP		0x20	/* enable popup color patch */
#define Pt_CPALETTE_RO_FLAGS			0

/* Callback structure for Pt_CB_CPALETTE_CHANGED */

typedef struct colorpalette_callback
{
	PgColor_t color;
	uint8_t x,y;
	uint16_t padding;
	
} PtColorPaletteCallback_t;

/* callback reason subtypes */

#define Pt_CPALETTE_COLOR_ADDED		1
#define Pt_CPALETTE_COLOR_CHANGED	2
#define Pt_CPALETTE_COLOR_REMOVED	3
#define Pt_CPALETTE_SWITCHED		4

/* node structure for PtColorPalette's list of colors */

typedef struct palette_node
{
	char *name;

	uint16_t index;
	uint8_t x,y;

	PgColor_t color;
	struct palette_node *next;

} PtColorPaletteNode_t;

/* Widget structure */

typedef struct pt_colorpalette_widget
{
	PtColorSelWidget_t colorsel;

	uint16_t flags;
	uint8_t ncols;						/* fixed # columns */
	uint8_t nrows;						/* fixed # rows */

	PtWidget_t *scrollarea;				/* scrollable view of palette */
	PtWidget_t *name_lbl,*name_txt;		/* palette name indicator */

	PhDim_t cell_dim;					/* dimensions of each cell */

	uint8_t sel_x,sel_y;				/* currently selected cell */
	uint16_t padding;
	
	PhDim_t swatch_dim;					/* dimensions of popup swatch */
	
	PtColorPaletteNode_t *clist;		/* list of colors in palette */	

} PtColorPaletteWidget_t;


/* Widget union */

typedef union pt_colorpalette_union
{
	PtWidget_t						core;
	PtBasicWidget_t					basic;
	PtContainerWidget_t				container;
	PtCompoundWidget_t				compound;
	PtColorSelWidget_t				colorsel;
	PtColorPaletteWidget_t			colorpalette;

} PtColorPaletteUnion_t;


#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtColorPalette.h $ $Rev: 219996 $" )
#endif
