/*
 * $QNXLicenseC:
 * Copyright 2008, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX

 * Software Systems before you may reproduce, modify or distribute this software
,
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

#ifndef _QNX_DRIVER_H_INCLUDED
#define _QNX_DRIVER_H_INCLUDED


/*
 * There's nothing we want from <strings.h>.
 * In particular we don't want it to define bcopy -> memmove.
 * We want bcopy -> memcpy from "sys/systm.h".  Catch any
 * potential occurrences of the former.
 */
#define _STRINGS_H_INCLUDED


/* Set up a BSD like environment */
#include <sys/types_bsd.h>
#include <sys/systm.h>
#include <machine/param.h>

#include <errno.h>
#include <atomic.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/siginfo.h>
#include <sys/syspage.h>
#include <sys/neutrino.h>
#include <sys/mbuf.h>

#include <net/if.h>
#include <net/if_dl.h>
#include <net/if_types.h>
#include <net/if_ether.h>
#include <net/if_media.h>
#include <sys/io-pkt.h>
#include <sys/cache.h>
#include <sys/callout.h>
#include <hw/inout.h>
#include <drvr/mdi.h>
#include <drvr/eth.h>
#include <hw/nicinfo.h>

#include <sys/device.h>
#include <sys/mallocvar.h>
#include <dev/mii/miivar.h>
#include <sys/cdefs_bsd.h>
#include <nw_tls.h>
#include <nw_datastruct.h>
#include <nw_dl.h>
#include <device_qnx.h>

#endif


__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/io-pkt/sys/iopkt_driver.h $ $Rev: 233581 $" )
