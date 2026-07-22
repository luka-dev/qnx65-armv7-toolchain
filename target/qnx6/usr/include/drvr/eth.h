/*
 * $QNXLicenseC: 
 * Copyright 2007,2008, QNX Software Systems.  
 *  
 * Licensed under the Apache License, Version 2.0 (the "License"). You  
 * may not reproduce, modify or distribute this software except in  
 * compliance with the License. You may obtain a copy of the License  
 * at: http://www.apache.org/licenses/LICENSE-2.0  
 *  
 * Unless required by applicable law or agreed to in writing, software  
 * distributed under the License is distributed on an "AS IS" basis,  
 * WITHOUT WARRANTIES OF ANY KIND, either express or implied. 
 * 
 * This file may contain contributions from others, either as  
 * contributors under the License or as licensors under other terms.   
 * Please review this entire file for other proprietary rights or license  
 * notices, as well as the QNX Development Suite License Guide at  
 * http://licensing.qnx.com/license-guide/ for other information. 
 * $ 
 */








#ifndef NIC_ETH_H_INCLUDED
#define NIC_ETH_H_INCLUDED

#define ETH_MAC_LEN			6				/* 6 bytes dst & src addrs */
#define ETH_MIN_DATA_LEN  	46				/* min = 64 - addrs - crc */
#define ETH_MAX_DATA_LEN	1500			/* max 1500 bytes data */
#define ETH_MIN_PKT_LEN		60				/* min bytes + crc=4 => 64 */
#define ETH_MAX_PKT_LEN		1514			/* max = 1500 + addrs + crc */
#define ETH_CRC_LEN			4				/* 4 byte crc append by 8390 */

#define ETH_MCAST_MAX_ADDR  64              /* Max mcast address to track */
#define ETH_MCAST_CRC_MASK  0x3F

typedef struct _ether_header ether_header_t;
struct _ether_header {
	unsigned char   dst_addr[ETH_MAC_LEN];
	unsigned char   src_addr[ETH_MAC_LEN];
	unsigned short  ether_type;
};

#endif

#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/hardware/devn/public/drvr/eth.h $ $Rev: 219612 $" )
