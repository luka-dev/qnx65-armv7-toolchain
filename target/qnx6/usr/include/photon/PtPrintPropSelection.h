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
#ifndef __Pt_PRINT_PROP_SELECTION_H_INCLUDED
#define __Pt_PRINT_PROP_SELECTION_H_INCLUDED

#ifndef __PPCTRL_H_INCLUDED
#include <photon/PpT.h>
#endif


#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*-----------------
 * String resources
 *-----------------*/
#define Pt_PSP_ID							72

#define Pt_ARG_PSP_LBL_CANCEL				Pt_RESOURCE( Pt_PSP_ID,  0 )
#define Pt_ARG_PSP_LBL_APPLY				Pt_RESOURCE( Pt_PSP_ID,  1 )
#define Pt_ARG_PSP_LBL_DONE					Pt_RESOURCE( Pt_PSP_ID,  2 )

#define Pt_ARG_PSP_LBL_SAVE_DFLT    		Pt_RESOURCE( Pt_PSP_ID,  3 )
#define Pt_ARG_PSP_LBL_LOAD_DFLT    		Pt_RESOURCE( Pt_PSP_ID,  4 )
#define Pt_ARG_PSP_LBL_LOAD_GLOBAL_DFLT    	Pt_RESOURCE( Pt_PSP_ID,  5 )

#define Pt_ARG_PSP_LBL_TITLE				Pt_RESOURCE( Pt_PSP_ID,  6 )
#define Pt_ARG_PSP_LBL_TITLE_PAPER			Pt_RESOURCE( Pt_PSP_ID,  7 )
#define Pt_ARG_PSP_LBL_TITLE_GRAPHICS		Pt_RESOURCE( Pt_PSP_ID,  8 )
#define Pt_ARG_PSP_LBL_TITLE_MARGINS		Pt_RESOURCE( Pt_PSP_ID,  9 )
#define Pt_ARG_PSP_LBL_TITLE_PRINT_ORDER	Pt_RESOURCE( Pt_PSP_ID, 10 )
#define Pt_ARG_PSP_LBL_TITLE_PRINTERS		Pt_RESOURCE( Pt_PSP_ID, 11 )
#define Pt_ARG_PSP_LBL_TITLE_DFLT			Pt_RESOURCE( Pt_PSP_ID, 12 )

#define Pt_ARG_PSP_LBL_PAPERSIZE			Pt_RESOURCE( Pt_PSP_ID, 13 )
#define Pt_ARG_PSP_LBL_PAPERSOURCE			Pt_RESOURCE( Pt_PSP_ID, 14 )
#define Pt_ARG_PSP_LBL_PAPERTYPE			Pt_RESOURCE( Pt_PSP_ID, 15 )
#define Pt_ARG_PSP_LBL_ORIENTATION			Pt_RESOURCE( Pt_PSP_ID, 16 )
#define Pt_ARG_PSP_LBL_PORTRAIT				Pt_RESOURCE( Pt_PSP_ID, 17 )
#define Pt_ARG_PSP_LBL_LANDSCAPE			Pt_RESOURCE( Pt_PSP_ID, 18 )

#define Pt_ARG_PSP_LBL_COLORMODE			Pt_RESOURCE( Pt_PSP_ID, 19 )
#define Pt_ARG_PSP_LBL_DITHERING			Pt_RESOURCE( Pt_PSP_ID, 20 )
#define Pt_ARG_PSP_LBL_RESOLUTION			Pt_RESOURCE( Pt_PSP_ID, 21 )
#define Pt_ARG_PSP_LBL_INTENSITY			Pt_RESOURCE( Pt_PSP_ID, 22 )
#define Pt_ARG_PSP_LBL_DARKEST				Pt_RESOURCE( Pt_PSP_ID, 23 )
#define Pt_ARG_PSP_LBL_LIGHTEST				Pt_RESOURCE( Pt_PSP_ID, 24 )

#define Pt_ARG_PSP_LBL_TOP					Pt_RESOURCE( Pt_PSP_ID, 25 )
#define Pt_ARG_PSP_LBL_BOTTOM				Pt_RESOURCE( Pt_PSP_ID, 26 )
#define Pt_ARG_PSP_LBL_LEFT					Pt_RESOURCE( Pt_PSP_ID, 27 )
#define Pt_ARG_PSP_LBL_RIGHT				Pt_RESOURCE( Pt_PSP_ID, 28 )
#define Pt_ARG_PSP_LBL_UNITS				Pt_RESOURCE( Pt_PSP_ID, 29 )
#define Pt_ARG_PSP_LBL_INCHES				Pt_RESOURCE( Pt_PSP_ID, 30 )
#define Pt_ARG_PSP_LBL_MILLIMETERS			Pt_RESOURCE( Pt_PSP_ID, 31 )

#define Pt_ARG_PSP_LBL_DEFAULT_PRINTER		Pt_RESOURCE( Pt_PSP_ID, 32 )
#define Pt_ARG_PSP_LBL_CURRENT_PRINTER		Pt_RESOURCE( Pt_PSP_ID, 33 )
#define Pt_ARG_PSP_LBL_REVERSED				Pt_RESOURCE( Pt_PSP_ID, 34 )
#define Pt_ARG_PSP_LBL_DOUBLE_SIDED			Pt_RESOURCE( Pt_PSP_ID, 35 )
#define Pt_ARG_PSP_LBL_COLLATED				Pt_RESOURCE( Pt_PSP_ID, 36 )
#define Pt_ARG_PSP_LBL_FONTMAP				Pt_RESOURCE( Pt_PSP_ID, 37 )


/*--------------
 * Return values
 *--------------*/
#define Pt_PSP_ERROR			-1				/* Bad/misssing info structure */
#define Pt_PSP_DONE				1				/* 'Done' button pressed */
#define Pt_PSP_CANCEL			2				/* 'Cancel' button pressed */


/*------
 * Flags
 *------*/
#define Pt_PSP_CENTER						0x0001	/* Center the printselection dialog wrt to the screen */
													/* or its parent 'pos' is ignored if this flag is set */

#define Pt_PSP_NO_GRAPHICS					0x0002	/* Do not display the 'Graphics' Pane */
#define Pt_PSP_NO_MARGINS					0x0004	/* Do not display the 'Margins' Pane */
#define Pt_PSP_NO_PAPER						0x0008	/* Do not display the 'Paper' Pane */
#define Pt_PSP_NO_PRINT_ORDER				0x0010	/* Do not display the 'Print Order' Pane */
#define Pt_PSP_NO_PRINTERS					0x0020	/* Do not display the 'Printers' Pane */
#define Pt_PSP_NO_DEFAULTS					0x0040	/* Do not display the 'Defaults' Pane */

#define Pt_PSP_NO_CANCEL_BUTTON				0x0080	/* Do not display the 'Cancel' button in the main button pane */
#define Pt_PSP_NO_APPLY_BUTTON				0x0100	/* Do not display the 'Apply' button in the main button pane */
#define Pt_PSP_NO_DONE_BUTTON				0x0200	/* Do not display the 'Done' button in the main button pane */

#define Pt_PSP_NO_SAVE_DFLT_BUTTON			0x0400	/* Do not display the 'Save Personal Defaults' button */
#define Pt_PSP_NO_LOAD_DFLT_BUTTON			0x0800	/* Do not display the 'Load Personal Defaults' button */
#define Pt_PSP_NO_LOAD_GLOBAL_DFLT_BUTTON	0x1000	/* Do not display the 'Load Global Defaults' button */


/*---------------
 * Info structure
 *---------------*/
typedef struct pt_print_prop_selection_info {
	PpPrintContext_t *pcontext;
	PhPoint_t pos;
	PtArg_t *args;
	int num_args;
	int flags;
	void *p;		/* Reserved. */
	int spare[8];	/* Reserved. */
} PtPrintPropSelectionInfo_t;


/*----------
 * Prototype
 *----------*/
int PtPrintPropSelect( PtWidget_t *parent, char const *title, PtPrintPropSelectionInfo_t *info );


#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
	

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtPrintPropSelection.h $ $Rev: 224590 $" )
#endif
