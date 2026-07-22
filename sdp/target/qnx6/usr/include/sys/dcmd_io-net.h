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
 *  dcmd_io-net.h   Non-portable low-level devctl definitions
 *

 */
#ifndef __DCMD_IO_NET_H_INCLUDED
#define __DCMD_IO_NET_H_INCLUDED

#include <devctl.h>

#include <_pack64.h>

#include <sys/io-net.h>

#define DCMD_IO_NET_MAX_QUEUE      __DIOT(_DCMD_NET, 10, unsigned)

/*
 * Desc:  Turn promiscuous mode on / off for network interface.
 * Args:  Pointer to int used as flag.
 * Notes: fd is associated with device representing the interface:
 *        eg. /dev/io-net/en0.
 */
#define DCMD_IO_NET_PROMISCUOUS    __DIOT(_DCMD_NET, 12, int)
#define DCMD_IO_NET_WIFI           __DIOTF(_DCMD_NET, 14, nic_wifi_dcmd_t)
#define DCMD_IO_NET_REDIRECT_BELOW __DIOT(_DCMD_NET, 15, struct _io_net_dcmd_redirect)
#define DCMD_IO_NET_VERSION        __DIOF(_DCMD_NET, 16, unsigned)
#define DCMD_IO_NET_CHANGE_MCAST   __DIOT(_DCMD_NET, 17, struct _io_net_msg_mcast)
#define DCMD_IO_NET_INSTANCE       __DIOF(_DCMD_NET, 18, unsigned)
#define DCMD_IO_NET_TX_FLUSH       __DIOT(_DCMD_NET, 19, int)
#define DCMD_IO_NET_MIIPHY         __DIOTF(_DCMD_NET, 20, nic_miiphy_dcmd_t)
#define DCMD_IO_NET_GET_CONFIG     __DIOF(_DCMD_NET, 21, nic_config_t)
#define DCMD_IO_NET_GET_STATS      __DIOF(_DCMD_NET, 22, nic_stats_t)
#define DCMD_IO_NET_STATIC         __DIOF(_DCMD_NET, 23, unsigned)
#define DCMD_IO_NET_PRIVATE        __DIOTF(_DCMD_NET, 24, nic_private_dcmd_t)

#include <_packpop.h>

#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/services/net/public/sys/dcmd_io-net.h $ $Rev: 219613 $" )
