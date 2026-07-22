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
#ifndef __Pt_FONTSEL_H_INCLUDED
#define __Pt_FONTSEL_H_INCLUDED

#ifndef __PT_CONTAINER_H_INCLUDED
#include <photon/PtContainer.h>
#endif
#include <photon/Pf.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <photon/fontsel_old.h>

extern PtWidgetClassRef_t *PtFontSel;

#define Pt_FONTSEL_ID		38

#define Pt_ARG_FONT_NAME						Pt_RESOURCE( 38,  0 )
#define Pt_ARG_FONT_SAMPLE						Pt_RESOURCE( 38,  1 )
#define Pt_ARG_FONT_SYMBOL						Pt_RESOURCE( 38,  2 )
#define Pt_ARG_FONT_FLAGS						Pt_RESOURCE( 38,  3 )
#define Pt_CB_FONT_MODIFY						Pt_RESOURCE( 38,  4 )
#define Pt_ARG_FONT_DISPLAY						Pt_RESOURCE( 38,  5 )

#define Pt_ARG_FONT_LBL_FONT					Pt_RESOURCE( 38,  6 )	/* "Font:" */
#define Pt_ARG_FONT_LBL_STYLE					Pt_RESOURCE( 38,  7 )	/* "Style:" */
#define Pt_ARG_FONT_LBL_SIZE					Pt_RESOURCE( 38,  9 )	/* "Size:" */

#define Pt_ARG_FONT_TEXT_COLOR                  Pt_RESOURCE( 38, 16 )
#define Pt_ARG_FONT_TEXT_BKGD_COLOR             Pt_RESOURCE( 38, 17 )
#define Pt_ARG_FONT_LBL_TEXTCOLOR				Pt_RESOURCE( 38, 18 )
#define Pt_ARG_FONT_LBL_BKGDCOLOR				Pt_RESOURCE( 38, 19 )
#define Pt_ARG_FONT_POINT_SIZE_MAX				Pt_RESOURCE( 38, 20 )


#define Pt_FONTSEL_AA_CHECK		0x01
#define Pt_FONTSEL_SAMPLE		0x02
#define Pt_FONTSEL_COLORSEL_TEXT	0x04
#define Pt_FONTSEL_COLORSEL_BKGD	0x08

#define Pt_FONTSEL_SCALABLE		PHFONT_SCALABLE
#define Pt_FONTSEL_BITMAP		PHFONT_BITMAP
#define Pt_FONTSEL_PROP			PHFONT_PROP
#define Pt_FONTSEL_FIXED		PHFONT_FIXED
#define Pt_FONTSEL_ALL_FONTS	PHFONT_ALL_FONTS

#define Pt_FONTSEL_ALL_SYMBOLS	PHFONT_ALL_SYMBOLS

/*------------------------------
 * Number of subordinate widgets
 *------------------------------*/
typedef struct
{
	PtContainerWidget_t container;
	const char *font;
	char *text;
/*	PtCallbackList_t *changed; */
	FontDetails *details;
	int count;
	long symbol;
	struct
	{
		FontName face;
		int16_t size;
		int16_t style;
		int16_t pfr;
	} desc;
	uint16_t display;
	uint16_t flags;
	int16_t match;

} PtFontSelWidget_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtFontSel.h $ $Rev: 224590 $" )
#endif
