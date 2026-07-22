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
 * SH-X3 prototype internal register offsets
 */

#ifndef _SH_X3P_H_INCLUDED
#define _SH_X3P_H_INCLUDED

/*
 * Interrupt Controller
 */

#define SH_X3P_INTC_ICR0			0xfe410000
#define SH_X3P_INTC_ICR1			0xfe41001c
#define SH_X3P_INTC_INTPRI0			0xfe410010
#define SH_X3P_INTC_INTREQ			0xfe410024
#define SH_X3P_INTC_C0INTMSK0		0xfe410030
#define SH_X3P_INTC_C1INTMSK0		0xfe410034
#define SH_X3P_INTC_C2INTMSK0		0xfe410038
#define SH_X3P_INTC_C3INTMSK0		0xfe41003c
#define SH_X3P_INTC_C0INTMSK1		0xfe410040
#define SH_X3P_INTC_C1INTMSK1		0xfe410044
#define SH_X3P_INTC_C2INTMSK1		0xfe410048
#define SH_X3P_INTC_C3INTMSK1		0xfe41004c
#define SH_X3P_INTC_C0INTMSKCLR0	0xfe410050
#define SH_X3P_INTC_C1INTMSKCLR0	0xfe410054
#define SH_X3P_INTC_C2INTMSKCLR0	0xfe410058
#define SH_X3P_INTC_C3INTMSKCLR0	0xfe41005c
#define SH_X3P_INTC_C0INTMSKCLR1	0xfe410060
#define SH_X3P_INTC_C1INTMSKCLR1	0xfe410064
#define SH_X3P_INTC_C2INTMSKCLR1	0xfe410068
#define SH_X3P_INTC_C3INTMSKCLR1	0xfe41006c
#define SH_X3P_INTC_NMIFCR			0xfe4100c0
#define SH_X3P_INTC_NMISET			0xfe4100c4
#define SH_X3P_INTC_USERIMASK		0xfe411000
#define SH_X3P_INTC_INT2PRI0		0xfe410800
#define SH_X3P_INTC_INT2PRI1		0xfe410804
#define SH_X3P_INTC_INT2PRI2		0xfe410808
#define SH_X3P_INTC_INT2PRI3		0xfe41080c
#define SH_X3P_INTC_INT2PRI4		0xfe410810
#define SH_X3P_INTC_C0INT2MSK0		0xfe410820
#define SH_X3P_INTC_C1INT2MSK0		0xfe410824
#define SH_X3P_INTC_C2INT2MSK0		0xfe410828
#define SH_X3P_INTC_C3INT2MSK0		0xfe41082c
#define SH_X3P_INTC_C0INT2MSK1		0xfe410830
#define SH_X3P_INTC_C1INT2MSK1		0xfe410834
#define SH_X3P_INTC_C2INT2MSK1		0xfe410838
#define SH_X3P_INTC_C3INT2MSK1		0xfe41083c
#define SH_X3P_INTC_C0INT2MSK2		0xfe410840
#define SH_X3P_INTC_C1INT2MSK2		0xfe410844
#define SH_X3P_INTC_C2INT2MSK2		0xfe410848
#define SH_X3P_INTC_C3INT2MSK2		0xfe41084c
#define SH_X3P_INTC_C0INT2MSKCLR0	0xfe410850
#define SH_X3P_INTC_C1INT2MSKCLR0	0xfe410854
#define SH_X3P_INTC_C2INT2MSKCLR0	0xfe410858
#define SH_X3P_INTC_C3INT2MSKCLR0	0xfe41085c
#define SH_X3P_INTC_C0INT2MSKCLR1	0xfe410860
#define SH_X3P_INTC_C1INT2MSKCLR1	0xfe410864
#define SH_X3P_INTC_C2INT2MSKCLR1	0xfe410868
#define SH_X3P_INTC_C3INT2MSKCLR1	0xfe41086c
#define SH_X3P_INTC_C0INT2MSKCLR2	0xfe410870
#define SH_X3P_INTC_C1INT2MSKCLR2	0xfe410874
#define SH_X3P_INTC_C2INT2MSKCLR2	0xfe410878
#define SH_X3P_INTC_C3INT2MSKCLR2	0xfe41087c
#define SH_X3P_INTC_C0INTICI		0xfe410070
#define SH_X3P_INTC_C1INTICI		0xfe410074
#define SH_X3P_INTC_C2INTICI		0xfe410078
#define SH_X3P_INTC_C3INTICI		0xfe41007c
#define SH_X3P_INTC_C0INTICICLR		0xfe410080
#define SH_X3P_INTC_C1INTICICLR		0xfe410084
#define SH_X3P_INTC_C2INTICICLR		0xfe410088
#define SH_X3P_INTC_C3INTICICLR		0xfe41008c
#define SH_X3P_INTC_C0ICIPRI		0xfe410090
#define SH_X3P_INTC_C1ICIPRI		0xfe410094
#define SH_X3P_INTC_C2ICIPRI		0xfe410098
#define SH_X3P_INTC_C3ICIPRI		0xfe41009c
#define SH_X3P_INTC_C0ICIPRICLR		0xfe4100a0
#define SH_X3P_INTC_C1ICIPRICLR		0xfe4100a4
#define SH_X3P_INTC_C2ICIPRICLR		0xfe4100a8
#define SH_X3P_INTC_C3ICIPRICLR		0xfe4100ac
#define SH_X3P_INTC_INTDISTCR0		0xfe4100b0
#define SH_X3P_INTC_INTDISTCR1		0xfe4100b4
#define SH_X3P_INTC_INT2DISTCR0		0xfe4108a0
#define SH_X3P_INTC_INT2DISTCR1		0xfe4108a4
#define SH_X3P_INTC_INT2DISTCR2		0xfe4108a8
#define SH_X3P_INTC_INTACK			0xfe4100b8
#define SH_X3P_INTC_INTACKCLR		0xfe4100bc
#define SH_X3P_INTC_INTACKMSK0		0xfe4100d0
#define SH_X3P_INTC_INTACKMSK1		0xfe4100d4
#define SH_X3P_INTC_INT2ACKMSK0		0xfe4100d8
#define SH_X3P_INTC_INT2ACKMSK1		0xfe4100dc
#define SH_X3P_INTC_INT2ACKMSK2		0xfe4100e0

/*
 * Local Bus State Controller
 */
#define SH_X3P_LBSC_MMSELR			0xff400020
#define SH_X3P_LBSC_BCR				0xff801000
#define SH_X3P_LBSC_CS0BCR			0xff802000
#define SH_X3P_LBSC_CS1BCR			0xff802010
#define SH_X3P_LBSC_CS4BCR			0xff802040
#define SH_X3P_LBSC_CS5BCR			0xff802050
#define SH_X3P_LBSC_CS6BCR			0xff802060
#define SH_X3P_LBSC_CS0WCR			0xff802008
#define SH_X3P_LBSC_CS1WCR			0xff802018
#define SH_X3P_LBSC_CS4WCR			0xff802048
#define SH_X3P_LBSC_CS5WCR			0xff802058
#define SH_X3P_LBSC_CS6WCR			0xff802068
#define SH_X3P_LBSC_CS5PCR			0xff802070
#define SH_X3P_LBSC_CS6PCR			0xff802080

/*
 * DDR2-SDRAM Interface Controller
 */
#define SH_X3P_DBSC2_DBSTATE		0xfe80000C
#define SH_X3P_DBSC2_DBEN			0xfe800010
#define SH_X3P_DBSC2_DBCMDCNT		0xfe800014
#define SH_X3P_DBSC2_DBCONF			0xfe800020
#define SH_X3P_DBSC2_DBTR0			0xfe800030
#define SH_X3P_DBSC2_DBTR1			0xfe800034
#define SH_X3P_DBSC2_DBTR2			0xfe800038
#define SH_X3P_DBSC2_DBRFCNT0		0xfe800040
#define SH_X3P_DBSC2_DBRFCNT1		0xfe800044
#define SH_X3P_DBSC2_DBRFCNT2		0xfe800048
#define SH_X3P_DBSC2_DBRFSTS		0xfe80004C
#define SH_X3P_DBSC2_DBFREQ			0xfe800050
#define SH_X3P_DBSC2_DBDICODTOCD	0xfe800054
#define SH_X3P_DBSC2_DBMRCNT		0xfe800060

/*
 * DMA Controller
 */
#define SH_X3P_DMAC_SAR0			0xfcc08020
#define SH_X3P_DMAC_DAR0			0xfcc08024
#define SH_X3P_DMAC_TCR0			0xfcc08028
#define SH_X3P_DMAC_CHCR0			0xfcc0802C
#define SH_X3P_DMAC_SAR1			0xfcc08030
#define SH_X3P_DMAC_DAR1			0xfcc08034
#define SH_X3P_DMAC_TCR1			0xfcc08038
#define SH_X3P_DMAC_CHCR1			0xfcc0803C
#define SH_X3P_DMAC_SAR2			0xfcc08040
#define SH_X3P_DMAC_DAR2			0xfcc08044
#define SH_X3P_DMAC_TCR2			0xfcc08048
#define SH_X3P_DMAC_CHCR2			0xfcc0804C
#define SH_X3P_DMAC_SAR3			0xfcc08050
#define SH_X3P_DMAC_DAR3			0xfcc08054
#define SH_X3P_DMAC_TCR3			0xfcc08058
#define SH_X3P_DMAC_CHCR3			0xfcc0805C
#define SH_X3P_DMAC_DMAOR0			0xfcc08060
#define SH_X3P_DMAC_SAR4			0xfcc08070
#define SH_X3P_DMAC_DAR4			0xfcc08074
#define SH_X3P_DMAC_TCR4			0xfcc08078
#define SH_X3P_DMAC_CHCR4			0xfcc0807C
#define SH_X3P_DMAC_SAR5			0xfcc08080
#define SH_X3P_DMAC_DAR5			0xfcc08084
#define SH_X3P_DMAC_TCR5			0xfcc08088
#define SH_X3P_DMAC_CHCR5			0xfcc0808C
#define SH_X3P_DMAC_SARB0			0xfcc08120
#define SH_X3P_DMAC_DARB0			0xfcc08124
#define SH_X3P_DMAC_TCRB0			0xfcc08128
#define SH_X3P_DMAC_SARB1			0xfcc08130
#define SH_X3P_DMAC_DARB1			0xfcc08134
#define SH_X3P_DMAC_TCRB1			0xfcc08138
#define SH_X3P_DMAC_SARB2			0xfcc08140
#define SH_X3P_DMAC_DARB2			0xfcc08144
#define SH_X3P_DMAC_TCRB2			0xfcc08148
#define SH_X3P_DMAC_SARB3			0xfcc08150
#define SH_X3P_DMAC_DARB3			0xfcc08154
#define SH_X3P_DMAC_TCRB3			0xfcc08158
#define SH_X3P_DMAC_DMARS0			0xfcc09000
#define SH_X3P_DMAC_DMARS1			0xfcc09004
#define SH_X3P_DMAC_DMARS2			0xfcc09008
#define SH_X3P_DMAC_SAR6			0xfce08020
#define SH_X3P_DMAC_DAR6			0xfce08024
#define SH_X3P_DMAC_TCR6			0xfce08028
#define SH_X3P_DMAC_CHCR6			0xfce0802C
#define SH_X3P_DMAC_SAR7			0xfce08030
#define SH_X3P_DMAC_DAR7			0xfce08034
#define SH_X3P_DMAC_TCR7			0xfce08038
#define SH_X3P_DMAC_CHCR7			0xfce0803C
#define SH_X3P_DMAC_SAR8			0xfce08040
#define SH_X3P_DMAC_DAR8			0xfce08044
#define SH_X3P_DMAC_TCR8			0xfce08048
#define SH_X3P_DMAC_CHCR8			0xfce0804C
#define SH_X3P_DMAC_SAR9			0xfce08050
#define SH_X3P_DMAC_DAR9			0xfce08054
#define SH_X3P_DMAC_TCR9			0xfce08058
#define SH_X3P_DMAC_CHCR9			0xfce0805C
#define SH_X3P_DMAC_DMAOR1			0xfce08060
#define SH_X3P_DMAC_SAR10			0xfce08070
#define SH_X3P_DMAC_DAR10			0xfce08074
#define SH_X3P_DMAC_TCR10			0xfce08078
#define SH_X3P_DMAC_CHCR10			0xfce0807C
#define SH_X3P_DMAC_SAR11			0xfce08080
#define SH_X3P_DMAC_DAR11			0xfce08084
#define SH_X3P_DMAC_TCR11			0xfce08088
#define SH_X3P_DMAC_CHCR11			0xfce0808C
#define SH_X3P_DMAC_SARB6			0xfce08120
#define SH_X3P_DMAC_DARB6			0xfce08124
#define SH_X3P_DMAC_TCRB6			0xfce08128
#define SH_X3P_DMAC_SARB7			0xfce08130
#define SH_X3P_DMAC_DARB7			0xfce08134
#define SH_X3P_DMAC_TCRB7			0xfce08138
#define SH_X3P_DMAC_SARB8			0xfce08140
#define SH_X3P_DMAC_DARB8			0xfce08144
#define SH_X3P_DMAC_TCRB8			0xfce08148
#define SH_X3P_DMAC_SARB9			0xfce08150
#define SH_X3P_DMAC_DARB9			0xfce08154
#define SH_X3P_DMAC_TCRB9			0xfce08158
#define SH_X3P_DMAC_DMARS3			0xfce09000
#define SH_X3P_DMAC_DMARS4			0xfce09004
#define SH_X3P_DMAC_DMARS5			0xfce09008

/*
 * Clock Pulse Generator
 */
#define SH_X3P_CPG_FRQCR0			0xffc00000
#define SH_X3P_CPG_FRQCR1			0xffc00004
#define SH_X3P_CPG_FRQMR1			0xffc00014
#define SH_X3P_CPG_SLPCR			0xffc00020
#define SH_X3P_CPG_PLLCR			0xffc00024
#define SH_X3P_CPG_MSTPCR0			0xffc00030
#define SH_X3P_CPG_MSTPCR1			0xffc00030
#define SH_X3P_CPG_MSTPMR			0xffc00044
#define SH_X3P_CPG_C0IFC			0xfe400000
#define SH_X3P_CPG_C0STBCR			0xfe400004
#define SH_X3P_CPG_C1IFC			0xfe401000
#define SH_X3P_CPG_C1STBCR			0xfe401004
#define SH_X3P_CPG_C2IFC			0xfe402000
#define SH_X3P_CPG_C2STBCR			0xfe402004
#define SH_X3P_CPG_C3IFC			0xfe403000
#define SH_X3P_CPG_C3STBCR			0xfe403004


/*
 * Watchdog Timer and Reset
 */
#define SH_X3P_WDT_C0WDTST			0xfe400080
#define SH_X3P_WDT_C0WDTCSR			0xfe400084
#define SH_X3P_WDT_C0WDTBST			0xfe400088
#define SH_X3P_WDT_C0WDTCNT			0xfe400090
#define SH_X3P_WDT_C0WDTBCNT		0xfe400098
#define SH_X3P_WDT_C0RESETVEC		0xfe400008
#define SH_X3P_WDT_C1WDTST			0xfe401080
#define SH_X3P_WDT_C1WDTCSR			0xfe401084
#define SH_X3P_WDT_C1WDTBST			0xfe401088
#define SH_X3P_WDT_C1WDTCNT			0xfe401090
#define SH_X3P_WDT_C1WDTBCNT		0xfe401098
#define SH_X3P_WDT_C1RESETVEC		0xfe401008
#define SH_X3P_WDT_C2WDTST			0xfe402080
#define SH_X3P_WDT_C2WDTCSR			0xfe402084
#define SH_X3P_WDT_C2WDTBST			0xfe402088
#define SH_X3P_WDT_C2WDTCNT			0xfe402090
#define SH_X3P_WDT_C2WDTBCNT		0xfe402098
#define SH_X3P_WDT_C2RESETVEC		0xfe402008
#define SH_X3P_WDT_C3WDTST			0xfe403080
#define SH_X3P_WDT_C3WDTCSR			0xfe403084
#define SH_X3P_WDT_C3WDTBST			0xfe403088
#define SH_X3P_WDT_C3WDTCNT			0xfe403090
#define SH_X3P_WDT_C3WDTBCNT		0xfe403098
#define SH_X3P_WDT_C3RESETVEC		0xfe403008

/*
 * TMU
 */
#define SH_X3P_TMU_TSTR0			0xffc10004
#define SH_X3P_TMU_TCOR0			0xffc10008
#define SH_X3P_TMU_TCNT0			0xffc1000C
#define SH_X3P_TMU_TCR0				0xffc10010
#define SH_X3P_TMU_TCOR1			0xffc10014
#define SH_X3P_TMU_TCNT1			0xffc10018
#define SH_X3P_TMU_TCR1				0xffc1001C
#define SH_X3P_TMU_TCOR2			0xffc10020
#define SH_X3P_TMU_TCNT2			0xffc10024
#define SH_X3P_TMU_TCR2				0xffc10028
#define SH_X3P_TMU_TSTR1			0xffc20004
#define SH_X3P_TMU_TCOR3			0xffc20008
#define SH_X3P_TMU_TCNT3			0xffc2000C
#define SH_X3P_TMU_TCR3				0xffc20010
#define SH_X3P_TMU_TCOR4			0xffc20014
#define SH_X3P_TMU_TCNT4			0xffc20018
#define SH_X3P_TMU_TCR4				0xffc2001C
#define SH_X3P_TMU_TCOR5			0xffc20020
#define SH_X3P_TMU_TCNT5			0xffc20024
#define SH_X3P_TMU_TCR5				0xffc20028

/*
 * Display Unit
 */
#define SH_X3P_DU_DSYSR				0xffcc0000
#define SH_X3P_DU_DSMR				0xffcc0004
#define SH_X3P_DU_DSSR				0xffcc0008
#define SH_X3P_DU_DSRCR				0xffcc000C
#define SH_X3P_DU_DIER				0xffcc0010
#define SH_X3P_DU_CPCR				0xffcc0014
#define SH_X3P_DU_DPPR				0xffcc0018
#define SH_X3P_DU_DEFR				0xffcc0020
#define SH_X3P_DU_DAPCR				0xffcc0024
#define SH_X3P_DU_HDSR				0xffcc0040
#define SH_X3P_DU_HDER				0xffcc0044
#define SH_X3P_DU_VDSR				0xffcc0048
#define SH_X3P_DU_VDER				0xffcc004C
#define SH_X3P_DU_HCR				0xffcc0050
#define SH_X3P_DU_HSWR				0xffcc0054
#define SH_X3P_DU_VCR				0xffcc0058
#define SH_X3P_DU_VSPR				0xffcc005C
#define SH_X3P_DU_EQWR				0xffcc0060
#define SH_X3P_DU_SPWR				0xffcc0064
#define SH_X3P_DU_CLAMPSR			0xffcc0070
#define SH_X3P_DU_CLAMPWR			0xffcc0074
#define SH_X3P_DU_DESR				0xffcc0078
#define SH_X3P_DU_DEWR				0xffcc007C
#define SH_X3P_DU_CP1TR				0xffcc0080
#define SH_X3P_DU_CP2TR				0xffcc0084
#define SH_X3P_DU_CP3TR				0xffcc0088
#define SH_X3P_DU_CP4TR				0xffcc008C
#define SH_X3P_DU_CP5TR				0xffcc00A0
#define SH_X3P_DU_CP6TR				0xffcc00A4
#define SH_X3P_DU_DOOR				0xffcc0090
#define SH_X3P_DU_CDER				0xffcc0094
#define SH_X3P_DU_BPOR				0xffcc0098
#define SH_X3P_DU_RINTOFSR			0xffcc009C
#define SH_X3P_DU_P1MR				0xffcc0100
#define SH_X3P_DU_P1MWR				0xffcc0104
#define SH_X3P_DU_P1ALPHAR			0xffcc0108
#define SH_X3P_DU_P1DSXR			0xffcc0110
#define SH_X3P_DU_P1DSYR			0xffcc0114
#define SH_X3P_DU_P1DPXR			0xffcc0118
#define SH_X3P_DU_P1DPYR			0xffcc011C
#define SH_X3P_DU_P1DSA0R			0xffcc0120
#define SH_X3P_DU_P1DSA1R			0xffcc0124
#define SH_X3P_DU_P1DSA2R			0xffcc0128
#define SH_X3P_DU_P1SPXR			0xffcc0130
#define SH_X3P_DU_P1SPYR			0xffcc0134
#define SH_X3P_DU_P1WASPR			0xffcc0138
#define SH_X3P_DU_P1WAMWR			0xffcc013C
#define SH_X3P_DU_P1BTR				0xffcc0140
#define SH_X3P_DU_P1TC1R			0xffcc0144
#define SH_X3P_DU_P1TC2R			0xffcc0148
#define SH_X3P_DU_P1MLR				0xffcc0150
#define SH_X3P_DU_P2MR				0xffcc0200
#define SH_X3P_DU_P2MWR				0xffcc0204
#define SH_X3P_DU_P2ALPHAR			0xffcc0208
#define SH_X3P_DU_P2DSXR			0xffcc0210
#define SH_X3P_DU_P2DSYR			0xffcc0214
#define SH_X3P_DU_P2DPXR			0xffcc0218
#define SH_X3P_DU_P2DPYR			0xffcc021C
#define SH_X3P_DU_P2DSA0R			0xffcc0220
#define SH_X3P_DU_P2DSA1R			0xffcc0224
#define SH_X3P_DU_P2DSA2R			0xffcc0228
#define SH_X3P_DU_P2SPXR			0xffcc0230
#define SH_X3P_DU_P2SPYR			0xffcc0234
#define SH_X3P_DU_P2WASPR			0xffcc0238
#define SH_X3P_DU_P2WAMWR			0xffcc023C
#define SH_X3P_DU_P2BTR				0xffcc0240
#define SH_X3P_DU_P2TC1R			0xffcc0244
#define SH_X3P_DU_P2TC2R			0xffcc0248
#define SH_X3P_DU_P2MLR				0xffcc0250
#define SH_X3P_DU_P3MR				0xffcc0300
#define SH_X3P_DU_P3MWR				0xffcc0304
#define SH_X3P_DU_P3ALPHAR			0xffcc0308
#define SH_X3P_DU_P3DPXR			0xffcc0318
#define SH_X3P_DU_P3DPYR			0xffcc031C
#define SH_X3P_DU_P3DSA0R			0xffcc0320
#define SH_X3P_DU_P3DSA1R			0xffcc0324
#define SH_X3P_DU_P3DSA2R			0xffcc0328
#define SH_X3P_DU_P3SPXR			0xffcc0330
#define SH_X3P_DU_P3SPYR			0xffcc0334
#define SH_X3P_DU_P3WASPR			0xffcc0338
#define SH_X3P_DU_P3WAMWR			0xffcc033C
#define SH_X3P_DU_P3BTR				0xffcc0340
#define SH_X3P_DU_P3TC1R			0xffcc0344
#define SH_X3P_DU_P3TC2R			0xffcc0348
#define SH_X3P_DU_P3MLR				0xffcc0350
#define SH_X3P_DU_P4MR				0xffcc0400
#define SH_X3P_DU_P4MWR				0xffcc0404
#define SH_X3P_DU_P4ALPHAR			0xffcc0408
#define SH_X3P_DU_P4DSXR			0xffcc0410
#define SH_X3P_DU_P4DSYR			0xffcc0414
#define SH_X3P_DU_P4DPXR			0xffcc0418
#define SH_X3P_DU_P4DPYR			0xffcc041C
#define SH_X3P_DU_P4DSA0R			0xffcc0420
#define SH_X3P_DU_P4DSA1R			0xffcc0424
#define SH_X3P_DU_P4DSA2R			0xffcc0428
#define SH_X3P_DU_P4SPXR			0xffcc0430
#define SH_X3P_DU_P4SPYR			0xffcc0434
#define SH_X3P_DU_P4WASPR			0xffcc0438
#define SH_X3P_DU_P4WAMWR			0xffcc043C
#define SH_X3P_DU_P4BTR				0xffcc0440
#define SH_X3P_DU_P4TC1R			0xffcc0444
#define SH_X3P_DU_P4TC2R			0xffcc0448
#define SH_X3P_DU_P4MLR				0xffcc0450
#define SH_X3P_DU_P5MR				0xffcc0500
#define SH_X3P_DU_P5MWR				0xffcc0504
#define SH_X3P_DU_P5ALPHAR			0xffcc0508
#define SH_X3P_DU_P5DSXR			0xffcc0510
#define SH_X3P_DU_P5DSYR			0xffcc0514
#define SH_X3P_DU_P5DPXR			0xffcc0518
#define SH_X3P_DU_P5DPYR			0xffcc051C
#define SH_X3P_DU_P5DSA0R			0xffcc0520
#define SH_X3P_DU_P5DSA1R			0xffcc0524
#define SH_X3P_DU_P5DSA2R			0xffcc0528
#define SH_X3P_DU_P5SPXR			0xffcc0530
#define SH_X3P_DU_P5SPYR			0xffcc0534
#define SH_X3P_DU_P5WASPR			0xffcc0538
#define SH_X3P_DU_P5WAMWR			0xffcc053C
#define SH_X3P_DU_P5BTR				0xffcc0540
#define SH_X3P_DU_P5TC1R			0xffcc0544
#define SH_X3P_DU_P5TC2R			0xffcc0548
#define SH_X3P_DU_P5MLR				0xffcc0550
#define SH_X3P_DU_P6MR				0xffcc0600
#define SH_X3P_DU_P6MWR				0xffcc0604
#define SH_X3P_DU_P6ALPHAR			0xffcc0608
#define SH_X3P_DU_P6DSXR			0xffcc0610
#define SH_X3P_DU_P6DSYR			0xffcc0614
#define SH_X3P_DU_P6DPXR			0xffcc0618
#define SH_X3P_DU_P6DPYR			0xffcc061C
#define SH_X3P_DU_P6DSA0R			0xffcc0620
#define SH_X3P_DU_P6DSA1R			0xffcc0624
#define SH_X3P_DU_P6DSA2R			0xffcc0628
#define SH_X3P_DU_P6SPXR			0xffcc0630
#define SH_X3P_DU_P6SPYR			0xffcc0634
#define SH_X3P_DU_P6WASPR			0xffcc0638
#define SH_X3P_DU_P6WAMWR			0xffcc063C
#define SH_X3P_DU_P6BTR				0xffcc0640
#define SH_X3P_DU_P6TC1R			0xffcc0644
#define SH_X3P_DU_P6TC2R			0xffcc0648
#define SH_X3P_DU_P6MLR				0xffcc0650
#define SH_X3P_DU_P7MR				0xffcc0700
#define SH_X3P_DU_P7MWR				0xffcc0704
#define SH_X3P_DU_P7ALPHAR			0xffcc0708
#define SH_X3P_DU_P7DSXR			0xffcc0710
#define SH_X3P_DU_P7DSYR			0xffcc0714
#define SH_X3P_DU_P7DPXR			0xffcc0718
#define SH_X3P_DU_P7DPYR			0xffcc071C
#define SH_X3P_DU_P7DSA0R			0xffcc0720
#define SH_X3P_DU_P7DSA1R			0xffcc0724
#define SH_X3P_DU_P7DSA2R			0xffcc0728
#define SH_X3P_DU_P7SPXR			0xffcc0730
#define SH_X3P_DU_P7SPYR			0xffcc0734
#define SH_X3P_DU_P7WASPR			0xffcc0738
#define SH_X3P_DU_P7WAMWR			0xffcc073C
#define SH_X3P_DU_P7BTR				0xffcc0740
#define SH_X3P_DU_P7TC1R			0xffcc0744
#define SH_X3P_DU_P7TC2R			0xffcc0748
#define SH_X3P_DU_P7MLR				0xffcc0750
#define SH_X3P_DU_P8MR				0xffcc0800
#define SH_X3P_DU_P8MWR				0xffcc0804
#define SH_X3P_DU_P8ALPHAR			0xffcc0808
#define SH_X3P_DU_P8DSXR			0xffcc0810
#define SH_X3P_DU_P8DSYR			0xffcc0814
#define SH_X3P_DU_P8DPXR			0xffcc0818
#define SH_X3P_DU_P8DPYR			0xffcc081C
#define SH_X3P_DU_P8DSA0R			0xffcc0820
#define SH_X3P_DU_P8DSA1R			0xffcc0824
#define SH_X3P_DU_P8DSA2R			0xffcc0828
#define SH_X3P_DU_P8SPXR			0xffcc0830
#define SH_X3P_DU_P8SPYR			0xffcc0834
#define SH_X3P_DU_P8WASPR			0xffcc0838
#define SH_X3P_DU_P8WAMWR			0xffcc083C
#define SH_X3P_DU_P8BTR				0xffcc0840
#define SH_X3P_DU_P8TC1R			0xffcc0844
#define SH_X3P_DU_P8TC2R			0xffcc0848
#define SH_X3P_DU_P8MLR				0xffcc0850
#define SH_X3P_DU_AP1MR				0xffccA100
#define SH_X3P_DU_AP1MWR			0xffccA104
#define SH_X3P_DU_AP1ALPHAR			0xffccA108
#define SH_X3P_DU_AP1DSXR			0xffccA110
#define SH_X3P_DU_AP1DSYR			0xffccA114
#define SH_X3P_DU_AP1DPXR			0xffccA118
#define SH_X3P_DU_AP1DPYR			0xffccA11C
#define SH_X3P_DU_AP1DSA0R			0xffccA120
#define SH_X3P_DU_AP1DSA1R			0xffccA124
#define SH_X3P_DU_AP1DSA2R			0xffccA128
#define SH_X3P_DU_AP1SPXR			0xffccA130
#define SH_X3P_DU_AP1SPYR			0xffccA134
#define SH_X3P_DU_AP1WASPR			0xffccA138
#define SH_X3P_DU_AP1WAMWR			0xffccA13C
#define SH_X3P_DU_AP1BTR			0xffccA140
#define SH_X3P_DU_AP1MLR			0xffccA150
#define SH_X3P_DU_AP2MR				0xffccA200
#define SH_X3P_DU_AP2MWR			0xffccA204
#define SH_X3P_DU_AP2ALPHAR			0xffccA208
#define SH_X3P_DU_AP2DSXR			0xffccA210
#define SH_X3P_DU_AP2DSYR			0xffccA214
#define SH_X3P_DU_AP2DPXR			0xffccA218
#define SH_X3P_DU_AP2DPYR			0xffccA21C
#define SH_X3P_DU_AP2DSA0R			0xffccA220
#define SH_X3P_DU_AP2DSA1R			0xffccA224
#define SH_X3P_DU_AP2DSA2R			0xffccA228
#define SH_X3P_DU_AP2SPXR			0xffccA230
#define SH_X3P_DU_AP2SPYR			0xffccA234
#define SH_X3P_DU_AP2WASPR			0xffccA238
#define SH_X3P_DU_AP2WAMWR			0xffccA23C
#define SH_X3P_DU_AP2BTR			0xffccA240
#define SH_X3P_DU_AP2MLR			0xffccA250
#define SH_X3P_DU_CP1_000R			0xffcc1000
#define SH_X3P_DU_CP1_255R			0xffcc13FC
#define SH_X3P_DU_CP2_000R			0xffcc2000
#define SH_X3P_DU_CP2_255R			0xffcc23FC
#define SH_X3P_DU_CP3_000R			0xffcc3000
#define SH_X3P_DU_CP3_255R			0xffcc33FC
#define SH_X3P_DU_CP4_000R			0xffcc4000
#define SH_X3P_DU_CP4_255R			0xffcc43FC
#define SH_X3P_DU_CP5_000R			0xffcc5000
#define SH_X3P_DU_CP5_255R			0xffcc53FC
#define SH_X3P_DU_CP6_000R			0xffcc6000
#define SH_X3P_DU_CP6_255R			0xffcc63FC
#define SH_X3P_DU_ESCR				0xffcd0000
#define SH_X3P_DU_OTAR				0xffcd0004

/*
 * General Purpose I/O
 */
#define SH_X3P_GPIO_PABCR			0xffc70000
#define SH_X3P_GPIO_PCDCR			0xffc70004
#define SH_X3P_GPIO_PEFCR			0xffc70008
#define SH_X3P_GPIO_PGHCR			0xffc7000C
#define SH_X3P_GPIO_PABDR			0xffc70010
#define SH_X3P_GPIO_PCDDR			0xffc70014
#define SH_X3P_GPIO_PEFR			0xffc70018
#define SH_X3P_GPIO_PGHR			0xffc7001C
#define SH_X3P_GPIO_PPUCR1			0xffc70020
#define SH_X3P_GPIO_PPUCR2			0xffc70024
#define SH_X3P_GPIO_PINTREQ1		0xffc70098
#define SH_X3P_GPIO_PINTREQ2		0xffc7009C

#endif /* _SH_X3P_H_INCLUDED */

/* __SRCVERSION("sh_x3p.h $Rev$"); */
