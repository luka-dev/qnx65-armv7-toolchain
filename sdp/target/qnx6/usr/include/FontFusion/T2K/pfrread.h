/*
 * Pfrread.h
 * Font Fusion Copyright (c) 1989-1999 all rights reserved by Bitstream Inc.
 * http://www.bitstream.com/
 * http://www.typesolutions.com/
 * Author: Sampo Kaasila, Robert Eggers, Mike Dewsnap
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




#ifndef _PFRReader_H
#define _PFRReader_H
#ifdef __cplusplus
extern "C" {            
#endif  

#ifndef BITOUT
#define BITOUT 0
#endif

#ifndef FF_FFCONFIG_HEADER
#include "config.h"
#else
#include FF_FFCONFIG_HEADER
#endif 

#include FF_FFT1HINT_HEADER

#define PFRHEDFMT  0     
#define PFRHEDSIZ  8     
#define PFRLFDSIZ 10     
#define PFRLFDOFF 12     
#define PFRLFTSZM 14     
#define PFRLFTSZT 16     
#define PFRLFTFOF 19     
#define PFRPFTSZM 22     
#define PFRPFTSZT 24     
#define PFRPFTFOF 27     
#define PFRGPSSZM 30     
#define PFRGPSSZT 32     
#define PFRGPSFOF 35     
#define PFRBVLMAX 38     
#define PFRXCCMAX 39     
#define PFRYCCMAX 40     


#define PFRRSRVD0 41     
#define PFRRSRVD1 42     


#define PFRPFTSZX 41     
#define PFRRSRVD1 42     


#define PFRPFTSZX 41     
#define PFRRSRVD1 42     
#define PFRBCTSZM 43     
#define PFRBCSSZM 46     
#define PFRPFXSZM 49     


#define PFRPFTCNT 52     


#define PFRSSVMAX 54     
#define PFRSSHMAX 55     


#define PFRCHRMAX 56
#ifdef ENABLE_2DEGREE_OPTIMIZED_PFR
#define PFRNUMOFHUFFMANTREES	58 
#define HUFFMANTREESIZE		103	   
#endif

#define PFR_HEADER_SIZE 43 





#define PFRLFTTMX      0     
#define PFRLFTSFX     12     
#define LFTMITER    0x00
#define LFTROUND    0x01
#define LFTBEVEL    0x02
#define LFTLINEJOIN 0x03
#define LFTSTROKE   0x04
#define LFTBIGSTR   0x08



#define BIT_0 0x01
#define BIT_1 0x02
#define BIT_2 0x04
#define BIT_3 0x08
#define BIT_4 0x10
#define BIT_5 0x20
#define BIT_6 0x40
#define BIT_7 0x80

#define MAX_ORUS 64


#define PFR_BLACK_PIXEL BIT_0    
#define PFR_INVERT_BMAP BIT_1    


#define PFR_MAX_BLUEVALUES	14
#define PFR_MAX_SNAPS		12


#ifndef MSB_FIRST
#define MSB_FIRST	1
#endif


typedef struct charElement_tag
{
	int32	xScale;
	int32	xPosition;
	int32	yScale;
	int32	yPosition;
	uint32	glyphProgStringOffset;
	uint16	glyphProgStringSize;
	uint8	matchSpec;
} charElement_t;


typedef struct gpsExecContext_tag
{
	int16	nXorus;
	int16	xOruTable[MAX_ORUS];
	int16	nYorus;
	int16	yOruTable[MAX_ORUS];
	int16	xPrevValue;
	int16	yPrevValue;
	int16	xPrev2Value;
	int16	yPrev2Value;
#ifdef ENABLE_2DEGREE_OPTIMIZED_PFR
	
	uint8   (*pDecoderArray)[HUFFMANTREESIZE];
	uint8	nDecoderTrees;
#endif
} gpsExecContext_t;


typedef void (*extraItemActions_t[])(uint8 *pByte);


void InitGpsExecContext(gpsExecContext_t *pGpsExecContext);

void ReadGpsArgs(uint8 **ppBuff, uint8 format, gpsExecContext_t *pGpsExecContext, int16 *pX, int16 *pY);

int16 ReadByte(uint8 *pBuff);
int16 ReadWord(uint8 *pBuff);
int32 ReadLongSigned(uint8 *pBuff);
int32 ReadLongUnsigned(uint8 *pBuff);

void ShowExtraItems(uint8 **ppByte, extraItemActions_t actionTable);

void ShowPfrStats(void);

typedef struct
{
	uint16	charCode;
	uint16	gpsSize;
	int32	gpsOffset;
#ifdef ENABLE_PSEUDOFONT_SUPPORT
	int16	fleftCorrection;
#endif
} physCharMap;


typedef struct
{
	F16Dot16	m00;
	F16Dot16	m01;
	F16Dot16	m10;
	F16Dot16	m11;
	F16Dot16	xOffset;
	F16Dot16	yOffset;
} tcb_t;


typedef struct bmapCharDir_tag
{
	uint16	charIndex;	
	uint16	charCode;
	uint16	gpsSize;
	uint32	gpsOffset;
} bmapCharDir_t;	


typedef struct bmapStrike_tag
{
	uint16			xppm;
	uint16			yppm;
	int32			nBmapChars;
	bmapCharDir_t	*bmapDir;
} bmapStrike_t;


typedef struct pfrGlyphInfoData_tag
{
	uint16		glyphIndex;
	uint8		greyScaleLevel;
	uint16		ppemX;
	uint16		ppemY;
	int32		width, height;
	F16Dot16	horiBearingX;
	F16Dot16	horiBearingY;
	F16Dot16	horiAdvance;
	F16Dot16	vertBearingX;
	F16Dot16	vertBearingY;
	F16Dot16	vertAdvance;
	int32		bytesPerRow;
	uint8		invertBitmap;
	uint8		*gpsPtr;
	uint16		gpsSize;
	uint32		gpsOffset;
	uint8		*baseAddr; 
	uint8		*tempBuffer;
	uint8		*dst;	
}pfrGlyphInfoData;

typedef struct
{
	
	tsiMemObject	*mem;
	InputStream		*in;
	uint8			pfrType;
	physCharMap		*charMap;
	uint32			directoryCount;
	uint16			fontNumber;
	uint16			physFontNumber;
	uint16			outlineRes;
	uint16			metricsRes;
	int8			verticalEscapement;
	uint8			*pAuxData;
	int32			nAuxBytes;
	F16Dot16		xyScale;
	int32			firstGpsOffset;
	int32			totalGpsSize;
	uint8			contourOpen;
	uint8			shortScaleFactors;
	
	uint8			bmapFlags;
	uint16			nBmapStrikes;
	bmapStrike_t	*bmapStrikes;
	pfrGlyphInfoData	gInfo;
	int32			lsbx;
	int32			lsby;
	int32			awx;
	int32			awy;
	
	int16			xmin, ymin, xmax, ymax;
	int16			strokeThickness;
	uint16			headerSize, version;

	int16			boldThickness;
	void			*sfntClassPtr;	
	uint8			pluggedIn;		
	uint8			rendering;		


	tcb_t			fontMatrix;
	tcb_t			outputMatrix;
	tcb_t			tcb;

	uint8			*fontID;		

	
	GlyphClass		*glyph;
	hmtxClass		*hmtx, *noDelete_hmtx;

	int16			NumCharStrings;
	int32			upem;
	int32			maxPointCount;
	int32			ascent;
	int32			descent;
	int32			lineGap;
	int32			advanceWidthMax;
	F16Dot16		italicAngle;
	kernClass		*kern;


	int32			BlueValues[PFR_MAX_BLUEVALUES];  
	int32			numBlueValues;
	int32			BlueFuzz;
	F16Dot16		BlueScale;
	int32			BlueShift;
	int32			StdVW;
	int32			StdHW;
	int32			nStemSnapV;
	int32			nStemSnapH;

	int32			StemSnapH[PFR_MAX_SNAPS];
	int32			StemSnapV[PFR_MAX_SNAPS];

	uint32			isFixedPitch;			
	uint16			firstCharCode;			
	uint16			lastCharCode;			

	int				glyphExists;				
#ifdef ENABLE_2DEGREE_OPTIMIZED_PFR
	uint8			(*pDecoderArray)[HUFFMANTREESIZE];
	uint8			bProcessOptBezCurves;
	uint8			nDecoderTrees;
#endif
#ifdef ENABLE_PSEUDOFONT_SUPPORT
	uint8			bFleftCorrection;			 
#endif

} PFRClass;

PFRClass *tsi_NewPFRClass( tsiMemObject *mem, InputStream *in, int32 fontNum );
void tsi_DeletePFRClass( PFRClass *t );
GlyphClass *tsi_PFRGetGlyphByIndex( PFRClass *t, uint16 index, uint16 *aWidth, uint16 *aHeight, FFT1HintClass *ffhint);
uint16 tsi_PFRGetGlyphIndex( PFRClass *t, uint32 charCode );
uint8 *GetPFRNameProperty( PFRClass *t, uint16 languageID, uint16 nameID );

#ifdef ENABLE_SBIT
int PFR_GlyphSbitsExists( void *p, uint16 glyphIndex, uint8 greyScaleLevel, int *errCode  );
int PFR_GetSbits(void *p, int32 code, uint8 greyScaleLevel, uint16 cmd);
#endif

void tsi_PFRListChars(void *userArg, PFRClass *t, void *ctxPtr, int ListCharsFn(void *userArg, void *p, uint16 code));

#ifdef __cplusplus
}
#endif  
#endif 





