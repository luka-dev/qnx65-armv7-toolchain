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








/*
 *  pci.h
 *
 */
#ifndef __PCI_H_INCLUDED

#include <_pack1.h>

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef _INTTYPES_H_INCLUDED
 #include <inttypes.h>
#endif

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#ifndef	_STDDEF_H_INCLUDED
 #include	<stddef.h>
#endif

__BEGIN_DECLS

struct _pci_config_regs
{
        uint16_t          Vendor_ID;					/* 0x00 */
        uint16_t          Device_ID;					/* 0x02 */
        uint16_t          Command;						/* 0x04 */
        uint16_t          Status;						/* 0x06 */
        uint8_t           Revision_ID;					/* 0x08 */
        uint8_t           Class_Code[3];				/* 0x09 */
        uint8_t           Cache_Line_Size;				/* 0x0C */
        uint8_t           Latency_Timer;				/* 0x0D */
        uint8_t           Header_Type;					/* 0x0E */
        uint8_t           BIST;							/* 0x0F */
        uint32_t          Base_Address_Regs[6];			/* 0x10 */
        uint32_t          CardBus_CIS;					/* 0x28 */
		uint16_t          Sub_Vendor_ID;				/* 0x2C */
		uint16_t          Sub_System_ID;				/* 0x2E */
        uint32_t          ROM_Base_Address;				/* 0x30 */
		uint8_t           Capabilities_Pointer;			/* 0x34 */
		uint8_t           Reserved2 [3];				/* 0x35 */
        uint32_t          Reserved3;					/* 0x38 */
        uint8_t           Interrupt_Line;				/* 0x3C */
        uint8_t           Interrupt_Pin;				/* 0x3D */
        uint8_t           Min_Gnt;						/* 0x3E */
        uint8_t           Max_Lat;						/* 0x3F */
        uint8_t           Device_Dependent_Regs[192];
};

struct _pci_bridge_config_regs
{
        uint16_t          Vendor_ID;					/* 0x00 */
        uint16_t          Device_ID;					/* 0x02 */
        uint16_t          Command;						/* 0x04 */
        uint16_t          Status;						/* 0x06 */
        uint8_t           Revision_ID;					/* 0x08 */
        uint8_t           Class_Code[3];				/* 0x09 */
        uint8_t           Cache_Line_Size;				/* 0x0C */
        uint8_t           Latency_Timer;				/* 0x0D */
        uint8_t           Header_Type;					/* 0x0E */
        uint8_t           BIST;							/* 0x0F */
        uint32_t          Base_Address_Regs[2];			/* 0x10 */
		uint8_t           Primary_Bus_Number;			/* 0x18 */
		uint8_t           Secondary_Bus_Number;			/* 0x19 */
		uint8_t           Subordinate_Bus_Number;		/* 0x1A */
        uint8_t           Secondary_Latency_Timer;		/* 0x1B */
		uint8_t           IO_Base;						/* 0x1C */
		uint8_t           IO_Limit;						/* 0x1D */
		uint16_t          Secondary_Status;				/* 0x1E */
		uint16_t          Memory_Base;					/* 0x20 */
		uint16_t          Memory_Limit;					/* 0x22 */
		uint16_t          Prefetchable_Memory_Base;		/* 0x24 */
		uint16_t          Prefetchable_Memory_Limit;	/* 0x26 */
		uint32_t          Prefetchable_Base_Upper32;	/* 0x28 */
		uint32_t          Prefetchable_Limit_Upper32;	/* 0x2c */
		uint16_t          IO_Base_Upper16;				/* 0x30 */
		uint16_t          IO_Limit_Upper16;				/* 0x32 */
		uint8_t           Capabilities_Pointer;			/* 0x34 */
        uint8_t           Reserved1 [3];				/* 0x35 */
        uint32_t          ROM_Base_Address;				/* 0x38 */
        uint8_t           Interrupt_Line;				/* 0x3C */
        uint8_t           Interrupt_Pin;				/* 0x3D */
		uint16_t          Bridge_Control;				/* 0x3E */
        uint8_t           Device_Dependent_Regs[192];
};

struct _pci_cardbus_config_regs
{
        uint16_t           Vendor_ID;					/* 0x00 */
        uint16_t           Device_ID;					/* 0x02 */
        uint16_t           Command;						/* 0x04 */
        uint16_t           Status;						/* 0x06 */
        uint8_t            Revision_ID;					/* 0x08 */
        uint8_t            Class_Code[3];				/* 0x09 */
        uint8_t            Cache_Line_Size;				/* 0x0C */
        uint8_t            Latency_Timer;				/* 0x0D */
        uint8_t            Header_Type;					/* 0x0E */
        uint8_t            BIST;						/* 0x0F */
        uint32_t           Socket_Exca_Base_Reg;		/* 0x10 */
		uint8_t            Capabilities_Pointer;		/* 0x14 */
        uint8_t            reserved1;					/* 0x15 */
        uint16_t           Secondary_Status;			/* 0x16 */
        uint8_t            Pci_Bus_Num;					/* 0x18 */
        uint8_t            Cardbus_Bus_Num;				/* 0x19 */
        uint8_t            Sub_Bus_Num;					/* 0x1A */
        uint8_t            Cardbus_Latency_Timer;		/* 0x1B */
        uint32_t           Mem_Base_Reg_0;				/* 0x1C */
        uint32_t           Mem_Limit_Reg_0;				/* 0x20 */
        uint32_t           Mem_Base_Reg_1;				/* 0x24 */
        uint32_t           Mem_Limit_Reg_1;				/* 0x28 */
        uint32_t           Io_Base_Reg_0;				/* 0x2C */
        uint32_t           Io_Limit_Reg_0;				/* 0x30 */
        uint32_t           Io_Base_Reg_1;				/* 0x34 */
        uint32_t           Io_Limit_Reg_1;				/* 0x38 */
        uint8_t            Interrupt_Line;				/* 0x3C */
        uint8_t            Interrupt_Pin;				/* 0x3D */
        uint16_t           Bridge_Control;				/* 0x3E */
        uint16_t           Subsystem_Vendor_Id;			/* 0x40 */
        uint16_t           Subsystem_Id;				/* 0x42 */
        uint32_t           If_Legacy_Base_Reg;			/* 0x44 */
        uint8_t            reserved2[56];				/* 0x48 */
        uint32_t           System_Control;				/* 0x80 */
        uint8_t            reserved3[8];				/* 0x84 */
		uint32_t           Multifunction_Routing;		/* 0x8C */
        uint8_t            Retry_Status;				/* 0x90 */
        uint8_t            Card_Control;				/* 0x91 */
        uint8_t            Device_Control;				/* 0x92 */
        uint8_t            Buffer_Control;				/* 0x93 */
        uint32_t           Dma_Reg_0;					/* 0x94 */
        uint32_t           Dma_Reg_1;					/* 0x98 */
        uint8_t            Device_Dependent_Regs[100];
};


/* Power management capability - 0x01 */

struct	_pci_capability_power
{
		uint8_t                 Capability_ID;
		uint8_t                 Next_Pointer;
		uint16_t				Power_PMC;
		uint16_t				Power_PMCSR;
		uint8_t					Power_PMCSR_BSE;
		uint8_t					Power_Data;
};

/* AGP capability - 0x02 */

struct	_pci_capability_agp
{
		uint8_t                 Capability_ID;
		uint8_t                 Next_Pointer;
		uint8_t					Major_Minor_Revision;
		uint8_t					Reserved;
		uint32_t				AGP_Status;
		uint32_t				AGP_Command;
};

/* Vital Product Data Capability - 0x03 */

struct	_pci_capability_vpd
{
		uint8_t                 Capability_ID;
		uint8_t                 Next_Pointer;
		uint16_t				VPD_Address;
		uint32_t				VPD_Data;
};

/* Slot Numbering capability - 0x04 */

struct	_pci_capability_slot_numbering
{
		uint8_t                 Capability_ID;
		uint8_t                 Next_Pointer;
		uint8_t					Card_Slot;
		uint8_t					Chassis_Number;
};

/* MSI capability for 32-bit message address - 0x05 */

struct	_pci_capability_msi32
{
		uint8_t                 Capability_ID;
		uint8_t                 Next_Pointer;
		uint16_t				Message_Control;
		uint32_t				Message_Address;
		uint16_t				Message_Data;
		uint16_t				Filler;
};

/* MSI capability for 64-bit message address - 0x05 */

struct	_pci_capability_msi64
{
		uint8_t                 Capability_ID;
		uint8_t                 Next_Pointer;
		uint16_t				Message_Control;
		uint32_t				Message_Address;
		uint32_t				Message_Address_Upper;
		uint16_t				Message_Data;
		uint16_t				Filler;
};

/* MSI capability for 32-bit message address and per-vector masking - 0x05 */

struct	_pci_capability_msi32_PVM
{
		uint8_t                 Capability_ID;
		uint8_t                 Next_Pointer;
		uint16_t				Message_Control;
		uint32_t				Message_Address;
		uint16_t				Message_Data;
		uint16_t				Filler;
		uint32_t				Mask_Bits;
		uint32_t				Pending_Bits;
};

/* MSI capability for 64-bit message address and per-vector masking - 0x05 */

struct	_pci_capability_msi64_PVM
{
		uint8_t                 Capability_ID;
		uint8_t                 Next_Pointer;
		uint16_t				Message_Control;
		uint32_t				Message_Address;
		uint32_t				Message_Address_Upper;
		uint16_t				Message_Data;
		uint16_t				Filler;
		uint32_t				Mask_Bits;
		uint32_t				Pending_Bits;
};

/* Message Control for MSI definitions */

#define	PCI_MSI_PVM				0x0100	/* Per vector masking */
#define	PCI_MSI_64BIT			0x0080	/* 64-bit address capable */
#define	PCI_MSI_MME_MASK		0x0070	/* Multiple message enable mask */
#define	PCI_MSI_MMC_MASK		0x000e	/* Multiple message_capable mask */
#define	PCI_MSI_ENABLE			0x0001	/* MSI Enable */
#define	PCI_MSIX_ENABLE			0x8000	/* MSI-X Enable */
#define	PCI_MSIX_TAB_SIZE		0x07ff	/* MSI-X Table size mask */
#define	PCI_MSIX_BIR_MASK		0x0007	/* MSI-X Base Index Register mask */

/* PCI-X capability - 0x07 */

struct	_pci_capability_pcix
{
		uint8_t                 Capability_ID;
		uint8_t                 Next_Pointer;
		uint16_t				PCI_X_Command;
		uint32_t				PCI_X_Status;
};

/* PCI-X bridge capability - 0x07 */

struct	_pci_capability_pcix_bridge
{
		uint8_t                 Capability_ID;
		uint8_t                 Next_Pointer;
		uint16_t				PCI_X_Secondary_Status;
		uint32_t				PCI_X_Bridge_Status;
		uint32_t				Upstream_Split_Transaction_Control;
		uint32_t				Downstream_Split_Transaction_Control;
};

/* PCI Hot Plug capability - 0x0C */

struct	_pci_capability_hot_plug
{
		uint8_t                 Capability_ID;
		uint8_t                 Next_Pointer;
		uint8_t					Dword_Select;
		uint8_t					CSP_CIP;
		uint32_t				Dword_Data;
};

/* PCI-Express capability - 0x10 */

struct	_pci_capability_pci_express
{
		uint8_t                 Capability_ID;
		uint8_t                 Next_Pointer;
		uint16_t				PCI_Express_Cap_Reg;
		uint32_t				Device_Capabilities;
		uint16_t				Device_Control;
		uint16_t				Device_Status;
		uint32_t				Link_Capabilities;
		uint16_t				Link_Control;
		uint16_t				Link_Status;
		uint32_t				Slot_Capabilities;
		uint16_t				Slot_Control;
		uint16_t				Slot_Status;
		uint16_t				Root_Control;
		uint16_t				Root_Capabilities;
		uint32_t				Root_Status;
};

/* MSI-X capability - 0x11 */

struct	_pci_capability_msix
{
		uint8_t                 Capability_ID;
		uint8_t                 Next_Pointer;
		uint16_t				Message_Control;
		uint32_t				Table_Offset;
		uint32_t				PBA_Offset;
};

struct	_pci_msix_table
{
		uint32_t				Message_Address;
		uint32_t				Message_Address_Upper;
		uint32_t				Message_Data;
		uint32_t				Vector_Control;
};
	
/* Message Control for MSI definitions */

#define	PCI_MSIX_ENABLE			0x8000
#define	PCI_MSIX_FUNC_MASK		0x4000
#define	PCI_MSIX_TABLE_MASK		0x07ff
#define	PCI_MSIX_BIR_MASK		0x0007

/* HyperTransport Slave/Primary Interface Block Format */

struct	_pci_ht_sp_capability
{
		uint8_t					Capability_ID;
		uint8_t					Next_Pointer;
		uint16_t				Command;
		uint16_t				Link_Control0;
		uint16_t				Link_Config0;
		uint16_t				Link_Control1;
		uint16_t				Link_Config1;
		uint8_t					Revision_ID;
		uint8_t					Link_Freq_Error0;
		uint16_t				Link_Freq_Cap0;
		uint8_t					Feature;
		uint8_t					Link_Freq_Error1;
		uint16_t				Link_Freq_Cap1;
		uint16_t				Enumeration_Scratch;
		uint16_t				Error_Handling;
		uint8_t					Mem_Base_Upper;
		uint8_t					Mem_Limit_Upper;
		uint8_t					Bus_Number;
		uint8_t					Reserved;
};

/* HyperTransport Host/Secondary Interface Block Format */

struct	_pci_ht_hs_capability
{
		uint8_t					Capability_ID;
		uint8_t					Next_Pointer;
		uint16_t				Command;
		uint16_t				Link_Control;
		uint16_t				Link_Config;
		uint8_t					Revision_ID;
		uint8_t					Link_Freq_Error;
		uint16_t				Link_Freq_Cap;
		uint16_t				Feature;
		uint16_t				Reserved;
		uint16_t				Enumeration_Scratch;
		uint16_t				Error_Handling;
		uint8_t					Mem_Base_Upper;
		uint8_t					Mem_Limit_Upper;
		uint16_t				Reserved2;
};

/*
 * Command Register; contains command and capability fields.
 */
#define HT_COMMAND_CAP_OFF    		0x00

#define HT_CAP_ID_MASK         		0x000000FF
#define HT_CAP_ID_SHIFT        		0
#define HT_CAP_PTR_MASK        		0x0000FF00
#define HT_CAP_PTR_SHIFT       		8

#define HT_COMMAND_MASK				0xFFFF0000
#define HT_COMMAND_SHIFT			16
#define HT_COMMAND(cmd) (((cmd) & HT_COMMAND_MASK) >> HT_COMMAND_SHIFT)
#define HT_COMMAND_TYPE_MASK		0xE0000000
#define HT_COMMAND_TYPE_SHIFT		(29)
#define HT_COMMAND_TYPE(cmd) (((cmd) & HT_COMMAND_TYPE_MASK) >> HT_COMMAND_TYPE_SHIFT)
#define HT_COMMAND_TYPE_SLAVE		0x0
#define HT_COMMAND_TYPE_HOST		0x1
#define HT_COMMAND_TYPE_SWITCH		0x2   /* extended in 1.05 */
#define HT_COMMAND_TYPE_IDC			0x4   /* ditto */
#define HT_COMMAND_TYPE_AMAP		0x5   /* ditto */

/*
 * An HT capability for type Slave (aka Primary, aka "tunnel") consists
 * of a Command register, two Link registers, and two Freq/Rev registers.
 */
/* Slave/Primary commands */
#define HT_COMMAND_UNIT_ID_MASK         	0x001F0000
#define HT_COMMAND_UNIT_ID_SHIFT        	(16)
#define HT_COMMAND_UNIT_ID(cmd) \
	(((cmd) & HT_COMMAND_UNIT_ID_MASK) >> HT_COMMAND_UNIT_ID_SHIFT)
#define HT_COMMAND_UNIT_COUNT_MASK        	0x03E00000
#define HT_COMMAND_UNIT_COUNT_SHIFT       	(21)
#define HT_COMMAND_UNIT_COUNT(cmd) \
	(((cmd) & HT_COMMAND_UNIT_COUNT_MASK) >> HT_COMMAND_UNIT_COUNT_SHIFT)
#define HT_COMMAND_MASTER_HOST_MASK			0x04000000
#define HT_COMMAND_MASTER_HOST(cmd) \
	(((cmd) & HT_COMMAND_MASTER_HOST_MASK) ? 1 : 0)
#define HT_COMMAND_DEFAULT_DIRECTION_MASK	0x08000000
#define HT_COMMAND_DEFAULT_DIRECTION(cmd) \
	(((cmd) & HT_COMMAND_DEFAULT_DIRECTION_MASK) ? 1 : 0)

/*
 * An HT capability for type Host (aka Secondary) consists of a
 * Command register, a single Link register, and a Freq/Rev register.
 */
/* Host/Secondary command fields */
#define HT_COMMAND_WARM_RESET				0x00010000
#define HT_COMMAND_DOUBLE_ENDED				0x00020000
#define HT_COMMAND_DEVICE_NUMBER_MASK		0x007C0000
#define HT_COMMAND_DEVICE_NUMBER_SHIFT		(18)
/* Following for 1.0x only */
#define HT_COMMAND_CHAIN_SIDE				0x00800000
#define HT_COMMAND_HOST_HIDE				0x01000000
#define HT_COMMAND_ACT_AS_SLAVE				0x04000000
#define HT_COMMAND_INBOUND_EOC_ERROR		0x08000000

/*
 * Link Register; contains control and config fields.
 */
#define HT_LINKn_OFF(n)				(0x04 + ((n)<<2))

#define HT_LINKCTRL_MASK			0x0000FFFF
#define HT_LINKCTRL_SHIFT			0
#define HT_LINKCTRL(cr) (((cr) & HT_LINKCTRL_MASK) >> HT_LINKCTRL_SHIFT)
#define HT_LINKCTRL_CFLE			0x00000002
#define HT_LINKCTRL_CST				0x00000004
#define HT_LINKCTRL_CFE				0x00000008
#define HT_LINKCTRL_LINKFAIL		0x00000010
#define HT_LINKCTRL_INITDONE		0x00000020
#define HT_LINKCTRL_EOC				0x00000040
#define HT_LINKCTRL_TXOFF			0x00000080
#define HT_LINKCTRL_CRCERROR_MASK	0x00000F00
#define HT_LINKCTRL_CRCERROR_SHIFT	8
#define HT_LINKCTRL_ISOCEN			0x00001000
#define HT_LINKCTRL_LSEN			0x00002000
/* Following for 1.0x only */
#define HT_LINKCTRL_EXTCTL			0x00004000
#define HT_LINKCTRL_64B				0x00008000

#define HT_LINKCFG_MASK				0xFFFF0000
#define HT_LINKCFG_SHIFT			16
#define HT_LINKCFG(cr) (((cr) & HT_LINKCFG_MASK) >> HT_LINKCFG_SHIFT)
#define HT_LINKCFG_MAX_WIDTH_MASK	0x00FF0000
#define HT_LINKCFG_MAX_WIDTH_SHIFT	16
#define HT_LINKCFG_MAX_WIDTH_IN(cr) (((cr) >> (16)) & 0x7)
#define HT_LINKCFG_MAX_WIDTH_OUT(cr) (((cr) >> (20)) & 0x7)
#define HT_LINKCFG_WIDTH_MASK		0xFF000000
#define HT_LINKCFG_WIDTH_SHIFT		24
#define HT_LINKCFG_WIDTH_IN(cr) (((cr) >> (24)) & 0x7)
#define HT_LINKCFG_WIDTH_OUT(cr) (((cr) >> (28)) & 0x7)

/* Slave/Primary offsets */

#define HT_CFG0_OFF					offsetof(struct _pci_ht_sp_capability, Link_Control0)
#define HT_CFG1_OFF					offsetof(struct _pci_ht_sp_capability, Link_Control1)
#define HT_CFGn_OFF(n)				(HT_CFG0_OFF + ((n)<<2))

/* Host/Secondary offsets */
#define HT_CFG_OFF					offsetof(struct _pci_ht_hs_capability, Link_Control)

#define HT_WIDTH_8					0x0
#define HT_WIDTH_16					0x1
#define HT_WIDTH_32					0x3
#define HT_WIDTH_2					0x4
#define HT_WIDTH_4					0x5
#define HT_WIDTH_DISC				0x7

/*
 * Link Frequency Register; contains version and frequency fields.
 */
#define HT_LINKFREQ_CAP(cr) (((cr) >> 16) & 0xFFFF)

#define HT_LINKFREQ_MASK			0x00000F00
#define HT_LINKFREQ_SHIFT			8
#define HT_LINKFREQ(cr) (((cr) >> 8) & 0x0F)

#define HT_REVISION_ID(cr) (cr & 0xFF)

#define HT_REV_017					0x11
#define HT_REV_102					0x22
#define HT_REV_105					0x25

/* Slave/Primary offsets */
#define HT_FREQ0_OFF				offsetof(struct _pci_ht_sp_capability, Revision_ID)
#define HT_FREQ1_OFF				offsetof(struct _pci_ht_sp_capability, Feature)
#define HT_FREQn_OFF(n)	(HT_FREQ0_OFF + ((n)<<2))

/* Host/Secondary offsets */
#define HT_FREQ_OFF					offsetof(struct _pci_ht_hs_capability, Revision_ID)

#define HT_FREQ_200					0x00
#define HT_FREQ_300					0x01
#define HT_FREQ_400					0x02
#define HT_FREQ_500					0x03
#define HT_FREQ_600					0x04
#define HT_FREQ_800					0x05
#define HT_FREQ_1000				0x06

#define	HT_PRIMARY					0x00
#define	HT_SECONDARY				0x01

/* End HyperTransport defines */

struct pci_dev_info {
		uint16_t		DeviceId;
		uint16_t		VendorId;
		uint16_t		SubsystemId;
		uint16_t		SubsystemVendorId;
		uint8_t			BusNumber;
		uint8_t			DevFunc;
		uint8_t			Revision;
		uint8_t			Rsvd[5];
		uint32_t		Class;
		uint32_t		Irq;

		uint64_t		CpuIoTranslation;	/* pci_addr = cpu_addr - translation */
		uint64_t		CpuMemTranslation;	/* pci_addr = cpu_addr - translation */
		uint64_t		CpuIsaTranslation;	/* pci_addr = cpu_addr - translation */
		uint64_t		CpuBmstrTranslation;/* pci_addr = cpu_addr + translation */

		uint64_t		PciBaseAddress[6];
		uint64_t		CpuBaseAddress[6];
		uint32_t		BaseAddressSize[6];
		uint64_t		PciRom;
		uint64_t		CpuRom;
		uint32_t		RomSize;
		uint32_t		Rsvd1;
		uint64_t		BusIoStart;
		uint64_t		BusIoEnd;
		uint64_t		BusMemStart;
		uint64_t		BusMemEnd;
		uint8_t			msi;
		uint8_t			Rsvd2 [3];
		uint32_t		Rsvd3;
};

typedef struct _pci_route_buffer {
		uint16_t		BufferSize;
		uint16_t		DataBufferOffset;
		uint16_t		DataBufferSeg;
		} IRQRoutingOptionsBuffer;


/* PCI class defines */
#define PCI_CLASS_PRE						0x00000000
	#define PCI_SUBCLASS_PRE_ALL			0x00000000
	#define PCI_SUBCLASS_PRE_VGA			0x00000100
#define PCI_CLASS_STORAGE					0x00010000
	#define PCI_SUBCLASS_STORAGE_SCSI		0x00000000
	#define PCI_SUBCLASS_STORAGE_IDE		0x00000100
	#define PCI_SUBCLASS_STORAGE_FLOPPY		0x00000200
	#define PCI_SUBCLASS_STORAGE_IPI		0x00000300
	#define PCI_SUBCLASS_STORAGE_RAID		0x00000400
	#define	PCI_SUBCLASS_STORAGE_ATA		0x00000500
	#define	PCI_SUBCLASS_STORAGE_SER_ATA	0x00000600
	#define	PCI_SUBCLASS_STORAGE_SAS		0x00000700
	#define PCI_SUBCLASS_STORAGE_OTHER		0x00008000
#define PCI_CLASS_NETWORK					0x00020000
	#define PCI_SUBCLASS_NETWORK_ETHERNET	0x00000000
	#define PCI_SUBCLASS_NETWORK_TOKENRING	0x00000100
	#define PCI_SUBCLASS_NETWORK_FDDI		0x00000200
	#define	PCI_SUBCLASS_NETWORK_ATM		0x00000300
	#define	PCI_SUBCLASS_NETWORK_ISDN		0x00000400
	#define	PCI_SUBCLASS_NETWORK_WORLDFIP	0x00000500
	#define	PCI_SUBCLASS_NETWORK_PICMG		0x00000600
	#define PCI_SUBCLASS_NETWORK_OTHER		0x00008000
#define PCI_CLASS_DISPLAY					0x00030000
	#define PCI_SUBCLASS_DISPLAY_VGA		0x00000000
	#define PCI_SUBCLASS_DISPLAY_XGA		0x00000100
	#define	PCI_SUBCLASS_DISPLAY_3D			0x00000200
	#define PCI_SUBCLASS_DISPLAY_OTHER		0x00008000
#define PCI_CLASS_MULTIMEDIA				0x00040000
	#define PCI_SUBCLASS_MULTIMEDIA_VIDEO	0x00000000
	#define PCI_SUBCLASS_MULTIMEDIA_AUDIO	0x00000100
	#define	PCI_SUBCLASS_TELEPHONY			0x00000200
	#define PCI_SUBCLASS_MULTIMEDIA_OTHER	0x00008000
#define PCI_CLASS_MEMORY					0x00050000
	#define PCI_SUBCLASS_MEMORY_RAM			0x00000000
	#define PCI_SUBCLASS_MEMORY_FLASH		0x00000100
	#define PCI_SUBCLASS_MEMORY_OTHER		0x00008000
#define PCI_CLASS_BRIDGE					0x00060000
	#define PCI_SUBCLASS_BRIDGE_HOST		0x00000000
	#define PCI_SUBCLASS_BRIDGE_ISA			0x00000100
	#define PCI_SUBCLASS_BRIDGE_EISA		0x00000200
	#define PCI_SUBCLASS_BRIDGE_MC			0x00000300
	#define PCI_SUBCLASS_BRIDGE_PCI			0x00000400
	#define PCI_SUBCLASS_BRIDGE_PCMCIA		0x00000500
	#define PCI_SUBCLASS_BRIDGE_NUBUS		0x00000600
	#define	PCI_SUBCLASS_BRIDGE_CARDBUS		0x00000700
	#define PCI_SUBCLASS_BRIDGE_RACEWAY		0x00000800
	#define PCI_SUBCLASS_BRIDGE_XPARENT		0x00000900
	#define PCI_SUBCLASS_BRIDGE_INFINIBAND	0x00000A00
	#define PCI_SUBCLASS_BRIDGE_OTHER		0x00008000
#define PCI_CLASS_COMMUNICATIONS			0x00070000
	#define	PCI_SUBCLASS_COMMS_SERIAL		0x00000000
	#define	PCI_SUBCLASS_COMMS_PARALLEL		0x00000100
	#define	PCI_SUBCLASS_COMMS_MULTIPORT	0x00000200
	#define	PCI_SUBCLASS_COMMS_MODEM		0x00000300
	#define	PCI_SUBCLASS_COMMS_GPIB			0x00000400
	#define	PCI_SUBCLASS_COMMS_SMARTCARD	0x00000500
	#define	PCI_SUBCLASS_COMMS_OTHER		0x00008000
#define PCI_CLASS_SYSTEM					0x00080000
	#define	PCI_SUBCLASS_SYSTEM_PIC			0x00000000
	#define	PCI_SUBCLASS_SYSTEM_DMA			0x00000100
	#define	PCI_SUBCLASS_SYSTEM_TIMER		0x00000200
	#define	PCI_SUBCLASS_SYSTEM_RTC			0x00000300
	#define	PCI_SUBCLASS_SYSTEM_HOT_PLUG	0x00000400
	#define	PCI_SUBCLASS_SYSTEM_SD			0x00000500
	#define	PCI_SUBCLASS_SYSTEM_OTHER		0x00008000
#define PCI_CLASS_INPUT						0x00090000
	#define PCI_SUBCLASS_INPUT_KBD			0x00000000
	#define PCI_SUBCLASS_INPUT_DIGITIZER	0x00000100
	#define PCI_SUBCLASS_INPUT_MOUSE		0x00000200
	#define PCI_SUBCLASS_INPUT_SCANNER		0x00000300
	#define PCI_SUBCLASS_INPUT_GAME_PORT	0x00000400
	#define PCI_SUBCLASS_INPUT_OTHER		0x00008000
#define PCI_CLASS_STATION					0x000a0000
	#define	PCI_SUBCLASS_STATION_DOCKING	0x00000000
	#define	PCI_SUBCLASS_STATION_OTHER		0x00008000
#define PCI_CLASS_PROCESSOR					0x000b0000
	#define	PCI_SUBCLASS_PROCESSOR_386		0x00000000
	#define	PCI_SUBCLASS_PROCESSOR_486		0x00000100
	#define	PCI_SUBCLASS_PROCESSOR_PENTIUM	0x00000200
	#define	PCI_SUBCLASS_PROCESSOR_ALPHA	0x00001000
	#define	PCI_SUBCLASS_PROCESSOR_PPC		0x00002000
	#define	PCI_SUBCLASS_PROCESSOR_MIPS		0x00003000
	#define	PCI_SUBCLASS_PROCESSOR_COPROC	0x00004000
#define PCI_CLASS_SERIAL					0x000c0000
	#define PCI_SUBCLASS_SERIAL_FIREWIRE	0x00000000
	#define PCI_SUBCLASS_SERIAL_ACCESS		0x00000100
	#define PCI_SUBCLASS_SERIAL_SSA			0x00000200
	#define PCI_SUBCLASS_SERIAL_USB			0x00000300
	#define PCI_SUBCLASS_SERIAL_FIBRECHNL	0x00000400
	#define PCI_SUBCLASS_SERIAL_SMBus		0x00000500
	#define PCI_SUBCLASS_SERIAL_INFINIBAND	0x00000600
	#define PCI_SUBCLASS_SERIAL_IPMI		0x00000700
	#define PCI_SUBCLASS_SERIAL_SERCOS		0x00000800
	#define PCI_SUBCLASS_SERIAL_CANBUS		0x00000900
#define	PCI_CLASS_WIRELESS					0x000d0000
	#define	PCI_SUBCLASS_WIRELESS_IRDA		0x00000000
	#define	PCI_SUBCLASS_WIRELESS_CONS_IR	0x00000100
	#define	PCI_SUBCLASS_WIRELESS_RF		0x00001000
	#define	PCI_SUBCLASS_WIRELESS_BLUETOOTH	0x00001100
	#define	PCI_SUBCLASS_WIRELESS_BROADBAND	0x00001200
	#define	PCI_SUBCLASS_WIRELESS_802_11A	0x00002000
	#define	PCI_SUBCLASS_WIRELESS_802_11B	0x00002100
	#define	PCI_SUBCLASS_WIRELESS_OTHER		0x00008000
/* 0x12-0xFE are reserved */
#define PCI_CLASS_UNDEFINED					0xFF0000


#define PCI_IS_IO(address)              (((address) & 1) &&1)
#define PCI_IS_MEM(address)             (!PCI_IS_IO(address))
#define PCI_IO_ADDR(address)            ((address) & ~0x3)
#define PCI_MEM_ADDR(address)           ((address) & ~0xf)
#define PCI_ROM_ADDR(address)           ((address) & ~1)
#define PCI_IS_MMAP20(address)          ((address) & 0x2)
#define PCI_IS_MMAP32(address)          (!((address) & 0x6))
#define PCI_IS_MMAP64(address)          ((address) & 0x4)
#define	PCI_IS_PREFETCH(address)		((address) & 0x8)
#define	PCI_IS_MULTIFUNC(address)		((address) & 0x80)
#define	PCI_DEVNO(address)				((address) >> 3)
#define	PCI_FUNCNO(address)				((address) & 7)
#define	PCI_DEVFUNC(dev,func)			((dev<<3)|(func))
#define PCI_CLASS(class)				(((class) & 0xff0000) >> 16)
#define PCI_SUBCLASS(class)				(((class) & 0xff00) >> 8)
#define PCI_INTERFACE(class)			((class) & 0xff)


#define	PCI_COMMAND_IO_ENABLE			0x0001
#define	PCI_COMMAND_MEM_ENABLE			0x0002
#define	PCI_COMMAND_MASTER_ENABLE		0x0004
#define	PCI_COMMAND_SPECIAL_ENABLE		0x0008
#define	PCI_COMMAND_INVALIDATE_ENABLE	0x0010
#define	PCI_COMMAND_PALETTE_ENABLE		0x0020
#define	PCI_COMMAND_PARITY_ENABLE		0x0040
#define	PCI_COMMAND_STEPPING_ENABLE		0x0080
#define	PCI_COMMAND_SERR_ENABLE			0x0100
#define	PCI_COMMAND_BACKTOBACK_ENABLE	0x0200
#define	PCI_COMMAND_INTX_DISABLE		0x0400

#define	PCI_STATUS_CAPABILITIES			0x0010
#define	PCI_STATUS_66MHZ_OKAY			0x0020
#define	PCI_STATUS_UDF_SUPPORTED		0x0040
#define	PCI_STATUS_BACKTOBACK_OKAY		0x0080
#define	PCI_STATUS_PARITY_ERROR			0x0100
#define	PCI_STATUS_DEVSEL_FAST			0x0000
#define	PCI_STATUS_DEVSEL_MEDIUM		0x0200
#define	PCI_STATUS_DEVSEL_SLOW			0x0400
#define	PCI_STATUS_DEVSEL_MASK			0x0600
#define	PCI_STATUS_DEVSEL_SHIFT			9
#define	PCI_STATUS_TARGET_TARGET_ABORT	0x0800
#define	PCI_STATUS_MASTER_TARGET_ABORT	0x1000
#define	PCI_STATUS_MASTER_ABORT			0x2000
#define	PCI_STATUS_SPECIAL_ERROR		0x4000
#define	PCI_STATUS_PARITY_DETECT		0x8000

#define PCI_ISPACEEN					0x00000001		/* IO space enable */
#define PCI_MSPACEEN					0x00000002		/* Memory space enable */
#define PCI_MASTEREN					0x00000004		/* Master enable */

/* pci capability defines */

#define	PCI_CAP_POWER_MANAGEMENT        0x01
#define	PCI_CAP_AGP                     0x02	/* Accelerated Graphics Port */
#define	PCI_CAP_VPD                     0x03	/* Vital Product Data */
#define PCI_CAP_SLOT_ID                 0x04	/* Slot Identification */
#define PCI_CAP_MSI                     0x05	/* Message Signalled Interrupts */
#define PCI_CAP_CPCI_HOT_SWAP           0x06	/* CompactPCI Hot Swap */
#define	PCI_CAP_PCIX					0x07	/* PCI-X */
#define	PCI_CAP_HT						0x08	/* HyperTransport */
#define	PCI_CAP_VENDSPEC				0x09	/* Vendor Specific */
#define	PCI_CAP_DEBUG_PORT				0x0a	/* Debug port */
#define	PCI_CAP_COMPACT_PCI				0x0b	/* Compact PCI */
#define	PCI_CAP_PCI_HOT_PLUG			0x0c	/* PCI Hot Plug */
#define	PCI_CAP_PCI_BRIDGE_SUBSYSTEM	0x0d	/* PCI Bridge Subsystem Vendor ID */
#define	PCI_CAP_AGP_8X					0x0e	/* AGP 8x */
#define	PCI_CAP_SECURE_DEVICE			0x0f	/* Secure Device */
#define	PCI_CAP_PCI_EXPRESS				0x10	/* PCI Express */
#define	PCI_CAP_MSI_X					0x11	/* MSI-X */

/* pci_attach_device flags */

#define PCI_SHARE			0x00000001
#define PCI_PERSIST			0x00000002
#define	PCI_SEARCH_VEND		0x00000010
#define	PCI_SEARCH_VENDEV	0x00000020
#define	PCI_SEARCH_CLASS	0x00000040
#define	PCI_SEARCH_BUSDEV	0x00000080
#define	PCI_SEARCH_MASK		0x000000f0
#define	PCI_MASK_VENDDEV	0x00000100
#define PCI_INIT_IRQ		0x00010000
#define PCI_INIT_ROM		0x00020000
#define PCI_INIT_BASE0		0x00040000
#define PCI_INIT_BASE1		0x00080000
#define PCI_INIT_BASE2		0x00100000
#define PCI_INIT_BASE3		0x00200000
#define PCI_INIT_BASE4		0x00400000
#define PCI_INIT_BASE5		0x00800000
#define	PCI_MASTER_ENABLE	0x01000000
#define	PCI_FASTB2B			0x02000000
#define	PCI_MGR_ATTACH		0x04000000
#define	PCI_BUS_INFO		0x10000000
#define	PCI_USE_MSI			0x20000000	/* default */
#define	PCI_USE_MSIX		0x40000000
#define PCI_INIT_ALL		0x00fd0000
#define	PCI_HW_INIT			0x00fe0000

#define	PCI_MSI				1
#define	PCI_MSIX			2

/* pci return codes */

#define PCI_SUCCESS                     0x00
#define PCI_UNSUPPORTED_FUNCT           0x81
#define PCI_BAD_VENDOR_ID               0x83
#define PCI_DEVICE_NOT_FOUND            0x86
#define PCI_BAD_REGISTER_NUMBER         0x87
#define PCI_SET_FAILED                  0x88
#define PCI_BUFFER_TOO_SMALL            0x89

/* pci prototypes */

extern int pci_attach(unsigned flags);
extern int pci_detach(unsigned handle);
extern int pci_find_device(unsigned devid, unsigned venid, unsigned index,
                                unsigned *busnum, unsigned *devfuncnum);
extern int pci_read_config(void *handle, unsigned offset, unsigned cnt,
								size_t size, void *bufptr);
extern int pci_write_config(void *handle, unsigned offset, unsigned cnt,
								size_t size, const void *bufptr);
extern void *pci_attach_device(void *handle, uint32_t flags, uint16_t idx, void *bufptr);
extern int pci_detach_device(void *handle);

extern int pci_read_config_bus(unsigned busnum, unsigned devfuncnum,
                    unsigned offset, unsigned cnt, size_t size, void *bufptr);
#define pci_read_config8(_a, _b, _c, _d, _e) pci_read_config_bus((_a), (_b), (_c), (_d), 1, (_e))
#define pci_read_config16(_a, _b, _c, _d, _e) pci_read_config_bus((_a), (_b), (_c), (_d), 2, (_e))
#define pci_read_config32(_a, _b, _c, _d, _e) pci_read_config_bus((_a), (_b), (_c), (_d), 4, (_e))


extern int pci_write_config_bus(unsigned busnum, unsigned devfuncnum,
                     unsigned offset, unsigned cnt, size_t size, const void *bufptr);
#define pci_write_config8(_a, _b, _c, _d, _e) pci_write_config_bus((_a), (_b), (_c), (_d), 1, (_e))
#define pci_write_config16(_a, _b, _c, _d, _e) pci_write_config_bus((_a), (_b), (_c), (_d), 2, (_e))
#define pci_write_config32(_a, _b, _c, _d, _e) pci_write_config_bus((_a), (_b), (_c), (_d), 4, (_e))

extern int pci_generate_special_cycle(unsigned Busnum,
                                unsigned long SpecialCycleData);
extern int pci_find_class(unsigned long ClassCode, unsigned index,
                                unsigned *busnum, unsigned *devfuncnum);
extern int pci_present(unsigned *lastbus, unsigned *version,
                                unsigned *hardware);
extern int pci_map_irq (unsigned busnum, unsigned devfuncnum, short intno, short intpin);

extern int pci_rescan_bus (void);

extern int pci_irq_routing_options (IRQRoutingOptionsBuffer *, uint32_t *);

__END_DECLS

#include <_packpop.h>

#define __PCI_H_INCLUDED
#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/hardware/pci/public/hw/pci.h $ $Rev: 237429 $" )
