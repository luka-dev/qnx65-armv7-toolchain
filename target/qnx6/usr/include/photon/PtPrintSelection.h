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



#ifndef __PT_PRINTSELECTION_H_INCLUDED
#define __PT_PRINTSELECTION_H_INCLUDED

/************************************************************************
 *
 *	PtPrintSelection.h
 *		Header file for the PtPrintSelect convenience functions
 *

 *
 ************************************************************************/


#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct Pt_printselection_info {

	PhPoint_t pos;			/* Desired/Terminal position of the print-selection dialog */
	char *btn1;				/* label of the 'Cancel' button */
	char *btn2;				/* label of the 'Preview' button */
	char *btn3;				/* label of the 'Print' button */
	int flags;				/* print selection flags */
	int num_args;			/* Number of args to set in the PtPrintSel widget */
	PtArg_t *args;			/* args for the PtPrintSel widget */

} PtPrintSelectionInfo_t;


/*-----------------------------------------------
 * Flags for the PrintSelect convenience function
 *-----------------------------------------------*/
#define Pt_PRINTSEL_CENTER		0x0001	/* Center the printselection dialog wrt to the screen or its parent */
										/* 'pos' is ignored if this flag is set */

#define Pt_PRINTSEL_NO_PREVIEW	0x0002	/* Disable the "Preview" button */



/*-----------------------------------------------------------
 * Return values of the PtPrintSelect() convenience functions
 *-----------------------------------------------------------*/
#define Pt_PRINTSEL_PRINT				1
#define Pt_PRINTSEL_PREVIEW			2
#define Pt_PRINTSEL_CANCEL			3
#define Pt_PRINTSEL_ERROR				-1	/* No print-context or PtPrintSelectionInfo_t is NULL */



/*-----------------------------------------------------
 * Prototype of the 'PtPrintSelect' convenience function
 *-----------------------------------------------------*/
int PtPrintSelect( PtWidget_t *parent, char const *title, PtPrintSelectionInfo_t *info );


#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtPrintSelection.h $ $Rev: 219996 $" )
#endif
