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
#ifndef __PH_TRANSPORT_INCLUDED
#define __PH_TRANSPORT_INCLUDED
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif


#define TRANSPORT_PACKING	0
#define TRANSPORT_UNPACKING	1

/* Transport values for use in the PhTransportInline* funcs */
	/* Endian of source == endian of dest */
		#define Ph_TRANSPORT_ENDIAN_OK	0x80000000

	/* Endian of source != endian of dest */
		#define Ph_TRANSPORT_ENDIAN_REV	0x00000080

	/* Data is not inlined, it must be requested.... == No inlined data available at drop time. */

	/* User callback called immediately, data is pointer to extracted drop data.
	   meaningless. */
		#define Ph_TRANSPORT_INLINE		0x00000004

	/* User callback called	when file indicated in data exists ( it is *NOT* automatically opend ) */
		#define Ph_TRANSPORT_FILEREF	0x00000001

	/* User callback called after mem area is ready (opened and mmapped) data is a pointer to an allocated shmemref { char *name, void *addr }
	   data, if provided, should be a shared mem name. */
		#define Ph_TRANSPORT_SHMEM		0x00000002

	/* User callback called after receiving each piece of streamed data */
		#define Ph_TRANSPORT_STREAM		0x00000010

	/* User callback called after entire stream received, entire size must be known at start */
		#define Ph_TRANSPORT_INLINED_STREAM 0x00000020

	/* User callback called with each piece of data ( stream has struct. ie PtNamedStream_t == { char *name, int offset, bytes, data } */
		#define Ph_TRANSPORT_NAMED_STREAM 0x00000040

	/* User callback called with each piece of data ( stream has structure ie PtFileInfo_t and PtNamedStream_t ) */
		#define Ph_TRANSPORT_FILE_STREAM	0x00000100

	#define Ph_TRANSPORT_NOT_INLINED	( Ph_TRANSPORT_FILE_STREAM | Ph_TRANSPORT_NAMED_STREAM | Ph_TRANSPORT_INLINED_STREAM | Ph_TRANSPORT_STREAM )

	/* indicates data is a part of a larger pack definition ( things like desc, major, handle, etc are omitted from the passed info) */
		#define Ph_TRANSPORT_SUBPART		0x08000000

	/* This is a response... */
		#define Ph_TRANSPORT_RESPONSE	0x10000000

	/* There is more data pending, please re-ask... usually for streaming. */
		#define Ph_TRANSPORT_PENDING	0x20000000

	/* Don't expect to get the data you asked for. */
		#define Ph_TRANSPORT_CANCEL		0x40000000
		
	#define Ph_TRANSPORT_MASK		0x0FFFFF7F


/* flags for PhInlineByType */
#define Ph_DONT_COPY	0x00000010

typedef int unsigned PhTransportReqDataCB_t( int unsigned type, void *req_hdr, void *requestables );
#if 0
typedef struct reqdatastruct PhTransportReqData_t;
struct reqdatastruct {
	PhTransportReqDataCB_t *	req_callback;
	void *			callback_data;
	}; /* ?? */
#endif

typedef struct ph_trans_hdr PhTransportHdr_t;
typedef struct __phlink PhTransportLink_t;
struct __phlink {
	void *			data;
	int unsigned	size;
	int				niovs;
	iov_t			*iovs;
	PhTransportLink_t *		next;
	};

typedef struct phdattransp {
	PhTransportLink_t *		first_inline;
	PhTransportLink_t *		last_inline;
	int unsigned 			n_inline;
	int unsigned			rqdata_cnt;
	} PhTransportCtrl_t ;

typedef struct phtransportfixupdrec {
	int member_spec;
	int unsigned size;	/* if size < 0, use fixup def. */
	int 	count;	/* if array, # of elements */
	short unsigned index;	/* index of fixup in BlobDef_t's fixup array */
	} PhTransportFixupDRec_t;

typedef struct phtransportfixuprec {
	int unsigned	member_spec;
	int unsigned	oper1;
	int unsigned	oper2;
	char 			cop;
	char 			spare[3];
	} PhTransportFixupRec_t;

typedef struct phtransportendian_rec {
	int type; /* size of elements to flip 2 or 4 bytes | ?OUTSTRUCT? | offset of member */
	} PhTransportEndianRec_t;

typedef struct ph_transport_reg_entry {
	char					*type;
	int unsigned			packing;	/* uchar */
	int unsigned 			size;		/* ushort */
	int unsigned			num_fixups; /* uchar */
	PhTransportFixupRec_t const		*fixups;
	int unsigned  const		*endians;
	int unsigned  const		*clear_refs;
	} PhTransportRegEntry_t;

/* PhTransportRegEntry_t.packing */
#define Ph_PACK_STRUCT	0
#define	Ph_PACK_STRING	1
#define	Ph_PACK_RAW		2

/* Operator modifiers */
#define TRANSPORT_FETCH 				0x80000000
#define TRANSPORT_SIZE_MASK 			0x0FFF0000
#define TRANSPORT_SIZE_SHIFT 			16

/* member specification */
#define TRANSPORT_REF_TYPE				0x80000000
#define TRANSPORT_STRLEN 				0x40000000
#define TRANSPORT_CALLBACK 				0x20000000
#define TRANSPORT_ALLOC					0x10000000
#define TRANSPORT_TYPE_ARRAY			0x08000000
#define TRANSPORT_REF_TYPE_ARRAY		0x04000000
#define TRANSPORT_REF_TYPE_REF_ARRAY	0x02000000
#define TRANSPORT_OP_MASK 				0xFF800000

#define TRANSPORT_OFFSET_MASK			0x0000FFFF


typedef struct transporttypelist TransTypeList_t;
struct transporttypelist {
	TransTypeList_t *next;
	PhTransportRegEntry_t *type_def;
	};

struct ph_trans_hdr {
	unsigned int			transport;
	unsigned int			request_transport;
	char					*packing_type;
	char					*type_name;
	char					*description;
	PhTransportRegEntry_t *trans_entry;
	char					*buffer;
	char					*data;
	int unsigned			handle;
	int unsigned			size;
	PhTransportHdr_t		*next;
	int unsigned		base_size;
	int unsigned			flags;
	};

#define Ph_TRANSPORT_DUP_DATA	0x01

typedef struct ph_trans_file_t {
	int num_files;
	char *abs_path;
	char **files;
	}
PhTransFiles_t;

typedef struct ph_file_info {
		int perms;
	}
PhFileInfo_t;

/*
 * PhFilesCtrl_t... used to control FileStream transfers...
 */
	typedef struct
ph_files_ctrl {
	int 			index; 	/* -1 == no files transfered yet */
	int unsigned	offset;
	int				fd;
	PhTransFiles_t	*files;
	PhFileInfo_t	*finfo;
	int unsigned nbytes;
	char *buffer;
	}
PhFilesCtrl_t;

/* accepted commands during FileStream/Files/FileRef transports. */
#define Tr_UNLINK_SOURCE	0x80000000
	



#define Tr_FETCH( _struct_type, b ) ( offsetof( _struct_type, b )|(sizeof(((_struct_type *)0)->b) << TRANSPORT_SIZE_SHIFT)|TRANSPORT_FETCH )
#define ARRAY_SIZE( m_array ) ( sizeof( m_array ) / sizeof( m_array[0] ) )

typedef unsigned int FixupCallback_t( char **dest, PhTransportRegEntry_t *blobdef, PhTransportFixupRec_t *fixup, int unpacking );

#define Tr_STRING( _struct_type, _member ) { offsetof( _struct_type, _member ) | TRANSPORT_STRLEN, 0, 0, '\0' }
#define Tr_STRING_ARRAY( _struct_type, _member ) Tr_TYPE_ARRAY( _struct_type, _member, "string" )
#define Tr_STRING_REF_ARRAY( _struct_type, _member, _num_els ) Tr_REF_TYPE_REF_ARRAY( _struct_type, _member, num_els, "string" )


#define Tr_ALLOC( _struct_type, _member, oper1, op, oper2 ) { offsetof( _struct_type, _member) | TRANSPORT_ALLOC, oper1, oper2, op }
#define Tr_CALLBACK( _struct_type, _member, callback ) { offsetof( _struct_type, _member ) | TRANSPORT_CALLBACK, (FixupCallback_t *)callback, 0, '\0' }

#define Tr_ARRAYSIZE( _struct_type, _member ) ( sizeof( (((_struct_type *)0)->_member) )/sizeof( ((_struct_type *)0)->_member[0] ) )

#define Tr_TYPE( _struct_type, _member, name ) Tr_TYPE_ARRAY( _struct_type, _member, name )
#define Tr_TYPE_ARRAY( _struct_type, _member, _type_name ) { offsetof( _struct_type, _member) | TRANSPORT_TYPE_ARRAY, (int unsigned)(void *)_type_name, Tr_ARRAYSIZE( _struct_type, _member ), '\0' }

#define Tr_REF_TYPE( _struct_type, _member, _type_name ) Tr_REF_TYPE_ARRAY( _struct_type, _member, 1, (int)(void *)_type_name )
#define Tr_REF_TYPE_ARRAY( _struct_type, _member, _num_els, _type_name ) { offsetof( _struct_type, _member) | TRANSPORT_REF_TYPE_ARRAY, (int unsigned)(void *)_type_name, _num_els, '*' }

#define Tr_REF_ARRAY( _struct_type, _member, _num_els ) Tr_ALLOC( _struct_type, _member, _num_els, '*', sizeof( *(((_struct_type *)0)->_member) ) ) 

#define Tr_REF_TYPE_REF_ARRAY( _struct_type, _member, _num_els, _type_name ) { offsetof( _struct_type, _member) | TRANSPORT_REF_TYPE_REF_ARRAY, (int unsigned)(void *)_type_name, _num_els, '\0' }

#define Tr_ENDIAN_NUM_SHIFT		20
#define Tr_ENDIAN_NUM_MASK		0xFF
#define Tr_ENDIAN_ELSIZE_SHIFT	12
#define Tr_ENDIAN_ELSIZE_MASK	0xFF
#define Tr_ENDIAN_OFFSET_MASK	0xFFF
#define Tr_OUTSTRUCT			0x80000000
#define Tr_REGSTRUCT			0x40000000


/** Endians only need be corrected for standard C type instances **/
/** References to Transport Registry types will be endian   **/
/** Corrected when they are unpacked				   **/

#define Tr_ENDIAN( _struct_type, _member ) ( \
	offsetof( _struct_type, _member ) | ( sizeof( (((_struct_type *)0)->_member) ) << Tr_ENDIAN_ELSIZE_SHIFT ) | ( 1 << Tr_ENDIAN_NUM_SHIFT ) \
	)
#define Tr_ENDIAN_ARRAY( _struct_type, _member ) ( \
	offsetof( _struct_type, _member ) | ( sizeof( (((_struct_type *)0)->_member) ) << Tr_ENDIAN_ELSIZE_SHIFT ) | ( Tr_ARRAYSIZE( _struct_type, _member )<< Tr_ENDIAN_NUM_SHIFT ) \
	)
#define Tr_ENDIAN_REF( _struct_type, _member ) (\
	offsetof( _struct_type, _member ) | ( sizeof( *(((_struct_type *)0)->_member) ) << Tr_ENDIAN_ELSIZE_SHIFT ) | Tr_OUTSTRUCT \
	)
#define Tr_ENDIAN_TYPE( _struct_type, _member, structtag )  offsetof( _struct_type, _member ) | Tr_REGSTRUCT, (int unsigned)(void *)(structtag)


typedef struct ph_trans_loc {
	char *type_name;
	char *description;
	int unsigned grouping_num;
	int unsigned handle;
	} PhTransLoc_t;


typedef struct ph_named_stream {
	char *name;
	int offset;
	int nbytes;
	char *data;
	} PhNamedStream_t;

typedef void *TransportMalloc_t( PhTransportRegEntry_t *trans_entry, void *cbdata, int fixup_index, size_t size );

/**************  P R O T O T Y P E S ************ protos */

	 extern PhTransportLink_t *
PhLinkTransportData( 
	PhTransportLink_t **   		first_link,
	PhTransportLink_t **   		last_link,
	char const * const	data,
	int unsigned const	size,
	iov_t *				iovs,
	int unsigned const	niovs
	);

	extern	int 
PhFreeTransportType( 
	void *data, 
	char *type_name 
	);
	extern int 
PhRegisterTransportType( 
	PhTransportRegEntry_t *ref 
	);
	extern PhTransportLink_t *
PhTransportFindLink(
	PhTransportLink_t *link_list, 	
	void *data );
	extern PhTransportRegEntry_t *
PhFindTransportType( 
	char *type
	);
	extern PhTransportLink_t *
PhTransportType( 
	PhTransportCtrl_t *ctrl, 
	char const * const	type,
	char const * const	desc, 
	int unsigned const	grouping_num, 
	int unsigned const	handle,
	int unsigned 		inlined_transport,
	char				*packing_type,
	void *				vdata,
	int	unsigned		len,
	int unsigned const	flags
	);
	extern PhTransportLink_t *
PhTransportRequestableType(
	PhTransportCtrl_t *	ctrl, 
	char const * const	type,
	char const * const	desc, 
	int unsigned const	grouping_num, 
	int unsigned const	handle,
	int unsigned		request_transport,
	int unsigned 		inlined_transport,
	char				*packing_type,
	void *				vdata,
	int	unsigned		len,
	int unsigned const	flags
	);
	extern char *
PhMallocUnpack( 
	PhTransportHdr_t *hdr, 
	void **ret_struct, 
	TransportMalloc_t *ymalloc, 
	void *ymalloc_cb_data 
	);
	extern char *
PhUnpack( 
	PhTransportHdr_t *hdr, 
	void **ret_struct 
	);
	extern char *
PhPackEntry( 
	char				*buffer,
	PhTransportRegEntry_t *			bdptr,
	char const * const	type,
	char const * const	desc,
	int unsigned const	grouping_num,
	int unsigned const	handle,
	int unsigned const	request_transport,
	int unsigned const	inlined_transport,
	char const * const	data,
	int unsigned const	size,
	int unsigned *		tot_size,
	iov_t *				iovs,
	int unsigned *		niovs,
	int unsigned *		iovsize
	);
	extern char *
PhPackType( 
	char *buffer,
	char const * const	type,
	char const * const	desc,
	int unsigned const	grouping_num,
	int unsigned const	handle,
	int unsigned 		request_transport,
	int unsigned 		inlined_transport,
	char const * const	packing_type,
	void const * const	data,
	int unsigned const	size,
	int unsigned *		tot_size,
	iov_t *				iovs,
	int unsigned *		niovs,
	int unsigned *		iovsize
	);
	extern void *
PhGetNextInlineData( 
	PhTransportCtrl_t *ctrl, 
	PhTransportLink_t *current, 
	PhTransportLink_t **new_link 
	);
	extern PhTransportHdr_t *
PhGetTransportHdr( 
	PhTransportHdr_t *hdr, 
	char *buffer 
	);
	extern PhTransportHdr_t *
PhGetNextTransportHdr( 
	PhTransportHdr_t *last_hdr, 
	PhTransportHdr_t *trans_hdr 
	);
	extern void
PhReleaseTransportHdrs( 
	PhTransportHdr_t *hdrs 
	);
	extern PhTransportHdr_t *
PhUnlinkTransportHdr( 
	PhTransportHdr_t *hdr_list, 
	PhTransportHdr_t *victim 
	);
	extern int
PhLocateTransHdr( 
	PhTransportHdr_t **hdr_list, 
	PhTransLoc_t *desired_data, 
	PhTransportHdr_t *found 
	);
	extern PhTransportHdr_t *
PhGetAllTransportHdrs( 
	char *buffer, 
	int unsigned buffer_size
	);
	extern PhTransportCtrl_t *
PhCreateTransportCtrl(
	);
	extern void
PhReleaseTransportCtrl( 
	PhTransportCtrl_t *ctrl 
	);
	extern iov_t *
PhGetTransportVectors( 
	PhTransportCtrl_t *trans_ctrl, 
	int num_hdr_vectors, 
	int unsigned *num_vectors, 
	int unsigned *size
	);

#ifdef __cplusplus
};
#endif

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PhTransport.h $ $Rev: 224590 $" )
#endif
