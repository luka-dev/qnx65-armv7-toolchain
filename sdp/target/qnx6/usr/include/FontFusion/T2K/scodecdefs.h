/*
 * scodecdefs.h
 * Font Fusion Copyright (c) 1989-2005 all rights reserved by Bitstream Inc.
 * http://www.bitstream.com/
 * http://www.typesolutions.com/
 * Author: Anup Belambe/Tohin
 *
 * This software is the property of Bitstream Inc. and it is furnished
 * under a license and may be used and copied only in accordance with the
 * terms of such license and with the inclusion of the above copyright notice.
 * This software or any other copies thereof may not be provided or otherwise
 * made available to any other person or entity except as allowed under license.
 * No title to and no ownership of the software or intellectual property
 * contained herein is hereby transferred. This information in this software
 * is subject to change without notice
 */

#ifndef SCODEC_H_
#define	SCODEC_H_


#ifndef FF_FFCONFIG_HEADER
#include "config.h"
#else
#include FF_FFCONFIG_HEADER
#endif 

#define C_MAX_LENGTH_MASK	0x8000

typedef	void	*DECODER;

typedef struct tag_CBLOCK
{
	uint32		*offset;		
	uint16		*clength;	
} CBLOCK, *PCBLOCK, **PPCBLOCK;

typedef struct tag_CSTREAMHEADER
{
	uint32 last_block_length;	
	uint32 enc_data_length;	
	uint32 data_length;	
	uint16 blockSize; 
	uint16 nblocks;	
	uint8 majorVer; 
	uint8 minorVer;
} CSTREAMHEADER, *PCSTREAMHEADER, **PPCSTREAMHEADER;

typedef struct tag_CBLOCKTABLE
{
	CSTREAMHEADER	header;	
	CBLOCK	 blocks;
} CBLOCKTABLE, *PCBLOCKTABLE, **PPCBLOCKTABLE;


typedef struct tag_CBLOCKCACHE
{
	tsiMemObject	*mem;
	PCBLOCKTABLE	table;
	uint8			*enc_stream;			
	
	uint8			*d_data;
	
	uint32			d_start_pos; 			
	uint32			d_end_pos_plus_1; 		
	uint32			d_current_pos; 			
	
	DECODER			decoder;
	int32			decodedLenPresent;
	uint32			lastControl;
	uint32			lastControlBit;
	int16			saved_block_id;
	int16			p_src_index;
	int16			byteShortage;	
} CBLOCKCACHE, *PCBLOCKCACHE, **PPCBLOCKCACHE;

#define _isencoded(l)			((l) &  C_MAX_LENGTH_MASK)
#define _setencoded(l)			((l) |= (clength) C_MAX_LENGTH_MASK)
#define _resetencoded(l)		((l) &= (~C_MAX_LENGTH_MASK))
#define _offset(x,i)			((PCBLOCKCACHE) (x))->table->blocks.offset[(i)]

#define _table(x) 				((PCBLOCKCACHE) (x))->table
#define _header(x) 				((PCBLOCKCACHE) (x))->table->header
#define _nblocks(x) 			((PCBLOCKCACHE) (x))->table->header.nblocks
#define _version(x)				((PCBLOCKCACHE) (x))->table->header.version
#define _last_block_length(x)	((PCBLOCKCACHE) (x))->table->header.last_block_length
#define  _data_length(x)		((PCBLOCKCACHE) (x))->table->header.data_length
#define _enc_data_length(x)		((PCBLOCKCACHE) (x))->table->header.enc_data_length
#define _enc_stream(x)			((PCBLOCKCACHE) (x))->enc_stream
#define _start_pos(x)			((PCBLOCKCACHE) (x))->d_start_pos
#define _end_pos(x)				((PCBLOCKCACHE) (x))->d_end_pos_plus_1
#define _d_current_pos(x)		((PCBLOCKCACHE) (x))->d_current_pos
#define _decoder(x)				((PCBLOCKCACHE) (x))->decoder
#define _blocks(x)				((PCBLOCKCACHE) (x))->table->blocks
#define _e_length(x,i)			((PCBLOCKCACHE) (x))->table->blocks.clength[(i)]
#define _d_data_3(x)			((PCBLOCKCACHE) (x))->d_data
#define _d_data(x)				(uint8*)(((PCBLOCKCACHE) (x))->d_data + 3)
#define _mem(x)					((PCBLOCKCACHE) (x))->mem
#define _saved_block(x)			((PCBLOCKCACHE) (x))->saved_block_id
#define _start_pos_abs(x)		(((PCBLOCKCACHE)(x))->saved_block_id * ((PCBLOCKCACHE)(x))->table->header.blockSize)
#define _d_current_ptr(x)		(uint8*)((((PCBLOCKCACHE) (x))->d_data + 3) + ((PCBLOCKCACHE) (x))->d_current_pos)



#define _exhausted(x)			((PCBLOCKCACHE)  (x))->d_current_pos >= ((PCBLOCKCACHE) (x))->d_end_pos_plus_1
#define _bytes_available(x)		(((PCBLOCKCACHE) (x))->d_end_pos_plus_1 - ((PCBLOCKCACHE) (x))->d_current_pos)
#define _end_of_file(x)			(((PCBLOCKCACHE)  (x))->d_current_pos >= ((PCBLOCKCACHE) (x))->table->header.data_length)

#define _getdecLen(x)					((PCBLOCKCACHE)  (x))->decodedLenPresent
#define _setFlagOn(x)					(((PCBLOCKCACHE)  (x))->byteShortage = 1)
#define _setFlagOff(x)					(((PCBLOCKCACHE)  (x))->byteShortage = 0)
#define _checkFlag(x)					(((PCBLOCKCACHE)  (x))->byteShortage)
#define _setCurrentPos(x, currPos)		(((PCBLOCKCACHE) (x))->d_current_pos = currPos)
#define _maxBlkSize(x)					((PCBLOCKCACHE)(x))->table->header.blockSize


#endif	



