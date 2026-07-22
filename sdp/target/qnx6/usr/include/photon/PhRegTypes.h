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
#if !defined( __PhREGTYPES_INCLUDED )
	#define __PhREGTYPES_INCLUDED

	#if defined __cplusplus
		extern "C" {
	#endif

#undef CONST_BUG
#define CONST_BUG
/*
 *	Raw definition
 */
 	static CONST_BUG PhTransportRegEntry_t
RawTransDef = {
	"raw",
	Ph_PACK_RAW
	};

/*
 *	String definition
 */
 	static CONST_BUG PhTransportRegEntry_t
StringTransDef = {
	"string",
	Ph_PACK_STRING
	};

/*
 *	PhImage_t definition.
 */

	static CONST_BUG int unsigned
PhImageEndians[] = {
	Tr_ENDIAN( PhImage_t, type ),
	Tr_ENDIAN( PhImage_t, image_tag ),
	Tr_ENDIAN( PhImage_t, bpl ),
	Tr_ENDIAN_TYPE( PhImage_t, size, "PhDim_t" ),
	Tr_ENDIAN( PhImage_t, palette_tag ),
	Tr_ENDIAN( PhImage_t, colors ), 
	Tr_ENDIAN( PhImage_t, mask_bpl ), 
	Tr_ENDIAN_REF( PhImage_t, palette ),
	0
	};
	
	static CONST_BUG PhTransportFixupRec_t
PhImageFixups[] = {
	Tr_ALLOC( PhImage_t, ghost_bitmap, Tr_FETCH( PhImage_t, ghost_bpl ), '*', Tr_FETCH( PhImage_t, size.h ) ),
	Tr_ALLOC( PhImage_t, mask_bm, Tr_FETCH( PhImage_t, mask_bpl ), '*', Tr_FETCH( PhImage_t, size.h ) ),
	Tr_ALLOC( PhImage_t, palette, Tr_FETCH( PhImage_t, colors ), '*', sizeof( PgColor_t ) ),
	Tr_ALLOC( PhImage_t, image, Tr_FETCH( PhImage_t, bpl ), '*', Tr_FETCH( PhImage_t, size.h ) ),
	Tr_ALLOC( PhImage_t, ghost_bitmap, Tr_FETCH( PhImage_t, ghost_bpl ), '*', Tr_FETCH( PhImage_t, size.h ) ),
	};

	static CONST_BUG PhTransportRegEntry_t
PhImageTransDef = {
	"PhImage",
	Ph_PACK_STRUCT,
	sizeof( PhImage_t ),
	ARRAY_SIZE( PhImageFixups ),
	PhImageFixups,
	PhImageEndians
	};

/*
 *	PhPoint_t Definition
 */
	static CONST_BUG int unsigned
PhPointEndians[] = {
	Tr_ENDIAN( PhPoint_t, x ),
	Tr_ENDIAN( PhPoint_t, y ),
	0
	};
	static CONST_BUG PhTransportRegEntry_t
PhPointTransDef = {
	"PhPoint",
	Ph_PACK_STRUCT,
	sizeof( PhPoint_t ),
	0,
	NULL,
	PhPointEndians
	};

/*
 *	PhDim_t Definition
 */
	static CONST_BUG int unsigned
PhDimEndians[] = {
	Tr_ENDIAN( PhDim_t, w ),
	Tr_ENDIAN( PhDim_t, h ),
	0
	};
	static CONST_BUG PhTransportRegEntry_t
PhDimTransDef = {
	"PhDim",
	Ph_PACK_STRUCT,
	sizeof( PhDim_t ),
	0,
	NULL,
	PhDimEndians
	};

/*
 *	PhArea_t Definition
 */
	static CONST_BUG int unsigned
PhAreaEndians[] = {
	Tr_ENDIAN_TYPE( PhArea_t, pos, "PhPoint" ),
	Tr_ENDIAN_TYPE( PhArea_t, size, "PhDim"	),
	0
	};
	
	static CONST_BUG PhTransportRegEntry_t
PhAreaTransDef = {
	"PhArea",
	Ph_PACK_STRUCT,
	sizeof( PhArea_t ),
	0,
	NULL,
	PhAreaEndians
	};

/*
 * Named stream transport type definition
 */
	static CONST_BUG int unsigned
PhNamedStreamEndians[] = {
	Tr_ENDIAN( PhNamedStream_t, offset ),
	Tr_ENDIAN( PhNamedStream_t, nbytes ),
	0
	};
 
	static CONST_BUG PhTransportFixupRec_t
PhNamedStreamFixups[] = {
	Tr_STRING( PhNamedStream_t, name ),
	Tr_ALLOC( PhNamedStream_t, data, Tr_FETCH( PhNamedStream_t, nbytes ), ' ', 0 ),
	};

	static CONST_BUG PhTransportRegEntry_t
PhNamedStreamDef = {
	"PhNamedStream",
	Ph_PACK_STRUCT,
	sizeof( PhNamedStream_t ),
	ARRAY_SIZE( PhNamedStreamFixups ),
	PhNamedStreamFixups,
	PhNamedStreamEndians
	};

/*
 * File transport type definition
 */
	static CONST_BUG int unsigned
PhFileEndians[] = {
	Tr_ENDIAN( PhTransFiles_t, num_files ),
	0
	};

	static CONST_BUG PhTransportFixupRec_t
PhTransFileFixups[] = {
	Tr_STRING( PhTransFiles_t, abs_path ),
	Tr_REF_TYPE_REF_ARRAY( PhTransFiles_t, files, Tr_FETCH( PhTransFiles_t, num_files ), "string" ),
	};

	static CONST_BUG PhTransportRegEntry_t
PhTransFileDef = {
	"PhTransfiles",
	Ph_PACK_STRUCT,
	sizeof( PhTransFiles_t ),
	ARRAY_SIZE( PhTransFileFixups ),
	PhTransFileFixups,
	PhFileEndians
	};

/*
 *	Transport File control type definition
 */
	static CONST_BUG int unsigned
PhFCtrlEndians[] = {
	Tr_ENDIAN( PhFilesCtrl_t, index ),
	Tr_ENDIAN( PhFilesCtrl_t, offset ),
	Tr_ENDIAN( PhFilesCtrl_t, nbytes ),
	0
	};

	static CONST_BUG PhTransportFixupRec_t
PhFCtrlFixups[] = {
	Tr_REF_TYPE( PhFilesCtrl_t, files, "files" ),
	Tr_REF_TYPE( PhFilesCtrl_t, finfo, "file info"),
	Tr_ALLOC( PhFilesCtrl_t, buffer, Tr_FETCH( PhFilesCtrl_t, nbytes ), ' ', 0 ),
	};

	static CONST_BUG PhTransportRegEntry_t
PhFCtrlDef = {
	"PhFilesCtrl",
	Ph_PACK_STRUCT,
	sizeof( PhFilesCtrl_t ),
	ARRAY_SIZE( PhFCtrlFixups ),
	PhFCtrlFixups,
	PhFCtrlEndians
	};


static CONST_BUG TransTypeList_t ph_ttl[] = {
	{ NULL, &PhAreaTransDef },
	{ &ph_ttl[0], &PhDimTransDef },
	{ &ph_ttl[1], &PhPointTransDef },
	{ &ph_ttl[2], &PhImageTransDef },
	{ &ph_ttl[3], &RawTransDef },
	{ &ph_ttl[4], &StringTransDef },
	{ &ph_ttl[5], &PhTransFileDef },
	{ &ph_ttl[6], &PhNamedStreamDef },
	{ &ph_ttl[7], &PhFCtrlDef },
	};
		

#if 0
#if defined(__CYGWIN__)
	typedef char	 int8_t;
#else
	typedef signed char	 int8_t;
#endif
	typedef short        int16_t;
	typedef int 		 int32_t;
	typedef unsigned char  uint8_t;
	typedef unsigned short uint16_t;
	typedef unsigned       uint32_t;
	#if defined __GNUC__ || defined __INTEL_COMPILER || defined __METROWERKS__ 
	typedef long long          int64_t;
	typedef unsigned long long uint64_t;
	#endif

	#define ENDIAN_RET16(__x)		((((__x) >> 8) & 0xff) | \
									(((__x) & 0xff) << 8))

	#define ENDIAN_RET32(__x)		((((__x) >> 24) & 0xff) | \
									(((__x) >> 8) & 0xff00) | \
									(((__x) & 0xff00) << 8) | \
									(((__x) & 0xff) << 24))

	#define ENDIAN_SWAP16(__x)		(*(uint16_t *)(__x) = ENDIAN_RET16(*(uint16_t *)(__x)))

	#define ENDIAN_SWAP32(__x)		(*(uint32_t *)(__x) = ENDIAN_RET32(*(uint32_t *)(__x)))

	#define ENDIAN_LE16(__x)		(__x)
	#define ENDIAN_LE32(__x)		(__x)
	#define ENDIAN_BE16(__x)		ENDIAN_RET16(__x)
	#define ENDIAN_BE32(__x)		ENDIAN_RET32(__x)

	#define UNALIGNED_RET16(__p)	(((uint8_t volatile *)(__p))[0] | \
									(((uint8_t volatile *)(__p))[1] << 8))

	#define UNALIGNED_RET32(__p)	(((uint8_t volatile *)(__p))[0] | \
									(((uint8_t volatile *)(__p))[1] << 8) | \
									(((uint8_t volatile *)(__p))[2] << 16) | \
									(((uint8_t volatile *)(__p))[3] << 24))

	#define UNALIGNED_PUT16(__p,__x) (((uint8_t volatile *)(__p))[0] = (__x) & 0xff, \
									((uint8_t volatile *)(__p))[1] = ((__x) >> 8) & 0xff)

	#define UNALIGNED_PUT32(__p,__x) (((uint8_t volatile *)(__p))[0] = (__x) & 0xff, \
									((uint8_t volatile *)(__p))[1] = ((__x) >> 8) & 0xff, \
									((uint8_t volatile *)(__p))[2] = ((__x) >> 16) & 0xff, \
									((uint8_t volatile *)(__p))[3] = ((__x) >> 24) & 0xff)

#endif
	#if defined CPLUSPLUS
		}
	#endif

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PhRegTypes.h $ $Rev: 224590 $" )
#endif
