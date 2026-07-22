/* Copyright 2009, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to 
 * QNX Software Systems before you may reproduce, modify or distribute this 
 * software, or any work that includes all or part of this software.  Free 
 * development licenses are available for evaluation and non-commercial purposes.  
 * For more information visit http://licensing.qnx.com or email licensing@qnx.com.
 * 
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 */
#ifdef __cplusplus
extern "C" {
#endif

#ifndef _PXIMAGE_H_INCLUDED
#define _PXIMAGE_H_INCLUDED

#include <Ph.h>
#include <stdio.h>

/* Macro to calculate 16.16 percentage a of b */

#define PX_PERCENTAGE(a,b) \
	(((((a) * 100) / (b)) << 16) | (((((a) * 100) % (b)) << 16) / (b)))


/* PxImageFunct_t format definitions */
#define PX_IMAGE_BMP		0x00
#define PX_IMAGE_GIF		0x01
#define PX_IMAGE_JPG		0x02
#define PX_IMAGE_PCX		0x03
#define PX_IMAGE_TGA		0x04
#define PX_IMAGE_PNG 		0x05
#define PX_IMAGE_TIFF		0x06
#define PX_IMAGE_XBM		0x07
#define PX_IMAGE_PHIMAGE	0x08

/* PxMethods_t flag definitions */
#define PX_LOAD				0x00
#define PX_QUERY			0x01
#define PX_SUPPRESS_CRC		0x02
#define PX_SUPPRESS_TAG		0x02
#define PX_DIRECT_COLOR		0x04
#define PX_TRANSPARENT		0x08
/*#define PX_SCALE			0x10 */
#define PX_USECOLORS		0x20
#define PX_DODITHER			0x40

/* px_alloc( ) type definitions */
#define PX_NORMAL			0x00
#define PX_IMAGE			0x01
#define PX_PALETTE			0x02
#define PX_METHODS			0x80000000

typedef struct pxmethods
{
	int			flags;
	void		*(*px_alloc)( long nbytes, int type );
	void		*(*px_free)( void *memory, int type );
	void		*(*px_error)( char *msg );
	void		*(*px_warning)( char *msg );
	void		*(*px_progress)( int );
	PhDim_t		scale;
	void		*colors;
	int			ncolors;
} PxMethods_t;

extern FILE			*PxFp;
extern PhImage_t	*PxImage;

void PxTerminate( PhImage_t *image );
PhImage_t * PxLoadImage( char const *filename, PxMethods_t const *methods );
int PxWriteImage( char const *filename, PhImage_t const *image, PxMethods_t const *methods, int iformat, int itype );
int PxGetImageExtensions( char *extlist, int len, char const *prefix );
long PxCRC( const char *buffer, int nbytes );

#define	PXIMG_ANGLE_90CW	0x0001921f  /* 90 degrees clockwise */
#define	PXIMG_ANGLE_90CCW	0x0004b65f  /* 90 degrees counterclockwise */
#define	PXIMG_ANGLE_180		0x0003243f  /* 180 degrees */

int PxRotateImage( PhImage_t const *src, PhImage_t *dst, unsigned angle, PxMethods_t const *methods);

#endif

#ifdef __cplusplus
}
#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/phexlib/public/photon/PxImage.h $ $Rev: 224591 $" )
#endif
