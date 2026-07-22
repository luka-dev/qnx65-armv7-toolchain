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



#ifndef __Pt_PRINTSEL_H_INCLUDED
#define __Pt_PRINTSEL_H_INCLUDED

/*****************************************************************

 PtPrintSel.h



******************************************************************/


#ifndef __PT_CONTAINER_H_INCLUDED
#include <PtContainer.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


extern PtWidgetClassRef_t *PtPrintSel;


#define PS_NUM_WIDGETS	33	/* Number of subordinate widgets */


typedef struct {

	PtContainerWidget_t		container;
	PtWidget_t				*w[PS_NUM_WIDGETS];
	char					**prop_strings;	/* labels for the Properties dialog */
	void					*dlist;			/* printer properties descriptor list */
	PtWidget_t				*spare00;
	pid_t					spare01;
/*	PtCallbackList_t		*propcbs, *filecbs; */
	char					ncopies, spare02, *filename;
	short					source;
	char					modified_prop[Pp_PC_FLAGSIZE];
	unsigned short			flags;
	short					nprinters;		/* number of installed printers */
	short					spare03;
	char					**pnames;		/* names of the available printers */
	PpPrintContext_t		*pcontext;		/* print context */
	unsigned short			prvt_flags;		/* private flags */
} PtPrintSelWidget_t;


/*----------------------------------
 * Resources for basic functionality
 *----------------------------------*/
#define Pt_ARG_PRINT_CONTEXT			Pt_RESOURCE(46,  0)
#define Pt_ARG_PRINT_FLAGS				Pt_RESOURCE(46,  1)
#define Pt_ARG_PRINT_FILE				Pt_RESOURCE(46,  2)
#define Pt_CB_PRINT_PROPS				Pt_RESOURCE(46,  3)
#define Pt_CB_PRINT_FILE				Pt_RESOURCE(46,  4)		/* No longer used */


/*-----------------
 * String resources
 *-----------------*/
#define Pt_ARG_PS_LBL_FILE				Pt_RESOURCE(46,  5)		/* 'File:' label */
#define Pt_ARG_PS_LBL_NAME				Pt_RESOURCE(46,  6)		/* 'Name:' label */
#define Pt_ARG_PS_LBL_DESCRIPTION		Pt_RESOURCE(46,  7)		/* 'Description:' label	(NO LONGER USED!!!) */
#define Pt_ARG_PS_LBL_COPIES			Pt_RESOURCE(46,  8)		/* 'Copies:' label */
#define Pt_ARG_PS_LBL_FROM				Pt_RESOURCE(46,  9)		/* 'From:' label */
#define Pt_ARG_PS_LBL_TO				Pt_RESOURCE(46, 10)		/* 'To:' label */
#define Pt_ARG_PS_LBL_COLLATED			Pt_RESOURCE(46, 11)		/* Label of 'Print Collated' toggle button */
#define Pt_ARG_PS_LBL_NOT_COLLATED		Pt_RESOURCE(46, 12)		/* Label of 'Print Not Collated' toggle button */
#define Pt_ARG_PS_LBL_DOUBLE_SIDED		Pt_RESOURCE(46, 13)		/* Label of 'Print Double Sided' toggle button */
#define Pt_ARG_PS_LBL_REVERSED			Pt_RESOURCE(46, 14)		/* Label of 'Print Reversed Order' toggle button */
#define Pt_ARG_PS_LBL_PRINT_ORDER		Pt_RESOURCE(46, 15)		/* Title of 'Print Order' pane */
#define Pt_ARG_PS_LBL_PRINT_PAGES		Pt_RESOURCE(46, 16)		/* Title of 'Print Pages' pane */
#define Pt_ARG_PS_LBL_ALL				Pt_RESOURCE(46, 17)		/* Label of 'Print All Pages' button */
#define Pt_ARG_PS_LBL_SELECTION			Pt_RESOURCE(46, 18)		/* Label of 'Print Selection' button */
#define Pt_ARG_PS_LBL_RANGE				Pt_RESOURCE(46, 19)		/* Label of 'Print Range' button */
#define Pt_ARG_PS_LBL_PREFERENCES		Pt_RESOURCE(46, 20)		/* Label of 'Preferences' button */
#define Pt_ARG_PS_LBL_INSTALL			Pt_RESOURCE(46, 21)		/* 'Install..." label (NO LONGER USED!!!) */
#define Pt_ARG_PS_LBL_SEND_TO_FILE		Pt_RESOURCE(46, 22)		/* Title of 'Send to file' pane */
#define Pt_ARG_PS_LBL_SEND_TO_PRINTER	Pt_RESOURCE(46, 23)		/* Title of 'Send to printer' pane */


/*---------------------
 * Print Selector Flags
 *---------------------*/
#define Pt_PRINTSEL_FILE_PANE			0x0001	/* Enable the "Send to file" pane */
#define Pt_PRINTSEL_SETTINGS_PANE		0x0002	/* Enable the "Print Pages", "Print Order" and "Copies" panes */
#define Pt_PRINTSEL_PREFERENCES			0x0004	/* Enable the "Preferences" button */
#define Pt_PRINTSEL_NO_PAGE_RANGE		0x0008	/* Disable the "Print Range" toggle button and the "From", "To" numeric integer widgets */
#define Pt_PRINTSEL_NO_SELECT_RANGE		0x0010	/* Disable the "Print Selection" toggle button */
#define Pt_PRINTSEL_NO_COPIES			0x0020	/* Disable the "Copies" numeric integer widget */
#define Pt_PRINTSEL_NO_COLLATE			0x0040	/* No longer used */
#define Pt_PRINTSEL_NO_REVERSED			0x0080	/* No longer used */
#define Pt_PRINTSEL_NO_DOUBLE_SIDED		0x0100	/* No longer used */
#define Pt_PRINTSEL_NO_INSTALL			0x0200	/* No longer used */
#define Pt_PRINTSEL_NO_PRINTSELECT		0x0400	/* The default printer name can not be changed, even if */
												/* other printers are available. */

#define Pt_PRINTSEL_ALL_PANES			( Pt_PRINTSEL_FILE_PANE | Pt_PRINTSEL_SETTINGS_PANE )
#define Pt_PRINTSEL_DFLT_LOOK			( Pt_PRINTSEL_ALL_PANES | Pt_PRINTSEL_PREFERENCES )
#define Pt_PRINTSEL_PROP_APP			Pt_PRINTSEL_PREFERENCES		/* Legacy */


/*----------------------------------
 * Pt_CB_PRINT_PROPS reason subtypes
 *----------------------------------*/
#define Pt_CB_PRINT_PROPS_START			0x0001	/* Properties callback */
#define Pt_CB_PRINT_PROPS_END			0x0002	/* Returned from properties callback */


#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtPrintSel.h $ $Rev: 219996 $" )
#endif
