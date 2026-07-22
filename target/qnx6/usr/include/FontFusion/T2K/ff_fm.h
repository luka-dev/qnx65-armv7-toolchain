/*
 * FF_FM.h
 * Font Fusion Copyright (c) 1989-1999 all rights reserved by Bitstream Inc.
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

#ifndef __FF_FM__
#define __FF_FM__
#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif  /* __cplusplus */

#ifdef FF_FM_DOCUMENTATION
-------------------------
Q&A Section:

Q1) What files do I need to look at ?
A1) First you need to familiarize yourself with "T2K.H"."T2K.H" contains
documentation, a coding example and the actual T2K API.
Second you need to look at "CONFIG.H". "CONFIG.H" is the only file you normally
need to edit. The file configures T2K for your platform, and it enables
or disables optional features, and it allows you to build debug or non-debug versions.
The file itself contains more information. Turn off features you do not need in order
to minimize the size of the T2K font engine. Then you need to look at this file, "FF_FM.H."
This file describes the API of the Font Fusion Font Manager. It also describes the Font Manager
Class structure, which really should be of little interest to you and you can probably
ignore totally.
-------------------------
Q2) Why should I use the Font Manager?
A2) In some ways the Font Manager hides some complexities of using the T2K engine. 
So it can make your life a bit easier. But mostly the Font Manager
allows you to have more than one outline font "registered" and ready to use
with the T2K engine. It saves you from building up your own code to handle multiple fonts.
Your application can get information about each font input stream that is
"installed," which is also convenient.
But one of the most important reasons for using the Font Manager could be that across all
font technologies, font fragments of the same font are dynamically merged by the Font Manager.
This can support dynamic downloading of font fragments of large character set CJK fonts. It can
also support adding characters to a font by adding a small fragment with the new characters. Characters
in later or newer fragments will over-ride the same characters in earlier fragments. This means
that systems where fonts are embedded in ROM can be patched by loading a new font fragment along
with the old font at run time.
-------------------------
Q3) I noticed that T2K, the Font Manager AND the Cache Manager each have RenderGlyph functions.
What is the story?
A3) They were designed that way so they could be independent of each other and work together.
The real RenderGlyph work is always done in T2K Core. If you are using the Cache Manager, the
FF_CM_RenderGlyph() will first check the cache for the glyph or call another module to render
the glyph into the cache. It will use either the Font Manager RenderGlyph function or call the
T2K core. The Font Manager Render Glyph function will look for the requested glyph from among the
font fragments of the font, and then call the T2K_RenderGlyph function.
-------------------------
Q4) It sounds like a lot of magic! How does the Cache Manager know if the Font Manager should render
a glyph? What is the configuration requirement for me to make these work together?
A4) There is no configuration requirement! You just build the Font or Cache Managers and use
them at run time. If you "register" a font with the Manager, when you create and select a strike, the
Font Manager stamps or marks itself in the T2K Class to let the Cache Manager know it is present. If you
are using the Cache Manager, it will respect this little stamp, which consists of enough information
for the Cache Manager to use the Font Managers API.
-------------------------
Q5) How many fonts can I have at once?
A5) The Font Manager was designed to handle up to 64K InputStreams, 64K physical fonts and 64K logical
fonts. InputStreams are like (and often are) font files. Within some of these streams (like TrueType
Collections and TrueDoc PFRs) there can be more than one physical font in the one stream. And logical
fonts are the possibly merged super-font made up of 1 or more physical font fragments. All of these,
streams, physicals and logicals, involve outline font resources.
"Strikes" are something different and there is a limit on the number of those which defaults to 128.
A strike is the instance of an outline resource scaled and transformed to a particular size, aspect
ratio, italic angle and etc. You can override the 128 limit by defining FF_FM_MAX_DYNAMIC_FONTS to be
whatever you prefer.
-------------------------
Q6) So I increase FF_FM_MAX_DYNAMIC_FONTS to something higher. What happens when I hit that maximum?
A6) Quite simply, you need to delete one of the strikes before you can create another.
Strikes are created with FF_FM_CreateFont() and deleted with FF_FM_DeleteFont().
-------------------------
Q7) Are there any other configuration parameters for the Font Manager?
A7) No.
-------------------------
Q8) OK, how do I use the Font Manager?
A8)	First you create the Font Manager Class. Then you configure it at runtime setting the platform ID,
specific ID, language ID, name ID (which all affect only font names you will receive in Font Properties
or in font enumeration), and the horizontal and vertical resolution. These configurations are optional,
since the Font Manager has viable usable values for North American Latin fonts and presumes a 72 dpi
square resolution.

Then you can add font streams to the Font Manager at any time. Creating InputStreams is something
covered in the T2K.H file as well as in a handy example below. After adding streams, you can call
the font enumeration function to find out what fonts are available and how many there are.

From the available fonts, you create strikes. When you create a strike, you are given a token
representing the strike which you use to select it. Once a strike is selected, you can render
characters from it.

All output is placed in the T2K Class just as if you are using the T2K Core. See "T2K.H" for how
to use the T2K Core.

With the Font Manager, the details of creating a T2K Classes and and sfnt Classes are managed
by the Font Manager, making your life simpler. You still need to create InputStreams.

There is a simple example of a main program below that shows how to do all these things.
-------------------------
Q9) Why does the FF_FM_AddTypefaceStream() function take 2 stream arguments?
A9) Some font technologies have metrics information in a second file. Adobe ships .AFM files containing
font metrics, particularly kerning information. The second stream argument should be used for
these auxiliary metrics files or streams. For other technologies or if you are not using kerning,
pass NULL for the second stream parameter.
-------------------------
Q10) Why does the FF_FM_CreateFont() have the flushCache parameter?
A10) This parameter is there to signal users of the Cache Manager that the cache should be flushed.
There is only one reason this would ever happen: when the Font Manager re-uses a font code from
a previously deleted strike, it signals the cache flush to purge glyphs that may be stranded in
the cache from the deleted font. If you are not using a Cache Manager, this parameters value
can always be ignored.
-------------------------

#endif /* FF_FM_DOCUMENTATION */

#ifdef FF_FM_DOCUMENTATION_CODING_EXAMPLE
	/* First configure T2K, please see "CONFIG.H" !!! */
	/* compile and link with
						T2K Core sources, 
						Font Manager sources
						(and optionally Cache Manager sources)
						and standard 'C' libraries
	*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "t2k.h"
#include "cachemgr.h"
#include "ff_fm.h"

#define ALL_BLACK_AND_WHITE		1			/* change to 0 for greyscale */
#define CACHE_SIZE				(32*1024)
#define USE_CACHE				0			/* change to 1 for testing use with Cache Manager */

/* Function Prototypes */
int main(int argc, char* argv[]);
static int enumFontCB(uint16 listIndex, uint8 *faceName8, uint16 *faceName16);
static void DoPrintFontProperties(T2K *aScaler);
static void print16Dot16(F16Dot16 aCode);
static void PrintChar( T2K *scaler );

/* PROGRAM CODE: */
/*
 * Main Program: Example of using the Font Fusion Font Manager (and Cache Manager)
 */
int main(int argc, char* argv[])
{
/* LOCALS: */
int errCode = 0;
FF_FM_Class *pFMGlobals;
#if USE_CACHE
FF_CM_Class *theCache;
uint8 filterTag = 0;	/* anywhere from 0...255 */
#endif
char flushCache;
uint16 fontCode, faceIndex;
T2K_TRANS_MATRIX trans;
T2K_AlgStyleDescriptor styleDesc, *stylePtr;
T2K *aScaler;
int testSize, jj;
long charCode;
#if ALL_BLACK_AND_WHITE
uint8 greyScaleLevel = BLACK_AND_WHITE_BITMAP;
uint16 cmd = T2K_NAT_GRID_FIT | T2K_GRID_FIT | T2K_SCAN_CONVERT;
#else
uint8 greyScaleLevel = GREY_SCALE_BITMAP_HIGH_QUALITY;
uint16 cmd = T2K_TV_MODE  | T2K_SCAN_CONVERT;
#endif
tsiMemObject *mem = NULL;
char *fName = "TT0003M_.TTF";
FILE *fpID;
unsigned long length, count;
unsigned char *data = NULL;
InputStream *InputStreamA = NULL, *InputStreamB = NULL;
char success = false;	/* we will set to true if we create an input stream OK */

	/* CODE BEGINS: */
	UNUSED (argc);
	UNUSED (argv);
	printf("Hello World from Font Fusion Font Manager Demo Program!\n");

	/* Create a Memhandler object. Use ONE for up to 507 (?) streams. */
	mem	= tsi_NewMemhandler( &errCode );
	assert( errCode == 0 );
	/* load a disk file into memory and make an input stream:*/
	if (mem != NULL && !errCode)
	{
		/* this is always deeply nested, eh? */
		fpID = fopen(fName, "rb");
		assert( fpID != NULL );
		if (fpID)	
		{
			errCode = fseek( fpID, 0L, SEEK_END );
			assert( errCode == 0 );
			if (!errCode)
			{
				length = (unsigned long)ftell( fpID );
				assert( ferror(fpID) == 0 );
				if ( ferror(fpID) == 0 )
				{
					errCode = fseek( fpID, 0L, SEEK_SET );  /* rewind */
					assert( errCode == 0 );
					if (!errCode)
					{
						data = (unsigned char *)CLIENT_MALLOC( sizeof( char ) * length );
						assert( data != NULL );
						if (data)
						{
							count = fread( data, sizeof( char ), length, fpID );
							assert(ferror(fpID) == 0 && count == length );
							if (ferror(fpID) == 0 && count == length )
							{
								errCode = fclose( fpID );
								assert( errCode == 0 );
								/* Please make sure you use the right New_InputStream call depending on who allocated data1,
					 				 and depending on if the font is in ROM/RAM or on the disk/server etc. */
								/* Create an InputStream object for the font data */
								InputStreamA 	= New_InputStream3( mem, data, length, &errCode );
								assert( errCode == 0 );
								success = true;
							}
							else printf("Failed fread() of file!\n");
						}
						else printf("Failed allocating data buffer size = %ld, for file!\n", length);
					}
					else printf("Failed rewinding file with fseek()!\n");
				}
				else printf("Failed getting size of file with ftell()!\n");
			}
			else printf("Failed fseek() to end of file!\n");
		}
		else printf("Failed opening file: %s with fopen()!\n", fName);
	}
	else printf("Failed getting new mem handler with tsi_NewMemhandler()!\n");
	InputStreamB = NULL;
	
	if (success)
	{
#if USE_CACHE
		/* Create a new Cache Manager to play around with. */
		theCache = FF_CM_New(CACHE_SIZE, &errCode);
		assert( errCode == 0 );
		if (theCache)
		{
#endif
			pFMGlobals = FF_FM_New(&errCode);
			if (pFMGlobals)
			{
				/* configure the way we like it: */
				FF_FM_SetPlatformID(pFMGlobals,3);
				FF_FM_SetPlatformSpecificID(pFMGlobals,1);
				FF_FM_SetLanguageID(pFMGlobals,0x0409);
				FF_FM_SetNameID(pFMGlobals,4);
				FF_FM_SetXYResolution(pFMGlobals, 72, 72);
				/* Add an input stream pack to the Font Manager */
				FF_FM_AddTypefaceStream(pFMGlobals, 
											InputStreamA,
											InputStreamB,
											&errCode);
				assert (errCode == 0);
		
				/* TESTING: FF_FM_EnumTypefaces() */
				FF_FM_EnumTypefaces (pFMGlobals, enumFontCB);
		
				/* TESTING: FF_FM_CreateFont() */
				stylePtr = NULL; /* we are not using the styleDesc variable at all */
#ifdef ALGORITHMIC_STYLES
				styleDesc.StyleFunc			= 	tsi_SHAPET_BOLD_GLYPH;
				styleDesc.StyleMetricsFunc	=	tsi_SHAPET_BOLD_METRICS;
#else
				styleDesc.StyleFunc			= 	NULL;
				styleDesc.StyleMetricsFunc	=	NULL;
#endif
				styleDesc.params[0] = 5L << 14;
		
				testSize = 24;	/* 24 lines per em */
				faceIndex = 0;
				trans.t00 = ONE16Dot16 * testSize;
				trans.t01 = 0;
				trans.t10 = 0;
				trans.t11 = ONE16Dot16 * testSize;
				fontCode = FF_FM_CreateFont(
									pFMGlobals,
									faceIndex,
									&flushCache,
									(T2K_TRANS_MATRIX *)&trans,
									stylePtr,
									&errCode);
				assert(errCode == 0);
#if USE_CACHE
				if (flushCache) /* will not happen with just one font created */
					FF_CM_Flush(theCache, &errCode);			
				assert(errCode == 0);
				filterTag = 0;
				FF_CM_SetFilter(theCache, 
									filterTag,
									NULL, 
									NULL);	/* all characters from now on will be coded with this tag */
#endif
	
				aScaler = FF_FM_SelectFont(pFMGlobals,
										fontCode,
										&errCode);
				if (aScaler && !errCode)
				{
					/* print font properties */
					T2K_SetNameString( aScaler, 0x409, 4 ); /* see if we can get a font name, too */
					DoPrintFontProperties(aScaler);

					printf("'A - Z' test\n");
					charCode = 'A';
					for (jj = 0; jj < 26; jj++, charCode++)
					{
						printf("\n***Here comes the %c ****\n", (char)charCode);
#if USE_CACHE
						FF_CM_RenderGlyph(theCache,fontCode,
									&aScaler, charCode, 
									0, 0,
									greyScaleLevel, cmd, &errCode);
#else
						FF_FM_RenderGlyph(pFMGlobals,fontCode,
									&aScaler, charCode, 
									0, 0,
									greyScaleLevel, cmd, &errCode);
#endif
						assert( errCode == 0 );
						/* Now draw the char */
						PrintChar( aScaler );
						/* Free up memory */
						T2K_PurgeMemory( aScaler, 1, &errCode );
						assert( errCode == 0 );
#if USE_CACHE
						/* render same char, expect to get from cache: */
						printf("\n***Here comes the %c ****\n", (char)charCode);
						FF_CM_RenderGlyph(theCache,fontCode,
									&aScaler, charCode, 
									0, 0,
									greyScaleLevel, cmd, &errCode);
						assert( errCode == 0 );
						/* Now draw the char */
						PrintChar( aScaler );
						/* Free up memory */
						T2K_PurgeMemory( aScaler, 1,
											&errCode );
						assert( errCode == 0 );
#endif
					}
				}
	
				FF_FM_Delete(pFMGlobals, &errCode);
				assert (errCode == 0);
			}
			else printf("Unable to initialize the Font Manager, errCode = %d!\n", errCode);
#if USE_CACHE
			FF_CM_Delete(theCache, &errCode);
			assert (errCode == 0);
		}
		else printf("Unable to initialize the Cache Manager, errCode = %d!\n", errCode);
#endif
	} /* if success */
	else
		errCode = 1;	/* InputStream initialization failed */

	/* clean up */
	if (InputStreamA)
	{
		Delete_InputStream( InputStreamA, &errCode  );
		assert (errCode == 0);
	}

	if (data)
		CLIENT_FREE(data);

	if (mem)	/* Destroy the Memhandler object. */
		tsi_DeleteMemhandler( mem );
			
	return errCode;
}

/*
 * Enumerate Fonts Callback Function
 */
static int enumFontCB(uint16 listIndex, uint8 *faceName8, uint16 *faceName16)
{
	int retCode = 0;
	printf("Logical font index %d ", (int)listIndex);
	if (faceName8)
		printf("	%s\n", faceName8);
	else if (faceName16)
	{
		char s[64];
		int ii = 0;
		while (faceName16[ii])
			s[ii] = (char)(faceName16[ii++]); /* dumb: truncate 16 bit chars to 8 bit chars */
		s[ii] = 0;
		printf("	%s\n", s);
	}
	else
		printf("\n");
	return retCode;
}

/*
 * Print/Display Character Function
 */
static void PrintChar( T2K *scaler )
{
int y, x, k, w, h;
char c;
	w = scaler->width;
	assert( w <= scaler->rowBytes * 8 );
	h = scaler->height;
	
	/* printf("w = %d, h = %d\n", w, h ); */
	k = 0;
	for ( y = 0; y < h; y++ )
	{
		for ( x = 0; x < w; x++ )
		{
			if (scaler->rowBytes == w)
			{		/* greyscale, byte walk, divide values by 12, map to digits and clamp > 9 to '@' */
				c = 
					(char)((scaler->baseAddr[ k + x ] ) ?
							scaler->baseAddr[ k + x ]/12 + '0' : '.');
				if (c > '9')
					c = '@';
			}
			else	/* BLACK_AND_WHITE, fancy bit walk, off = '.' and on = '@' */
				c = 
					(char)((scaler->baseAddr[ k + (x>>3) ] & (0x80 >> (x&7)) ) ?
							'@' : '.');
			printf("%c", c );
		}
		printf("\n");
		k += scaler->rowBytes;
	}
	if (scaler->embeddedBitmapWasUsed)
		printf("Bitmap was embedded BITMAP!\n");
	else
		printf("Bitmap generated from OUTLINE.\n");
}

/* utility functions */

/*
 * Print 16.16 Function
 */
static void print16Dot16(F16Dot16 aCode)
{
int hiWord, loWord;
	hiWord = (aCode & 0xffff0000) >> 16;
	loWord = aCode & 0x0000ffff;
	printf("0x%x.", hiWord);
	printf("%4x\n", loWord);
}

/*
 * Print Font Properties Function
 */
static void DoPrintFontProperties(T2K *aScaler)
{
char s[64];
int ii;
	printf("Font Properties:\n");
	if (aScaler->nameString8)
		printf("Font name: %s\n", aScaler->nameString8);
	if (aScaler->nameString16)
		{
		for (ii = 0; aScaler->nameString16[ii]; ii++)
			s[ii] = (char)aScaler->nameString16[ii];
		s[ii] = 0;
		printf("Font name: %s\n", s);
		}
	printf("# logical fonts inside: %d\n", (int)aScaler->numberOfLogicalFonts);
	if (aScaler->horizontalFontMetricsAreValid)
	{
		/*** Begin font wide HORIZONTAL Metrics data */
		printf("xAscender = ");
		print16Dot16(aScaler->xAscender);
		printf("yAscender = ");
		print16Dot16(aScaler->yAscender);

		printf("xDescender = ");
		print16Dot16(aScaler->xDescender);
		printf("yDescender = ");
		print16Dot16(aScaler->yDescender);

		printf("xLineGap = ");
		print16Dot16(aScaler->xLineGap);
		printf("yLineGap = ");
		print16Dot16(aScaler->yLineGap);

		printf("xMaxLinearAdvanceWidth = ");
		print16Dot16(aScaler->xMaxLinearAdvanceWidth);
		printf("yMaxLinearAdvanceWidth = ");
		print16Dot16(aScaler->yMaxLinearAdvanceWidth);

		printf("caretDx = ");
		print16Dot16(aScaler->caretDx);
		printf("caretDy = ");
		print16Dot16(aScaler->caretDy);
	
		printf("xUnderlinePosition = ");
		print16Dot16(aScaler->xUnderlinePosition);
		printf("yUnderlinePosition = ");
		print16Dot16(aScaler->yUnderlinePosition);

		printf("xUnderlineThickness = ");
		print16Dot16(aScaler->xUnderlineThickness);
		printf("yUnderlineThickness = ");
		print16Dot16(aScaler->yUnderlineThickness);
		/*** End font wide HORIZONTAL Metrics data */
	}

	if (aScaler->verticalFontMetricsAreValid)
	{
		/*** Begin font wide VERTICAL Metrics data */
		printf("vert_xAscender = ");
		print16Dot16(aScaler->vert_xAscender);
		printf("vert_yAscender = ");
		print16Dot16(aScaler->vert_yAscender);

		printf("vert_xDescender = ");
		print16Dot16(aScaler->vert_xDescender);
		printf("vert_yDescender = ");
		print16Dot16(aScaler->vert_yDescender);

		printf("vert_xLineGap = ");
		print16Dot16(aScaler->vert_xLineGap);
		printf("vert_yLineGap = ");
		print16Dot16(aScaler->vert_yLineGap);

		printf("vert_xMaxLinearAdvanceWidth = ");
		print16Dot16(aScaler->vert_xMaxLinearAdvanceWidth);
		printf("vert_yMaxLinearAdvanceWidth = ");
		print16Dot16(aScaler->vert_yMaxLinearAdvanceWidth);

		printf("vert_caretDx = ");
		print16Dot16(aScaler->vert_caretDx);
		printf("vert_caretDy = ");
		print16Dot16(aScaler->vert_caretDy);
	
	}
}


#endif /* FF_FM_DOCUMENTATION_CODING_EXAMPLE */

/************************************************************/
/************************************************************/
/************************************************************/
/************************************************************/
/************************************************************/
/************************************************************/
/***** HERE THE ACTUAL NON-DOCUMENTATION CONTENTS BEGIN *****/
/************************************************************/
/************************************************************/
/************************************************************/
/************************************************************/
/************************************************************/


#ifndef FF_FM_MAX_DYNAMIC_FONTS
#define FF_FM_MAX_DYNAMIC_FONTS 128	/* 0xfffe is the max it can be */
#endif

/* Font Fusion Font Manager error codes: */
#define FF_FM_ERR_BAD_INDEX				20000
#define FF_FM_ERR_BAD_FONTCODE			20001
#define FF_FM_ERR_CREATE_FONT_OFLO_ERR	20002
#define FF_FM_ERR_FONT_CODE_ERR			20003
#define FF_FM_ERR_UNKNOWN_FONT_TYPE		20004

typedef struct
{
	uint16					logFontIndex;	/* index of logical font */
	uint16					fontCode;		/* unique integer for strike */
	T2K_TRANS_MATRIX		transM;			/* transform of strike */
	T2K_AlgStyleDescriptor	styleDesc;		/* style of strike */
	int16					nSubScalers;	/* # of scalers created for multi-font merge */
	T2K						**subScalers;	/* array of scalers for multi-font merge */
	sfntClass				**subFonts;		/* array of T2K fonts for multi-font merge */
	tsiMemObject			**subMems;		/* array of mem objects for multi-font merge */
} NewFontEntry;

typedef struct
{
	int16			fontType;		/* type technology code */
	InputStream		*InputStreamA;	/* font stream */
	InputStream		*InputStreamB;	/* optional metrics stream */
} InputStreamPack;

typedef struct
{
	uint16	StreamIndex;		/* which input stream pack */
	uint16	SubIndex;			/* which logical font in that stream (for TTC or PFR) */
	int8	SubFontName8[64];	/* 8 bit font name, asciiz string */
	uint16	SubFontName16[64];	/* 16 bit font name, 0x0000 terminus */
} PhysicalFontEntry;

typedef struct
{
	int16	nFragments;		/* # of font fragment for multi-font merge */
	uint16	*fragmentList;	/* list of physical font indices comprising multi-font merge */
} LogicalFontEntry;

typedef struct
{
	uint16				nStreams;								/* # of installed input stream packs */
	InputStreamPack		*inputStreamList;						/* array of installed input stream packs */
	uint16				nPhysicalFonts;							/* # of physical fonts in physicalFontList[] */
	PhysicalFontEntry	*physicalFontList;						/* array of physical fonts */
	uint16				nLogicalFonts;							/* # of logical fonts in logicalFontList[] */
	LogicalFontEntry	*logicalFontList;						/* array of logical fonts */
	uint16				nextNewFontKey;							/* hash key for generating fontCodes */
	uint16				nNewFonts;								/* # of strikes created */
	NewFontEntry		newFontList[FF_FM_MAX_DYNAMIC_FONTS];	/* array of strikes */
	uint16				curFontCode;							/* fontCode current strike */
	T2K					*theFMScaler;							/* convenience pointer to subScalers */
	sfntClass			*theFMFont;								/* convenience pointer to subFonts */
	uint16				platformID;								/* TrueType, T2K platform ID */
	uint16				platformSpecificID;						/* TrueType, T2K specific ID */
	uint16				languageID;								/* TrueType, T2K language ID for font name */
	uint16				nameID;									/* TrueType, T2K font name type (use 4) */
	int32				xRes;									/* horiz resolution in dpi */
	int32				yRes;									/* vert resolution in dpi */
	/* mem object */
	tsiMemObject		*mem;									/* Font Managers mem handler object */
} FF_FM_Class;


/* ------------------------- "public" functions: ------------------------- */
/*
 *	Font Manager New Class Function
 *		Instantiates the Font Fusion Font Manager.
 *		Returns a context pointer which is NULL on failure. The errCode parameter will also be clear on success.
 *
 *		Possible error codes:
 *			T2K_ERR_MEM_MALLOC_FAILED
 */
FF_FM_Class *FF_FM_New(int *errCode);

/*
 *	Font Manager Enumerate Typefaces Function
 *		Enumerates the available logical fonts found among the outline font resources.
 *		At least two of the supported type technologies allow multiple logical fonts in
 *		each outline resource. Once outline resources are installed, this is how the
 *		application environment determines what logical fonts are available.
 *		Returns whatever the enumTypefaceCallBack() function returns the last
 *		time FF_FM_EnumTypefaces() calls it.
 *
 *		The enumTypefaceCallBack() function will be called once for each logical font
 *		in the internal list order of the Font Fusion Font Manager, or until
 *		the enumTypefaceCallBack() function returns a non-zero value.
 */
void FF_FM_EnumTypefaces(FF_FM_Class * pFM,								/* class pointer from FF_FM_New() */
						 int16 enumTypefaceCallBack(					/* your callback to acquire enumeration */
													uint16 listIndex,	/* internal logical font index of typeface */	
													uint8 *faceName8,	/* 8 bit asciiz name string, may be NULL */
													uint16 *faceName16	/* 16 bit 0x0000 terminated name string, may be NULL */
													)
						);

/*
 *	Font Manager Add Typeface Stream Function
 *		Installs an outline font resource stream(s) to the Font Fusion Font Manager context.
 *		The errCode parameter returns 0 on success or an error code.
 *		Most typefaces consist of a single stream. Pass NULL for InputStreamB
 *		unless a second stream is needed for Adobe Postscript font metrics stream.
 *
 *		Possible error codes:
 *			T2K_ERR_MEM_MALLOC_FAILED
 *			T2K_ERR_MEM_REALLOC_FAILED
 *			T2K_ERR_BAD_T2K_STAMP
 *			T2K_ERR_NULL_MEM
 *			T2K_ERR_MEM_BAD_PTR
 */
void FF_FM_AddTypefaceStream(FF_FM_Class *p,				/* class pointer from FF_FM_New() */
							 InputStream *InputStreamA,		/* font resource stream (outline resource) */
							 InputStream *InputStreamB,		/* possible Adobe PostScript metrics stream */
							 int *errCode);					/* to return possible error code */


/*
 *	Font Manager Create Font Function
 *		Creates a font instance (outline resource plus transformation) and
 *		returns a font code for the application environment to use to select a font
 *		using FF_FM_SelectFont(). Does not select the font. The font code is valid
 *		if the errCode parameter is not set. Also sets flushCache to TRUE if the font
 *		creation causes a need for the cache to be flushed. In this event, existing valid tokens of
 *		previously created fonts will remain valid; the cache flush is rarely needed
 *		to clean out stranded glyphs from fonts that the application has already deleted.
 *
 *		Possible error returns (in errCode):
 *			T2K_ERR_MEM_MALLOC_FAILED
 *			T2K_ERR_MEM_REALLOC_FAILED
 *			T2K_ERR_MEM_INVALID_PTR
 *			T2K_ERR_TRANS_IS_NULL
 *			T2K_ERR_RES_IS_NOT_POS)
 *			FF_FM_ERR_UNKNOWN_FONT_TYPE
 */
uint16 FF_FM_CreateFont(FF_FM_Class *pFM,					/* class pointer from FF_FM_New() */
						uint16 index,						/* logical font index from which to create the strike */
						int8 *flushCache,					/* returns true if cache should be flushed (if previously used fontCode is generated) */
						T2K_TRANS_MATRIX *trans,			/* transformation matrix for the strike */
						T2K_AlgStyleDescriptor *styling,	/* styling for the strike, e.g.: bold */
						int *errCode);						/* to return possible error code */

/*
 *	Font Manager Select Font Function
 *		Selects a previously created font instance.
 *		The errCode parameter is
 *		set on failure indicating the T2K scaler returned is invalid.
 *		The selected font is now active in the T2K scaler and ready for glyphs to be rendered.
 *
 *		Possible error code returns (in errCode):
 *			T2K_ERR_MEM_IS_NULL
 *			FF_FM_ERR_BAD_FONTCODE
 *			FF_FM_ERR_CREATE_FONT_OFLO_ERR
 */
T2K *FF_FM_SelectFont(FF_FM_Class *pFM,		/* class pointer from FF_FM_New() */
					  uint16 fontCode,		/* font code returned from FF_FM_CreateFont() */
					  int *errCode);		/* to return possible error code */

/*
 *	Font Manager Delete Font Function
 *		Deletes a previously created font instance.
 *		The font instance represented by fontCode becomes invalid and images
 *		from it may be stranded in the cache, requiring a cache flush.
 *		Returns nothing. Sets errCode to 0 on success or:
 *			FF_FM_ERR_FONT_CODE_ERR
 *			T2K_ERR_MEM_MALLOC_FAILED
 *			T2K_ERR_BAD_T2K_STAMP
 *			T2K_ERR_NULL_MEM
 *			T2K_ERR_MEM_BAD_PTR
 *
 */
void FF_FM_DeleteFont(FF_FM_Class *pFM,		/* class pointer from FF_FM_New() */
					  uint16 fontCode,		/* font code returned from FF_FM_CreateFont() */
					  int *errCode);		/* to return possible error code */

/*
 *	Font Manager Render Glyph Function
 *		Renders a glyph from a font instance active in the T2K scaler parameter.
 *		Uses the fontCode parameter to reference internal FF_FM data structures
 *		to walk through "merged" font fragments until the glyph is successfully
 *		rendered or the fragment list is depleted. May alter what pScaler points
 *		to as it is trying to generate the glyph if more than one font fragment
 *		makes up a merged font. 
 *
 *		Possible error codes:
 *			FF_FM_ERR_FONT_CODE_ERR
 *			Error set by setjmp()
 */
void FF_FM_RenderGlyph( FF_FM_Class *pFM,			/* class pointer from FF_FM_New() */
						fontCode_t fontCode,		/* font code returned from FF_FM_CreateFont() */
						T2K **pScaler,				/* address of scaler pointer returned by FF_FM_SelectFont() */
						uint32 code,					/* character code or index to render */
						int8 xFracPenDelta,			/* horizontal sub pixel position (0..63) */
						int8 yFracPenDelta,			/* vertical sub pixel position (0..63) */
						uint8 greyScaleLevel,		/* BLACK_AND_WHITE_BITMAP, GREY_SCALE_BITMAP_HIGH_QUALITY ...  */
						uint16 cmd,					/* T2K_NAT_GRID_FIT, T2K_GRID_FIT, T2K_TV_MODE, T2K_SCAN_CONVERT ... */  
						int *errCode );				/* to return possible error code */


/*
 *	Font Manager Delete Class Function
 *		Deletes the Font Fusion Font Manager context and cleans up.
 *		Can return an error code from Delete_sfntClass() while
 *		"bringing down" the current internal scalers and fonts
 *		Possible error codes:
 *			T2K_ERR_BAD_T2K_STAMP
 *			T2K_ERR_NULL_MEM
 *			T2K_ERR_MEM_BAD_PTR
 */
void FF_FM_Delete(FF_FM_Class *pFM,		/* class pointer from FF_FM_New() */
				  int *errCode);		/* to return possible error code */


/* ------------------------- "public" macros: ------------------------- */
/*
 *	Font Manager Set Platform ID
 *		Sets the platform ID for accessing 'cmap' tables in TrueType and T2K fonts.
 *		The default platform ID is 3 (Microsoft); call this function to change to
 *		another platform ID for font character maps.
 *
 *		In the Font Fusion Font Manager, this will impact the settings stored in
 *		the T2K scaler created in FF_FM_SelectFont().
 *
 *		For other font technologies, this setting is ignored.
 */
#define FF_FM_SetPlatformID(p,v)	(p->platformID=v)

/*
 *	Font Manager Set Specific ID
 *		Sets the platform specific ID for accessing 'cmap' tables in
 *		TrueType and T2K fonts. The default platform specific ID is 1 (Unicode).
 *		Call this "function" to change to another platform specific ID for font character maps.
 *
 *		In the Font Fusion Font Manager, this will impact the settings stored in
 *		the T2K scaler created in FF_FM_SelectFont().
 *
 *		For other font technologies, this setting is ignored.
 */
#define FF_FM_SetPlatformSpecificID(p,v)	(p->platformSpecificID=v)

/*
 *	Font Manager Set Language ID
 *		Sets the language ID for accessing name tables in TrueType and T2K fonts.
 *		The default language ID is 0x0409 (Microsoft, American English).
 *		Call this function to change to another language ID for font name strings.
 *
 *		In the Font Fusion Font Manager, this will impact the names strings returned
 *		in the enumTypefaceCallBack of the FF_FM_EnumTypefaces() API function.
 *		Call this function as needed before FF_FM_AddTypefaceStream().
 *
 *		For other font technologies, this setting is ignored.
 */
#define FF_FM_SetLanguageID(p,v)	(p->languageID=v)

/*
 *	Font Manager Set Name ID
 *		Set the name ID for accessing name tables in Truetype and T2K fonts.
 *		The default name ID is 4 (full font name). Call this function to change
 *		to another name ID for font name strings.
 *
 *		In the Font Fusion Font Manager, this will impact the names strings returned
 *		in the enumTypefaceCallBack of the FF_FM_EnumTypefaces() API function.
 *		Call this "function" as needed before FF_FM_AddTypefaceStream().
 *
 *		For other font technologies, this setting is ignored.
 */
#define FF_FM_SetNameID(p,v)	(p->nameID=v)

/*
 *	Font Manager Set X and Y resolution
 *		Set the x and y resolutions in dot per inch.
 *		The Font Manager will use this resolution setting whenever
 *		FF_FM_SelectFont() is called.
 *		The default settings are xRes = 72 and yRes = 72
 */
#define FF_FM_SetXYResolution(p, x, y)	{p->xRes=x;p->yRes=y;}

#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif /*  __FF_FM__ */



/*********************** R E V I S I O N   H I S T O R Y **********************
 *  
 *     $Header: /home/archive/FontFusion/FontFusion/fontmanager/ff_fm.h,v 1.3 2008/02/12 20:26:01 sflynn Exp $
 *                                                                           *
 *     $Log: ff_fm.h,v $
 *     Revision 1.3  2008/02/12 20:26:01  sflynn
 *     Updated for 32-bit character code support.
 *
 *     Revision 1.2  2006/06/02 18:12:27  sflynn
 *     Modified to support configurable 16\32 bit cache tag.
 *
 *     Revision 1.1  2006/04/27 17:52:23  sflynn
 *     no message
 *
 *     Revision 1.15  2003/03/05 18:56:14  Shawn_Flynn
 *     Modified errCode arguments from int32* to int*.
 *     
 *     Revision 1.14  2003/01/03 18:28:34  Shawn_Flynn
 *     dtypED
 *     
 *     Revision 1.13  2000/05/31 15:27:41  reggers
 *     Removed unintentional trigraph in a comment
 *     Revision 1.12  1999/10/18 17:26:27  mdewsnap
 *     Changed include files to lower case
 *     Revision 1.11  1999/09/30 13:21:35  jfatal
 *     Added correct Copyright notice.
 *     Revision 1.10  1999/09/20 16:39:55  reggers
 *     Removed single quote items in comment blocks that bothered both
 *     compilers (cc and gcc) on Linux.
 *     Revision 1.9  1999/07/22 20:44:07  sampo
 *     Corrected PrintFontProperties 16 bit string error in commented code.
 *     Revision 1.8  1999/07/19 18:22:19  sampo
 *     Insignificant change
 *     Revision 1.7  1999/07/15 14:35:16  sampo
 *     Corrected simple spelling error in Q & A.
 *     Revision 1.6  1999/07/14 22:07:59  sampo
 *     Added Font Manager Q & A section.
 *     Revision 1.5  1999/07/08 21:08:18  sampo
 *     In comment section of sample code, changed FF_CM_Destroy
 *     to FF-CM_Delete,
 *     Revision 1.4  1999/07/08 18:47:45  sampo
 *     Corrected comments. Added new error codes.
 *     Added new macro, Ff_FM_SetXYResolution()
 *     Revision 1.3  1999/07/08 16:16:58  sampo
 *     Increased length of SubFontName<8 and 16> in PhysicalFontEntry
 *     type from 32 to 64.
 *     Inserted demonstration code block.
 *     Revision 1.2  1999/06/10 20:15:00  sampo
 *     Added subMems array
 *     Revision 1.1  1999/05/27 22:02:58  sampo
 *     Initial revision
 *                                                                           *
******************************************************************************/

/* EOF FF_FM.h */
