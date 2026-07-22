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
 *	PtClient.h
 *		Header file for the PtClient widget class
 *

 */
#ifndef __PT_CLIENT_H_INCLUDED
#define __PT_CLIENT_H_INCLUDED

#ifndef __PT_CONTAINER_H_INCLUDED
 #include <photon/PtContainer.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtClient public
 */

extern PtWidgetClassRef_t *const PtClient;

#define Pt_CLIENT_ID	99

/* Resources */

#define Pt_ARG_CLIENT_SERVER		Pt_RESOURCE( 99,  0 )
#define Pt_ARG_CLIENT_SEND			Pt_RESOURCE( 99,  1 )
#define Pt_ARG_CLIENT_REPLY_LEN		Pt_RESOURCE( 99,  2 )
#define Pt_ARG_CLIENT_NAME			Pt_RESOURCE( 99,  4 )
#define Pt_ARG_CLIENT_FLAGS			Pt_RESOURCE( 99,  7 )
#define Pt_CB_CLIENT_EVENT			Pt_RESOURCE( 99,  3 )
#define Pt_CB_CLIENT_CONNECTED		Pt_RESOURCE( 99,  6 )
#define Pt_CB_CLIENT_NOT_FOUND		Pt_RESOURCE( 99,  8 )
#define Pt_CB_CLIENT_ERROR			Pt_RESOURCE( 99,  9 )
#define Pt_ARG_CLIENT_FORCE_EXPOSE	Pt_RESOURCE( 99, 10 )


/* Flags in Pt_ARG_CLIENT_FLAGS */
#define Pt_CLIENT_NONBLOCK	0x0001
#define Pt_CLIENT_NOEVENTS	0x0002

/* Callback structure */
typedef struct Pt_client_callback {
	void const *message;
	unsigned nbytes;
	}
		PtClientCallback_t;

typedef struct Pt_client_error_callback {
	int action;
	int errnum;
	int where; /* see enum PtConnectionClientError */
	}
		PtClientErrorCallback_t;


/* Widget structure */

typedef struct Pt_client_widget {
	PtContainerWidget_t	cntr;
	struct Pt_connection_client *connection;
	void *reply;
	unsigned reply_len;
	int reply_nbytes;
	char *name;
	unsigned flags;
	PtWorkProcId_t *bgid;
	long reserved[ 8 ];
	}
		PtClientWidget_t;

/* Widget union */
typedef union Pt_client_union {
	PtWidget_t				core;
	PtBasicWidget_t			basic;
	PtContainerWidget_t		cntnr;
	PtClientWidget_t		clnt;
	}
		PtClientUnion_t;

typedef int PtClientNotifyF_t(
	PtWidget_t *widget, long type, void const *msg, unsigned len
	);

typedef struct Pt_client_widget_class {
    PtContainerClass_t	container;
	PtClientNotifyF_t	*notify;
	}
		PtClientClass_t;

#define Pt_SET_CLIENT_NOTIFY_F	Pt_ARG_IS_POINTER( PtClientClass_t, notify )

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif


#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtClient.h $ $Rev: 219996 $" )
#endif
