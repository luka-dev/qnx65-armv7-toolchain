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
#ifndef __PG_MACROS_H_INCLUDED
#define __PG_MACROS_H_INCLUDED

#define	_PgSWAPRGB(c)			(((c) & 0xFF00FF00) | ((c >> 16) & 0x000000FF) | ((c << 16) & 0x00FF0000))
#define _PgSWAPPRGB(c)			_PgSWAPRGB(c)
#define _PgSWAPARGB(c)			(((c >> 24) & 0x000000FF) | ((c >> 16) & 0x000000FF) | ((c) & 0x0000FF00) | ((c << 16) & 0x00FF0000))

/* Macros for manipulating color values */
#define	PgRGB(r,g,b)			(((PgColor_t)((r) & 0xFF) << 16) | ((PgColor_t)((g) & 0xFF) << 8) | (PgColor_t)((b) & 0xFF))
#define	PgRGBA(r,g,b,a)			(((PgColor_t)((r) & 0xFF) << 16) | ((PgColor_t)((g) & 0xFF) << 8) | (PgColor_t)((b) & 0xFF) | ((PgColor_t)((a) & 0xFF) << 24))
#define PgARGB(a,r,g,b)			(((PgColor_t)((a) & 0xFF) << 24) | ((PgColor_t)((r) & 0xFF) << 16) | ((PgColor_t)((g) & 0xFF) << 8) | (PgColor_t)((b) & 0xFF))
#define	PgCMY(c,m,y)			(PgRGB( c, m, y ) ^ 0xFFFFFF)
#define PgCMYK(c,m,y,k)			PgRGB(					\
								0xff ^ min(c + k,255),	\
								0xff ^ min(m + k,255),	\
								0xff ^ min(y + k,255))
#define PgCMYK2RGB(a)			PgCMYK((a).c,(a).m,(a).y,(a).k)
#define PgGray(v)				(PgRGB( v, v, v ))
#define	PgGrey(v)				PgGray(v)
#define PgBlueValue(c)			((int)((c) & 0xFF))
#define PgGreenValue(c)			((int)(((c) >> 8) & 0xFF))
#define PgRedValue(c)			((int)(((c) >> 16) & 0xFF))
#define PgAlphaValue(c)			((int)(((c) >> 24) & 0xFF))
#define	PgGreyValue(c)			(((PgRedValue( c ) * 77) + (PgGreenValue( c ) * 151) + (PgBlueValue( c ) * 28)) >> 8)
#define	PgGrayValue(c)			(((PgRedValue( c ) * 77) + (PgGreenValue( c ) * 151) + (PgBlueValue( c ) * 28)) >> 8)

/* Macros for manipulating 16-bit color values (565) */
#define Pg565to8888(c)			((((c) & 0x1F) << 3) | (((c) & 0x7E0) << 5) | (((c) & 0xF800) << 8))
#define Pg8888to565(c)			((((c) & 0xF8) >> 3) | (((c) & 0xFC00) >> 5) | (((c) & 0xF80000) >> 8))
#define PgRGB565(r,g,b)			((((r) & 0xF8) << 8) | (((g) & 0xFC) << 3) | (((b) & 0xF8) >> 3))
#define PgBlueValue565(c)		(((c) & 0x1F) << 3)
#define PgGreenValue565(c)		(((c) & 0x7E0) >> 3)
#define PgRedValue565(c)		(((c) & 0xF800) >> 8)

/* Macros for manipulating 16-bit color values (555) */
#define Pg555to8888(c)			((((c) & 0x1F) << 3) | (((c) & 0x3E0) << 6) | (((c) & 0x7C00) << 9))
#define Pg8888to555(c)			((((c) & 0xF8) >> 3) | (((c) & 0xF800) >> 6) | (((c) & 0xF80000) >> 9))
#define PgRGB555(r,g,b)			((((r) & 0xF8) << 7) | (((g) & 0xF8) << 2) | (((b) & 0xF8) >> 3))
#define PgBlueValue555(c)		PgBlueValue565( c )
#define PgGreenValue555(c)		(((c) & 0x3E0) >> 2)
#define PgRedValue555(c)		(((c) & 0x7C00) >> 7)

/* Macros for manipulating 16-bit color values (1555) */
#define Pg1555to8888(c)			((((c) & 0x8000) ? 0xff000000 : 0x0) | (((c) & 0x1F) << 3) | (((c) & 0x3E0) << 6) | (((c) & 0x7C00) << 9))
#define Pg8888to1555(c)			((((c) & 0x80000000) >> 16) | (((c) & 0xF8) >> 3) | (((c) & 0xF800) >> 6) | (((c) & 0xF80000) >> 9))
#define PgRGB1555(a,r,g,b)		((((a) & 0x80) << 8) | (((r) & 0xF8) << 7) | (((g) & 0xF8) << 2) | (((b) & 0xF8) >> 3))
#define PgAlphaValue1555(c)		(((c) & 0x8000) >> 8)
#define PgBlueValue1555(c)		PgBlueValue565( c )
#define PgGreenValue1555(c)		(((c) & 0x3E0) >> 2)
#define PgRedValue1555(c)		(((c) & 0x7C00) >> 7)

/* Macros for manipulating 16-bit color values (444) */
#define Pg444to8888(c)			((((c) & 0xF) << 4) | (((c) & 0xF0) << 8) | (((c) & 0xF00) << 12))
#define Pg8888to444(c)			((((c) & 0xF0) >> 4) | (((c) & 0xF000) >> 8) | (((c) & 0xF00000) >> 12))
#define PgRGB444(r,g,b)			((((r) & 0xF0) << 4) | ((g) & 0xF0) |  (((b) & 0xF0) >> 4))
#define PgBlueValue444(c)		(((c) & 0xF) << 4)
#define PgGreenValue444(c)		((c) & 0xF0)
#define PgRedValue444(c)		(((c) & 0xF00) >> 4)

#define Pg4444to8888(c)			((((c) & 0xF) << 4) | (((c) & 0xF0) << 8) | (((c) & 0xF00) << 12) | (((c) & 0xF000) << 16))
#define Pg8888to4444(c)			((((c) & 0xF0) >> 4) | (((c) & 0xF000) >> 8) | (((c) & 0xF00000) >> 12) | (((c) & 0xF0000000) >> 16))
#define PgRGB4444(a,r,g,b)		((((a) & 0xF0) << 8) | (((r) & 0xF0) << 4) | ((g) & 0xF0) |  (((b) & 0xF0) >> 4))
#define PgBlueValue4444(c)		(((c) & 0xF) << 4)
#define PgGreenValue4444(c)		((c) & 0xF0)
#define PgRedValue4444(c)		(((c) & 0xF00) >> 4)
#define PgAlphaValue4444(c)		(((c) & 0xF000) >> 8)

#define	PgLighterColor(c)		(PgRGB( (0xff-((0xff-PgRedValue( c )) >> 1)),	\
								(0xff-((0xff-PgGreenValue( c )) >> 1)),			\
								(0xff-((0xff-PgBlueValue( c )) >> 1)) ) )

#define PgALighterColor(c)		(PgARGB(PgAlphaValue(c), \
								(0xff - ((0xff - PgRedValue(c)) >> 1)), \
								(0xff - ((0xff - PgGreenValue(c)) >> 1)), \
								(0xff - ((0xff - PgBlueValue(c)) >> 1))))

#define	PgDarkerColor(c)		(PgRGB( (PgRedValue( c ) >> 1),		\
								(PgGreenValue( c ) >> 1),			\
								(PgBlueValue( c ) >> 1) ) )

#define PgADarkerColor(c)		(PgARGB(PgAlphaValue(c), \
								(PgRedValue(c) >> 1),\
								(PgGreenValue(c) >> 1),\
								(PgBlueValue(c) >> 1)))

#define	PgAverageColor(a,b)		(PgRGB( ((PgRedValue( a ) >> 1) + (PgRedValue( b ) >> 1)),	\
								((PgGreenValue( a ) >> 1) + (PgGreenValue( b ) >> 1)),		\
								((PgBlueValue( a ) >> 1) + (PgBlueValue( b ) >> 1)) ) )

#define PgAAverageColor(a,b)	(PgARGB(PgAlphaValue(c), \
								((PgRedValue( a ) >> 1) + (PgRedValue( b ) >> 1)), \
								((PgGreenValue( a ) >> 1) + (PgGreenValue( b ) >> 1)), \
								((PgBlueValue( a ) >> 1) + (PgBlueValue( b ) >> 1))))


/* convert rgb to/from channels using color model */

#define PgCalcRGB(m,c,r)		((m)->compose_f(c,r))
#define PgCalcChannels(m,r,c)	((m)->decompose_f(r,c))

#define PgCMChannelAbbrev(m,c)	((m)->channels[c].name ? *((m)->channels[c].name) : (c) + '0')

/* macro for identifying custom color spaces */

#define Pg_CM_CUSTOM_ID(x)		(((x) & 0xdf) + 32)

/* adjust only single channel when setting color resources */

#define PgSetChannel(c,v)		((ulong_t)((((c) & 3) << 16) | ((v) & 0xffff) | 0xc0000000))
#define PgAdjustChannel(c,v)	((ulong_t)((((c) & 3) << 16) | (((v) < 0 ? (-(v)) : ((v) | 0x20000000)) & 0x2000ffff) | 0x80000000))

#endif /* __PG_MACROS_H_INCLUDED */

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PgMacros.h $ $Rev: 224590 $" )
#endif
