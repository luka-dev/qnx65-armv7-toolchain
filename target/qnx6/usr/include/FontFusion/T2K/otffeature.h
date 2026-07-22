/*
 * otffeature.h
 * $Header: /home/archive/Panorama/layout/otf/hdr/otffeature.h,v 1.9 2007/11/12 04:47:57 himanshu Exp $
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


#ifndef __OTFFEATURE_HEADER__
#define __OTFFEATURE_HEADER__

#ifndef LLM_LLCONFIG_HEADER
#include "LLConfig.h"
#else
#include LLM_LLCONFIG_HEADER
#endif 
#include FF_DTYPES_HEADER

#if defined(ENABLE_LLE) && defined(ENABLE_OTF)

#ifdef __cplusplus
extern "C" {
#endif 


typedef enum {

	GSUBPOS_AALT = 0,
	GSUBPOS_ABVF,
	GSUBPOS_ABVM,
	GSUBPOS_ABVS,
	GSUBPOS_AFRC,
	GSUBPOS_AKHN,
	GSUBPOS_BLWF,
	GSUBPOS_BLWM,
	GSUBPOS_BLWS,
	GSUBPOS_C2PC,
	GSUBPOS_C2SC,
	GSUBPOS_CALT,
	GSUBPOS_CASE,
	GSUBPOS_CCMP,
	GSUBPOS_CLIG,
	GSUBPOS_CPSP,
	GSUBPOS_CRCY, 
	GSUBPOS_CSWH,
	GSUBPOS_CURS,
	GSUBPOS_DIST,
	GSUBPOS_DLIG,
	GSUBPOS_DNOM,
	GSUBPOS_EXPT,
	GSUBPOS_FALT,
	GSUBPOS_FIN2,
	GSUBPOS_FIN3,
	GSUBPOS_FINA,
	GSUBPOS_FRAC,
	GSUBPOS_FWID,
	GSUBPOS_HALF,
	GSUBPOS_HALN,
	GSUBPOS_HALT,
	GSUBPOS_HIST,
	GSUBPOS_HKNA,
	GSUBPOS_HLIG,
	GSUBPOS_HNLG,
	GSUBPOS_HOJO,
	GSUBPOS_HWID,
	GSUBPOS_INIT,
	GSUBPOS_ISOL,
	GSUBPOS_ITAL,
	GSUBPOS_JALT,
	GSUBPOS_JP03,
	GSUBPOS_JP78,
	GSUBPOS_JP83,
	GSUBPOS_JP90,
	GSUBPOS_KERN,
	GSUBPOS_LFBD,
	GSUBPOS_LIGA,
	GSUBPOS_LJMO,
	GSUBPOS_LNUM,
	GSUBPOS_LOCL,
	GSUBPOS_MARK,
	GSUBPOS_MED2,
	GSUBPOS_MEDI,
	GSUBPOS_MGRK,
	GSUBPOS_MKMK,
	GSUBPOS_MSET,
	GSUBPOS_NALT,
	GSUBPOS_NLCK,
	GSUBPOS_NUKT,
	GSUBPOS_NUMR,
	GSUBPOS_ONUM,
	GSUBPOS_OPBD,
	GSUBPOS_ORDN,
	GSUBPOS_ORNM,
	GSUBPOS_PALT,
	GSUBPOS_PCAP,
	GSUBPOS_PNUM,
	GSUBPOS_PREF,
	GSUBPOS_PRES,
	GSUBPOS_PSTF,
	GSUBPOS_PSTS,
	GSUBPOS_PWID,
	GSUBPOS_QWID,
	GSUBPOS_RAND,
	GSUBPOS_RLIG,
	GSUBPOS_RPHF,
	GSUBPOS_RTBD,
	GSUBPOS_RTLA,
	GSUBPOS_RUBY,
	GSUBPOS_SALT,
	GSUBPOS_SINF,
	GSUBPOS_SIZE,
	GSUBPOS_SMCP,
	GSUBPOS_SMPL,
	GSUBPOS_SS01,
	GSUBPOS_SS02,
	GSUBPOS_SS03,
	GSUBPOS_SS04,
	GSUBPOS_SS05,
	GSUBPOS_SS06,
	GSUBPOS_SS07,
	GSUBPOS_SS08,
	GSUBPOS_SS09,
	GSUBPOS_SS10,
	GSUBPOS_SS11,
	GSUBPOS_SS12,
	GSUBPOS_SS13,
	GSUBPOS_SS14,
	GSUBPOS_SS15,
	GSUBPOS_SS16,
	GSUBPOS_SS17,
	GSUBPOS_SS18,
	GSUBPOS_SS19,
	GSUBPOS_SS20,
	GSUBPOS_SUBS,
	GSUBPOS_SUPS,
	GSUBPOS_SWSH,
	GSUBPOS_TITL,
	GSUBPOS_TJMO,
	GSUBPOS_TNAM,
	GSUBPOS_TNUM,
	GSUBPOS_TRAD,
	GSUBPOS_TWID,
	GSUBPOS_UNIC,
	GSUBPOS_VALT,
	GSUBPOS_VATU,
	GSUBPOS_VERT,
	GSUBPOS_VHAL,
	GSUBPOS_VJMO,
	GSUBPOS_VKNA,
	GSUBPOS_VKRN,
	GSUBPOS_VPAL,
	GSUBPOS_VRT2,
	GSUBPOS_ZERO,
	GSUBPOS_UNWN,

	
	MAX_FEATURE_NAME

}LLMFeatureName;


typedef struct {

	uint32 tag;
	LLMFeatureName id;

#ifdef ENABLE_OTFTAGS_STRINGS
	char * name;
#endif 

} OTFFeatureTag;



int
isFeatureSupported (uint32 tag);

const OTFFeatureTag *
getFeatureFromID (LLMFeatureName id);

const OTFFeatureTag *
getFeatureFromTag (uint32 tag);

#ifdef __cplusplus
}
#endif 

#endif 

#endif 



