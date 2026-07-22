#ifndef MGT5200_CPU_H
#define MGT5200_CPU_H
/*
 * $QNXLicenseC:
 * Copyright 2003, 2008, QNX Software Systems. 
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


/******************************************************************************
*
*       COPYRIGHT (c) 2002 MOTOROLA INC.
*       ALL RIGHTS RESERVED
*
*       This code is the property of Motorola, Inc. and is
*       Confidential Proprietary Information.
*
*       The copyright notice above does not evidence any
*       actual or intended publication of such source code.
*
* Filename:     $Source$
* Author:       $Author: hsbrown $
* Locker:       $Locker$
* State:        $State$
* Revision:     $Revision: 169807 $
*
* Functions:	
*
* History:      Use the RCS command rlog to display revision history
*               information.
*
* Description:	MGT5200 register and field definitions
*
* Notes:		
*
******************************************************************************/

/*
 * These are offsets from MBAR
 */
#define MBAR_CS         0x0000
#define MBAR_SDRAM      0x0100
#define MBAR_CDM        0x0200
#define MBAR_LPC        0x0300
#define MBAR_SCTMR      0x0400
#define MBAR_INT_CTRL   0x0500
#define MBAR_GPTIMER    0x0600
#define MBAR_SLTIMER    0x0700
#define MBAR_RTCLOCK    0x0800
#define MBAR_MSCAN      0x0900
#define MBAR_GPIO_STD   0x0B00
#define MBAR_GPIO_WKUP  0x0C00
#define MBAR_XCPCI      0x0D00
#define MBAR_SPI        0x0F00
#define MBAR_USB        0x1000
#define MBAR_SDMA       0x1200
#define MBAR_BDLC       0x1300
#define MBAR_IR         0x1400
#define MBAR_XLB_ARB    0x1F00
#define MBAR_PSC1       0x2000
#define MBAR_PSC2       0x2200
#define MBAR_PSC3       0x2400
#define MBAR_PSC4       0x2600
#define MBAR_PSC5       0x2800
#define MBAR_PSC6       0x2C00
#define MBAR_IRDA       0x2C00
#define MBAR_ETHERNET   0x3000
#define MBAR_SCPCI      0x3800
#define MBAR_ATA        0x3A00
#define MBAR_SCLPC      0x3C00
#define MBAR_I2C        0x3D00
#define MBAR_SRAM       0x8000

/* 
 * Absolute base addresses (including MBAR)
 */
#define MGT5200_MBAR_BASE			(0xf0000000)
#define MGT5200_MBAR_CDM			(MGT5200_MBAR_BASE + 0x0200)
#define MGT5200_MBAR_CSC_BOOT_ROM    (MGT5200_MBAR_BASE+0x0300)
#define MGT5200_MBAR_INT_CTRL		(MGT5200_MBAR_BASE + 0X0500)
#define MGT5200_MBAR_SLTIMER		(MGT5200_MBAR_BASE + 0X0700)
#define MGT5200_MBAR_GPIO_STD        (MGT5200_MBAR_BASE+0x0b00)

#define MGT5200_MBAR(reg, size)	(*(volatile uint##size##_t *)(MGT5200_MBAR_BASE + MGT5200_MBAR_##reg))

/* 
 * Clock Distribution Module(CDM) register addresses offset off of MBAR  
 */
#define MGT5200_MBAR_CDM_PORCFG		(0x0204)
#define MGT5200_MBAR_CDM_CFG		(0x020c)

/*
 * Interrupt Controller Register addresses offset off of MBAR
 */
#define MGT5200_MBAR_INT_CTRL_PIMSK			(0x0500)
#define MGT5200_MBAR_INT_CTRL_IRQCTL		(0x0510)
#define MGT5200_MBAR_INT_CTRL_CPRIMMSK		(0x0514)
#define MGT5200_MBAR_INT_CTRL_ISTAEC		(0x0524)
#define MGT5200_MBAR_INT_CTRL_CSTAB			(0x0528)
#define MGT5200_MBAR_INT_CTRL_MSTAB			(0x052c)
#define MGT5200_MBAR_INT_CTRL_PSTAB			(0x0530)


/*
 * General Purpose Timer Module (GPTMR)
 */
#define MGT5200_MBAR_GPTMR_CTL0			(0x0600)
#define MGT5200_MBAR_GPTMR_CNTINP0		(0X0604)
#define MGT5200_MBAR_GPTMR_PWMCFG0		(0x0608)
#define MGT5200_MBAR_GPTMR_STA0			(0x060c)

#define MGT5200_GPTMR_CTL_WDEN			_ONEBIT32B(16)
#define MGT5200_GPTMR_CTL_CE			_ONEBIT32B(19)

/*
 * Slice timer addresses offset off of MBAR
 */
#define MGT5200_MBAR_SLTIMER_TCNT1			(0X0700)
#define MGT5200_MBAR_SLTIMER_CTL1			(0X0704)
#define MGT5200_MBAR_SLTIMER_TMRCNT1		(0X0708)
#define MGT5200_MBAR_SLTIMER_TMRSTA1		(0X070c)
#define MGT5200_MBAR_SLTIMER_TCNT2	 		(0X0710)
#define MGT5200_MBAR_SLTIMER_CTL2			(0X0714)
#define MGT5200_MBAR_SLTIMER_TMRCNT2		(0X0718)
#define MGT5200_MBAR_SLTIMER_TMRSTA2		(0X071c)

/*
 * Real-time clock module
 */
#define MGT5200_MBAR_RTC_BASE               (0x800)
#define MGT5200_MBAR_RTC_CTIME				(0x0810)
#define MGT5200_MBAR_RTC_CDATE				(0x0814)

#define MGT5200_RTC_CTIME_HRS_MASK		(0x001f0000)
#define MGT5200_RTC_CTIME_HRS_SHIFT		16
#define MGT5200_RTC_CTIME_MIN_MASK		(0x00003f00)
#define MGT5200_RTC_CTIME_MIN_SHIFT		8
#define MGT5200_RTC_CTIME_SEC_MASK		(0x0000003f)
#define MGT5200_RTC_CTIME_SEC_SHIFT		0
#define MGT5200_RTC_CDATE_MON_MASK		(0x0f000000)
#define MGT5200_RTC_CDATE_MON_SHIFT		24
#define MGT5200_RTC_CDATE_DAY_MASK		(0x001f0000)
#define MGT5200_RTC_CDATE_DAY_SHIFT		16
#define MGT5200_RTC_CDATE_YEAR_MASK		(0x00000fff)
#define MGT5200_RTC_CDATE_YEAR_SHIFT	0

/* SET time register */
#define MGT5200_MBAR_RTC_STIME					(0x0800)
#define MGT5200_MBAR_RTC_STIME_SET_MASK			(0x02000000)
#define MGT5200_MBAR_RTC_STIME_PAUSE_MASK		(0x01000000)
#define MGT5200_MBAR_RTC_STIME_HOUR_MASK		(0x001f0000)
#define MGT5200_MBAR_RTC_STIME_HOUR_SHIFT		16
#define MGT5200_MBAR_RTC_STIME_MIN_MASK			(0x00003f00)
#define MGT5200_MBAR_RTC_STIME_MIN_SHIFT		8
#define MGT5200_MBAR_RTC_STIME_SEC_MASK			(0x0000003f)
#define MGT5200_MBAR_RTC_STIME_SEC_SHIFT		0

/* SET date register */
#define MGT5200_MBAR_RTC_SDATE					(0x0804)
#define MGT5200_MBAR_RTC_SDATE_SET_MASK			(0x02000000)
#define MGT5200_MBAR_RTC_SDATE_PAUSE_MASK		(0x01000000)
#define MGT5200_MBAR_RTC_SDATE_MON_MASK			(0x001f0000)
#define MGT5200_MBAR_RTC_SDATE_MON_SHIFT		16
#define MGT5200_MBAR_RTC_SDATE_WDAY_MASK		(0x00003f00)
#define MGT5200_MBAR_RTC_SDATE_WDAY_SHIFT		8
#define MGT5200_MBAR_RTC_SDATE_DAY_MASK			(0x0000003f)
#define MGT5200_MBAR_RTC_SDATE_DAY_SHIFT		0

/* SET year register */
#define MGT5200_MBAR_RTC_SYEAR					(0x0808)
#define MGT5200_MBAR_RTC_SYEAR_YEAR_MASK		(0x00000FFF)
#define MGT5200_MBAR_RTC_SYEAR_YEAR_SHIFT		0

/* 
 * POR Configuration Register (PORCFG) 
 */
#define MGT5200_PORCFG_SYS_PLL_CFG_0		_ONEBIT32B(25)
#define MGT5200_PORCFG_XLB_CLK_SEL			_ONEBIT32B(26)
#define MGT5200_PORCFG_PPC_PLL_CFG_4		_ONEBIT32B(27)
#define MGT5200_PORCFG_PPC_PLL_CFG_3		_ONEBIT32B(28)
#define MGT5200_PORCFG_PPC_PLL_CFG_2		_ONEBIT32B(29)
#define MGT5200_PORCFG_PPC_PLL_CFG_1		_ONEBIT32B(30)
#define MGT5200_PORCFG_PPC_PLL_CFG_0		_ONEBIT32B(31)


/*
 * CDM Configuration Register (CDMCFG)
 */
#define MGT5200_CDMCFG_DDR_MODE			_ONEBIT32B(7)
#define MGT5200_CDMCFG_XLB_SEL			_ONEBIT32B(15)
#define MGT5200_CDMCFG_IPB_CLK_SEL		_ONEBIT32B(23)
#define MGT5200_CDMCFG_PCI_CLK_SEL		_ONEBIT32B(31)


/*
 * Slice Timer Registers (SLTMR)
 */
#define MGT5200_TCNT1_TERMINALCNT_MASK		_BITFIELD32B(31, 0xffffff)
#define MGT5200_CTL1_RUNWAIT				_ONEBIT32B(5)
#define MGT5200_CTL1_IE						_ONEBIT32B(6)
#define	MGT5200_CTL1_TE						_ONEBIT32B(7)
#define MGT5200_TMRCNT1_TIMERCNT_MASK		_BITFIELD32B(31, 0xffffff)
#define MGT5200_TMRSTA1_ST					_ONEBIT32B(7)


/*
 * Peripheral Interrupt Mask (PIMSK)
 */
#define MGT5200_PIMSK_PERMASK_MASK			_BITFIELD32B(21, 0x3fffff)
#define MGT5200_PIMSK_PERMASK_SHIFT			(31-21) 


/*
 * Interrupt Request Control Register (IRQCTL)
 */
#define MGT5200_IRQCTL_ECLR_MASK			_BITFIELD32B(7, 0xf)
#define MGT5200_IRQCTL_MEE					_ONEBIT32B(19)


/*
 * Critical Priority & Main Mask Register (CPRIMMSK)
 */
#define MGT5200_CPRIMMSK_CRIT0_PRI_MASK		_BITFIELD32B(1, 0x3)
#define MGT5200_CPRIMMSK_CRIT0_PRI_SHIFT	(31-1)
#define MGT5200_CPRIMMSK_CRIT1_PRI_MASK		_BITFIELD32B(3, 0x3)
#define MGT5200_CPRIMMSK_CRIT1_PRI_SHIFT	(31-3)
#define MGT5200_CPRIMMSK_CRIT2_PRI_MASK		_BITFIELD32B(5, 0x3)
#define MGT5200_CPRIMMSK_CRIT2_PRI_SHIFT	(31-5)
#define MGT5200_CPRIMMSK_CRIT3_PRI_MASK		_BITFIELD32B(7, 0x3)
#define MGT5200_CPRIMMSK_CRIT3_PRI_SHIFT	(31-7)
#define MGT5200_CPRIMMSK_MAINMASK_MASK		_BITFIELD32B(31, 0x1ffff)
#define MGT5200_CPRIMMSK_MAINMASK_SHIFT		(31-31)



/*
 * Interrupt Status Encoded (ISTAEC)
 */
#define MGT5200_ISTAEC_PSE_MASK				_BITFIELD32B(7, 0x3f)
#define MGT5200_ISTAEC_PSE_SHIFT			(31-7)
#define MGT5200_ISTAEC_MSE_MASK				_BITFIELD32B(15, 0x3f)
#define MGT5200_ISTAEC_MSE_SHIFT			(31-15)
#define MGT5200_ISTAEC_CSE_MASK				_BITFIELD32B(23, 0x7)
#define MGT5200_ISTAEC_CSE_SHIFT			(31-23)



/*
 * Critical Status Binary Register (CSTAB)
 */
#define MGT5200_CSTAB_CSA0		_ONEBIT32B(4)
#define MGT5200_CSTAB_CSA1		_ONEBIT32B(5)
#define MGT5200_CSTAB_CSA3		_ONEBIT32B(6)
#define MGT5200_CSTAB_CSA4		_ONEBIT32B(7)

/*
 * Programmable Serial Controller Module (PSC)
 */

/* These offsets are relative to the start of each PSCn register set */
#define MGT5200_PSC_SR			(0x0004)
#define MGT5200_PSC_CSR			(0x0004)
#define MGT5200_PSC_RB			(0x000c)
#define MGT5200_PSC_TB			(0x000c)

/* These are bit-masks for register fields */
#define MGT5200_PSC_SR_TXRDY	(0x4000)
#define MGT5200_PSC_SR_RXRDY	(0x1000)
#define MGT5200_PSC_SR_RB		(0x8000)

/*
 * Main Status Binary Register (MSTAB)
 */
#define MGT5200_MSTAB_MSA_MASK		_BITFIELD32B(31, 0x1ffff)

/*
 *Definitions for Glacier detection routine 
 */
#define CSCR_MX			0x00008000
#define CSCR_AL			0x00004000
#define CSCR_AS_25		0x00000C00
#define CSCR_DS_32		0x00000300
#define CSCR_CE			0x00001000


/*****************************************************************************/
#endif	/* MGT5200_CPU_H */
