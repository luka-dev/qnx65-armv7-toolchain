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
#ifndef __AW_FILE_SELECT_H_INCLUDED
#define __AW_FILE_SELECT_H_INCLUDED

#ifndef __PT_WIDGET_H_INCLUDED
 #include <PtWidget.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern PtWidgetClassRef_t *AwFileSelect;

typedef struct {
	PtWidget_t				core;
	char					*dirpath;
	char					*filespec;
	char					*filename;
	char					*action_txt;
	char					*cancel_txt;
	PtCallbackList_t		*action;
	PtCallbackList_t		*cancel;
} AwFileSelectWidget_t;

/* callback structure */
typedef struct {
	char					*dirpath;
	char					*filename;
	char					*filespec;
	} AwFileSelectCallback_t;

/* resources */
#define Aw_ARG_DIRECTORY_PATH 	Pt_RESOURCE( AB_PhAB( 2 ), 0 )
#define Aw_ARG_FILE_SPEC      	Pt_RESOURCE( AB_PhAB( 2 ), 1 )
#define Aw_ARG_FILE_NAME      	Pt_RESOURCE( AB_PhAB( 2 ), 2 )
#define Aw_ARG_ACTION_TEXT    	Pt_RESOURCE( AB_PhAB( 2 ), 3 )
#define Aw_ARG_CANCEL_TEXT    	Pt_RESOURCE( AB_PhAB( 2 ), 4 )

/* callback resources */
#define Aw_CB_FS_ACTION			Pt_RESOURCE( AB_PhAB( 2 ), 5 )
#define Aw_CB_FS_CANCEL			Pt_RESOURCE( AB_PhAB( 2 ), 6 )

#ifdef __cplusplus
};
#endif
#endif


#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ap/public/photon/AwFileSelect.h $ $Rev: 224582 $" )
#endif
