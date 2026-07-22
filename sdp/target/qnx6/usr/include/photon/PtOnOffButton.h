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
#ifndef __PT_ONOFF_BUTTON_H_INCLUDED
#define __PT_ONOFF_BUTTON_H_INCLUDED

#ifndef __PT_BUTTON_H_INCLUDED
 #include <photon/PtButton.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

extern PtWidgetClassRef_t *PtOnOffButton;

#define Pt_ONOFFBUTTON_ID	8	

#define Pt_ARG_ONOFF_STATE    	Pt_RESOURCE( 8, 0 )
#define Pt_CB_ONOFF_NEW_VALUE	Pt_RESOURCE( 8, 1 )
#define Pt_ARG_ONOFF_FLAGS    	Pt_RESOURCE( 8, 2 )

/* callback structure */

typedef struct {
	int		state;
} PtOnOffButtonCallback_t;

/* widget structure */

typedef struct Pt_onoff_button_widget
{
	PtButtonWidget_t button;
	PgColor_t reserved;
	ushort_t flags;
	uchar_t state;
	char padding;
/*	PtCallbackList_t *new_value; */

} PtOnOffButtonWidget_t;

/* Widget union */

typedef union Pt_onoff_button_union
{
	PtWidget_t				core;
	PtBasicWidget_t			basic;
	PtLabelWidget_t			label;
	PtButtonWidget_t		button;
	PtOnOffButtonWidget_t	onoff;
} PtOnOffButtonUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtOnOffButton.h $ $Rev: 224590 $" )
#endif
