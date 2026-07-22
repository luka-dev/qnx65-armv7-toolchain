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





#ifndef __DCMD_IP_H_INCLUDED
#define __DCMD_IP_H_INCLUDED

#ifndef _DEVCTL_H_INCLUDED
#include <devctl.h>
#endif

#ifndef _INTTYPES_H_INCLUDED
#include <inttypes.h>
#endif

#ifndef __SOCKET_H_INCLUDED
#include <sys/socket.h>
#endif

/*
 * IP devctl's
 * 0x600 - 0x6ff reserved for the IP stacks
 */

/*
 * Desc:  Get local address associated with socket.
 * Args:  Pointer to struct sockaddr in which address is returned.
 * Notes: Clients usually use getsockname() to generate this request.
 */
#define DCMD_IP_GSRCADDR	__DIOF(_DCMD_IP, 0x00, struct sockaddr)

/*
 * Desc:  Set local address to associate with socket.
 * Args:  Pointer to struct sockaddr from which address is taken.
 * Notes: Clients usually use bind() to generate this request.
 */
#define DCMD_IP_SSRCADDR	__DIOT(_DCMD_IP, 0x01, struct sockaddr)

/*
 * Desc:  Get foreign address associated with socket.
 * Args:  Pointer to struct sockaddr in which address is returned.
 * Notes: Clients usually use getpeername() to generate this request.
 */
#define DCMD_IP_GDESTADDR	__DIOF(_DCMD_IP, 0x02, struct sockaddr)

/*
 * Desc:  Set foreign address to associate with socket.
 * Args:  Pointer to struct sockaddr from which address is taken.
 * Notes: Clients usually use connect() to generate this request.
 */
#define DCMD_IP_SDESTADDR	__DIOT(_DCMD_IP, 0x03, struct sockaddr)

/*
 * Desc:  Set backlog on a socket.
 * Args:  Pointer to int from which backlog is taken.
 * Notes: Clients usually use listen() to generate this request.
 */
#define DCMD_IP_LISTEN		__DIOT(_DCMD_IP, 0x04, uint32_t)

/*
 * Desc:  Set method of shutting down socket.
 * Args:  Pointer to int which defines method.
 * Notes: Clients usually use shutdown() to generate this request.
 */
#define DCMD_IP_SHUTDOWN	__DIOT(_DCMD_IP, 0x05, uint32_t)

#define DCMD_IP_FDINFO		__DIOF(_DCMD_IP, 0x06, char)


#endif


__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/socket/public/sys/dcmd_ip.h $ $Rev: 233581 $" )
