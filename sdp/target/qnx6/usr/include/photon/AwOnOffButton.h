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
#ifndef __AW_ONOFF_BUTTON_H_INCLUDED
#define __AW_ONOFF_BUTTON_H_INCLUDED

#ifndef __PT_TOGGLE_BUTTON_H_INCLUDED
 #include <PtToggleButton.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern PtWidgetClass_t *AwOnOffButton;

typedef struct Aw_onoff_button_widget {
	PtToggleButtonWidget_t	tbutton;
	uchar_t					state;
	PtCallbackList_t		*new_value;
} AwOnOffButtonWidget_t;

/* callback structure */
typedef struct {
	int		state;
	} AwOnOffButtonCallback_t;

#define Aw_CB_ONOFF_NEW_VALUE	Pt_RESOURCE( 5, 0 )
#define Aw_ARG_ONOFF_STATE    	Pt_RESOURCE( 5, 1 )

/* prototypes */
extern	void			 AwDfltsOnOffButton( PtWidget_t *widget );
extern	int				 AwInitOnOffButton( PtWidget_t *widget );
extern	void			 AwDrawOnOffButton( PtWidget_t *widget );
extern	int				 AwDestroyOnOffButton( PtWidget_t *widget );
extern	void			 AwOnOffButtonValue( PtWidget_t *widget, void *data, PtCallbackInfo_t *cbinfo );
extern	PtWidgetClass_t	*AwCreateOnOffButtonClass( void );

#ifdef __cplusplus
};
#endif
#endif


#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ap/public/photon/AwOnOffButton.h $ $Rev: 224582 $" )
#endif
