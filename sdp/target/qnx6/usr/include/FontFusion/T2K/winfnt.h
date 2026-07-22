/*
	$Header: /home/archive/FontFusion/FontFusion/core/winfnt.h,v 1.3 2009/02/06 15:54:25 sflynn Exp $

 * winfnt.h
 * Font Fusion Copyright (c) 1989-2006all rights reserved by Bitstream Inc.
 * http://www.bitstream.com/
 * http://www.typesolutions.com/
 * Author: Ritesh
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

#ifndef __WINFNT_HEADER_
#define __WINFNT_HEADER_

#ifdef __cplusplus
extern "C" {            
#endif  

#ifndef FF_FFCONFIG_HEADER
#include "config.h"
#else
#include FF_FFCONFIG_HEADER
#endif 


typedef struct
{
	tsiMemObject *mem;			 
	InputStream	*in;
	uint16 version;				
	
	uint32 copyRightOffset;		
	
								
								
								

	uint16 pointSize;		
	uint16 xRes;				
	uint16 yRes;				
	uint16 ascent;
	uint16 internalLeading;
	uint16 externalLeading;
	uint8 style;				
								
								
	uint16 weight;				
								
	
	uint8 charset;				
	uint16 width;				

	uint16 height;				

	uint8 pitchfamily;
								

	uint16 avgWidth;			
								

	uint16 maxWidth;			

	uint8 firstCharCode;
	uint8 lastCharCode;
	uint8 defCharCode;		
	uint8 breakCharCode;		
	uint16 widthBytes;			
	uint32 deviceOffset;	
	uint32 faceOffset;			
	uint32 bitsPointer;	
	uint32 bitsOffset;			
	

	
	uint32	flags;				
	uint16 bitsPerPixel;
	uint16 aSpace;
	uint16 bSpace;
	uint16 cSpace;
	uint32 colorOffset;			
	uint32 CharTableOffset;		
								   
	uint8 requestedBitDepth;	
	int32 newPpemX;
	int32 newPpemY;
}winFntClass;

							

int16 readLittleInt16(InputStream * in);
int32 readLittleInt32(InputStream * in);

winFntClass *tsi_NewWinFntClass( tsiMemObject *mem, InputStream *in );

int tsi_winFntGetSbits ( void *p, int32 aCode, uint8 greyScaleLevel, uint16 cmd
#ifdef ENABLE_SBITS_TRANSFORM
				  , int8 xFracPenDelta, int8 yFracPenDelta
#endif 
				  );

uint8 *GetWinFntNameProperty( winFntClass *winFntPtr, uint16 languageID, uint16 nameID );

uint16 tsi_WinFntGetGlyphIndex ( winFntClass *winFntPtr, uint32 charCode );

void WinFnt_GetFontWideMetrics( void *t, T2K_FontWideMetrics *hori, T2K_FontWideMetrics *vert );

void Delete_winFntClass( winFntClass *winFntPtr );

uint16 FF_GetAW_WinFntClass ( void *param1, register uint16 index );

void tsi_WinFntGetGlyphByIndex ( winFntClass *winFntPtr, uint16 index, uint16 *aWidth, uint16 *aHeight );

#ifdef __cplusplus
}
#endif  

#endif 

