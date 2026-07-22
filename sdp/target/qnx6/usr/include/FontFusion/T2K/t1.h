/*
	$Header: /home/archive/FontFusion/FontFusion/core/t1.h,v 1.10 2008/02/12 20:05:53 sflynn Exp $

 * t1.h
 * Font Fusion Copyright (c) 1989-2007 all rights reserved by Bitstream Inc.
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

#ifndef __T2K_T1__
#define __T2K_T1__
#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif  /* __cplusplus */

#ifndef FF_FFCONFIG_HEADER
#include "config.h"
#else
#include FF_FFCONFIG_HEADER
#endif /* FF_FFCONFIG_HEADER */

#include FF_UTIL_HEADER

#if defined(ENABLE_T1) || defined(ENABLE_CFF)
#include FF_FFT1HINT_HEADER


#define ENABLE_DECRYPT
/* #define ENABLE_ENCRYPT */

#ifdef ENABLE_DECRYPT
#define ENABLE_EITHER_CRYPT
#endif

#ifdef ENABLE_ENCRYPT
#undef ENABLE_EITHER_CRYPT
#define ENABLE_EITHER_CRYPT
#endif

#define kMaxStackValues		32
#define T1_MAX_MASTERS		16
#define T1_MAX_BLUEVALUES	14
#define T1_MAX_SNAPS		12

#ifdef ENABLE_T1_FORCE_ENCODING
typedef enum {
	FF_T1_ADOBE_STANDARD_ENCODING,
	FF_T1_ISO_LATIN1_ENCODING,
	FF_T1_MAC_ENCODING,
	FF_T1_CUSTOM_ENCODING,
	FF_T1_DEFAULT_ENCODING = 0xffff,
}FF_T1_Encoding;
#endif /* ENABLE_T1_FORCE_ENCODING */

typedef struct {
	/* private */
	tsiMemObject *mem;
	uint8 *dataInPtr;
	uint8 *decryptedData;
	int32 dataLen;
	int32 eexecGO;
	int32 charstringsGO;

	int32 x, y;
	int32 flexOn;
	int32 flexCount;

	int16	lenIV;

	uint8   *encoding;
	int16    NumCharStrings;
	uint16  *charCode; /* CharStrings big array of character codes */
	uint16  *adobeCode; /* CharStrings big array of character codes */
	uint8  **charData; /* CharStrings big array of pointers to character data */
	int16    numSubrs;
	uint8  **subrsData; /* Array of pointers to subroutines */

	int16    gNumStackValues;
	int32    gStackValues[kMaxStackValues]; /* kMaxStackValues is the max allowed */

	int32    numMasters;
	int32    numAxes;
	F16Dot16 WeightVector[T1_MAX_MASTERS]; /* 0..(numMasters-1) */

	int32    BlueValues[T1_MAX_BLUEVALUES];  /* 0 .. (numBlueValues-1) */
	int32    numBlueValues;
	int32    BlueFuzz;
	int32    BlueShift;
	F16Dot16 BlueScale;

	int32    StemSnapH[T1_MAX_SNAPS];
	int32    numStemSnapH;

	int32    StemSnapV[T1_MAX_SNAPS];
	int32    numStemSnapV;

	int32    StdHW;
	int32    StdVW;

	/* public */
	GlyphClass *glyph;

#if 0
	hmtxClass *hmtx, *noDelete_hmtx;
#endif

	int32 lsbx;
	int32 lsby;
	int32 awx;
	int32 awy;

	int32 upem;
	int32 maxPointCount;
	int32 ascent;
	int32 descent;
	int32 lineGap;
	int32 advanceWidthMax;

	F16Dot16 italicAngle;

	int32 UnderlinePosition;
	int32 UnderlineThickness;

	F16Dot16 m00, m01, m10, m11;

	uint32	isFixedPitch;
	uint16	firstCharCode, lastCharCode;

	hashClass *T1_StringsHash;

	int32 glyphExists;

#if defined (ENABLE_T1) && defined (ENABLE_T1_FORCE_ENCODING)
	FF_T1_Encoding forceEncoding;
#endif /* (ENABLE_T1) && (ENABLE_T1_FORCE_ENCODING) */

} T1Class;
#endif /* defined(ENABLE_T1)  || defined(ENABLE_CFF) */

#ifdef ENABLE_T1

#ifdef ENABLE_MAC_T1
int8* ExtractPureT1FromMacPOSTResources( tsiMemObject *mem, int16 refNum, uint32 *length );
#endif
uint8 *ExtractPureT1FromPCType1( uint8 *src, uint32 *length, int *errCode  );

uint8 *GetT1NameProperty( T1Class *t, uint16 languageID, uint16 nameID );

T1Class *tsi_NewT1Class( tsiMemObject *mem, InputStream *in, int32 dataLen );

void ParseCharString( T1Class *t, uint16 charCode );

uint16      tsi_T1GetGlyphIndex( T1Class *t, uint32 charCode );
GlyphClass *tsi_T1GetGlyphByIndex( T1Class *t, uint16 index, uint16 *aWidth, uint16 *aHeight, FFT1HintClass *ffhint, int32 PPEm );

int32 tsi_T1GetParam( T1Class *t, const uint8 *param, int32 defaultValue );
int32 tsi_T1GetBoolParam( T1Class *t, const uint8 *param, int32 defaultValue );

F16Dot16 tsi_T1GetFixedParam( T1Class *t, const uint8 *param, F16Dot16 defaultValue );

void tsi_DeleteT1Class( T1Class *t );

kernSubTable0Data *New_T1kernSubTable0Data(T1Class *tp, tsiMemObject *mem, uint8 *data, int32 dataLen );
kernSubTable *New_T1kernSubTable(T1Class *tp, tsiMemObject *mem, uint8 *in , int32 extraItemSize);
kernClass *New_T1kernClass(T1Class *tp, tsiMemObject *mem, uint8 *in, int32 extraItemSize );

void tsi_T1ListChars(void *userArg, T1Class *t, void *ctxPtr, int ListCharsFn(void *userArg, void *p, uint16 code));
uint16 FF_GetAW_T1Class( void *param1, register uint16 index );

/*
 * converts PSName to ccode for Type1 fonts
*/
uint16 tsi_T1PSName2CharCode( T1Class *t, int8 *PSName);

#ifdef ENABLE_T1_FORCE_ENCODING
/* Returns the current encoding type of FF being currently used to encode the T1 font. */
/* It can either be the one present in the font or the one that is being forced by user */
FF_T1_Encoding tsi_GetT1Encoding(T1Class *t1Font);


/* Returns 0 on Failure and 1 on success */
/* Note:: It is not recommended to force the custom encoded font to some other standard 
 * encoding because the names inside the custom fonts are not standard names */
int tsi_ForceT1Encoding(T1Class *t1Font, FF_T1_Encoding encType);
#endif /* ENABLE_T1_FORCE_ENCODING */

#endif /* ENABLE_T1 */

#if defined(ENABLE_T1) | defined(ENABLE_CFF)
uint8 *tsi_T1Find( T1Class *t, const uint8 *param, int32 start, int32 limit );
#endif

#ifdef ENABLE_CFF

#define Card8	uint8	/* 0..255 		1 byte unsigned number */
#define Card16	uint16	/* 0..65535		2 byte unsigned number */
#define OffSize	uint8	/* 1..4 		1 byte unsigned number, specifies the size of an Offset field(s) */
#define SIDCode	uint16	/* 0 - 64999	2 byte string identifier */

/* number of Standard Strings referenced by SIDs */
#define nStdStrings		391

typedef struct {
	/* private */
	tsiMemObject *mem;

	uint32  baseDataOffset;

	OffSize offSize;

	uint32 *offsetArray; /* uint32 offsetArray[ count + 1 ] */

	/* public */
	Card16  count;
} CFFIndexClass;

#define CFF_MAX_STACK 64
#define CFF_MAX_MASTERS 16



typedef struct {
	int32 Subr, SubrOffset;
	int32 defaultWidthX;
	int32 nominalWidthX;

	/* Local Subr Index */
	CFFIndexClass *lSubr;
	int32 lSubrBias;
} PrivateDictInfo;



typedef struct {
	Card16 version;
	Card16 Notice;
	Card16 FullName;
	Card16 FamilyName;
	Card16 Weight;
	Card16 Copyright;

	int32 UniqueId;
	int32 bbox_xmin, bbox_ymin, bbox_xmax, bbox_ymax;
	uint32 isFixedPitch;
	F16Dot16 italicAngle;
	int32 UnderlinePosition;
	int32 UnderlineThickness;
	int32 PaintType;
	uint8 CharstringType;
	int32 StrokeWidth;

	int32 charset;
	int32 Encoding;
	int32 Charstrings;
	int32 *XUID;
	int32 PrivateDictSize, PrivateDictOffset;

	Card16 ROSRegistry, ROSOrdering;
	int32  ROSSupplement;

	int32 CIDFontVersion;
	int32 CIDFontRevision;
	int32 CIDFontType;
	int32 CIDCount;
	int32 UIDBase;
	int32 FDArray;
	int32 FDSelect;
	Card16 FontName;

	/* Private DICT */
	PrivateDictInfo *privateDictData;

	int numAxes;
	int numMasters;
	int lenBuildCharArray;
	F16Dot16 *buildCharArray; /* the transient array */
	F16Dot16 defaultWeight[CFF_MAX_MASTERS];
	SIDCode NDV; /* SID of the Normalize Design vector subroutine */
	SIDCode CDV; /* SID of the Convert Design vector subroutine */
	/* The registry */
	F16Dot16 reg_WeightVector[CFF_MAX_MASTERS]; 			/* item 0 */
	F16Dot16 reg_NormalizedDesignVector[CFF_MAX_MASTERS];	/* item 1 */
	F16Dot16 reg_UserDesignVector[CFF_MAX_MASTERS];			/* item 2 */

	/* Font Matrix */
	F16Dot16 m00, m01, m10, m11;
	Card8 isCIDKeyed;
} TopDictInfo;


typedef struct
{
	SIDCode		IDCode;
	uint16		glyphIndex;
} cmap_t;

typedef struct {
	/* private */
	tsiMemObject *mem;

	InputStream *in;
	uint32 cffOffset;

	/* Global font data */
	int32 NumCharStrings;

	/* Encoding */
	SIDCode charCodeToSID[256];
	cmap_t	*T2_CMAPTable;
	hashClass *T2_StringsHash;
	hashClass *T2_SIDToCharCodeHash;

	int32 upem;
	int32 maxPointCount;
	int32 ascent;
	int32 descent;
	int32 lineGap;
	int32 advanceWidthMax;
	F16Dot16 italicAngle;
	int32 fontNum;

	/* Begin Type2BuildChar state */
	F16Dot16 gStackValues[ CFF_MAX_STACK ];
	int32 gNumStackValues;
	GlyphClass *glyph;
	int32 x, y, awy, awx;
	int32 lsbx, lsby;
	int numStemHints;
	int pointAdded;
	int widthDone;
	int stkClrOpCalled;

	uint16 seed;
	/* End Type2BuildChar state */

	/* Begin Header */
	Card8	major;
	Card8	minor;
	Card8	hdrSize;
	OffSize	offSize;
	/* End Header */

	/* Name Index */
	CFFIndexClass *name; /* NumFonts in this set == name->count !!! */

	/* Top DICT Index */
	CFFIndexClass *topDict;
	TopDictInfo    topDictData;

	/* String Index */
	CFFIndexClass *string; /* shared by all fonts */

	/* Global Subr Index */
	CFFIndexClass *gSubr;
	int32 gSubrBias;

	/* Encoding */

	/* Charsets */

	/* CharStrings, per font, found through the topDict */
	CFFIndexClass *CharStrings;

	/* Font DICT Index per-font (CIDFonts only) */
	CFFIndexClass *FDArrayIndex;

	/* Font Dict Array */
	TopDictInfo *FDDictData;

	/* Private DICT */
	PrivateDictInfo *privateDictData;

	/* Local Subr Index */
	CFFIndexClass *lSubr;
	int32 lSubrBias;

	/* Copyright and trandemark notices */

	/* public */
	uint32 isFixedPitch;
	uint16 firstCharCode;
	uint16 lastCharCode;

	int glyphExists;				/* keep track if default glyph or found */

} CFFClass;

CFFClass *tsi_NewCFFClass( tsiMemObject *mem, InputStream *in, int32 fontNum );
CFFClass *tsi_NewCFFClassOTF( tsiMemObject *mem, InputStream *in, int32 fontNum , uint32 cffOffest);
void tsi_DeleteCFFClass( CFFClass *t );

uint16 tsi_T2GetGlyphIndex( CFFClass *t, uint32 charCode );
GlyphClass *tsi_T2GetGlyphByIndex( CFFClass *t, uint16 index, uint16 *aWidth, uint16 *aHeight );

uint8 *GetT2NameProperty( CFFClass *t, uint16 languageID, uint16 nameID );

void tsi_T2ListChars(void *userArg, CFFClass *t, void *ctxPtr, int ListCharsFn(void *userArg, void *p, uint16 code));

uint16 FF_GetAW_CFFClass( void *param1, register uint16 index );

/*
 * converts PSName to ccode for CFF fonts
*/
uint16 tsi_T2PSName2CharCode( CFFClass *t, int8 *PSName);

#endif /* ENABLE_CFF */

#if defined(ENABLE_T1) || defined (ENABLE_BDF)
uint16 tsi_PSNameToAppleCode( register uint8 *PSName, uint16 *adobeCode, uint16 *ISOCode, uint16 *tableIdx );
#endif /* (ENABLE_T1) || ENABLE_BDF) */

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* __T2K_T1__ */

/*********************** R E V I S I O N   H I S T O R Y **********************
 *
 *     $Header: /home/archive/FontFusion/FontFusion/core/t1.h,v 1.10 2008/02/12 20:05:53 sflynn Exp $
 *                                                                           *
 *     $Log: t1.h,v $
 *     Revision 1.10  2008/02/12 20:05:53  sflynn
 *     Updated for 32-bit character code support.
 *
 *     Revision 1.9  2008/01/11 05:47:27  ljoshi
 *     Adding support for forced Type1 encoding.
 *
 *     Revision 1.8  2007/11/19 20:29:20  sflynn
 *     Modified to support CID Keyed OTF fonts.
 *
 *     Revision 1.7  2007/11/06 13:19:58  himanshu
 *     Adding support for variable include file name.
 *
 *     Revision 1.6  2007/11/05 15:11:02  sflynn
 *     Added entries for CID tokens in the Top Dictionary.
 *
 *     Revision 1.5  2006/04/28 17:49:29  sflynn
 *     no message
 *
 *     Revision 1.23  2005/10/06 19:24:37  Shawn_Flynn
 *     Added a prototype statement for tsi_PSNameToAppleCode.
 *
 *     Revision 1.22  2005/09/30 13:52:00  Shawn_Flynn
 *     Modified to correct macro definitions for EANBLE_T! and/or ENABLE_CFF.
 *
 *     Revision 1.21  2005/05/19 15:19:28  Shawn_Flynn
 *     Added prototype statement for tsi_T1Find() routine.
 *
 *     Revision 1.20  2004/06/18 13:30:52  Shawn_Flynn
 *     Added "int stkClrOpCalled" flag to the CFF_Class structure to track if
 *     stack-clearing/width-adjusting operators have been called.
 *
 *     Revision 1.19  2003/04/03 17:45:24  Shawn_Flynn
 *     Compiler warning cleanup.
 *
 *     Revision 1.18  2003/01/03 18:10:57  Shawn_Flynn
 *     dtypED
 *
 *     Revision 1.17  2001/05/01 18:29:36  reggers
 *     Added support for GlyphExists()
 *     Revision 1.16  2001/04/26 20:45:14  reggers
 *     Cleanup relative to PSName conversion. Added errCode parameter,
 *     Revision 1.15  2001/04/25 21:58:09  reggers
 *     Improvements of hash table stuff for PSName to ccode conversion.
 *     Revision 1.13  2000/06/14 21:30:36  reggers
 *     Prototype for ExtractPureT1...
 *     Revision 1.12  2000/05/19 14:40:12  mdewsnap
 *     Converted variables from short to long.
 *     Revision 1.11  2000/05/09 20:40:48  reggers
 *     Correction of #include file name: fft1hint.h
 *     Correction of prototypes of ListChars functions.
 *     Add prototypes of Ff_GetAW... functions,
 *     Revision 1.10  2000/04/19 19:00:14  mdewsnap
 *     Added in code to handle T1 hints
 *     Revision 1.9  2000/03/10 19:18:20  reggers
 *     Enhanced for enumeration of character codes in font.
 *     Revision 1.8  2000/01/06 20:53:06  reggers
 *     Corrections of data types and casts. Cleanup for configurations.
 *     Revision 1.7  1999/12/09 21:45:44  reggers
 *     End to end OTF test, changes to cffOffest use.
 *     Revision 1.6  1999/12/08 19:02:11  reggers
 *     Dismantled old cmap structures: SIDToGIndex and gIndexToSID
 *     so char mapping can handle large character sets.
 *     Added prototype of new API function for supporting OpenType CFF
 *     class. Meant to be called internally from the TrueType module.
 *     Revision 1.5  1999/11/15 20:07:23  reggers
 *     firstCharCode, lastCharCode and isFixedPitch, first pass.
 *     Revision 1.4  1999/09/30 15:12:00  jfatal
 *     Added correct Copyright notice.
 *     Revision 1.3  1999/07/01 20:43:36  mdewsnap
 *     Added prototypes for kern routines
 *     Revision 1.2  1999/05/17 15:57:48  reggers
 *     Inital Revision
 *                                                                           *
******************************************************************************/
