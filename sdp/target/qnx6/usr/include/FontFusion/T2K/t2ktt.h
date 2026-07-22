/*
 * T2KTT.H
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

#ifndef __T2K_TT__
#define __T2K_TT__





#ifndef FF_FFCONFIG_HEADER
#include "config.h"
#else
#include FF_FFCONFIG_HEADER
#endif 

#include FF_FNT_HEADER

#ifdef __cplusplus
extern "C" {            
#endif  

typedef struct
{
	

	

	
	tsiMemObject	*mem;
	int32			xPixelsPerEm, yPixelsPerEm;
	int16			*ocvt;
	int32			numCVTs;
	F26Dot6			*ptr32;

	fnt_GlobalGraphicStateType	globalGS;

	uint16			UPEM;
	int16			maxTwilightPoints;
	uint32			pgmLength[MAXPREPROGRAMS];	
	uint8			delete_preprograms;

	int16			spZeroWord, epZeroWord;
	fnt_ElementType	elements[2];
} T2KTTClass;


T2KTTClass *New_T2KTTClass( tsiMemObject *mem, InputStream *in, void *font );


void SetScale_T2KTTClass( T2KTTClass *t, int32 xPixelsPerEm, int32 yPixelsPerEm, int8 non90DegreeTransformation );

void GridOutline_T2KTTClass( T2KTTClass *t, GlyphClass *glyph );



void Delete_T2KTTClass( T2KTTClass *t );

#ifdef __cplusplus
}
#endif  
#endif 



