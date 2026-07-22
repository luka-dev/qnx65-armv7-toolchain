/* $NetBSD: ieee80211_rssadapt.h,v 1.6 2005/12/10 23:26:35 elad Exp $ */
/*-
 * Copyright (c) 2003, 2004 David Young.  All rights reserved.
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

#ifndef _NET80211_IEEE80211_RSSADAPT_H_INCLUDED
#define _NET80211_IEEE80211_RSSADAPT_H_INCLUDED

#ifndef __TIME_H_INCLUDED
#include <sys/time.h>
#endif
#ifndef _NET80211__IEEE80211_H_INCLUDED
#include <net80211/_ieee80211.h>
#endif
#ifndef _NET80211_IEEE80211_VAR_H_INCLUDED
#include <net80211/ieee80211_var.h>
#endif
#ifndef _INTTYPES_H_INCLUDED
#include <inttypes.h>
#endif

/* Data-rate adaptation loosely based on "Link Adaptation Strategy
 * for IEEE 802.11 WLAN via Received Signal Strength Measurement"
 * by Javier del Prado Pavon and Sunghyun Choi.
 */

/* Buckets for frames 0-128 bytes long, 129-1024, 1025-maximum. */
#define	IEEE80211_RSSADAPT_BKTS		3
#define IEEE80211_RSSADAPT_BKT0		128
#define	IEEE80211_RSSADAPT_BKTPOWER	3	/* 2**_BKTPOWER */

#define	ieee80211_rssadapt_thresh_new \
    (ieee80211_rssadapt_thresh_denom - ieee80211_rssadapt_thresh_old)
#define	ieee80211_rssadapt_decay_new \
    (ieee80211_rssadapt_decay_denom - ieee80211_rssadapt_decay_old)
#define	ieee80211_rssadapt_avgrssi_new \
    (ieee80211_rssadapt_avgrssi_denom - ieee80211_rssadapt_avgrssi_old)

struct ieee80211_rssadapt_expavgctl {
	/* RSS threshold decay. */
	unsigned rc_decay_denom;
	unsigned rc_decay_old;
	/* RSS threshold update. */
	unsigned rc_thresh_denom;
	unsigned rc_thresh_old;
	/* RSS average update. */
	unsigned rc_avgrssi_denom;
	unsigned rc_avgrssi_old;
};

struct ieee80211_rssadapt {
	/* exponential average RSSI << 8 */
	uint16_t		ra_avg_rssi;
	/* Tx failures in this update interval */
	uint32_t		ra_nfail;
	/* Tx successes in this update interval */
	uint32_t		ra_nok;
	/* exponential average packets/second */
	uint32_t		ra_pktrate;
	/* RSSI threshold for each Tx rate */
	uint16_t		ra_rate_thresh[IEEE80211_RSSADAPT_BKTS]
					      [IEEE80211_RATE_SIZE];
	struct timeval		ra_last_raise;
	struct timeval		ra_raise_interval;
};

/* Properties of a Tx packet, for link adaptation. */
struct ieee80211_rssdesc {
	unsigned			 id_len;	/* Tx packet length */
	unsigned			 id_rateidx;	/* index into ni->ni_rates */
	struct ieee80211_node	*id_node;	/* destination STA MAC */
	uint8_t		 id_rssi;	/* destination STA avg RSS @
						 * Tx time
						 */
};

void	ieee80211_rssadapt_updatestats(struct ieee80211_rssadapt *);
void	ieee80211_rssadapt_input(struct ieee80211com *, struct ieee80211_node *,
	    struct ieee80211_rssadapt *, int);
void	ieee80211_rssadapt_lower_rate(struct ieee80211com *,
	    struct ieee80211_node *, struct ieee80211_rssadapt *,
	    struct ieee80211_rssdesc *);
void	ieee80211_rssadapt_raise_rate(struct ieee80211com *,
	    struct ieee80211_rssadapt *, struct ieee80211_rssdesc *);
int	ieee80211_rssadapt_choose(struct ieee80211_rssadapt *,
	    struct ieee80211_rateset *, struct ieee80211_frame *, unsigned, int,
	    const char *, int);
#ifdef IEEE80211_DEBUG
extern int ieee80211_rssadapt_debug;
#endif /* IEEE80211_DEBUG */

#endif /* !_NET80211_IEEE80211_RSSADAPT_H_INCLUDED */


__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/socket/public/net80211/ieee80211_rssadapt.h $ $Rev: 233581 $" )
