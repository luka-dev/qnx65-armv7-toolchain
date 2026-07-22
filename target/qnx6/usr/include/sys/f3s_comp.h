/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to QNX 
 * Software Systems before you may reproduce, modify or distribute this software, 
 * or any work that includes all or part of this software.   Free development 
 * licenses are available for evaluation and non-commercial purposes.  For more 
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *  
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/ 
 * for other information.
 * $
 */




/*
** File: f3s_comp.h
**
** Description:
**
** This file contains the compression structure definitions for the f3s
** resource manager for Neutrino
**
** Ident: $Id: f3s_comp.h 219996 2009-05-04 18:47:03Z keith $
*/

/*
** Include Loop Prevention
*/

#ifndef __F3S_COMP_H_INCLUDED
#define __F3S_COMP_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

/* Constant definitions */

#define F3S_COMP_NO_SIG    0x0001  /* no sig (and type) fields in header */
#define F3S_COMP_NO_RAW    0x0002  /* not raw data */

#define F3S_COMP_TYPE      0x00f0  /* decompressor type */
#define F3S_COMP_FZIP      0x00f0  /* decompressor is zlib */
#define F3S_COMP_FLZO      0x00e0  /* decompressor is lzo */
#define F3S_COMP_FBZ2      0x00d0  /* decompressor is bz2 */
#define F3S_COMP_FUCL      0x00c0  /* decompressor is ucl */

#define F3S_FZIP_SIG       "F3S_FZIP"              /* zlib signature */
#define F3S_FLZO_SIG       "F3S_FLZO"              /* lzo signature */
#define F3S_FUCL_SIG       "F3S_FUCL"              /* ucl signature */
#define F3S_FBZ2_SIG       "F3S_FBZ2"              /* bz2 signature */
#define F3S_COMP_SIG_SIZE  8                       /* signature length */

/* Compression header info */

typedef struct f3s_comp_s
{
  _Uint16t status;         /* status of dirent */
  _Uint16t struct_size;    /* size of this structure */
  _Uint16t compress_size;  /* size of compressed data */
  _Uint16t normal_size;    /* size of uncompressed data */
/*_Uint8t  sig[8];            optional signature for compressed block */
/*_Uint8t  data[];            compressed data */
}
f3s_comp_t;

#endif /* __F3S_COMP_H_INCLUDED */

/*
** End
*/

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/fs-flash/public/sys/f3s_comp.h $ $Rev: 219996 $" )
#endif
