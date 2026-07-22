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
 *	PtColorSel.h
 *		Header file for the PtColorSel meta class
 *

 */
 
#ifndef __PT_COLORSEL_H_INCLUDED
#define __PT_COLORSEL_H_INCLUDED

#include <photon/PtCompound.h>
#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

extern PtWidgetClassRef_t *PtColorSel;

/* Resources */

#define Pt_ARG_CS_FLAGS				Pt_RESOURCE( 150, 0 )
#define Pt_ARG_CS_COLOR				Pt_RESOURCE( 150, 1 )
#define Pt_ARG_CS_COLOR_MODELS		Pt_RESOURCE( 150, 2 )
#define Pt_ARG_CS_CURRENT_MODEL		Pt_RESOURCE( 150, 3 )
#define Pt_ARG_CS_PALETTE			Pt_RESOURCE( 150, 4 )
#define Pt_CB_CS_COLOR_CHANGED		Pt_RESOURCE( 150, 5 )

/* Pt_ARG_CS_FLAGS manifests */

#define Pt_CS_FAST_UPDATE			0x1
#define Pt_CS_QUANTIZE_COLOR		0x2		/* Ensure Pt_ARG_CS_COLOR_RGB is always quantized to palette */
#define Pt_CS_QUANTIZE_DISPLAY		0x4		/* Show effects of palette quantization in widget display */

#define Pt_CS_GAMUT_WARNING			0x8000	/* r/o, indicates color mapping accuracy loss */
#define Pt_CS_RO_FLAGS				0xf000

/* Pt_CB_CS_COLOR_CHANGED callback reason_subtypes, may be ORred together.  If reason_subtype is 0, can
   be deemed as a hi-bandwidth change */

#define Pt_CS_COLOR_CHANGED			1	/* Lo-bandwidth change (eg click, set) */
#define Pt_CS_COLOR_CHANGE_COMPLETE	2	/* UI-effected change deemed "complete" */

#define Pt_CS_LOCK_CHANNEL			-1

/* structure used for transporting color across apps */

typedef struct pt_color
{
	PgColor_t rgb;
	uchar_t color_model_id;
	uchar_t padding[3];
	PgColorChannel_t channels[Pg_CM_MAX_CHANNELS];

} PtColor_t;

/* Callback structure for Pt_CB_CS_COLOR_CHANGED */

typedef struct colorsel_callback
{
	PgColor_t rgb;
	PgColorModel_t const *color_model;
	PgColorChannel_t const *channels;
	
} PtColorSelCallback_t;


/* Widget structure */

typedef struct pt_colorsel_widget
{
	PtCompoundWidget_t compound;

	PgColorModel_t **color_models;			/* Color models that this selector uses */
	PgColorChannel_t *channels;				/* channels that current model is using */

	uint8_t nmodels;						/* Number of color models used */
	uint8_t current_model;					/* Current color model in use */
	uint16_t flags;

	PgColor_t rgb;							/* Currently selected color (rgb) */
	PgPalette_t *palette;					/* Palette to conform to */	

} PtColorSelWidget_t;


/* Widget union */

typedef union pt_colorsel_union
{
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtContainerWidget_t			container;
	PtCompoundWidget_t			compound;
	PtColorSelWidget_t			colorsel;

} PtColorSelUnion_t;

extern void PtCSColorChangedCallback(PtWidget_t *,int,PgColorModel_t const *,PgColorChannel_t const *,PhEvent_t const *);
extern void PtCSUpdateChannels(PtWidget_t*);
extern void PtCSUpdateRGB(PtWidget_t*);
extern int PtCSShmemAvailable(PtWidget_t *);
extern int PtCSGetColor(PtWidget_t*,PtArg_t*,PtResourceRec_t const*);
extern int PtCSGeneratePatch(void*,PhDim_t const*,PgColorModel_t const*,PgColorChannel_t const*,int,int,uint_t,int);

/*#define PtCSCurrentModel(w)		(((PtColorSelWidget_t*)(w))->color_models[((PtColorSelWidget_t*)(w))->current_model])*/
#define PtCSCurrentModel(w)		(PtMember(PtColorSel,w,color_models)[PtMember(PtColorSel,w,current_model)])

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtColorSel.h $ $Rev: 219996 $" )
#endif
