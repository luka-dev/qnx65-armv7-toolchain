/*
 * LLMTypes.h
 * $Header: /home/archive/Panorama/layout/LLManager/hdr/LLMTypes.h,v 1.29 2009/07/10 12:35:24 ljoshi Exp $
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

#ifndef __LLMTYPES_HEADER__
#define __LLMTYPES_HEADER__

#ifndef LLM_LLCONFIG_HEADER
#include "LLConfig.h"
#else
#include LLM_LLCONFIG_HEADER
#endif /* LLM_LLCONFIG_HEADER */
#include FF_DTYPES_HEADER
#include FF_SYSHEAD_HEADER

#ifdef ENABLE_LLM_UNICODE32
typedef uint32 LLMUnicode;
#else
typedef uint16 LLMUnicode;
#endif /* ENABLE_LLM_UNICODE32 */

typedef LLMUnicode LLMGid;

/**
 * The LLMFontStyle enumeration specifies several formatting options that you
 * can set for the text to be rendered.
 *
 * @see LLManager::setStyle
 * @see LLManager::getStyle
 */
typedef enum
{
	/**
	 * Has the highest priority, removes all the styles and the text will be
	 * rendered without any style or filters.
	 */
	LLMFontPlain              = 0, /* If nothing is set then its plain */
	/**
	 * Italicizes the text in the current run.
	 */
	LLMFontItalic             = 1 << 0,
	/**
	 * Applies boldface type to the text in the current run.
	 */
	LLMFontBold               = 1 << 1,

/* @cond */
#ifndef LLM_COLOR_FORMAT_MONO
/* @endcond */
#ifdef ENABLE_COLORBORDERS
	/**
	* Draws a line marking the outer contours of
	* the text in the current run.
	*/
	LLMFontBordered           = 1 << 2,
#endif /* ENABLE_COLORBORDERS */
#ifdef ENABLE_T2K_TV_EFFECTS
	LLMFontLeftShadowed       = 1 << 3,
	/**
	* Applies a visual effect which looks like the
	* shadow of an object at the right side for the
	* text in the current run.
	*/
	LLMFontRightShadowed      = 1 << 4,
	/**
	 * Creates a three dimensional pattern for the
	 * text in the current run.
	 */
	LLMFontEmbossed           = 1 << 5,
	/**
	 * Creates a carved/etched out style for the
	 * text in the current run.
	 */
	LLMFontEngraved           = 1 << 6,
#endif /* ENABLE_T2K_TV_EFFECTS */
/* @cond */
#endif /* LLM_COLOR_FORMAT_MONO */
/* @endcond */
#ifdef ENABLE_OUTLINEFILTER
	/**
	* Creates a carved/etched out style for the
	* text in the current run.
	*/
	LLMFontOutlined           = 1 << 7,
#endif /* ENABLE_OUTLINEFILTER */

	/*
	 * Implementation wise the enums below do not affect the cache tag
	 */
	/**
	* Underlines the text in the current run.
	*/
	LLMFontUnderlined         = 1 << 8,
	/**
	* Draws a line immediately above the text in
	* the current run.
	*/
	LLMFontOverlined          = 1 << 9,
	/**
	* Draws a horizontal line through the center
	* of the text in the current run.
	*/
	LLMFontStrikethrough      = 1 << 10,

	/* This should be the last one, Should not be used by the clients.*/
	LLMMaxFontStyles			= 1 << 11
}LLMFontStyle;

/* @cond */
#ifndef LLM_COLOR_FORMAT_MONO
/* @endcond */
/**
 * Antialiasing Enums
 *
 * @see LLManager::setAntialiasMode
 * @see LLManager::getAntialiasMode
 */
typedef enum
{
	/* For monochrome bitmap output. This should not be thought and black and white
	 * output, but a output which has uniform back and fore color */
	LLMNoAntialias = 0,

	/* Antilaised font, ideal for monitors etc */
	LLMGrayScaleAlias

/* @cond */
#ifndef LLM_COLOR_FORMAT_GRAY
/* @endcond */
	/* Antialiasing that works great on LCDs */
#ifdef ENABLE_LCD_SUPPORT
	/* The generic antialias. Its suggested to use the LCD orientation specific subpixel
	 * rendering methods */
	, LLMSubPixelAlias
#endif /* ENABLE_LCD_SUPPORT */
/* @cond */
#endif /* LLM_COLOR_FORMAT_GRAY */
/* @endcond */

}LLMAlias;

/* @cond */
#ifndef LLM_COLOR_FORMAT_GRAY
/* @endcond */

/**
 * This enum is used to avoid the extra methods to retrieve the
 * colors for Foreground, Background and Outline.
 */
typedef enum
{
	/**
	 * The foreground color.
	 */
	LLMForeground,

	/**
	 * The background color.
	 */
	LLMBackground,

	/**
	 * Color for the glyph border.
	 */
	LLMOutline

}LLMComponent;

/**
 * This enum is made to avoid the extra methods to retrieve the
 * colors for Foreground, Background and Outline
 */
typedef enum
{
	LLMRed,
	LLMGreen,
	LLMBlue
}LLMColorComponent;

/* @cond */
#endif /* LLM_COLOR_FORMAT_GRAY */
/* @endcond */
/* @cond */
#endif /* LLM_COLOR_FORMAT_MONO */
/* @endcond */

/**
 * This enum should be used to get the font info from the current
 * font, while using getFontInfo API.
 *
 * @see LLManager::getFontInfo
 */
typedef enum
{
	/**
	 * Refers to the copyright notice information
	 * in the font.
	 */
	LLMCopyrightNotice,		    /* 0 */
	/**
	 * Refers to the font family name in the font.
	 */
	LLMFontFamilyName,			/* 1 */
	/**
	 * Refers to the Sub Family name in the font,
	 * as present in the Roman/Latin in the
	 * detailed name.
	 */
	LLMFontSubfamilyName,		/* 2 */
	/**
	 * Refers to the unique identifier that is
	 * attached with the font.
	 */
	LLMUniqueFontIdentifier,	/* 3 */
	/**
	 * Refers to the full font name, which includes
	 * the family name and the sub family name.
	 */
	LLMFullFontName,			/* 4 */
	/**
	 * Refers to the version of the software.
	 */
	LLMFontVersionString,		/* 5 */
	/**
	 * Refers to the postscript version name of the font.
	 */
	LLMFontPostscriptName,		/* 6 */
	/**
	 * Refers to the trademark notice.
	 */
	LLMFontTrademark			/* 7 */

}LLMFontInfo;


/**
 * This enum indicates LLManager to use the type of extender
 * if the string exceeds the line.
 *
 * @see LLManager::getLineExtender
 * @see LLManager::setLineExtender
 */
typedef enum
{

	/**
	 * No extender, breaks the word and writes the next char
	 * in next line.
	 */
	LLMNoExtender = 0,

	/**
	 * Adds hyphen before going to next line, which depends
	 * on the availability of hyphen in the font; if its not present'
	 * then the default type of extender scheme that is No Extender is
	 * chosen.
	 */
	LLMHyphenExtender,

	/**
	 * The extender provided by the user; if the Unicode provided by user
	 * doesn't exists in the font then the line extender style will be considered
	 * as NoExtender
	 */
	LLMUserExtender,

	/**
	 * This writes the complete word in the before breaking and if space is not
	 * there for the next word then breaks and goes to next line; if the word is
	 * bigger than length of the area then the default scheme is applied for that
	 * word only.
	 */
	LLMWordExtender

#ifdef ENABLE_USER_LINEBREAK
	/**
	 * This makes possible for the caller to break line according to some predefined 
	 * mechanism; if the extender of this type is registered then a callback is called
	 * pre line break and a number of characters which LLManager should go back and then
	 * break the line is expected
	 */
	, LLMUserCallbackExtender
#endif /* ENABLE_USER_LINEBREAK */
/* @cond */
#ifdef ENABLE_OTF_JSTF
/* @endcond */
	/* @cond */,/* @endcond */
	/**
	 * Jstf table has Extender list, which can be used to specify the extender;
	 * by default the first extender in the list is chosen. The usage of
	 * this extender depends on the following two factors: <br>
	 * o Jstf Table should be present, if not then default scheme is used. <br>
	 * o The extender table should be present in the current setting of
	 *   language and script else the default scheme is used.
	 */
	/* @cond */ , /* @endcond */ LLMJstfExtender
/* @cond */
#endif /* ENABLE_OTF_JSTF */
/* @endcond */


}LLMLineExtender;


/**
 * This enum indicates LLManager to align the line in different ways.
 * This enum should be used to change the line alignment. It should
 * be taken in to consideration even when the extenders are used then
 * too some space is left  and that is also used for alignment.
 *
 * @see LLManager::setLineAlignment
 * @see LLManager::getLineAlignment
 */
typedef enum
{

	/**
	 * By default LLManager renders the line left aligned.
	 */
	LLMLeftAligned,

	/**
	 * Used to make the line right aligned.
	 */
	LLMRightAligned,

	/**
	 * For the central alignment.
	 */
	LLMCenterAligned,

	/**
	 * This enum is special, this enum will make the space left at
	 * the end of the line distributed among all the words. Space left
	 * depends on the type of extenders chosen. OTF files have the
	 * justification table which can also be used for Justification in
	 * case of OTF fonts and the availability of the table. ELse internal
	 * algorithm is used by the LLManager to justify the text. Application
	 * of JSTF table in case of OTF fonts is little bit performance intensive.
	 * So to turn ON the OTF JSTF table application needs to be done through
	 * setJstfJustification API.
	 */
	LLMJustified

} LLMLineAlignment;


/**
 * The indentation enum. Needed to set and get indentation widths.
 *
 * @see LLManager::setIndentValue
 * @see LLManager::getIndentValue
 */
typedef enum
{
	/**
	 * For left side indentation
	 */
	LLMLeftIndent  = 0,

	/**
	 * For right side indentation
	 */
	LLMRightIndent = 1

}LLMIndentEnum;

/**
 * The line style enum. Needed to set and get Line Styles.
 *
 * @see LLManager::setLineStyle
 * @see LLManager::getLineStyle
 */
typedef enum
{
	LLMUnderline  = 0x02,
	LLMStrikethru = 0x04,
	LLMOverline   = 0x06

}LLMLineType;

/**
* The line style enum. Needed to set and get Line Styles.
 *
 * @see LLManager::setLineStyle
 * @see LLManager::getLineStyle
 */
typedef enum
{
	LLMLineStyleSingle = 0x00,
	LLMLineStyleDouble = 0x01,
	LLMLineStyleDotted = 0x02
}LLMLineStyle;

#ifdef ENABLE_TABSTOP
/**
 * Enumeration for TabStop type.
 */
typedef enum
{
	LLMTabstopLeft   = 0,
	LLMTabstopRight  = 1,
	LLMTabstopCenter = 2
}LLMTabstopType;

/**
 * Structure that stores the tabstop value and tabstop type.
 */
typedef struct LLMTabstop_t
{
	/**
	 * The LLMTabstopType type.
	 */
	uint16 type;
	
	/**
	 * Value of the tabstop in pixels.
	 */
	uint16 value;
}LLMTabstop;

#endif /* ENABLE_TABSTOP */

#ifdef LLM_COLOR_FORMAT_CLUT
typedef struct LLMClutStruct_t
{
	/* Thr original clut */
	const uint8 * clutData;
	/* The final palette array */
	const uint8 * paletteData;
	uint16 numColors;
	uint16 numAlpha;
	
}LLMClutStruct;
#endif /* LLM_COLOR_FORMAT_CLUT */

/* LLManager environment */
typedef struct LLMEnvStruct_t
{
	CLIENT_JMPBUF jmpBuf;
	int state;
}LLMEnv;


#ifdef ENABLE_UNICODE_IMAGE_MAPPING
/**
 * The Unicode Image Mapping structure.
 */
typedef struct
{
	/**
	 * The Unicode values that are mapped to the graphic object.
	 */
	LLMUnicode * unicode;
	/**
	 * The number of mapped Unicode values.
	 */
	uint16		 mapCount;
	/**
	 * The image index set by the user.
	 */
	uint16       imageIndex;
	/**
	 * The width of the mapped graphic object.
	 */
	uint16       width;
	/**
	 * The height of the mapped graphic object.
	 */
	uint16       height;
}LLMUnicodeImage;
#endif /* ENABLE_UNICODE_IMAGE_MAPPING */

#ifdef ENABLE_DYNAMIC_BIDI_CONTROL
/**
 * The enumeration to set the text directionality.
 */
typedef enum
{
	/**
	 * Paragraph directionality depends on the first occurrence of any strong RTL or LTR character
	 */
	LLMDefaultBidi,
	/**
	 * No bidirectional behavior is applied to the paragraph text
	 */
	LLMNoBidi,
	/**
	 * Paragraph directionality changes to RTL if any strong RTL character is present
	 */
	LLMForceRtoL,
	/**
	 * Paragraph directionality changes to LTR if any strong LTR character is present
	 */
	LLMForceLtoR
	
}LLMBidiControl;
#endif /* ENABLE_DYNAMIC_BIDI_CONTROL */

#ifndef ENABLE_MILLI_INTERCHAR_SPACE
typedef int16 InterCharSpaceType;
#else
typedef F16Dot16 InterCharSpaceType;
#endif /* ENABLE_MILLI_INTERCHAR_SPACE */

#ifdef ENABLE_FRACTIONAL_SIZE
#define LLM_FONTSIZE_TYPE uint32
#else
#define LLM_FONTSIZE_TYPE uint16
#endif /* ENABLE_FRACTIONAL_SIZE */

typedef struct
{
	/**
	 * String width in pixels.
	 */
	uint16 width;
	/**
	 * String height in pixels.
	 */
	uint16 height;
	/**
	 * Left-side bearing.
	 */
	int16 lsb;
	/**
	 * Advance Width of the string.
	 */
	uint16 aw;
	
	/**
	 * Real ascent of the string.
	 */
	int16 ascent;
	
	/**
	 * Higher ascent value between the real ascent and the ascent value based on the font metrics.
	 */
	int16 fAscent;
	
	/**
	 * Higher height value between the real height and the height based on the font metrics.
	 */
	uint16 fHeight;
	
}LLMStringMetrics;

/**
 * Metrics struct that can be used by the client to get the information about
 * a glyph rendered.
 * @see LLManager::layoutChar
 */
typedef struct
{
	/**
	 * Width of the character.
	 */
	uint16 width;

	/**
	 * Height of the character.
	 */
	uint16 height;

	/**
	 * Advancewidth of the character.
	 */
	uint16 advanceWidth;

	/**
	 * Left-side bearing of the character, which can take a negative value also.
	 */
	int16 leftSideBearing;

	/**
	 * Ascent of the character.
	 */
	uint16 ascent;

	/**
	 * Descent of the character, which can take a negative value also.
	 */
	int16 descent;

}LLMGlyphMetrics;

typedef struct
{
	/**
	 * Left most x co-ordinate of rectangle.
	 */
	uint16 left;
	/**
	 * Top most y co-ordinate of rectangle.
	 */
	uint16 top;
	/**
	 * Right most x co-ordinate of rectangle.
	 */
	uint16 right;
	/**
	 * Bottom y co-ordinate of rectangle.
	 */
	uint16 bottom;
}LLMRect;

#endif /* __LLMTYPES_HEADER__ */


/*********************** R E V I S I O N   H I S T O R Y **********************
 * 
 *    $Header: /home/archive/Panorama/layout/LLManager/hdr/LLMTypes.h,v 1.29 2009/07/10 12:35:24 ljoshi Exp $
 *
 *    $Log: LLMTypes.h,v $
 *    Revision 1.29  2009/07/10 12:35:24  ljoshi
 *    Changes in comments for 5.0 release.
 *
 *    Revision 1.28  2009/03/25 11:43:06  himanshu
 *    Adding Support for Windget/Text On Path feature.
 *
 *    Revision 1.27  2009/03/19 14:24:40  ljoshi
 *    Addition for font wide metrics while in meaure string.
 *
 *    Revision 1.26  2009/02/13 19:09:25  ljoshi
 *    Warnings/Error fix.
 *
 *    Revision 1.25  2009/02/10 12:42:29  ljoshi
 *    Adding support for string height and ascent.
 *
 *    Revision 1.24  2008/11/10 14:25:08  ljoshi
 *    Adding Fractional Size.
 *
 *    Revision 1.23  2008/10/21 10:32:35  ljoshi
 *    Support for interchar space at milli level.
 *
 *    Revision 1.22  2008/09/24 05:37:27  ljoshi
 *    Adding support for runtime bidi control.
 *
 *    Revision 1.21  2008/07/03 09:03:13  himanshu
 *    Adding support for Unicode Image Mapping and Floating Objects.
 *
 *    Revision 1.20  2008/05/16 11:40:31  ljoshi
 *    Making frst 2 bits free and its used for flag also.
 *
 *    Revision 1.19  2008/03/05 10:26:33  ljoshi
 *    Adding LLMEnv.
 *
 *    Revision 1.18  2008/03/04 15:46:08  ljoshi
 *    Adding 32bit Unicode Support
 *
 *    Revision 1.17  2007/11/29 05:57:49  ljoshi
 *    Adding code for CLUT
 *
 *    Revision 1.16  2007/10/19 14:00:55  ljoshi
 *    Ritesh:Changed done for style based selection of fonts under the macro ENABLE_LLM_EXTENSION.
 *
 *    Revision 1.15  2007/09/13 09:18:14  ljoshi
 *    Adding support to make LLConfig.h file name configurable.
 *
 *    Revision 1.14  2007/09/10 10:20:07  ljoshi
 *    Adding new line to end of file.
 *
 *    Revision 1.13  2007/08/27 11:13:19  ljoshi
 *    Added support or tabstop
 *
 *    Revision 1.12  2007/08/25 20:12:27  ljoshi
 *    Adding support for TABs
 *
 *    Revision 1.11  2007/08/09 14:24:51  ljoshi
 *    Garima: Correcting/Adding the comments.
 *
 *    Revision 1.10  2007/07/19 04:36:00  ljoshi
 *    Lokesh/Himanshu: Adding support for dotted line
 *
 *    Revision 1.9  2007/06/19 13:39:24  jaydeep
 *    Jaydeep : added outline filter support and enum LLMLineTypes for various line types (underline, overline etc.)
 *
 *    Revision 1.8  2007/02/13 06:41:31  ljoshi
 *    Initial CVS Version
 *
 *
******************************************************************************/
