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

#ifndef __IO_PKT_H_INCLUDED
#define __IO_PKT_H_INCLUDED


#ifndef __NEUTRINO_H_INCLUDED
#include <sys/neutrino.h>
#endif

#ifndef _PTHREAD_H_INCLUDED
#include <pthread.h>
#endif

struct nw_work_thread;


struct _iopkt_inter {
	struct			_iopkt_inter *next;
	int			on_list;
	unsigned		spurious;
	int			tidx;
	int			(*func)(void *arg, struct nw_work_thread *);
	int			(*enable)(void *arg);
	void			*arg;
	int			flags;
	struct _iopkt_inter	*next_all;
};

struct _iopkt_self {
	int		version;
	int		(*ex_init)(pthread_mutex_t *);
	int		(*ex_destroy)(pthread_mutex_t *);
	void		(*ex_lk)(pthread_mutex_t *);
	void		(*ex_unlk)(pthread_mutex_t *);
	struct inter_thread {
		struct _iopkt_inter	*inter_head;
		struct _iopkt_inter	**inter_tail;
		intrspin_t		spin;
		int			working;
		struct sigevent		*event;
		struct sigevent		intr_ev;

		/* Interrupt load balancing info */
		int			intr_samples;
		int			intr_collisions;
		int			intr_collisions_smoothed;
		int			intr_mig_backoff;
		int			intr_mig_backoff_lim;
	} inter_threads[1];
};

enum _iopkt_module_type {
	IOPKT_MODULE_GENERAL,
	IOPKT_MODULE_UNI,
	IOPKT_MODULE_SMP
};

struct _iopkt_drvr_entry {
	int version;
	enum _iopkt_module_type type;
	int (*drvr_init)(void *dll_hdl, struct _iopkt_self *iopkt, char *options);
};

struct _iopkt_lsm_entry {
	int version;
	enum _iopkt_module_type type;
	int (*lsm_init)(void *dll_hdl, struct _iopkt_self *iopkt, char *options);
};


#define IOPKT_VERSION		1
#define IOPKT_STRING		"io-pkt"

extern struct _iopkt_self *iopkt_selfp;


#if defined(VARIANT_uni)
#define IOPKT_MODULE_TYPE	IOPKT_MODULE_UNI
#elif defined(VARIANT_smp)
#define IOPKT_MODULE_TYPE	IOPKT_MODULE_SMP
#else
#define IOPKT_MODULE_TYPE	IOPKT_MODULE_GENERAL
#endif

#ifndef VARIANT_a
#define IOPKT_DRVR_ENTRY_SYM(sfx)	iopkt_drvr_entry
#define IOPKT_LSM_ENTRY_SYM(sfx)	iopkt_lsm_entry
#else
#define IOPKT_DRVR_ENTRY_SYM(sfx)	___CONCAT(iopkt_drvr_entry_, sfx)
#define IOPKT_LSM_ENTRY_SYM(sfx)	___CONCAT(iopkt_lsm_entry_, sfx)
#endif


#define IOPKT_DRVR_ENTRY_SYM_INIT(entry)	{IOPKT_VERSION, IOPKT_MODULE_TYPE, (entry)}
#define IOPKT_LSM_ENTRY_SYM_INIT(entry)		{IOPKT_VERSION, IOPKT_MODULE_TYPE, (entry)}

#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/io-pkt/sys/sys/io-pkt.h $ $Rev: 233581 $" )
