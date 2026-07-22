/* Copyright 2009, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to 
 * QNX Software Systems before you may reproduce, modify or distribute this 
 * software, or any work that includes all or part of this software.  Free 
 * development licenses are available for evaluation and non-commercial purposes.  
 * For more information visit http://licensing.qnx.com or email licensing@qnx.com.
 * 
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 */
/*!
    \file font_types.h
    \brief font server - Public data type definitions.
*/

#ifndef __FONTTYPES_H_INCLUDED
#define __FONTTYPES_H_INCLUDED

#ifdef __LINUX__
#include <stdint.h>
#endif
#include <stdlib.h>
#include <limits.h>
#ifndef NAME_MAX
#define NAME_MAX 255
#endif
#include <inttypes.h>

#if defined(__linux__) || defined(__SOLARIS__)
#include "lib/compat.h"
#endif

#if defined(__QNXNTO__)
    #include <_pack64.h>
#else
    #if __WATCOMC__ > 1000
        #pragma pack(__push,1)
    #else
        #pragma pack(1)
    #endif
#endif

typedef struct pfPoint
{  short x,y;
} pf_point_t;

typedef struct pfRect
{  pf_point_t ul;
   pf_point_t lr;
} pf_rect_t;

typedef struct pfDim
{  unsigned short w,h;
} pf_dim_t;

typedef struct pfPoint16dot16
{  int32_t x_16dot16,y_16dot16;
} pf_point_16dot16_t;

typedef struct pfRect16dot16
{  pf_point_16dot16_t ul;
   pf_point_16dot16_t lr;
} pf_rect_16dot16_t;

#define D_MAX_CHARACTER_ARRAY 100

typedef char pf_item_t[D_MAX_CHARACTER_ARRAY];

#define MAX_FONT_TAG 80

typedef char FontName[MAX_FONT_TAG];
typedef char FontFilename[NAME_MAX + 16];

#define MAX_DESC_LENGTH 32

typedef char FontDescription[MAX_DESC_LENGTH];

/** Font general data.
 *  - Description : FontDetails describes the available
 *                  point sizes (0,0 indicates scalable)
 *                  for a font, as well as the foundry
 *                  assigned descriptive name.  The flags
 *                  are comprised of PHFONT_INFO_XXXX values.
 */
typedef struct {
#if defined(__QNXNTO__)
	int16_t			losize; /*!<Lowest point size. */
	int16_t			hisize; /*!<Highest point size. */
	uint16_t		flags; /*!<PHFONT_INFO_XXXX flags. */
	uint16_t		nSpare[1];
	uint32_t		ulSpare[2];
	FontDescription	desc; /*!<Foundry name, i.e. PrimaSans BT */
	FontName		stem; /*/Base stem name, i.e. primasansbts */
#else
	FontDescription	desc; /*!<Foundry name, i.e. PrimaSans BT */
	FontName		stem; /*/Base stem name, i.e. primasansbts */
	int16_t			losize; /*!<Lowest point size. */
	int16_t			hisize; /*!<Highest point size. */
	uint16_t		flags; /*!<PHFONT_INFO_XXXX flags. */
#endif
} FontDetails;

/** Font specific data.
 *  - Description : FontqueryInfo describes the global metrics,
 *                  font style (PHFONT_INFO_XXXX values), and
 *                  code point range.
 */
typedef struct {
#if defined(__QNXNTO__)
	int16_t			size; /*!<Point size, 0 for scalable. */
	uint16_t		style; /*!<PHFONT_INFO_XXXX flags. */
	int16_t			ascender; /*!<Overall font ascender in pixels. */
	int16_t			descender; /*!<Overall font descender in pixels. */
	int16_t			width; /*!<Maximum font width in pixels. */
	uint16_t		nSpare[1];
	int32_t			lochar; /*!<Lowest code point. */
	int32_t			hichar; /*!<Highest code point. */
	uint32_t		ulSpare[2];
	FontName		font; /*!<Stem name of font, i.e. primasansbts12 */
	FontDescription	desc; /*!<Foundry name, i.e. PrimaSans BT */
#else
	FontName		font; /*!<Stem name of font, i.e. primasansbts12 */
	FontDescription	desc; /*!<Foundry name, i.e. PrimaSans BT */
	int16_t			size; /*!<Point size, 0 for scalable. */
	uint16_t		style; /*!<PHFONT_INFO_XXXX flags. */
	int16_t			ascender; /*!<Overall font ascender in pixels. */
	int16_t			descender; /*!<Overall font descender in pixels. */
	int16_t			width; /*!<Maximum font width in pixels. */
	int32_t			lochar; /*!<Lowest code point. */
	int32_t			hichar; /*!<Highest code point. */
#endif
} FontQueryInfo;

/** Render RGB flag value.
 *  - Description : If the FontRender 'flags' member has
 *                  this bit set, the resultant pixmap
 *                  if represented as RGB values per pixel.
 *                  Not all font technologies may support
 *                  this format.
 */
#define FONTRENDER_RGB_PIXMAP 0x1

/** Render BGR flag value.
 *  - Description : If the FontRender 'flags' member has
 *                  this bit set, the resultant pixmap
 *                  if represented as BGR values per pixel.
 *                  Not all font technologies may support
 *                  this format.
 */
#define FONTRENDER_BGR_PIXMAP 			0x2
#define FONTRENDER_IGNORED_LEFT_BEARING 0x4
#define FONTRENDER_IGNORED_XMAX 		0x8

/** Render data structure.
 *  - Description: Data structure which defines render
 *                 information returns from routine
 *                 PfRenderCx.
 */
typedef struct {
	pf_point_t		size; /*!< Size in pixels of resultant image. */
	pf_point_t		offset; /*!< Offset to apply to destination co-oridinates. */
	int32_t			width; /*!< Black pixel width. */
	int16_t			bpl; /*!< Bytes-per-line of resultant image. */
	int16_t			bpp; /*!< Bits-per-pixel of resultant image. */
	uint32_t		flags; /*!< Render flags, see above. */
#if defined(__QNXNTO__)
	uint32_t		ulSpare[1]; /*!< Spare element for future expansion. */
#endif
	unsigned char	*bmptr; /*!< Image reference. */
} FontRender;

typedef struct pf_globals * font_private_globals_t;

/** Font context.
 *  - Description : Context state information.
 */
struct _Pf_ctrl {
#if defined(__QNXNTO__)
	int32_t				server; /*!< File descriptor to external font server. */
	int32_t				size; /*!< Size of render buffer, 0 none, <0 heap buffer, >0 shmem buffer. */
	uint32_t			x_dpi, y_dpi; /*!< Requested render/extent DPI.  May be ignored by font server. */
    font_private_globals_t globals; /*!< Opaque font server data. */
	uint32_t			ulSpare[1]; /*!< Spare element for future expansion. */
	unsigned char		*shmem; /*!< Reference to render buffer. */
	void				*local; /*!< Opaque reference to local metric data. */
#else
  #if defined(__linux__) || defined(__CYGWIN__)
	COID_T              server; /*!< File descriptor to external font server. */
  #else
	int32_t          	server; /*!< File descriptor to external font server. */
  #endif
	int32_t				size; 			/*!< Size of render buffer, 0 none, <0 heap buffer, >0 shmem buffer. */
	uint32_t			x_dpi, y_dpi;	/*!< Requested render/extent DPI.  May be ignored by font server. */
    font_private_globals_t globals; 	/*!< Opaque font server data. */
	unsigned char		*shmem; 		/*!< Reference to render buffer. */
	void				*local; 		/*!< Opaque reference to local metric data. */
#endif
};

/** Detailed glyph metrics.
 *  - Description : High precision glyph metrics.
 */
typedef struct
{  int32_t Advance;  /*!< 16.16 format */
   int32_t BearingX; /*!< 16.16 format */
   int32_t BearingY; /*!< 16.16 format */
   int32_t MaxX;     /*!< 16.16 format */
   int32_t Height;   /*!< pixel format */
   int32_t Width;    /*!< pixel format */
   int32_t uiSpare[2]; /*!< Spare element for future expansion. */
   uint32_t ulSpare[4]; /*!< Spare element for future expansion. */
}  pf_metrics_t;

/**
 * Backwards compile compatibility.
 */
#define PHFONT_METRICS pf_metrics_t

/** Cache statistics.
 *  - Description : Used to describe cache heuristics.
 */
typedef struct __TS_FONT_STATS_
{  uint32_t uiCacheHits; /*!<Number of times cache was hit. */
   uint32_t uiTotalAttempts; /*!<Number of times cache was accessed. */
   uint32_t uiSpare[6];
}  FontStats; 

typedef struct __TS_FONT_ID_ FontID;

#if defined(__QNXNTO__)
    #include <_packpop.h>
#else
    #if __WATCOMC__ > 1000
        #pragma pack(__pop)
    #else
        #pragma pack()
    #endif
#endif

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/font/public/font_types.h $ $Rev: 224585 $" )
#endif
