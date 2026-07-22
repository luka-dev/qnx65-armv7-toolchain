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
#include <wlconfig/wlconfig.h>

#ifndef _PTHREAD_H_INCLUDED
#include <pthread.h>
#endif

/* move headers of wifi_mgmt.c here */

#define MAX_SSID_LEN    32
#define BSSID_LEN       6

/* security bits for wl_net and wl_accpt */
#define PROTO_WPA   0x01000000
#define PROTO_WPA2  0x02000000
#define PROTO_RSN	PROTO_WPA2

#define KEY_MGMT_IEEE8021X  0x00010000
#define KEY_MGMT_PSK        0x00020000
#define KEY_MGMT_EAP        0x00040000
#define KEY_MGMT_NONE       0x00080000

#define AUTH_ALG_OPEN   0x00000100
#define AUTH_ALG_SHARED 0x00000200
#define AUTH_ALG_LEAP   0x00000400

/* key action bits for keyaction in wl_net */
#define PAIR_CCMP	0x00000001
#define PAIR_TKIP	0x00000002
#define PAIR_NONE	0x00000003

#define GROUP_CCMP	0x00000100
#define GROUP_TKIP	0x00000200
#define GROUP_WEP104	0x00000400
#define GROUP_WEP40	0x00000800

struct wl_advanced {
	/* all of the rest */
};
struct wl_net {
	struct wl_net *next;			
	char ifname[64];				/* interface name */
	int  id;						/* internal id */
	char ssid[IEEE80211_NWID_LEN];	/* max size defined in ieee80211.h */
	char bssid[64];					/* enough to hold hex-lized 6 bytes */

	int mode;

	int security;					/* policy */
	int keyaction;					/* group and pairwise cipher in action */

	char proto[64];					/* proto for quick reference */
	char key_mgmt[64];				/* key management for quick reference */

	char wep_key[4][16];			/* wep keys */
	int wep_keyidx;					/* default wep: -1 means not wep */
	char psk[1024];					/* psk */

	int priority;

	struct wl_advanced *advanced;

	int signal;						/* signal strengh if current */
};

#define WNET_CONNECTED	1 /* bits in wl_accpt.stat */

struct wl_accpt {
	struct wl_accpt *next;	
	uint8_t ssid[64]; /* max size defined in ieee80211.h */
	int ssidlen;

	uint32_t signal;
	uint32_t channel;
	uint32_t rates;
	uint8_t bssid[64]; /* hold string */
	int bssidlen;

	int caps; /* refer to ieee802*.h for bit for capabilities */
        uint8_t attr[16]; /* hold string */
        int stat; /* status */
};

struct wl_ip_status {
	char ifname[64];
	int flags;

	struct sockaddr_in addr;
	struct sockaddr_in mask;
	struct sockaddr_in broadcast;

	int status;
};

struct wl_status {
	struct wl_net network;
	struct wl_ip_status ipstatus;
};


/* api */
/* query/edit api */
extern void * wlm_init(const char *wl_ifname, const char* ctrl_iface_dir);
extern void wlm_destroy(void *wlm_handle);
extern int wlm_load_conf(void *wlm_handle, char *conf, struct wl_net netarray[], int* num); 
extern int wlm_store_conf(void *wlm_handle);
extern int wlm_cleannet(struct wl_net *nethead);
extern int wlm_cleanaccpt(struct wl_accpt *accpthead);
extern int wlm_wlnet_add(void *wlm_handle, struct wl_net *net);
extern int wlm_wlnet_delete(void *wlm_handle, void *id, int flag);
extern int wlm_wlnet_update(void *wlm_handle, struct wl_net *netnew);
extern int wlm_connect_ssid(void *wlm_handle, char* ssid);
extern int wlm_scan(void *wlm_handle, int doscan, struct wl_accpt accpt[], int *num);
extern int wlm_connect_accpt(void *wlm_handle, struct wl_accpt *accp);
extern int wlm_disconnect(void *wlm_handle);
extern int wlm_query_current(void *wlm_handle, struct wl_status *status);
extern int wlm_query_iface(void *wlm_handle, char *ifname, struct wl_ip_status
						   *ipstatus);

/* event api */
enum event { ARRIVAL, DEPARTURE, UP, DOWN, CARRIER, NO_CARRIER, /* iface */
			 SCAN_CHANGED, /* scan */
			 STATUS_LOST, STATUS_LEVELLOW /* current status */
			};
extern int wlm_register_event(void *wlm_handle, 
							  void (*cbfunct) (void *wlm_handle, int event, void *data),
							  void *userdata);

int wlm_monitor_scan(void *wlm_handle); 
/* this function will create a thread to monitor
 * neigbours (ap-es or ahhoc-es) and generate event upon the changes
 * of neighbours, ap or adhocs
 */
int wlm_monitor_status(void *wlm_handle);
/* this function creats a thread to monitor
 * the status of current connected network,
 * and generate event upon (1) lost of connection (2) low signal
 */
int wlm_monitor_iface(void *wlm_handle);
/* this funtion creates a thread to monitor
 * the interface changes and generate event accordingly, including
 * interface up, down, media operation status changes, 
 * and new interface arrive/depature etc.
 */

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/io-pkt/lib/wlconfig/public/wlconfig/wifi_mgmt.h $ $Rev: 233581 $" )
