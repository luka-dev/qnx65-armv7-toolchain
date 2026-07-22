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
 *	PtConnectionServer.h
 *

 */

#if !defined(__PT_CONNECTION_SERVER_H_INCLUDED)
#define __PT_CONNECTION_SERVER_H_INCLUDED

#include <signal.h>
#include <photon/PtT.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Pt_connection_server PtConnectionServer_t;
typedef struct Pt_connector PtConnector_t;

typedef void PtConnectorCallbackFunc_t(
	PtConnector_t *connector,
	PtConnectionServer_t *connection,
	void *user_data
	);

typedef void const *PtConnectionMsgFunc_t(
	PtConnectionServer_t *connection, void *user_data,
	unsigned long type, void const *msg, unsigned len,
	unsigned *reply_len
	);

enum PtConnectionServerError {
	Pt_CONNECTION_REPLY_FAILED,
	Pt_CONNECTION_REALLOC_RECEIVE,
	Pt_CONNECTION_SERVER_BROKEN,
	Pt_CONNECTION_MSGREAD_FAILED,
	};

typedef int PtConnectionServerErrorFunc_t(
	PtConnectionServer_t *connection, int err, enum PtConnectionServerError where
	);

typedef struct Pt_connection_msg_handler {
	unsigned long type;
	PtConnectionMsgFunc_t *fun;
	}
		PtConnectionMsgHandler_t;

/* Flags for PtConnectionNotify */
#define Pt_CONNECTION_NOTIFY_RESIZE  1	/* Resize buffer if necessary */
#define Pt_CONNECTION_NOTIFY_NOFLUSH 2	/* Don't flush if buffer too small */
#define Pt_CONNECTION_NOTIFY_FLUSH   4	/* Force a flush */

PtConnector_t *PtConnectorCreate( const char *name, PtConnectorCallbackFunc_t *cb, void *data );
PhConnectorId_t PtConnectorGetId( PtConnector_t const *connector );
int PtConnectorDestroy( PtConnector_t *ctor );

void PtConnectionServerDestroy( PtConnectionServer_t *connection );

int PtConnectionFlush( PtConnectionServer_t *connection );

int PtConnectionNotify(
        PtConnectionServer_t *connection, unsigned long type,
        void const *message, unsigned length, unsigned flags
        );

int PtConnectionAddMsgHandlers(
	PtConnectionServer_t *connection,
	PtConnectionMsgHandler_t const handlers[], unsigned nhandlers
	);

int PtConnectionResizeEventBuffer(
	PtConnectionServer_t *connection, unsigned length
	);

PtConnectionServerErrorFunc_t *PtConnectionServerSetError(
	PtConnectionServer_t *connection,
	PtConnectionServerErrorFunc_t *func
	);

void PtConnectionServerSetUserData(
	PtConnectionServer_t *connection, void *data
	);

void *PtConnectionServerGetUserData(
	PtConnectionServer_t *connection
	);

int PtConnectionReply(
	PtConnectionServer_t *connection, int len, void const *buf
	);

int PtConnectionReplymx(
	PtConnectionServer_t *connection, int n, iov_t *iov
	);

int PtConnectionGetClientRcvid( PtConnectionServer_t *connection );

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>
#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtConnectionServer.h $ $Rev: 219996 $" )
#endif
