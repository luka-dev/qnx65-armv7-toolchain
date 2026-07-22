/*
 * $QNXtpLicenseC:
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

/* $NetBSD: ieee80211_sysctl.h,v 1.7 2005/12/10 23:26:35 elad Exp $ */
/*-
 * Copyright (c) 2005 David Young.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 * 3. The name of David Young may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY David Young ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL David
 * Young BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 */
#ifndef _NET80211_IEEE80211_SYSCTL_H_INCLUDED
#define _NET80211_IEEE80211_SYSCTL_H_INCLUDED

#include <net80211/_ieee80211.h>
#include <net80211/ieee80211.h>
#ifndef _INTTYEPS_H_INCLUDED
#include <inttypes.h>
#endif

/* sysctl(9) interface to net80211 client/peer records */   

/* Name index, offset from net.link.ieee80211.node. */

#define	IEEE80211_SYSCTL_NODENAME_IF		0
#define	IEEE80211_SYSCTL_NODENAME_OP		1
#define	IEEE80211_SYSCTL_NODENAME_ARG		2
#define	IEEE80211_SYSCTL_NODENAME_TYPE		3
#define	IEEE80211_SYSCTL_NODENAME_ELTSIZE	4
#define	IEEE80211_SYSCTL_NODENAME_ELTCOUNT	5
#define	IEEE80211_SYSCTL_NODENAMELEN		6

/* Record type numbers. */
#define	IEEE80211_SYSCTL_T_NODE		0	/* client/peer record */
#define	IEEE80211_SYSCTL_T_RSSADAPT	1	/* rssadapt(9) record
						 * (optional)
						 */
#define	IEEE80211_SYSCTL_T_DRVSPEC	2	/* driver-specific record
						 * (optional)
						 */

#define	IEEE80211_SYSCTL_OP_ALL		0
 
/* Every record begins with this information. */
struct ieee80211_node_sysctlhdr {
/*00*/	uint16_t	sh_ifindex;
/*02*/	uint8_t	sh_macaddr[IEEE80211_ADDR_LEN];
/*08*/	uint8_t	sh_bssid[IEEE80211_ADDR_LEN];
};

/* Exportable node. */
struct ieee80211_node_sysctl {
/*00*/	uint16_t	ns_ifindex;
/*02*/	uint8_t	ns_macaddr[IEEE80211_ADDR_LEN];
/*08*/	uint8_t	ns_bssid[IEEE80211_ADDR_LEN];
/*0e*/	uint16_t	ns_capinfo;	/* capabilities */
/*10*/	uint32_t	ns_flags;	/* properties of this node,
					 * IEEE80211_NODE_SYSCTL_F_*
					 */
/*14*/	uint16_t	ns_freq;
/*16*/	uint16_t	ns_chanflags;
/*18*/	uint16_t	ns_chanidx;
/*1a*/	uint8_t	ns_rssi;	/* recv ssi */
/*1b*/	uint8_t	ns_esslen;
/*1c*/	uint8_t	ns_essid[IEEE80211_NWID_LEN];
/*3c*/	uint8_t	ns_rsvd0;	/* reserved */
/*3d*/	uint8_t	ns_erp;		/* 11g only */
/*3e*/	uint16_t	ns_associd;	/* assoc response */
/*40*/	uint32_t	ns_inact;	/* inactivity mark count */
/*44*/	uint32_t	ns_rstamp;	/* recv timestamp */
/*48*/	struct ieee80211_rateset ns_rates;	/* negotiated rate set */
/*58*/	uint16_t	ns_txrate;	/* index to ns_rates[] */
/*5a*/	uint16_t	ns_intval;	/* beacon interval */
/*5c*/	uint8_t	ns_tstamp[8];	/* from last rcv'd beacon */
/*64*/	uint16_t	ns_txseq;	/* seq to be transmitted */
/*66*/	uint16_t	ns_rxseq;	/* seq previous received */
/*68*/	uint16_t	ns_fhdwell;	/* FH only */
/*6a*/	uint8_t	ns_fhindex;	/* FH only */
/*6b*/	uint8_t	ns_fails;	/* failure count to associate */
/*6c*/
#ifdef notyet
	/* DTIM and contention free period (CFP) */
	uint8_t	ns_dtimperiod;
	uint8_t	ns_cfpperiod;	/* # of DTIMs between CFPs */
	uint16_t	ns_cfpduremain;	/* remaining cfp duration */
	uint16_t	ns_cfpmaxduration;/* max CFP duration in TU */
	uint16_t	ns_nextdtim;	/* time to next DTIM */
	uint16_t	ns_timoffset;
#endif
} __attribute__((__packed__));

#if defined(__NetBSD_) || defined(__QNXNTO__)
enum ieee80211_node_walk_state {
	IEEE80211_WALK_BSS = 0,
	IEEE80211_WALK_SCAN,
	IEEE80211_WALK_STA
};

struct ieee80211_node_walk {
	struct ieee80211com		*nw_ic;
	struct ieee80211_node_table	*nw_nt;
	struct ieee80211_node		*nw_ni;
	unsigned short			nw_ifindex;
};
#endif /* __NetBSD__ || __QNXNTO__ */

#define	IEEE80211_NODE_SYSCTL_F_BSS	0x00000001	/* this node is the
							 * ic->ic_bss
							 */
#define	IEEE80211_NODE_SYSCTL_F_STA	0x00000002	/* this node is in
							 * the neighbor/sta
							 * table
							 */
#define	IEEE80211_NODE_SYSCTL_F_SCAN	0x00000004	/* this node is in
							 * the scan table
							 */
#endif /* !_NET80211_IEEE80211_SYSCTL_H_INCLUDED */

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/socket/public/net80211/ieee80211_sysctl.h $ $Rev: 233581 $" )
