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



#ifndef __PT_FONTSELECTION_H_INCLUDED
#define __PT_FONTSELECTION_H_INCLUDED

/*********************************************************************************
 *
 *	PtFontSelection.h
 *		Header file for the PtFontSelect and PtFontSelection convenience functions
 *

 *
 *********************************************************************************/

#ifndef __PF_H_INCLUDED
#include <photon/Pf.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct Pt_fontselection_info
{
	FontName font;
	PhArea_t area;			/* Desired area of the font-selection dialog */
	char *btn1;				/* label of the 'Apply' button */
	char *btn2;				/* label of the 'Cancel' button */
	int num_args;			/* Number of args to set in the PtFontsel widget */
	PtArg_t *args;			/* args for the PtFontSel widget */
	uint32_t flags;			/* flags */
} PtFontSelectionInfo_t;


#define Pt_FONTSELECT_CENTER	0x1

/*-----------------------
 * PtFontSelect() buttons
 *-----------------------*/

#define Pt_FONTSELECT_CANCEL	1
#define Pt_FONTSELECT_ACCEPT	2

extern int PtFontSelect( PtWidget_t *parent, char const *title, PtFontSelectionInfo_t *info );

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtFontSelection.h $ $Rev: 219996 $" )
#endif
