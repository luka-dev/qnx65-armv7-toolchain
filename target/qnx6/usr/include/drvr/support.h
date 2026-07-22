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






/* This file obsolete; network drivers should use nicsupport.h */

#ifndef SUPPORT_H_INCLUDED
#define SUPPORT_H_INCLUDED

#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <hw/pci.h>
#include <sys/nic.h>
#include <sys/types.h>
#include <sys/siginfo.h>
#include <sys/neutrino.h>
#include <hw/inout.h>
#include <gulliver.h>
#include <pthread.h>


/*
 * Common options to all driver types.  Must be the
 * first structure entry in the driver specific structure.
 */
typedef struct _drvr_options
{
    uint32_t  verbose;
    uint32_t  bustype;
    uint32_t  busindex;
    uint32_t  busdevice;
    uint32_t  busvendor;
    paddr_t   ioport;
    uint32_t  irq;
    uint32_t  dma;
    uint32_t  priority;

    uint32_t       spare[7]; 	/* spare(s) rounds the struct to 16 words */
} drvr_options_t;


/*
 * Network Device Options.
 */
typedef struct _nic_options
{
    drvr_options_t drvr;
    uint32_t       single;
    uint32_t       fullduplex;
    uint32_t       nomulticast;
    uint32_t       promiscuous;
    uint32_t       notcacheable;
    uint32_t       media;
    paddr_t        smem;
    uint32_t       smemsize;
    uint32_t       mtu;
    uint8_t        mac[8];	/*Note: last 2 bytes are not used */
    uint32_t       width;
    uint32_t       chipset;
    uint32_t       transmit;
    uint32_t       receive;
    uint32_t       pktque;
    uint32_t       speed;

    uint32_t       spare[3];


} nic_options_t;



#ifndef TAILQ_EMPTY
#define TAILQ_EMPTY(head) ((head)->tqh_first == NULL)
#endif
#ifndef TAILQ_FIRST
#define TAILQ_FIRST(head) ((head)->tqh_first)
#endif
#ifndef TAILQ_LAST
#define TAILQ_LAST(head) ((head)->tqh_last)
#endif
#ifndef TAILQ_NEXT
#define TAILQ_NEXT(elm, field) ((elm)->field.tqe_next)
#endif
#ifndef TAILQ_PREV
#define TAILQ_PREV(elm, field) ((elm)->field.tqe_prev)
#endif

#define DRVR_OPT_FLAG_VAL_REQ          (1<<0)
#define DRVR_OPT_FLAG_VAL_NONE         (1<<1)
#define DRVR_OPT_FLAG_VAL_UINT32     ( (1<<2) | DRVR_OPT_FLAG_VAL_REQ )
#define DRVR_OPT_FLAG_VAL_SINT32     ( (1<<3) | DRVR_OPT_FLAG_VAL_REQ )
#define DRVR_OPT_FLAG_VAL_PADDR      ( (1<<4) | DRVR_OPT_FLAG_VAL_REQ )

#define DRVR_BUSTYPE_PCI       0x70636900  /* "pci" */
#define DRVR_BUSTYPE_ISA       0x69736100  /* "isa" */
#define DRVR_BUSTYPE_USB       0x75736200  /* "usb" */
#define DRVR_BUSTYPE_VME       0x766d6500  /* "vme" */
#define DRVR_BUSTYPE_PCCARD    0x70636300  /* "pcc" */
#define DRVR_BUSTYPE_IEEE1394  0x66697200  /* "fir" */

/*
 * Structure used to build driver option tables.
 */
typedef struct
{
    char name[32];
    int  offset;
    int  flags;
    int(*handler)( void *hdl, char *dev, char *name, char *val );
} drvr_subopt_tbl_t;

typedef struct _drvr_subopt_tbl_chain
{
    struct _drvr_subopt_tbl_chain *next;
    drvr_subopt_tbl_t *table;
    int               table_size;
} drvr_subopt_tbl_chain_t;



/* Generic, Universal driver options parsing function */
int drvr_parse_subopts( void *hdl, char *dev, char *args, 
                        drvr_subopt_tbl_chain_t *chain );
int nic_parse_subopts( void *hdl, char *dev, char *args, 
                       drvr_subopt_tbl_chain_t *chain );
#ifndef _KERNEL /* Only export these to io-net drivers */
int nic_slogf(int opcode, int severity, const char *fmt, ...)
    __attribute__((format (printf, 3, 4)));
#endif


/* Deprecated Functions - Phase out by 6.2.0 */
int nic_drvr_options( Nic_t *nic, char *options );
int nic_pic_irq( Nic_t *nic, int irr_mmask, int irr_smask, void (*irq_assert)( Nic_t * ), void (*irq_clear)( Nic_t * ) );
int nic_strtomac( const char *s, unsigned char *mac );

ulong_t	nic_calc_crc_le( char *buf, int len );
ulong_t	nic_calc_crc_be( char *buf, int len );

Nic_t *nic_create_dev( int ext_size );
void dma_cascade( int dchnl );
int nic_display_config( Nic_t *nic );
void nsec_delay( int nsec );
int nic_ne2000( int iobase );

extern paddr_t mphys( void * );

/* Typed memory functions. Should be in libc! */

void	*mmap_typed_device_memory (void *addr, size_t len, int prot, int flags, uint64_t physical,
									char *name, int oflag, int tflag);
uintptr_t	mmap_typed_device_io (size_t len, uint64_t io, char *name, int oflag, int tflag);


#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/drvr/public/drvr/support.h $ $Rev: 223076 $" )
