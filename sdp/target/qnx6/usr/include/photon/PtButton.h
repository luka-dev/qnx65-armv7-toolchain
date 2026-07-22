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
 *	PtButton.h
 *		Header file for the PtButton widget class
 *

 */
#ifndef __PT_BUTTON_H_INCLUDED
#define __PT_BUTTON_H_INCLUDED

#ifndef __PT_LABEL_H_INCLUDED
 #include <photon/PtLabel.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtButton public
 */

extern PtWidgetClassRef_t *PtButton;

#define Pt_BUTTON_ID	6

/* Resources */
#define	Pt_ARG_ARM_COLOR		Pt_RESOURCE( 6, 0 )
#define	Pt_ARG_ARM_IMAGE		Pt_RESOURCE( 6, 1 )
#define	Pt_ARG_ARM_DATA			Pt_ARG_ARM_IMAGE
#define	Pt_ARG_ARM_FILL			Pt_RESOURCE( 6, 2 )
#define Pt_ARG_SET_FILL			Pt_ARG_ARM_FILL

/*
 * PtButton private
 */

/* Widget structure */
typedef struct Pt_button_widget {
	PtLabelWidget_t			label;
	PgColor_t				arm_color;
	PhImage_t				*arm_data;
	PhImage_t				*unarmed_data;
	uchar_t					arm_fill;
/*	PtCallbackList_t		*activate; */
} PtButtonWidget_t;

/* Widget union */
typedef union Pt_button_union {
	PtWidget_t				core;
	PtBasicWidget_t			basic;
	PtLabelWidget_t			label;
	PtButtonWidget_t		button;
} PtButtonUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtButton.h $ $Rev: 219996 $" )
#endif
