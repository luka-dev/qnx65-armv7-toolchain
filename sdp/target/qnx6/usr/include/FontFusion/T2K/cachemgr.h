/*
 * cachemgr.h
 * Font Fusion Copyright (c) 1989-1999 all rights reserved by Bitstream Inc.
 * http://www.bitstream.com/
 * http://www.typesolutions.com/
 * Author: Mike Dewsnap
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


#ifndef cachemgr_h
#define cachemgr_h
#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif  /* __cplusplus */


#ifdef FF_CM_DOCUMENTATION
-------------------------

Q&A Section:

Q1) What files should I look at for the Cache Manager ?
A1) There are only two files that involve the cache :: "cachemgr.c" and
"cachemgr.h".  "cachemgr.h" contains documentation, a coding example
and the actual Cache Manager API.  Source code is contained in "cachemgr.c".
-------------------------
Q2) What are the benefits to using a the Cache Manager in Font Fusion ?
A2) Using a cache could speed up the performance of your application.  If
a character exists in the cache then the Cache Manager will deliver the
bitmap to the calling application instead of Font Fusion having to create
the character each time it is needed.  The trade off is memory.  The more
memory allicated for cache purposes, the more characters can be stored in
the cache.
-------------------------
Q3) How much memory should I allocate for the cache ?
A3) The amount of memory that is given to the Cache Manager at creation time
is all it will use.  It will never allocate more memory on its own.  Keep in
mind that the amount of memory that is set at creation time will hold all the
characters in the cache as well as the cache framework itself.  Therefore the
final amount of usable memory for the cache is the total declared at creation
minus the size of the cache management structures.  The amount of memory desired
depends on the purposed uses of the application.  If large 500 line bitmaps will
be created than allocate plenty of memory for the cache manager.  If large grey
scale images are needed than again, allocate over 100K for the cache to use.
The more memory the cache is given, the more characters it can hold.  As it
runs out of space the cache will get rid of the oldest characters that is was
holding in order to make room for the newly created characters.
-------------------------
Q4) How do I use the Cache Manager ?
A4) There is not much for the application to do with the cache.  It can
create the cache, make render glyph calls through it, flush and delete.
Filter functions are attached to Font Fusion through the cache.
The function calls are::

FF_CM_New, FF_CM_Delete, FF_CM_Flush, FF_CM_RenderGlyph and
FF_CM_SetFilter.  Please see the description of each of these below.
Basically, just call the Cache Manager constructor FF_CM_New specifying
the amount of memeory to use, set a filter tag with FF_CM_SetFilter and
then create characters with FF_CM_RenderGlyph.  That is it!!
-------------------------
Q5) I noticed that T2K, the Font Manager AND the Cache Manager each have
RenderGlyph functions. What is the story?
A5) They were designed that way so they could be independent of each
other and work together.  The real RenderGlyph work is always done in
T2K Core. If you are using the Cache Manager, the FF_CM_RenderGlyph()
will first check the cache for the glyph or call another module to render
the glyph into the cache. It will use either the Font Manager RenderGlyph
function or call the T2K core. The Font Manager Render Glyph function will
look for the requested glyph from among the font fragments of the font,
and then call the T2K_RenderGlyph function.
-------------------------
Q6) It sounds like a lot of magic! How does the Cache Manager know if
the Font Manager should render a glyph? What is the configuration requirement
for me to make these work together?
A6) There is no configuration requirement! You just build the Font or
Cache Managers and use them at run time. If you "register" a font with
the Manager, when you create and select a strike, the Font Manager stamps
or marks itself in the T2K Class to let the Cache Manager know it is present.
If you are using the Cache Manager, it will respect this little stamp, which
consists of enough information for the Cache Manager to use the Font Managers API.
-------------------------
Q7) Tell me more about the setting up of a post-processing filter and why
does this involve the cache manager ?
A7) Font Fusion allows filters to be registered with the core.  Each filter
has a seperate ID.  By setting that filter ID with the cache the ID
will be stored with the created bitmap in the cache.  This is used as further
search criteria when retriving characters.  Filter functions are registered
through the cache manager to the core.  If a filter function has been set up
the core will call this function.


#endif /* FF_CM_DOCUMENTATION */


#ifdef CM_DOCUMENTATION_CODING_EXAMPLE
/* a simple example program using the Cache Manager and T2K Core! */
/* To see Cache Manager instrumentation, add this line to CONFIG.H or cachemgr.h: */
/* #define CM_DEBUG		1	*/

#include "syshead.h"
#include "t2k.h"
#include "cachemgr.h"

/*
 *  Constants
 */
#define CACHE_SIZE	20000

/*
 *  Prototypes
 */
int16 main(void);
static void PrintChar( T2K *scaler );


/*
 *  main: where it all happens, mainly!
 */
int16 main(void)
{
/* locals needed for the Cache Manager */
FF_CM_Class		*theCache;
int				 errCode;
fontCode_t		 font_code = 0;  /* only one font, always fontCode 0 */
uint8			 filterTag = 0;  /* only one filter: none */
/* locals needed for general T2K Core usage */
FILE			*fpID = NULL;
uint32			 length, count;
uint8			*data;
T2K_TRANS_MATRIX trans;
uint16			 charCode;
tsiMemObject	*mem = NULL;
InputStream		*in = NULL;
sfntClass		*font = NULL;
T2K				*scaler = NULL;
int8			*fName = "TT0003M_.TTF";
int16			 fontType = FONT_TYPE_TT_OR_T2K;
int16			 fontSize = 24;
uint8			 cmd = T2K_NAT_GRID_FIT  | T2K_SCAN_CONVERT;
uint8			 greyScaleLevel = BLACK_AND_WHITE_BITMAP;
int8			*string = "AABBCCabcdefghijklmnopqrsabcdefghijklmnopqrsabcdefghijklmnopqrs";

int				index;

	printf("\n\n\n");
	printf("**********    ******     **       **\n");
	printf("    **      **     **    **     **\n");
	printf("    **              **   **   **\n");
	printf("    **              **   ** **\n");
	printf("    **             **    ****\n");
	printf("    **            **     ** **\n");
	printf("    **          **       **   **\n");
	printf("    **        **         **     **\n");
	printf("    **      **********   **       **\n\n\n");
	printf ("Hello World, this is a simple Font Fusion Example,\n\n");
	printf ("showing use of the Cache Manager with T2K Core,\n\n");
	printf ("with just printf statements for output,\n\n");
	printf ("from www.bitstream.com !\n\n");

	// Create a new Cache Manager to play around with.
	theCache = FF_CM_New(CACHE_SIZE, &errCode);
	CLIENT_ASSERT( errCode == 0 );

		/* configure Cache filterTag for all the characters we will make */
		FF_CM_SetFilter(theCache,
						filterTag,
						NULL,
						NULL);
		/* Create the Memhandler object. */
		mem	= tsi_NewMemhandler( &errCode );
		CLIENT_ASSERT( errCode == 0 );

		/* Open the font. */
		fpID	= fopen(fName, "rb"); CLIENT_ASSERT( fpID != NULL );
		errCode	= fseek( fpID, 0L, SEEK_END ); CLIENT_ASSERT( errCode == 0 );
		length	= (uint32)ftell( fpID ); CLIENT_ASSERT( ferror(fpID) == 0 );
		errCode	= fseek( fpID, 0L, SEEK_SET ); CLIENT_ASSERT( errCode == 0 ); /* rewind */

		/* Read the font into memory. */
		data	= (uint8*)CLIENT_MALLOC( sizeof( int8 ) * length ); CLIENT_ASSERT( data != NULL );
		count	= fread( data, sizeof( int8 ), length, fpID ); CLIENT_ASSERT( ferror(fpID) == 0 && count == length );
		errCode	= fclose( fpID ); CLIENT_ASSERT( errCode == 0 );
		/* in = New_NonRamInputStream( mem, fpID, ReadFileDataFunc, length, &errCode  ); */

		/* Create the InputStream object, with data already in memory */
		in 	= New_InputStream3( mem, data, length, &errCode ); /* */
		CLIENT_ASSERT( errCode == 0 );

		/* Create an sfntClass object*/
		font = New_sfntClass( mem, fontType, in, NULL, &errCode );
		CLIENT_ASSERT( errCode == 0 );

		/* Create a T2K font scaler object.  */
		scaler = NewT2K( font->mem, font, &errCode );
		CLIENT_ASSERT( errCode == 0 );
		/* 12 point */
		trans.t00 = ONE16Dot16 * fontSize;
		trans.t01 = 0;
		trans.t10 = 0;
		trans.t11 = ONE16Dot16 * fontSize;
		/* Set the transformation */
		T2K_NewTransformation( scaler, true, 72, 72, &trans, true, &errCode );
		CLIENT_ASSERT( errCode == 0 );

		for ( index = 0; (charCode = string[index]) != 0; i++ )
		{
			/* Create a character */
			printf("\n\n***Here comes the %c ****\n\n", (int8)charCode);
			FF_CM_RenderGlyph(theCache,font_code,
							  &scaler, charCode,
							  0, 0,
							  greyScaleLevel, cmd, &errCode);
			CLIENT_ASSERT( errCode == 0 );
			/* Now draw the char */
			PrintChar( scaler );
			/* Free up memory */
			T2K_PurgeMemory( scaler, 1, &errCode );
			CLIENT_ASSERT( errCode == 0 );
		}

		/* Destroy the T2K font scaler object. */
		DeleteT2K( scaler, &errCode );
		CLIENT_ASSERT( errCode == 0 );

		/* Destroy the sfntClass object. */
		Delete_sfntClass( font, &errCode );

		/* Destroy the InputStream object. */
		Delete_InputStream( in, &errCode  );

		CLIENT_FREE( data );
		/* Destroy the Memhandler object. */
		tsi_DeleteMemhandler( mem );

	FF_CM_Delete(theCache, &errCode);

	return 0;
}

/*
 * Print/Display Character Function
 */
static void PrintChar( T2K *scaler )
{
int16 h, k, w;
int8 c;

int x, y;

	w = scaler->width;
	CLIENT_ASSERT( w <= scaler->rowBytes * 8 );
	h = scaler->height;

	/* printf("w = %d, h = %d\n", w, h ); */
	k = 0;
	for ( y = 0; y < h; y++ )
	{
		for ( x = 0; x < w; x++ )
		{
			if (scaler->rowBytes == w)
			{	/* greyscale, byte walk, divide values by 12, map to digits and clamp > '9' to '@' */
				c = (int8)((scaler->baseAddr[ k + x ] ) ?
							scaler->baseAddr[ k + x ]/12 + '0' : '.');
				if (c > '9')
					c = '@';
			}
			else	/* BLACK_AND_WHITE, fancy bit walk, off = '.' and on = '@' */
				c = (int8)((scaler->baseAddr[ k + (x>>3) ] & (0x80 >> (x&7)) ) ?
							'@' : '.');
			printf("%c", c );
		}
		printf("\n");
		k += scaler->rowBytes;
	}
}

#endif	/* CM_DOCUMENTATION_CODING_EXAMPLE */

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

#ifndef FF_FFCONFIG_HEADER
#include "config.h"
#else
#include FF_FFCONFIG_HEADER
#endif /* FF_FFCONFIG_HEADER */

#include FF_SYSHEAD_HEADER
#include FF_T2K_HEADER


/* Do not change this value!!! */
#define HASHSZ 128

/* Default value for structure alignment */
#ifndef STRUCTALIGN
#define STRUCTALIGN			4
#endif

#ifdef ENABLE_CACHE_COMPACTION
/**
 * These are the macros which can be used to enable any one of the
 * two heuristic approaches used to identify the two candidates between
 * which the compaction is done. Out of below two option, only one
 * option needs to be active at once.
 */
/* #define ENABLE_FACTOR */
#define ENABLE_RATIONAL_MIN
#endif /* ENABLE_CACHE_COMPACTION */

/* Used to align memory in the cache */
/* This must be modified if STRUCTALIGN != 4 */
#define SIZEALIGN(size) size = (size + 3) & ~0x03

typedef void *(*FF_FilterSizeFunc)(int32 width, int32 height, int32 *newWidth, int32 *newHeight);
typedef void *(*FF_FilterFunc)( );

#ifdef ENABLE_CACHE_COMPRESSION
typedef void (*FF_CM_CompressionPtr)( uint8 * inBuffer, uint32 inLength, uint8* outBuffer, int32 * outLength);
typedef FF_CM_CompressionPtr FF_CM_DecompressionPtr;
#endif

/* Number of memHandler pointers */
#ifdef CACHE_MALLOC
#ifdef ENABLE_CACHE_COMPRESSION
#define NUM_CACHE_PTRS	2
#else
#define NUM_CACHE_PTRS	0
#endif /* ENABLE_CACHE_COMPRESSION */
#else
#ifdef ENABLE_CACHE_COMPRESSION
#define NUM_CACHE_PTRS	3
#else
#define NUM_CACHE_PTRS	1
#endif /* ENABLE_CACHE_COMPRESSION */
#endif



/* Cached Bitmap specifications */

typedef struct cacheSpecs_tag
{
	int16		horizontalMetricsAreValid;
	F16Dot16	xAdvanceWidth16Dot16;
	F16Dot16	yAdvanceWidth16Dot16;
	F16Dot16	xLinearAdvanceWidth16Dot16;
	F16Dot16	yLinearAdvanceWidth16Dot16;
	F26Dot6		fTop26Dot6;
	F26Dot6		fLeft26Dot6;
	int16		verticalMetricsAreValid;
	F16Dot16	vert_xAdvanceWidth16Dot16;
	F16Dot16	vert_yAdvanceWidth16Dot16;
	F16Dot16	vert_xLinearAdvanceWidth16Dot16;
	F16Dot16	vert_yLinearAdvanceWidth16Dot16;
	F26Dot6		vert_fTop26Dot6;
	F26Dot6		vert_fLeft26Dot6;
	int32		width;
	int32		height;
	int32		rowBytes;
	int16		embeddedBitmapWasUsed;
	uint32		glyphIndex;
} cacheSpecs_t;

#define COLORBITMAP  0x1                /* 0th bit is for identifying baseAddr(low) or baseARGB(high) */

#ifdef ENABLE_CACHE_COMPRESSION
#define COMPRESSION  0x2                /* 1st bit is for identifying compression */
#endif /* ENABLE_CACHE_COMPRESSION */   /* ( low = No compression, high = compression ) */

#define NOBITMAP     0x4                /* 2nd bit for identifying T2K_SKIP_SCAN_BM
                                         * (high = No bitmaps, low = bitmaps available) */
#ifdef ENABLE_COMMON_DEFGLYPH
#define DEFGLYPHNODE 0x8                /* 3rd bit for identifying whether the node is the main node having metrics and bitmap or */
#endif /*  ENABLE_COMMON_DEFGLYPH */    /* its the secondary node having initial info */

typedef struct chardata_hdr
{
	int32				 len;
	struct chardata_hdr	*next, *prev;
	struct chardata_hdr	*lruprev, *lrunext;

#ifdef ENABLE_CACHE_COMPRESSION
	uint32				 compressBitmaplen;
#endif/*ENABLE_CACHE_COMPRESSION*/

	uint32				 maskBits;  /* Stores the control bits */

} chardata_hdr;

typedef struct memory_seg
{
	int32				 len;
	struct memory_seg	*next, *prev;
} memory_hdr;

typedef struct char_desc_tag
{
	fontCode_t fontCode;
	uint16	   charCode;
	uint32	   instCode;
} char_desc_t;

typedef struct cmGlobals_tag
{
	int32			  cacheSize;
	uint8			 *imagedata;
	chardata_hdr	 *current_char;
	chardata_hdr	**hashtable;
	memory_hdr		 *freelist;
	chardata_hdr	 *lruhead, *lrutail;
	uint8			  FilterTag;

	FF_FilterSizeFunc	SetFilterSizeFunc;
	FF_FilterFunc		SetFilterFunc;

	tsiMemObject	 *mem;

	FF_T2K_FilterFuncPtr	BitmapFilter;		/* Private reference to bitmap filter function */
	void					*filterParamsPtr;	/* Private reference to bitmap filter 2nd parameter */

#ifdef ENABLE_CACHE_COMPRESSION
	int32					 sizeOfGlobalCompressionBuffer;
	uint8					*compressedBuffer;
	int32					  compressedBufferLength;
	int32					 maxbitmapLen;
	int32					 bitmapLen;
	FF_CM_CompressionPtr	 getCompressionFunc;
	FF_CM_DecompressionPtr	 getDecompressionFunc;
#endif/*ENABLE_CACHE_COMPRESSION*/

#ifdef ENABLE_COMMON_DEFGLYPH
	char_desc_t fontinfo;
#endif/*ENABLE_COMMON_DEFGLYPH*/

	uint32 currHashSize;

} FF_CM_Class;

chardata_hdr *CmFindChar(
	FF_CM_Class		*pCmGlobals,
	char_desc_t		*req);

chardata_hdr *CmMakeChar(
	T2K		 **theScaler,
	uint32	   char_code,
	int8	   xFracPenDelta,
	int8	   yFracPenDelta,
	uint8	   greyScaleLevel,
	uint16	   cmd,
	fontCode_t font_code,
	uint32	   inst_code,
	int		  *errCode);

void *ff_cm_GetMemory(
	void	*cache,
	int32	 length);


/* Cache Manager "Public" function prototypes: */
/*
 *	Cache Manager New Class function
 *		Instantiates the Font Fusion Cache Manager.
 *		Returns the context pointer for the cache or a NULL if not successful.
 *		Possible error codes:
 *			T2K_ERR_MEM_MALLOC_FAILED
 *			T2K_ERR_NULL_MEM
 *			T2K_ERR_MEM_TOO_MANY_PTRS
 *			T2K_ERR_MEM_BAD_LOGIC
 */
#ifndef ENABLE_CLIENT_ALLOC
#define FF_CM_New( sizeofCache, errCode) FF_CM_New1( sizeofCache, HASHSZ, errCode)
#else
#define FF_CM_New( sizeofCache, errCode, allocPtr, freePtr, reallocPtr, clientArgs) FF_CM_New1( sizeofCache, HASHSZ, errCode, allocPtr, freePtr, reallocPtr, clientArgs)
#endif /* ENABLE_CLIENT_ALLOC */

#ifndef ENABLE_CLIENT_ALLOC
FF_CM_Class *FF_CM_New1(
				    int32 sizeofCache,	/* size of cache, including FF_CM_Class */
					int32 hashSize,		/* size of hashTable */
					int   *errCode);	/* to return possible errors */
#else
FF_CM_Class *FF_CM_New1(
				    int32					sizeofCache,	/* size of cache, including FF_CM_Class */
					int32					hashSize,		/* size of hashTable */
					int						*errCode,		/* to return possible errors */
					tsi_ClientAllocMethod	allocPtr, 		/* the allocation client method */
					tsi_ClientDeAllocMethod freePtr,		/* the de-allocation client method */
					tsi_ClientReAllocMethod reallocPtr,		/* the re-alloc client method */
					void					*clientArgs);	/* arguments needed by the client alloc/de-alloc/re-alloc methods */
#endif /* ENABLE_CLIENT_ALLOC */


/*
 *	Cache Manager Delete Class function
 *		Destroys the cache manager context and frees the memory used to hold the cache
 *		Currently does not return any error code
 */
void FF_CM_Delete(
			FF_CM_Class *theCache,	/* Cache class pointer returned from FF_CM_New() */
			int			*errCode);	/* to return possible errors */

/*
 *	Cache Manager Cache Flush function
 *		Reinitializes the cache, emptying its contents
 *		Possible error codes:
 *			T2K_ERR_NULL_MEM
 */
void FF_CM_Flush(
			FF_CM_Class *cache,		/* Cache class pointer returned from FF_CM_New() */
			int			*errCode);	/* to return possible errors */

/*
 *	Cache Manager Set Filter Tag Code and filter function pointers
 *		Set parameters related to filtering. These parameters will be stored and applied
 *		to new characters that are being created. The FilterTag is a component of the search
 *		criteria for finding chracters in the cache. The BitmapFilter and the parameter
 *		block are responsibility of the application. The BitmapFilter interface is specified
 *		by the T2K core and takes a void pointer to a T2K scaler, and a void pointer to
 *		some arbitrary parameter block used by the filter function itself.
 *		The filter function will be called by the core after preparing a source image
 *		which it *will not* put into the cache. The filter function will find this image
 *		in the T2K scaler, and can request cache memory for the target image just as the
 *		T2K Core code does.
 */
void FF_CM_SetFilter(
			FF_CM_Class *theCache,				/* Cache class pointer returned from FF_CM_New() */
			uint8 theFilterTag,					/* numeric tag for identifying filtering done
												   by BitmapFilter() using the filterParams block */
			FF_T2K_FilterFuncPtr BitmapFilter,	/* function pointer to T2K filter spec */
			void *filterParamsPtr);				/* Pointer to optional parameter block the BitmapFilter */

/*
 *	Cache Manager Render Glyph function
 *		Searches the cache based on the input parameters. If the character is found in the cache
 *		then the appropriate fields in the T2K scaler structure are updated.  If the character
 *		is not in the cache then the cache manager begins the sequence to have the character created
 *		and placed in the cache. The scaler is then updated. A nonzero result is returned if everything
 *		was successful.  Parameters passed into the function include the scaler that is to be updated
 *		as well as a pointer to the cache.  The fontCode and charCode refer to the desired character
 *		in a particular typeface.  The FracPenDelta fields are required by the core. They have valid
 *		values from 0 to 63 and refer to subpixel resolution.  The greyScaleLevel is another field
 *		needed by the core.  It refers to what output mode the core should operate in.
 *		If the Font Fusion Font Manager is active, the Cache Manager calls for the Font Manager
 *		to generate any characters not in the cache. Otherwise, it calls directly to the T2K Core.
 *		The cmd is used to set the desired level of hinting in the core.
 *		Possible error codes:
 *			FF_FM_ERR_FONT_CODE_ERR			( if Font Fusion Font Manager is active  )
 *			Error set by setjmp()
 */
void FF_CM_RenderGlyph(
			FF_CM_Class	 *theCache,				/* Cache class pointer returned from FF_CM_New() */
			fontCode_t	  font_code,			/* integer code identifying the font	*/
			T2K			**theScaler,			/* a T2K scaler context in which the font is current */
			uint32	      char_code, 			/* the character code to render */
			int8		  xFracPenDelta,		/* sub-pixel position in x (0...63) */
			int8		  yFracPenDelta,		/* sub-pixel position in y (0...63) */
			uint8		  greyScaleLevel,		/* BLACK_AND_WHITE_BITMAP, GREY_SCALE_BITMAP_HIGH_QUALITY ... */
			uint16		  cmd,					/* T2K_NAT_GRID_FIT, T2K_GRID_FIT, T2K_TV_MODE, T2K_SCAN_CONVERT ... */
			int			 *errCode);				/* to return possible errors */

/*
 *	Cache Manager Query Glyph function
 *		Searches the cache based on the input parameters. If the character is found in the cache
 *		then returns true.  If the character is not in the cache , returns false.
 *		Possible error codes:
 *			NONE
 */
int16 FF_CM_GlyphInCache(
			FF_CM_Class	 *theCache,
			fontCode_t	  font_code,
			T2K			**theScaler,
			uint32	      char_code,
			int8		  xFracPenDelta,
			int8		  yFracPenDelta,
			uint8		  greyScaleLevel,
			uint16		  cmd,
			int			 *errCode);

#ifdef ENABLE_CACHE_COMPRESSION
void FF_CM_SetCompDecomp( FF_CM_Class *theCache,
						  FF_CM_CompressionPtr compression,
						  FF_CM_DecompressionPtr decompression);
#endif/*ENABLE_CACHE_COMPRESSION*/

#ifdef ENABLE_CACHE_RESIZE
FF_CM_Class *FF_CM_SetCacheSize(FF_CM_Class *theOldCache, int32 newCacheSize, int32 hashSize, int *errCode);
#endif/*ENABLE_CACHE_RESIZE*/


#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* ifndef cachemgr_h */
/*********************** R E V I S I O N   H I S T O R Y **********************
 *
 *     $Header: /home/archive/FontFusion/FontFusion/cachemanager/cachemgr.h,v 1.11 2008/02/12 19:52:47 sflynn Exp $
 *                                                                           *
 *     $Log: cachemgr.h,v $
 *     Revision 1.11  2008/02/12 19:52:47  sflynn
 *     Updated for 32-bit character code support.
 *
 *     Revision 1.10  2007/11/06 13:19:58  himanshu
 *     Adding support for variable include file name.
 *
 *     Revision 1.9  2007/05/09 04:57:01  ljoshi
 *     Using macros for library functions and using only syshead.h for all library files.
 *
 *     Revision 1.8  2007/04/06 04:30:10  himanshu
 *     Fixing warnings and errors for Symbian Series 60 3rd Edition.
 *
 *     Revision 1.7  2007/01/04 22:05:38  sflynn
 *     Modified for ENABLE_CLIENT_ALLOC functionality.
 *
 *     Revision 1.6  2006/12/20 19:00:24  sflynn
 *     Modified the typedef for (*FF_CM_CompressionPtr) to correct a Mac compiler error.
 *
 *     Revision 1.5  2006/06/02 18:10:06  sflynn
 *     Modified to support configurable 16\32 bit cache tag.
 *
 *     Revision 1.4  2006/04/28 18:54:05  sflynn
 *     no message
 *
 *     Revision 1.25  2006/04/12 17:11:48  Shawn_Flynn
 *     Added support for cache memory compaction.
 *
 *     Revision 1.24  2006/04/10 18:58:14  Shawn_Flynn
 *     Modified to use the smallest required memHandler.
 *
 *     Revision 1.23  2006/04/10 15:57:28  Shawn_Flynn
 *     Modified to support metrics-only caching.
 *     Modified to support a variasble hash size.
 *
 *     Revision 1.22  2005/11/21 15:21:11  Shawn_Flynn
 *     Moved SIZEALIGN() macro from the cachemgr.c file.
 *
 *     Revision 1.21  2005/09/15 19:25:32  Shawn_Flynn
 *     Modified for new cache functionality.
 *
 *     Revision 1.20  2003/03/05 18:55:20  Shawn_Flynn
 *     Modified errCode arguments from int32* to int*.
 *
 *     Revision 1.19  2003/01/03 18:26:49  Shawn_Flynn
 *     Added element glyphIndex to cache structure for cached characters.
 *
 *     Revision 1.17  2002/01/21 14:24:04  Reggers
 *     Removed RETURN_OUTLINES from the render glyph parameter.
 *     Revision 1.16  2001/05/02 21:42:01  reggers
 *     Added new FF_CM_GlyphInCache() function.
 *     Revision 1.15  1999/10/18 16:44:24  mdewsnap
 *     Changed include files to lower case.
 *     Revision 1.14  1999/09/30 13:15:54  jfatal
 *     Added correct Copyright notice.
 *     Revision 1.13  1999/09/20 16:40:09  reggers
 *     Removed single quote items in comment blocks that bothered both
 *     compilers (cc and gcc) on Linux.
 *     Revision 1.12  1999/07/30 19:44:21  mdewsnap
 *     Remover returned error tag regarding no generated character.
 *     Revision 1.11  1999/07/23 17:51:26  sampo
 *     newline added to end of file.
 *     Revision 1.10  1999/07/19 19:40:32  sampo
 *     Error/warning cleanup
 *     Revision 1.9  1999/07/16 14:50:17  mdewsnap
 *     Added warning to the HASHSZ variable
 *     Revision 1.8  1999/07/15 13:20:46  mdewsnap
 *     Added in a Q and A section....
 *     Revision 1.7  1999/07/09 21:02:15  sampo
 *     Corrected the filter spec for FF_CM_SetfilterTag
 *     Revision 1.6  1999/07/08 21:09:30  sampo
 *     Cleanup. Moved static prototypes to cachemgr.c. Added lots
 *     of comments. Renamed FF_FM_Destroy to FF_CM_Delete.
 *     Revision 1.5  1999/07/08 16:12:24  sampo
 *     Added header and footer comment blocks.
 *     Inserted demonstration code,
 *                                                                           *
 *     AUTHOR: Mike Dewsnap                                                 *
******************************************************************************/
/* EOF cachemgr.h */
