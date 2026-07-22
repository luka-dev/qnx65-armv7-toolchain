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
#ifndef __AW_MESSAGE_H_INCLUDED
#define __AW_MESSAGE_H_INCLUDED

#ifndef __PT_WIDGET_H_INCLUDED
 #include <photon/PtWidget.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

extern PtWidgetClassRef_t *AwMessage;

typedef struct {
	PtWidget_t				core;
	char					*title;
	char					*text;
	char					*font;
	char					*button1_txt;
	char					*button2_txt;
	char					*button3_txt;
	short					def_button;
	#if defined(__QNXNTO__)
		short				filler;
	#endif
	PtWidget_t				*dlg;
	PtWidget_t				*msg;
	PtWidget_t				*opt;
	PtCallbackList_t		*button1;
	PtCallbackList_t		*button2;
	PtCallbackList_t		*button3;
} AwMessageWidget_t;

/* resources */
#define Aw_ARG_MSG_TITLE		Pt_RESOURCE( AB_PhAB( 3 ), 0 )
#define Aw_ARG_MSG_TEXT       	Pt_RESOURCE( AB_PhAB( 3 ), 1 )
#define Aw_ARG_MSG_FONT       	Pt_RESOURCE( AB_PhAB( 3 ), 3 )
#define Aw_ARG_MSG_BUTTON1    	Pt_RESOURCE( AB_PhAB( 3 ), 4 )
#define Aw_ARG_MSG_BUTTON2    	Pt_RESOURCE( AB_PhAB( 3 ), 5 )
#define Aw_ARG_MSG_BUTTON3    	Pt_RESOURCE( AB_PhAB( 3 ), 6 )
#define Aw_ARG_MSG_DEFAULT    	Pt_RESOURCE( AB_PhAB( 3 ), 7 )

/* callback resources */
#define Aw_CB_MSG_BUTTON1		Pt_RESOURCE( AB_PhAB( 3 ), 8 )
#define Aw_CB_MSG_BUTTON2		Pt_RESOURCE( AB_PhAB( 3 ), 9 )
#define Aw_CB_MSG_BUTTON3		Pt_RESOURCE( AB_PhAB( 3 ),10 )

/* prototypes */
extern	PtWidgetClass_t	*AwCreateMessageClass( void );

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif


#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ap/public/photon/AwMessage.h $ $Rev: 224582 $" )
#endif
