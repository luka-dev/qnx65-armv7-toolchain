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




#ifndef __PHGULLIVER_H_INCLUDED
#define __PHGULLIVER_H_INCLUDED

#include <photon/Pg.h>

#if defined(__BIGENDIAN__)
	#include <gulliver.h>

	#define PhEndianFixLong( ptr )			ENDIAN_SWAP32( ptr )
	#define PhEndianFixShort( ptr )			ENDIAN_SWAP16( ptr )
	extern void PhEndianFixImage( PhImage_t *ptr );
	extern void PhEndianFixImageData( PhImage_t const *ptr );
	extern void PhEndianFixAlpha( PgAlpha_t *ptr );
	extern void PhEndianFixLongArray( unsigned long *ptr, unsigned n );
	extern void PhEndianFixShortArray( unsigned short *ptr, unsigned n );
	extern void PhEndianFixDim( PhDim_t * );
	extern void PhEndianFixPoint( PhPoint_t * );
	extern void PhEndianFixArea( PhArea_t * );
	extern void PhEndianFixRect( PhRect_t * );
	#define PhEndianGetLong( val )			ENDIAN_LE32(val)
	#define PhEndianGetShort( val )			ENDIAN_LE16(val)
	#define PhEndianFixInt( ptr )			(	sizeof(*(ptr)) == sizeof(short) ? (void) PhEndianFixShort(ptr) \
											:	sizeof(*(ptr)) == sizeof(long) ?  (void) PhEndianFixLong(ptr) \
											:	(void)(ptr) )
#elif defined(__LITTLEENDIAN__) || !defined(__QNXNTO__)
	#define PhEndianFixLong( ptr )			( (void)(ptr) )
	#define PhEndianFixShort( ptr )			( (void)(ptr) )
	#define PhEndianFixImage( ptr )			( (void)(ptr) )
	#define PhEndianFixImageData( ptr )		( (void)(ptr) )
	#define PhEndianFixAlpha( ptr )			( (void)(ptr) )
	#define PhEndianFixDim( ptr )			( (void)(ptr) )
	#define PhEndianFixPoint( ptr )			( (void)(ptr) )
	#define PhEndianFixArea( ptr )			( (void)(ptr) )
	#define PhEndianFixRect( ptr )			( (void)(ptr) )
	#define PhEndianFixLongArray( ptr, n )	( (void)(ptr), (void)(n) )
	#define PhEndianFixShortArray( ptr, n )	( (void)(ptr), (void)(n) )
	#define PhEndianFixInt( ptr )			( (void)(ptr) )
	#define PhEndianGetLong( val )			( val )
	#define PhEndianGetShort( val )			( val )
#else
	#error ENDIAN Not defined for system
#endif

#define PhEndianFixColorArray	PhEndianFixLongArray
#define PhEndianFixColor		PhEndianFixLong
#define PhEndianGetColor		PhEndianGetLong

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PhGulliver.h $ $Rev: 219996 $" )
#endif
