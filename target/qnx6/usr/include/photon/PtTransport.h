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
#ifndef __PT_TRANSPORT_INCLUDED
#define __PT_TRANSPORT_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <photon/PtConnectionServer.h>
#include <photon/PtConnectionClient.h>
#include <photon/PhTransport.h>
typedef struct pt_dnd_callback_info PtDndCallbackInfo_t;

#define Pt_DND_REQUEST				1
#define Pt_DND_REQUEST_DATA 		1
#define Pt_DND_REQUEST_SERVICE 		2
#define Pt_DND_CANCEL_DATA_REQUEST 	3
#define Pt_DND_ACK 					4
#define Pt_DND_CHANGE_TRANSPORT		5

enum {
	Pt_DND_CMD_PROVIDE_DATA = 0,
	Pt_DND_CMD_DELETE,
	Pt_DND_CMD_COPY,
	Pt_DND_CMD_QUREY_PROPERTIES,
	};

typedef struct req_resp_msg_hdr PtReqResponseHdr_t;
typedef struct ptrequestables PtRequestables_t;
typedef int unsigned PtTransportReqDataCB_t( int unsigned type, PtReqResponseHdr_t *req_hdr, PtRequestables_t  *requestables );
/* return 0 == source cancels destination request */
/* non-0 data has been or will be provided. */

typedef struct ptdatatransctrl PtTransportCtrl_t;
typedef struct PtDndDestCtrl {
	PtConnectionClient_t *connection;
	} PtDndDestCtrl_t;



/* PtReqRespMsgHdr_t
 *
 * Determines how a data request will be responded to.
 */
struct req_resp_msg_hdr {
	int unsigned	transport; /* includes endian OK. */
	int unsigned	cmd;
	int unsigned 	chunk_size;
			/* used per block if streaming, as max */
			/* receive size otherwise. if data too big */
			/* fail the request. */
	int				total_size;
	int unsigned	byte_offset;
	void *			source_handle;
	void *			dest_handle;
	int unsigned	data_size; /* data which follows. (if responding w/packed data, size is packed data size, not unpacked size) */
	};
	/* msg specific data follows. */
	/* usually a string when requesting */
	/* usually the requested data when replying. */


struct ptrequestables {
	PtTransportCtrl_t	*ctrl;
	PhTransportRegEntry_t *trans_entry;
	int	unsigned	flags;
	int	unsigned	size; 
	void			*response_data; /*	pointer to data added in response chain. (set when found). */
	PhTransportLink_t	*link;
	int	unsigned	response_transport;
	void			*rq_callback_data;
	PtTransportReqDataCB_t	*rq_callback;
	PtRequestables_t	*next;
	};

/* Used on senders side... */

typedef struct pt_requested_link PtRequestedLink_t;
struct pt_requested_link {
	PtRequestables_t	*data;
	PtReqResponseHdr_t	rr_hdr;
	PtRequestedLink_t	*next;
	 };

typedef struct pt_transport_hdr {
	int 	connector_id;
	int 	photon_channel_id;
	int unsigned	flags;
	int	unsigned	 buf_size; /* size of following buffer. */
	} PtTransportHdr_t;

/* Used on sender's side */
struct ptdatatransctrl {
	PtTransportHdr_t	hdr;
	PhTransportCtrl_t	*ctrl;
	PtWidget_t		*widget;
	PtRequestables_t	*requestables;
	PtRequestedLink_t	*requested;
	PhTransportLink_t	*response;
	PhTransportLink_t	*last_response;
	PtConnector_t		*connector;
	PtConnectionServer_t *connection;
	int				(*complete)( PtTransportCtrl_t *tctrl, short unsigned event_subtype );
	void				*data;
	};

typedef struct pt_dnd_fpending PtDndFetchPending_t;

typedef int PtRequestFunc_t( PhTransportHdr_t *hdr, PtDndFetchPending_t *fetch_pending );

typedef struct ptdndfetch PtDndFetch_t;
typedef int unsigned PtSelectFunc_t( PhTransportHdr_t *hdr, PtDndFetch_t *fetch_entry, int unsigned index );
/* Used by receiver to specify types of data to accept */
struct ptdndfetch {
	char 			*type_name;
	char 			*description;
	int unsigned	transport;	/* used to indicate the acceptable transport methods to get the data if. */
	int unsigned 	select_flags;
	void			*user_data;
	PtSelectFunc_t	*select_cb;
	PtRequestFunc_t	*request_cb;
	TransportMalloc_t *transport_malloc;
	void			*transport_malloc_cb_data;
	};
/* Fetch select flag bits */
#define Pt_DND_SELECT_DATA_DUP	0x00000001
#define Pt_DND_SELECT_DUP_DATA	0x00000001
#define Pt_DND_SELECT_MOTION	0x00000002
#define Pt_DND_SELECT_MULTIPLE	0x00000004

/* Added to receiver widget data in preperation for drop */
/* typedef struct pt_dnd_fpending PtDndFetchPending_t; */
struct pt_dnd_fpending {
	PtWidget_t			*widget;
	int	unsigned		transport;
	int unsigned		fetch_index;
	PtDndFetch_t		*fetch_element;
	PhTransportHdr_t	hdr;
	int unsigned		byte_offset;
	int unsigned		max_chunk_size;
	char				*buffer;
	int unsigned		buffer_len;
	int unsigned		handle;
	int					asked; /* one when awaiting response, zero when source should be asked for more data. */
	int 				*cmds;
	int unsigned		ncmds;
	char				*req_spec_data; /* ie filenames or whatever */
	int unsigned		*req_spec_data_size;
	};

/*** P R O T O T Y P E S ***/	

	extern PtRequestables_t *
PtTransportRequestableType( 
	PtTransportCtrl_t	*ctrl, 
	char const * const	type,
	char const * const	desc, 
	int unsigned const	data_flags,
	int unsigned		request_transport,
	int unsigned		inlined_transport,
	char				*packing_type,
	void *				vdata,
	int unsigned		len,
	PtTransportReqDataCB_t *rq_callback, 
	void *				rq_callback_data,
	int unsigned const	flags
	);
	
	extern int
PtTransportType( 
	PtTransportCtrl_t *ctrl, 
	char const * const	type,
	char const * const	desc, 
	int unsigned const	data_flags,
	int unsigned		transport,
	char				*packing_type,
	void *				vdata,
	int	unsigned		len,
	int unsigned const	flags
	);

	extern PtRequestables_t *
PtTransportRequestable(
	PtTransportCtrl_t 	*ctrl,
	char const * const	type,
	char const * const	desc,
	int unsigned const	flags,
	int unsigned 		transport,
	char				*packing_type,
	PtTransportReqDataCB_t *rq_callback, 
	void *				rq_callback_data
	);

	PhTransportLink_t *
PtAddResponseType(
	PtTransportCtrl_t	*ctrl, 
	PtRequestables_t	*requestable,
	char				*type,
	char				*desc,
	int unsigned		transport,
	char *				packing_type,
	void *				vdata,
	int unsigned		vdata_size,
	int unsigned const	flags
	);

	extern char *
PtAllocPackType( 
	char unsigned	*type, 
	char unsigned	*desc, 
	int unsigned	flags,
	int unsigned	handle,
	int unsigned	transport,
	char			*packing_type, 
	char unsigned	*data, 
	int unsigned	len,
	int *size
	);

	extern int
PtDndSelect( PtWidget_t *widget, PtDndFetch_t *data_array, int unsigned data_array_size, PhCursorDescription_t *accept_cursor, PhCursorDescription_t *reject_cursor, PtCallbackInfo_t *cbinfo );

	extern void
PtReleaseTransportCtrl( PtTransportCtrl_t *ctrl );

extern int
PtHandleDnDrop( PtWidget_t *widget, PhEvent_t *event, PtDndCallbackInfo_t *dndcbinfo );

	extern void *
PtUnpack( PtWidget_t *widget, PhEvent_t *event );

	extern iov_t *
PtGetTransportVectors( PtTransportCtrl_t *ctrl, int num_hdr_vectors, int unsigned *niovs, int unsigned *size );

	extern int
PtGetDndFetchIndex( const PtDndCallbackInfo_t *, const PtDndFetch_t *, unsigned );

	extern int
PtInitDnd( PtTransportCtrl_t *ctrl, PtWidget_t *widget, PhEvent_t *event, PhDndCursors_t *cursors, int unsigned flags );
/** PtInitDnd F L A G S! **/
	/* reflect no Dnd events to source. */
#define Pt_DND_SILENT	0x00000001
	/* only allow drop/paste within the same application */
#define Pt_DND_LOCAL	0x80000000

	extern PtTransportCtrl_t *
PtCreateTransportCtrl();

	extern void
PtDndDeselect( PtWidget_t *widget );

#ifdef __cplusplus
	}
#endif
#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtTransport.h $ $Rev: 224590 $" )
#endif
