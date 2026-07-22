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

#ifndef __WLCONFIG_H_INCLUDED__
#define __WLCONFIG_H_INCLUDED__

#ifndef __SOCKET_H_INCLUDED__
#include <sys/socket.h>
#endif
#ifndef __WPA_CTRL_H
#include <wlconfig/wpa_ctrl.h>
#endif

/* The *_help() functions list all the command and the corresponding output formats */
/* structure that holds operation result */
struct w_res {
	char* res_data;	 /* point to buffer to hold result */
	int   res_buflen; /* total buffer len */
	int   res_len;	 /* reply data len */
	int   res_status;/* operation status */
};

/* status items */
#define STAT_SSID			1
#define STAT_MODE			2
			#define MODE_HOSTAP		0 /* otherwise ws */
#define STAT_HIDESSID		4
			#define HIDESSID_HIDDEN	0 /* otherwise = shown */
#define STAT_APBRIDGE		8
			#define IS_APBRIDGE		0 /* otherwise = not */
#define STAT_FRAGTHRESHOLD	16
#define STAT_WEPKEY			32
			#define WEP_OFF			0 
			#define WEP_ON			1
#define STAT_POWERSAFE		64
			#define POWERSAFE_OFF	0
			#define POWERSAFE_ON	1
#define STAT_BSSID			128
#define STAT_CHANNEL		256

/* Interface config
 */
/* open */
struct w_cfg* wcfg_openconnection(const char *ifname);
int wcfg_getsock(struct w_cfg *pcfg);
/* media */
int setmedia     (struct w_cfg *pcfg, const char *val);
int setmediamode (struct w_cfg *pcfg, const char *val);
int setmediaopt  (struct w_cfg *pcfg, const char *val);
int unsetmediaopt(struct w_cfg *pcfg, const char *val);
int setmediainst (struct w_cfg *pcfg, const char *val);

int find_wificard(const char *ifname, char *pout, int len); 
#define MEDIA_INVALID    0
#define MEDIA_ACTIVE    1
#define MEDIA_NONETWORK    2
int find_wifinic(const char *ifname, char *pout, int len);
int is_active(struct w_cfg *pcfg);
int ifup(struct w_cfg *pcfg);
/* ieee80211 */
int sethidessid  (struct w_cfg *pcfg, int d);
int setapbridge  (struct w_cfg *pcfg, int d);
int setifnwid    (struct w_cfg *pcfg, const char *val);
int setifnwkey   (struct w_cfg *pcfg, const char *val, int d);
int setifbssid   (struct w_cfg *pcfg, const char *val, int d);
int setifchan    (struct w_cfg *pcfg, const char *val, int d);
int setiffrag    (struct w_cfg *pcfg, const char *val, int d);
int setifpowersave(struct w_cfg *pcfg, int d);
int setifpowersavesleep(struct w_cfg *pcfg, const char *val);
int ieee80211_statistics(struct w_cfg *pcfg, int zflag, struct w_res *pres);
int ieee80211_status(struct w_cfg *pcfg, struct w_res *pres);
int set80211scan (struct w_cfg *pcfg, struct w_res *pres);
int set80211list (struct w_cfg *pcfg, const char *, int, struct w_res *pres);

int getconnecednet(struct w_cfg *pcfg, char *pout, int len, int *chan);
struct wl_accpt * wcfg_scan(struct w_cfg *pcfg, const char *ifname, int doscan);
/* close */
int wcfg_closeconnection(struct w_cfg *cfg);
#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/io-pkt/lib/wlconfig/public/wlconfig/wlconfig.h $ $Rev: 233581 $" )
