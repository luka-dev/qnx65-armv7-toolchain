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
#if !defined(AL_H_INCLUDED)
#define AL_H_INCLUDED

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct Al_db AlDataBase_t;

typedef struct {
	const char		*wgt_name;
	unsigned long	res_value;
	const char		*res_descr;
	unsigned long	res_index;
	const char		*wgt_font;
	const char		*str_original;
	const char		*str_translated;
	unsigned long	res_flags;
	const char		*item_name;
	}
		AlTextEntry_t;

enum AlResFlags {
	Al_MULTILINE   = 1,
	Al_ACCELERATOR = 2,
	Al_ISMESSAGE   = 4,
	Al_ISMENUITEM  = 8
	};

extern AlDataBase_t *AlOpenDBase( const char *path );  /* Read database file into memory */
extern int AlReadTranslation( AlDataBase_t *db, const char *path );  /* Read translation file into memory */
extern int AlSaveTranslation( AlDataBase_t const *db, const char *path );  /* Save translation file */
extern void AlClearTranslation( AlDataBase_t *db );
extern void AlCloseDBase( AlDataBase_t *db );  /* Free memory */
extern int AlGetVersion( AlDataBase_t const *db );

extern unsigned AlGetSize( AlDataBase_t const *db );
extern const AlTextEntry_t *AlGetEntry( AlDataBase_t const *db, unsigned index );
extern int AlSetEntry( AlDataBase_t *db, unsigned index, const char *string );
extern int AlSetVersion( AlDataBase_t *db, int version ); /* Set format for saving */

#ifdef __cplusplus
}
#endif

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/phexlib/public/photon/Al.h $ $Rev: 224591 $" )
#endif
