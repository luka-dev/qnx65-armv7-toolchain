/*
 * $Header: /home/archive/FontFusion/FontFusion/core/t2kotf.h,v 1.1 2009/04/29 10:34:00 ljoshi Exp $
 * 
 * t2kotf.c
 * Font Fusion Copyright (c) 1989-2009 all rights reserved by Bitstream Inc.
 * http://www.bitstream.com/
 * Author: Lokesh Joshi
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

#ifndef __T2KOTF_HEADER__
#define __T2KOTF_HEADER__
#ifdef __cplusplus
extern "C" {            
#endif  

#ifndef FF_FFCONFIG_HEADER
#include "config.h"
#else
#include FF_FFCONFIG_HEADER
#endif 
	
#ifdef ENABLE_OPENTYPE_SUPPORT
	
typedef void * otfHandle;
	
typedef struct t2kotfClass_t
{
	otfHandle otf;
	otfHandle placer;
	otfHandle gidListMemMan;
	otfHandle uniListMemMan;
	otfHandle reposMemMan;

	otfHandle gHead;
	otfHandle gTail;
	otfHandle uHead;
	otfHandle uTail;	
	tsiMemObject * mem;
	otfHandle * scaler;
}t2kotfClass;
	
t2kotfClass * New_t2kotfClass( tsiMemObject *mem, InputStream * in, void * font);
void Delete_t2kotfClass(t2kotfClass * t2kotf);
uint16 applyOTFFeaturesOnGlyph (t2kotfClass * t2kotf, void * scaler, uint16 unicode, int isGindex, uint16 featureVector, int isGSUB);

#endif 
	
#ifdef __cplusplus
}
#endif  

#endif 
