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
#ifndef __Pt_GLOBAL_FOCUS_H_INCLUDED
#define __Pt_GLOBAL_FOCUS_H_INCLUDED

/*---------------------------------
 * Global focus-rendering resources
 *---------------------------------*/
#define Pt_ARG_GFR_COLOR1		Pt_RESOURCE( 75, 0 )	/* Color used for outlines and underlines */
#define Pt_ARG_GFR_COLOR2		Pt_RESOURCE( 75, 1 )	/* Underline color in PtText when it loses focus */
#define Pt_ARG_GFR_COLOR3		Pt_RESOURCE( 75, 2 )	/* Fill color for ghosted PtText */
#define Pt_ARG_GFR_FLAGS		Pt_RESOURCE( 75, 3 )	/* Global focus flags */


/*-----------------------------
 * Global focus-rendering flags
 *-----------------------------*/
#define Pt_GFR_HEAVY_OUTLINE		0x0001		/* 1-Heavy outline, 0-light outline */

#define Pt_GFR_LBL_NO_UNDERLINE		0x0002		/* Do not underline text in labels */
#define Pt_GFR_LBL_OUTLINE			0x0004		/* Outline labels */

#define Pt_GFR_BTN_NO_UNDERLINE		0x0008		/* Do not underline text in buttons */
#define Pt_GFR_BTN_OUTLINE			0x0010		/* Outline buttons (always on for image-only buttons.) */

#define Pt_GFR_TGL_NO_UNDERLINE		0x0020		/* Do not underline text in toggle-buttons */
#define Pt_GFR_TGL_OUTLINE			0x0040		/* Outline togglebuttons */

#define Pt_GFR_TXT_NO_UNDERLINE		0x0080		/* Do not underline text in PtText when focused */
#define Pt_GFR_TXT_NO_UNDERLINE2	0x0100		/* Do not underline text using color2 in PtText when not focused */
#define Pt_GFR_TXT_OUTLINE			0x0200		/* Outline PtText */

#define Pt_GFR_CBX_OUTLINE			0x0400		/* Outline editable comboboxes. (Uneditable comboboxes are always outlined) */


/*-----------
 * Prototypes
 *-----------*/
void PtSetFocusRender( int num_args, PtArg_t *args );
void PtSetFocusRenderDflt( void );
int PtGetFocusRender( int num_args, PtArg_t *args );

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtFocusRender.h $ $Rev: 224590 $" )
#endif
