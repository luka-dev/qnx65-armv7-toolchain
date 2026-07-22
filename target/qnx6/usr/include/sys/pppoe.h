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






#ifndef __PPPOE_H_INCLUDED
#define __PPPOE_H_INCLUDED

#include <gulliver.h>
#include <net/if.h>
#include <net/if_ether.h>
#include <sys/iofunc.h>

#include <_pack64.h>

typedef u_char eth_mac_t[6];

#define HTONS(x) ENDIAN_BE16(x)
#define HTONL(x) ENDIAN_BE32(x)

#define PPPOE_DCMD_MAX_DATA     1400
#define PPPOE_IFACE_MAX		    IFNAMSIZ
#define PPPOE_RELAY_TAG_SIZE	12

typedef struct pppoe_status PPPOE_status_t;
struct pppoe_status {
    uint32_t    status;                     /* see PPPOE_STATUS_* */
    char        iface[PPPOE_IFACE_MAX];     /* interface name  eg. en0 */
    eth_mac_t   host_mac;
    eth_mac_t   ac_mac;
    uint32_t    session_id;
    uint32_t    index;
};

#define PPPOE_STATUS_NONE       0           /* PADI hasn't been sent -- idle */
#define PPPOE_STATUS_PADI       1           /* PADI has been sent */
#define PPPOE_STATUS_PADO       2           /* PADO has been received */
#define PPPOE_STATUS_PADR       4           /* PADR has been sent */
#define PPPOE_STATUS_PADS       8           /* PADS has been received */
#define PPPOE_STATUS_ACTIVE     16          /* session established */
#define PPPOE_STATUS_ABORT      32          /* session is going down */
#define PPPOE_STATUS_RELAY		256			/* this is a relay session */


typedef struct pppoe_nicinfo PPPOE_nicinfo_t;
struct pppoe_nicinfo {
    char        iface[PPPOE_IFACE_MAX];     /* interface name  eg. en0 */
    eth_mac_t   host_mac;
    uint32_t    index;
};

typedef struct pppoe_packet PPPOE_pkt_t;
struct pppoe_packet {
        eth_mac_t       host_mac;               /* which iface to use */
        eth_mac_t       ac_mac;                 /* which remote ac to use */
        uint32_t        code;
        uint32_t        data_len;               /* data contains encoded tags */
        u_char          data[PPPOE_DCMD_MAX_DATA];
};

	/* codes determine what kind of pkt */
#define PPPOE_CODE_PADI			0x09
#define PPPOE_CODE_PADO			0x07
#define PPPOE_CODE_PADR			0x19
#define PPPOE_CODE_PADS			0x65
#define PPPOE_CODE_PADT			0xa7
#define PPPOE_CODE_SESSION		0x00
#define PPPOE_CODE_PADM			0xd3
#define PPPOE_CODE_PADN			0xd4

	/* standard tags	(RFC-2516) */
#define PPPOE_TAG_EOL			0x0000
#define PPPOE_TAG_SERVICE		0x0101
#define PPPOE_TAG_ACNAME		0x0102
#define PPPOE_TAG_UNIQ			0x0103
#define PPPOE_TAG_AC_COOKIE		0x0104
#define PPPOE_TAG_VENDOR		0x0105
#define PPPOE_TAG_RELAY			0x0110

	/* draft tags		(draft-carrel-info-pppoe-ext-00.txt) */
#define	PPPOE_TAG_HURL			0x0111
#define	PPPOE_TAG_MOTM			0x0112
#define	PPPOE_TAG_IP_ROUTE		0x0121

	/* error tags		(RFC-2516) */
#define PPPOE_TAG_ERR_SRV		0x0201
#define PPPOE_TAG_ERR_AC		0x0202
#define PPPOE_TAG_ERR_GEN		0x0203

#include <_packpop.h>

#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/socket/public/sys/pppoe.h $ $Rev: 233581 $" )
