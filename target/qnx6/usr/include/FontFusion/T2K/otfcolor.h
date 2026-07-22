/*
 * otfcolor.h
 * $Header: /home/archive/Panorama/layout/LLManager/hdr/otfcolor.h,v 1.14 2007/11/12 04:47:57 himanshu Exp $
 * Font Fusion Copyright (c) 1989-2004 all rights reserved by Bitstream Inc.
 * http://www.bitstream.com/
 * http://www.typesolutions.com/
 * Author: Lokesh
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
#ifndef __OTFCOLOR_HEADER__
#define __OTFCOLOR_HEADER__

#ifndef LLM_LLCONFIG_HEADER
#include "LLConfig.h"
#else
#include LLM_LLCONFIG_HEADER
#endif /* LLM_LLCONFIG_HEADER */
#include FF_DTYPES_HEADER

#ifdef ENABLE_LLE

/* This was the easiest way for me to define the type for mem
 * buffer type
 */

/**
 * The platform dependent color buffer type. It depends on the macro chosen for color
 * format.
 */
#ifdef LLM_COLOR_FORMAT_MONO
#define LLM_MEM_BUF_TYPE LLM_MEM_BUF_TYPE_MONO
#elif defined(LLM_COLOR_FORMAT_GRAY)
#define LLM_MEM_BUF_TYPE LLM_MEM_BUF_TYPE_GRAY
#elif defined(LLM_COLOR_LAYOUT_R8G8B8) || defined(LLM_COLOR_LAYOUT_A8R8G8B8)
#define LLM_MEM_BUF_TYPE LLM_MEM_BUF_TYPE_888
#define LLM_DEFAULT_COLOR_LAYOUT LLMColorLayout_R8G8B8
#elif defined(LLM_COLOR_LAYOUT_R6G6B6)
#define LLM_MEM_BUF_TYPE LLM_MEM_BUF_TYPE_666
#define LLM_DEFAULT_COLOR_LAYOUT LLMColorLayout_R6G6B6
#elif defined(LLM_COLOR_LAYOUT_R5G6B5)
#define LLM_MEM_BUF_TYPE LLM_MEM_BUF_TYPE_565
#define LLM_DEFAULT_COLOR_LAYOUT LLMColorLayout_R5G6B5
#elif defined(LLM_COLOR_LAYOUT_R5G5B5)
#define LLM_MEM_BUF_TYPE LLM_MEM_BUF_TYPE_555
#define LLM_DEFAULT_COLOR_LAYOUT LLMColorLayout_R5G5B5
#elif defined(LLM_COLOR_LAYOUT_R3G3B2)
#define LLM_MEM_BUF_TYPE LLM_MEM_BUF_TYPE_332
#define LLM_DEFAULT_COLOR_LAYOUT LLMColorLayout_R3G3B2
#elif defined(LLM_COLOR_LAYOUT_R3G2B3)
#define LLM_MEM_BUF_TYPE LLM_MEM_BUF_TYPE_323
#define LLM_DEFAULT_COLOR_LAYOUT LLMColorLayout_R3G2B3
#elif defined(LLM_COLOR_LAYOUT_R2G3B3)
#define LLM_MEM_BUF_TYPE LLM_MEM_BUF_TYPE_233
#define LLM_DEFAULT_COLOR_LAYOUT LLMColorLayout_R2G3B3
#endif /* LLM_COLOR_FORMAT_MONO */

#define LLM_MEM_BUF_TYPE_MONO uint8
#define LLM_MEM_BUF_TYPE_GRAY uint8

/**
 * This is a very useful macro when conversion between two color formats and layout is needed. It can be very handy in those cases.
 * For example if the source color format is RGB 888 and the desired target color frmat is 332 BGR then each color can be converted as <code>
 * newColor = LLM_GET_FINAL_COLOR ( oldColor, 888, RGB, 332, BGR );
 * </code>
 */
#define LLM_GET_FINAL_COLOR( __color__, __layout_from__, __format_from__, __layout_to__, __format_to__ )																		\
							(LLM_MEM_BUF_TYPE_##__layout_to__)(LLM_GET_COLOR_##__layout_to__##_##__format_to__ ( LLM_GET_R_##__layout_from__##_##__format_from__ (__color__),	\
																												 LLM_GET_G_##__layout_from__##_##__format_from__ (__color__),	\
																												 LLM_GET_B_##__layout_from__##_##__format_from__ (__color__)))


/* Start: Generic ARGB */
/**
 * This is the type used for the buffers in GlyphObj class.
 */
#define LLM_ARGB_BUF_TYPE uint32

/**
 * To get the 8 Bit R g and B.
 */
#define LLM_GET_STAND_COLOR(R, G, B) ((((LLM_ARGB_BUF_TYPE)R & 0xff) << 16) | (((LLM_ARGB_BUF_TYPE)G & 0xff) << 8) | (((LLM_ARGB_BUF_TYPE)B & 0xff)))

/**
 * Get the RGB with Alpha factor.
 */
#define LLM_GET_ARGB_COLOR(A, R, G, B)((((LLM_ARGB_BUF_TYPE)A & 0xff) << 24) | \
									   (((LLM_ARGB_BUF_TYPE)R & 0xff) << 16) | \
									   (((LLM_ARGB_BUF_TYPE)G & 0xff) << 8 ) | \
									   (((LLM_ARGB_BUF_TYPE)B & 0xff)      ))
/**
 * To access ALPHA.
 */
#define LLM_GET_ARGB_A(color) (((color) >> 24) & 0xff)
/**
 * To Access RED component.
 */
#define LLM_GET_ARGB_R(color) (((color) >> 16) & 0xff)
/**
 * To Access GREEN component.
 */
#define LLM_GET_ARGB_G(color) (((color) >> 8 ) & 0xff)
/**
 * To Access BLUE component.
 */
#define LLM_GET_ARGB_B(color) (((color)      ) & 0xff)
/* End: Generic ARGB */

/* Start Layout: R8G8B8 */
#define LLM_MEM_BUF_TYPE_888  uint32
/* Start Format: RGB */
/**
 * To get the color in LLM_MEM_BUF_TYPE_888 from the 8 bit R,G and B.
 */
#define LLM_GET_COLOR_888_RGB(R, G, B) ((((LLM_MEM_BUF_TYPE_888)R & 0xff) << 16) | \
							            (((LLM_MEM_BUF_TYPE_888)G & 0xff) << 8 ) | \
										((LLM_MEM_BUF_TYPE_888)B & 0xff) )
/**
 * To get the 8 bit R component from LLM_MEM_BUF_TYPE_888 color format.
 */
#define LLM_GET_R_888_RGB(color) (((color) >> 16) & 0xff)
/**
 * To get the 8 bit G component from LLM_MEM_BUF_TYPE_888 color format.
 */
#define LLM_GET_G_888_RGB(color) (((color) >> 8 ) & 0xff)
/**
 * To get the 8 bit B component from LLM_MEM_BUF_TYPE_888 color format.
 */
#define LLM_GET_B_888_RGB(color) (((color)      ) & 0xff)
/* End Format: RGB */

/* Start Format: BGR */
/**
 * To get the color in LLM_MEM_BUF_TYPE_888 from the 8 bit R,G and B.
 */
#define LLM_GET_COLOR_888_BGR(R, G, B) ((((LLM_MEM_BUF_TYPE_888)B & 0xff) << 16) | \
										(((LLM_MEM_BUF_TYPE_888)G & 0xff) << 8 ) | \
										(((LLM_MEM_BUF_TYPE_888)R & 0xff)      ))
/**
 * To get the 8 bit B component from LLM_MEM_BUF_TYPE_888 color format.
 */
#define LLM_GET_B_888_BGR(color) (((color) >> 16) & 0xff)
/**
 * To get the 8 bit G component from LLM_MEM_BUF_TYPE_888 color format.
 */
#define LLM_GET_G_888_BGR(color) (((color) >> 8 ) & 0xff)
/**
 * To get the 8 bit R component from LLM_MEM_BUF_TYPE_888 color format.
 */
#define LLM_GET_R_888_BGR(color) (((color)      ) & 0xff)
/* End Format: BGR */
/* End Layout: R8G8B8 */

/* Start Layout: A8R8G8B8 */
#define LLM_MEM_BUF_TYPE_A888  LLM_MEM_BUF_TYPE_888
/* Start Format: RGB */
/**
 * To get the color in LLM_MEM_BUF_TYPE_A888 from the 8 bit R,G and B.
 */
#define LLM_GET_COLOR_A888_RGB(R, G, B) LLM_GET_COLOR_888_RGB(R, G, B)
/**
* To get the color in LLM_MEM_BUF_TYPE_A888 from the 8 bit R,G and B.
 */
#define LLM_GET_COLOR_A888_ARGB(A, R, G, B) ((((LLM_MEM_BUF_TYPE_888)A & 0xff) << 24) | \
											 (((LLM_MEM_BUF_TYPE_888)R & 0xff) << 16) | \
											 (((LLM_MEM_BUF_TYPE_888)G & 0xff) << 8 ) | \
											 ((LLM_MEM_BUF_TYPE_888)B & 0xff) )
/**
 * To get the 8 bit A component from LLM_MEM_BUF_TYPE_A888 color format.
 */
#define LLM_GET_A_A888_RGB(color) (((color) >> 24) & 0xff)
/**
 * To get the 8 bit R component from LLM_MEM_BUF_TYPE_A888 color format.
 */
#define LLM_GET_R_A888_RGB(color) LLM_GET_R_888_RGB(color)
/**
 * To get the 8 bit G component from LLM_MEM_BUF_TYPE_A888 color format.
 */
#define  LLM_GET_G_A888_RGB(color) LLM_GET_G_888_RGB(color)
/**
 * To get the 8 bit B component from LLM_MEM_BUF_TYPE_A888 color format.
 */
#define LLM_GET_B_A888_RGB(color) LLM_GET_B_888_RGB(color)
/* End Format: RGB */

/* Start Format: BGR */
/**
 * To get the color in LLM_MEM_BUF_TYPE_A888 from the 8 bit R,G and B.
 */
#define  LLM_GET_COLOR_A888_BGR(R, G, B) LLM_GET_COLOR_888_BGR(R, G, B)
/**
* To get the color in LLM_MEM_BUF_TYPE_A888 from the 8 bit R,G and B.
 */
#define  LLM_GET_COLOR_A888_ABGR(A, R, G, B) ((((LLM_MEM_BUF_TYPE_888)A & 0xff) << 24) | \
											  (((LLM_MEM_BUF_TYPE_888)B & 0xff) << 16) | \
											  (((LLM_MEM_BUF_TYPE_888)G & 0xff) << 8 ) | \
											  (((LLM_MEM_BUF_TYPE_888)R & 0xff)      ))
/**
 * To get the 8 bit B component from LLM_MEM_BUF_TYPE_A888 color format.
 */
#define LLM_GET_B_A888_BGR(color) LLM_GET_B_888_BGR(color)
/**
* To get the 8 bit G component from LLM_MEM_BUF_TYPE_888 color format.
 */
#define LLM_GET_G_A888_BGR(color) LLM_GET_G_888_BGR(color)
/**
* To get the 8 bit R component from LLM_MEM_BUF_TYPE_888 color format.
 */
#define LLM_GET_R_A888_BGR(color) LLM_GET_R_888_BGR(color)
/* End Format: BGR */
/* End Layout: R8G8B8 */


/* Start Layout: R6G6B6 */
#define LLM_MEM_BUF_TYPE_666  uint32
/* Start Format: RGB */
/**
 * To get the color in LLM_MEM_BUF_TYPE_666 from the 8 bit R,G and B.
 */
#define LLM_GET_COLOR_666_RGB(R, G, B) ((((LLM_MEM_BUF_TYPE_666)R & 0xfc) << 10) | \
										(((LLM_MEM_BUF_TYPE_666)G & 0xfc) << 4 ) | \
										(((LLM_MEM_BUF_TYPE_666)B & 0xfc) >> 2 ))
/**
 * To get the 8 bit R component from LLM_MEM_BUF_TYPE_666 color format.
 */
#define LLM_GET_R_666_RGB(color) (((color) >> 10) & 0xfc)
/**
 * To get the 8 bit G component from LLM_MEM_BUF_TYPE_666 color format.
 */
#define LLM_GET_G_666_RGB(color) (((color) >> 4 ) & 0xfc)
/**
 * To get the 8 bit B component from LLM_MEM_BUF_TYPE_666 color format.
 */
#define LLM_GET_B_666_RGB(color) (((color) << 2 ) & 0xfc)
/* End Format: RGB */

/* Start Format: BGR */
/**
 * To get the color in LLM_MEM_BUF_TYPE_666 from the 8 bit R,G and B.
 */
#define LLM_GET_COLOR_666_BGR(R, G, B) ((((LLM_MEM_BUF_TYPE_666)B & 0xfc) << 10) | \
										(((LLM_MEM_BUF_TYPE_666)G & 0xfc) << 4 ) | \
										(((LLM_MEM_BUF_TYPE_666)R & 0xfc) >> 2 ))

/**
 * To get the 8 bit B component from LLM_MEM_BUF_TYPE_666 color format.
 */
#define LLM_GET_B_666_BGR(color) (((color) >> 10) & 0xfc)

/**
 * To get the 8 bit G component from LLM_MEM_BUF_TYPE_666 color format.
 */
#define LLM_GET_G_666_BGR(color) (((color) >> 4 ) & 0xfc)

/**
 * To get the 8 bit R component from LLM_MEM_BUF_TYPE_666 color format.
 */
#define LLM_GET_R_666_BGR(color) (((color) << 2 ) & 0xfc)
/* End Format: BGR */
/* End Format: R6G6B6 */

/* Start Layout: R5G6B5 */
#define LLM_MEM_BUF_TYPE_565  uint16
/* Start Format: RGB */
/**
 * To get the color in LLM_MEM_BUF_TYPE from the 8 bit R,G and B.
 */
#define LLM_GET_COLOR_565_RGB(R, G, B) ((((LLM_MEM_BUF_TYPE_565)R & 0xf8) << 8 ) | \
										(((LLM_MEM_BUF_TYPE_565)G & 0xfc) << 3 ) | \
										(((LLM_MEM_BUF_TYPE_565)B & 0xf8) >> 3 ))
/**
 * To get the 8 bit R component from LLM_MEM_BUF_TYPE_565 color format.
 */
#define LLM_GET_R_565_RGB(color) (((color) >> 8 ) & 0xf8)
/**
 * To get the 8 bit G component from LLM_MEM_BUF_TYPE_565 color format.
 */
#define LLM_GET_G_565_RGB(color) (((color) >> 3 ) & 0xfc)
/**
 * To get the 8 bit B component from LLM_MEM_BUF_TYPE_565 color format.
 */
#define LLM_GET_B_565_RGB(color) (((color) << 3 ) & 0xf8)
/* End Format: RGB */

/* Start Format: BGR */
/**
 * To get the color in LLM_MEM_BUF_TYPE_565 from the 8 bit R,G and B.
 */
#define LLM_GET_COLOR_565_BGR(R, G, B) ((((LLM_MEM_BUF_TYPE_565)B & 0xf8) << 8 ) | \
										(((LLM_MEM_BUF_TYPE_565)G & 0xfc) << 3 ) | \
										(((LLM_MEM_BUF_TYPE_565)R & 0xf8) >> 3 ))
/**
 * To get the 8 bit B component from LLM_MEM_BUF_TYPE_565 color format.
 */
#define LLM_GET_B_565_BGR(color) (((color) >> 8 ) & 0xf8)
/**
 * To get the 8 bit G component from LLM_MEM_BUF_TYPE_565 color format.
 */
#define LLM_GET_G_565_BGR(color) (((color) >> 3 ) & 0xfc)
/**
 * To get the 8 bit R component from LLM_MEM_BUF_TYPE_565 color format.
 */
#define LLM_GET_R_565_BGR(color) (((color) << 3 ) & 0xf8)
/* End Format: BGR */
/* End Format: R5G6B5 */

/* Start Layout: R5G5B5 */
#define LLM_MEM_BUF_TYPE_555  uint16
/* Start Format: RGB */
/**
 * To get the color in LLM_MEM_BUF_TYPE_555 from the 8 bit R,G and B.
 */
#define LLM_GET_COLOR_555_RGB(R, G, B) ((((LLM_MEM_BUF_TYPE_555)R & 0xf8) << 7 ) | \
										(((LLM_MEM_BUF_TYPE_555)G & 0xf8) << 2 ) | \
										(((LLM_MEM_BUF_TYPE_555)B & 0xf8) >> 3 ))
/**
 * To get the 8 bit R component from LLM_MEM_BUF_TYPE_555 color format.
 */
#define LLM_GET_R_555_RGB(color) (((color) >> 7 ) & 0xf8)
/**
 * To get the 8 bit G component from LLM_MEM_BUF_TYPE_555 color format.
 */
#define LLM_GET_G_555_RGB(color) (((color) >> 2 ) & 0xf8)
/**
 * To get the 8 bit B component from LLM_MEM_BUF_TYPE_555 color format.
 */
#define LLM_GET_B_555_RGB(color) (((color) << 3 ) & 0xf8)
/* End Format: RGB */

/* Start Format: BGR */
/**
 * To get the color in LLM_MEM_BUF_TYPE_555 from the 8 bit R,G and B.
 */
#define LLM_GET_COLOR_555_BGR(R, G, B) ((((LLM_MEM_BUF_TYPE_555)B & 0xf8) << 7 ) | \
										(((LLM_MEM_BUF_TYPE_555)G & 0xf8) << 2 ) | \
										(((LLM_MEM_BUF_TYPE_555)R & 0xf8) >> 3 ))
/**
 * To get the 8 bit B component from LLM_MEM_BUF_TYPE_555 color format.
 */
#define LLM_GET_B_555_BGR(color) (((color) >> 7 ) & 0xf8)
/**
 * To get the 8 bit G component from LLM_MEM_BUF_TYPE_555 color format.
 */
#define LLM_GET_G_555_BGR(color) (((color) >> 2 ) & 0xf8)
/**
 * To get the 8 bit R component from LLM_MEM_BUF_TYPE_555 color format.
 */
#define LLM_GET_R_555_BGR(color) (((color) << 3 ) & 0xf8)
/* End Format: BGR */
/* End Format: R5G5B5 */

/* Start Layout: R3G3B2 */
#define LLM_MEM_BUF_TYPE_332  uint8
/* Start Format: RGB */
/**
 * To get the color in LLM_MEM_BUF_TYPE_332 from the 8 bit R,G and B.
 */
#define LLM_GET_COLOR_332_RGB(R, G, B) ((((LLM_MEM_BUF_TYPE_332)R & 0xe0)      ) | \
										(((LLM_MEM_BUF_TYPE_332)G & 0xe0) >> 3 ) | \
										(((LLM_MEM_BUF_TYPE_332)B & 0xc0) >> 6 ))
/**
 * To get the 8 bit R component from LLM_MEM_BUF_TYPE_332 color format.
 */
#define LLM_GET_R_332_RGB(color) (((color)      ) & 0xe0)
/**
 * To get the 8 bit G component from LLM_MEM_BUF_TYPE_332 color format.
 */
#define LLM_GET_G_332_RGB(color) (((color) << 3 ) & 0xe0)
/**
 * To get the 8 bit B component from LLM_MEM_BUF_TYPE_332 color format.
 */
#define LLM_GET_B_332_RGB(color) (((color) << 6 ) & 0xc0)
/* End Format: RGB */

/* Start Format: BGR */
/**
 * To get the color in LLM_MEM_BUF_TYPE_332 from the 8 bit R,G and B.
 */
#define LLM_GET_COLOR_332_BGR(R, G, B) ((((LLM_MEM_BUF_TYPE_332)B & 0xc0)      ) | \
										(((LLM_MEM_BUF_TYPE_332)G & 0xe0) >> 2 ) | \
										(((LLM_MEM_BUF_TYPE_332)R & 0xe0) >> 5 ))
/**
 * To get the 8 bit B component from LLM_MEM_BUF_TYPE_332 color format.
 */
#define LLM_GET_B_332_BGR(color) (((color)      ) & 0xc0)
/**
 * To get the 8 bit G component from LLM_MEM_BUF_TYPE_332 color format.
 */
#define LLM_GET_G_332_BGR(color) (((color) << 2 ) & 0xe0)
/**
 * To get the 8 bit R component from LLM_MEM_BUF_TYPE_332 color format.
 */
#define LLM_GET_R_332_BGR(color) (((color) << 5 ) & 0xe0)
/* End Format: BGR */
/* End Format: R3G3B2 */

/* Start Layout: R3G2B3 */
#define LLM_MEM_BUF_TYPE_323  uint8
/* Start Format: RGB */
/**
 * To get the color in LLM_MEM_BUF_TYPE_323 from the 8 bit R,G and B.
 */
#define LLM_GET_COLOR_323_RGB(R, G, B) ((((LLM_MEM_BUF_TYPE_323)R & 0xe0)      ) | \
										(((LLM_MEM_BUF_TYPE_323)G & 0xc0) >> 3 ) | \
										(((LLM_MEM_BUF_TYPE_323)B & 0xe0) >> 5 ))
/**
 * To get the 8 bit R component from LLM_MEM_BUF_TYPE_323 color format.
 */
#define LLM_GET_R_323_RGB(color) (((color)      ) & 0xe0)
/**
 * To get the 8 bit G component from LLM_MEM_BUF_TYPE_323 color format.
 */
#define LLM_GET_G_323_RGB(color) (((color) << 3 ) & 0xc0)
/**
 * To get the 8 bit B component from LLM_MEM_BUF_TYPE_323 color format.
 */
#define LLM_GET_B_323_RGB(color) (((color) << 5 ) & 0xe0)
/* End Format: RGB */

/* Start Format: BGR */
/**
 * To get the color in LLM_MEM_BUF_TYPE_323 from the 8 bit R,G and B.
 */
#define LLM_GET_COLOR_323_BGR(R, G, B) ((((LLM_MEM_BUF_TYPE_323)B & 0xe0)      ) | \
										(((LLM_MEM_BUF_TYPE_323)G & 0xc0) >> 3 ) | \
										(((LLM_MEM_BUF_TYPE_323)R & 0xe0) >> 5 ))
/**
 * To get the 8 bit B component from LLM_MEM_BUF_TYPE_323 color format.
 */
#define LLM_GET_B_323_BGR(color) (((color)      ) & 0xe0)
/**
 * To get the 8 bit G component from LLM_MEM_BUF_TYPE_323 color format.
 */
#define LLM_GET_G_323_BGR(color) (((color) << 3 ) & 0xc0)
/**
 * To get the 8 bit R component from LLM_MEM_BUF_TYPE_323 color format.
 */
#define LLM_GET_R_323_BGR(color) (((color) << 5 ) & 0xe0)
/* End Format: BGR */
/* End Format: R3G2B3 */

/* Start Layout: R2G3B3 */
#define LLM_MEM_BUF_TYPE_233  uint8
/* Start Format: RGB */
/**
 * To get the color in LLM_MEM_BUF_TYPE_233 from the 8 bit R,G and B.
 */
#define LLM_GET_COLOR_233_RGB(R, G, B) ((((LLM_MEM_BUF_TYPE_233)R & 0xc0)      ) | \
										(((LLM_MEM_BUF_TYPE_233)G & 0xe0) >> 2 ) | \
										(((LLM_MEM_BUF_TYPE_233)B & 0xe0) >> 5 ))
/**
 * To get the 8 bit R component from LLM_MEM_BUF_TYPE_233 color format.
 */
#define LLM_GET_R_233_RGB(color) (((color)      ) & 0xc0)
/**
 * To get the 8 bit G component from LLM_MEM_BUF_TYPE_233 color format.
 */
#define LLM_GET_G_233_RGB(color) (((color) << 2 ) & 0xe0)
/**
 * To get the 8 bit B component from LLM_MEM_BUF_TYPE_233 color format.
 */
#define LLM_GET_B_233_RGB(color) (((color) << 5 ) & 0xe0)
/* End Format: RGB */

/* Start Format: BGR */
/**
 * To get the color in LLM_MEM_BUF_TYPE_233 from the 8 bit R,G and B.
 */
#define LLM_GET_COLOR_233_BGR(R, G, B) ((((LLM_MEM_BUF_TYPE_233)B & 0xe0)      ) | \
										(((LLM_MEM_BUF_TYPE_233)G & 0xe0) >> 3 ) | \
										(((LLM_MEM_BUF_TYPE_233)R & 0xc0) >> 6 ))
/**
 * To get the 8 bit B component from LLM_MEM_BUF_TYPE_233 color format.
 */
#define LLM_GET_B_233_BGR(color) (((color)      ) & 0xe0)

/**
 * To get the 8 bit G component from LLM_MEM_BUF_TYPE_233 color format.
 */
#define LLM_GET_G_233_BGR(color) (((color) << 3 ) & 0xe0)

/**
 * To get the 8 bit R component from LLM_MEM_BUF_TYPE_233 color format.
 */
#define LLM_GET_R_233_BGR(color) (((color) << 6 ) & 0xc0)
/* End Format: BGR */
/* End Format: R2G3B3 */


/* The macro makes the color from RGB components based on the current RGB or
 * BGR format plus the color components depths. So major of the complexity is
 * covered in this macro. Only one statement will be executed in these several
 * statements. This cud have been done by creating one blending macro for RGB
 * and for BGR just call the blending macro with BGR. But for clarity i have put
 * two sections */

#if defined(LLM_COLOR_LAYOUT_R8G8B8) || defined(LLM_COLOR_LAYOUT_A8R8G8B8)

#if defined(LLM_COLOR_FORMAT_RGB)
#define LLM_GET_COLOR	LLM_GET_COLOR_888_RGB
#define LLM_GET_R		LLM_GET_R_888_RGB
#define LLM_GET_G		LLM_GET_G_888_RGB
#define LLM_GET_B		LLM_GET_B_888_RGB
#ifdef LLM_COLOR_LAYOUT_A8R8G8B8
#define LLM_GET_A		LLM_GET_A_888_ARGB
#endif /* LLM_COLOR_LAYOUT_A8R8G8B8 */
#elif defined(LLM_COLOR_FORMAT_BGR)
#define LLM_GET_COLOR	LLM_GET_COLOR_888_BGR
#define LLM_GET_R		LLM_GET_R_888_BGR
#define LLM_GET_G		LLM_GET_G_888_BGR
#define LLM_GET_B		LLM_GET_B_888_BGR
#ifdef LLM_COLOR_LAYOUT_A8R8G8B8
#define LLM_GET_A		LLM_GET_A_888_ABGR
#endif /* LLM_COLOR_LAYOUT_A8R8G8B8 */
#endif /* LLM_COLOR_FORMAT_RGB */
#elif defined(LLM_COLOR_LAYOUT_R6G6B6)

#if defined(LLM_COLOR_FORMAT_RGB)
#define LLM_GET_COLOR	LLM_GET_COLOR_666_RGB
#define LLM_GET_R		LLM_GET_R_666_RGB
#define LLM_GET_G		LLM_GET_G_666_RGB
#define LLM_GET_B		LLM_GET_B_666_RGB
#elif defined(LLM_COLOR_FORMAT_BGR)
#define LLM_GET_COLOR	LLM_GET_COLOR_666_BGR
#define LLM_GET_R		LLM_GET_R_666_BGR
#define LLM_GET_G		LLM_GET_G_666_BGR
#define LLM_GET_B		LLM_GET_B_666_BGR
#endif /* LLM_COLOR_FORMAT_RGB */

#elif defined(LLM_COLOR_LAYOUT_R5G6B5)

#if defined(LLM_COLOR_FORMAT_RGB)
#define LLM_GET_COLOR	LLM_GET_COLOR_565_RGB
#define LLM_GET_R		LLM_GET_R_565_RGB
#define LLM_GET_G		LLM_GET_G_565_RGB
#define LLM_GET_B		LLM_GET_B_565_RGB
#elif defined(LLM_COLOR_FORMAT_BGR)
#define LLM_GET_COLOR	LLM_GET_COLOR_565_BGR
#define LLM_GET_R		LLM_GET_R_565_BGR
#define LLM_GET_G		LLM_GET_G_565_BGR
#define LLM_GET_B		LLM_GET_B_565_BGR
#endif /* LLM_COLOR_FORMAT_RGB */

#elif defined(LLM_COLOR_LAYOUT_R5G5B5)

#if defined(LLM_COLOR_FORMAT_RGB)
#define LLM_GET_COLOR	LLM_GET_COLOR_555_RGB
#define LLM_GET_R		LLM_GET_R_555_RGB
#define LLM_GET_G		LLM_GET_G_555_RGB
#define LLM_GET_B		LLM_GET_B_555_RGB
#elif defined(LLM_COLOR_FORMAT_BGR)
#define LLM_GET_COLOR	LLM_GET_COLOR_555_BGR
#define LLM_GET_R		LLM_GET_R_555_BGR
#define LLM_GET_G		LLM_GET_G_555_BGR
#define LLM_GET_B		LLM_GET_B_555_BGR
#endif /* LLM_COLOR_FORMAT_RGB */

#elif defined(LLM_COLOR_LAYOUT_R3G3B2)

#if defined(LLM_COLOR_FORMAT_RGB)
#define LLM_GET_COLOR	LLM_GET_COLOR_332_RGB
#define LLM_GET_R		LLM_GET_R_332_RGB
#define LLM_GET_G		LLM_GET_G_332_RGB
#define LLM_GET_B		LLM_GET_B_332_RGB
#elif defined(LLM_COLOR_FORMAT_BGR)
#define LLM_GET_COLOR	LLM_GET_COLOR_332_BGR
#define LLM_GET_R		LLM_GET_R_332_BGR
#define LLM_GET_G		LLM_GET_G_332_BGR
#define LLM_GET_B		LLM_GET_B_332_BGR
#endif /* LLM_COLOR_FORMAT_RGB */

#elif defined(LLM_COLOR_LAYOUT_R3G2B3)

#if defined(LLM_COLOR_FORMAT_RGB)
#define LLM_GET_COLOR	LLM_GET_COLOR_323_RGB
#define LLM_GET_R		LLM_GET_R_323_RGB
#define LLM_GET_G		LLM_GET_G_323_RGB
#define LLM_GET_B		LLM_GET_B_323_RGB
#elif defined(LLM_COLOR_FORMAT_BGR)
#define LLM_GET_COLOR	LLM_GET_COLOR_323_BGR
#define LLM_GET_R		LLM_GET_R_323_BGR
#define LLM_GET_G		LLM_GET_G_323_BGR
#define LLM_GET_B		LLM_GET_B_323_BGR
#endif /* LLM_COLOR_FORMAT_RGB */

#elif defined(LLM_COLOR_LAYOUT_R2G3B3)

#if defined(LLM_COLOR_FORMAT_RGB)
#define LLM_GET_COLOR	LLM_GET_COLOR_233_RGB
#define LLM_GET_R		LLM_GET_R_233_RGB
#define LLM_GET_G		LLM_GET_G_233_RGB
#define LLM_GET_B		LLM_GET_B_233_RGB
#elif defined(LLM_COLOR_FORMAT_BGR)
#define LLM_GET_COLOR	LLM_GET_COLOR_233_BGR
#define LLM_GET_R		LLM_GET_R_233_BGR
#define LLM_GET_G		LLM_GET_G_233_BGR
#define LLM_GET_B		LLM_GET_B_233_BGR
#endif /* LLM_COLOR_FORMAT_RGB */

#endif /* LLM_COLOR_LAYOUT_R8G8B8 || LLM_COLOR_LAYOUT_A8R8G8B8 */

#endif /* ENABLE_LLE */
#endif /* __OTFCOLOR_HEADER__ */


/*********************** R E V I S I O N   H I S T O R Y **********************
 *
 *    $Header: /home/archive/Panorama/layout/LLManager/hdr/otfcolor.h,v 1.14 2007/11/12 04:47:57 himanshu Exp $
 *
 *    $Log: otfcolor.h,v $
 *    Revision 1.14  2007/11/12 04:47:57  himanshu
 *    Making changes to Pano files according to the new Include system in FF.
 *
 *    Revision 1.13  2007/09/13 09:18:14  ljoshi
 *    Adding support to make LLConfig.h file name configurable.
 *
 *    Revision 1.12  2007/09/13 06:40:10  ljoshi
 *    Adding support for configurable header names.
 *
 *    Revision 1.11  2007/09/10 10:16:49  ljoshi
 *    Adding new line to end of file.
 *
 *    Revision 1.10  2007/06/15 07:25:53  ljoshi
 *    Adding support for dynamic ARGB
 *
 *    Revision 1.9  2007/04/18 04:57:55  ljoshi
 *    Support for A8R8G8B8 color format
 *
 *    Revision 1.8  2007/02/13 06:41:31  ljoshi
 *    Initial CVS Version
 *
 *
******************************************************************************/
