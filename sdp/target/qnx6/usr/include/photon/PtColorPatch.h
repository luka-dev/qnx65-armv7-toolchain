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
 *	PtColorPatch.h
 *		Header file for the PtColorPatch widget class
 *

 */
 
#ifndef __PT_COLORPATCH_H_INCLUDED
#define __PT_COLORPATCH_H_INCLUDED

#include <photon/PtColorSel.h>
#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

extern PtWidgetClassRef_t *PtColorPatch;

/* Resources */

#define Pt_ARG_CPATCH_FLAGS			Pt_RESOURCE( 151, 0 )

#define Pt_CPATCH_SHOW_SELECTOR	0x1		/* show combobox patch selector */
#define Pt_CPATCH_ENABLE_MENU	0x2		/* allow popup menu */
#define Pt_CPATCH_SHOW_SLIDER	0x4		/* show slider */

#define Pt_CPATCH_FAST_UPDATE	0x1000	/* read-only */
#define Pt_CPATCH_RESIZE_IMAGE	0x2000	/* read-only */
#define Pt_CPATCH_UPDATE_XY		0x4000	/* read-only */
#define Pt_CPATCH_UPDATE_Z		0x8000	/* read-only */
#define Pt_CPATCH_UPDATE_XYZ	(Pt_CPATCH_UPDATE_XY | Pt_CPATCH_UPDATE_Z)
#define Pt_CPATCH_RO_FLAGS		0xf000

/* Widget structure */

typedef struct pt_colorpatch_widget
{
	PtColorSelWidget_t colorsel;

	uchar_t *image;						/* precomputed color image */
	long xy_crc,z_crc;					/* crc tags for images */

	PtWidget_t *slider;					/* z-axis slider widget */
	PtWidget_t *raw;					/* xy-plane widget */
	PtWidget_t *combobox;				/* Colorpatch selector widget */
	PtWidget_t *label;

	short *axes;						/* channels in x,y,z axes for each model */
	
	ushort_t x_width,y_height,z_height;	/* lengths of axes */
	ushort_t flags;
	
} PtColorPatchWidget_t;


/* Widget union */

typedef union pt_colorpatch_union
{
	PtWidget_t						core;
	PtBasicWidget_t					basic;
	PtContainerWidget_t				container;
	PtCompoundWidget_t				compound;
	PtColorSelWidget_t				colorsel;
	PtColorPatchWidget_t			colorpatch;

} PtColorPatchUnion_t;

#define PtCPatchXAxis(w)		(((PtColorPatchWidget_t*)(w))->axes[((PtColorSelWidget_t*)(w))->current_model] & 0xf)
#define PtCPatchYAxis(w)		((((PtColorPatchWidget_t*)(w))->axes[((PtColorSelWidget_t*)(w))->current_model] & 0xf0) >> 4)
#define PtCPatchZAxis(w)		((((PtColorPatchWidget_t*)(w))->axes[((PtColorSelWidget_t*)(w))->current_model] & 0xf00) >> 8)
#define PtCPatchSetXAxis(w,c)	(((PtColorPatchWidget_t*)(w))->axes[((PtColorSelWidget_t*)(w))->current_model] = \
									(((PtColorPatchWidget_t*)(w))->axes[((PtColorSelWidget_t*)(w))->current_model] & 0xff0) | (c & 0xf))
#define PtCPatchSetYAxis(w,c)	(((PtColorPatchWidget_t*)(w))->axes[((PtColorSelWidget_t*)(w))->current_model] = \
									(((PtColorPatchWidget_t*)(w))->axes[((PtColorSelWidget_t*)(w))->current_model] & 0xf0f) | ((c & 0xf) << 4))
#define PtCPatchSetZAxis(w,c)	(((PtColorPatchWidget_t*)(w))->axes[((PtColorSelWidget_t*)(w))->current_model] = \
									(((PtColorPatchWidget_t*)(w))->axes[((PtColorSelWidget_t*)(w))->current_model] & 0xff) | ((c & 0xf) << 8))

extern void PtCPatchUpdate(PtWidget_t const *);
extern int PtCPatchUpdateImage(PtWidget_t*);


#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtColorPatch.h $ $Rev: 219996 $" )
#endif
