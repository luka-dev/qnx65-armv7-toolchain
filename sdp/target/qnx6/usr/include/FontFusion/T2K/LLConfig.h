/*
 * LLConfig.h
 * $Header: /home/archive/Panorama/layout/LLManager/hdr/LLConfig.h,v 1.90 2009/07/10 12:38:42 ljoshi Exp $
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

#ifndef __LLCONFIG_HEADER__
#define __LLCONFIG_HEADER__
/**
 * This file contains the configuration macros for FFManager. Remember
 * this configuration is additional to what is in config.h.
 */

/* Include the parent config file */
#ifndef FF_FFCONFIG_HEADER
#include "config.h"
#else
#include FF_FFCONFIG_HEADER
#endif /* FF_FFCONFIG_HEADER */

#ifndef LLM_LLMINCLUDE_HEADER
/* Include Path File */
#include "LLMInclude.h"
#else
#include LLM_LLMINCLUDE_HEADER
#endif /* LLM_LLMINCLUDE_HEADER */

/*-------------------------- System Wide Configuration Macros --------------------------*/

/*** #1 ***/
/**
 * Enable the support for Line Layout Engine. (LLE)
 * LLE is an OOPS based set of APIs providing the integrated support for TTF/T2K and OTF
 * fonts, provides rich set of APIs for OTF. All of the Bitstream Panorama has been coded
 * under this macro.
 */
#define	ENABLE_LLE


 /*** #2 ***/
/**
 * This macro will enable the default embedded font feature. This macro makes sure that
 * LLManager will be working with one default validated font. This feature can be enabled
 * when one wants to have at least one default font, easy functionality to reset the font
 * to default or needs to have well validated font at any instance. Enabling this will
 * result in the increase of code/ROM or executable size. No side-effect on RAM requirements.
 */
/* #define ENABLE_EMBEDDED_FONT */


/*** #3 ***/
/**
 * Enabling this will allow to set the font directly from the file name. For this the full
 * file system should be supported on the device. Else this feature can be turned off and
 * the font can be set by providing the font buffer.
 */
/* #define ENABLE_FONT_FILE_SUPPORT */


/*** #4 ***/
/**
 * The debug mode macro. If turned ON its a <b> Debug Build </b>. In this mode
 * the LLManager is very strict, fonts with invalid data fail with assertions.
 * When this macro is OFF its a <b> Release Build</b> where the components are
 * not loaded whose data is not valid
 */
#define ENABLE_OTF_DEBUG


/*** #5 ***/
/**
 * This macro make the LLE to validate every OTF font before loading and
 * checking the contents before taking the loaded structs for rendering.
 * The process of validation may be processor intensive, but its recommended
 * to keep this on if targeted system can load the OTF font from web etc.
 * Turning OFF this validation may make the target implementation unsafe for
 * uncertified fonts. <br>
 * If its for sure that the font to be used will be valid and certified then this
 * option can be turned off, will save processing time and space. <br>
 * <b>Info</b>: If the macro ENABLE_OTF_DEBUG is OFF and ENABLE_OTF_VALIDATION is ON
 * then FF tries its best to recover and work on corrupted font also, its recommended
 * to keep ENABLE_OTF_DEBUG option OFF in build release and ON during development.
 * @see ENABLE_OTF_DEBUG
 */
#define ENABLE_OTF_VALIDATION


/*** #6 ***/
/**
 * Color configuring Macros<br>
 * Macros for the LCD RGB configuration. If the target platform
 * is not having LCD then keep the default settings. Apart from LCD
 * settings one should also see the format of the buffer that is needed
 * by the base rendering system/driver. FF supports the direct rendering
 * system where FF can render the string on the buffer and that can be in turn
 * rendered on the target screen. Its suggested to use the format and layout of
 * RGB same as of the base platform. <br>
 * So the COLOR FORMATS supported are <br>
 * 1. LLM_COLOR_FORMAT_RGB <br>
 * 2. LLM_COLOR_FORMAT_BGR <br>
 * 3. LLM_COLOR_FORMAT_MONO - 1 bit pixel depth : This needs some explanation. If this
 *    is turned on then none of the color formats will work and LLManager will work
 *    on mono - color basis, no antialiasing calls will be valid. The buffer format
 *    passed as input or output will be treated bitwise. No calls for setting fore
 *    or backcolor will be available.
 * @see LLM_COLOR_FORMAT_GRAY,
 *      LLM_COLOR_FORMAT_MONO
 */


/*** #7 ***/
/*
 * Most of the time we have RGB. For RGB sequence use this macro
 */
 #define LLM_COLOR_FORMAT_RGB


/*** #8 ***/
/**
 * If LCD/target System takes buffer in BGR format then FF is capable of doing
 * the same while rendering the text. Windows takes Pixel color in BGR .
 */
/* #define LLM_COLOR_FORMAT_BGR */


/*** #9 ***/
/**
 * This flag will turn OFF all the RGB support and one bit buffer will be
 * supported. The input/output buffer will be treated bitwise.
 */
/* #define LLM_COLOR_FORMAT_MONO */


/*** #10 ***/
/**
 * For the support of gray format shared buffer. One byte per pixel. 0 stands for full
 * background component and 255 stands for the full foreground component. Two schemes
 * of  antialiasing are supported in this mode.
 */
/* #define LLM_COLOR_FORMAT_GRAY */

/*** #11 ***/
/**
 * Macros for color depth. <br>
 * Remember that the way buffer is interpreted depends on the color format.
 * Plus the format of RGB does not depends on these macros. These macros are
 * only to decide the depth of each component. Types of Color Layouts supported
 * are: <br>
 * 1. LLM_COLOR_LAYOUT_R8G8B8 - 4 Bytes <br>
 * 2. LLM_COLOR_LAYOUT_R6G6B6 - 4 Bytes <br>
 * 3. LLM_COLOR_LAYOUT_R5G6B5 - 2 Bytes <br>
 * 4. LLM_COLOR_LAYOUT_R5G5B5 - 2 Bytes <br>
 * 4. LLM_COLOR_LAYOUT_R3G3B2 - 1 Byte  <br>
 * 5. LLM_COLOR_LAYOUT_R3G2B3 - 1 Byte  <br>
 * 6. LLM_COLOR_LAYOUT_R2G3B3 - 2 Byte  <br>
 * 7. LLM_COLOR_LAYOUT_A8R8G8B8 - 4 Bytes <br>
 */


/*** #12 ***/
/*
 * 4 Bytes  will be used for one Pixel
 */
 #define LLM_COLOR_LAYOUT_R8G8B8


/*** #13 ***/
/*
 * 4 Bytes will be used for one Pixel
 */
/* #define LLM_COLOR_LAYOUT_R6G6B6 */


/*** #14 ***/
/*
 * 2 Bytes will be used for one Pixel
 */
/* #define LLM_COLOR_LAYOUT_R5G6B5 */


/*** #15 ***/
/*
 * 2 Bytes will be used for one Pixel
 */
/* #define LLM_COLOR_LAYOUT_R5G5B5 */


/*** #16 ***/
/*
 * One Byte will be used for one pixel
 */
/* #define LLM_COLOR_LAYOUT_R3G3B2 */


/*** #17 ***/
/*
 * One Byte will be used for one pixel
 */
/* #define LLM_COLOR_LAYOUT_R3G2B3  */


/*** #18 ***/
/*
 * One Byte will be used for one pixel
 */
/* #define LLM_COLOR_LAYOUT_R2G3B3  */


/*** #19 ***/
/*
 * 4 Bytes  will be used for one Pixel. This format supports the alpha channel.
 */
/* #define LLM_COLOR_LAYOUT_A8R8G8B8 */


/*** #20 ***/
/**
 * This macro will make available the descriptive name of the tags for
 * Language/Scripts/Features/JSTF/Base etc. In embedded environment it may not be
 * needed in the final build, but may be needed for sample prototyping and debugging.
 * Its recommended to turn the macro OFF for final production release, since it increases
 * the total code size.
 */
#define ENABLE_OTFTAGS_STRINGS


/*** #21 ***/
/**
 * Macro to enable GPOS table in OTF, if ENABLE_FULL_OTF is turned on then all
 * the tables GSUB, GPOS, JSTF, GDEF and BASE is turned on. <b>Remeber</b>
 * there is macro of GDEF, it will be turned on of either GPOS/GDEF is turned on.
 * Any of the module needs RAM and ROM to run, so for small systems, the limited
 * capability of LLE can be configured. <br>
 * So the macros for OTF configuration are: <br>
 * 1. ENABLE_OTF_GSUB - for GSUB table support <br>
 * 2. ENABLE_OTF_GPOS - for GPOS table support <br>
 * 3. ENABLE_OTF_JSTF - for JSTF table support. NOT SUPPORTED <br>
 * 4. ENABLE_OTF_BASE - for BASE table support  NOT SUPPORTED <br>
 * 5. ENABLE_OTF_FULL - This macro turns on all the previous 4 macros and full
 *    implementation of OTF gets available. <br>
 *
 * Enabling macro for GSUB table.
 */
#define ENABLE_OTF_GSUB


/*** #22 ***/
/**
 * Enabling macro for GPOS table. GPOS table is responsible for the context based
 * positioning of the characters. This is generally used for cursive scripts as Arabic
 * Indic and for general kerning. This GSUB based kerning is different than the 'kern'
 * table stored in the TTF/OTF font files.
 */
#define ENABLE_OTF_GPOS


/*** #23 ***/
/**
 * Enabling macro for JSTF table. <b>
 * NOT SUPPORTED RIGHT NOW. DO NOT TURN ON.
 * </b>
 */
/* #define ENABLE_OTF_JSTF */


/*** #24 ***/
/**
 * Enabling macro for BASE table. <b>
 * NOT SUPPORTED RIGHT NOW. DO NOT TURN ON
 * </b>
 */
/* #define ENABLE_OTF_BASE */


/*** #25 ***/
/**
 * This macro will enable the support for all the OTF features, basically GSUB and GPOS.
 *
 * @see ENABLE_OTF_GPOS,
 *      ENABLE_OTF_GSUB
 */
/* #define ENABLE_OTF_FULL */


/*** #26 ***/
/**
 * If enabled, provides methods for registering the callbacks for alternate glyphs that
 * may be there in GSUB table.
 */
/* #define ENABLE_ALTGLYPH_CALLBACK */


/*** #27 ***/
/**
 * This enables the tab processing. It means that a TAB character is replaced by the
 * DEFAULT_NUM_TAB_SPACES. If this is not enabled normally tabs will be rendered as the
 * block characters. Normally fonts doesn't stores the data for tab and tab is mapped
 * to the integral number of spaces.
 * It is suggested to disable this if its not really needed, it adds to the performance
 *
 * @see DEFAULT_NUM_TAB_PIXELS
 */
/* #define ENABLE_TAB_PROCESSING */


/*** #28 ***/
/**
 * Enables the Unicode BIDIR Algorithm. It is suggested to turn this macro on for the
 * Arabic/Hebrew and other Right to Left languages plus the mixed mode languages. This
 * adds to the ROM, RAM and performance cost of LLManager.
 *
 * @see ENABLE_ARABIC_SHAPING, ENABLE_HEBREW_SHAPING
 */
/* #define ENABLE_BIDIR */


/*** #29 ***/
/**
 * For Normal port its very unlikely that the GASP table support with be toggled at
 * run time. Enabling this macro will GASPify the command before rendering any character.
 * Enable ENABLE_GASP_TABLE_SUPPORT in config.h before turning on this feature.
 * Please turn on ENABLE_MULTIMODE_GLYPH_CACHING for better performance, if the grayscale is the
 * default rendering mode and ENABLE_GASP_SUPPORT is enabled.
 */
/* #define ENABLE_GASP_SUPPORT */


/*** #30 ***/
/**
 * To enable the TV modes, turn on this macro. Not needed for normal and LCD modes.
 * This mode is recommended for TV like CRO devices.
 */
#define ENABLE_TV_MODE


/*** #31 ***/
/**
 * If enabled the shaping engines for the complex languages as Arabic, Hebrew are turned on.
 * These can be needed if accurate rendering of these complex scripts is needed. Enabling
 * this macro adds an intelligence to Bitstream Panorama, and the GSUB/GPOS tags for a
 * character are selected and applied based on its position and context. Yet it adds to the
 * performance and memory too. <br>
 * The user selected GSUB/GPOS tags are applied for rest of the text that does not falls in
 * to any one of the complex scripts selected.
 */
/* #define ENABLE_SHAPING */

#ifdef ENABLE_SHAPING

/*** #32 ***/
/**
 * Turns ON the shaping engine for Arabic Script. OTF should be turned on for this
 * script. Unicode range for Arabic script is: U+0600 - U+06FF <br>
 * The Arabic script is used for writing the Arabic language and has been extended for
 * a number of other languages, such as Persian, Urdu, Pashto, Sindhi, and Kurdish.
 * Its suggested to turn the macro ENABLE_BIDIR on, since the Arabic has an orientation
 * right-to-left and bidirectional algorithm should be applied on the same.
 *
 * @see ENABLE_BIDIR, ENABLE_SHAPING
 */
/* #define ENABLE_ARABIC_SHAPING */


/*** #33 ***/
/**
 * Turns ON the shaping engine for Hebrew. This is exactly not shaping but some sort of intelligent
 * preprocessing. OTF support is not required for this feature. But this adds to the performance.
 * Unicode range for Hebrew script is U+0590 - U+05FF <br>
 * The Hebrew script is used for writing the Hebrew language as well as Yiddish, Judezmo
 * (Ladino), and a number of other languages. Its suggested to turn the macro ENABLE_BIDIR on,
 * since the Arabic has an orientation right-to-left and bidirectional algorithm should be applied on the
 * same.
 * @see ENABLE_BIDIR, ENABLE_SHAPING
 */
/* #define ENABLE_HEBREW_SHAPING */

#ifdef ENABLE_HEBREW_SHAPING

/**
 * Enables the support for vertical and horizontal positioning of Hebrew marks and points.
 * Hebrew marks combine with vowels and other Hebrew points, which may involve complex
 * typographical rules to position these characters.
 * @see ENABLE_BIDIR, ENABLE_SHAPING
 */
#define ENABLE_HEBREW_POSITIONING

/*** #34 ***/
/**
 * Define this to have complete support for the positioning of the cantillation marks correctly.
 * This may slow down the Hebrew shaping a bit though.
 */
#define ENABLE_HEBREW_CANTILLATION_MARKS
#endif /* ENABLE_HEBREW_SHAPING */


/*** #35 ***/
/**
 * This macro turns on the basic data structs, common methods needed for Indic Language shaping.
 * The core algorithm for Indic Language shaping is the same but different data driven models are
 * made for each Indic Language. The Indic Language for which shaping is supported are: <br>
 * Bengali, Devanagari, Gujarati, Gurmukhi, Kannada, Tamil and Telugu.
 * @see ENABLE_SHAPING, ENABLE_BENGALI_SHAPING, ENABLE_DEVANAGIRI_SHAPING,
 *      ENABLE_GUJRATI_SHAPING, ENABLE_GURMUKHI_SHAPING, ENABLE_KANNADA_SHAPING,
 *      ENABLE_TAMIL_SHAPING, ENABLE_TELUGU_SHAPING
 */
/* #define ENABLE_INDIC_SHAPING */

#ifdef ENABLE_INDIC_SHAPING

/*** #36 ***/
/**
 * The macro will turn on shaping for language Bengali script. OTF should be turned on for
 * this script. Unicode range for Bengali script is U+0980 - U+09FF.
 * The Bengali script is a North Indian script somewhat closely related to Devanagari. It is used
 * in the Bengali language primarily in the West Bengal state of India and in the adjoining
 * nation Bangladesh. It is also used to write Assamese in Assam state of India and a number of
 * other small languages, such as Daphla, Garo, Hallam, Khasi, Manipuri, Mizo, Munda, Naga, Rian,
 * and Santali, in north-eastern region of India.
 *
 * @see OTF, ENABLE_SHAPING, ENABLE_INDIC_SHAPING
 */
#define ENABLE_BENGALI_SHAPING


/*** #37 ***/
/**
 * The macro will turn on the shaping for Devanagari script. OTF should be turned on for
 * this script. Unicode range for Devanagari or Hindi script is U+0900 - U+097F. By default for
 * Indic Shaping, Devanagari is turned on.
 * The Devanagari or Hindi script is used for writing classical Sanskrit and its modern historical
 * derivative, Hindi. Extensions to the Sanskrit language are used to write other related languages
 * of India (as Marathi) and of Nepal (Nepali). Devanagari script is also used to write some localized
 * Indian languages (mostly north Indian) as: Awadhi, Bagheli, Bhatneri, Bhili, Bihari, Braj Bhasha,
 * Chhattisgarhi, Garhwali, Gondi (Betul, Chhindwara, and Mandla dialects), Harauti, Ho,
 * Jaipuri, Kachchhi, Kanauji, Konkani, Kului, Kumaoni, Kurku, Kurukh, Marwari, Mundari,
 * Newari, Palpa, and Santali.
 *
 * @see ENABLE_SHAPING, ENABLE_INDIC_SHAPING
 */
#define ENABLE_DEVANAGIRI_SHAPING


/*** #38 ***/
/**
 * The macro will turn on the shaping for Gujarati script. OTF should be turned on for
 * this script. Unicode range for Gujarati script is U+0A80 - U+0AFF.
 * The Gujarati script is a North Indian script closely related to Devanagari/Hindi script.
 * It very much  distinguished from Devanagari by not having a horizontal bar for its letterforms,
 * a characteristic of the older Kaithi script to which Gujarati is related. The Gujarati script
 * is used to write the Gujarati language of the Gujarat state in India.
 *
 * @see ENABLE_SHAPING, ENABLE_INDIC_SHAPING
 */
#define ENABLE_GUJRATI_SHAPING

/*** #39 ***/
/**
 * The macro will turn on the shaping for Gurmukhi or Punjabi script. OTF should be turned on for
 * this script. Unicode range for Gurmukhi script is U+0A00 - U+0A7F.
 * The Gurmukhi script is a North Indian script used to write the Punjabi language in the Punjab
 * state of India. Gurmukhi is derived from an older script called Lahnda, and is closely related
 * to Devanagari structurally. The script is also closely associated with Sikh and Sikhism.
 *
 * @see ENABLE_SHAPING, ENABLE_INDIC_SHAPING
 */
#define ENABLE_GURMUKHI_SHAPING

/*** #40 ***/
/**
 * The macro will turn on the shaping for Kannada script. OTF should be turned on for
 * this script. Unicode range for Kannada script is U+0C80 - U+0CFF.
 * The Kannada script is a South Indian script. It is used to write the Kannada
 * language of the Karnataka state in India and to write other localized languages such
 * as Tulu. The Kannada language is also used in many parts of other states of India as
 * Tamil Nadu, Kerala, Andhra Pradesh, and Maharashtra.
 *
 * @see ENABLE_SHAPING, ENABLE_INDIC_SHAPING
 */
#define ENABLE_KANNADA_SHAPING

/*** #41 ***/
/**
 * The macro will turn on the shaping for Malayalam script. OTF should be turned on for
 * this script. Unicode range for Kannada script is U+0D00 - U+0D7F.
 * The Malayalam script is a South Indian script. It is used to write the Malayalam
 * language of the Kerala state in India.
 *
 * @see ENABLE_SHAPING, ENABLE_INDIC_SHAPING
 */
#define ENABLE_MALAYALAM_SHAPING


/*** #42 ***/
/**
 * The macro will turn on the shaping for Oriya script. OTF should be turned on for
 * this script. Unicode range for Oriya script is U+0B00 - U+0B7F.
 * The Oriya script is a North Indian script. It is used to write the Oriya
 * language of the Orissa state in India, as well as minority languages such as Khondi and Santali.
 *
 * @see ENABLE_SHAPING, ENABLE_INDIC_SHAPING
 */
#define ENABLE_ORIYA_SHAPING


/*** #43 ***/
/**
 * The macro will turn on the shaping for Tamil script. OTF should be turned on for
 * this script. Unicode range for Tamil script is U+0B80 - U+0BFF.
 * The Tamil script is a South Indian script mostly used in Tamil Nadu state of India
 * and for some localized languages as the Dravidian language Badaga and the Indo-European
 * language Saurashtra. Tamil is also used in Sri Lanka, Singapore, and parts of Malaysia.
 *
 * @see ENABLE_SHAPING, ENABLE_INDIC_SHAPING
 */
#define ENABLE_TAMIL_SHAPING

/*** #44 ***/
/**
 * The macro will turn on the shaping for Telugu script. OTF should be turned on for
 * this script. Unicode range for Telugu script is U+0C00 - U+0C7F.
 * The Telugu script is a South Indian script used to write the Telugu language in
 * Andhra Pradesh state in India, as well as some localized languages as Gondi
 * and Lambadi. The script is also used rarely in Maharashtra, Orissa, Madhya Pradesh, and
 * West Bengal states of India.
 *
 * @see ENABLE_SHAPING, ENABLE_INDIC_SHAPING
 */
#define ENABLE_TELUGU_SHAPING

#endif /* ENABLE_INDIC_SHAPING */

/*** #45 ***/
/**
 * This macro will turn on the Thai Shaping engine.
 */
/* #define ENABLE_THAI_SHAPING */

#ifdef ENABLE_THAI_SHAPING

/*** #46 ***/
/**
 * The most common norms for combined and error glyphs followed for Thai.
 */
/* #define ENABLE_THAI_WINDOWS_NORMS */

/*** #47 ***/
/**
 * Will enable the MAC norms for Thai combined and error glyphs.
 */
/* #define ENABLE_THAI_MAC_NORMS */

/**
 * This enables the manual positioning, this gets turned on when GPOS rules for Thai are not present in the
 * font.
 */
#define ENABLE_THAI_POSITIONING

#endif /* ENABLE_THAI_SHAPING */

#endif /* ENABLE_SHAPING */

/*** #48 ***/
/**
 * Normally OTF is very much strict about the case of the characters used for tags for script
 * features and rules but its seen that in many OTF fonts its not followed. Enabling this
 * macro will check tags in all possible combination of cases of characters. This may make
 * getting script/feature/language structs little bit slower. For a strict environment this
 * can be kept disabled.
 */
/* #define ENABLE_CHECK_TAG_CASE */

/*** #49 ***/
/**
 * Enables the call back mechanism to create the new runs on user needs basis. This in turn also
 * enables the user to render multiple sizes, fonts, styles in a single line. The runs lines etc
 * are automatically adjusted according to the sizes, fonts , styles in the line.
 */
#define ENABLE_NEW_RUN_CALLBACK

/*** #50 ***/
/**
 * Enables the user defines line break mechanism. This is needed for some complex scripts as Thai.
 */
/* #define ENABLE_USER_LINEBREAK */

/*** #51 ***/
/**
 * Enables the mapping of scripts to fonts. This helps to render the multiple scripts (in different
 * font files) per line. LLManager sets the font automatically for the script.
 * @see LLM_MAX_NUM_FONTS
 */
/* #define ENABLE_SCRIPT_TO_FONT_MAP */

/*** #52 ***/
/**
 * Enables the uniset APIs of the LLMRunIter. In most of the cases its felt that these
 * APIs are not really needed.
 */
/* #define ENABLE_LLM_UNISET */

/*** #53 ***/
/**
 * Enables the dynamic insertion/deletion of characters, joining of lines, changing
 * of runs etc.
 */
/* #define ENABLE_DYNAMIC_RUNCHANGE */

/*** #54 ***/
/**
 * Enables the API for setting inter char space. Only enable when its needed else it slows
 * down the layout phase
 */
/* #define ENABLE_INTERCHAR_SPACING */

/*** #55 ***/
/**
 * Enables the correction of a Run Ascent/Height based on the characters contained in it.
 * Normally the maximum values in a font are correct, but with kerning these values can
 * change per character. This manifest enables that check. This may be undesirable to some
 * platforms where for same font, the line height etc is expected to be constant irrespective
 * of the characters contained in it.
 */
#define ENABLE_DYNAMIC_RUNCHECK

/*** #56 ***/
/**
 * Enables to handle the dynamic change in color depth and in color format. With this enabled one can
 * change the format in which LLManager should render the strings dynamically. Please make sure this is
 * enabled only when needed. This does contributes in increase of code size and a bit on performance.
 */
/* #define ENABLE_DYNAMIC_COLOR */

/*** #57 ***/
/**
 * Enables the alpha channel support for direct text rendering. Enable this when alpha support is needed else
 * slows down the performance a bit. Alpha support can be turned off or turned on at runtime.
 */
/* #define ENABLE_ALPHA_CHANNEL */

/*** #58 ***/
/**
 * Enables the use of new/delete operators for LLManager. Apart from LLManager no internal new/delete operations are
 * used. In LLManager new/delete operations are overridden with CLEINT_MALLOC call internally, but if still the compiler
 * doesn't supports new/delete then please turn off this macro. This will turn off the new/delete and constructor/destructor,
 * instead LLManager::LLManagerCtor/ LLManager::LLManagerDtor can be called manually after allocation.
 */
#define ENABLE_LLMANAGER_NEWDELETE

/*** #59 ***/
/**
 * Enables the lineGap APIs. This can be enabled when desired lineGap property is needed. Else it adds to the performance.
 */
/* #define ENABLE_LINEGAP */

/*** #60 ***/
/**
 * Enables the paragraph specific properties as alignment, line gap, indentation etc individually to a paragraph. This is by default
 * valid globally but can be changed individually if this macro is enabled. Only turn this on when its really needed, this adds to the
 * memory consumption per paragraph.
 */
/* #define ENABLE_PARAGRAPH_SPECIFIC_PROPERTIES */

/*** #61 ***/
/**
 * Enables the multiple light instances of Panorama. This feature uses the static member functions and may not be compatible with some
 * systems as Symbian or BREW. Enabling this feature shares the font resources and the cache.
 */
/* #define ENABLE_MULTIPLE_INSTANCE */

/*** 62 ***/
/**
 * Enables the many other styles for lines used for UnderLine, StrikeThrough and OverLine apart from the single line.
 */
/* #define ENABLE_LINES_STYLES */

/*** 63 ***/
/**
 * Enables the extra run specific properties as interchar spacing which is normally needed by advanced editors etc. For normal embedded systems
 * enabling this option adds more to the memory need.
 */
/* #define ENABLE_EXTRA_RUN_PROPS */

#ifdef ENABLE_TAB_PROCESSING
/*** 64 ***/
/**
 * Enables the Tab Stops property.
 */
/* #define ENABLE_TABSTOP */
#endif /* ENABLE_TAB_PROCESSING */

#ifdef ENABLE_NEW_RUN_CALLBACK
/*** 65 ***/
/**
 * Enables the sniffing and updating of the paragraph properties after the new run callback.
 * It is always suggested to change the paragraph properties only in the callback at first character
 * of the paragraph.
 */
/* #define ENABLE_PARAGRAPH_UPDATE_CALLBACK */
#endif /* ENABLE_PARAGRAPH_UPDATE_CALLBACK */

/*** 66 ***/
/**
 * Enables the coexistence of glyphs in all aliasing modes together. This should be turned ON when multiple instances
 * of LLManager are made to share the same font repository with varying rendering modes.
 */
/* #define ENABLE_MULTIMODE_GLYPH_CACHING */

/*** 67 ***/
/**
 * Enables the 'anchor run' feature, which lets the user shift the current run by the specified amount,
 * (shift can be positive or negative).
 */
/* #define ENABLE_ANCHOR_RUN */

/*** 67 ***/
/**
 * Enabling this option lets user to select font based on style.
 */
/* #define ENABLE_LLM_EXTENSION */

/*** 68 ***/
/**
 * Enables GlyphIter iterator for direct rendering.
 */
/* #define ENABLE_GLYPH_ITERATOR */

/*** 69 ***/
/**
 * Enables GlyphObj iterator for indirect rendering.
 */
#define ENABLE_GLYPH_OBJ 

/*** 70 ***/
/**
 * Enables the check for font metrics at runtime. The macro should be enabled only when the font data is not
 * limited, as it can slow down the rendering process. If the fonts are pre-checked, the macro can be disabled
 * for embedded platforms.
 */
/* #define ENABLE_RUNTIME_METRICSCHECK */

/*** 71 ***/
/**
 * Enable setting of termination Style for layout.
 */
/* #define ENABLE_LLM_TERMINATION_STYLE */

/*** 72 ***/
/**
 * Enables Panorama to behave similar to other editors in case of space. This implies that except the first line of a record, each new line will start with a visible glyph.
 */
/* #define ENABLE_SPACE_WRAP */

/*** 73 ***/
/**
 * Enables the application of OTF rules through iterators. This macro can be used when application is capable of
 * identifying and applying the OTF rules itself. Shaping and auto application of OTF rules according to the script
 * will work even when ENABLE_MANUAL_OTF is OFF.
 */
/* #define ENABLE_MANUAL_OTF */

/*** 73 ***/
/**
 * Enables 32 bit Unicode support. It is suggested that this macro should be turned ON if ENABLE_UNICODE_32_SUPPORT
 * is on in config.h.
 */
/* #define ENABLE_LLM_UNICODE32 */

/*** 74 ***/
/**
 * Enables the extra check for the OTF fonts which more depend on the language specifics. Should be turned on only when needed,
 * may affect the performance.
 */
/* #define LLM_USE_SEAT_BELTS */

/*** 75 ***/
/** 
 * If enabled, forces the base direction of the paragraph to be RtoL, if any of the RtoL hard character is there. By default
 * the base direction is  decided based on the directionality of the first hard character.
 */
/* #define ENABLE_FORCE_RTL_DIRECTION */

/*** 76 ***/
/**
 * If enabled, uses the kern pairs of the font. ENABLE_KERNING should be turned on in config.h for the same.
 */
/* #define ENABLE_AUTO_KERNING */

/*** 77 ***/
/**
 * Enables the support for user-defined colors for underline, strikethrough and overline
 * line styles.
 */
/* #define ENABLE_LINE_COLOR */

/*** 78 ***/
/**
 * Enables the floating object support. The inline graphic object flows with the text as
 * you perform dynamic addition or deletion operations on the text.
 */
/* #define ENABLE_FLOATING_OBJECT */

/*** 79 ***/
/**
 * Enables the Unicode-to-image mapping support that allows establishing a mapping between
 * Unicode values/glyphs and graphic objects. Once a user establishes the mapping, the
 * engine renders the mapped graphic object in the layout area on each occurrence of
 * the mapped Unicode/glyph sequence. Panorama provides the exact (x,y) coordinates for the graphic
 * object to be drawn; the client is responsible to draw the image on the buffer.
 */
/* #define ENABLE_UNICODE_IMAGE_MAPPING */

/*** 80 ***/
/**
 * Enables user to introduce the antialiasing property to run, by this feature user can have different anitialaising mode
 * in same text. Enabling this feature can decrease the performance as base engine Panorama need to shift between
 * anti-aliasing modes.Enabling this macro will also enable ENABLE_MULTIMODE_GLYPH_CACHING, which in term will help to 
 * increase the performance speed.
 */
/* #define ENABLE_RUN_ANTIALIASED */

/*** 81 ***/
/**
 * Enables the support for extended Unicode mirror characters. This can be bit slow on embedded systems.
 */
/* #define ENABLE_EXTENDED_MIRROR_SUPPORT */

/*** 82 ***/
/**
 * Enables accurate dynamic entry support. This involves a bit higher memory allocation for low level object.
 */
/* #define ENABLE_ACCURATE_DYNAMIC_METRICS */

/*** 83 ***/
/**
 * Enables the runtime dynamic directionality control on bidirectional and Mixed oriented text.
 */
/* #define ENABLE_DYNAMIC_BIDI_CONTROL */

#ifdef ENABLE_INTERCHAR_SPACING
/*** 84 ***/
/**
 * Enables finer resolution for interchar space at milli (16.16 format) level.
 */
/* #define ENABLE_MILLI_INTERCHAR_SPACE */
#endif /* ENABLE_INTERCHAR_SPACING */

/*** 85 ***/
/**
 * Enables the cache. This should be turned on by default always. Turning this macro off will stop caching glyphs and will
 * impact performance.
 */
#define ENABLE_CACHE

/*** 86 ***/
/**
 * Enables the support for formatting Unicode, such as LRE, RLE etc.
 */
/* #define ENABLE_FORMATTING_UNICODE_SUPPORT */

/*** 87 ***/
/**
 * This will enable Widget support in Panorama, user can include the 'Text On Path' widget.
 */
/* #define ENABLE_LLM_WIDGET_SUPPORT */
 
/*** 88 ***/
/**
 * This will enable the real UDB data. This is recommended and enabled by default and should be changed only when RtoL support is not
 * desired and all white spaces, segment separators, line separators are expected to be in ASCII limit. Disabling this will save 32KB of code size.
 */
#define ENABLE_UDB_SUPPORT

/*------------------------- System Wide Values ----------------------------------- */

/*** #1 ***/
/**
 * The default Cache Size used by the LLManager class.
 */
#define DEFAULT_CACHE_SIZE 0x4000 /* 16K by default */

/*** #2 ***/
/**
 * The X Resolution. Normally its 72 and this is by default, but can be changed too.
 * @see LLManager::setResolution,
 *      LLManager::getResolution
 */
#define SCREEN_X_RES 72

/*** #3 ***/
/**
 * The Y Resolution. Normally its 72 and this is by default, but can be changed too. Many
 * screens are not proportional, in that case the values can be modified according to the
 * hardware.
 * @see LLManager::setResolution,
 *      LLManager::getResolution
 */
#define SCREEN_Y_RES 72

/*** #4 ***/
/**
 * The number of simultaneous fonts supported.
 */
#define LLM_MAX_NUM_FONTS 5

#ifdef ENABLE_TAB_PROCESSING
/*** #5 ***/
/**
 * This this is the number of pixels that are actually placed instead of TAB.
 */
#define DEFAULT_NUM_TAB_PIXELS 8
#endif /* ENABLE_TAB_PROCESSING */

/*** #6 ***/
/**
 * The base FontFusion version on which the panorama is being built. If using FF 3.1+ then
 * please enable this option, for lower version this macro can be disabled itself.
 */
#define BASE_FF_VER 0x00031000

#ifdef ENABLE_LLM_EXTENSION
#define LLM_MAX_FONT_FOR_FAMILY 4
#endif /* ENABLE_LLM_EXTENSION */

/* ---------------------- Standard Library Functions Port ---------------------------- */
/*** #1 ***/
#ifndef CLIENT_MEMCMP
#define CLIENT_MEMCMP( mem1, mem2, len )	memcmp( mem1, mem2, len )
#endif /* CLIENT_MEMCMP */

/* -----------------------------------------------------------------------------------
 *     *****    DO NOT MAKE ANY CHANGES BEYOND THIS.     *****
 *            All the definitions further are internal.
 * -----------------------------------------------------------------------------------
 */

/*----------------------- Check for the OTF macros from FontFusion --------------------*/
#ifdef ENABLE_OPENTYPE_SUPPORT
	#if defined(ENABLE_OPENTYPE_VERT) && !defined(ENABLE_OTF_GSUB)
		#define ENABLE_OTF_GSUB
	#endif /* ENABLE_OPENTYPE_VERT && !ENABLE_OTF_GSUB */

	/* No support for GPOS in FF right now */
	#undef ENABLE_OTF_GPOS
#endif /* ENABLE_OPENTYPE_SUPPORT */

/*----------------------- Check for Macros compatability and internal macros ----------*/

/**
 * If GPOS or GSUB are defined then define GDEF too.
 * If manually defined then error.
 */
#if defined(ENABLE_OTF_GPOS) || defined(ENABLE_OTF_GSUB)
	#define ENABLE_OTF_GDEF
#else
	#ifdef ENABLE_OTF_GDEF
		#error COMPILE ERROR: Manually GDEF defined.
	#endif /* ENABLE_OTF_GDEF */
#endif /* ENABLE_OTF_GPOS || ENABLE_OTF_GSUB */

/**
 * Do not check Panorama specefic conditions when invoked from FontFusion.
 */
#ifndef ENABLE_OPENTYPE_SUPPORT

#ifdef ENABLE_FRACTIONAL_SIZE
/**
 * We will enable this when we add line and path orientation support.
 */
/* #define ENABLE_Y_FRAC */
#endif /* ENABLE_FRACTIONAL_SIZE */

/**
 * Check macro conditions. If OTF_FULL is on, enable all the OTF tables
 */
#if defined(ENABLE_OTF_FULL)

	#define ENABLE_OTF_GSUB
	#define ENABLE_OTF_GPOS
	/* #define ENABLE_OTF_JSTF */
	/* #define ENABLE_OTF_BASE */
	#define ENABLE_OTF_GDEF

#endif /* ENABLE_OTF_FULL */

/**
 * For internal use. Printing Debug messages.
 */
/* #define LLM_DEBUG_PRINT */

#ifndef ENABLE_BOLDFILTER
	#error COMPILE ERROR: Turn on macro ENABLE_BOLDFILTER in t2kextra.h
#endif /* ENABLE_BOLDFILTER */

#if defined(ENABLE_OTF_GPOS) || defined(ENABLE_OTF_GSUB) || defined(ENABLE_OTF_JSTF) || defined(ENABLE_OTF_BASE)

	#ifndef ENABLE_OTF
		#error COMPILE ERROR: Turn on macro ENABLE_OTF in config.h
	#endif /* ENABLE_OTF */

	#ifndef ENABLE_CFF
	/* Lokesh: 13Sep2005: I am not sure why this was done, seems to be no need of this error
	 * when we do not need cff or t1 fonts */
	/* #error COMPILE ERROR: Turn on macro ENABLE_CFF in config.h */
	#endif /* ENABLE_CFF */

#endif /* ENABLE_OTF */

#ifdef ENABLE_GASP_SUPPORT
	#ifndef ENABLE_GASP_TABLE_SUPPORT
		#error COMPILE ERROR: Enable ENABLE_GASP_TABLE_SUPPORT in config.h before enabling ENABLE_GASP_SUPPORT
	#endif /* ENABLE_GASP_TABLE_SUPPORT */
#endif /* ENABLE_GASP_SUPPORT */

/* Turn Off the OTF if neither of the OTF props is supported */
#if !defined(ENABLE_OTF_GPOS) && !defined(ENABLE_OTF_GSUB) && !defined(ENABLE_OTF_JSTF) && !defined(ENABLE_OTF_BASE)
	#ifdef ENABLE_OTF
		/* #error COMPILE ERROR: Turn Off ENABLE_OTF */
	#endif /* ENABLE_OTF */
#endif

/* Shaping Constructs */
/* If any of the complex scripts are ON then lets common complex scripts code. Some
 * Langs as hebrew are not exactly the complex scripts that need OTF rules and the other
 * common code.
 */
#if defined(ENABLE_SHAPING) && (defined(ENABLE_ARABIC_SHAPING) || defined(ENABLE_INDIC_SHAPING) || defined(ENABLE_HEBREW_SHAPING))
	/**
	 * Internal Macro.
	 */
	#define ENABLE_COMPLEX_SHAPING
#endif /* ENABLE_ARABIC_SHAPING || ENABLE_INDIC_SHAPING || ENABLE_HEBREW_SHAPING */

#ifdef ENABLE_COMPLEX_SHAPING
	#ifndef ENABLE_OTF
		#error COMPILE ERROR: Enable ENABLE_OTF in config.h before enabling any shaping for complex scripts as Arabic, Indic, Thai
	#endif /* ENABLE_OTF */
#endif /* ENABLE_COMPLEX_SHAPING */

/* Disable Shaping if none of the shaping is enabled explicitly */
#if !defined(ENABLE_COMPLEX_SHAPING) && !defined(ENABLE_HEBREW_SHAPING)
	#ifdef ENABLE_SHAPING
		#undef ENABLE_SHAPING
	#endif /* ENABLE_SHAPING */
#endif /* !ENABLE_COMPLEX_SHAPING && !ENABLE_HEBREW_SHAPING */

/* Defining internal macros for Indic shaping */
#ifdef ENABLE_INDIC_SHAPING

#if defined(ENABLE_BENGALI_SHAPING) || defined(ENABLE_TAMIL_SHAPING) || \
    defined(ENABLE_TELUGU_SHAPING)  || defined(ENABLE_KANNADA_SHAPING)

/* Enabling the code for multiple matras in a single syllable */
/**
 * Internal Macro.
 */
#define ENABLE_SHAPING_MULT_MATRA
#endif /* for multiple matras */

#if defined(ENABLE_TELUGU_SHAPING)  || defined(ENABLE_KANNADA_SHAPING)
	/**
	 * Internal Macro.
	 */
	#define ENABLE_MATRA_AFTER_BASE
#endif /* for matras after base */

/* This is needed only in two indic languages. Bengali and Oriya. */
#if defined(ENABLE_BENGALI_SHAPING)
	/**
	 * Internal Macro.
	 */
	#define ENABLE_REPH_AFTER_BELOW
#endif /* for reph after below case */

/* This happens for the case of Tamil and Malayalam where the matras have to be
 * readjusted just before the final application of GSUB tags. */
#if defined(ENABLE_TAMIL_SHAPING)
	/**
	 * Internal Macro.
	 */
	#define ENABLE_MATRA_ADJUST
#endif /* ENABLE_TAMIL_SHAPING */

#endif /* ENABLE_INDIC_SHAPING */

/* Lokesh: When we need the outArray its in case of hebrew or Indic shaping */
#if defined(ENABLE_INDIC_SHAPING) || defined(ENABLE_HEBREW_SHAPING)
	/**
	 * Internal Macro.
	 */
	#define ENABLE_EXTRA_OUTARRAY
#endif /* ENABLE_INDIC_SHAPING || ENABLE_HEBREW_SHAPING*/

/* Lokesh: 17Jun2005: We will have a single enabling macro for LCD if anyone of
 * these are open */
#if defined(ENABLE_EXTENDED_LCD_OPTION)
	#if defined(LLM_COLOR_FORMAT_MONO) || defined(LLM_COLOR_FORMAT_GRAY)
		#error COMPILE ERROR: Cannot have Mono or Gray color format when LCD is enabled. Turn off LLM_COLOR_FORMAT_MONO or ENABLE_EXTENDED_LCD_OPTION
	#endif /* LLM_COLOR_FORMAT_MONO */

	/* The internal combined LCD manifest */
	#define ENABLE_LCD_SUPPORT
#endif /* ENABLE_EXTENDED_LCD_OPTION */

	/* Lets have a single manifest to have no filters or colors for mono or gray format */
#if defined(LLM_COLOR_FORMAT_MONO) || defined(LLM_COLOR_FORMAT_GRAY)
	/**
 	 * Internal Macro.
	 */
	#define LLM_NO_COLOR_LCD_FILTERS
#endif /* LLM_COLOR_FORMAT_MONO || LLM_COLOR_FORMAT_GRAY  */

#if defined(LLM_COLOR_FORMAT_MONO)
	#ifdef ENABLE_GASP_SUPPORT
		#error COMPILE ERROR: Cannot have ENABLE_GASP_SUPPORT when Mono color format is ON.
	#endif /* ENABLE_GASP_SUPPORT */
#endif /* LLM_COLOR_FORMAT_MONO */

/* Macro to decide for the script variable */
#if defined(ENABLE_SCRIPT_TO_FONT_MAP) || defined(ENABLE_SHAPING) || defined(ENABLE_BIDIR) || (defined(ENABLE_DYNAMIC_RUNCHANGE) && defined(ENABLE_OTF))
	/**
 	 * Internal Macro.
	 */
	#define LLM_NEED_SCRIPT
#endif /* ENABLE_SCRIPT_TO_FONT_MAP || ENABLE_SHAPING || ENABLE_BIDIR || (ENABLE_DYNAMIC_RUNCHANGE && ENABLE_OTF)*/

/* Macro to decide wether the characters will be composed at all */
#if defined (ENABLE_HEBREW_SHAPING) || defined (ENABLE_OTF)
#define ENABLE_CHARACTER_DYNAMIC_COMPOSITION
#endif /* ENABLE_HEBREW_SHAPING || ENABLE_OTF */

#if defined(ENABLE_HEBREW_POSITIONING) || defined(ENABLE_THAI_POSITIONING)
/**
 * Internal Macro
 */
#define ENABLE_MANUAL_POSITIONING
#endif /* ENABLE_HEBREW_POSITIONING || ENABLE_THAI_POSITIONING */

#if defined(LLM_COLOR_FORMAT_MONO) || defined(LLM_COLOR_FORMAT_GRAY)
	#if defined ENABLE_DYNAMIC_COLOR
		#error COMPILE ERROR: Cannot have Mono or Gray color format when ENABLE_DYNAMIC_COLOR is enabled.
	#endif
    #ifdef ENABLE_ALPHA_CHANNEL
		#error COMPILE ERROR: Cannot have Mono or Gray color format when ENABLE_ALPHA_CHANNEL is enabled.
	#endif
	#ifdef ENABLE_LINE_COLOR
		#error COMPILE ERROR: Cannot have Mono or Gray color format when ENABLE_LINE_COLOR is enabled.
	#endif /* ENABLE_LINE_COLOR */
#endif /* LLM_COLOR_FORMAT_MONO || LLM_COLOR_FORMAT_GRAY */

#ifndef ENABLE_DYNAMIC_COLOR
	#if defined(LLM_COLOR_LAYOUT_A8R8G8B8) && defined(ENABLE_ALPHA_CHANNEL)
		#error COMPILE ERROR: ENABLE_ALPHA_CHANNEL and LLM_COLOR_LAYOUT_A8R8G8B8 cannot be turned on together.
	#endif /* LLM_COLOR_LAYOUT_A8R8G8B8 && ENABLE_ALPHA_CHANNEL */
#endif /* !ENABLE_DYNAMIC_COLOR */

#if defined(ENABLE_T1) && defined(ENABLE_KERNING)
/**
 * Internal macro.
 */
#define ENABLE_ALTERNATE_FONT_STREAM
#endif /* ENABLE_T1 && ENABLE_KERNING */
/**
 * Internal Macro. Should be enabled by default.
 */
#define ENABLE_REAL_UDB_DATA

#ifdef ENABLE_BIDIR
/**
 * Internal Macro. Should be enabled by default
 */
#define ENABLE_BIDI_MIRRORING
#endif /* ENABLE_BIDIR */

#if defined  ENABLE_ANCHOR_RUN
	#if !defined ENABLE_EXTRA_RUN_PROPS
		#error COMPILE ERROR: ENABLE_EXTRA_RUN_PROPS should be ON if ENABLE_ANCHOR_RUN is ON
	#endif /* ENABLE_EXTRA_RUN_PROPS */
#endif /* ENABLE_ANCHOR_RUN */

#ifdef ENABLE_MANUAL_OTF
	#if !defined(ENABLE_OTF_GSUB) && !defined(ENABLE_OTF_GPOS)
		#error  COMPILE ERROR: Enable ENABLE_OTF_GSUB or ENABLE_OTF_GPOS for ENABLE_MANUAL_OTF
	#endif /* !ENABLE_OTF_GSUB && !ENABLE_OTF_GPOS */
#endif /* ENABLE_MANUAL_OTF */

#if defined(ENABLE_MANUAL_OTF) || defined(LLM_NEED_SCRIPT)
	#define LLM_CHECK_COMPLEXWORD
#endif /* ENABLE_MANUAL_OTF && LLM_NEED_SCRIPT */

#ifdef ENABLE_LLM_UNICODE32
	#ifndef ENABLE_UNICODE_32_SUPPORT
		#error COMPILE ERROR: Enable ENABLE_UNICODE_32_SUPPORT for ENABLE_LLM_UNICODE32
	#endif /* !ENABLE_UNICODE_32_SUPPORT */
#endif /* ENABLE_LLM_UNICODE32 */

#ifdef ENABLE_AUTO_KERNING
	#ifndef ENABLE_KERNING
		#error COMPILE ERROR: Enable ENABLE_KERNING for ENABLE_AUTO_KERNING 
	#endif /* ENABLE_KERNING */
#endif /* ENABLE_AUTO_KERNING */

#ifdef ENABLE_DYNAMIC_BIDI_CONTROL
	#ifndef ENABLE_BIDIR
		#error COMPILE ERROR: Enable ENABLE_BIDIR for ENBALE_DYNAMIC_BIDI_CONTROL
	#endif /* ENABLE_BIDIR */

	#ifdef ENABLE_FORCE_RTL_DIRECTION
		#error COMPILE_ERROR: Turn off ENABLE_FORCE_RTL_DIRECTION if ENBALE_DYNAMIC_BIDI_CONTROL is on.
	#endif /* ENABLE_FORCE_RTL_DIRECTION */
#endif /* ENABLE_DYNAMIC_BIDI_CONTROL */

#ifdef ENABLE_MILLI_INTERCHAR_SPACE
	#ifndef ENABLE_ACCURATE_DYNAMIC_METRICS
		#error COMPILE ERROR: Enable ENABLE_ACCURATE_DYNAMIC_METRICS when ENABLE_MILLI_INTERCHAR_SPACE is enabled.
	#endif /* !ENABLE_ACCURATE_DYNAMIC_METRICS */
#endif /* ENABLE_ACCURATE_DYNAMIC_METRICS */

#if defined(ENABLE_FRACTIONAL_SIZE) && !defined(ENABLE_ACCURATE_DYNAMIC_METRICS)
	#error COMPILE ERROR: Enable ENABLE_ACCURATE_DYNAMIC_METRICS when ENABLE_FRACTIONAL_SIZE is on.
#endif /* ENABLE_FRACTIONAL_SIZE && !ENABLE_ACCURATE_DYNAMIC_METRICS */

#if defined(ENABLE_CACHE) && !defined(ENABLE_32BIT_CACHE_TAG)
	#error COMPILE ERROR: Enable ENABLE_32BIT_CACHE_TAG for correct glyph caching.
#endif /* ENABLE_CACHE && !ENABLE_32BIT_CACHE_TAG */

#if defined(ENABLE_DROPOUT_ADAPTATION)
	#error COMPILE ERROR: Define ENABLE_DROPOUT_ADAPTATION=0 for correct layout.
#endif /* !ENABLE_DROPOUT_ADAPTATION */

/**
 * Enables user to draw images on screen. Panorama will call the registered image draw fuction, Panorama will provide 
 * the space X,Y co-ordinates and the image index which is to be drawn at that place. User need to implenet the image 
 * draw function available in the platform. Image draw should be used in the following cases :-
 * 1. Inline Images (Static/Floating Images)
 * 2. Unicode Image Mapping.
 */

#if defined(ENABLE_FLOATING_OBJECT) || defined(ENABLE_UNICODE_IMAGE_MAPPING)
#define ENABLE_CUSTOMRUN
#endif /* (defined ENABLE_FLOATING_OBJECT) || (defined ENABLE_UNICODE_IMAGE_MAPPING) */

#ifdef ENABLE_RUN_ANTIALIASED
#define ENABLE_MULTIMODE_GLYPH_CACHING
#endif /* ENABLE_RUN_ANTIALIASED */

#ifdef ENABLE_OTF_GDEF
#define ENABLE_MARKCLASS_CHECK
#endif /* ENABLE_MARKCLASS_CHECK */

/* #define ENABLE_LLM_SELF_VALIDATION */

#endif /* ENABLE_OPENTYPE_SUPPORT */

/*----------------------- Unwanted warnings suppression for cl ------------------------*/
#ifdef _MSC_VER
/* This suppression is for the warning thats generated when an inline method of a class
 * is not used and the header defining that class is included. */
#pragma warning ( disable : 4514 )

/* This suppression is done to remove the warning where i do the assert failures as
 * assert("Error Message" == NULL); */
#pragma warning ( disable : 4130 )

/* Lokesh: 29Mar2005: In Shaping we have macros which are passed constant many times */
#pragma warning ( disable : 4127 )

/* Himanhsu: 25th Sept 2007: In setjmp call from LLManager.*/
#pragma warning ( disable : 4611 )
#endif /* _MSC_VER */

/*----------------------- For backward compatibility ---------------------------------*/
/*** #1 ***/
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

/*** #2 ***/
#ifndef CLIENT_ASSERT
	#define CLIENT_ASSERT( x )					assert( x )
#endif /* CLIENT_ASSERT */

/*** #3 ***/
#ifndef CLIENT_STRLEN
	#define CLIENT_STRLEN( str )				strlen( str )
#endif /* CLIENT_STRLEN */

/*** #4 ***/
#ifndef CLIENT_MEMSET
	#define CLIENT_MEMSET( pd, c, s )			memset( pd, c, s )
#endif /* CLIENT_MEMSET */

#endif /* __LLCONFIG_HEADER__ */

/*********************** R E V I S I O N   H I S T O R Y **********************
 *
 *    $Header: /home/archive/Panorama/layout/LLManager/hdr/LLConfig.h,v 1.90 2009/07/10 12:38:42 ljoshi Exp $
 *
 *    $Log: LLConfig.h,v $
 *    Revision 1.90  2009/07/10 12:38:42  ljoshi
 *    Changes in comments for 5.0 release.
 *
 *    Revision 1.89  2009/04/29 12:06:03  ljoshi
 *    Rearrangement of macros and auto ON
 *
 *    Revision 1.88  2009/04/29 10:49:12  ljoshi
 *    Adding check for FF OPENTYPE Support Macro.
 *
 *    Revision 1.87  2009/04/06 08:44:02  ljoshi
 *    Adding support for ENABLE_UDB_SUPPORT.
 *
 *    Revision 1.86  2009/03/25 11:43:06  himanshu
 *    Adding Support for Windget/Text On Path feature.
 *
 *    Revision 1.85  2009/02/20 06:48:46  ljoshi
 *    Support for ENABLE_MARKCLASS_CHECK
 *
 *    Revision 1.84  2009/02/17 15:02:36  ljoshi
 *    Adding ENABLE_FORMATTING_UNICODE_SUPPORT
 *
 *    Revision 1.83  2009/01/06 18:26:09  ljoshi
 *    Correcting the dependency.
 *
 *    Revision 1.82  2009/01/06 05:03:53  ljoshi
 *    Adding preconditions for macros.
 *
 *    Revision 1.81  2008/11/25 09:23:11  ljoshi
 *    We need accurate metrics when frac mode is on.
 *
 *    Revision 1.80  2008/11/23 14:15:05  ljoshi
 *    Fixes for frac pen.
 *
 *    Revision 1.79  2008/11/13 09:07:13  himanshu
 *    Removing the extra macro (termination_by_height).
 *
 *    Revision 1.78  2008/11/12 12:02:16  himanshu
 *    new feature, termination by height and bug fixing.
 *
 *    Revision 1.77  2008/10/27 07:49:53  ljoshi
 *    Adding new manifest ENABLE_CACHE
 *
 *    Revision 1.76  2008/10/23 06:12:09  ljoshi
 *    Adding condition when milli interchatspace is ON.
 *
 *    Revision 1.75  2008/10/21 10:24:28  ljoshi
 *    Adding support for InterChar space at milli level
 *
 *    Revision 1.74  2008/09/24 05:20:29  ljoshi
 *    Adding support for runtime bidi control.
 *
 *    Revision 1.73  2008/09/12 12:00:23  ljoshi
 *    Adding ENABLE_ACCURATE_DYNAMIC_METRICS.
 *
 *    Revision 1.72  2008/08/25 13:56:27  ljoshi
 *    Adding more checks for incompatible macros.
 *
 *    Revision 1.71  2008/08/18 06:12:33  ljoshi
 *    Adding extended bidi mirroring and extended mirroring support .
 *
 *    Revision 1.70  2008/08/12 10:08:22  ljoshi
 *    Disabling Thai shaping by default.
 *
 *    Revision 1.69  2008/07/23 12:05:06  himanshu
 *    Adding support for run based anti-aliasing, all code is in ENABLE_RUN_ANTIALIASED macro.
 *
 *    Revision 1.68  2008/07/07 12:38:13  ljoshi
 *    Adding macros for Library functions.
 *
 *    Revision 1.67  2008/07/03 09:03:13  himanshu
 *    Adding support for Unicode Image Mapping and Floating Objects.
 *
 *    Revision 1.66  2008/07/03 03:57:19  ljoshi
 *    Adding support for user defined line color support under macro ENABLE_LINE_COLOR.
 *
 *    Revision 1.65  2008/06/20 08:30:47  ljoshi
 *    Adding auto kerning.
 *
 *    Revision 1.64  2008/06/17 15:39:29  ljoshi
 *    Adding macros for backward compatability with FontFusion releases.
 *
 *    Revision 1.63  2008/06/13 08:51:47  ljoshi
 *    Adding ENABLE_FORCE_RTL_DIRECTION to force RtoL if single R/AL character is there.
 *
 *    Revision 1.62  2008/06/11 02:52:07  ljoshi
 *    Adding LLM_USE_SEAT_BELTS
 *
 *    Revision 1.61  2008/03/31 15:25:04  ljoshi
 *    Warning fix.
 *
 *    Revision 1.60  2008/03/04 16:15:31  ljoshi
 *    Comments corrected.
 *
 *    Revision 1.59  2008/03/04 15:28:59  ljoshi
 *    Adding 32bit Unicode Support
 *
 *    Revision 1.58  2008/02/07 08:34:27  ljoshi
 *    Adding manifest ENABLE_MANUAL_OTF for confuguration of manual OTF application.
 *
 *    Revision 1.57  2008/02/06 05:45:34  himanshu
 *    Space Wrap support.
 *
 *    Revision 1.56  2008/01/24 14:41:52  ljoshi
 *    Himanshu: Adding support for line termination and termination style.
 *
 *    Revision 1.55  2008/01/21 14:30:45  ljoshi
 *    Adding support for parallel Alpha Channel and A8R8G8B8 support.
 *
 *    Revision 1.54  2008/01/15 12:48:46  ljoshi
 *    Adding the internal macro for self validation.
 *
 *    Revision 1.53  2007/12/10 14:53:39  ljoshi
 *    Adding supprt for faulty metrcs under ENABLE_RUNTIME_METRICSCHECK
 *
 *    Revision 1.52  2007/12/05 10:24:54  ljoshi
 *    Making ENABLE_CHECK_TAG_CASE off by default.
 *
 *    Revision 1.51  2007/11/28 14:37:07  ljoshi
 *    Ritesh:Changes done for enabling dynamic color support in iterator mode.Moved the glypiter and glyphobj codes under the macro ENABLE_GLYPH_ITERATOR and ENABLE_GLYPH_OBJ respectively.
 *
 *    Revision 1.50  2007/11/12 04:47:57  himanshu
 *    Making changes to Pano files according to the new Include system in FF.
 *
 *    Revision 1.49  2007/11/07 06:46:19  ljoshi
 *    Fixing comment error.
 *
 *    Revision 1.48  2007/10/19 14:00:55  ljoshi
 *    Ritesh:Changed done for style based selection of fonts under the macro ENABLE_LLM_EXTENSION.
 *
 *    Revision 1.47  2007/10/15 05:50:03  ljoshi
 *    Adding support for GASP
 *
 *    Revision 1.46  2007/10/11 08:41:19  himanshu
 *    Adding support for anchor run, code under ENABLE_ANCHOR_RUN macro.
 *
 *    Revision 1.45  2007/10/08 06:08:51  ljoshi
 *    Support for multi aliasmode glyphs caching under ENABLE_MULTIMODE_GLYPH_CACHING macro.
 *
 *    Revision 1.44  2007/09/25 10:53:00  himanshu
 *    Support for the Unicode Range Based font toggling.
 *
 *    Revision 1.43  2007/09/13 09:18:14  ljoshi
 *    Adding support to make LLConfig.h file name configurable.
 *
 *    Revision 1.42  2007/09/13 06:40:10  ljoshi
 *    Adding support for configurable header names.
 *
 *    Revision 1.41  2007/09/10 10:10:23  ljoshi
 *    Adding new line to end of file.
 *
 *    Revision 1.40  2007/08/29 10:05:19  ljoshi
 *    Support and fixes for tabstops
 *
 *    Revision 1.39  2007/08/27 11:12:01  ljoshi
 *    Added client macro for CLIENT_MEMCMP
 *
 *    Revision 1.38  2007/08/25 20:12:27  ljoshi
 *    Adding support for TABs
 *
 *    Revision 1.37  2007/08/17 05:12:22  ljoshi
 *    Adding support for alternate file for Type1 Fonts.
 *
 *    Revision 1.36  2007/08/14 08:52:45  ljoshi
 *    Turning ENABLE_FONT_FILE_SUPPORT off by default
 *
 *    Revision 1.35  2007/07/18 10:03:52  ljoshi
 *    Adding support for run specific interchar space and correcting render syllable api.
 *
 *    Revision 1.34  2007/06/15 10:50:25  ljoshi
 *    Adding support for multiple LLManager light instances
 *
 *    Revision 1.33  2007/06/12 07:12:44  ljoshi
 *    Adding support for paragraph specifi indentation support.
 *
 *    Revision 1.32  2007/06/12 04:26:44  ljoshi
 *    Adding support for paragraph specific properties as indents, line gaps, alignment.
 *
 *    Revision 1.31  2007/05/02 16:13:42  ljoshi
 *    internal macro ENABLE_REAL_UDB_DATA should be enabled by default.
 *
 *    Revision 1.30  2007/05/01 12:27:00  ljoshi
 *    Adding internal macro ENABLE_REAL_UDB_DATA
 *
 *    Revision 1.29  2007/04/21 18:54:32  ljoshi
 *    Fix for various macro combinations.
 *
 *    Revision 1.28  2007/04/18 12:41:47  ljoshi
 *    Comments fixed.
 *
 *    Revision 1.27  2007/04/18 04:57:55  ljoshi
 *    Support for A8R8G8B8 color format
 *
 *    Revision 1.26  2007/04/17 10:00:50  ljoshi
 *    Introdcing the macro ENABLE_LINEGAP for LineGap.
 *
 *    Revision 1.25  2007/04/10 06:27:42  ljoshi
 *    Documentation
 *
 *    Revision 1.24  2007/04/09 05:40:46  ljoshi
 *    Added ENABLE_LLMANAGAER_NEWDELETE to support the platforms where new/delete has a problem.
 *
 *    Revision 1.23  2007/03/26 12:54:35  ljoshi
 *    Support for Alpha Channel
 *
 *    Revision 1.22  2007/02/27 12:55:48  ljoshi
 *    Changes for Manual Positioning for Thai and Hebrew.
 *
 *    Revision 1.21  2007/02/22 13:03:26  himanshu
 *    Making default color mode as RGB and error when dynamic color is ON in mono/gray mode.
 *
 *    Revision 1.20  2007/02/13 06:41:31  ljoshi
 *    Initial CVS Version
 *
 *
******************************************************************************/
