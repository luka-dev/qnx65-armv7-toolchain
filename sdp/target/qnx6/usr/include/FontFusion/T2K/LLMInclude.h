/*
 * LLMInclude.h
 * $Header: /home/archive/Panorama/layout/LLManager/hdr/LLMInclude.h,v 1.5 2009/03/25 11:43:06 himanshu Exp $
 * Font Fusion Copyright (c) 1989-2007 all rights reserved by Bitstream Inc.
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

#ifndef __LLMINCLUDE_HEADER__
#define __LLMINCLUDE_HEADER__

#ifndef FF_FFCONFIG_HEADER
#include "config.h"
#else
#include FF_FFCONFIG_HEADER
#endif /* FF_FFCONFIG_HEADER */

/* LLManager Headers */
#define LLM_DEFAULTFONT_HEADER				"defaultfont.h"
#define LLM_GLYPHITER_HEADER				"glyphiter.h"
#define LLM_GLYPHOBJ_HEADER					"glyphobj.h"
#define LLM_LLMANAGER_HEADER				"LLManager.h"
#define LLM_LLMANAGERPRVT_HEADER			"LLManagerPrvt.h"
#define LLM_LLMCALLBACK_HEADER				"LLMCallback.h"
#define LLM_LLMFILTER_HEADER				"LLMFilter.h"
#define LLM_LLMLIST_HEADER					"LLMList.h"
#define LLM_LLMMEMMAN_HEADER				"LLMMemMan.h"
#define LLM_LLMRUNITER_HEADER				"LLMRunIter.h"
#define LLM_LLMTYPES_HEADER					"LLMTypes.h"
#define LLM_OTFCOLOR_HEADER					"otfcolor.h"
#define LLM_OTFITER_HEADER					"otfiter.h"
#define LLM_SHAPING_HEADER					"shaping.h"
#define LLM_UDB_HEADER						"udb.h"
#define LLM_WIDGET_HEADER					"LLMWidget.h"

/* OTF Headers */
#define LLM_BASE_HEADER						"base.h"
#define LLM_GDEF_HEADER						"gdef.h"
#define LLM_GSUBPOS_HEADER					"gsubpos.h"
#define LLM_JSTF_HEADER						"jstf.h"
#define LLM_OTF_HEADER						"otf.h"
#define LLM_OTFBASETAG_HEADER				"otfbasetag.h"
#define LLM_OTFCOMMON_HEADER				"otfcommon.h"
#define LLM_OTFFEATURE_HEADER				"otffeature.h"
#define LLM_OTFLANGSYS_HEADER				"otflangsys.h"
#define LLM_OTFSCRIPT_HEADER				"otfscript.h"
#define LLM_PLACER_HEADER					"placer.h"
#define LLM_VALGSUBPOS_HEADER				"valgsubpos.h"

/* Standard Headers */
#define LLM_STD_STDIO_HEADER				<stdio.h>
#define LLM_STD_STDLIB_HEADER				<stdlib.h>
#define LLM_STD_ASSERT_HEADER				<assert.h>
#define LLM_STD_STRING_HEADER				<string.h>

#ifndef FF_DTYPES_HEADER
#define FF_DTYPES_HEADER					"dtypes.h"
#endif /* FF_DTYPES_HEADER */

#ifndef FF_T2K_HEADER
#define FF_T2K_HEADER						"t2k.h"
#endif /* FF_T2K_HEADER */

#ifndef FF_TT_PRVT_HEADER
#define FF_TT_PRVT_HEADER					"tt_prvt.h"
#endif /* FF_TT_PRVT_HEADER */

#ifndef FF_CACHEMANAGER_HEADER
#define FF_CACHEMANAGER_HEADER				"cachemgr.h"
#endif /* FF_CACHEMANAGER_HEADER */

#ifndef FF_T2KEXTRA_HEADER
#define FF_T2KEXTRA_HEADER					"t2kextra.h"
#endif /* FF_T2KEXTRA_HEADER */

#ifndef FF_TSIMEM_HEADER
#define FF_TSIMEM_HEADER					"tsimem.h"
#endif /* FF_TSIMEM_HEADER */

#ifndef FF_TRUETYPE_HEADER
#define FF_TRUETYPE_HEADER					"truetype.h"
#endif /* FF_TRUETYPE_HEADER */

#ifndef FF_T2KSTRM_HEADER
#define FF_T2KSTRM_HEADER					"t2kstrm.h"
#endif /* FF_T2KSTRM_HEADER */

#ifndef FF_GLYPH_HEADER
#define FF_GLYPH_HEADER						"glyph.h"
#endif /* FF_GLYPH_HEADER */

#ifndef FF_ORION_HEADER
#define FF_ORION_HEADER						"orion.h"
#endif /* FF_ORION_HEADER */

#ifndef FF_UTIL_HEADER
#define FF_UTIL_HEADER						"util.h"
#endif /* FF_UTIL_HEADER */

#ifndef FF_AUTOGRID_HEADER
#define FF_AUTOGRID_HEADER					"autogrid.h"
#endif /* FF_AUTOGRID_HEADER */

#ifndef FF_GHINTS_HEADER
#define FF_GHINTS_HEADER					"ghints.h"
#endif /* FF_GHINTS_HEADER */

#ifndef FF_SYSHEAD_HEADER
#define FF_SYSHEAD_HEADER					"syshead.h"
#endif /* FF_SYSHEAD_HEADER */

#ifdef YOUR_COMPANY
#else
/* Include the common headers */
#include LLM_STD_STDIO_HEADER
#include LLM_STD_STDLIB_HEADER
#include LLM_STD_ASSERT_HEADER
#include LLM_STD_STRING_HEADER
#endif /* YOUR_COMPANY */

#endif /* __LLMINCLUDE_HEADER__ */

/*********************** R E V I S I O N   H I S T O R Y **********************
*
*    $Header: /home/archive/Panorama/layout/LLManager/hdr/LLMInclude.h,v 1.5 2009/03/25 11:43:06 himanshu Exp $
*
*    $Log: LLMInclude.h,v $
*    Revision 1.5  2009/03/25 11:43:06  himanshu
*    Adding Support for Windget/Text On Path feature.
*
*    Revision 1.4  2007/11/12 05:57:58  himanshu
*    Bug fixing.
*
*    Revision 1.3  2007/11/12 04:47:57  himanshu
*    Making changes to Pano files according to the new Include system in FF.
*
*    Revision 1.2  2007/09/13 07:09:13  ljoshi
*    Correcting the filenames.
*
*    Revision 1.1  2007/09/13 06:45:55  ljoshi
*    Initial Version.
*
*
*
******************************************************************************/

