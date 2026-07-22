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





#ifndef _DRVR_SUPPORT_H_INCLUDED
#define _DRVR_SUPPORT_H_INCLUDED

#include <stdio.h>
#ifndef _DRVR_COMMON_H_INCLUDED
#include <drvr/common.h>
#endif
#ifndef _HW_NICINFO_H_INCLUDED
#include <hw/nicinfo.h>
#endif

#ifndef _KERNEL	/* Not an io-pkt driver */
#ifndef __IO_NET_H_INCLUDED
#include <sys/io-net.h>
#endif
#endif

/* NIC specific stuff */
int nic_parse_options(nic_config_t *cfg, char *options);
int nic_strtomac(const char *s, unsigned char *mac);
int nic_get_syspage_mac(char *mac);
void nic_dump_config(nic_config_t *cfg);

#ifndef _KERNEL /* Only export these to io-net drivers */
int nic_slogf(int opcode, int severity, const char *fmt, ...)
    __attribute__((format (printf, 3, 4)));
int nic_ether_mcast_valid(struct _io_net_msg_mcast *mcast);
#endif

/* CRC generation */
_Uint32t nic_calc_crc_le(const _Uint8t *buf, int len);
_Uint32t nic_calc_crc_be(const _Uint8t *buf, int len);

/* Legacy ISA stuff */
int nic_ne2000(int iobase);

/* Typed memory functions. Should be in libc! */

void	*mmap_typed_device_memory (void *addr, size_t len, int prot, int flags, _Uint64t physical,
									char *name, int oflag, int tflag);
_Uintptrt	mmap_typed_device_io (size_t len, _Uint64t io, char *name, int oflag, int tflag);

#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/drvr/public/drvr/nicsupport.h $ $Rev: 223136 $" )
