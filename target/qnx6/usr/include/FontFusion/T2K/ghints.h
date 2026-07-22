/*
 * Ghints.h
 * Font Fusion Copyright (c) 1989-1999 all rights reserved by Bitstream Inc.
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

#ifdef ENABLE_AUTO_GRIDDING_CORE

#ifndef __T2K_GHINTS__
#define __T2K_GHINTS__
#ifdef __cplusplus
extern "C" {            
#endif  

void t2k_ComputeGlobalHints( sfntClass *font, ag_HintHandleType hintHandle, ag_GlobalDataType *gHints, int kanji );
void t2k_ReadGHints( ag_GlobalDataType *gHints, InputStream *in );
void t2k_WriteGHints( ag_GlobalDataType *gHints, OutputStream *out );


#ifdef __cplusplus
}
#endif  
#endif 

#endif 





