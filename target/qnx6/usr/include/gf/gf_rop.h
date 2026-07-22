/* Copyright 2009, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to 
 * QNX Software Systems before you may reproduce, modify or distribute this 
 * software, or any work that includes all or part of this software.  Free 
 * development licenses are available for evaluation and non-commercial purposes.  
 * For more information visit http://licensing.qnx.com or email licensing@qnx.com.
 * 
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 */
#ifndef _GF_GF_ROP_H_INCLUDED
#define _GF_GF_ROP_H_INCLUDED

/*
 * Raster Op Defines
 *
 * Reverse Polish Notation Defines of ROPS
 * This follows Microsofts 256 raster operation
 * definitions
 *
 * D = Dest Bit
 * S = Source Bit
 * P = Pattern Bit
 * o = bitwise or operation
 * a = bitwise and operation
 * x = bitwise exclusive or operation
 * n = bitwise not operation
 *
 * Truth Table
 *	P	S	D	ropbit
 *	0	0	0	0
 *	0	0	1	1
 * 	0	1	0	2
 *	0	1	1	3
 *	1	0	0	4
 *	1	0	1	5
 *	1	1	0	6
 *	1	1	1	7
 *
 * if the condition in the table is true for 
 * each test turned on then dst bit=1, else 0
 *
 * So: GF_ROP CC =  Source Copy
 * 		if ((conditions 2 | 3 | 6 | 7) == 1) on current bits, dst bit=1, else 0
 *	   GF_ROP 66 = S ^ D
 *		if ((conditions 1 | 2 | 5 | 6) == 1) on current bits, dst bit=1, else 0
 *	   GF_ROP 03 = ~ (P | S)
 *      if ((conditions 0 | 1) == 1) on current bits, dst bit=1, else 0
 *
 * It's a little confusing at first, but it does make sense once you wrap
 * your brain around it.
 *
 *          Name                Rop #            Operation
 *--------------------------------------------------------------------------
 */
#define GF_ROP_ZERO				0x00	/* 0 */
#define GF_ROP_DPSoon			0x01	/* ~ ( (D | (P | S) ) ) */
#define GF_ROP_DPSona			0x02	/* D & ( ~ (P | S) ) */
#define GF_ROP_PSon				0x03	/* ~ (P | S) */
#define GF_ROP_SDPona			0x04	/* S & ( ~ (D | P) ) */
#define GF_ROP_DPon				0x05	/* ~ (D | P) */
#define GF_ROP_PDSxnon			0x06	/* ~ (P | (~ (D ^ S))) */
#define GF_ROP_PDSaon			0x07	/* ~ (P | (D & S)) */
#define GF_ROP_SDPnaa			0x08	/* S & (D & (~ P)) */
#define GF_ROP_PDSxon			0x09	/* ~ (P | (D ^ S)) */
#define GF_ROP_DPna				0x0A	/* D & (~ P) */
#define GF_ROP_PSDnaon			0x0B	/* ~ (P | (S & (~ D))) */
#define GF_ROP_SPna				0x0C	/* S & (~ P) */
#define GF_ROP_PDSnaon			0x0D	/* ~ (P | (D & (~ S))) */
#define GF_ROP_PDSonon			0x0E	/* ~ (P | (~(D | S))) */
#define GF_ROP_Pn				0x0F	/* ~ P */
#define GF_ROP_PDSona			0x10	/* P & (~ (D | S)) */
#define GF_ROP_DSon				0x11	/* ~ (D | S) */
#define GF_ROP_SDPxnon			0x12	/* ~ (S | (~ (D ^ P))) */
#define GF_ROP_SDPaon			0x13	/* ~ (S | (D & P)) */
#define GF_ROP_DPSxnon			0x14	/* ~ (D | (~ (P ^ S))) */
#define GF_ROP_DPSaon			0x15	/* ~ (D | (P & S)) */
#define GF_ROP_PSDPSanaxx		0x16	/* P ^ (S ^ (D & (~ (P & S)))) */
#define GF_ROP_SSPxDSxaxn		0x17	/* ~ (S ^ ((S ^ P) & (D ^ S))) */
#define GF_ROP_SPxPDxa			0x18	/* (S ^ P) & (P ^ D) */
#define GF_ROP_SDPSanaxn		0x19	/* ~ (S ^ (D & (~ (P & S)))) */
#define GF_ROP_PDSPaox			0x1A	/* P ^ (D | (S & P)) */
#define GF_ROP_SDPSxaxn			0x1B	/* ~ (S ^ (D & (P ^ S)))) */
#define GF_ROP_PSDPaox			0x1C	/* P ^ (S | (D & P))) */
#define GF_ROP_DSPDxaxn			0x1D	/* ~ (D ^ (S & (P ^ D))) */
#define GF_ROP_PDSox			0x1E	/* P ^ (D | S) */
#define GF_ROP_PDSoan			0x1F	/* ~ (P & (D | S)) */
#define GF_ROP_DPSnaa			0x20	/* D & (P & (~S)) */
#define GF_ROP_SDPxon			0x21	/* ~ (S | (D ^ P)) */
#define GF_ROP_DSna				0x22	/* D & (~S) */
#define GF_ROP_SPDnaon			0x23	/* ~ (S | (P & (~D))) */
#define GF_ROP_SPxDSxa			0x24	/* (S ^ P) & (D ^ S) */
#define GF_ROP_PDSPanaxn		0x25	/* ~ (P ^ (D & (~ (S & P)))) */
#define GF_ROP_SDPSaox			0x26	/* S ^ (D | (P & S)) */
#define GF_ROP_SDPSxnox			0x27	/* S ^ (D | (~ (P ^ S))) */
#define GF_ROP_DPSxa			0x28	/* D & (P ^ S) */
#define GF_ROP_PSDPSaoxxn		0x29	/* ~ (P ^ (S ^ (D | (P & S)))) */
#define GF_ROP_DPSana			0x2A	/* D & (~ (P & S)) */
#define GF_ROP_SSPxPDxaxn		0x2B	/* ~ (S ^ ((S ^ P) & (P ^ D)) */
#define GF_ROP_SPDSoax			0x2C	/* S ^ (P & (D | S)) */
#define GF_ROP_PSDnox			0x2D	/* P ^ (S | (~D)) */
#define GF_ROP_PSDPxox			0x2E	/* P ^ (S | (D ^ P)) */
#define GF_ROP_PSDnoan			0x2F	/* ~ (P & (S | (~D))) */
#define GF_ROP_PSna				0x30	/* P & (~ S) */
#define GF_ROP_SDPnaon			0x31	/* ~ (S | (D & (~P))) */
#define GF_ROP_SDPSoox			0x32	/* S ^ (D | (P | S)) */
#define GF_ROP_Sn				0x33	/* ~S */
#define GF_ROP_SPDSaox			0x34	/* S ^ (P | (D & S)) */
#define GF_ROP_SPDSxnox			0x35	/* S ^ (P | (~ (D ^ S))) */
#define GF_ROP_SDPox			0x36	/* S ^ (D | P) */
#define GF_ROP_SDPoan			0x37	/* ~ (S & (D | P)) */
#define GF_ROP_PSDPoax			0x38	/* P ^ (S & (D | P))) */
#define GF_ROP_SPDnox			0x39	/* S ^ (P | (~ D))) */
#define GF_ROP_SPDSxox			0x3A	/* S ^ (P | (D ^ S)) */
#define GF_ROP_SPDnoan			0x3B	/* ~ (S & (P | (~ D))) */
#define GF_ROP_PSx				0x3C	/* P ^ S */
#define GF_ROP_SPDSonox			0x3D	/* S ^ (P | (~ (D | S))) */
#define GF_ROP_SPDSnaox			0x3E	/* S ^ (P | (D & (~ S))) */
#define GF_ROP_PSan				0x3F	/* ~ (P & S) */
#define GF_ROP_PSDnaa			0x40	/* P & (S & (~ D)) */
#define GF_ROP_DPSxon			0x41	/* ~ (D | (P ^ S) */
#define GF_ROP_SDxPDxa			0x42	/* (S ^ D) & (P ^ D) */
#define GF_ROP_SPDSanaxn		0x43	/* ~ (S ^ (P & (~ (D & S)))) */
#define GF_ROP_SDna				0x44	/* S & (~ D) */
#define GF_ROP_DPSnaon			0x45	/* ~ (D | (P & (~ S))) */
#define GF_ROP_DSPDaox			0x46	/* D ^ (S | (P & D))) */
#define GF_ROP_PSDPxaxn			0x47	/* ~ (P ^ (S & (D ^ P))) */
#define GF_ROP_SDPxa			0x48	/* S & (D ^ P)) */
#define GF_ROP_PDSPDoaxxn		0x49	/* ~ (P ^ (D ^ (S & (P | D)))) */
#define GF_ROP_DPSDoax			0x4A	/* D ^ (P & (S | D)) */
#define GF_ROP_PDSnox			0x4B	/* P ^ (D | (~ S)) */
#define GF_ROP_SDPana			0x4C	/* S & (~ (D & P)) */
#define GF_ROP_SSPxDSxoxn		0x4D	/* ~ (S ^ ((S ^ P) | (D ^ S))) */
#define GF_ROP_PDSPxox			0x4E	/* P ^ (D | (S ^ P)) */
#define GF_ROP_PDSnoan			0x4F	/* ~ (P & (D | (~S))) */
#define GF_ROP_PDna				0x50	/* (~ D) & P */
#define GF_ROP_DSPnaon			0x51	/* ~ (D | (S & (~P))) */
#define GF_ROP_DPSDaox			0x52	/* D ^ (P | (S & D)) */
#define GF_ROP_SPDSxaxn			0x53	/* ~ (S ^ (P & (D ^ S))) */
#define GF_ROP_DPSonon			0x54	/* ~ (D | (~ (P | S))) */
#define GF_ROP_Dn				0x55	/* ~ D */
#define GF_ROP_DPSox			0x56	/* D ^ (P | S) */
#define GF_ROP_DPSoan			0x57	/* ~ (D & (P | S)) */
#define GF_ROP_PDSPoax			0x58	/* P ^ (D & (S | P)) */
#define GF_ROP_DPSnox			0x59	/* D ^ (P | (~ S)) */
#define GF_ROP_DPx				0x5A	/* D ^ P */
#define GF_ROP_DPSDonox			0x5B	/* D ^ (P | (~ (S | D))) */
#define GF_ROP_DPSDxox			0x5C	/* D ^ (P | (S ^ D)) */
#define GF_ROP_DPSnoan			0x5D	/* ~ (D & (P | (~ S))) */
#define GF_ROP_DPSDnaox			0x5E	/* D ^ (P | (S & (~ D))) */
#define GF_ROP_DPan				0x5F	/* ~ (D & P) */
#define GF_ROP_PDSxa			0x60	/* P & (D ^ S) */
#define GF_ROP_DSPDSaoxxn		0x61	/* ~ (D ^ (S ^ (P | (D & S)))) */
#define GF_ROP_DSPDoax			0x62	/* D ^ (S & (P | D)) */
#define GF_ROP_SDPnox			0x63	/* S ^ (D | (~ P)) */
#define GF_ROP_SDPSoax			0x64	/* S ^ (D & (P | S)) */
#define GF_ROP_DSPnox			0x65	/* D ^ (S | (~ P)) */
#define GF_ROP_DSx				0x66	/* D ^ S */
#define GF_ROP_SDPSonox			0x67	/* S ^ (D | (~ (P | S))) */
#define GF_ROP_DSPDSonoxxn		0x68	/* ~ (D ^ (S ^ (P | (~ (D | S))))) */
#define GF_ROP_PDSxxn			0x69	/* ~ (P ^ (D ^ S)) */
#define GF_ROP_DPSax			0x6A	/* D ^ (P & S) */
#define GF_ROP_PSDPSoaxxn		0x6B	/* ~ (P ^ (S ^ (D & (P | S)))) */
#define GF_ROP_SDPax			0x6C	/* S ^ (D & P) */
#define GF_ROP_PDSPDoaxx		0x6D	/* P ^ (D ^ (S & (P | D))) */
#define GF_ROP_SDPSnoax			0x6E	/* S ^ (D & (P | (~ S))) */
#define GF_ROP_PDSxnan			0x6F	/* ~ (P & (~ (D ^ S))) */
#define GF_ROP_PDSana			0x70	/* P & (~ (D & S)) */
#define GF_ROP_SSDxPDxaxn		0x71	/* ~ (S ^ ((S ^ D) & (P ^ D))) */
#define GF_ROP_SDPSxox			0x72	/* S ^ (D | (P ^ S)) */
#define GF_ROP_SDPnoan			0x73	/* ~ (S & (D | (~P))) */
#define GF_ROP_DSPDxox			0x74	/* D ^ (S | (P ^ D)) */
#define GF_ROP_DSPnoan			0x75	/* ~ (D & (S | (~ P))) */
#define GF_ROP_SDPSnaox			0x76	/* S ^ (D | (P & (~ S))) */
#define GF_ROP_DSan				0x77	/* ~ (D & S) */
#define GF_ROP_PDSax			0x78	/* P ^ (D & S) */
#define GF_ROP_DSPDSoaxxn		0x79	/* ~ (D ^ (S ^ (P & (D | S)))) */
#define GF_ROP_DPSDnoax			0x7A	/* D ^ (P & (S | (~ D))) */
#define GF_ROP_SDPxnan			0x7B	/* ~ (S & (~ (D ^ P))) */
#define GF_ROP_SPDSnoax			0x7C	/* S ^ (P & (D | (~ S))) */
#define GF_ROP_DPSxnan			0x7D	/* ~ (D & (~ (P ^ S))) */
#define GF_ROP_SPxDSxo			0x7E	/* (S ^ P) | (D ^ S) */
#define GF_ROP_DPSaan			0x7F	/* ~ (D & (P & S)) */
#define GF_ROP_DPSaa			0x80	/* D & (P & S) */
#define GF_ROP_SPxDSxon			0x81	/* ~ ((P ^ S) | (D ^ S)) */
#define GF_ROP_DPSxna			0x82	/* D & (~ (P ^ S)) */
#define GF_ROP_SPDSnoaxn		0x83	/* ~ (S ^ (P & (D | (~ S)))) */
#define GF_ROP_SDPxna			0x84	/* S & (~ (D ^ P)) */
#define GF_ROP_PDSPnoaxn		0x85	/* ~ (P ^ (D & (S | (~ P)))) */
#define GF_ROP_DSPDSoaxx		0x86	/* D ^ (S ^ (P & (D | S))) */
#define GF_ROP_PDSaxn			0x87	/* ~ (P ^ (D & S)) */
#define GF_ROP_DSa				0x88	/* D & S */
#define GF_ROP_SDPSnaoxn		0x89	/* ~ (S ^ (D | (P & (~ S)))) */
#define GF_ROP_DSPnoa			0x8A	/* D & (S | (~ P)) */
#define GF_ROP_DSPSxoxn			0x8B	/* ~ (D ^ (S | (P ^ S))) */
#define GF_ROP_SDPnoa			0x8C	/* S & (D | (~ P)) */
#define GF_ROP_SDPSxoxn			0x8D	/* ~ (S ^ (D | (P ^ S))) */
#define GF_ROP_SSDxPDxax		0x8E	/* S ^ ((S ^ D) & (P ^ D)) */
#define GF_ROP_PDSanan			0x8F	/* ~ (P & (~ (D & S))) */
#define GF_ROP_PDSxna			0x90	/* P & (~ (D ^ S)) */
#define GF_ROP_SDPSnoaxn		0x91	/* ~ (S ^ (D & (P | (~ S)))) */
#define GF_ROP_DPSDPoaxx		0x92	/* D ^ (P ^ (S & (D | P))) */
#define GF_ROP_SPDaxn			0x93	/* ~ (S ^ (P & D)) */
#define GF_ROP_PSDPSoaxx		0x94	/* P ^ (S ^ (D & (P | S))) */
#define GF_ROP_DPSaxn			0x95	/* ~ (D ^ (P & S)) */
#define GF_ROP_DPSxx			0x96	/* D ^ (P ^ S) */
#define GF_ROP_PSDPSonoxx		0x97	/* P ^ (S ^ (D | (~ (P | S)))) */
#define GF_ROP_SDPSonoxn		0x98	/* ~ (S ^ (D | (~ (P | S)))) */
#define GF_ROP_DSxn				0x99	/* ~ (D ^ S) */
#define GF_ROP_DPSnax			0x9A	/* D ^ (P & (~ S)) */
#define GF_ROP_SDPSoaxn			0x9B	/* ~ (S ^ (D & (P | S))) */
#define GF_ROP_SPDnax			0x9C	/* S ^ (P & (~ D)) */
#define GF_ROP_DSPDoaxn			0x9D	/* ~ (D ^ (S & (P | D))) */
#define GF_ROP_DSPDSaoxx		0x9E	/* D ^ (S ^ (P | (D & S))) */
#define GF_ROP_PDSxan			0x9F	/* ~ (P & (D ^ S)) */
#define GF_ROP_DPa				0xA0	/* (D & P) */
#define GF_ROP_PDSPnaoxn		0xA1	/* ~ (P ^ (D | (S & (~ P)))) */
#define GF_ROP_DPSnoa			0xA2	/* D & (P | (~ S)) */
#define GF_ROP_DPSDxoxn			0xA3	/* ~ (D ^ (P | (S ^ D))) */
#define GF_ROP_PDSPonoxn		0xA4	/* ~ (P ^ (D | (~ (S | P)))) */
#define GF_ROP_PDxn				0xA5	/* ~ (P ^ D) */
#define GF_ROP_DSPnax			0xA6	/* D ^ (S & (~ P)) */
#define GF_ROP_PDSPoaxn			0xA7	/* ~ (P ^ (D & (S | P))) */
#define GF_ROP_DPSoa			0xA8	/* D & (P | S) */
#define GF_ROP_DPSoxn			0xA9	/* ~ (D ^ (P | S)) */
#define GF_ROP_D				0xAA	/* D */
#define GF_ROP_DPSono			0xAB	/* D | (~ (P | S)) */
#define GF_ROP_SPDSxax			0xAC	/* S ^ (P & (D ^ S)) */
#define GF_ROP_DPSDaoxn			0xAD	/* ~ (D ^ (P | (S & D))) */
#define GF_ROP_DSPnao			0xAE	/* D | (S & (~ P)) */
#define GF_ROP_DPno				0xAF	/* D | (~ P) */
#define GF_ROP_PDSnoa			0xB0	/* P & (D | (~ S)) */
#define GF_ROP_PDSPxoxn			0xB1	/* ~ (P ^ (D | (S ^ P))) */
#define GF_ROP_SSPxDSxox		0xB2	/* S ^ ((S ^ P) | (D ^ S)) */
#define GF_ROP_SDPanan			0xB3	/* ~ (S & (~ (D & P))) */
#define GF_ROP_PSDnax			0xB4	/* P ^ (S & (~ D)) */
#define GF_ROP_DPSDoaxn			0xB5	/* ~ (D ^ (P & (S | D))) */
#define GF_ROP_DPSDPaoxx		0xB6	/* D ^ (P ^ (S | (D & P))) */
#define GF_ROP_SDPxan			0xB7	/* ~ (S & (D ^ P)) */
#define GF_ROP_PSDPxax			0xB8	/* P ^ (S & (D ^ P)) */
#define GF_ROP_DSPDaoxn			0xB9	/* ~ (D ^ (S | (P & D))) */
#define GF_ROP_DPSnao			0xBA	/* D | (P & (~ S)) */
#define GF_ROP_DSno				0xBB	/* D | (~ S) */
#define GF_ROP_SPDSanax			0xBC	/* S ^ (P & (~ (D & S))) */
#define GF_ROP_SDxPDxan			0xBD	/* ~ ((S ^ D) & (P ^ D)) */
#define GF_ROP_DPSxo			0xBE	/* D | (P ^ S) */
#define GF_ROP_DPSano			0xBF	/* D | (~ (P & S)) */
#define GF_ROP_PSa				0xC0	/* P & S */
#define GF_ROP_SPDSnaoxn		0xC1	/* ~ (S ^ (P | (D & (~ S)))) */
#define GF_ROP_SPDSonoxn		0xC2	/* ~ (S ^ (P | (~ (D | S)))) */
#define GF_ROP_PSxn				0xC3	/* ~ (P ^ S) */
#define GF_ROP_SPDnoa			0xC4	/* S & (P | (~ D)) */
#define GF_ROP_SPDSxoxn			0xC5	/* ~ (S ^ (P | (D ^ S))) */
#define GF_ROP_SDPnax			0xC6	/* S ^ (D & (~ P)) */
#define GF_ROP_PSDPoaxn			0xC7	/* ~ (P ^ (S & (D | P))) */
#define GF_ROP_SDPoa			0xC8	/* S & (D | P) */
#define GF_ROP_SPDoxn			0xC9	/* ~ (S ^ (P | D)) */
#define GF_ROP_DPSDxax			0xCA	/* D ^ (P & (S ^ D)) */
#define GF_ROP_SPDSaoxn			0xCB	/* ~ (S ^ (P | (D & S))) */
#define GF_ROP_S				0xCC	/* S */
#define GF_ROP_SDPono			0xCD	/* S | (~ (D | P)) */
#define GF_ROP_SDPnao			0xCE	/* S | (D & (~ P)) */
#define GF_ROP_SPno				0xCF	/* S | (~ P) */
#define GF_ROP_PSDnoa			0xD0	/* P & (S | (~ D)) */
#define GF_ROP_PSDPxoxn			0xD1	/* ~ (P ^ (S | (D ^ P))) */
#define GF_ROP_PDSnax			0xD2	/* P ^ (D & (~ S)) */
#define GF_ROP_SPDSoaxn			0xD3	/* ~ (S ^ (P & (D | S))) */
#define GF_ROP_SSPxPDxax		0xD4	/* S ^ ((S ^ P) & (P ^ D)) */
#define GF_ROP_DPSanan			0xD5	/* ~ (D & (~ (P & S))) */
#define GF_ROP_PSDPSaoxx		0xD6	/* P ^ (S ^ (D | (P & S))) */
#define GF_ROP_DPSxan			0xD7	/* ~ (D & (P ^ S)) */
#define GF_ROP_PDSPxax			0xD8	/* P ^ (D & (S ^ P)) */
#define GF_ROP_SDPSaoxn			0xD9	/* ~ (S ^ (D | (P & S))) */
#define GF_ROP_DPSDanax			0xDA	/* D ^ (P & (~ (S & D))) */
#define GF_ROP_SPxDSxan			0xDB	/* ~ ((S ^ P) & (D ^ S)) */
#define GF_ROP_SPDnao			0xDC	/* S | (P & (~ D)) */
#define GF_ROP_SDno				0xDD	/* S | (~ D) */
#define GF_ROP_SDPxo			0xDE	/* S | (D ^ P) */
#define GF_ROP_SDPano			0xDF	/* S | (~ (D & P)) */
#define GF_ROP_PDSoa			0xE0	/* P & (D | S) */
#define GF_ROP_PDSoxn			0xE1	/* ~ (P ^ (D | S)) */
#define GF_ROP_DSPDxax			0xE2	/* D ^ (S & (P ^ D)) */
#define GF_ROP_PSDPaoxn			0xE3	/* ~ (P ^ (S | (D & P))) */
#define GF_ROP_SDPSxax			0xE4	/* S ^ (S & (P ^ S)) */
#define GF_ROP_PDSPaoxn			0xE5	/* ~ (P ^ (D | (S & P))) */
#define GF_ROP_SDPSanax			0xE6	/* S ^ (D & (~ (P & S))) */
#define GF_ROP_SPxDPxan			0xE7	/* ~ ((S ^ P) & (D ^ P)) */
#define GF_ROP_SSPxDSxax		0xE8	/* S ^ ((S ^ P) & (D ^ S)) */
#define GF_ROP_DSPDSanaxxn		0xE9	/* ~ (D ^ (S ^ (P & (~ (D & S))))) */
#define GF_ROP_DPSao			0xEA	/* D | (P & S) */
#define GF_ROP_DPSxno			0xEB	/* D | (~ (P ^ S)) */
#define GF_ROP_SDPao			0xEC	/* S | (D & P) */
#define GF_ROP_SDPxno			0xED	/* S | (~ (D ^ P)) */
#define GF_ROP_DSo				0xEE	/* D | S */
#define GF_ROP_SDPnoo			0xEF	/* S | (D | (~ P)) */
#define GF_ROP_P				0xF0	/* P */
#define GF_ROP_PDSono			0xF1	/* P | (~ (D | S)) */
#define GF_ROP_PDSnao			0xF2	/* P | (D & (~ S)) */
#define GF_ROP_PSno				0xF3	/* P | (~ S) */
#define GF_ROP_PSDnao			0xF4	/* P | (S & (~ D)) */
#define GF_ROP_PDno				0xF5	/* P | (~ D) */
#define GF_ROP_PDSxo			0xF6	/* P | (D ^ S) */
#define GF_ROP_PDSano			0xF7	/* P | (~ (D & S)) */
#define GF_ROP_PDSao			0xF8	/* P | (D & S) */
#define GF_ROP_PDSxno			0xF9	/* P | (~ (D ^ S)) */
#define GF_ROP_DPo				0xFA	/* D | P */
#define GF_ROP_DPSnoo			0xFB	/* D | (P | (~ S)) */
#define GF_ROP_PSo				0xFC	/* P | S */
#define GF_ROP_PSDnoo			0xFD	/* P | (S | (~ D)) */
#define GF_ROP_DPSoo			0xFE	/* D | (P | S) */
#define GF_ROP_ONE				0xFF	/* 1 */

/* Convenience Defines */
#define GF_ROP_BLACK			GF_ROP_ZERO
#define GF_ROP_WHITE			GF_ROP_ONE

#define GF_ROP_SRCCOPY			GF_ROP_S
#define GF_ROP_SRCINVERT		GF_ROP_Sn

#define GF_ROP_PATCOPY			GF_ROP_P
#define GF_ROP_PATINVERT		GF_ROP_Pn

#define GF_ROP_NOP				GF_ROP_D
#define GF_ROP_DSTINVERT		GF_ROP_Dn

#define GF_ROP_SRCXOR			GF_ROP_DSx
#define GF_ROP_PATXOR			GF_ROP_DPx
#define GF_ROP_SRCAND			GF_ROP_DSa
#define GF_ROP_PATAND			GF_ROP_DPa
#define GF_ROP_SRCOR			GF_ROP_DSo
#define GF_ROP_PATOR			GF_ROP_DPo

/* Simple ROP defines */
#define GF_ROP_Opaque			GF_ROP_SRCCOPY
#define GF_ROP_XOR				GF_ROP_SRCXOR
#define GF_ROP_AND				GF_ROP_SRCAND
#define GF_ROP_OR				GF_ROP_SRCOR

/* Defines for interpreting ternary Raster OPs (ROP3) */
#define GF_ROP_NO_PATTERN(__rop)	(((__rop) & 0xf) == \
					    (((__rop) >> 4) & 0xf))
#define GF_ROP_NO_SOURCE(__rop)	(((__rop) & 0x33) == \
					    (((__rop) >> 2) & 0x33))
#define GF_ROP_NO_DEST(__rop)		(((__rop) & 0x55) == \
					    (((__rop) >> 1) & 0x55))

/* Rastor op conversion macros */
#define GF_ROP_SRC_TO_PAT(__rop)	(((__rop) & 0xc0) | 		\
					    ((__rop) & 0xc) << 2 |	\
					    ((__rop) & 0x30) >> 2 |	\
					    ((__rop) & 0x3))
#define GF_ROP_PAT_TO_SRC(__rop)	(((__rop) & 0xc0) |		\
					    ((__rop) & 0x30) >> 2 |	\
					    ((__rop) & 0xc) << 2 |	\
					    ((__rop) & 0x3))

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/gf/public/gf/gf_rop.h $ $Rev: 244324 $" )
#endif
#endif /* _GF_GF_ROP_H_INCLUDED */

