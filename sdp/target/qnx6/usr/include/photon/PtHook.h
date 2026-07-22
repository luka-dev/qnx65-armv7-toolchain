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
#ifndef __PT_HOOK_H_INCLUDED
#define __PT_HOOK_H_INCLUDED

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct
{  int size;
   int version;
} PtHookData_t;

typedef int PtHookF_t( PtHookData_t *data );
extern PtHookF_t PtHook;

#ifdef __cplusplus
};
#endif /* __cplusplus */

#include <photon/PhPackPop.h>

#endif /* __PT_HOOK_H_INCLUDED */


#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PtHook.h $ $Rev: 224590 $" )
#endif
