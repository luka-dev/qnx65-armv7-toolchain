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
    \file font_msg.h
    \brief font server - messaging definitions.
*/

#ifndef __FONTMSG_H_INCLUDED
#define __FONTMSG_H_INCLUDED

#include <sys/types.h>
#include <inttypes.h>
#include <font_api.h>
#include <font_types.h>

#if defined(__QNXNTO__)
    #include <_pack64.h>
#else
    #if __WATCOMC__ > 1000
        #pragma pack(__push,1)
    #else
        #pragma pack(1)
    #endif
#endif

#ifdef __cplusplus
extern "C" {
#endif


#define PHFONT_MSG_NEWFONTS					1	/*!< \internal Reload 'fontdir' and 'fontext' files */
#define PHFONT_MSG_LOAD						2	/*!< \internal Load metrics/image data for a font */
#define PHFONT_MSG_LIST						3	/*!< \internal List suitable fonts */
#define PHFONT_MSG_QUERY					4	/*!< \internal Query attributes of a font */
#define PHFONT_MSG_EXTENT					5	/*!< \internal Calculate extent of a string */
#define PHFONT_MSG_CEXTENT1					6	/*!< \internal Calculate multi-part extent of a string */
#define PHFONT_MSG_RENDER					7	/*!< \internal Render bitmap of a string */
#define PHFONT_MSG_SHMEM					8	/*!< \internal Create shmem for bitmap transfer */
#define PHFONT_MSG_GLYPH					9	/*!< \internal Return character metrics and bitmap */
#define PHFONT_MSG_LOCAL1					10	/*!< \internal Return character metrics pre-info */
#define PHFONT_MSG_LOCAL2					11	/*!< \internal Return character metrics info */
#define PHFONT_MSG_ANTIALIAS				12	/*!< \internal Set global antialias mode */
#define PHFONT_MSG_RENDER2					13	/*!< \internal Continuation of string bitmap render */
#define PHFONT_MSG_CEXTENT2					14	/*!< \internal Continuation of multi-part extent */
#define PHFONT_MSG_WEXTENT					15	/*!< \internal Calculate extent of widechar string */
#define PHFONT_MSG_WRENDER					16	/*!< \internal Render bitmap of a widechar string */
#define PHFONT_MSG_WRENDER2					17	/*!< \internal Continuation of wide string bitmap render */
#define PHFONT_MSG_FEXTENT					18	/*!< \internal Calculate extent of a string (fract) */
#define PHFONT_MSG_FRENDER					19	/*!< \internal Render bitmap of a string (fract) */
#define PHFONT_MSG_FRENDER2					20	/*!< \internal Continuation of string bitmap render (fract) */
#define PHFONT_MSG_GET_PEN_POS				21	/*!< \internal Request the penx position after all provided indices. */
#define PHFONT_MSG_GET_FRACT_PEN_POS		22	/*!< \internal Request the penx position after all provided indices (fract). */
#define PHFONT_MSG_GET_PEN_POS_WIDE			23	/*!< \internal Request the penx position after all provided indices. (wide) */
#define PHFONT_MSG_GET_FRACT_PEN_POS_WIDE	24	/*!< \internal Request the penx position after all provided indices (fract). (wide) */
#define PHFONT_MSG_FRENDER_WIDE				25	/*!< \internal Render fractional wide characters. */
#define PHFONT_MSG_FEXTENT_WIDE 			26	/*!< \internal Extent fractional wide characters. */
#define PHFONT_MSG_FRENDER_WIDE2			27	/*!< \internal Render fractional wide characters (Continuation). */
#define PHFONT_MSG_STAT_PHF					28	/*!< \internal Get cache stats for PHF fonts. */
#define PHFONT_MSG_STAT_PFR					29	/*!< \internal Get cache stats for PFR fonts. */
#define PHFONT_MSG_STAT_TTF					30	/*!< \internal Get cache stats for TTF fonts. */
#define PHFONT_MSG_LOCAL2_V20               31  /*!< \internal Return character metrics info (v2.0) */
#define PHFONT_MSG_LIST_CONT				32	/*!< \internal List suitable fonts (continued) */
#define PHFONT_MSG_QUERY_INFO				33  /*!< \internal Query font which handles scalable fonts correctly. */
#define PHFONT_MSG_EXTENT_CLIP				34  /*!< \internal Extent text to clip rectange. */
#define	PHFONT_MSG_QUERY_DESCRIPTION_INFO	35	/*!< \internal Just like the PHFONT_MSG_QUERY_INFO message, but uses font description instead of font stem. */

#define	PHFONT_MSG_DYNAMIC_LOAD				0x1000 /*!< \internal Dynamically install a font file. */
#define PHFONT_MSG_DYNAMIC_UNLOAD			0x1001 /*!< \internal Dynamically uninstall a font file. */
#define PHFONT_MSG_DYNAMIC_ID				0x1002 /*!< \internal Locate the dynamic ID of this filename. */
#define PHFONT_MSG_DYNAMIC_EXIST			0x1003 /*!< \internal Has a file already been loaded? */

#define PHFONT_MSG_OUTLINE_GLYPH			0x3000 /*!< \internal Provide the outline of a glyph. */

#define PHFONT_MSG_MAP						0x4000 /*!< \internal Provide font mapping information. */
#define PHFONT_MSG_MAP_MODIFY				0x4001 /*!< \internal Modify the particular font map entry. */
#define PHFONT_MSG_MAP_ADD					0x4002 /*!< \internal Add a new mapping rule. */
#define PHFONT_MSG_OKEY_ADD					0x4003 /*!< \internal Add a new keyword to identify Oriental fonts. */
#define PHFONT_MSG_OKEY_REMOVE				0x4004 /*!< \internal Remove a keyword used to identify Oriental fonts. */

#define PHFONT_MSG_CFG						0x5000 /*!< \internal Dynamic configuration information. */
#define PHFONT_MSG_CFG_MODIFY				0x5001 /*!< \internal Dynamically modify a configuration option. */
#define PHFONT_MSG_PREFERRED_EXTENSION		0x5002 /*!< \internal The preferred font to use with specific Unicode range. */
#define PHFONT_MSG_RETRIEVE_PREFERRED		0x5003 /*!< \internal Retrieve the preferred font being used with a specific Unicode range. */
#define PHFONT_MSG_OPTION_LIST				0x5004 /*!< \internal Retrieve option list per specified engine. */
#define PHFONT_MSG_SET_OPTION				0x5005 /*!< \internal Set option per specified engine. */
#define PHFONT_MSG_GET_OPTION				0x5006 /*!< \internal Get option per specified engine. */
#define PHFONT_MSG_SET_OPTION_NAME			0x5007 /*!< \internal Set option per specified engine for particular option name (dll mode). */
#define PHFONT_MSG_CFG_MODIFY_NAME			0x5008 /*!< \internal Dynamically modify a configuration option for particular option name (dll mode). */

#define PHFONT_MSG_FONT_TYPE				0x6000 /*!< \internal Return the "type" of font, i.e. TrueType, Stroke, Bitmap, as a string. */
#define PHFONT_MSG_INSTALL_STAMP			0x6001 /*!< \internal Install stamp, internal use. */

#define PHFONT_MSG_EXTENT_TEXT				0x7000
#define PHFONT_MSG_RENDER_TEXT				0x7001
#define PHFONT_MSG_PEN_POS					0x7002
#define PHFONT_MSG_EXTENT_TEXT_16DOT16		0x7003

#define PHFONT_MSG_GLYPH_INDEX				0x8000
#define PHFONT_MSG_OT_DATA					0x8001
#define PHFONT_MSG_GLYPH_RUN				0x8002

/** \internal
 *  Extent/Render data.
 *  - Description : Extent/Render data.
 */
union ext_rend
{	pf_rect_t			extent; /*!<Extent data. */
	pf_rect_16dot16_t	extent16dot16; /*!<Extent data. */
	FontRender			render; /*!<Render data. */
};

/** \internal
 *  Font server message header.
 *  - Description : Message header used at the beginning
 *                  of all font messages.
 */
typedef struct {
	msg_t		type; /*!<Always _PHFONT_REQUEST */
	msg_t		subtype; /*!<One of PHFONT_MSG_* */
	int16_t		fd; /*!<File descriptor for this connection. */
	int16_t		strlen; /*!<Length in bytes of string to process. */

	int16_t n; /*!<Current position of multi-pass processing. */
	int16_t spare; /*!<Reserved for future use. */
	int32_t symbol; /*!<Code point to process. */
	int32_t xscale; /*!<Fractional horizontal point size. */
    int32_t yscale; /*!<Fractional vertical point size. */
	uint32_t flags; /*!<Flags. */
    uint32_t flags2; /*!<Flags. */
    union ext_rend size;	
	uint32_t x_dpi; /*/Horizontal resolution. */
    uint32_t y_dpi; /*/Vertical resolution. */
    int32_t bitmap_size; /*!<Size of message passed bitmap. */
	uint32_t spare_int[3]; /*!<Reserved for future use. */
	FontName font; /*!<Font stem name. */
} PfServerMessage;

#define PHFONT_MAX_XFER_SZ 		(4096 - sizeof(PfServerMessage))
#define PHFONT_MAX_WIDTHS  		(PHFONT_MAX_XFER_SZ / sizeof(FontWidths))
#define PHFONT_MAX_WIDTHS_LONG 	((PHFONT_MAX_WIDTHS / 2) - 1)

#define PHFONT_MAX_STRLEN   	(PHFONT_MAX_XFER_SZ / sizeof(char))
#define PHFONT_MAX_FONTLIST 	(PHFONT_MAX_XFER_SZ / sizeof(FontDetails))
#define PHFONT_MAX_GLYPH    	(PHFONT_MAX_XFER_SZ / sizeof(unsigned char))

#ifdef __cplusplus
};
#endif

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
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/font/public/font_msg.h $ $Rev: 224585 $" )
#endif
