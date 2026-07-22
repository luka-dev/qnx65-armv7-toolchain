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
 *	PtColorSelect.h
 *		Header file for the PtColorSelect() convenience functions
 *

 */

#ifndef __PT_COLORSELECT_H_INCLUDED
#define __PT_COLORSELECT_H_INCLUDED

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

#define Pt_COLORSELECT_LOAD_PALETTE		0x1		/* load palette for me */
#define Pt_COLORSELECT_RECYCLE			0x2		/* don't destroy dialog after use */
#define Pt_COLORSELECT_MODAL			0x4		/* do not return until selection made */
#define Pt_COLORSELECT_USE_SIZE			0x8		/* override default size */
#define Pt_COLORSELECT_USE_POS			0x10	/* override default pos (centering) */
#define Pt_COLORSELECT_POS_RELATIVE		0x20	/* position relative to parent */

/* following flags cannot be passed to the function, they will be set accordingly
   by the function to indicate exit state */

#define Pt_COLORSELECT_RO_FLAGS			0xf000
   
#define Pt_COLORSELECT_CHANGED			0x2000	/* indicates a change in color */
#define Pt_COLORSELECT_DISMISS			0x4000	/* dialog was dismissed */
#define Pt_COLORSELECT_ACCEPT			0x8000	/* selected color was accepted */
#define Pt_COLORSELECT_ACCEPT_DISMISS	(Pt_COLORSELECT_ACCEPT | Pt_COLORSELECT_DISMISS)


typedef struct pt_colorselector_spec
{
	PtWidgetClassRef_t *wclass;	/* class of color selector */
	char const *name;			/* name to assign to associated panel */
	PtArg_t const *args;		/* argument array to set on widget */
	uint32_t nargs;				/* length of argument array */

} PtColorSelectorSpec_t;


typedef struct pt_colorselect_info
{
	/*****************************
	 * dialog control parameters */
	
	uint16_t flags;						/* behavioural flags including user response bits */
	uint8_t nselectors;					/* number of subordinate selectors specified */
	uint8_t ncolor_models;				/* number of color models specified */

	PgColorModel_t **color_models;		/* user-defined color models to install */
	PtColorSelectorSpec_t *selectors;	/* user-define list of color selectors to use */

	PhPoint_t pos;						/* for position overriding */
	PhDim_t size;						/* for size overriding */
	
	/* allows user to specify palette as an instance or filename to load */
	
	union
	{
		PgPalette_t *instance;
		char const *filename;
	
	} palette;

	char const *accept_text;			/* alternate text for accept button */
	char const *dismiss_text;			/* alternate text for cancel/done button */
	char const *accept_dismiss_text;	/* applies only to non-modal dialogs */

	/* end of dialog control          *
	 **********************************
	 * non-modal operation parameters */
	
	void (*apply_f)(struct pt_colorselect_info const *);	/* apply color callback */
	void *data;												/* arbitrary data useful for identifying structure */
	
	/* end of non-modal parameters *
	 *******************************
	 * returned info               */
	
	PgColor_t rgb;				/* selected color */
	PtWidget_t *dialog;			/* recycled dialog widget */
	
} PtColorSelectInfo_t;

extern int PtColorSelect( PtWidget_t *, char const *, PtColorSelectInfo_t * );
extern void PtColorSelectSetColor( PtColorSelectInfo_t *, PgColor_t );

#define PtColorSelectChanged(csinfo) \
	((((PtColorSelectInfo_t*)(csinfo))->flags & (Pt_COLORSELECT_ACCEPT | Pt_COLORSELECT_CHANGED)) == \
	(Pt_COLORSELECT_ACCEPT | Pt_COLORSELECT_CHANGED))

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtColorSelect.h $ $Rev: 219996 $" )
#endif
