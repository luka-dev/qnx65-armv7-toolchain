/*
 * Glyph.h
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

#ifndef __T2K_GLYPH__
#define __T2K_GLYPH__
#ifdef __cplusplus
extern "C" {            
#endif  

#ifdef ENABLE_T2KE

#ifndef FF_FFCONFIG_HEADER
#include "config.h"
#else
#include FF_FFCONFIG_HEADER
#endif 


#include FF_T2KSC_HEADER
#include FF_T2K_CLRSCR_HEADER
#endif


#define BASE0 0
#define BASE1 2200
#define BASE2 12604
#define BASE3 14652
#define BASEMAX 16384


#define SbPtCount	4


#define COMPONENTCTRCOUNT				-1		
#define ARG_1_AND_2_ARE_WORDS		0x0001	
#define ARGS_ARE_XY_VALUES			0x0002	
#define ROUND_XY_TO_GRID			0x0004	
#define WE_HAVE_A_SCALE				0x0008	
#define NON_OVERLAPPING				0x0010	
#define MORE_COMPONENTS				0x0020	
#define WE_HAVE_AN_X_AND_Y_SCALE	0x0040	
#define WE_HAVE_A_TWO_BY_TWO		0x0080	
#define WE_HAVE_INSTRUCTIONS		0x0100	
#define USE_MY_METRICS				0x0200	


#define T2K_CTR_BUFFER_SIZE 8
typedef struct
{
	
	tsiMemObject	*mem;

	int16	contourCountMax;
	int32	pointCountMax;

	int32	colorPlaneCount;
	int32	colorPlaneCountMax;

	int16	ctrBuffer[T2K_CTR_BUFFER_SIZE + T2K_CTR_BUFFER_SIZE];

#ifdef ENABLE_T2KE
	tsiColorDescriptor	*colors;
	uint16				 gIndex; 
#endif

	
	int16	curveType;		
	int16	contourCount;	
	int16	pointCount;		
	int16	*sp;			
	int16	*ep;  			
	int16	*oox;			
	int16	*ooy;			
							
							
	uint8	*onCurve;		

	F26Dot6	*x, *y;			

	int16	*componentData;
	int32	componentSize;
	int32	componentSizeMax;

	uint8	*hintFragment;
	int32	hintLength;

	int16	xmin, ymin, xmax, ymax;

	int8	dropOutControl; 
	uint16	myGlyphIndex;
#ifdef ENABLE_PSEUDOFONT_SUPPORT
	int16	fleftCorrection;
#endif
} GlyphClass;

#ifdef ENABLE_FF_CURVE_CONVERSION


GlyphClass *FF_ConvertGlyphSplineTypeInternal( GlyphClass *glyph, int16 curveTypeOut );

#endif 

GlyphClass *New_EmptyGlyph( tsiMemObject *mem, int16 lsb, uint16 aw, int16 tsb, uint16 ah );

void ResequenceContoursAndPoints( GlyphClass *glyph, int closed );
int32 Write_GlyphClassT2K( GlyphClass *glyph, OutputStream *out, void *model );
GlyphClass *New_GlyphClassT2K( tsiMemObject *mem, InputStream *in, int8 readHints, int16 lsb, uint16 aw, int16 tsb, uint16 ah, void *model );

GlyphClass *New_GlyphClassT2KE( void *t, register InputStream *in, int32 byteCount, int16 lsb, uint16 aw, int16 tsb, uint16 ah);
int32 Write_GlyphClassT2KE( GlyphClass *glyph, OutputStream *out );

void TEST_T2K_GLYPH( tsiMemObject *mem );

#ifdef T1_OR_T2_IS_ENABLED
void glyph_CloseContour( GlyphClass *t );
void glyph_AddPoint( GlyphClass *t, int32 x, int32 y, uint8 onCurveBit );
void glyph_StartLine( GlyphClass *t, int32 x, int32 y );
#endif 

#ifdef ENABLE_T2KE
void glyph_CloseColorContour( GlyphClass *glyph, tsiColorDescriptor *color );
#endif

#ifdef ENABLE_PRINTF
void glyph_PrintPoints( GlyphClass *t );
#endif

#ifdef ENABLE_WRITE
#define CURVE_CONVERSION
#ifdef CURVE_CONVERSION
GlyphClass *glyph_Convert3rdDegreeGlyphTo2ndDegree( GlyphClass *glyph1 );
int glyph_RemoveRedundantPoints( GlyphClass *glyph, int pass );
#endif 
#endif 
#ifdef ENABLE_WRITE
void WriteDeltaXYValue( OutputStream *out, int dx, int dy, int8 onCurve );
#endif
int ReadDeltaXYValue( InputStream *in, int16 *dxPtr, int16 *dyPtr );
#ifdef ENABLE_ORION
int ReadOrionDeltaXYValue( InputStream *in, void *model, int16 *dxPtr, int16 *dyPtr );
#endif

void Add_GlyphClass( GlyphClass **tPtr, GlyphClass *addMe, uint16 flags, int32 arg1, int32 arg2 );

void AllocGlyphPointMemory( GlyphClass *t, int32 pointCount );
void glyph_AllocContours( GlyphClass *t, int16 contourCountMax );

void Delete_GlyphClass( GlyphClass *t );

#ifdef __cplusplus
}
#endif  

#endif 


