/*
  $Header: /home/archive/FontFusion/FontFusion/core/truetype.h,v 1.23 2009/04/29 10:29:11 ljoshi Exp $

 * TRUETYPE.H
 * Font Fusion Copyright (c) 1989-2009 all rights reserved by Bitstream Inc.
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

#ifndef __T2K_TRUETYPE__
#define __T2K_TRUETYPE__
#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif  /* __cplusplus */

/*
 * T2K internal font wide metric data type. used here and in T2KSBIT.H
 */
typedef struct
{
	int			isValid;
	int16		Ascender;
	int16		Descender;
	int16		LineGap;
	uint16		maxAW;
	F16Dot16	caretDx, caretDy;

	int16 underlinePosition;	/* Zero, if unknown. */
	int16 underlineThickness;	/* Zero, if unknown. */
} T2K_FontWideMetrics;


#ifndef FF_FFCONFIG_HEADER
#include "config.h"
#else
#include FF_FFCONFIG_HEADER
#endif


#include FF_TT_PRVT_HEADER
#include FF_GLYPH_HEADER
#include FF_T1_HEADER
#include FF_T2KSBIT_HEADER


#ifdef ALGORITHMIC_STYLES
#include FF_SHAPET_HEADER
#endif

#ifdef ENABLE_T2KE
#include FF_T2KEXEC_HEADER
#endif

#ifdef ENABLE_PFR
#include FF_PFRREAD_HEADER
#endif

#ifdef ENABLE_SPD
#include FF_SPDREAD_HEADER
#endif

#if defined(ENABLE_PCL) | defined(ENABLE_PCLETTO)
#include FF_PCLREAD_HEADER
#endif

#ifdef ENABLE_NATIVE_TT_HINTS
#include FF_T2KTT_HEADER
#endif

#ifdef ENABLE_NATIVE_T1_HINTS
#include FF_FFT1HINT_HEADER
#endif

#ifdef ENABLE_BDF
#include FF_BDF_HEADER
#endif

#ifdef ENABLE_MAC_RFORK
#include FF_FORK_HEADER
#endif

#ifdef ENABLE_WINFNT
#include FF_WINFNT_HEADER
#endif

#ifdef ENABLE_OPENTYPE_SUPPORT
#include FF_T2KOTF_HEADER
#endif /* ENABLE_OPENTYPE_SUPPORT */
	
#ifdef ENABLE_POSTHINT_ALGORITHMIC_STYLES
typedef void (*StyleFuncPtr)( void *t2k, tsiMemObject *mem, int16 fontType, int16 UPEM, F16Dot16 params[]);
#else
typedef void (*StyleFuncPtr)( GlyphClass *glyph, tsiMemObject *mem, int16 fontType, int16 UPEM, F16Dot16 params[] );
#endif

typedef void (*StyleMetricsFuncPtr)( hmtxClass *hmtx, tsiMemObject *mem, int16 UPEM, F16Dot16 params[] );

#define MAX_STYLE_PARAMS 4


/* A private T2K internal structure containing scaling in formation. */
#define T2K_IMULSHIFT	0
#define T2K_IMULDIV		1
#define T2K_FIXMUL		2

typedef struct
{
	int16		nScale;
	int16		dShift;
	int32		dScale;
	int32		dScaleDiv2;
	F16Dot16	fixedScale;
	int16		scaleType;
} T2KScaleInfo;

void setT2KScaleFactors( F16Dot16 pixelsPerEm, int32 UPEM, T2KScaleInfo *si );

/* Only for use use when we do not want to use an hmtx class */
typedef uint16 (*FF_GetAWFuncPtr)( void *param1, uint16 gIndex);

/* Set to either Get_hmtx_AW or Get_Cached_AW or Get_Upem_Width */
#define FF_Set_GetAWFuncPtr_Reference1( sfntClassPtr, funcptr1, param1 ) (sfntClassPtr->GetAWFuncPtr1 = (funcptr1), sfntClassPtr->GetAWParam1 = (void *)(param1) )

/* If above set to Get_Cached_AW then set this to font format reader specific FF_GetAWFuncPtr */
#define FF_Set_GetAWFuncPtr_Reference2( sfntClassPtr, funcptr2, param2 ) (sfntClassPtr->GetAWFuncPtr2 = (funcptr2), sfntClassPtr->GetAWParam2 = (void *)(param2) )
#define FF_AW_CACHE_SIZE 251

#define FF_SET_NATIVE_HINTS( font, bol_value ) ((font)->useNativeHints  = (bol_value))
#define FF_SET_AUTO_HINTS( font, bol_value ) ((font)->useAutoHints  = (bol_value))
#define FF_SET_FONT_SCALE( font, xScaleIn, yScaleIn ) ( (font)->xScale = (xScaleIn),  (font)->yScale = (yScaleIn) )
#define FF_SET_STROKING( font, bol_value ) ((font)->strokeGlyph  = (bol_value))

#define FF_SetVertPos( font, value )  ((font)->Vert_Pos = (value))

typedef struct
{
	/* private */
	sfnt_OffsetTable	*offsetTable0;

	FF_GetAWFuncPtr		 GetAWFuncPtr1;
	void				*GetAWParam1;
	FF_GetAWFuncPtr		 GetAWFuncPtr2;
	void				*GetAWParam2;
	uint16				*awCache_hashKey;
	uint16				*awCache_aw;

	uint16				upem;

#ifdef ENABLE_T1
	T1Class *T1;
#endif
#ifdef ENABLE_CFF
	CFFClass *T2;
#endif
#ifdef ENABLE_T2KE
	T2KEClass *T2KE;
#endif
#ifdef ENABLE_PFR
	PFRClass *PFR;
#endif
#ifdef ENABLE_SPD
	SPDClass *SPD;
#endif
#ifdef ENABLE_PCL
	PCLClass *PCLeo;
#endif
#ifdef ENABLE_PCLETTO
	PCLettoClass *PCLetto;
#endif
#ifdef ENABLE_BDF
	bdfClass *bdf;
#endif
#ifdef ENABLE_T2KS
	slocClass	*sloc;
	ffstClass	*ffst;
	ffhmClass	*ffhm;
#endif
#ifdef ENABLE_SBIT
	blocClass	*bloc;
	ebscClass	*ebsc;
	uint32		bdatOffset;
#endif
#ifdef ENABLE_NATIVE_TT_HINTS
	T2KTTClass *t2kTT;
#endif
#ifdef ENABLE_NATIVE_T1_HINTS
	FFT1HintClass *ffhint;
#endif

	ttcfClass	*ttcf;
	headClass	*head;
	maxpClass	*maxp;
	locaClass	*loca;
	gaspClass	*gasp;
	hheaClass	*hhea;
	hheaClass	*vhea;
	hmtxClass	*hmtx;
	hmtxClass	*vmtx;
	cmapClass	*cmap;
	kernClass	*kern;

#ifdef ENABLE_MAC_RFORK
	rforkClass *rfork;
#endif

#ifdef ENABLE_WINFNT
	winFntClass *winFnt;
#endif

#ifdef ENABLE_OPENTYPE_SUPPORT
	t2kotfClass * otf;
#endif/* ENABLE_OPENTYPE_SUPPORT */

#ifdef ENABLE_SBITS_COMPRESSION
	symbClass	*symb;
#endif

	CFF_Class	CFF;
	DSIGClass	DSIG;

	uint16	preferedPlatformID, preferedPlatformSpecificID;

	int16	post_underlinePosition;		/* Zero, if unknown. */
	int16	post_underlineThickness;	/* Zero, if unknown. */

	uint32	isFixedPitch;			/* 0 = proportional, non-0 = monospace */
	uint32	firstCharCode;			/* lowest code point, character code in font */
	uint32	lastCharCode;			/* highest code point, character code in font */
	uint16	hintsAvailable;			/* hinting tables are available = 0x00 */
	uint16	PCLetto_pitch;			/* PCLetto pitch for whitespace glyphs */

	int32	xPPEm, yPPEm;

	void	*globalHintsCache;

	StyleFuncPtr		StyleFunc;
	StyleMetricsFuncPtr	StyleMetricsFunc;
	F16Dot16			params[MAX_STYLE_PARAMS];

	/* For Stroke Font Hints */
	F16Dot16	xScale, yScale;
	int			useNativeHints;
	int			useAutoHints;
	int			strokeGlyph;
	int			greyScaleLevel;

#ifdef ENABLE_T2KS
	F16Dot16	currentCoordinate[2];
#endif

	int16			fontType;
	uint8			Vertical;
	uint8			Vert_Sub;
	uint8			Vert_Pos;	/* 0 = off, 1 = middle right, 2 = upper right */
	uint8			Vert_Rotate;

	InputStream		*in;		/* Primary InputStream */
	InputStream		*in2;		/* Secondary InputStream, normally == NULL, except for Type 1 fonts with kerning */
	OutputStream	*out;
	tsiMemObject	*mem;

	/* OrionModelClass *model; */
	void			*model;

	/* public */
	int32			numGlyphs;
	int32			numberOfLogicalFonts;	/* Number of logical fonts inside, normally == 1. */

#ifdef ENABLE_OTF
	int16			sTypoAscender;
	int16			sTypoDescender;
	uint8			OS2Table;
#endif

} sfntClass;

hmtxClass *New_hmtxEmptyClass( tsiMemObject *mem, int32 numGlyphs, int32 numberOfHMetrics );
void Delete_hmtxClass( hmtxClass *t );

/* Some useful getter methods */
uint16 GetUPEM( sfntClass *t);
int GetMaxPoints( sfntClass *t);

void GetFontWideOutlineMetrics( sfntClass *font, T2K_FontWideMetrics *hori, T2K_FontWideMetrics *vert );


typedef struct
{
	StyleFuncPtr		StyleFunc;
	StyleMetricsFuncPtr	StyleMetricsFunc;
	F16Dot16			params[MAX_STYLE_PARAMS];
} T2K_AlgStyleDescriptor;


void FF_SetAlgorithmicStyle(sfntClass *sfnt, T2K_AlgStyleDescriptor *StylePtr, int *errCode);
void FF_SetStyling( sfntClass *t, T2K_AlgStyleDescriptor *styling );


/* Caller does something like in = New_InputStream3( t->mem, data, length ); */
#define FONT_TYPE_UNKNOWN	-1
#define FONT_TYPE_1			 1
#define FONT_TYPE_2			22
#define FONT_TYPE_TT_OR_T2K	 2
#define FONT_TYPE_PFR		 3
#define FONT_TYPE_PCL		 4
#define FONT_TYPE_PCLETTO	 5
#define FONT_TYPE_SPD		 6
#define FONT_TYPE_OTF		 7
#define FONT_TYPE_BDF		 8
#define FONT_TYPE_RFORK		 9
#define FONT_TYPE_WINFNT	10

/* Next two for backwards compatibility. */
#define New_sfntClassLogical( mem, fontType, fontNum, in, styling, errCode ) FF_New_sfntClass( mem, fontType, fontNum, in, NULL, styling, errCode )

#ifdef ENABLE_PCLETTO
typedef struct
{
	uint8	lsbSet;
	uint16	lsb;
	uint8	awSet;
	uint16	aw;
	uint8	tsbSet;
	uint16	tsb;
} HPXL_MetricsInfo_t;

/* callback for getting outline char string pointer from application environment: */
int tt_get_char_data(int32 cCode,
					 uint8 cmd,
					 uint8 **pCharData,
					 uint16 *dataSize,
					 uint16 *gIndex,
					 HPXL_MetricsInfo_t	*metricsInfo
					);
#endif

#ifdef ENABLE_PCL
/* callback for getting outline char string pointer from application environment: */
int eo_get_char_data(int32 cCode,
					 uint8 cmd,
					 uint8 **pCharData,
					 uint16 *dataSize,
					 uint16 *charCode,
					 uint16 *gIndex
					);
#endif

#define New_sfntClass( mem, fontType, in, styling, errCode ) New_sfntClassLogical( mem, fontType, 0, in, styling, errCode )

/*
 * Creates a new font (sfntClass) object.
 * Parameters:
 * mem: 		A pointer to tsiMemObject
 * fontType:	Type of font.
 * fontNum:		Logical font number.
 * in1:			The primary InputStream.
 * in2:			The seconday InputStream. This is normally == NULL.
 * styling:		An function pointer to a function that modifies the outlines algorithmically. This is normally == NULL.
 * errCode:		The returned errorcode.
 */
sfntClass *FF_New_sfntClass( tsiMemObject *mem, int16 fontType, int32 fontNum, InputStream *in1, InputStream *in2, T2K_AlgStyleDescriptor *styling, int *errCode );

#define CMD_GRID		2
#define CMD_TT_TO_T2K	3
#define CMD_T2K_TO_TT	4
#define CMD_HINT_ROMAN	5
#define CMD_HINT_OTHER	6
#define CMD_TT_TO_T2KE	7

sfntClass *New_sfntClass2( sfntClass *sfnt0, int cmd, int param );
sfnt_OffsetTable *New_sfnt_OffsetTable( tsiMemObject *mem, InputStream *in );

void Delete_sfnt_OffsetTable( sfnt_OffsetTable *t );
void WriteToFile_sfntClass( sfntClass *t, const int8 *fname );
void Purge_cmapMemory( sfntClass *t );
void ff_LoadCMAP( sfntClass *t );

#define tag_T2KG		0x54324B47		/* 'T2KG' */
#define tag_T2KC		0x54324B43		/* 'T2KC' */

sfnt_DirectoryEntry *GetTableDirEntry_sfntClass( sfntClass *t, int32 tag );

/* caller need to do Delete_InputStream on the stream */
InputStream *GetStreamForTable( sfntClass *t, int32 tag  );

#define Delete_sfntClass( t, errCode ) FF_Delete_sfntClass( t, errCode )
void FF_Delete_sfntClass( sfntClass *t, int *errCode );

/*
 * Maps a PostScript Name to character code
 */
uint16 SfntClassPSNameTocharCode( sfntClass *t, int8 *PSName );

/*
 * Maps the character code to glyphIndex
 */
uint32 GetSfntClassGlyphIndex( sfntClass *t, uint32 charCode );

/*
 * Returns a glyph given the glyphIndex
 */
GlyphClass *GetGlyphByIndex( sfntClass *t, uint32 index, int8 readHints, uint16 *aWidth, uint16 *aHeight );
/*
 * Returns a glyph given the character code.
 */
#define GetGlyphByCharCode( t, charCode, readHints, aw, ah ) GetGlyphByIndex( t, GetSfntClassGlyphIndex(t,charCode), readHints, aw, ah )

int IsFigure( sfntClass *t, uint32 gIndex );

#ifdef ENABLE_KERNING
void GetSfntClassKernValue( sfntClass *t, uint32 leftGIndex, uint32 rightGIndex, int16 *xKern, int16 *yKern );
#endif


int32 GetNumGlyphs_sfntClass( sfntClass *t );

void GetTTNameProperty( sfntClass *font, uint16 languageID, uint16 nameID, uint8 **p8, uint16 **p16 );

void ff_KernShellSort(kernPair0Struct *pairs, int num_pair);

/*
 * Internal list characters function
*/
void T2K_SfntListChars(void *userArg, sfntClass *t, void *ctxPtr, int ListCharsFn(void *userArg, void *p, uint16 code), int *errCode);

#ifdef ENABLE_GASP_TABLE_SUPPORT
/*
 * IN: t, ppem
 * OUT: useGridFitting, useGrayScaleRendering
 * returns true if information found
 */
int Read_gasp( gaspClass *t, sfntClass *font, int ppem, int *useGridFitting, int *useGrayScaleRendering );
#endif


#ifdef ENABLE_NATIVE_TT_HINTS
#include FF_T2KTT_HEADER
#endif

/***** ***** ***** ***** ***** ***** *****/
locaClass *New_locaClass( tsiMemObject *mem, InputStream *in, int16 indexToLocFormat, int32 length );

#ifdef ENABLE_WRITE
void CreateTableIfMissing( sfnt_OffsetTable *t, int32 tag );
sfnt_OffsetTable *New_sfnt_EmptyOffsetTable( tsiMemObject *mem, int16 numberOfOffsets );
void Write_sfnt_OffsetTable( sfnt_OffsetTable *t, OutputStream *out );
void Write_locaClass( locaClass *t, OutputStream *out );
void SortTableDirectory( sfnt_OffsetTable *offsetTable );
void CalculateNewCheckSums( sfntClass *sfnt );
void Write_hmtxClass( hmtxClass *t, OutputStream *out);
void Write_maxpClass( maxpClass *t, OutputStream *out );
void Write_headClass( headClass *t, OutputStream *out);
void Write_hheaClass( hheaClass *t, OutputStream *out);
int32 CalculateCheckSumAdjustment( sfntClass *sfnt );
uint8 *GetTTFPointer( sfntClass *sfnt );
uint32 GetTTFSize( sfntClass *sfnt );

void TEST_T2K_CMAP( InputStream *in, uint16 *charCodeToGIndex, int32 N, uint16 platformID, uint16 encodingID);

#endif /* ENABLE_WRITE */
/***** ***** ***** ***** ***** ***** *****/

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* __T2K_TRUETYPE__ */


/*********************** R E V I S I O N   H I S T O R Y **********************
 *
 *     $Header: /home/archive/FontFusion/FontFusion/core/truetype.h,v 1.23 2009/04/29 10:29:11 ljoshi Exp $
 *                                                                           *
 *     $Log: truetype.h,v $
 *     Revision 1.23  2009/04/29 10:29:11  ljoshi
 *     Adding t2kotf class.
 *
 *     Revision 1.22  2009/04/27 18:14:24  sflynn
 *     Added sfnt->Vert_Rotate flag
 *
 *     Revision 1.21  2009/04/14 17:12:18  sflynn
 *     Added sfnt->Vert_Pos flag.
 *     Added FF_SetVertPos() macro.
 *
 *     Revision 1.20  2009/04/09 15:13:41  sflynn
 *     sfnt->Vertical changed to a uint8
 *     added uint8 sfnt->Vert_Sub
 *
 *     Revision 1.19  2009/04/03 19:29:55  sflynn
 *     Added sfnt->Vertical for "vertical" writing flag
 *
 *     Revision 1.18  2009/02/05 21:51:19  sflynn
 *     Changed include of pclread.h to ENABLE_PCL | ENABLE_PCLETTO.
 *     Added PCLettoClass pointer in sfntClass structure.
 *
 *     Revision 1.17  2008/11/19 22:23:47  sflynn
 *     Added "int16 fontType" to typedefs of StyleFuncPtr().
 *     Added "int16 fontType" to sfntClass structure.
 *
 *     Revision 1.16  2008/11/05 12:32:24  ljoshi
 *     Adding support for ENABLE_FRACTIONAL_SIZE.
 *
 *     Revision 1.15  2008/07/29 05:57:22  ljoshi
 *     Lokesh/Rohit: Fixing the compile error due to T2K definition conflict.
 *
 *     Revision 1.14  2008/07/08 13:02:41  rpasricha
 *     Implementation of post-hint Emboldening
 *
 *     Revision 1.13  2008/02/12 20:15:07  sflynn
 *     Updated for 32-bit character code support.
 *
 *     Revision 1.12  2008/01/07 05:19:53  ljoshi
 *     Moving the logic to disable hinting when x/y ppem is less than lowestRecPPEM to Read_gasp.
 *
 *     Revision 1.11  2007/11/13 14:40:19  ritesh
 *     Ritesh: Added the support for the windows fnt font format.
 *
 *     Revision 1.10  2007/11/06 13:19:58  himanshu
 *     Adding support for variable include file name.
 *
 *     Revision 1.9  2007/09/17 18:47:21  sflynn
 *     Added member "uint16 PCLetto_pitch" to the sfntClass.
 *
 *     Revision 1.8  2007/09/10 16:41:25  sflynn
 *     Added member sfntClass->useAutoHints and macro FF_SET_AUTO_HINTS().
 *
 *     Revision 1.7  2007/09/06 14:34:02  sflynn
 *     Added sfntClass members OS2Table, sTypoAscender and sTypoDescender.
 *
 *     Revision 1.6  2007/04/05 15:57:19  sflynn
 *     Modified for support of Dfont fonts.
 *
 *     Revision 1.5  2007/01/04 22:14:26  sflynn
 *     Added "symb" class for compressed embedded bitmaps.
 *
 *     Revision 1.4  2006/09/27 13:49:52  sflynn
 *     Added sfntClass->hintsAvailable member.
 *
 *     Revision 1.3  2006/04/28 17:49:29  sflynn
 *     no message
 *
 *     Revision 1.33  2005/10/06 19:33:04  Shawn_Flynn
 *     Modified to support BDF format font files.
 *     FONT_TYPE_BDF added to list of font types.
 *
 *     Revision 1.32  2003/10/07 18:14:34  Shawn_Flynn
 *     Added prototype statements for:
 *     FF_SetStyling()
 *     FF_SetAlgorithmicStyle()
 *
 *     Revision 1.31  2003/04/03 17:46:12  Shawn_Flynn
 *     Removed C++ style comments.
 *
 *     Revision 1.30  2003/01/10 21:04:05  Shawn_Flynn
 *     dtypED again.
 *
 *     Revision 1.29  2003/01/09 17:00:21  Shawn_Flynn
 *     dtypED.
 *
 *     Revision 1.28  2002/03/06 16:07:39  Shawn_Flynn
 *     Added CFF_Class and DSIGClass for OpenType 'CFF ' and 'DSIG' tables.
 *     Added "FONT_TYPE_OTF   7" for OpenType and "FONT_TYPE_UNKNOWN  -1".
 *
 *     Revision 1.27  2001/05/04 21:44:39  reggers
 *     Warning cleanup
 *     Revision 1.26  2001/05/03 20:46:51  reggers
 *     LoadCMAP mapped to ff_LoadCMAP
 *     Revision 1.25  2001/04/27 20:33:38  reggers
 *     Added new API function T2K_ForceCMAPChange()
 *     Revision 1.24  2001/04/24 21:57:17  reggers
 *     Added GASP table support (Sampo).
 *     Revision 1.23  2001/04/19 17:38:55  reggers
 *     Sampo mod to support improved stroke font hinting.
 *     Revision 1.22  2000/05/17 20:43:39  mdewsnap
 *     Fixed Hint Include file name.
 *     Revision 1.21  2000/04/27 21:35:47  reggers
 *     New Stroke convert painting
 *     Revision 1.20  2000/04/19 19:01:17  mdewsnap
 *     Added in code to deal with T1 hints
 *     Revision 1.19  2000/04/14 17:01:01  reggers
 *     First cut applying selective hints to stroke font glyphs.
 *     Revision 1.18  2000/03/10 19:18:32  reggers
 *     Enhanced for enumeration of character codes in font.
 *     Revision 1.17  2000/02/18 18:56:19  reggers
 *     Added Speedo processor capability.
 *     Revision 1.16  2000/01/20 15:48:26  reggers
 *     Changed MKS comment to correct to ENABLE_PCLETTO
 *     Revision 1.15  2000/01/20 15:47:20  reggers
 *     HPXLMetricsInfo_t now defined only on ENABLE_PCLETTO.
 *     Revision 1.14  2000/01/19 19:21:28  reggers
 *     Changed all references to PCLClass member PCL to PCLeo to
 *     avoid nasty namespace conflict on Windows builds.
 *     Revision 1.13  2000/01/18 20:53:59  reggers
 *     Changes to abstract the character directory and character string
 *     storage to the application environment for ENABLE_PCL.
 *     Revision 1.11  2000/01/07 19:46:04  reggers
 *     Sampo enhancements for FFS fonts.
 *     Revision 1.10  1999/12/23 22:03:19  reggers
 *     New ENABLE_PCL branches. Rename any 'code' and 'data' symbols.
 *     Revision 1.9  1999/11/04 20:20:38  reggers
 *     Added code for getting fixed/proportional setting, firstCharCode and
 *     lastCharCode.
 *     Revision 1.8  1999/10/18 17:02:46  jfatal
 *     Changed all include file names to lower case.
 *     Revision 1.7  1999/09/30 15:12:31  jfatal
 *     Added correct Copyright notice.
 *     Revision 1.6  1999/08/27 20:08:54  reggers
 *     Latest changes from Sampo
 *     Revision 1.5  1999/07/29 16:10:53  sampo
 *     First revision for T2KS
 *     Revision 1.4  1999/07/19 16:59:40  sampo
 *     Prototype of kern shell sort routine moved here from util.h
 *     Revision 1.3  1999/07/16 17:52:12  sampo
 *     Sampo work. Drop #8 July 16, 1999
 *     Revision 1.2  1999/05/17 15:58:45  reggers
 *     Inital Revision
 *                                                                           *
******************************************************************************/
