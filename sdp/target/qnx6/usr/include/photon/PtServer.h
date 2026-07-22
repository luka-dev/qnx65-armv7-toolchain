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
 *	PtServer.h
 *		Header file for the PtServer widget class
 *

 */
#ifndef __PT_SERVER_H_INCLUDED
#define __PT_SERVER_H_INCLUDED

#ifndef __PT_REGION_H_INCLUDED
 #include <photon/PtRegion.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtServer public
 */

extern PtWidgetClassRef_t *const PtServer;

/* Resources */

#define Pt_ARG_SERVER_SEND			Pt_RESOURCE( 98,  2 )
#define Pt_ARG_SERVER_CONNECTION	Pt_RESOURCE( 98,  6 )
#define Pt_ARG_SERVER_NAME			Pt_RESOURCE( 98,  7 )
#define Pt_CB_SERVER_RECEIVE		Pt_RESOURCE( 98,  3 )
#define Pt_CB_SERVER_TRANSPORT		Pt_RESOURCE( 98,  4 )
#define Pt_CB_SERVER_CONNECTED		Pt_RESOURCE( 98,  8 )
#define Pt_CB_SERVER_ERROR			Pt_RESOURCE( 98,  9 )


/* Callback structure */
typedef struct Pt_server_callback {
	void const *message;
	unsigned msg_len;
	void *reply;
	unsigned reply_len;
	}
		PtServerCallback_t;

typedef struct Pt_server_error_callback {
	int action;
	int errnum;
	int where; /* see enum PtConnectionServerError */
	}
		PtServerErrorCallback_t;

/* Widget structure */

typedef struct Pt_server_widget {
	PtRegionWidget_t	reg;
	struct Pt_connection_server *connection;
/*	PtCallbackList_t *receive; */
/*	PtCallbackList_t *transport; */
/*	PtCallbackList_t *connected; */
/*	PtCallbackList_t *errorcb; */
	int consumed;
	struct Pt_connector *ctor;
	char *name;
	long reserved[ 9 ];
	}
		PtServerWidget_t;

/* Widget union */
typedef union Pt_server_union {
	PtWidget_t				core;
	PtBasicWidget_t			basic;
	PtContainerWidget_t		cntnr;
	PtRegionWidget_t		reg;
	PtServerWidget_t		clnt;
	}
		PtServerUnion_t;


typedef void const *PtServerMsgF_t(
	PtWidget_t *widget,
	unsigned long type, void const *msg, unsigned len,
	unsigned *reply_len
	);

typedef struct Pt_server_widget_class {
    PtContainerClass_t	container;
	PtServerMsgF_t		*msgfun;
	}
		PtServerClass_t;

#define Pt_SET_SERVER_MSG_F	Pt_ARG_IS_POINTER( PtServerClass_t, msgfun )

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtServer.h $ $Rev: 219996 $" )
#endif
