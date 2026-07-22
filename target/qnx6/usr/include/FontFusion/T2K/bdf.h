/*
 * bdf.h
 * Font Fusion Copyright (c) 1989-2005 all rights reserved by Bitstream Inc.
 * http://www.bitstream.com/
 * http://www.typesolutions.com/
 * Author: Ritesh Singh
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


#ifndef __BDF_HEADER_
#define __BDF_HEADER_
#ifdef __cplusplus
extern "C" {            
#endif  


#ifndef FF_FFCONFIG_HEADER
#include "config.h"
#else
#include FF_FFCONFIG_HEADER
#endif 

typedef struct {
	uint16 uniCode;
	uint32 offset;
} bdfUnicodeOffset;

typedef struct {
int32 vVectorx , vVectory;
} bdfGlobalVector;

typedef struct {
	int32 sWidth0_1, sWidth0_2;
	int32 dWidth0_1, dWidth0_2;
	int32 sWidth1_1, sWidth1_2;
	int32 dWidth1_1, dWidth1_2;
	bdfGlobalVector *vVector;
} bdfMetricsWidths;

typedef struct  {
	tsiMemObject	*mem; 
	InputStream		*in;

	uint32 copyrightNotice;
	uint32 fontFamilyName; 
	uint32 fontSubfamilyName; 
	uint32 uniqueFontIdentifier; 
	uint32 fullFontName; 
	uint32 fontVersionString; 
	uint32 fontPostscriptName; 
	uint32 fontTradeMark; 

	int8 *linePtr;
	uint32 length;
	int32 metricsSet;
	bdfMetricsWidths *sdwidths;
	uint16 pixelSize;
	uint32 bitsAtPtSize;
	uint16 firstCharCode;
	uint16 lastCharCode;
	int32 fontNum;
	uint32 numGlyf; 
	int32 pointSize;
	int32 newPointSize;
	int32 xres, yres, bits;

	int32 xmax, ymax, xmin, ymin;
	int32 ascent, descent;

	int32 bbx;
	int32 encoding ;
	int32 defCharEncoding; 
	int32 underLinePos;
	int32 underLineThickness;
	bdfUnicodeOffset *ptr;
    int32 newPpemX  ;
	int32 newPpemY ;
	uint8 requestedBitDepth; 

} bdfClass;

bdfClass *tsi_NewBDFClass( tsiMemObject *mem, InputStream *in, int32 fontNum );

int tsi_BDFGetSbits ( void *p, int32 aCode, uint8 greyScaleLevel, uint16 cmd
#ifdef ENABLE_SBITS_TRANSFORM
				  , int8 xFracPenDelta, int8 yFracPenDelta
#endif 
				  );

uint8 *GetBdfNameProperty( bdfClass *bdfPtr, uint16 languageID, uint16 nameID );

uint16 tsi_BDFGetGlyphIndex ( bdfClass *bdfPtr, uint32 charCode );

void Bdf_GetFontWideMetrics( void *t, T2K_FontWideMetrics *hori, T2K_FontWideMetrics *vert );

void tsi_DeleteBDFClass( bdfClass *t );

uint16 FF_GetAW_BDFClass ( void *param1, register uint16 index );

void tsi_BDFGetGlyphByIndex ( bdfClass *bdfPtr, uint16 index, uint16 *aWidth, uint16 *aHeight );



#ifdef __cplusplus
}
#endif  
#endif 





