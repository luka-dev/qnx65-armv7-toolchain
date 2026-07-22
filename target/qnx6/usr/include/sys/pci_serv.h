/*
 * $QNXLicenseC: 
 * Copyright 2008, QNX Software Systems.  
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


#ifndef _pci_serv_h_
#define _pci_serv_h_

#ifndef __PCI_H_INCLUDED
#include	<hw/pci.h>
#endif

#include	<sys/iomsg.h>

typedef	enum {
	IOM_PCI_READ_CONFIG_BYTE,
	IOM_PCI_READ_CONFIG_WORD,
	IOM_PCI_READ_CONFIG_DWORD,
	IOM_PCI_WRITE_CONFIG_BYTE,
	IOM_PCI_WRITE_CONFIG_WORD,
	IOM_PCI_WRITE_CONFIG_DWORD,
	IOM_PCI_READ_CONFIG_HANDLE,
	IOM_PCI_WRITE_CONFIG_HANDLE,
	IOM_PCI_FIND_DEVICE,
	IOM_PCI_FIND_CLASS,
	IOM_PCI_BIOS_PRESENT,
	IOM_PCI_MAP_ADDRESS,
	IOM_PCI_GET_VERSION,
	IOM_PCI_ATTACH_DEVICE,
	IOM_PCI_DETACH_DEVICE,
	IOM_PCI_MAP_IRQ,
	IOM_PCI_RESCAN_BUS,
	IOM_PCI_IRQ_ROUTING_OPTIONS
	} PCI_FUNCS;

struct _pci_present {
	ulong_t lastbus;
	ulong_t version;
	ulong_t hardware;
};

struct _pci_config {
	ushort_t bus;
	ushort_t devfunc;
	ushort_t offset;
	ushort_t count;
	uchar_t buffer [sizeof (struct _pci_config_regs)];
};

struct _pci_config_hdl {
	void	*handle;
	ushort_t offset;
	ushort_t count;
	size_t	size;
	uchar_t buffer [sizeof (struct _pci_config_regs)];
};
struct _pci_device {
	ushort_t deviceid;
	ushort_t vendorid;
	ulong_t index;
	ulong_t busnum;
	ulong_t devfuncnum;
};

struct _pci_class {
	ulong_t class;
	ulong_t index;
	ulong_t busnum;
	ulong_t devfuncnum;
};

struct _pci_map {
	ulong_t pciaddr;
	ulong_t cpuaddr;
	ulong_t flags;
};

struct _pci_map_irq {
	ushort_t bus;
	ushort_t devfunc;
	ushort_t intno;
	ushort_t intpin;
};

struct _pci_version {
	ushort_t version;
	ushort_t numdevices;
};

struct _pci_attach {
	ulong_t	flags;
	void	*handle;
	ushort_t	idx;
	ushort_t	filler;
	struct pci_dev_info configbuffer;
};

struct _pci_detach {
	void	*handle;
};

struct	_pci_route_opt {
	ushort_t	irq_info;
	ushort_t	buf_size;
	ushort_t	filler [2];
	uchar_t		buffer [512];
};

struct	_pci_reply_hdr {
	ulong_t	 reply_status;
	ulong_t	 reply_length;
};

struct	_pci_message {
	io_msg_t					 msg_hdr;
	struct	_pci_reply_hdr		 rep_hdr;
	union {
		struct _pci_present		 present;
		struct _pci_config		 config;
		struct _pci_config_hdl	 config_hdl;
		struct _pci_device		 device;
		struct _pci_class		 class;
		struct _pci_map			 map;
		struct _pci_version		 version;
		struct _pci_attach		 lock;
		struct _pci_detach		 unlock;
		struct _pci_map_irq		 map_irq;
		struct _pci_route_opt	 route_opt;
		} msg;
};

#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/hardware/pci/public/sys/pci_serv.h $ $Rev: 238819 $" )
