/*
 * T2kstrm.h
 * Font Fusion Copyright (c) 1989-1999 all rights reserved by Bitstream Inc.
 * http://www.bitstream.com/
 * http://www.typesolutions.com/
 * Author: Sampo Kaasila
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

#ifndef __T2K_STREAM__
#define __T2K_STREAM__
#ifdef __cplusplus
extern "C" {            
#endif  



#ifdef COMPRESSED_INPUT_STREAM

#ifndef FF_FFCONFIG_HEADER
#include "config.h"
#else
#include FF_FFCONFIG_HEADER
#endif 

#include FF_SCODECDEFS_HEADER

#endif 



#ifdef ENABLE_NON_RAM_STREAM
typedef int (*PF_READ_TO_RAM) ( void *id, uint8 *dest_ram, uint32 offset, int32 numBytes );
#endif

#ifdef JUST_AN_EXAMPLE_OF_PF_READ_TO_RAM
int ReadFileDataFunc( void *id, uint8 *dest_ram, uint32 offset, int32 numBytes )
{
	int error;
	size_t count;
	FILE *fp = (FILE *)id;

	CLIENT_ASSERT( fp != NULL );
	
	error	= fseek( fp, offset, SEEK_SET );
	if ( error )
		return -1; 
	count = fread( dest_ram, sizeof( int8 ), numBytes, fp );
	return (ferror(fp) == 0 && count == (size_t)numBytes ) ? 0 : -1; 
}
#endif


#ifdef ENABLE_NON_RAM_STREAM

#define USE_PRE_CACHING
#endif 

typedef struct InputStream_t InputStream;

struct InputStream_t
{
	
	uint8 *privateBase;
#ifdef ENABLE_NON_RAM_STREAM
	PF_READ_TO_RAM 	ReadToRamFunc;
	void			*nonRamID;
	uint8			tmp_ch;
#ifdef USE_PRE_CACHING
#define PRE_CACHE_SIZE 512
	uint8 cacheBase[ PRE_CACHE_SIZE ];
	int32 bytesLeftToPreLoad;
#endif
	uint32 cacheCount;
	uint32 cachePosition; 
#endif

#ifdef COMPRESSED_INPUT_STREAM
	void*	cache;
	uint8 (*ReadUnsignedBytePtr)(InputStream *t);
#endif
	uint32 pos;
	uint32 maxPos; 
	uint32 posZero;
	int8 constructorType;
	tsiMemObject *mem;

	uint32 bitBufferIn,  bitCountIn;  
	uint8 decrypted;
	

};


#ifdef USE_PRE_CACHING
void PreLoadT2KInputStream( InputStream *t, int32 requestedByteCount );
int PrimeT2KInputStream(InputStream *t );
#define EnsureWeHaveDataInT2KInputStream( stream, n ) \
	( ( stream->pos - stream->cachePosition + (n) > stream->cacheCount ) ? \
	PrimeT2KInputStream( stream ) : 0 )
#endif 



InputStream *New_InputStream( tsiMemObject *mem, uint8 *data, uint32 length, int *errCode );
InputStream *New_InputStream2( tsiMemObject *mem, InputStream *in, uint32 offset, uint32 length, int fastIndex, int *errCode );

InputStream *New_InputStream3( tsiMemObject *mem, uint8 *data, uint32 length, int *errCode );
InputStream *New_InputStream4( tsiMemObject *mem, uint8 *data, uint32 length, int *errCode );

#ifdef ENABLE_NON_RAM_STREAM
InputStream *New_NonRamInputStream( tsiMemObject *mem, void *nonRamID, PF_READ_TO_RAM readFunc, uint32 length, int *errCode );
#endif

void Delete_InputStream( InputStream *t, int *errCode );

int32 SizeInStream( InputStream *stream );

int32 ReadInt32( InputStream *stream );
int16 ReadInt16( InputStream *stream );

#define EOF_STREAM -1


#ifdef COMPRESSED_INPUT_STREAM 
uint8 ReadUnsignedByteSlow( InputStream *stream );
uint8 ReadUnsignedByteSlow2( InputStream *stream );

#define ReadUnsignedByteMacro( stream )	(stream->ReadUnsignedBytePtr(stream))
#define ReadUnsignedByteMacro2( stream ) ( (int32)(stream->pos >= stream->maxPos ? EOF_STREAM : (ReadUnsignedByteMacro(stream)) ) )
#elif !defined(ENABLE_NON_RAM_STREAM)
#define ReadUnsignedByteMacro( stream )  ((uint8)(stream->privateBase[(stream->pos)++]))
#define ReadUnsignedByteMacro2( stream ) ((int32)(stream->pos >= stream->maxPos ? EOF_STREAM : stream->privateBase[(stream->pos)++]) )
#endif 

#ifdef  ENABLE_NON_RAM_STREAM
#if defined(USE_PRE_CACHING) & !defined(COMPRESSED_INPUT_STREAM)
#define ReadUnsignedByteMacro( stream ) \
	( (uint8) (stream->privateBase != NULL ? \
	( stream->ReadToRamFunc != NULL ? \
	EnsureWeHaveDataInT2KInputStream( stream, 1 ), stream->privateBase[(stream->pos)++ - stream->cachePosition] : \
	stream->privateBase[(stream->pos)++] ) : \
	( ( stream->ReadToRamFunc( stream->nonRamID, &(stream->tmp_ch), (stream->pos)++, 1 ) < 0 ) ? tsi_Error( stream->mem, T2K_EXT_IO_CALLBACK_ERR),0 : stream->tmp_ch))  )
#else
#ifndef COMPRESSED_INPUT_STREAM
#define ReadUnsignedByteMacro( stream ) ( (uint8) (stream->privateBase != NULL ? (stream->privateBase[(stream->pos)++]) : ( stream->ReadToRamFunc( stream->nonRamID, &(stream->tmp_ch), (stream->pos)++, 1 ) < 0 ? tsi_Error( stream->mem, T2K_EXT_IO_CALLBACK_ERR),0 : stream->tmp_ch))  )
#endif 
#endif 
#ifndef COMPRESSED_INPUT_STREAM
#define ReadUnsignedByteMacro2( stream ) ( (int32)(stream->pos >= stream->maxPos ? EOF_STREAM : (ReadUnsignedByteMacro(stream)) ) )
#endif 
#endif 


uint8 *GetEntireStreamIntoMemory( InputStream *stream  );
void ReadSegment( InputStream *stream, uint8 *dest, int32 numBytes );

void Rewind_InputStream( InputStream *t );
void Seek_InputStream( InputStream *t, uint32 offset );
uint32 Tell_InputStream( InputStream *t );


typedef struct {
	
	uint8 *base;
	uint32 maxPos;
	uint32 pos;
	uint32 maxLength;
	tsiMemObject *mem;

	uint32 bitBufferOut, bitCountOut; 
	

} OutputStream;

#define Tell_OutputStream( out ) (out->pos)

#define GET_POINTER( out ) ( out->base )
OutputStream *New_OutputStream( tsiMemObject *mem, int32 initialSize );

void WriteBitsToStream( OutputStream *out, uint32 bits, uint32 count );

void FlushOutStream( OutputStream *out );
void WriteInt32( OutputStream *stream, int32 value );
void WriteInt16( OutputStream *stream, int16 value );
void WriteUnsignedByte( OutputStream *stream, uint8 value );
void Write( OutputStream *stream, uint8 *src, int32 numBytes );
void Rewind_OutputStream( OutputStream *t );
void Delete_OutputStream( OutputStream *t );

int32 SizeOutStream( OutputStream *stream ); 
int32 OutStreamPos( OutputStream *stream );  


void WriteUnsignedNumber( OutputStream *out, uint32 n );
uint32 ReadUnsignedNumber( InputStream *in );

#ifdef __cplusplus
}
#endif 
#endif 



