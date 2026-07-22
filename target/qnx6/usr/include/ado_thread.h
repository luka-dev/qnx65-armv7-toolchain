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
 *      ado_thread.c
 *              The header of wrappers around the pthread_* functions.
 */

#ifndef _ADO_THREAD_H_INCLUDED_
#define _ADO_THREAD_H_INCLUDED_

#include <pthread.h>

/***** defines **************/
#define ADO_MUTEX_INITIALIZER	PTHREAD_MUTEX_INITIALIZER

#ifdef ADO_DEBUG
#define ado_mutex_init(mutex)				ado_mutex_init_recursive_debug(mutex, __FILE__, __LINE__)
#define ado_mutex_init_default(mutex)		ado_mutex_init_default_debug(mutex, __FILE__, __LINE__)
#define ado_mutex_init_recursive(mutex)		ado_mutex_init_recursive_debug(mutex, __FILE__, __LINE__)
#define ado_mutex_lock(mutex)				ado_mutex_lock_debug(mutex, __FILE__, __LINE__)
#define ado_mutex_unlock(mutex)				ado_mutex_unlock_debug(mutex, __FILE__, __LINE__)
#define ado_mutex_destroy(mutex)			ado_mutex_destroy_debug(mutex, __FILE__, __LINE__)
#else
#define ado_mutex_init(mutex)				ado_mutex_init_recursive_nodebug(mutex)
#define ado_mutex_init_default(mutex)		pthread_mutex_init(mutex, NULL)
#define ado_mutex_init_recursive(mutex)		ado_mutex_init_recursive_nodebug(mutex)
#define ado_mutex_lock(mutex)				pthread_mutex_lock(mutex)
#define ado_mutex_unlock(mutex)				pthread_mutex_unlock(mutex)
#define ado_mutex_destroy(mutex)			pthread_mutex_destroy(mutex)
#endif

#ifdef ADO_DEBUG
#define ado_rwlock_init(rwl)		ado_rwlock_init_debug(rwl, __FILE__, __LINE__)
#define ado_rwlock_rdlock(rwl)		ado_rwlock_rdlock_debug(rwl, __FILE__, __LINE__)
#define ado_rwlock_wrlock(rwl)		ado_rwlock_wrlock_debug(rwl, __FILE__, __LINE__)
#define ado_rwlock_unlock(rwl)		ado_rwlock_unlock_debug(rwl, __FILE__, __LINE__)
#define ado_rwlock_destroy(rwl)		ado_rwlock_destroy_debug(rwl, __FILE__, __LINE__)
#else 
#define ado_rwlock_init(rwl)		pthread_rwlock_init(rwl, NULL)
#define ado_rwlock_rdlock(rwl)		pthread_rwlock_rdlock(rwl)
#define ado_rwlock_wrlock(rwl)		pthread_rwlock_wrlock(rwl)
#define ado_rwlock_unlock(rwl)		pthread_rwlock_unlock(rwl)
#define ado_rwlock_destroy(rwl)		pthread_rwlock_destroy(rwl)
#endif


/***** typedefs *************/
typedef pthread_mutex_t ado_mutex_t;
typedef pthread_rwlock_t ado_rwlock_t;


/*** function prototypes ****/

/* thread.c */
int ado_mutex_init_default_debug ( ado_mutex_t *mutex , char *filename , int line );
int ado_mutex_init_recursive_debug ( ado_mutex_t *mutex , char *filename , int line );
int ado_mutex_lock_debug ( ado_mutex_t *mutex , char *filename , int line );
int ado_mutex_unlock_debug ( ado_mutex_t *mutex , char *filename , int line );
int ado_mutex_destroy_debug ( ado_mutex_t *mutex , char *filename , int line );
int ado_rwlock_init_debug ( ado_rwlock_t *rwl , char *filename , int line );
int ado_rwlock_rdlock_debug ( ado_rwlock_t *rwl , char *filename , int line );
int ado_rwlock_wrlock_debug ( ado_rwlock_t *rwl , char *filename , int line );
int ado_rwlock_unlock_debug ( ado_rwlock_t *rwl , char *filename , int line );
int ado_rwlock_destroy_debug ( ado_rwlock_t *rwl , char *filename , int line );
int ado_mutex_init_recursive_nodebug ( ado_mutex_t *mutex );


#endif /* _ADO_THREAD_H_INCLUDED_ */

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/services/audio/public/include/ado_thread.h $ $Rev: 219613 $" )
