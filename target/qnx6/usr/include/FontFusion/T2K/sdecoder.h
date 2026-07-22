/*
 * scodecdefs.h
 * Font Fusion Copyright (c) 1989-2005 all rights reserved by Bitstream Inc.
 * http://www.bitstream.com/
 * http://www.typesolutions.com/
 * Author: Anup Belambe/Tohin
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

#ifndef SDECODER
#define SDECODER


#ifdef COMPRESSED_INPUT_STREAM

#ifndef FF_FFCONFIG_HEADER
#include "config.h"
#else
#include FF_FFCONFIG_HEADER
#endif 

#include FF_SCODECDEFS_HEADER

PCBLOCKCACHE
sc_load_cstream(tsiMemObject* mem, uint8* enc_data, uint32 length);

PCBLOCKCACHE
sc_load_cstream1(PCBLOCKCACHE srcCache, uint32 offset, uint32 length);

void
sc_cstream_cache_reload(PCBLOCKCACHE cache, int32 abs_pos, int32 savebytes);

void
sc_cstream_cache_reload_if_needed(PCBLOCKCACHE cache, int32 abs_pos, int32 savebytes);

void
sc_delete_cstream(PCBLOCKCACHE cache);

void
sc_delete_cstream1(PCBLOCKCACHE cache);

#ifdef SELF_TEST_CSTREAM
void
test_compressed_stream(tsiMemObject* mem, const char* szin_edata, const char* szinput_file);
#endif

#endif	
#endif	


