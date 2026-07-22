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



#ifndef _NW_INTR_H_INCLUDED
#define _NW_INTR_H_INCLUDED

#include <sys/siginfo.h>
#include <sys/io-pkt.h>
#include <nw_defs.h>
#include <nw_sig.h>
#include <nw_datastruct.h>

#define NW_INTR_SIG NW_SIG_INTR
#define NW_INTR_PRIO 21

/* flags to interrupt_entry_init() */
#define IRUPT_OOB_HIGH	0x00000001
#define IRUPT_OOB_LOW	0x00000002
#define IRUPT_NOTHREAD	0x00000004
#define IRUPT_OOB_ISR	0x80000000

/* prio arg to interrupt_entry_init */
#define IRUPT_PRIO_DEFAULT	-1

int interrupt_pre_main_init(void);
void interrupt_pre_main_fini(void);

int interrupt_init(void);
void interrupt_fini(void);

int interrupt_thread_reg(struct nw_work_thread *, int);
void interrupt_thread_dereg(struct nw_work_thread *);
void interrupt_process_dead(struct nw_work_thread *);

int interrupt_entry_init(struct _iopkt_inter *, int, struct sigevent **, int);
int interrupt_entry_remove(struct _iopkt_inter *, struct sigevent *);

const struct sigevent * interrupt_queue(struct _iopkt_self *,
    struct _iopkt_inter *);

#ifdef OPT_SIGEV_SIGNAL_TID
void interrupt_sig_handler(int signo, siginfo_t *, void *);
#endif
void process_interrupts(struct nw_work_thread *);
struct inter_thread * process_interrupts_noswitch(struct nw_work_thread *);
#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/io-pkt/sys/nw_intr.h $ $Rev: 233581 $" )
