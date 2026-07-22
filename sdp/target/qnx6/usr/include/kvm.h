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





#ifndef _KVM_H_INCLUDED
#define _KVM_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef _NLIST_H_INCLUDED
#include <nlist.h>
#endif

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

__BEGIN_DECLS

typedef struct __kvm kvm_t;

char	 *kvm_geterr(kvm_t *);
kvm_t	 *kvm_open
	    (const char *, const char *, const char *, int, const char *);
kvm_t	 *kvm_openfiles(const char *, const char *, const char *, int, char *);
int	  kvm_nlist(kvm_t *, struct nlist *);
ssize_t	  kvm_read(kvm_t *, u_long, void *, size_t);
ssize_t	  kvm_write(kvm_t *, u_long, const void *, size_t);
int	  kvm_close(kvm_t *);

__END_DECLS

#endif /* !_KVM_H_INCLUDED */

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/socket/public/kvm.h $ $Rev: 235252 $" )
