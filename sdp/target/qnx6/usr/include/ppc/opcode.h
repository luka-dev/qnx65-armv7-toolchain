/*
 * $QNXLicenseC:
 * Copyright 2007, 2009, QNX Software Systems. All Rights Reserved.
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

#ifndef __PPC_OPCODE_H_INCLUDED
#define __PPC_OPCODE_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef __PPC_CONTEXT_H_INCLUDED
#include _NTO_HDR_(ppc/context.h)
#endif

/* PPC instruction */
#if defined(__LITTLEENDIAN__ )

	union ppc_instr {
		unsigned int op_code;

		struct {
			unsigned kk : 1;
			unsigned aa : 1;
			unsigned li : 24;
			unsigned op : 6;
		} i_t;

		struct {
			unsigned kk : 1;
			unsigned aa : 1;
			unsigned bd : 14;
			unsigned bi : 5;
			unsigned bo : 5;
			unsigned op : 6;
		} b_t;

		struct {
			unsigned res1:1;
			unsigned aa : 1;
			unsigned res: 19;
			unsigned rt : 5;
			unsigned op : 6;
		} sc_t;

		struct {
			signed 	 d	: 16;
			unsigned a  : 5;
			unsigned ds : 5;
			unsigned op : 6;
		} d_t;

		struct {
			unsigned rc : 1;
			unsigned xo : 10;
			unsigned b	: 5;
			unsigned a	: 5;
			unsigned ds : 5;
			unsigned op : 6;
		} x_t;

		struct {
			unsigned lk : 1;
			unsigned xo : 10;
			unsigned b	: 5;
			unsigned bi_a: 5;
			unsigned bo_d: 5;
			unsigned op : 6;
		} xl_t;

		struct {
			unsigned res: 1;
			unsigned xo : 10;
			unsigned spr: 10;
			unsigned ds	: 5;
			unsigned op	: 6;
		} xfx_t;

		struct {
			unsigned rc : 1;
			unsigned xo : 10;
			unsigned b	: 5;
			unsigned res1: 1;
			unsigned fm	: 8;
			unsigned res: 1;
			unsigned op	: 6;
		} xfl_t;

		struct {
			unsigned rc : 1;
			unsigned xo : 9;
			unsigned oe : 1;
			unsigned b	: 5;
			unsigned a	: 5;
			unsigned d	: 5;
			unsigned op : 6;
		} xo_t;

		struct {
			unsigned rc : 1;
			unsigned xo : 5;
			unsigned c	: 5;
			unsigned b	: 5;
			unsigned a	: 5;
			unsigned d	: 5;
			unsigned op : 6;
		} a_t;

		struct {
			unsigned rc : 1;
			unsigned me : 5;
			unsigned mb	: 5;
			unsigned b	: 5;
			unsigned a	: 5;
			unsigned s	: 5;
			unsigned op : 6;
		} m_t;

		struct {
			unsigned xo : 11;
			unsigned b	: 5;
			unsigned a	: 5;
			unsigned t	: 5;
			unsigned op : 6;
		} evx_t;

		struct {
			unsigned xo : 11;
			unsigned b	: 5;
			unsigned a	: 5;
			unsigned 	: 2;
			unsigned bf	: 3;
			unsigned op : 6;
		} evx_bf_t;

	};

#else /* __BIGENDIAN__ */

	union ppc_instr {
		unsigned int op_code;

		struct {
			unsigned op : 6;
			unsigned li : 24;
			unsigned aa : 1;
			unsigned kk : 1;
		} i_t;

		struct {
			unsigned op : 6;
			unsigned bo : 5;
			unsigned bi : 5;
			unsigned bd : 14;
			unsigned aa : 1;
			unsigned kk : 1;
		} b_t;

		struct {
			unsigned op : 6;
			unsigned rt : 5;
			unsigned res: 19;
			unsigned aa : 1;
			unsigned res1:1;
		} sc_t;

		struct {
			unsigned op : 6;
			unsigned ds : 5;
			unsigned a  : 5;
			signed 	 d	: 16;
		} d_t;

		struct {
			unsigned op : 6;
			unsigned ds : 5;
			unsigned a	: 5;
			unsigned b	: 5;
			unsigned xo : 10;
			unsigned rc : 1;
		} x_t;

		struct {
			unsigned op : 6;
			unsigned bo_d: 5;
			unsigned bi_a: 5;
			unsigned b	: 5;
			unsigned xo : 10;
			unsigned lk : 1;
		} xl_t;

		struct {
			unsigned op	: 6;
			unsigned ds	: 5;
			unsigned spr: 10;
			unsigned xo : 10;
		} xfx_t;

		struct {
			unsigned op	: 6;
			unsigned res: 1;
			unsigned fm	: 8;
			unsigned res1: 1;
			unsigned b	: 5;
			unsigned xo : 10;
			unsigned rc : 1;
		} xfl_t;

		struct {
			unsigned op : 6;
			unsigned d	: 5;
			unsigned a	: 5;
			unsigned b	: 5;
			unsigned oe : 1;
			unsigned xo : 9;
			unsigned rc : 1;
		} xo_t;

		struct {
			unsigned op : 6;
			unsigned d	: 5;
			unsigned a	: 5;
			unsigned b	: 5;
			unsigned c	: 5;
			unsigned xo : 5;
			unsigned rc : 1;
		} a_t;

		struct {
			unsigned op : 6;
			unsigned s	: 5;
			unsigned a	: 5;
			unsigned b	: 5;
			unsigned mb	: 5;
			unsigned me : 5;
			unsigned rc : 1;
		} m_t;

		struct {
			unsigned op : 6;
			unsigned t	: 5;
			unsigned a	: 5;
			unsigned b	: 5;
			unsigned xo : 11;
		} evx_t;

		struct {
			unsigned op : 6;
			unsigned bf	: 3;
			unsigned 	: 2;
			unsigned a	: 5;
			unsigned b	: 5;
			unsigned xo : 11;
		} evx_bf_t;

	};

#endif

/* PPC instructions opcodes */
#define	PPCOPCODE_BC		16
#define	PPCOPCODE_B			18
#define	PPCOPCODE_LBZ		34
#define	PPCOPCODE_LBZU		35
#define	PPCOPCODE_LFD		50
#define	PPCOPCODE_LFDU		51
#define	PPCOPCODE_LFS		48
#define	PPCOPCODE_LFSU		49
#define	PPCOPCODE_LMW		46
#define	PPCOPCODE_LHA		42
#define	PPCOPCODE_LHAU		43
#define	PPCOPCODE_LHZ		40
#define	PPCOPCODE_LHZU		41
#define	PPCOPCODE_LWZ		32
#define	PPCOPCODE_LWZU		33
#define	PPCOPCODE_STB		38
#define	PPCOPCODE_STBU		39
#define	PPCOPCODE_STFD		54
#define	PPCOPCODE_STFDU		55
#define	PPCOPCODE_STFS		52
#define	PPCOPCODE_STFSU		53
#define	PPCOPCODE_STMW		47
#define	PPCOPCODE_STH		44
#define	PPCOPCODE_STHU		45
#define	PPCOPCODE_STW		36
#define	PPCOPCODE_STWU		37

#define	PPCOPCODE_XLFORM	19
#define	PPCOPCODE_XFORM		31
#define	PPCOPCODE_EVXFORM	4

#define PPCOPCODE_LSUPDATE_MASK	0x1

/* PPC instructions XO code */
#define	PPCXOCODE_MFTB		371
#define	PPCXOCODE_MFSPR		339
#define	PPCXOCODE_LFDX		599
#define	PPCXOCODE_LFDUX		631
#define	PPCXOCODE_LFSX		535
#define	PPCXOCODE_LFSUX		567
#define	PPCXOCODE_LHAX		343
#define	PPCXOCODE_LHAUX		375
#define	PPCXOCODE_LHBRX		790
#define	PPCXOCODE_LHZX		279
#define	PPCXOCODE_LHZUX		311
#define	PPCXOCODE_LSWI		597
#define	PPCXOCODE_LSWX		533
#define	PPCXOCODE_LWBRX		534
#define	PPCXOCODE_LWZX		23
#define	PPCXOCODE_LWZUX		55
#define	PPCXOCODE_STFDX		727
#define	PPCXOCODE_STFDUX	759
#define	PPCXOCODE_STFSX		663
#define	PPCXOCODE_STFSUX	695
#define	PPCXOCODE_STHBRX	918
#define	PPCXOCODE_STHX		407
#define	PPCXOCODE_STHUX		439
#define	PPCXOCODE_STSWI		725
#define	PPCXOCODE_STSWX		661
#define	PPCXOCODE_STWBRX	662
#define	PPCXOCODE_STWX		151
#define	PPCXOCODE_STWUX		183
#define	PPCXOCODE_DCBZ		1014

#define	PPCXOCODE_BCLR		16
#define	PPCXOCODE_BCCTR		528

#define PPCXOCODE_LSUPDATE_MASK	0x20

#define PPCXOCODE_EVLDD				769
#define PPCXOCODE_EVLDDX			768
#define PPCXOCODE_EVLDH				773
#define PPCXOCODE_EVLDHX			772
#define PPCXOCODE_EVLDW				771
#define PPCXOCODE_EVLDWX			770
#define PPCXOCODE_EVLHHESPLAT		777
#define PPCXOCODE_EVLHHESPLATX		776
#define PPCXOCODE_EVLHHOSSPLAT		783
#define PPCXOCODE_EVLHHOSSPLATX		782
#define PPCXOCODE_EVLHHOUSPLAT		781
#define PPCXOCODE_EVLHHOUSPLATX		780
#define PPCXOCODE_EVLWHE			785
#define PPCXOCODE_EVLWHEX			784
#define PPCXOCODE_EVLWHOS			791
#define PPCXOCODE_EVLWHOSX			790
#define PPCXOCODE_EVLWHOU			789
#define PPCXOCODE_EVLWHOUX			788
#define PPCXOCODE_EVLWHSPLAT		797
#define PPCXOCODE_EVLWHSPLATX		796
#define PPCXOCODE_EVLWWSPLAT		793
#define PPCXOCODE_EVLWWSPLATX		792

#define PPCXOCODE_EVSTDD			801
#define PPCXOCODE_EVSTDDX			800
#define PPCXOCODE_EVSTDH			805
#define PPCXOCODE_EVSTDHX			804
#define PPCXOCODE_EVSTDW			803
#define PPCXOCODE_EVSTDWX			802
#define PPCXOCODE_EVSTWHE			817
#define PPCXOCODE_EVSTWHEX			816
#define PPCXOCODE_EVSTWHO			821
#define PPCXOCODE_EVSTWHOX			820
#define PPCXOCODE_EVSTWWE			825
#define PPCXOCODE_EVSTWWEX			824
#define PPCXOCODE_EVSTWWO			829
#define PPCXOCODE_EVSTWWOX			828

#endif


__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/services/system/public/ppc/opcode.h $ $Rev: 219613 $" )
