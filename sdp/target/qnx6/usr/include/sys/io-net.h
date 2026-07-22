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





#ifndef __NTO_IO_NET_H_INCLUDED
#define __NTO_IO_NET_H_INCLUDED

#include <sys/types.h>
#include <sys/queue.h>
#include <sys/dispatch.h>
#include <sys/iofunc.h>
#include <inttypes.h>
#include <net/if_dl.h>
#include <sys/socket.h>
#include <sys/pm.h>


__BEGIN_DECLS

/*
 * npkt_t flags
 */
#define _NPKT_NOT_TXED     0x0001    /* Clue to down producer's tx_done routine that error occured */
#define _NPKT_NO_RES       0x0002    /* Up producer wants its buffer back right away. */
#define _NPKT_UP           0x0004    /* npkt headed up. Down if not set. */
#define _NPKT_MSG          0x0008
#define _NPKT_MSG_DYING    0x0010
#define _NPKT_BCAST        0x0020
#define _NPKT_MCAST        0x0040
#define _NPKT_INTERNAL     0x0080
#define _NPKT_UP_SPECIFIC  0x0100
#define _NPKT_PROMISC      0x0200
#define _NPKT_TX_WAIT      0x0400    /* More packets or a DCMD_IO_NET_TX_FLUSH to come */

/*
 * Originator can use bits 20-23 as it likes.
 * Don't look at or modify these if you didn't
 * originate the packet.
 */
#define _NPKT_ORG_MASK     0x00f00000
/*
 * 24-31 for use by layer in which npkt currently resides.
 * Set these to a known state before use.
 */
#define _NPKT_SCRATCH_MASK 0xff000000


/*
 * io_net_registrant_t flags
 */
#define _REG_FILTER_ABOVE      0x00000001
#define _REG_FILTER_BELOW      0x00000002
#define _REG_CONVERTOR         0x00000004
#define _REG_PRODUCER_UP       0x00000008
#define _REG_PRODUCER_DOWN     0x00000010
#define _REG_DEREG_ALL         0x00000020

#define _REG_REMOUNT_NEW       0x00000040
#define _REG_NO_REMOUNT        0x00000080
#define _REG_NO_RAW_ACCESS     0x00000100
#define _REG_ENDPOINT          0x00000200 /* Deprecated.  Use _REG_ENDPOINT_ARG */
#define _REG_RAW_SELF          0x00000400
#define _REG_TRACK_MCAST       0x00000800
#define _REG_POWER_MNGR        0x00001000
#define _REG_POWER_MNGR_STRICT 0x00002000
#define _REG_ENDPOINT_ARG      0x00004000

#define _REG_TYPE_MASK      0x1f




typedef struct _net_iovec net_iov_t;

struct _net_iovec {
	void    *iov_base;
	paddr_t  iov_phys;
	size_t   iov_len;
};


typedef struct _net_buf net_buf_t;

struct _net_buf {
	TAILQ_ENTRY(_net_buf) ptrs;
	int niov;
	net_iov_t *net_iov;
};



typedef struct _npkt_done npkt_done_t;

struct _npkt_done {
	int   registrant_hdl;
	void *done_hdl;
};
	



typedef struct _npkt npkt_t;

struct _npkt {
	TAILQ_HEAD(, _net_buf) buffers;
	npkt_t                 *next;
	void                   *io_net0;        /* Internal to io-net. */

	void                   *org_data;       /* for originator of npkt.  No one   */
	                                        /* else should touch on way through. */


	uint32_t                flags;          /* Status of buffer. */
	uint32_t                framelen;       /* Total length of entire pkt. */
	uint16_t                tot_iov;        /* total number of iovs in packet. */
	uint16_t                reserved;
	uint32_t                csum_flags;

	uint32_t                ref_cnt;        /* Initialize to 1 for up packets. */

	uint16_t                num_complete;
	uint16_t                req_complete;   /* Required number of npkt_complete_t */
	                                        /* this packet required before it was */
	                                        /* consumed. Only for information     */
	                                        /* purposes (rd only) in originator's */
	                                        /* tx_done function if originator not */
	                                        /* using io-net's alloc_down_pkt().   */

	uint16_t                cell;           /* Cell down npkt is headed to. */

	uint16_t                endpoint;       /* Endpoint within cell. */

	uint16_t                iface;          /* Iface within endpoint. */

	uint16_t                skip;

	union {                                 /* this can be changed by any    */
		void *p;                            /* module to pass info to module */
		unsigned char c[16];                /* above / below.                */
		uint32_t csum_data;
	} inter_module;


/*
 *	npkt_done_t             c[num_complete];  (on down tx)
 *	npkt_done_t             c[1];             (on up tx)
 */
};	



typedef struct _io_net_iofunc_attr io_net_iofunc_attr_t;

struct _io_net_iofunc_attr {
	iofunc_attr_t attr;
	uint16_t       cell;
	uint16_t       endpoint;
	int            reserved[2];
	int            io_net0;
	int            io_net1;
};



union _io_net_dcmd_ret_cred {
	int ret;                   /* io-net version 0 (_DCMD_IO_NET_VERSION returns EOPNOTSUPP) */
	struct {                   /* io-net version > 0 */
		int ret;
		struct _cred_info *cred;
		uint16_t iface;
	} ret_cred;
};



typedef struct _io_net_registrant_funcs io_net_registrant_funcs_t;

struct _io_net_registrant_funcs {
	u_int     nfuncs;
	int     (*rx_up)      (npkt_t *npkt, void *func_hdl, int off, int framlen_sub, uint16_t cell, uint16_t endpoint, uint16_t iface);

	int     (*rx_down)    (npkt_t *npkt, void *func_hdl);

	int     (*tx_done)    (npkt_t *npkt, void *done_hdl, void *func_hdl);

	int     (*shutdown1)   (int registrant_hdl, void *func_hdl);
	int     (*shutdown2)   (int registrant_hdl, void *func_hdl);

	int     (*dl_advert)  (int registrant_hdl, void *func_hdl);

	int     (*devctl)     (void *func_hdl, int dcmd, void *data, size_t size, union _io_net_dcmd_ret_cred *ret);
	int     (*flush)      (int registrant_hdl, void *func_hdl);
	int     (*raw_open)   (resmgr_context_t *ctp, io_open_t *msg, io_net_iofunc_attr_t *attr, void *extra);
	int     (*raw_umount_in_progress) (io_net_iofunc_attr_t *attr);
};
#define _IO_NET_REG_NFUNCS		((sizeof(io_net_registrant_funcs_t)-sizeof(u_int))/sizeof(void *))



#define _DEP_SATISFIED 0x0001

typedef struct _io_net_dependency io_net_dependency_t;

struct _io_net_dependency {
	char     *dep;
	uint32_t  flags;
};

/*
 * The following are entry points a module provides into itself
 * when it registers.  Will be called by io-net.
 */
typedef struct _io_net_registrant io_net_registrant_t;

struct _io_net_registrant {
	uint32_t                  flags; 
	char                      *name;
	char                      *top_type;
	char                      *bot_type;
	void                      *func_hdl;
	io_net_registrant_funcs_t *funcs;
	int                       ndependencies;
	union {
		/*
		 * This method of specifying endpoint
		 * will be deprecated.  Should use
		 * _REG_ENDPOINT_ARG.
		 *
		 * Valid if _REG_PRODUCER* and _REG_ENDPOINT_REG
		 * set
		 */
		uint16_t       regu_endpoint;
		char           *regu_pmmparent;
	} regu;
#define reg_pmmparent regu.regu_pmmparent
	pmd_attr_t                *pmd_attrp;   /*  Valid if _REG_POWER_MNGR set */
/*	io_net_dependency_t       [ndependencies]; */
};


/* tx_down() return codes */
#define TX_DOWN_AGAIN 1
#define TX_DOWN_OK 0
#define TX_DOWN_FAILED -1

#define _BYTE_PAT_ALL 0x0001


typedef struct _io_net_self io_net_self_t;

struct _io_net_self {
	u_int	nfuncs;

	void *   (*alloc)          (size_t size, int flags);
	npkt_t * (*alloc_down_npkt)(int registrant_hdl, size_t size, void **data);
	npkt_t * (*alloc_up_npkt)  (size_t size, void **data);
	int		(*free)           (void *ptr);
	paddr_t	(*mphys)          (void *ptr);

	int		(*reg)            (void *dll_hdl, io_net_registrant_t *registrant, int *reg_hdlp, uint16_t *cell, uint16_t *endpoint);
	int		(*dereg)          (int registrant_hdl);

	int		(*tx_up)          (int registrant_hdl, npkt_t *npkt, int off, int framlen_sub, uint16_t cell, uint16_t endpoint, uint16_t iface);
	/*
	@@ down originator stuffs the cell, endpoint and iface it's trying to reach.
	*/
	int		(*tx_down)        (int registrant_hdl, npkt_t *npkt);

	/*
	@@ TX_DOWN
	@@   Only called if not passing packet to lower layer (or
	@@   done with packet and no lower layer to pass it to).
	@@
	@@ TX_UP
	@@   Always called after done with packet (after layer stops
	@@   packet or after it passes it on).
	*/
	int      (*tx_done)        (int registrant_hdl, npkt_t *npkt);

	int      (*reg_tx_done)    (int registrant_hdl, npkt_t *npkt, void *done_hdl);

	int		(*reg_byte_pat)   (int registrant_hdl, unsigned off, unsigned len, unsigned char *pat, unsigned flags);
	int		(*dereg_byte_pat) (int registrant_hdl, unsigned off, unsigned len, unsigned char *pat, unsigned flags);

	int		(*devctl)         (int registrant_hdl, int dcmd, void *data, size_t size, int *ret);
	npkt_t *	(*tx_up_start)    (int registrant_hdl, npkt_t *npkt, int off, int framlen_sub, uint16_t cell, uint16_t endpoint, uint16_t iface, void *tx_done_hdl);
	int      (*memcpy_from_npkt)(const iov_t *dst, int dparts, int doff, const npkt_t *snpkt, int soff, int smax_len);
	int		(*raw_devctl)     (resmgr_context_t *ctp, io_devctl_t *m, io_net_iofunc_attr_t *attr);
};
#define _IO_NET_NFUNCS		((sizeof(io_net_self_t)-sizeof(u_int))/sizeof(void *))



enum _io_net_msg_bases {
   _IO_NET_MSG_BASE = 0x100,
   _IO_NET_MSG_MAX  = 0x1FF
};

enum _io_net_uint16_types {
   _IO_NET_MSG_DL_ADVERT = _IO_NET_MSG_BASE,
	_IO_NET_MSG_ADDR_ADD,
	_IO_NET_MSG_ADDR_DEL,
	QNET_IMMSG_IFUP,
	QNET_IMMSG_IFDOWN,
	_IO_NET_JOIN_MCAST,
	_IO_NET_REMOVE_MCAST
};



typedef struct _io_net_msg_dl_advert io_net_msg_dl_advert_t;

struct _io_net_msg_dl_advert {
	uint16_t            type;
	uint16_t            zero;
	uint32_t            iflags;
	uint32_t            mtu_min;
	uint32_t            mtu_max;
	uint32_t            mtu_preferred;
	uint32_t            capabilities_rx;
	uint32_t            capabilities_tx;
	uint32_t            reserved[2];
	char                up_type[20];
	struct sockaddr_dl  dl;
};



typedef struct _io_net_msg_addr_add io_net_msg_addr_add_t;
typedef struct _io_net_msg_addr_add io_net_msg_addr_del_t;

struct _io_net_msg_addr_add {
	uint16_t        type;
	uint16_t        above_endpoint; /* only valid if packet headed down. */
	uint16_t        above_iface;    /* only valid if packet headed down. */
	uint16_t        zero;
	uint32_t        reserved[2];
	struct sockaddr addr;
	union {
		struct sockaddr destaddr;
		struct sockaddr broadaddr;
	} u;
	struct sockaddr mask;
};



/* These typedefs may be deprecated.  Use struct _io_net_msg_mcast directly. */
typedef struct _io_net_msg_mcast io_net_msg_join_mcast_t;
typedef struct _io_net_msg_mcast io_net_msg_remove_mcast_t;

/* flags */
#define _IO_NET_MCAST_ALL   0x0001
#define _IO_NET_MCAST_RANGE 0x0002
struct _io_net_msg_mcast {
	uint16_t                  type;
	uint16_t                  flags;
	struct _io_net_msg_mcast *next;
	int32_t                   ref_cnt;
	uint32_t                  reserved[2];
	union {
		struct sockaddr    addr;
		struct sockaddr_dl addr_dl;
		uint32_t pad[5];
	} mc_min, mc_max;
};



typedef struct _io_net_dll_entry io_net_dll_entry_t;

struct _io_net_dll_entry {
	int nfuncs;
	int (*init) (void *dll_hdl, dispatch_t *dpp, io_net_self_t *ion, char *options);
	int (*shutdown) (void *dll_hdl);
	int (*delreg) (void);
};

#define _IO_NET_REDIRECT_MSG                0
#define _IO_NET_REDIRECT_ENDPOINT           1
#define _IO_NET_REDIRECT_CONVERTOR_ENDPOINT 2
struct _io_net_dcmd_redirect {
	int op;
	union {
		struct {
			resmgr_context_t *ctp;
			io_net_iofunc_attr_t *attr;
		} attr;
		struct {
			int dcmd;
			void *data;
			size_t size;
			int *ret_val;
			uint16_t cell;
			uint16_t endpoint;
			uint16_t iface;
		} endpoint;
	} u;
};

__END_DECLS
#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/services/net/public/sys/io-net.h $ $Rev: 219613 $" )
