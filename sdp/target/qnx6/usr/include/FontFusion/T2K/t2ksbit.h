/*
 * T2ksbit.h
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

#ifndef __T2K_SBIT__
#define __T2K_SBIT__
#ifdef __cplusplus
extern "C" {            
#endif  


#ifdef ENABLE_SBIT

typedef struct
{
	uint16	height;
	uint16	width;
	int16	horiBearingX;
	int16	horiBearingY;
	uint16	horiAdvance;
	int16	vertBearingX;
	int16	vertBearingY;
	uint16	vertAdvance;
} bigGlyphMetrics;


typedef struct
{
	uint16 indexFormat;		
	uint16 imageFormat;		
	uint32 imageDataOffset;	
} indexSubHeader;

#ifdef ENABLE_CACHING_EBLC
typedef struct
{
	indexSubHeader header;
	uint32 *offsetArray;
}indexSubTable1;

typedef struct
{
	indexSubHeader header;
	uint32 imageSize;
	bigGlyphMetrics bigMetrics;
}indexSubTable2;

typedef struct
{
	indexSubHeader header;
	uint32 *offsetArray;
}indexSubTable3;

typedef struct
{
	uint16 glyphCode;
	uint16 offset;
}codeOffsetPair;

typedef struct
{
	indexSubHeader header;
	uint32 numGlyphs;
	codeOffsetPair *glyphArray;
}indexSubTable4;

typedef struct
{
	indexSubHeader header;
	uint32 imageSize;
	bigGlyphMetrics bigMetrics;
	uint32 numGlyphs;
	uint16 *glyphArray;
}indexSubTable5;


typedef struct
{
	uint16 firstGlyphIndex;						
	uint16 lastGlyphIndex;						
	indexSubHeader *indexSubTable;
} indexSubTableArray;

#else
typedef struct
{
	uint16 firstGlyphIndex;						
	uint16 lastGlyphIndex;						
	uint32 additionalOffsetToIndexSubTable;		 
} indexSubTableArray;
#endif 



#define NUM_SBIT_METRICS_BYTES 12


#define SBIT_SMALL_METRIC_DIRECTION_IS_HORIZONTAL	0x01
#define SBIT_SMALL_METRIC_DIRECTION_IS_VERTICAL		0x02


typedef struct
{
	
	tsiMemObject	*mem;

	
	uint32			indexSubTableArrayOffset;		
	uint32			indexTableSize;					
	uint32			numberOfIndexSubTables;			
	uint32			colorRef;						

	uint8			hori[NUM_SBIT_METRICS_BYTES];	
	uint8			vert[NUM_SBIT_METRICS_BYTES];	

	uint16			startGlyphIndex;				
	uint16			endGlyphIndex;					
	uint8			ppemX;							
	uint8			ppemY;							
	uint8			bitDepth;						
	uint8			flags;							

	indexSubTableArray	*table;						
} bitmapSizeTable;

typedef struct
{
	
	uint32	offset;								
	uint32	glyphIndex;							
	uint16	ppemX, ppemY;						
	uint16	substitutePpemX, substitutePpemY;	
	uint8	substituteBitDepth, bitDepth;		
	uint8	flags;								
	uint16	imageFormat;						

	bigGlyphMetrics bigM;						

	int		smallMetricsUsed;					

	
	int32	rowBytes;							
	uint8	*baseAddr;							

	
	uint32	N;									

#ifdef ENABLE_SBITS_COMPRESSION
	uint32 blockOffset;
	uint8 compLength;
#endif 
} sbitGlypInfoData;

#ifdef ENABLE_SBITS_COMPRESSION

typedef struct {
	uint8 noOfPix;
	uint8 shift;
	uint8 mask;
	uint32 column;
} barStruct;

typedef struct {

	uint8 *lookup;
	uint8 *huffTree;
	uint8 *patternData;

	int8 patternIndex;
	uint8 maxY;
	uint8 noOfBars;
	barStruct *barArray;

} symbolTable_t;

typedef struct {
    
    tsiMemObject *mem;
	uint32	startOffset;

    
    uint32 numSizes;
	symbolTable_t * symbolTableArr;

	symbolTable_t * activeSymbolTable;

} symbClass;
#endif 


typedef struct
{
	
	tsiMemObject	*mem;
	uint32			startOffset;
	int				fontIsSbitOnly;
	uint32			requestedBitDepth;
	
	
	sbitGlypInfoData	gInfo;

	
	F16Dot16		version; 
	uint32			nTables; 

	bitmapSizeTable	*table; 
#ifdef ENABLE_CACHING_EBLC
	uint8 *cacheTables;
#endif 

#ifdef ENABLE_SBITS_COMPRESSION
	symbClass		*symb;
#endif 
} blocClass;


typedef struct
{
	uint8	hori[NUM_SBIT_METRICS_BYTES];		
	uint8	vert[NUM_SBIT_METRICS_BYTES];		
	uint8	ppemX;							
	uint8	ppemY;							
	uint8	substitutePpemX;					
	uint8	substitutePpemY;					
} bitmapScaleEntry;


typedef struct
{
	
	tsiMemObject	*mem;
	uint32			startOffset;

	
	F16Dot16		version; 	
	uint32			numSizes;	

	bitmapScaleEntry	*table; 
} ebscClass;



ebscClass *New_ebscClass( tsiMemObject *mem, InputStream *in );


void Delete_ebscClass( ebscClass *t );


blocClass *New_blocClass( tsiMemObject *mem, int fontIsSbitOnly, InputStream *in );


void Delete_blocClass( blocClass *t );



void GetFontWideSbitMetrics(blocClass *bloc, ebscClass *ebsc, uint16 ppemX, uint16 ppemY,
							T2K_FontWideMetrics *hori, T2K_FontWideMetrics *vert );


int FindGlyph_blocClass(blocClass *t, ebscClass *ebsc, InputStream *in, uint32 glyphIndex,
						uint16 ppemX, uint16 ppemY, sbitGlypInfoData *result );


#define MAX_SBIT_RECURSION_DEPTH	16

void ExtractBitMap_blocClass(blocClass *t, ebscClass *ebsc, sbitGlypInfoData *gInfo, InputStream *in,
							 uint32 bdatOffset, uint8 greyScaleLevel, int recursionLevel, int myBlackValue, uint16 cmd );

#ifdef ENABLE_SBITS_COMPRESSION


symbClass *New_symbClass(tsiMemObject *mem, InputStream *in);


void Delete_symbClass(symbClass * symb);

#endif 

#endif 

#ifdef __cplusplus
}
#endif  
#endif 


