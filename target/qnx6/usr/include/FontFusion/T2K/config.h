/*
	$Header: /home/archive/FontFusion/FontFusion/core/config.h,v 1.36 2009/07/03 09:23:30 rpasricha Exp $

 * Config.h
 * Font Fusion Copyright (c) 1989-2005 all rights reserved by Bitstream Inc.
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

/***********************************************/
#ifndef __T2K_CONFIG__
#define __T2K_CONFIG__

#ifdef UNUSED
#undef UNUSED
#endif
#define UNUSED(x) ((void)(x))

#ifndef FF_FFINCLUDE_HEADER
/* Include Path File */
#include "ffinclude.h"
#else
#include FF_FFINCLUDE_HEADER
#endif /* FF_FFINCLUDE_HEADER */


/* User specific include file */
#include FF_USER_HEADER


/**********************************************************************/
/**********************************************************************/
/**********************************************************************/

/**** **** **** BEGIN configuration defines **** **** ****/
/* The T2K client has to define the meaning of the following functions in case the
 * default definitions are not available or needs to be changed for the target platform */
/*** #1 ***/
#ifndef CLIENT_MALLOC
#define CLIENT_MALLOC( size )				malloc( size )
/*#define CLIENT_MALLOC( size )				AllocateTaggedMemoryNilAllowed(n,"t2k")*/
#endif
/*** #2 ***/
#ifndef CLIENT_FREE
#define CLIENT_FREE( ptr )					free( ptr )
/*#define CLIENT_FREE( ptr )				FreeTaggedMemory(p,"t2k")*/
#endif
/*** #3 ***/
#ifndef CLIENT_REALLOC
#define CLIENT_REALLOC( ptr, newSize )		realloc( ptr, newSize )
/*#define CLIENT_REALLOC( ptr, newSize )	ReallocateTaggedMemoryNilAllowed(ptr, size, "t2k")*/
#endif

/*** #4 ***/
#ifndef CLIENT_MEMSET
#define CLIENT_MEMSET( pd, c, s )			memset( pd, c, s )
#endif /* CLIENT_MEMSET */

/*** #5 ***/
#ifndef CLIENT_MEMCPY
#define CLIENT_MEMCPY( pd, ps, s)			memcpy( pd, ps, s )
#endif /* CLIENT_MEMCPY */

/*** #6 ***/
#ifndef CLIENT_STRLEN
#define CLIENT_STRLEN( str )				strlen( str )
#endif /* CLIENT_STRLEN */

/*** #7 ***/
#ifndef CLIENT_STRCPY
#define CLIENT_STRCPY( str1, str2 )			strcpy( str1, str2 )
#endif /* CLIENT_STRCPY */

/*** #8 ***/
#ifndef CLIENT_STRCMP
#define CLIENT_STRCMP( str1, str2 )			strcmp( str1, str2 )
#endif /* CLIENT_STRCMP */

/*** #9 ***/
#ifndef CLIENT_STRNCMP
#define CLIENT_STRNCMP( str1, str2, len )	strncmp( str1, str2, len )
#endif /* CLIENT_STRNCMP */

/*** #10 ***/
#ifndef CLIENT_ASSERT
#define CLIENT_ASSERT( x )					assert( x )
#endif /* CLIENT_ASSERT */

/*** #11 ***/

#if defined(__QNXNTO__) 
#define	CLIENT_JMPBUF					sigjmp_buf
#define	CLIENT_SETJMP( env )			sigsetjmp( env, 0 )
#define	CLIENT_LONGJMP( env, rval )		siglongjmp( env, rval )
#endif

#if !defined(CLIENT_SETJMP) || !defined(CLIENT_LONGJMP)
/* While defining own version of CLIENT_SETJMP, please make sure that the
 * function return 0 for successful completion. */
#define CLIENT_SETJMP( _env )			setjmp( _env)
#define CLIENT_LONGJMP( _env, _val )	longjmp( _env, _val )
/* While defining own version of CLIENT_SETJMP/CLIENT_LONGJMP please also
 * define CLIENT_JMPBUF, the size of this data type depends on the platform.
 * It should hold enough space to store the current state of stack on that platform. */
#define CLIENT_JMPBUF					jmp_buf
#endif /* !CLIENT_SETJMP || !CLIENT_LONGJMP */

/* The T2K client has to define the meaning of these 2 functions */
/* if there is a need for CACHE specific memory access (different than CLIENT) */

/*#define CACHE_MALLOC( size )				malloc( size )*/
/*#define CACHE_FREE( ptr )					free( ptr )*/

/*** #12 ***/
/* Here the client can optionally redefine assert, by adding two lines according to the below example */
/* #undef assert  (line1) */
/* Just leave it for some clients, OR */
/* #define assert(cond) 					CLIENT_ASSERT( cond ) */
/* OR for a _FINAL_ build _ALWAYS_ define as NULL for maximum speed */
/* #define assert(cond) 					NULL*/


/*** Start of optional features ***/
/* The optional features increase ROM/RAM needs, so only enable them if you are using them */

/*** #13 ***/
/* This enables the following T2K functions/methods:
 * T2K_MeasureTextInX()
 * T2K_GetIdealLineWidth()
 * T2K_LayoutString()
 */
#define									ENABLE_LINE_LAYOUT

/*** #14 ***/
/* Enables kerning support for all technologies */
#define									ENABLE_KERNING

/*** #15 ***/
/* We consume 8 * somesize bytes for the cache */
/* #define									LAYOUT_CACHE_SIZE somesize */
/*
 * This just speeds up T2K_MeasureTextInX()
 * It only makes sense to enable if ENABLE_LINE_LAYOUT and ENABLE_KERNING is enabled
 * and you are using T2K_MeasureTextInX().
 */
#define									LAYOUT_CACHE_SIZE	149

/*** #16 ***/
/* See more info in T2K.H */
#define									ALGORITHMIC_STYLES

/*** #17 ***/
/* Always enable if you need Type 1 font support */
#define									ENABLE_T1

/*** #18 ***/
/* If you have enabled Type 1 support and also need Mac specific Type 1 then also enable this ***/
/*#define									ENABLE_MAC_T1*/

/*** #19 ***/
/* Enable if you need CFF font support */
/* or if you need CFF/OTF support      */
#define									ENABLE_CFF

/*** #20 ***/
/* Always enable if you need to be able to read entropy encoded T2K fonts (for compact Kanji fonts) */
/*#define									ENABLE_ORION*/

/*** #21 ***/
/* Enable if you need non RAM/ROM resident fonts. Allows you to leave the fonts on the disk/server etc. */
#define									ENABLE_NON_RAM_STREAM

/* 3 Scan-converter bitmap compile time configuration options (14,15, and 16): */

/*** #22 ***/
/* Enable if you want to use a non-zero winding rule in the scan-converter instead of even-odd fill */
/* The strongly recommended setting is to leave it ON (defined)*/
/* See info in T2K.H */
#ifndef	USE_NON_ZERO_WINDING_RULE
#define	USE_NON_ZERO_WINDING_RULE
#else
#if USE_NON_ZERO_WINDING_RULE == 0
#undef	USE_NON_ZERO_WINDING_RULE
#endif
#endif

/*** #23 ***/
/* If defined the scan-converter rowbytes will be a 4 byte multiple, otherwise it is just byte aligned */
/* The normal setting is to leave it OFF (not defined) */
/* Defining it consumes more memory for each bitmap */
/*#define									MAKE_SC_ROWBYTES_A_4BYTE_MULTIPLE*/

/*** #24 ***/
/* The normal setting is to leave it OFF (not defined) */
/* When defined the y-axis goes up and not down as is normal in graphics system with a top left 0,0 origin */
/*#define									REVERSE_SC_Y_ORDER*/

/*** #25 ***/
/* Only enable if you need embedded bitmap font support */
#define									ENABLE_SBIT

/*** #26 Only enable if you need native TT hint support format */
#ifndef	ENABLE_NATIVE_TT_HINTS
#define	ENABLE_NATIVE_TT_HINTS
#else
#if ENABLE_NATIVE_TT_HINTS == 0 
#undef	ENABLE_NATIVE_TT_HINTS
#endif
#endif

/*** #27 ***/
/* Only enable if you want run time auto-hinting/gridding ability */
/* If you only need for instace TV_MODE then you do not need to enable this */
/*#define									ENABLE_AUTO_GRIDDING*/

/*** #28 ***/
/* Only enable if you need Font Fusion stroke font support */
#define									ENABLE_T2KS

/*** #29 ***/
/* Only enable if you intend to use the T2K_LCD_MODE_2 or T2K_TV_MODE_2 mode */
/*#define									ENABLE_AUTO_GRIDDING_CORE*/

/*** #30 ***/
/* Only enable if you need Webfont/TrueDoc PFR font support */
#define									ENABLE_PFR

/*** #31 ***/
/* Define IF
 * *ptr16Bit++ = (uint16)data16;
 * is slower than
 * *ptr8Bit++ = (uint8)data1; *ptr8Bit++ = (uint8)data2;
 *
 * This should be define on for instance the MIPS CPU
 * where word writes are Really BAD. Basically, it can only write bytes or longs
 * so word writes compile into consecutive byte writes, PLUS the shifting and masking
 * to make them work!
*/
#if ((TARGET == __MIPSLE__) || (TARGET == __MIPSBE__))
#define									MY_CPU_WRITES_WORDS_SLOW
#endif

/*** #32 ***/
/*
 * Define IF you need increased TrueType black & white low resolution bitmap compatibility.
 *
 * If you do not need LOW resolution TrueType black & white bitmap compatability then do not define this.
 * If you are only using gray scale output then there is no need to define this.
 * Defining this will make FontFusion run somewhat slower as well as slightly increase code size.
 * The performance loss from defining this is about 4% - 5% at 12 ppem and the code size increase is about 2 Kbytes.
*/
#define									ENABLE_MORE_TT_COMPATIBILITY

/*** #33 ***/
/* Only enable if you intend to use the LCD modes */
#define									ENABLE_LCD_OPTION

/*** #34 ***/
/* Enable for PCLeo support */
/*#define									ENABLE_PCL*/

/*** #35 ***/
/* Enable for PCLetto support */
/*#define									ENABLE_PCLETTO*/

/*** #36 ***/
/* Enable for Speedo support */
#define									ENABLE_SPD

/*** #37 ***/
/* This enables the direct stroke to bitmap converter code. It provides a 3X
   speed boost at low sizes for stroke fonts!!!. This makes stroke fonts
   render faster than outline fonts. It however uses approximations that
   become visible at higher sizes. The define actives the code and defines the
   largest size that is allowed to use the fast stroke conversion process.
   We do not recommend that it is used above 32 ppem.
   The code size increase from this is about 4.5 Kbytes.
*/
#define									ENABLE_STRKCONV 32

/*** #38 ***/
/* Enables the T2K_ConvertGlyphSplineType() method.
 * The code size increase from this is about 7 Kbytes.
 * Only enable if you need outline curve conversion capability!
*/
#define									ENABLE_FF_CURVE_CONVERSION

/*** #39 ***/
/* Enables the native Type 1 and PFR hint interpreter.
 * Only enable this if you intend to use Type 1 or PFR fonts with native hints.
 * Native hints are only used by T2K_NAT_GRID_FIT and the LCD4 mode for T2K_RenderGlyph.
 * For instance if you only intend to use PFR fonts using TV_MODES for T2K_RenderGlyph
 * then you do not need to enable it. Enabling this means an increase
 * in code size, RAM usage as well as a slower execution.
*/
#define									ENABLE_NATIVE_T1_HINTS

/*** #40 ***/
/* Enables optional support for the TrueType gasp table.
 * When enabled the T2K_GaspifyTheCmds() method lloks at the gasp table.
*/
/*#define									ENABLE_GASP_TABLE_SUPPORT*/

/*** #41 ***/
/* Enabling this enables FontFusion to deal better with corrupt fonts.
 * The downside of this is that it produces some more code and FontFusion will run a little slower.
 * On an embedded system with a known to be good font set, do not enable this.
 * In a desk-top like situation when FontFusion will encounter random fonts -- some of them corrupt --
 * please do enable this.
*/
#define									USE_SEAT_BELTS

/*** #42 ***/
/* Enables optional support for Type1 fonts in ROM.
 * If your application will never have a ROM based Type1 font,
 * you may save some run time memory allocation by
 * disabling this option.
*/
/*#define									ROM_BASED_T1*/

/*** #43 **/
/* Enable support for OpenType fonts */
#define									ENABLE_OTF
#define									ENABLE_OPENTYPE_SUPPORT

/*** #44 ***/
/* Enable support for compressed input streams */
/*#define									COMPRESSED_INPUT_STREAM*/

/*** #45 ***/
/* Enable support for extended LCD modes */
/*#define									ENABLE_EXTENDED_LCD_OPTION*/

/*** #46 ***/
/* Enable support for SBITs Transformation */
/*#define									ENABLE_SBITS_TRANSFORM*/

/*** #47 ***/
/* Enable cache compression and decompression */
/*#define									ENABLE_CACHE_COMPRESSION*/

/*** #48 ***/
/* Enable the support to share the defualt glyph in cache */
/*#define									ENABLE_COMMON_DEFGLYPH*/

/*** #49 ***/
/* Enable cache resize functionality */
/*#define									ENABLE_CACHE_RESIZE*/

/*** #50 ***/
/* Enable the BDF font format */
/*#define									ENABLE_BDF*/

/*** #51 ***/
/* Enable Multiple Filter functionality */
/*#define									ENABLE_MULTIPLE_FILTERS*/

/*** #52 ***/
/* For enabling memory compaction in cache */
/*#define									ENABLE_CACHE_COMPACTION*/

/*** #53 ***/
/* For enabling the 32 bit font code for cache. */
/*#define									ENABLE_32BIT_CACHE_TAG*/

/*** #54 ***/
/* Enables caching of subIndexTables in EBLC table. Only enable this when you intend to use
 * embedded bitmap fonts. This enables the fast rendering of the bitmaps but uses extra heap
 * memory for caching subIndexTables which is font dependent.
 */
#ifndef	ENABLE_CACHING_EBLC
#define	ENABLE_CACHING_EBLC
#else
#if ENABLE_CACHING_EBLC == 0
#undef	ENABLE_CACHING_EBLC
#endif
#endif

/*** #55 ***/
/* Enables a client defined error routine ClientError() called from tsi_Error().
 * The following ClientError() prototype statement and #define CLIENT_ERROR compile conditional
 * should be modified as necessary for the target implementation
 */
#ifdef ENABLE_CLIENT_ERROR
#ifdef __cplusplus
extern "C"
#endif
/* Prototype statement */
void ClientError(void* memObject, int errorCode);
#ifdef __cplusplus
extern "C"
#endif
/* Compile Conditional */
#define CLIENT_ERROR ClientError
#endif

/*** #56 ***/
/* Enables the support for compressed sbits fonts. */
/*#define									ENABLE_SBITS_COMPRESSION*/

/*** #57 ***/
/* Enables client specific methods to allocate/re-allocate/free memory. */
/*#define									ENABLE_CLIENT_ALLOC*/

/*** #58 ***/
/* Enables the dropout adaptation system. */
#ifndef	ENABLE_DROPOUT_ADAPTATION
#define	ENABLE_DROPOUT_ADAPTATION
#else 
#if ENABLE_DROPOUT_ADAPTATION == 0
#undef	ENABLE_DROPOUT_ADAPTATION
#endif
#endif

/*** #59 ***/
/* Enables the support for SFNT fonts embedded in mac resource font files as dfont */
/*#define									ENABLE_MAC_RFORK*/

/*** #60 ***/
/* Enable the Windows Fnt font format */
/*#define									ENABLE_WINFNT*/

/*** #61 ***/
/* Enable the user to select the encoding other than which is present in the T1 fonts */
/*#define									ENABLE_T1_FORCE_ENCODING*/

/*** #62 ***/
/* Enables 32-bit unicode  support. */
/* #define									ENABLE_UNICODE_32_SUPPORT */

/*** #63 ***/
/* Enables the user to track and validate the heap usage. Its suggested to keep this on unless the base platform has 
 * its own memory validation system. Enabling this will help in graceful recovery in case of any memory corruption. */
#ifndef	ENABLE_MEM_VALIDATION
#define	ENABLE_MEM_VALIDATION
#else
#if	ENABLE_MEM_VALIDATION == 0
#undef	ENABLE_MEM_VALIDATION
#endif
#endif

/*** #64 ***/
/* 
 * Enables Smart Scaling feature.
 */
/* #define									ENABLE_SMARTSCALE */

/*** #65 ***/
/*
 * Enables 2-D emboldening
 */
/* #define									ENABLE_2D_EMBOLD */

/*** #66 ***/
/*
 * Enables contour direction correction in algorithmic styles
 */
/* #define									ENABLE_CHECK_CONTOUR_DIRECTION */

/*** #67 ***/
/*
 * Enabbles support for fractional point sizes.
 */
/* #define									ENABLE_FRACTIONAL_SIZE */

/*** #67 ***/
/*
 * Enables the Pseudo font support with lsb correction
 */
/* #define									ENABLE_PSEUDOFONT_SUPPORT */

/*** #68 ***/
/*
 * Enables Support for optimized 2-degree PFR
 */
/* #define									ENABLE_2DEGREE_OPTIMIZED_PFR */

/*** #69 ***/
/*
 * Enable Support for OpenType VERT feature.
 */
/* #define									ENABLE_OPENTYPE_VERT */

/*** #70 ***/
/* 
 * Enable more precised value of metrics
 */
/* #define									ENABLE_EXTRA_PRECISION */

/*** End of optional features ***/

/**** **** **** END configuration defines **** **** ****/

/* The T2K client is not supposed to change anything beyond the "END configuration defines" */


/* #XX Research on a future T2K format, DO NOT ENABLE!!! */
/*#define									ENABLE_T2KE*/


/**********************************************************************/
/**********************************************************************/
/**********************************************************************/

#ifdef ENABLE_LCD_OPTION
#define DRIVE_8BIT_LCD
#endif

#ifdef ENABLE_EXTENDED_LCD_OPTION
#define DRIVE_8BIT_LCD
#endif

#ifdef ENABLE_SBITS_TRANSFORM
#ifndef ENABLE_SBIT
#define ENABLE_SBIT
#endif
#endif

#ifdef ENABLE_BDF
#ifndef ENABLE_SBIT
#define ENABLE_SBIT
#endif
#endif

/* Below we just have internal, non-user-configurable stuff */
#define ENABLE_WRITE
#define ENABLE_PRINTF

/* Should ALWAYS be define when T2K is used as a font engine */
#ifndef	T2K_SCALER
#define	T2K_SCALER
#else
#if T2K_SCALER == 0
#undef	T2K_SCALER
#endif
#endif

/* #define ENABLE_T2KE_EDITING */

#ifdef T2K_SCALER
#	ifdef ENABLE_AUTO_GRIDDING
#		define ENABLE_ALL_AUTO_HANDG_CODE
#	endif

#	undef ENABLE_WRITE
#	undef ENABLE_PRINTF
#else
	/* Can not be defined at the same time as ENABLE_AUTO_GRIDDING */
#	define ENABLE_AUTO_HINTING
#	define ENABLE_ALL_AUTO_HANDG_CODE
#	ifdef ENABLE_AUTO_GRIDDING
#		undef ENABLE_AUTO_GRIDDING
#	endif
#	ifdef ENABLE_NATIVE_TT_HINTS
#		undef ENABLE_NATIVE_TT_HINTS
#	endif
#endif /* T2K_SCALER */

#ifdef ENABLE_ALL_AUTO_HANDG_CODE
#	ifndef ENABLE_AUTO_GRIDDING_CORE
#		define ENABLE_AUTO_GRIDDING_CORE
#	endif
#endif


/* #define SAMPO_TESTING_T2K , should not be defined in a release going out from Type Solutions, Inc. */
#ifdef SAMPO_TESTING_T2K
#define ENABLE_WRITE
#define ENABLE_PRINTF
#endif /* SAMPO_TESTING_T2K */

#ifdef ENABLE_T1
#	define T1_OR_T2_IS_ENABLED
#endif

#ifdef ENABLE_CFF
#	ifndef T1_OR_T2_IS_ENABLED
#		define T1_OR_T2_IS_ENABLED
#	endif
#endif

#ifdef ENABLE_PFR
#	ifndef T1_OR_T2_IS_ENABLED
#		define T1_OR_T2_IS_ENABLED
#	endif
#endif

#ifdef ENABLE_PCL
#	ifndef T1_OR_T2_IS_ENABLED
#		define T1_OR_T2_IS_ENABLED
#	endif
#endif

#ifdef ENABLE_SPD
#	ifndef T1_OR_T2_IS_ENABLED
#		define T1_OR_T2_IS_ENABLED
#	endif
#endif

#if defined (ENABLE_STRKCONV) && !defined (ENABLE_T2KS)
#	undef ENABLE_STRKCONV
#endif

#ifdef ENABLE_T1
#	define ENABLE_HASH_CLASS
#endif
#ifdef ENABLE_CFF
#	ifndef ENABLE_HASH_CLASS
#		define ENABLE_HASH_CLASS
#	endif
#endif

#ifdef ENABLE_OPENTYPE_VERT
/* Enable the OPENTYPE flag. Do not enable to disable this manually */
#	define ENABLE_OPENTYPE_SUPPORT
#endif /* ENABLE_OPENTYPE_VERT */

#ifdef ENABLE_OPENTYPE_SUPPORT
#	ifndef ENABLE_OTF
#		define ENABLE_OTF
#	endif
#endif /* ENABLE_OPENTYPE_SUPPORT */

/****      End of configuration defines     ****/
/***********************************************/

/**********************************************************************/
/**********************************************************************/
/*            Error Checking for illegal cofigurations                */
/**********************************************************************/
/**********************************************************************/

#if defined(ENABLE_MAC_T1) && (!defined(ENABLE_T1))
#error ILLEGAL_CONFIGURATION_OPTION_IN_CONFIG_DOT_H
#endif
#ifdef ENABLE_T2KE
#error CONFIGURATION_NOT_SUPPORTED_IN_CONFIG_DOT_H
#endif

#if defined(ENABLE_T1_FORCE_ENCODING) && !defined(ENABLE_T1)
#error ILLEGAL_CONFIGURATION_OPTION_IN_CONFIG_DOT_H
#endif /* ENABLE_T1_FORCE_ENCODING & !ENABLE_T1 */

#endif /* __T2K_CONFIG__ */



/*********************** R E V I S I O N   H I S T O R Y **********************
 *                                                                            *
 *     $Header: /home/archive/FontFusion/FontFusion/core/config.h,v 1.36 2009/07/03 09:23:30 rpasricha Exp $
 *                                                                            *
 *     $Log: config.h,v $
 *     Revision 1.36  2009/07/03 09:23:30  rpasricha
 *     gcc_4_4_0 warnings fixed
 *
 *     Revision 1.35  2009/06/24 08:45:53  rpasricha
 *     Macro Name changed
 *
 *     Revision 1.34  2009/05/13 20:57:23  sflynn
 *     Added check for ENABLE_OTF
 *
 *     Revision 1.33  2009/05/04 09:26:34  ljoshi
 *     Enabling OTF when GSUB features are turned on.
 *
 *     Revision 1.32  2009/04/29 10:34:30  ljoshi
 *     Having OpenType VERT feature off by default.
 *
 *     Revision 1.31  2009/04/29 10:25:19  ljoshi
 *     OTF Feature support including VERT feature.
 *
 *     Revision 1.30  2009/01/06 09:14:22  rpasricha
 *     Implementation: Support for optimized 2-degree PFR
 *
 *     Revision 1.29  2008/11/13 07:10:11  rpasricha
 *     Implementation: Pseudo Font with LSB Correction
 *
 *     Revision 1.28  2008/11/05 11:17:10  ljoshi
 *     Adding support fro Frac Size.
 *
 *     Revision 1.27  2008/06/17 05:23:10  rpasricha
 *     Added the ENABLE_CHECK_CONTOUR_DIRECTION  compile conditional
 *
 *     Revision 1.26  2008/06/12 03:29:44  rpasricha
 *     Added the ENABLE_2D_EMBOLD compile conditional
 *
 *     Revision 1.25  2008/03/11 16:11:37  sflynn
 *     Added the ENABLE_SMARTSCALE compile conditional.
 *
 *     Revision 1.24  2008/02/19 18:32:51  sflynn
 *     Redefined ENABLE_MEM_VALIDATION so it can be shut off externally.
 *
 *     Revision 1.23  2008/02/19 06:29:16  ljoshi
 *     Conrrecting indentation.
 *
 *     Revision 1.22  2008/02/19 06:02:12  ljoshi
 *     Adding ENABLE_MEM_VALIDATION
 *
 *     Revision 1.21  2008/02/12 19:54:50  sflynn
 *     Updated for 32-bit character code support.
 *
 *     Revision 1.20  2008/01/11 05:49:55  ljoshi
 *     Adding support for forced Type1 encoding.
 *
 *     Revision 1.19  2007/11/22 04:13:35  ljoshi
 *     Correcting the file name.
 *
 *     Revision 1.18  2007/11/13 14:40:19  ritesh
 *     Ritesh: Added the support for the windows fnt font format.
 *
 *     Revision 1.17  2007/11/06 13:19:58  himanshu
 *     Adding support for variable include file name.
 *
 *     Revision 1.16  2007/05/09 06:15:24  ljoshi
 *     Adding macros for vaious library functions.
 *
 *     Revision 1.15  2007/04/05 15:55:34  sflynn
 *     Added ENABLE_MAC_RFORK compile conditional for support of Dfonts.
 *
 *     Revision 1.14  2007/03/23 17:51:48  sflynn
 *     Moved compile conditional ENABLE_DROPOUT_ADAPTATION from t2k.c.
 *
 *     Revision 1.13  2007/01/04 22:06:38  sflynn
 *     Added ENABLE_SBITS_COMPRESSION compile conditional.
 *     Added ENABLE_CLIENT_ALLOC compile conditional.
 *
 *     Revision 1.12  2006/12/14 16:49:28  sflynn
 *     Added compile conditional #47 ENABLE_CLIENT_ERROR
 *     The defines CLIENT_ERROR as a user routine to call from tsi_Error() if defined.
 *
 *     Revision 1.11  2006/10/06 16:01:50  sflynn
 *     Modified ENABLE_CACHING_EBLC for external control.
 *
 *     Revision 1.10  2006/09/29 16:50:01  sflynn
 *     Added ENABLE_CACHING_EBLC compile conditional.
 *
 *     Revision 1.9  2006/06/02 18:10:54  sflynn
 *     Modified to support configurable 16\32 bit cache tag.
 *
 *     Revision 1.8  2006/05/24 18:12:15  sflynn
 *     Added #include ff_user.h
 *     Added #ifndef for all memory allocation Macros
 *
 *     Revision 1.7  2006/04/28 18:54:05  sflynn
 *     no message
 *
 *     Revision 1.45  2006/04/13 15:34:21  Shawn_Flynn
 *     Added "#define ENABLE_CACHE_COMPACTION".
 *
 *     Revision 1.44  2005/11/02 16:04:09  Shawn_Flynn
 *     Added the ENABLE_MULTIPLE_FILTERS compile conditional.
 *
 *     Revision 1.43  2005/10/06 19:14:12  Shawn_Flynn
 *     Added ENABLE_BDF for BDF bitmap font support.
 *
 *     Revision 1.42  2005/09/15 19:27:09  Shawn_Flynn
 *     Added following manifests:
 *     ENABLE_SBITS_TRANSFORM
 *     ENABLE_CACHE_COMPRESSION
 *     ENABLE_COMMON_DEFGLYPH
 *     ENABLE_CACHE_RESIZE
 *
 *     Revision 1.41  2005/04/21 17:34:41  Shawn_Flynn
 *     Added ENABLE_EXTENDED_LCD_OPTION manifest.
 *
 *     Revision 1.40  2005/04/19 16:12:33  Shawn_Flynn
 *     Added manifest for COMPRESSED_INPUT_STREAM processing.
 *
 *     Revision 1.39  2004/04/08 18:35:01  Shawn_Flynn
 *     Add comment close on line 53.
 *     Added comment indicating ENABLE_CFF is required for CFF/OTF support.
 *
 *     Revision 1.38  2004/03/10 20:01:20  Shawn_Flynn
 *     Now use #ifndef/#elif/#endif for options on by default - this allows these
 *          options to be turned off without modifying this file.
 *
 *     Revision 1.37  2003/04/03 17:43:55  Shawn_Flynn
 *     Removed C++ style comments.
 *     Removed ENABLE_AUTO_GRIDDING_CORE.
 *
 *     Revision 1.36  2003/03/31 20:31:10  Shawn_Flynn
 *     Turned of ENABLE_AUTO_GRIDDING_CORE.
 *
 *     Revision 1.35  2003/03/14 15:41:02  Shawn_Flynn
 *     Cleaned up compiler warnings.
 *
 *     Revision 1.34  2003/01/03 18:05:28  Shawn_Flynn
 *     dtypED
 *     Reduced default compile options to T2K/TTF Native hints only.
 *
 *     Revision 1.33  2002/03/26 16:21:13  Shawn_Flynn
 *     Total of 35 configuration options.
 *
 *     Revision 1.32  2002/03/06 15:17:56  Shawn_Flynn
 *     Added support for OpenType via ENABLE_OTF. (off by default)
 *
 *     Revision 1.31  2001/05/04 21:04:34  reggers
 *     Cosmetic correction only.
 *     Revision 1.28  2001/04/26 19:27:29  reggers
 *     Fixed a missing #endif
 *     Revision 1.27  2001/04/26 15:23:50  reggers
 *     Enable ENABLE_HASH_CLASS if T1 of CFF enabled.
 *     Revision 1.26  2001/04/25 21:57:09  reggers
 *     Moved ROM_BASED_T1 option here from t1.c
 *     Revision 1.25  2001/04/24 21:56:26  reggers
 *     Added option #32 for GASP table support. (Sampo)
 *     Revision 1.24  2000/07/11 17:31:20  reggers
 *     Set STRKCONV to 32 lines as default.
 *     Automatically set T1_OR_T2_IS_ENABLED on ENABLE_SPD
 *     Automatically unset ENABLE_STRKCONV if ENABLE_T2KS not set.
 *     Revision 1.23  2000/06/16 21:39:14  reggers
 *     Fixed a comment.
 *     Revision 1.22  2000/06/16 17:17:54  reggers
 *     Made ENABLE_NATIVE_T1_HINTS user config option.
 *     Revision 1.21  2000/05/17 17:05:56  reggers
 *     Cleanup extra space before #define
 *     Revision 1.20  2000/05/12 19:56:17  reggers
 *     Made legacy settings consistent with last release.
 *     Revision 1.19  2000/05/11 13:36:38  reggers
 *     Added the outline curve conversion as an option. (Sampo)
 *     Revision 1.18  2000/04/24 17:10:50  reggers
 *     Added new stroke converter size threshold option (#29).
 *     Revision 1.17  2000/04/19 18:59:28  mdewsnap
 *     Added in ENABLE_T1_NATIVE_HINTS
 *     Revision 1.16  2000/03/27 22:16:45  reggers
 *     Updates for new LCD mode and functionality
 *     Revision 1.14  2000/01/20 16:19:41  reggers
 *     Set T1_OR_T2_IS_ENABLED when ENABLE_PCL is enabled.
 *     Revision 1.13  2000/01/20 15:48:47  reggers
 *     Got rid of ENABLE_HP_PRINTER: unneedeed.
 *     Revision 1.12  2000/01/18 20:51:26  reggers
 *     Improve indenting of #'s
 *     Added options for PCL and PCLETTO.
 *     Revision 1.11  2000/01/17 14:31:27  reggers
 *     Leave ENABLE_PCL and ENABLE_PCLETTO defaulted to off.
 *     Revision 1.10  2000/01/14 18:19:46  reggers
 *     Added new #define for ENABLE_PCLETTO.
 *     Revision 1.9  1999/12/23 22:02:51  reggers
 *     New ENABLE_PCL branches. Rename any 'code' and 'data' symbols.
 *     Revision 1.8  1999/12/09 22:14:04  reggers
 *     Added new ENABLE_MORE_TT_COMPATIBILITY option.
 *     Revision 1.7  1999/10/29 15:04:59  jfatal
 *     Check for a couple of bad (or unsupported) configuration and
 *     return a compiler error.
 *     Revision 1.6  1999/10/19 16:20:08  shawn
 *     Changed UNUSED(x) macro to '((void)(x))'.
 *
 *     Revision 1.5  1999/09/30 15:10:23  jfatal
 *     Added correct Copyright notice.
 *                                                                            *
 ******************************************************************************/

