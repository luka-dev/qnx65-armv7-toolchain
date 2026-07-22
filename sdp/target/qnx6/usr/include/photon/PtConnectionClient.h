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
 *	PtConnectionClient.h
 *

 */

#if !defined(__PT_CONNECTION_CLIENT_H_INCLUDED)
#define __PT_CONNECTION_CLIENT_H_INCLUDED

#include <photon/PtT.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Pt_connection_client PtConnectionClient_t;

enum PtConnectionClientError {
	Pt_CONNECTION_SEND_FAILED,
	Pt_CONNECTION_REALLOC_REPLY,
	Pt_CONNECTION_CLIENT_BROKEN
	};

typedef int PtConnectionClientErrorFunc_t(
	PtConnectionClient_t *connection, int err, enum PtConnectionClientError where
	);

typedef int PtConnectionEventFunc_t(
	PtConnectionClient_t *connection, void *user_data,
	unsigned long type, void const *msg, unsigned len
	);

typedef int PtConnectionWaitFunc_t( 
	PtConnectionClient_t *connection, void *user_data, unsigned n
	);

typedef void PtConnectionReplyFunc_t(
	PtConnectionClient_t *connection, void *user_data,
	unsigned long type, const void *smsg, void const *rmsg,
	unsigned snbytes, unsigned rnbytes
	);

typedef struct Pt_connection_event_handler {
	unsigned long type;
	PtConnectionEventFunc_t *fun;
	}
		PtConnectionEventHandler_t;

#define Pt_CONNECTIONCLIENT_THREADED 0x01

PtConnectionClient_t *PtConnectionFindId( PhConnectorId_t id, int subtype, unsigned flags );
PtConnectionClient_t *PtConnectionFindName( const char *name, int subtype, unsigned flags );
int PtConnectionNameExists( const char *name );
char *PtConnectionTmpName( char name[32] );

int PtConnectionWaitForId( PhConnectorId_t id, int subtype, unsigned flags, PtConnectionWaitFunc_t *cb, void *usrdata );
int PtConnectionWaitForName( const char *name, int subtype, unsigned flags, PtConnectionWaitFunc_t *cb, void *usrdata );

void PtConnectionClientDestroy( PtConnectionClient_t *connection );

int PtConnectionSendmx(
		PtConnectionClient_t *connection, unsigned long type,
		int sparts, iov_t *siov, int rparts, iov_t *riov
		);

int PtConnectionSend(
		PtConnectionClient_t *connection,
		unsigned long type, const void *smsg, void *rmsg,
		unsigned snbytes, unsigned rnbytes
		);

int PtConnectionSendBg( 
		PtConnectionClient_t *connection,
		unsigned long type, const void *smsg, void *rmsg,
		unsigned snbytes, unsigned rnbytes,
		PtConnectionReplyFunc_t *cb
		);

int PtConnectionAddEventHandlers(
		PtConnectionClient_t *connection,
		PtConnectionEventHandler_t const *handlers, unsigned nhandlers
		);

PtConnectionClientErrorFunc_t *PtConnectionClientSetError(
		PtConnectionClient_t *connection,
		PtConnectionClientErrorFunc_t *func
		);

void PtConnectionClientSetUserData(
		PtConnectionClient_t *connection, void *data
		);

void *PtConnectionClientGetUserData(
		PtConnectionClient_t *connection
		);

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtConnectionClient.h $ $Rev: 219996 $" )
#endif
