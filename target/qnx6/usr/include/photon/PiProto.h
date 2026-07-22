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
 * PiProto.h	
 *		Prototypes for the Photon imaging (Pi) suite
 *

 */

#ifndef __PI_PROTO_H_INCLUDED
#define __PI_PROTO_H_INCLUDED

#ifndef __PT_T_H_INCLUDED
#include <photon/PtT.h>
#endif

#ifndef __PI_T_H_INCLUDED
#include <photon/PiT.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int PiGetPixelFromData( uint8_t const *, int, ushort_t, ulong_t *);
extern int PiGetPixel( PhImage_t const *, ushort_t, ushort_t, ulong_t * );
extern int PiGetPixelRGB( PhImage_t const *, ushort_t, ushort_t, PgColor_t * );
extern int PiSetPixelInData( uint8_t *, int, ushort_t, ulong_t );
extern int PiSetPixel( PhImage_t *, ushort_t, ushort_t, ulong_t );
extern PhImage_t *PiInitImage(PhImage_t *, PhRect_t const *, PhRect_t *,int ,int flags,int );
extern PhImage_t *PiConvertImage(PhImage_t *, PhRect_t const *,int type,int flags);
extern PhImage_t *PiDuplicateImage(PhImage_t *,int );
extern PhImage_t *PiCropImage(PhImage_t *, PhRect_t const *, int );
extern PhImage_t *PiFlipImage(PhImage_t *, PhRect_t const *, int );
extern PhImage_t *PiResizeImage(PhImage_t *, PhRect_t const *, short, short, int );

#ifdef __cplusplus
};
#endif /* __cplusplus */

#include <photon/PhPackPop.h>

#endif /* __PT_PROTO_H_INCLUDED */


#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PiProto.h $ $Rev: 219996 $" )
#endif
