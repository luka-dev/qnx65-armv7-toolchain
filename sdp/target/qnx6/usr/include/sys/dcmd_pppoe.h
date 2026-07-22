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





#ifndef __DCMD_PPPOE_H_INCLUDED
#define __DCMD_PPPOE_H_INCLUDED

#ifndef _DEVCTL_H_INCLUDED
#include <devctl.h>
#endif

#ifndef __DCMD_IO_NET_H_INCLUDED
#include <sys/dcmd_io-net.h>
#endif

#define	_DCMD_PPPOE_BASE		32

#define _DCMD_PPPOE_STATUS		0
#define _DCMD_PPPOE_NIC_INFO	1	
#define _DCMD_PPPOE_SEND_PKT	2
#define _DCMD_PPPOE_GET_PKT		3

#define	DCMD_PPPOE_STATUS		__DIOTF(_DCMD_NET, _DCMD_PPPOE_BASE + _DCMD_PPPOE_STATUS,   PPPOE_status_t)
#define	DCMD_PPPOE_NIC_INFO		__DIOTF(_DCMD_NET, _DCMD_PPPOE_BASE + _DCMD_PPPOE_NIC_INFO, PPPOE_nicinfo_t)
#define DCMD_PPPOE_SEND_PKT		__DIOTF(_DCMD_NET, _DCMD_PPPOE_BASE + _DCMD_PPPOE_SEND_PKT, PPPOE_pkt_t)
#define DCMD_PPPOE_GET_PKT		__DIOTF(_DCMD_NET, _DCMD_PPPOE_BASE + _DCMD_PPPOE_GET_PKT,  PPPOE_pkt_t)


#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/socket/public/sys/dcmd_pppoe.h $ $Rev: 233581 $" )
