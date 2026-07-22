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
 *      audio_driver.h
 *         The main header for the audio drivers.
 */

#ifndef __AUDIO_DRIVER_H_INCLUDED_
#define __AUDIO_DRIVER_H_INCLUDED_


#include <atomic.h>
#include <ctype.h>
#include <dlfcn.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <hw/inout.h>
#include <hw/pci.h>
#include <hw/sysinfo.h>
#include <libgen.h>
#include <malloc.h>
#include <ps/ps.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ioctl.h>
#include <devctl.h>
#include <sys/cache.h>
#include <sys/mman.h>
#include <sys/procmgr.h>
#include <sys/rsrcdbmgr.h>
#include <sys/slog.h>
#include <sys/slogcodes.h>
#include <sys/syspage.h>
#include <sys/trace.h>
#include <sys/types.h>
#include <unistd.h>

#include <sys/iofunc.h>

#include <sys/asound.h>
#include "ado_core.h"
#include "ado_thread.h"
#include "ado_memory.h"
#include "ado_debug.h"
#include "ado_pci.h"
#include "ado_power.h"


typedef struct ado_ocb				ado_ocb_t;


/*** depandant header files ****/
#include "ado_pcm.h"
#include "ado_mixer.h"

#include "ado_isa.h"


/*** function prototypes ****/

/* resmgr.c */
void ado_driver_terminate ( ado_card_t *card );

/* card_helper.c */
void ado_card_set_shortname ( ado_card_t *card , char *name );
void ado_card_set_longname ( ado_card_t *card , char *name , uint32_t addr );

/* resource.c */
int ado_reserve_resource ( uint32_t flags , char *name , uint64_t start , uint64_t len );
int ado_release_resource ( uint32_t flags , char *name , uint64_t start , uint64_t len );

#endif	/* __AUDIO_DRIVER_H_INCLUDED_ */

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/services/audio/public/include/audio_driver.h $ $Rev: 219613 $" )
