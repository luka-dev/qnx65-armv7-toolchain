/*
 * $QNXLicenseC: 
 * Copyright 2007, QNX Software Systems.  
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


#ifndef MPC512X_CPU_H
#define MPC512X_CPU_H


/*
 * These are offsets from MBAR
 */
#define MBAR_XLBMEM                 0x00000
#define MBAR_WDT                    0x00900
#define MBAR_RTC                    0x00A00
#define MBAR_GPT                    0x00B00
#define MBAR_IPIC                   0x00C00
#define MBAR_CSB                    0x00D00
#define MBAR_RESET                  0x00E00
#define MBAR_CLOCK                  0x00F00
#define MBAR_PMC                    0x01000
#define MBAR_GPIO                   0x01100
#define MBAR_MSCAN                  0x01300
#define MBAR_BDLC                   0x01400
#define MBAR_SDHC                   0x01500
#define MBAR_SPDIR                  0x01600
#define MBAR_I2C0                   0x01700
#define MBAR_I2C1                   0x01720
#define MBAR_I2C2                   0x01740
#define MBAR_AXE                    0x02000
#define MBAR_DIU                    0x02100
#define MBAR_CFM                    0x02200
#define MBAR_FEC                    0x02800
#define MBAR_USB_ULPI               0x03000
#define MBAR_USB_UTMI               0x04000
#define MBAR_PCI_DMA                0x08000
#define MBAR_PCI_CFG                0x08300
#define MBAR_PCI_IOS                0x08400
#define MBAR_PCI_CTRL               0x08500
#define MBAR_MDDRC                  0x09000
#define MBAR_IO_CTRL                0x0A000
#define MBAR_IIM                    0x0B000
#define MBAR_LPC                    0x10000
#define MBAR_ATA                    0x10200
#define MBAR_PSC0                   0x11000
#define MBAR_PSC1                   0x11100
#define MBAR_PSC2                   0x11200
#define MBAR_PSC3                   0x11300
#define MBAR_PSC4                   0x11400
#define MBAR_PSC5                   0x11500
#define MBAR_PSC6                   0x11600
#define MBAR_PSC7                   0x11700
#define MBAR_PSC8                   0x11800
#define MBAR_PSC9                   0x11900
#define MBAR_PSC10                  0x11A00
#define MBAR_PSC11                  0x11B00
#define MBAR_SFIFO                  0x11C00
#define MBAR_DMA                    0x14000
#define MBAR_SATA                   0x20000

/*
 * These are size within  MBAR
 */

#define MBAR_XLBMEM_SIZE            0x200
#define MBAR_WDT_SIZE               0x100
#define MBAR_RTC_SIZE               0x100
#define MBAR_GPT_SIZE               0x100
#define MBAR_IPIC_SIZE              0x100
#define MBAR_CSB_SIZE               0x100
#define MBAR_RESET_SIZE             0x100
#define MBAR_CLOCK_SIZE             0x100
#define MBAR_PMC_SIZE               0x100
#define MBAR_GPIO_SIZE              0x100
#define MBAR_MSCAN_SIZE             0x100
#define MBAR_BDLC_SIZE              0x100
#define MBAR_SDHC_SIZE              0x100
#define MBAR_SPDIR_SIZE             0x100
#define MBAR_I2Cx_SIZE              0x20
#define MBAR_AXE_SIZE               0x100
#define MBAR_DIU_SIZE               0x100
#define MBAR_CFM_SIZE               0x100
#define MBAR_FEC_SIZE               0x800
#define MBAR_USB_ULPI_SIZE          0x600
#define MBAR_USB_UTMI_SIZE          0x600
#define MBAR_PCI_DMA_SIZE           0x300
#define MBAR_PCI_CFG_SIZE           0x80
#define MBAR_PCI_IOS_SIZE           0x100
#define MBAR_PCI_CTRL_SIZE          0x100
#define MBAR_MDDRC_SIZE             0x1000
#define MBAR_IO_CTRL_SIZE           0x1000
#define MBAR_IIM_SIZE               0x1000
#define MBAR_LPC_SIZE               0x200
#define MBAR_ATA_SIZE               0x100
#define MBAR_PSCx_SIZE              0x100
#define MBAR_SFIFO_SIZE             0x100
#define MBAR_DMA_SIZE               0x180
#define MBAR_SATA_SIZE              0x2000

#define MPC512X_MBAR(reg, size) (*(volatile uint##size##_t *)(MPC512X_MBAR_BASE + MPC512X_MBAR_##reg))

/* 
 * Clock Distribution Module(CDM) register addresses offset off of MBAR  
 */
#define MPC512X_MBAR_CDM_PORCFG     (0x0204)
#define MPC512X_MBAR_CDM_CFG        (0x020c)

/*
 * Interrupt Controller Register addresses offset off of MBAR
 */
#define MPC512X_MBAR_INT_CTRL_PIMSK         (0x0500)
#define MPC512X_MBAR_INT_CTRL_IRQCTL        (0x0510)
#define MPC512X_MBAR_INT_CTRL_CPRIMMSK      (0x0514)
#define MPC512X_MBAR_INT_CTRL_ISTAEC        (0x0524)
#define MPC512X_MBAR_INT_CTRL_CSTAB         (0x0528)
#define MPC512X_MBAR_INT_CTRL_MSTAB         (0x052c)
#define MPC512X_MBAR_INT_CTRL_PSTAB         (0x0530)

/*
 * General Purpose Timer Module (GPTMR)
 */
#define MPC512X_MBAR_GPTMR_CTL0         (0x0600)
#define MPC512X_MBAR_GPTMR_CNTINP0      (0X0604)
#define MPC512X_MBAR_GPTMR_PWMCFG0      (0x0608)
#define MPC512X_MBAR_GPTMR_STA0         (0x060c)

#define MPC512X_GPTMR_CTL_WDEN          _ONEBIT32B(16)
#define MPC512X_GPTMR_CTL_CE            _ONEBIT32B(19)

/*
 * Slice timer addresses offset off of MBAR
 */
#define MPC512X_MBAR_SLTIMER_TCNT1          (0X0700)
#define MPC512X_MBAR_SLTIMER_CTL1           (0X0704)
#define MPC512X_MBAR_SLTIMER_TMRCNT1        (0X0708)
#define MPC512X_MBAR_SLTIMER_TMRSTA1        (0X070c)
#define MPC512X_MBAR_SLTIMER_TCNT2          (0X0710)
#define MPC512X_MBAR_SLTIMER_CTL2           (0X0714)
#define MPC512X_MBAR_SLTIMER_TMRCNT2        (0X0718)
#define MPC512X_MBAR_SLTIMER_TMRSTA2        (0X071c)

/*
 * Real-time clock module
 */
#define MPC512X_MBAR_RTC_BASE               (MBAR_RTC)
#define MPC512X_MBAR_RTC_CTIME              (MPC512X_MBAR_RTC_BASE + 0x10)
#define MPC512X_MBAR_RTC_CDATE              (MPC512X_MBAR_RTC_BASE + 0x14)

#define MPC512X_RTC_CTIME_HRS_MASK      (0x001f0000)
#define MPC512X_RTC_CTIME_HRS_SHIFT     16
#define MPC512X_RTC_CTIME_MIN_MASK      (0x00003f00)
#define MPC512X_RTC_CTIME_MIN_SHIFT     8
#define MPC512X_RTC_CTIME_SEC_MASK      (0x0000003f)
#define MPC512X_RTC_CTIME_SEC_SHIFT     0
#define MPC512X_RTC_CDATE_MON_MASK      (0x0f000000)
#define MPC512X_RTC_CDATE_MON_SHIFT     24
#define MPC512X_RTC_CDATE_DAY_MASK      (0x001f0000)
#define MPC512X_RTC_CDATE_DAY_SHIFT     16
#define MPC512X_RTC_CDATE_YEAR_MASK     (0x00000fff)
#define MPC512X_RTC_CDATE_YEAR_SHIFT    0

/* SET time register */
#define MPC512X_MBAR_RTC_STIME                  (MBAR_RTC)
#define MPC512X_MBAR_RTC_STIME_SET_MASK         (0x02000000)
#define MPC512X_MBAR_RTC_STIME_PAUSE_MASK       (0x01000000)
#define MPC512X_MBAR_RTC_STIME_HOUR_MASK        (0x001f0000)
#define MPC512X_MBAR_RTC_STIME_HOUR_SHIFT       16
#define MPC512X_MBAR_RTC_STIME_MIN_MASK         (0x00003f00)
#define MPC512X_MBAR_RTC_STIME_MIN_SHIFT        8
#define MPC512X_MBAR_RTC_STIME_SEC_MASK         (0x0000003f)
#define MPC512X_MBAR_RTC_STIME_SEC_SHIFT        0

/* SET date register */
#define MPC512X_MBAR_RTC_SDATE                  (MBAR_RTC + 4)
#define MPC512X_MBAR_RTC_SDATE_SET_MASK         (0x02000000)
#define MPC512X_MBAR_RTC_SDATE_PAUSE_MASK       (0x01000000)
#define MPC512X_MBAR_RTC_SDATE_MON_MASK         (0x001f0000)
#define MPC512X_MBAR_RTC_SDATE_MON_SHIFT        16
#define MPC512X_MBAR_RTC_SDATE_WDAY_MASK        (0x00003f00)
#define MPC512X_MBAR_RTC_SDATE_WDAY_SHIFT       8
#define MPC512X_MBAR_RTC_SDATE_DAY_MASK         (0x0000003f)
#define MPC512X_MBAR_RTC_SDATE_DAY_SHIFT        0

/* SET year register */
#define MPC512X_MBAR_RTC_SYEAR                  (MBAR_RTC + 8)
#define MPC512X_MBAR_RTC_SYEAR_YEAR_MASK        (0x00000FFF)
#define MPC512X_MBAR_RTC_SYEAR_YEAR_SHIFT       0

/* 
 * POR Configuration Register (PORCFG) 
 */
#define MPC512X_PORCFG_SYS_PLL_CFG_0        _ONEBIT32B(25)
#define MPC512X_PORCFG_XLB_CLK_SEL          _ONEBIT32B(26)
#define MPC512X_PORCFG_PPC_PLL_CFG_4        _ONEBIT32B(27)
#define MPC512X_PORCFG_PPC_PLL_CFG_3        _ONEBIT32B(28)
#define MPC512X_PORCFG_PPC_PLL_CFG_2        _ONEBIT32B(29)
#define MPC512X_PORCFG_PPC_PLL_CFG_1        _ONEBIT32B(30)
#define MPC512X_PORCFG_PPC_PLL_CFG_0        _ONEBIT32B(31)


/*
 * CDM Configuration Register (CDMCFG)
 */
#define MPC512X_CDMCFG_DDR_MODE         _ONEBIT32B(7)
#define MPC512X_CDMCFG_XLB_SEL          _ONEBIT32B(15)
#define MPC512X_CDMCFG_IPB_CLK_SEL      _ONEBIT32B(23)
#define MPC512X_CDMCFG_PCI_CLK_SEL      _ONEBIT32B(31)


/*
 * Slice Timer Registers (SLTMR)
 */
#define MPC512X_TCNT1_TERMINALCNT_MASK      _BITFIELD32B(31, 0xffffff)
#define MPC512X_CTL1_RUNWAIT                _ONEBIT32B(5)
#define MPC512X_CTL1_IE                     _ONEBIT32B(6)
#define MPC512X_CTL1_TE                     _ONEBIT32B(7)
#define MPC512X_TMRCNT1_TIMERCNT_MASK       _BITFIELD32B(31, 0xffffff)
#define MPC512X_TMRSTA1_ST                  _ONEBIT32B(7)


/*
 * Peripheral Interrupt Mask (PIMSK)
 */
#define MPC512X_PIMSK_PERMASK_MASK          _BITFIELD32B(21, 0x3fffff)
#define MPC512X_PIMSK_PERMASK_SHIFT         (31-21) 


/*
 * Interrupt Request Control Register (IRQCTL)
 */
#define MPC512X_IRQCTL_ECLR_MASK            _BITFIELD32B(7, 0xf)
#define MPC512X_IRQCTL_MEE                  _ONEBIT32B(19)


/*
 * Critical Priority & Main Mask Register (CPRIMMSK)
 */
#define MPC512X_CPRIMMSK_CRIT0_PRI_MASK     _BITFIELD32B(1, 0x3)
#define MPC512X_CPRIMMSK_CRIT0_PRI_SHIFT    (31-1)
#define MPC512X_CPRIMMSK_CRIT1_PRI_MASK     _BITFIELD32B(3, 0x3)
#define MPC512X_CPRIMMSK_CRIT1_PRI_SHIFT    (31-3)
#define MPC512X_CPRIMMSK_CRIT2_PRI_MASK     _BITFIELD32B(5, 0x3)
#define MPC512X_CPRIMMSK_CRIT2_PRI_SHIFT    (31-5)
#define MPC512X_CPRIMMSK_CRIT3_PRI_MASK     _BITFIELD32B(7, 0x3)
#define MPC512X_CPRIMMSK_CRIT3_PRI_SHIFT    (31-7)
#define MPC512X_CPRIMMSK_MAINMASK_MASK      _BITFIELD32B(31, 0x1ffff)
#define MPC512X_CPRIMMSK_MAINMASK_SHIFT     (31-31)



/*
 * Interrupt Status Encoded (ISTAEC)
 */
#define MPC512X_ISTAEC_PSE_MASK             _BITFIELD32B(7, 0x3f)
#define MPC512X_ISTAEC_PSE_SHIFT            (31-7)
#define MPC512X_ISTAEC_MSE_MASK             _BITFIELD32B(15, 0x3f)
#define MPC512X_ISTAEC_MSE_SHIFT            (31-15)
#define MPC512X_ISTAEC_CSE_MASK             _BITFIELD32B(23, 0x7)
#define MPC512X_ISTAEC_CSE_SHIFT            (31-23)



/*
 * Critical Status Binary Register (CSTAB)
 */
#define MPC512X_CSTAB_CSA0      _ONEBIT32B(4)
#define MPC512X_CSTAB_CSA1      _ONEBIT32B(5)
#define MPC512X_CSTAB_CSA3      _ONEBIT32B(6)
#define MPC512X_CSTAB_CSA4      _ONEBIT32B(7)

/*
 * Programmable Serial Controller Module (PSC)
 */

/* These offsets are relative to the start of each PSCn register set */
#define MPC512X_PSC_SR          (0x0004)
#define MPC512X_PSC_CSR         (0x0004)
#define MPC512X_PSC_RB          (0x000c)
#define MPC512X_PSC_TB          (0x000c)

/* These are bit-masks for register fields */
#define MPC512X_PSC_SR_TXRDY    (0x4000)
#define MPC512X_PSC_SR_RXRDY    (0x1000)
#define MPC512X_PSC_SR_RB       (0x8000)

/*
 * Main Status Binary Register (MSTAB)
 */
#define MPC512X_MSTAB_MSA_MASK      _BITFIELD32B(31, 0x1ffff)

/*
 *Definitions for Glacier detection routine 
 */
#define CSCR_MX         0x00008000
#define CSCR_AL         0x00004000
#define CSCR_AS_25      0x00000C00
#define CSCR_DS_32      0x00000300
#define CSCR_CE         0x00001000

/*
 * NAND flash controller base address and size
 */
#define MPC512X_NAND_BASE					0x40000000
#define MPC512X_NAND_SIZE					0x1000

/* NAND flash controller register offsets */
#define MPC512X_NAND_MAIN_BUF_0				0x000
#define MPC512X_NAND_MAIN_BUF_1				0x200
#define MPC512X_NAND_MAIN_BUF_2				0x400
#define MPC512X_NAND_MAIN_BUF_3				0x600
#define MPC512X_NAND_SPARE_BUF_0			0x800
#define MPC512X_NAND_SPARE_BUF_1			0x810
#define MPC512X_NAND_SPARE_BUF_2			0x820
#define MPC512X_NAND_SPARE_BUF_3			0x830
#define	MPC512X_NAND_NFC_REGISTER			0xE00

#define MPC512X_NAND_NFC_BUFSIZE			0x000
#define MPC512X_NAND_RAM_BUFFER_ADDRESS		0x004
#define MPC512X_NAND_FLASH_ADD				0x006
#define MPC512X_NAND_FLASH_CMD				0x008
#define MPC512X_NAND_NFC_CONFIGURATION		0x00A
#define MPC512X_NAND_ECC_STATUS_RESULT		0x00C
#define MPC512X_NAND_ECC_RSLT_MAIN_AREA		0x00E
#define MPC512X_NAND_ECC_RSLT_SPARE_AREA	0x010
#define MPC512X_NAND_NF_WR_PROT				0x012
#define MPC512X_NAND_UNLOCK_START_BLK_ADD	0x014
#define MPC512X_NAND_UNLOCK_END_BLK_ADD		0x016
#define MPC512X_NAND_FLASH_WR_PR_ST			0x018
#define MPC512X_NAND_FLASH_CONFIG1			0x01A
#define MPC512X_NAND_FLASH_CONFIG2			0x01C

/* bit definitions for various NAND registers */
#define NAND_CONFIG1_NF_CE					0x80	// force CE# always
#define NAND_CONFIG1_NFC_RST				0x40	// reset NAND state machine
#define NAND_CONFIG1_NF_BIG					0x20	// enable big endian mode
#define NAND_CONFIG1_INT_MSK				0x10	// mask interrupt - 0 == interrupt enabled, 1 == interrupt disabled
#define NAND_CONFIG1_ECC_EN					0x08	// enable ECC operation
#define NAND_CONFIG1_SP_EN					0x04	// enable spare area only

#define NAND_CONFIG2_INT					0x8000	// status; 1 == ready, 0 == busy

#define NAND_CONFIG2_FDO_PDO				0x08	// 1 page data out
#define NAND_CONFIG2_FDO_ID_OUT				0x10	// flash ID data out
#define NAND_CONFIG2_FDO_STAT_OUT			0x20	// flash status register data out

#define NAND_CONFIG2_FDI					0x04	// enable NAND data input
#define NAND_CONFIG2_FADD					0x02	// enable NAND address input
#define NAND_CONFIG2_FCMD					0x01	// enable NAND command input

/*****************************************************************************/
#endif  /* MPC512X_CPU_H */

