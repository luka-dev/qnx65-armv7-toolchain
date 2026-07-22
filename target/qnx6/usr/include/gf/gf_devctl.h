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
#ifndef _GF_GF_DEVCTL_H_INCLUDED
#define _GF_GF_DEVCTL_H_INCLUDED

#include <gf/gf.h>

/* driver devctl command manifests for gf_devctl() */
enum {
	GF_DEVCTL_STATS = 1, /* for used with devg-stats module */
	/* Driver specific devctl's start at 0x100 */
};

/* driver devctl command manifests for gf_display_devctl() */
typedef enum {
	GF_DISPLAY_DEVCTL_SET_SYNC_SOURCE = 1,
	GF_DISPLAY_DEVCTL_UPDATE_DISPLAY_SETTINGS
} gf_display_devctl_t;

__BEGIN_DECLS

extern int gf_devctl(gf_dev_t gdev, int cmd, void *data_in, 
    int nbytes, void *data_out, int *out_buffer_size);
extern int gf_display_devctl(gf_display_t display, gf_display_devctl_t cmd,
    void *data_in, int nbytes, void *data_out, int *out_buffer_size);

__END_DECLS
	
#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/gf/public/gf/gf_devctl.h $ $Rev: 224586 $" )
