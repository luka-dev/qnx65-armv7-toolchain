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





/*
 *      ado_pci.c
 *	    - Manifests for audio pci bus access.
 */

#ifndef _ADO_PCI_H_INCLUDED_
#define _ADO_PCI_H_INCLUDED_


/***** structures ***********/
struct ado_pci
{
	int32_t 	index;
	int32_t 	id;						/* id returned by pci_attach() call */
	void   		*handle;				/* handle returned by pci_attach_device() call */
	uint16_t	vendor;
	uint16_t	device;
	uint16_t	subsystem;
	uint16_t	subsysvendor;
	uint8_t		devfunc;
	uint8_t		revision;
	uint8_t		class_protocol;
	uint8_t		busnumber;	
	uint32_t	irq;
	uint64_t	bmstr;					/* CPU to PCI busmaster translation (pci_addr = cpu_addr + bmstr) */
	uint64_t	iobase[6];
	uint32_t	iolen[6];
	uint32_t	class;
	uint64_t	membase[6];
	uint32_t	memlen[6];
	uint32_t	spare[32];
};


/*** function prototypes ****/

/* pci.c */
struct ado_pci *ado_pci_device ( int32_t vendor , int32_t device , char *args);
struct ado_pci *ado_pci_device2 ( int32_t vendor , int32_t device , uint32_t flags , char *args);
void ado_pci_release ( struct ado_pci *pci );

#endif /* _ADO_PCI_H_INCLUDED_ */

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/services/audio/public/include/ado_pci.h $ $Rev: 219613 $" )
