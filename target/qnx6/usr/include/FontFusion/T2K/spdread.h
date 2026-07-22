/*
 * SPDREAD.h
 * Font Fusion Copyright (c) 1989-2000 all rights reserved by Bitstream Inc.
 * http://www.bitstream.com/
 * http://www.typesolutions.com/
 * Author: Robert Eggers
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



#ifndef _SPDRead_H
#define _SPDRead_H
#ifdef __cplusplus
extern "C" {            
#endif  


#define  FH_FMVER    0      
#define  FH_FNTSZ    8      
#define  FH_FBFSZ   12      
#define  FH_CBFSZ   16      
#define  FH_HEDSZ   18      
#define  FH_FNTID   20      
#define  FH_SFVNR   22      
#define  FH_FNTNM   24      
#define  FH_MDATE   94      
#define  FH_LAYNM  104      
#define  FH_CPYRT  174      
#define  FH_NCHRL  252      
#define  FH_NCHRF  254      
#define  FH_FCHRF  256      
#define  FH_NKTKS  258      
#define  FH_NKPRS  260      
#define  FH_FLAGS  262      
                            
                            
                            
                            
                            
                            
                            
                            
#define  FH_CLFGS  263      
                            
                            
                            
                            
                            
                            
                            
                            
#define  FH_FAMCL  264      
                            
                            
                            
                            
                            
                            
                            
#define  FH_FRMCL  265      
                            
                            
                            
                            
                            
                            
                            
                            
                            
                            
                            
                            
                            
                            
                            
                            
                            
                            
                            
                            
                            
                            
                            
                            
                            
                            
                            
                            
                            
#define  FH_SFNTN  266      
#define  FH_SFACN  298      
#define  FH_FNTFM  314      
#define  FH_ITANG  328      
#define  FH_ORUPM  330      
#define  FH_WDWTH  332      
#define  FH_EMWTH  334      
#define  FH_ENWTH  336      
#define  FH_TNWTH  338      
#define  FH_FGWTH  340      
#define  FH_FXMIN  342      
#define  FH_FYMIN  344      
#define  FH_FXMAX  346      
#define  FH_FYMAX  348      
#define  FH_ULPOS  350      
#define  FH_ULTHK  352      
#define  FH_SMCTR  354      
#define  FH_DPSTR  360      
#define  FH_FNSTR  366      
#define  FH_ALSTR  372      
#define  FH_CMITR  378      
#define  FH_SNMTR  384      
#define  FH_SDNTR  390      
#define  FH_MNMTR  396      
#define  FH_MDNTR  402      
#define  FH_LNMTR  408      
#define  FH_LDNTR  414      
                            
                            
                            
                            
#define  FH_METRS  420      
#define  FH_PVHSZ  422      
#define  FH_NDSNA  424      


#define  FH_ORUMX    0      
#define  FH_PIXMX    2      
#define  FH_CUSNR    4      
#define  FH_OFFCD    6      
#define  FH_OFCNS    9      
#define  FH_OFFTK   12      
#define  FH_OFFPK   15      
#define  FH_OCHRD   18      
#define  FH_NBYTE   21      
#define  FH_OFIRN   24      
#define  FH_OFITM   27      
#define  FH_OFCAD   30      
#define  FH_OFTAD   33      
#define  FH_OFPAD   36      



#define KEY0    0                  
#define KEY1   72                  
#define KEY2  123                  
#define KEY3    1                  
#define KEY4  222                  
#define KEY5  194                  
#define KEY6  113                  
#define KEY7  119                  
#define KEY8   52                  

#define  BIT0           0x01
#define  BIT1           0x02
#define  BIT2           0x04
#define  BIT3           0x08
#define  BIT4           0x10
#define  BIT5           0x20
#define  BIT6           0x40
#define  BIT7           0x80



typedef struct point_tag
{
	int16   x;                     
	int16   y;                     
} point_t;                         


typedef struct
{
	uint16	charID;
	uint16	charIndex;
} spdCharDir_t;

typedef struct
{
	uint16	gpsSize;
	uint32	gpsOffset;
	uint16	charID;
} spdLocDir_t;

typedef struct
{
	uint8	start_edge;
	uint8	end_edge;
	int16	constr_nr;
} controlZone_t;

typedef struct
{
	uint8	start_edge;
	int16	start_adj;
	uint8	end_edge;
	int16	end_adj;
} interpolationTable_t;

typedef struct
{
	F16Dot16	m00;
	F16Dot16	m01;
	F16Dot16	m10;
	F16Dot16	m11;
	F16Dot16	xOffset;
	F16Dot16	yOffset;
} spdtcb_t;


typedef struct
{
	
	tsiMemObject	*mem;
	InputStream		*in;
	uint16			outlineRes;
	uint16			metricsRes;
	F16Dot16		xyScale;
	int8			verticalEscapement;
	uint8			contourOpen;
	uint8			shortScaleFactors;
	int32			lsbx;
	int32			lsby;
	int32			awx;
	int32			awy;
	uint8			weight;
	
	uint16			wordSpace;
	uint16			emSpace;
	uint16			enSpace;
	uint16			thinSpace;
	uint16			figureSpace;

	
	int16			minX;
	int16			minY;
	int16			maxX;
	int16			maxY;

	int16			uline_pos;
	int16			uline_thickness;


	spdtcb_t		fontMatrix;
	spdtcb_t		outputMatrix;
	spdtcb_t		tcb;

	uint8			fontName[64];		
	uint16			firstCharIndex;
	uint16			nKernPairs;
	uint32			charDirOffset;
	uint32			pairKernOffset;
	uint32			charDataOffset;
	uint16			NumLayoutChars;

	spdCharDir_t	*spdCodeToIndex;
	spdLocDir_t		*spdIndexToLoc;

	
	uint16			no_X_orus;
	uint16			no_Y_orus;
	int16			Y_edge_org;       
	int16			orus[256];        	

	
	int16			Y_zone_org;
	controlZone_t	controlZoneTbl[256];

	
	uint8			edge_org;
	int16			no_X_int_zones;
	int16			no_Y_int_zones;
	interpolationTable_t	interpolationTable[256];

	int16			x_orus, y_orus;

	
	GlyphClass		*glyph;
	hmtxClass		*hmtx;

	int16			NumCharStrings;
	int32			upem;
	int32			maxPointCount;
	int32			ascent;
	int32			descent;
	int32			lineGap;
	int32			advanceWidthMax;
	F16Dot16		italicAngle;
	kernClass		*kern;

	uint32			isFixedPitch;			
	uint16			firstCharCode;			
	uint16			lastCharCode;			

	int				glyphExists;			

} SPDClass;

SPDClass *tsi_NewSPDClass( tsiMemObject *mem, InputStream *in, int32 fontNum );
void tsi_DeleteSPDClass( SPDClass *t );
GlyphClass *tsi_SPDGetGlyphByIndex( SPDClass *t, uint16 index, uint16 *aWidth, uint16 *aHeight );
uint16 tsi_SPDGetGlyphIndex( SPDClass *t, uint32 charCode );
uint8 *GetSPDNameProperty( SPDClass *t, uint16 languageID, uint16 nameID );
void tsi_SPDListChars(void *userArg, SPDClass *t, void *ctxPtr, int ListCharsFn(void *userArg, void *p, uint16 code));


#ifdef __cplusplus
}
#endif  
#endif 






