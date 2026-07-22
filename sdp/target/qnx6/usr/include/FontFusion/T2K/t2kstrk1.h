/*
 * T2Kstrk1.h
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

#ifndef __T2K_STRK1__
#define __T2K_STRK1__
#ifdef __cplusplus
extern "C" {            
#endif  


GlyphClass *ff_glyph_StrokeGlyph( GlyphClass *glyph1, int radius, int joinType, int capType, int open );


GlyphClass *ff_New_GlyphClassT2KS(sfntClass *font, GlyphClass *glyph, int32 index,
								  uint16 *aWidth, uint16 *aHeight, void *model, int depth );

void ff_Read2Numbers( InputStream *in, uint16 arr[] );
void ff_Read4Numbers( InputStream *in, uint16 arr[] );

#ifdef ENABLE_WRITE
	
int  Write2Numbers( uint16 arrIn[], OutputStream *out );
int  Write4Numbers( uint16 arrIn[], OutputStream *out );
void WriteLowUnsignedNumber( OutputStream *out, uint32 n );
#endif

#ifdef ENABLE_T2KS
ffstClass *FF_New_ffstClass( tsiMemObject *mem, InputStream *in, uint32 length );
void FF_Delete_ffstClass( ffstClass *t );
#endif

#ifdef ENABLE_WRITE

void FF_Write_ffstClass( OutputStream *out, int gIndexFirstRoman, int gIndexLastRoman );
#endif 



ffhmClass *FF_New_ffhmClass( tsiMemObject *mem, InputStream *in );


uint16 FF_GetAW_ffhmClass( void *param1, register uint16 index );


void FF_Delete_ffhmClass( ffhmClass *t );

#ifdef ENABLE_WRITE

void FF_Write_ffhmClass( OutputStream *out, int32 numGlyphs, uint16 *aw, uint16 defaultWidth );
#endif 


#ifdef __cplusplus
}
#endif  

#endif 




