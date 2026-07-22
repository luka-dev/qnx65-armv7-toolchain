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
 *	Pg.h	
 *		Manifests and data structures for the Pg-lib
 *

 */
#ifndef __PH_GLIB_H_INCLUDED
#define __PH_GLIB_H_INCLUDED

#ifndef _INTTYPES_H_INCLUDED
	#include <inttypes.h>
#endif

#ifndef __PHT_H_INCLUDED
	#include <photon/PhT.h>
#endif

#ifndef __PG_MACROS_H_INCLUDED
#include <photon/PgMacros.h>
#endif

#ifndef __PH_GLIB_VECTOR_H_INCLUDED
/*#include <photon/PgVector.h>*/
#endif

#include <photon/Pf.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" 
{
#endif

#define Pg_LEFT						0x1
#define Pg_RIGHT					0x2
#define Pg_TOP						0x4
#define Pg_BOTTOM					0x8

#define Pg_DO_EXTENT				0x0002
#define Pg_ITEST_CURSOR_HIDE		0x0010
#define Pg_CLIPTEST_CURSOR_HIDE		0x0020
#define Pg_CURSOR_SHOW				0x0080

#define	Pg_SET		1
#define	Pg_UNSET	0

#define		__PgShmemF_Valid		1
#define		__PgShmemF_Disabled		2
#define		__PgShmemF_Unlink				4


/* Trend flags	*/
#define Pg_TREND_HORIZ	0x00		/* Horizontal trend				*/
#define Pg_TREND_VERT	0x01		/* Vertical trend				*/

/* PgDrawBeveled flags */
#define Pg_BEVEL_SET		0x1000
#define Pg_BEVEL_ARROW		0x2000

#define	Pg_BEVEL_SQUARE		0x0000
#define	Pg_BEVEL_ROUND		0xC000
#define	Pg_BEVEL_CLIP		0x8000

#define	Pg_BEVEL_ALEFT		0x2000
#define	Pg_BEVEL_ARIGHT		0x6000
#define	Pg_BEVEL_AUP		0xA000
#define	Pg_BEVEL_ADOWN		0xE000

#define	Pg_BEVEL_TYPE_MASK	0xE000
#define	Pg_BEVEL_MAX		15


typedef struct pgpulse {
	uint32_t reserved[8]; /* will define later */
} PgPulse_t;

#if 0
#ifndef __CYGWIN__
/* PgSem typedef */

typedef struct pgsemaphore {
        sem_t *sem;
        char  *name;
        uint32_t flags;
} PgSemaphore_t;

/* PgSem related flags */

/* Semaphore flags */
#define Pg_SEM_NAMED 0x00000001

/* PgDestroySemaphore flags */
#define Pg_SEM_KEEP	 0x00000001

#endif
#endif

typedef uint32_t PgVidMemTag_t;
typedef uint32_t PgPluginTag_t;

typedef struct pg_surface_props {
	uint32_t type;
	PhDim_t size;
	PhPoint_t trans;
	unsigned long bpl;
	uint32_t reserved[2];
} PgSurfaceProps_t;

typedef struct pg_surface PgSurface_t;

/* PgVidMemDesc_t struct */
typedef struct {
	PgVidMemTag_t tag;
	PhDim_t size;
	unsigned long type;
	uint32_t pitch;
} PgVidMemDesc_t;

/* Xtended Bevelbox def struct */
typedef struct {
	PhPoint_t	ul;
	PhPoint_t	lr;
	short		width;
	short		depth;
	PgColor_t	ul_flat_color;
	PgColor_t	lr_flat_color;
	PgColor_t	light_color;
	PgColor_t	dark_color;
	PgColor_t	outline_color;
	PgColor_t	inline_color;
	int			flags;
	} PgBevelBoxDef_t;

/* Xtended Bevelbox flags */

#define Pg_BVB_FILL					0x00000001
#define Pg_BVB_FULL_GRADIENTS		0x00000002

/* These two flags are not supported, use
 * Pg_BVB_DRAW_ALL_INLINE or Pg_BVB_DRAW_ALL_OUTLINE.
 */
#define Pg_BVB_DRAW_INLINE			0x00000004
#define Pg_BVB_DRAW_OUTLINE			0x00000008

#define Pg_BVB_DRAW_LEFT			0x00000010
#define Pg_BVB_DRAW_RIGHT			0x00000020
#define Pg_BVB_DRAW_TOP				0x00000040
#define Pg_BVB_DRAW_BOTTOM			0x00000080

#define Pg_BVB_DRAW_TOP_OUTLINE 	0x00000100
#define Pg_BVB_DRAW_BOTTOM_OUTLINE	0x00000200
#define Pg_BVB_DRAW_LEFT_OUTLINE	0x00000400
#define Pg_BVB_DRAW_RIGHT_OUTLINE	0x00000800
#define Pg_BVB_DRAW_TOP_INLINE 		0x00001000
#define Pg_BVB_DRAW_BOTTOM_INLINE	0x00002000
#define Pg_BVB_DRAW_LEFT_INLINE		0x00004000
#define Pg_BVB_DRAW_RIGHT_INLINE	0x00008000

#define Pg_BVB_DRAW_ALL_INLINE	(Pg_BVB_DRAW_LEFT_INLINE | Pg_BVB_DRAW_RIGHT_INLINE | Pg_BVB_DRAW_TOP_INLINE | Pg_BVB_DRAW_BOTTOM_INLINE)
#define Pg_BVB_DRAW_ALL_OUTLINE	(Pg_BVB_DRAW_LEFT_OUTLINE | Pg_BVB_DRAW_RIGHT_OUTLINE | Pg_BVB_DRAW_TOP_OUTLINE | Pg_BVB_DRAW_BOTTOM_OUTLINE)
#define Pg_BVB_DRAW_ALL_BV		(Pg_BVB_DRAW_LEFT | Pg_BVB_DRAW_RIGHT | Pg_BVB_DRAW_TOP | Pg_BVB_DRAW_BOTTOM)
#define Pg_BVB_DRAW_ALL			(Pg_BVB_DRAW_ALL_INLINE | Pg_BVB_DRAW_ALL_OUTLINE | Pg_BVB_DRAW_ALL_BV)
#define Pg_BVB_DRAW_BITS		(Pg_BVB_DRAW_ALL | Pg_BVB_DRAW_OUTLINE | Pg_BVB_DRAW_INLINE | Pg_BVB_FULL_GRADIENTS | Pg_BVB_FILL )

/*
 * Mode for draw operations, all drivers 
 *	Pg_SetDrawMode
 */
/*     Photon name             value       X            	Logic	Mach	MSWin

 Raster Op Defines
 
 Reverse Polish Notation Defines of ROPS
 This follows Microsofts 256 raster operation
 definitions

 D = Dest Bit
 S = Source Bit
 P = Pattern Bit
 o = bitwise or operation
 a = bitwise and operation
 x = bitwise exclusive or operation
 n = bitwise not operation

 Truth Table
	P	S	D	ropbit
	0	0	0	0
	0	0	1	1
 	0	1	0	2
	0	1	1	3
	1	0	0	4
	1	0	1	5
	1	1	0	6
	1	1	1	7

 if the condition in the table is true for 
 each test turned on then dst bit=1, else 0

 So: DrawMode CC =  Source Copy
 		if ((conditions 2 | 3 | 6 | 7) == 1) on current bits, dst bit=1, else 0
	   DrawMode 66 = S ^ D
		if ((conditions 1 | 2 | 5 | 6) == 1) on current bits, dst bit=1, else 0
	   DrawMode 03 = ~ (P | S)
      if ((conditions 0 | 1) == 1) on current bits, dst bit=1, else 0

 It's a little confusing at first, but it does make sense once you wrap
 your brain around it.

          Name                Rop #            Operation
--------------------------------------------------------------------------*/

/* OLD */
#define Pg_DRAWMODE_OPAQUE		0		/* GXcopy			S		7		R2_COPYPEN */
#define Pg_DRAWMODE_XOR			1		/* GXxor			D ^ S	5		R2_XORPEN */
#define Pg_DRAWMODE_AND			2		/* GXand			D & S	C		R2_MASKPEN */
#define Pg_DRAWMODE_OR			3		/* GXor				D | S	B		R2_MERGEPEN */

/* NEW */
#define Pg_DrawModeZERO			0x0080	/* 0 */
#define Pg_DrawModeDPSoon			0x0180	/* ~ ( (D | (P | S) ) ) */
#define Pg_DrawModeDPSona			0x0280	/* D & ( ~ (P | S) ) */
#define Pg_DrawModePSon			0x0380	/* ~ (P | S) */
#define Pg_DrawModeSDPona			0x0480	/* S & ( ~ (D | P) ) */
#define Pg_DrawModeDPon			0x0580	/* ~ (D | P) */
#define Pg_DrawModePDSxnon			0x0680	/* ~ (P | (~ (D ^ S))) */
#define Pg_DrawModePDSaon			0x0780	/* ~ (P | (D & S)) */
#define Pg_DrawModeSDPnaa			0x0880	/* S & (D & (~ P)) */
#define Pg_DrawModePDSxon			0x0980	/* ~ (P | (D ^ S)) */
#define Pg_DrawModeDPna			0x0A80	/* D & (~ P) */
#define Pg_DrawModePSDnaon			0x0B80	/* ~ (P | (S & (~ D))) */
#define Pg_DrawModeSPna			0x0C80	/* S & (~ P) */
#define Pg_DrawModePDSnaon			0x0D80	/* ~ (P | (D & (~ S))) */
#define Pg_DrawModePDSonon			0x0E80	/* ~ (P | (~(D | S))) */
#define Pg_DrawModePn				0x0F80	/* ~ P */
#define Pg_DrawModePDSona			0x1080	/* P & (~ (D | S)) */
#define Pg_DrawModeDSon			0x1180	/* ~ (D | S) */
#define Pg_DrawModeSDPxnon			0x1280	/* ~ (S | (~ (D ^ P))) */
#define Pg_DrawModeSDPaon			0x1380	/* ~ (S | (D & P)) */
#define Pg_DrawModeDPSxnon			0x1480	/* ~ (D | (~ (P ^ S))) */
#define Pg_DrawModeDPSaon			0x1580	/* ~ (D | (P & S)) */
#define Pg_DrawModePSDPSanaxx		0x1680	/* P ^ (S ^ (D & (~ (P & S)))) */
#define Pg_DrawModeSSPxDSxaxn		0x1780	/* ~ (S ^ ((S ^ P) & (D ^ S))) */
#define Pg_DrawModeSPxPDxa			0x1880	/* (S ^ P) & (P ^ D) */
#define Pg_DrawModeSDPSanaxn		0x1980	/* ~ (S ^ (D & (~ (P & S)))) */
#define Pg_DrawModePDSPaox			0x1A80	/* P ^ (D | (S & P)) */
#define Pg_DrawModeSDPSxaxn		0x1B80	/* ~ (S ^ (D & (P ^ S)))) */
#define Pg_DrawModePSDPaox			0x1C80	/* P ^ (S | (D & P))) */
#define Pg_DrawModeDSPDxaxn		0x1D80	/* ~ (D ^ (S & (P ^ D))) */
#define Pg_DrawModePDSox			0x1E80	/* P ^ (D | S) */
#define Pg_DrawModePDSoan			0x1F80	/* ~ (P & (D | S)) */
#define Pg_DrawModeDPSnaa			0x2080	/* D & (P & (~S)) */
#define Pg_DrawModeSDPxon			0x2180	/* ~ (S | (D ^ P)) */
#define Pg_DrawModeDSna			0x2280	/* D & (~S) */
#define Pg_DrawModeSPDnaon			0x2380	/* ~ (S | (P & (~D))) */
#define Pg_DrawModeSPxDSxa			0x2480	/* (S ^ P) & (D ^ S) */
#define Pg_DrawModePDSPanaxn		0x2580	/* ~ (P ^ (D & (~ (S & P)))) */
#define Pg_DrawModeSDPSaox			0x2680	/* S ^ (D | (P & S)) */
#define Pg_DrawModeSDPSxnox		0x2780	/* S ^ (D | (~ (P ^ S))) */
#define Pg_DrawModeDPSxa			0x2880	/* D & (P ^ S) */
#define Pg_DrawModePSDPSaoxxn		0x2980	/* ~ (P ^ (S ^ (D | (P & S)))) */
#define Pg_DrawModeDPSana			0x2A80	/* D & (~ (P & S)) */
#define Pg_DrawModeSSPxPDxaxn		0x2B80	/* ~ (S ^ ((S ^ P) & (P ^ D)) */
#define Pg_DrawModeSPDSoax			0x2C80	/* S ^ (P & (D | S)) */
#define Pg_DrawModePSDnox			0x2D80	/* P ^ (S | (~D)) */
#define Pg_DrawModePSDPxox			0x2E80	/* P ^ (S | (D ^ P)) */
#define Pg_DrawModePSDnoan			0x2F80	/* ~ (P & (S | (~D))) */
#define Pg_DrawModePSna			0x3080	/* P & (~ S) */
#define Pg_DrawModeSDPnaon			0x3180	/* ~ (S | (D & (~P))) */
#define Pg_DrawModeSDPSoox			0x3280	/* S ^ (D | (P | S)) */
#define Pg_DrawModeSn				0x3380	/* ~S */
#define Pg_DrawModeSPDSaox			0x3480	/* S ^ (P | (D & S)) */
#define Pg_DrawModeSPDSxnox		0x3580	/* S ^ (P | (~ (D ^ S))) */
#define Pg_DrawModeSDPox			0x3680	/* S ^ (D | P) */
#define Pg_DrawModeSDPoan			0x3780	/* ~ (S & (D | P)) */
#define Pg_DrawModePSDPoax			0x3880	/* P ^ (S & (D | P))) */
#define Pg_DrawModeSPDnox			0x3980	/* S ^ (P | (~ D))) */
#define Pg_DrawModeSPDSxox			0x3A80	/* S ^ (P | (D ^ S)) */
#define Pg_DrawModeSPDnoan			0x3B80	/* ~ (S & (P | (~ D))) */
#define Pg_DrawModePSx				0x3C80	/* P ^ S */
#define Pg_DrawModeSPDSonox		0x3D80	/* S ^ (P | (~ (D | S))) */
#define Pg_DrawModeSPDSnaox		0x3E80	/* S ^ (P | (D & (~ S))) */
#define Pg_DrawModePSan			0x3F80	/* ~ (P & S) */
#define Pg_DrawModePSDnaa			0x4080	/* P & (S & (~ D)) */
#define Pg_DrawModeDPSxon			0x4180	/* ~ (D | (P ^ S) */
#define Pg_DrawModeSDxPDxa			0x4280	/* (S ^ D) & (P ^ D) */
#define Pg_DrawModeSPDSanaxn		0x4380	/* ~ (S ^ (P & (~ (D & S)))) */
#define Pg_DrawModeSDna			0x4480	/* S & (~ D) */
#define Pg_DrawModeDPSnaon			0x4580	/* ~ (D | (P & (~ S))) */
#define Pg_DrawModeDSPDaox			0x4680	/* D ^ (S | (P & D))) */
#define Pg_DrawModePSDPxaxn		0x4780	/* ~ (P ^ (S & (D ^ P))) */
#define Pg_DrawModeSDPxa			0x4880	/* S & (D ^ P)) */
#define Pg_DrawModePDSPDoaxxn		0x4980	/* ~ (P ^ (D ^ (S & (P | D)))) */
#define Pg_DrawModeDPSDoax			0x4A80	/* D ^ (P & (S | D)) */
#define Pg_DrawModePDSnox			0x4B80	/* P ^ (D | (~ S)) */
#define Pg_DrawModeSDPana			0x4C80	/* S & (~ (D & P)) */
#define Pg_DrawModeSSPxDSxoxn		0x4D80	/* ~ (S ^ ((S ^ P) | (D ^ S))) */
#define Pg_DrawModePDSPxox			0x4E80	/* P ^ (D | (S ^ P)) */
#define Pg_DrawModePDSnoan			0x4F80	/* ~ (P & (D | (~S))) */
#define Pg_DrawModePDna			0x5080	/* (~D) & P */
#define Pg_DrawModeDSPnaon			0x5180	/* ~ (D | (S & (~P))) */
#define Pg_DrawModeDPSDaox			0x5280	/* D ^ (P | (S & D)) */
#define Pg_DrawModeSPDSxaxn		0x5380	/* ~ (S ^ (P & (D ^ S))) */
#define Pg_DrawModeDPSonon			0x5480	/* ~ (D | (~ (P | S))) */
#define Pg_DrawModeDn				0x5580	/* ~ D */
#define Pg_DrawModeDPSox			0x5680	/* D ^ (P | S) */
#define Pg_DrawModeDPSoan			0x5780	/* ~ (D & (P | S)) */
#define Pg_DrawModePDSPoax			0x5880	/* P ^ (D & (S | P)) */
#define Pg_DrawModeDPSnox			0x5980	/* D ^ (P | (~ S)) */
#define Pg_DrawModeDPx				0x5A80	/* D ^ P */
#define Pg_DrawModeDPSDonox		0x5B80	/* D ^ (P | (~ (S | D))) */
#define Pg_DrawModeDPSDxox			0x5C80	/* D ^ (P | (S ^ D)) */
#define Pg_DrawModeDPSnoan			0x5D80	/* ~ (D & (P | (~ S))) */
#define Pg_DrawModeDPSDnaox		0x5E80	/* D ^ (P | (S & (~ D))) */
#define Pg_DrawModeDPan			0x5F80	/* ~ (D & P) */
#define Pg_DrawModePDSxa			0x6080	/* P & (D ^ S) */
#define Pg_DrawModeDSPDSaoxxn		0x6180	/* ~ (D ^ (S ^ (P | (D & S)))) */
#define Pg_DrawModeDSPDoax			0x6280	/* D ^ (S & (P | D)) */
#define Pg_DrawModeSDPnox			0x6380	/* S ^ (D | (~ P)) */
#define Pg_DrawModeSDPSoax			0x6480	/* S ^ (D & (P | S)) */
#define Pg_DrawModeDSPnox			0x6580	/* D ^ (S | (~ P)) */
#define Pg_DrawModeDSx				0x6680	/* D ^ S */
#define Pg_DrawModeSDPSonox		0x6780	/* S ^ (D | (~ (P | S))) */
#define Pg_DrawModeDSPDSonoxxn		0x6880	/* ~ (D ^ (S ^ (P | (~ (D | S))))) */
#define Pg_DrawModePDSxxn			0x6980	/* ~ (P ^ (D ^ S)) */
#define Pg_DrawModeDPSax			0x6A80	/* D ^ (P & S) */
#define Pg_DrawModePSDPSoaxxn		0x6B80	/* ~ (P ^ (S ^ (D & (P | S)))) */
#define Pg_DrawModeSDPax			0x6C80	/* S ^ (D & P) */
#define Pg_DrawModePDSPDoaxx		0x6D80	/* P ^ (D ^ (S & (P | D))) */
#define Pg_DrawModeSDPSnoax		0x6E80	/* S ^ (D & (P | (~ S))) */
#define Pg_DrawModePDSxnan			0x6F80	/* ~ (P & (~ (D ^ S))) */
#define Pg_DrawModePDSana			0x7080	/* P & (~ (D & S)) */
#define Pg_DrawModeSSDxPDxaxn		0x7180	/* ~ (S ^ ((S ^ D) & (P ^ D))) */
#define Pg_DrawModeSDPSxox			0x7280	/* S ^ (D | (P ^ S)) */
#define Pg_DrawModeSDPnoan			0x7380	/* ~ (S & (D | (~P))) */
#define Pg_DrawModeDSPDxox			0x7480	/* D ^ (S | (P ^ D)) */
#define Pg_DrawModeDSPnoan			0x7580	/* ~ (D & (S | (~ P))) */
#define Pg_DrawModeSDPSnaox		0x7680	/* S ^ (D | (P & (~ S))) */
#define Pg_DrawModeDSan			0x7780	/* ~ (D & S) */
#define Pg_DrawModePDSax			0x7880	/* P ^ (D & S) */
#define Pg_DrawModeDSPDSoaxxn		0x7980	/* ~ (D ^ (S ^ (P & (D | S)))) */
#define Pg_DrawModeDPSDnoax		0x7A80	/* D ^ (P & (S | (~ D))) */
#define Pg_DrawModeSDPxnan			0x7B80	/* ~ (S & (~ (D ^ P))) */
#define Pg_DrawModeSPDSnoax		0x7C80	/* S ^ (P & (D | (~ S))) */
#define Pg_DrawModeDPSxnan			0x7D80	/* ~ (D & (~ (P ^ S))) */
#define Pg_DrawModeSPxDSxo			0x7E80	/* (S ^ P) | (D ^ S) */
#define Pg_DrawModeDPSaan			0x7F80	/* ~ (D & (P & S)) */
#define Pg_DrawModeDPSaa			0x8080	/* D & (P & S) */
#define Pg_DrawModeSPxDSxon		0x8180	/* ~ ((P ^ S) | (D ^ S)) */
#define Pg_DrawModeDPSxna			0x8280	/* D & (~ (P ^ S)) */
#define Pg_DrawModeSPDSnoaxn		0x8380	/* ~ (S ^ (P & (D | (~ S)))) */
#define Pg_DrawModeSDPxna			0x8480	/* S & (~ (D ^ P)) */
#define Pg_DrawModePDSPnoaxn		0x8580	/* ~ (P ^ (D & (S | (~ P)))) */
#define Pg_DrawModeDSPDSoaxx		0x8680	/* D ^ (S ^ (P & (D | S))) */
#define Pg_DrawModePDSaxn			0x8780	/* ~ (P ^ (D & S)) */
#define Pg_DrawModeDSa				0x8880	/* D & S */
#define Pg_DrawModeSDPSnaoxn		0x8980	/* ~ (S ^ (D | (P & (~ S)))) */
#define Pg_DrawModeDSPnoa			0x8A80	/* D & (S | (~ P)) */
#define Pg_DrawModeDSPSxoxn		0x8B80	/* ~ (D ^ (S | (P ^ S))) */
#define Pg_DrawModeSDPnoa			0x8C80	/* S & (D | (~ P)) */
#define Pg_DrawModeSDPSxoxn		0x8D80	/* ~ (S ^ (D | (P ^ S))) */
#define Pg_DrawModeSSDxPDxax		0x8E80	/* S ^ ((S ^ D) & (P ^ D)) */
#define Pg_DrawModePDSanan			0x8F80	/* ~ (P & (~ (D & S))) */
#define Pg_DrawModePDSxna			0x9080	/* P & (~ (D ^ S)) */
#define Pg_DrawModeSDPSnoaxn		0x9180	/* ~ (S ^ (D & (P | (~ S)))) */
#define Pg_DrawModeDPSDPoaxx		0x9280	/* D ^ (P ^ (S & (D | P))) */
#define Pg_DrawModeSPDaxn			0x9380	/* ~ (S ^ (P & D)) */
#define Pg_DrawModePSDPSoaxx		0x9480	/* P ^ (S ^ (D & (P | S))) */
#define Pg_DrawModeDPSaxn			0x9580	/* ~ (D ^ (P & S)) */
#define Pg_DrawModeDPSxx			0x9680	/* D ^ (P ^ S) */
#define Pg_DrawModePSDPSonoxx		0x9780	/* P ^ (S ^ (D | (~ (P | S)))) */
#define Pg_DrawModeSDPSonoxn		0x9880	/* ~ (S ^ (D | (~ (P | S)))) */
#define Pg_DrawModeDSxn			0x9980	/* ~ (D ^ S) */
#define Pg_DrawModeDPSnax			0x9A80	/* D ^ (P & (~ S)) */
#define Pg_DrawModeSDPSoaxn		0x9B80	/* ~ (S ^ (D & (P | S))) */
#define Pg_DrawModeSPDnax			0x9C80	/* S ^ (P & (~ D)) */
#define Pg_DrawModeDSPDoaxn		0x9D80	/* ~ (D ^ (S & (P | D))) */
#define Pg_DrawModeDSPDSaoxx		0x9E80	/* D ^ (S ^ (P | (D & S))) */
#define Pg_DrawModePDSxan			0x9F80	/* ~ (P & (D ^ S)) */
#define Pg_DrawModeDPa				0xA080	/* (D & P) */
#define Pg_DrawModePDSPnaoxn		0xA180	/* ~ (P ^ (D | (S & (~ P)))) */
#define Pg_DrawModeDPSnoa			0xA280	/* D & (P | (~ S)) */
#define Pg_DrawModeDPSDxoxn		0xA380	/* ~ (D ^ (P | (S ^ D))) */
#define Pg_DrawModePDSPonoxn		0xA480	/* ~ (P ^ (D | (~ (S | P)))) */
#define Pg_DrawModePDxn			0xA580	/* ~ (P ^ D) */
#define Pg_DrawModeDSPnax			0xA680	/* D ^ (S & (~ P)) */
#define Pg_DrawModePDSPoaxn		0xA780	/* ~ (P ^ (D & (S | P))) */
#define Pg_DrawModeDPSoa			0xA880	/* D & (P | S) */
#define Pg_DrawModeDPSoxn			0xA980	/* ~ (D ^ (P | S)) */
#define Pg_DrawModeD				0xAA80	/* D */
#define Pg_DrawModeDPSono			0xAB80	/* D | (~ (P | S)) */
#define Pg_DrawModeSPDSxax			0xAC80	/* S ^ (P & (D ^ S)) */
#define Pg_DrawModeDPSDaoxn		0xAD80	/* ~ (D ^ (P | (S & D))) */
#define Pg_DrawModeDSPnao			0xAE80	/* D | (S & (~ P)) */
#define Pg_DrawModeDPno			0xAF80	/* D | (~ P) */
#define Pg_DrawModePDSnoa			0xB080	/* P & (D | (~ S)) */
#define Pg_DrawModePDSPxoxn		0xB180	/* ~ (P ^ (D | (S ^ P))) */
#define Pg_DrawModeSSPxDSxox		0xB280	/* S ^ ((S ^ P) | (D ^ S)) */
#define Pg_DrawModeSDPanan			0xB380	/* ~ (S & (~ (D & P))) */
#define Pg_DrawModePSDnax			0xB480	/* P ^ (S & (~ D)) */
#define Pg_DrawModeDPSDoaxn		0xB580	/* ~ (D ^ (P & (S | D))) */
#define Pg_DrawModeDPSDPaoxx		0xB680	/* D ^ (P ^ (S | (D & P))) */
#define Pg_DrawModeSDPxan			0xB780	/* ~ (S & (D ^ P)) */
#define Pg_DrawModePSDPxax			0xB880	/* P ^ (S & (D ^ P)) */
#define Pg_DrawModeDSPDaoxn		0xB980	/* ~ (D ^ (S | (P & D))) */
#define Pg_DrawModeDPSnao			0xBA80	/* D | (P & (~ S)) */
#define Pg_DrawModeDSno			0xBB80	/* D | (~ S) */
#define Pg_DrawModeSPDSanax		0xBC80	/* S ^ (P & (~ (D & S))) */
#define Pg_DrawModeSDxPDxan		0xBD80	/* ~ ((S ^ D) & (P ^ D)) */
#define Pg_DrawModeDPSxo			0xBE80	/* D | (P ^ S) */
#define Pg_DrawModeDPSano			0xBF80	/* D | (~ (P & S)) */
#define Pg_DrawModePSa				0xC080	/* P & S */
#define Pg_DrawModeSPDSnaoxn		0xC180	/* ~ (S ^ (P | (D & (~ S)))) */
#define Pg_DrawModeSPDSonoxn		0xC280	/* ~ (S ^ (P | (~ (D | S)))) */
#define Pg_DrawModePSxn			0xC380	/* ~ (P ^ S) */
#define Pg_DrawModeSPDnoa			0xC480	/* S & (P | (~ D)) */
#define Pg_DrawModeSPDSxoxn		0xC580	/* ~ (S ^ (P | (D ^ S))) */
#define Pg_DrawModeSDPnax			0xC680	/* S ^ (D & (~ P)) */
#define Pg_DrawModePSDPoaxn		0xC780	/* ~ (P ^ (S & (D | P))) */
#define Pg_DrawModeSDPoa			0xC880	/* S & (D | P) */
#define Pg_DrawModeSPDoxn			0xC980	/* ~ (S ^ (P | D)) */
#define Pg_DrawModeDPSDxax			0xCA80	/* D ^ (P & (S ^ D)) */
#define Pg_DrawModeSPDSaoxn		0xCB80	/* ~ (S ^ (P | (D & S))) */
#define Pg_DrawModeS				0xCC80	/* S */
#define Pg_DrawModeSDPono			0xCD80	/* S | (~ (D | P)) */
#define Pg_DrawModeSDPnao			0xCE80	/* S | (D & (~ P)) */
#define Pg_DrawModeSPno			0xCF80	/* S | (~ P) */
#define Pg_DrawModePSDnoa			0xD080	/* P & (S | (~ D)) */
#define Pg_DrawModePSDPxoxn		0xD180	/* ~ (P ^ (S | (D ^ P))) */
#define Pg_DrawModePDSnax			0xD280	/* P ^ (D & (~ S)) */
#define Pg_DrawModeSPDSoaxn		0xD380	/* ~ (S ^ (P & (D | S))) */
#define Pg_DrawModeSSPxPDxax		0xD480	/* S ^ ((S ^ P) & (P ^ D)) */
#define Pg_DrawModeDPSanan			0xD580	/* ~ (D & (~ (P & S))) */
#define Pg_DrawModePSDPSaoxx		0xD680	/* P ^ (S ^ (D | (P & S))) */
#define Pg_DrawModeDPSxan			0xD780	/* ~ (D & (P ^ S)) */
#define Pg_DrawModePDSPxax			0xD880	/* P ^ (D & (S ^ P)) */
#define Pg_DrawModeSDPSaoxn		0xD980	/* ~ (S ^ (D | (P & S))) */
#define Pg_DrawModeDPSDanax		0xDA80	/* D ^ (P & (~ (S & D))) */
#define Pg_DrawModeSPxDSxan		0xDB80	/* ~ ((S ^ P) & (D ^ S)) */
#define Pg_DrawModeSPDnao			0xDC80	/* S | (P & (~ D)) */
#define Pg_DrawModeSDno			0xDD80	/* S | (~ D) */
#define Pg_DrawModeSDPxo			0xDE80	/* S | (D ^ P) */
#define Pg_DrawModeSDPano			0xDF80	/* S | (~ (D & P)) */
#define Pg_DrawModePDSoa			0xE080	/* P & (D | S) */
#define Pg_DrawModePDSoxn			0xE180	/* ~ (P ^ (D | S)) */
#define Pg_DrawModeDSPDxax			0xE280	/* D ^ (S & (P ^ D)) */
#define Pg_DrawModePSDPaoxn		0xE380	/* ~ (P ^ (S | (D & P))) */
#define Pg_DrawModeSDPSxax			0xE480	/* S ^ (S & (P ^ S)) */
#define Pg_DrawModePDSPaoxn		0xE580	/* ~ (P ^ (D | (S & P))) */
#define Pg_DrawModeSDPSanax		0xE680	/* S ^ (D & (~ (P & S))) */
#define Pg_DrawModeSPxDPxan		0xE780	/* ~ ((S ^ P) & (D ^ P)) */
#define Pg_DrawModeSSPxDSxax		0xE880	/* S ^ ((S ^ P) & (D ^ S)) */
#define Pg_DrawModeDSPDSanaxxn		0xE980	/* ~ (D ^ (S ^ (P & (~ (D & S))))) */
#define Pg_DrawModeDPSao			0xEA80	/* D | (P & S) */
#define Pg_DrawModeDPSxno			0xEB80	/* D | (~ (P ^ S)) */
#define Pg_DrawModeSDPao			0xEC80	/* S | (D & P) */
#define Pg_DrawModeSDPxno			0xED80	/* S | (~ (D ^ P)) */
#define Pg_DrawModeDSo				0xEE80	/* D | S */
#define Pg_DrawModeSDPnoo			0xEF80	/* S | (D | (~ P)) */
#define Pg_DrawModeP				0xF080	/* P */
#define Pg_DrawModePDSono			0xF180	/* P | (~ (D | S)) */
#define Pg_DrawModePDSnao			0xF280	/* P | (D & (~ S)) */
#define Pg_DrawModePSno			0xF380	/* P | (~ S) */
#define Pg_DrawModePSDnao			0xF480	/* P | (S & (~ D)) */
#define Pg_DrawModePDno			0xF580	/* P | (~ D) */
#define Pg_DrawModePDSxo			0xF680	/* P | (D ^ S) */
#define Pg_DrawModePDSano			0xF780	/* P | (~ (D & S)) */
#define Pg_DrawModePDSao			0xF880	/* P | (D & S) */
#define Pg_DrawModePDSxno			0xF980	/* P | (~ (D ^ S)) */
#define Pg_DrawModeDPo				0xFA80	/* D | P */
#define Pg_DrawModeDPSnoo			0xFB80	/* D | (P | (~ S)) */
#define Pg_DrawModePSo				0xFC80	/* P | S */
#define Pg_DrawModePSDnoo			0xFD80	/* P | (S | (~ D)) */
#define Pg_DrawModeDPSoo			0xFE80	/* D | (P | S) */
#define Pg_DrawModeONE				0xFF80	/* 1 */

/* New ROP Convenience Defines */
#define Pg_DrawModeBLACK			Pg_DrawModeZERO
#define Pg_DrawModeWHITE			Pg_DrawModeONE

#define Pg_DrawModeSRCCOPY			Pg_DrawModeS
#define Pg_DrawModeSRCINVERT		Pg_DrawModeSn

#define Pg_DrawModePATCOPY			Pg_DrawModeP
#define Pg_DrawModePATINVERT		Pg_DrawModePn

#define Pg_DrawModeNOP				Pg_DrawModeD
#define Pg_DrawModeDSTINVERT		Pg_DrawModeDn

#define Pg_DrawModeSRCXOR			Pg_DrawModeDSx
#define Pg_DrawModePATXOR			Pg_DrawModePDx
#define Pg_DrawModeSRCAND			Pg_DrawModeDSa
#define Pg_DrawModePATAND			Pg_DrawModePDa
#define Pg_DrawModeSRCOR			Pg_DrawModeDSo
#define Pg_DrawModePATOR			Pg_DrawModePDo






/* Defines for the yet to be named super cool blt */
typedef struct _pg_offscreen_blit_info {
	long unsigned	src_id;
	long unsigned	dest_id;
	PhRect_t		src_rect;
	PhRect_t		dest_rect;
	} PgOffscreenBlitInfo_t;

/* Chroma Key BitBlt Operations */
#if 0
#define Pg_CHROMA_SRC_KEY 			0x00000000
#define Pg_CHROMA_DEST_KEY 			0x00000001
#define Pg_CHROMA_NOT_SRC_KEY 		0x00000002
#define Pg_CHROMA_NOT_DST_KEY		0x00000003
#else
#define Pg_CHROMA_SRC_MATCH		0
#define Pg_CHROMA_DEST_MATCH		1
#define Pg_CHROMA_DRAW		0
#define Pg_CHROMA_NODRAW		2
#endif
#define Pg_ENABLE_CHROMA			0x80000000

/* Hardware Scaling */
#define Pg_STRETCH_BLT				0x00000008

/* Wait for V_SYNC */
#define Pg_WAIT_VSYNC				0x00000010

/*
 * Palette Modes - PgSetPalette
 */
#define Pg_PALSET_TYPEMASK		0x0F
#define Pg_PALSET_SOFT			0x00
#define Pg_PALSET_HARD			0x01
#define Pg_PALSET_HARDLOCKED	0x02
#define Pg_PALSET_GLOBAL		0x03
#define Pg_PALSET_HARDINACTIVE	0x05
#define Pg_PALSET_FORCE_EXPOSE	0x80


/*
 * PgDrawPhImagemx flags 
 */
#define  Pg_GHOST	0x01000000
 
/*
 * Bitmap array types
 *	PgDrawBitmap
 */
#define Pg_BITMAP_TRANSPARENT	0xFF	/* Bitmap transparent backfill */
#define Pg_BITMAP_BACKFILL		0xFE	/* Bitmap backfill */

/*
 * Image array types
 *	PgDrawImage
 */
#define	Pg_IMAGE_CLASS_MASK		0x38
#define	Pg_IMAGE_CLASS_PALETTE	0x10
#define	Pg_IMAGE_CLASS_GRADIENT	0x18
#define	Pg_IMAGE_CLASS_BLEND	0x08
#define	Pg_IMAGE_CLASS_DIRECT	0x20

#define Pg_IMAGE_PALETTE_BYTE	0x10	/* IIIIIIII */
#define Pg_IMAGE_BYTE_PALETTE	Pg_IMAGE_PALETTE_BYTE
#define	Pg_IMAGE_PALETTE_NIBBLE	0x11	/* IIIIiiii (I first, i second ) */
#define	Pg_IMAGE_NIBBLE_PALETTE	Pg_IMAGE_PALETTE_NIBBLE
#define Pg_IMAGE_PALETTE_BYTE_TRANSLATED	0x12 /* IIIIIIII (indexes to display native palette) */
#define Pg_IMAGE_TRANSLATED_BYTE_PALETTE Pg_IMAGE_PALETTE_BYTE_TRANSLATED  
#define	Pg_IMAGE_GRADIENT_BYTE	0x18
#define	Pg_IMAGE_GRADIENT_NIBBLE 0x19
#define	Pg_IMAGE_GBLEND_BYTE	0x08
#define	Pg_IMAGE_GBLEND_NIBBLE	0x09
#define	Pg_IMAGE_DBLEND_SHORT	0x0A
#define	Pg_IMAGE_DBLEND_LONG	0x0B
#define	Pg_IMAGE_DIRECT_8888	0x20	/* AAAAAAAARRRRRRRRGGGGGGGGBBBBBBBB */
#define	Pg_IMAGE_DIRECT_888		0x21	/* RRRRRRRRGGGGGGGGBBBBBBBB */
#define	Pg_IMAGE_DIRECT_565		0x22	/* RRRRRGGGGGGBBBBB */
#define	Pg_IMAGE_DIRECT_555		0x23	/* xRRRRRGGGGGBBBBB	*/
#define	Pg_IMAGE_DIRECT_444		0x24	/* xxxxRRRRGGGGBBBB	*/
#define Pg_IMAGE_DIRECT_4444	0x25	/* AAAARRRRGGGGBBBB	*/
#define Pg_IMAGE_DIRECT_1555	0x26	/* ARRRRRGGGGGBBBBB */
#define	Pg_IMAGE_FIRST_TIME		0x10000l

typedef char *PgPattern_t;

typedef struct {
	unsigned short	hue;
	unsigned char	sat, vid;
} PgColorHSV_t;

typedef struct {
	unsigned char c,m,y,k;
} PgColorCMYK_t;

/* Some common colors */
#define	Pg_TRANSPARENT		((PgColor_t)0xFFFFFFFF)
#define	Pg_INVERT_COLOR		((PgColor_t)0xFFFFFFFE)
#define	Pg_MIX_COLOR		((PgColor_t)0x1000000)
#define	Pg_INDEX_COLOR		((PgColor_t)0x2000000)
#define	Pg_DEVICE_COLOR		((PgColor_t)0x4000000)
#define	PgColorByIndex( v )	(Pg_INDEX_COLOR | ((v) & 0xFF))
#define	Pg_CLOSE_COLOR		((PgColor_t)0x4000000)
#define Pg_DEFAULT_WM_COLOR	((PgColor_t)0xFFFFFFFD)

#define	Pg_BLACK			PgGrey( 0 )
#define	Pg_WHITE			PgGrey( 255 )
#define Pg_LGREY			PgGrey( 216 )
#define	Pg_GREY				PgGrey( 192 )
#define	Pg_MGREY			PgGrey( 144 )
#define	Pg_DGREY			PgGrey( 96 )
#define	Pg_RED				PgRGB( 255, 0, 0 )
#define	Pg_GREEN			PgRGB( 0, 255, 0 ) 
#define	Pg_BLUE				PgRGB( 0, 0, 255 )
#define	Pg_YELLOW			PgRGB( 255, 255, 0 )
#define	Pg_MAGENTA			PgRGB( 255, 0, 255 )
#define	Pg_CYAN				PgRGB( 0, 255, 255 )
#define	Pg_CELIDON			(PgRGB( 39, 176, 136 ) | Pg_MIX_COLOR)

#define	Pg_WINDOWGREEN		PgRGB( 0, 128, 112 )
#define	Pg_BALLOONCOLOR		PgRGB( 254, 255, 177 )

#define Pg_GRAY				Pg_GREY
#define Pg_LGRAY			Pg_LGREY
#define Pg_MGRAY			Pg_MGREY
#define Pg_DGRAY			Pg_DGREY

#define	Pg_DGREEN			PgRGB( 0, 160, 0 )
#define	Pg_DCYAN			PgRGB( 0, 128, 160 )
#define	Pg_DBLUE			PgRGB( 0, 0, 160 )
#define	Pg_BROWN			PgRGB( 96, 54, 0 )
#define	Pg_PURPLE			PgRGB( 133, 0, 182 )

/* The standard VGA palette */
#define	Pg_VGA0				PgRGB( 0, 0, 0 )
#define	Pg_VGA1				PgRGB( 0, 0, 168 )
#define	Pg_VGA2				PgRGB( 0, 168, 0 )
#define	Pg_VGA3				PgRGB( 0, 168, 168 )
#define	Pg_VGA4				PgRGB( 168, 0, 0 )
#define	Pg_VGA5				PgRGB( 168, 0, 168 )
#define	Pg_VGA6				PgRGB( 168, 84, 0 )
#define	Pg_VGA7				PgRGB( 168, 168, 168 )
#define	Pg_VGA8				PgRGB( 84, 84, 84 )
#define	Pg_VGA9				PgRGB( 84, 84, 255 )
#define	Pg_VGAA				PgRGB( 84, 255, 84 )
#define	Pg_VGAB				PgRGB( 84, 255, 255 )
#define	Pg_VGAC				PgRGB( 255, 84, 84 )
#define	Pg_VGAD				PgRGB( 255, 84, 255 )
#define	Pg_VGAE				PgRGB( 255, 255, 84 )
#define	Pg_VGAF				PgRGB( 255, 255, 255 )


/* Some useful patterns */
#define	Pg_PAT_DEFAULT		NULL
#define	Pg_PAT_NONE			((PgPattern_t) "\x00\x00\x00\x00\x00\x00\x00\x00")
#define	Pg_PAT_FULL			((PgPattern_t) "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF")
#define	Pg_PAT_HALF			((PgPattern_t) "\xAA\x55\xAA\x55\xAA\x55\xAA\x55")
#define	Pg_PAT_CHECKB8		((PgPattern_t) "\xF0\xF0\xF0\xF0\x0F\x0F\x0F\x0F")
#define	Pg_PAT_CHECKB4		((PgPattern_t) "\xCC\xCC\x33\x33\xCC\xCC\x33\x33")
#define	Pg_PAT_BACK_HALF	((PgPattern_t) "\x55\xAA\x55\xAA\x55\xAA\x55\xAA")
#define	Pg_PAT_DIAMOND		((PgPattern_t) "\x10\x38\x7C\xFE\x7C\x38\x10\x00")
#define	Pg_PAT_HORIZ8		((PgPattern_t) "\xFF\x00\x00\x00\x00\x00\x00\x00")
#define	Pg_PAT_HORIZ4		((PgPattern_t) "\xFF\x00\x00\x00\xFF\x00\x00\x00")
#define	Pg_PAT_HORIZ2		((PgPattern_t) "\xFF\x00\xFF\x00\xFF\x00\xFF\x00")
#define	Pg_PAT_VERT8		((PgPattern_t) "\x80\x80\x80\x80\x80\x80\x80\x80")
#define	Pg_PAT_VERT4		((PgPattern_t) "\x88\x88\x88\x88\x88\x88\x88\x88")
#define	Pg_PAT_VERT2		((PgPattern_t) "\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA")
#define	Pg_PAT_DIAGF8		((PgPattern_t) "\x80\x01\x02\x04\x08\x10\x20\x40")
#define	Pg_PAT_DIAGF4		((PgPattern_t) "\x88\x11\x22\x44\x88\x11\x22\x44")
#define	Pg_PAT_DIAGB8		((PgPattern_t) "\x80\x40\x20\x10\x08\x04\x02\x01")
#define	Pg_PAT_DIAGB4		((PgPattern_t) "\x88\x44\x22\x11\x88\x44\x22\x11")
#define	Pg_PAT_BRICK		((PgPattern_t) "\x20\x20\xFF\x02\x02\x02\xFF\x20")
#define	Pg_PAT_WEAVE		((PgPattern_t) "\x3E\x1D\x88\xD1\xE3\xC5\x88\x5C")
#define	Pg_PAT_RXHATCH8		((PgPattern_t) "\xFF\x80\x80\x80\x80\x80\x80\x80")
#define	Pg_PAT_RXHATCH4		((PgPattern_t) "\xFF\x88\x88\x88\xFF\x88\x88\x88")
#define	Pg_PAT_RXHATCH2		((PgPattern_t) "\xFF\xAA\xFF\xAA\xFF\xAA\xFF\xAA")
#define	Pg_PAT_DXHATCH8		((PgPattern_t) "\x80\x41\x22\x14\x08\x14\x22\x41")
#define	Pg_PAT_DXHATCH4		((PgPattern_t) "\x88\x55\x22\x55\x88\x55\x22\x55")

/*
 *	Flags used for various commands
 */

#define Pg_RELATIVE		(0x01 << 8)
#define Pg_CENTER_BASED	(0x00 << 8)
#define Pg_EXTENT_BASED	(0x01 << 8)
#define Pg_CLOSED		(0x10 << 8)
#define Pg_BACK_FILL	(0x01 << 8)
#define	Pg_SMART_BLIT	(0x01 << 8)
#define	Pg_EXPOSE_SOURCE (0x02 << 8)
#define	Pg_REPBM_ALTERNATE	(0x10ul<<16)

/*
 * Stroke and Fill rules
 *	PgDrawPolygon
 */
#define 	Pg_POLY_STROKE				Pg_DRAW_STROKE
#define 	Pg_POLY_STROKE_CLOSED		Pg_DRAW_STROKE | Pg_CLOSED
#define 	Pg_POLY_FILL				Pg_DRAW_FILL
#define		Pg_POLY_RELATIVE			Pg_RELATIVE
#define		Pg_REL_POLY_STROKE			(Pg_POLY_STROKE | Pg_POLY_RELATIVE)
#define		Pg_REL_POLY_STROKE_CLOSED	(Pg_POLY_STROKE_CLOSED | Pg_POLY_RELATIVE)
#define		Pg_REL_POLY_FILL			(Pg_POLY_FILL | Pg_POLY_RELATIVE)

/*
 * Draw arc flags
 *	PgDrawArc 
 */
#define Pg_ARC_CHORD	(0x00 << 8)
#define Pg_ARC_PIE		(0x10 << 8)
#define Pg_ARC			(0x20 << 8)
#define	Pg_ARC_FILL		Pg_DRAW_FILL
#define	Pg_ARC_STROKE	Pg_DRAW_STROKE

#define		Pg_ARC_STROKE_CHORD		Pg_DRAW_STROKE | Pg_ARC_CHORD
#define		Pg_ARC_STROKE_PIE		Pg_DRAW_STROKE | Pg_ARC_PIE
#define		Pg_ARC_STROKE_ARC		Pg_DRAW_STROKE | Pg_ARC
#define		Pg_ARC_FILL_CHORD		Pg_DRAW_STROKE | Pg_ARC_CHORD
#define		Pg_ARC_FILL_PIE			Pg_DRAW_FILL | Pg_ARC_PIE

/*
 * Line Joins - only relevant for lines thicker than 1 pixel
 *	PgSetLineJoin
 */	 
#define 	Pg_MITER_JOIN				0x00		/* default */
#define 	Pg_ROUND_JOIN				0x01
#define 	Pg_BEVEL_JOIN				0x02
#define 	Pg_QROUND_JOIN				0x03
#define		Pg_BUTT_JOIN				0x04

/*
 * Line Caps - only relevant for lines thicker than 1 pixel
 *	PgSetLineCap
 */	 
#define 	Pg_BUTT_CAP					0x00		/* default */
#define 	Pg_ROUND_CAP				0x01
#define 	Pg_SQUARE_CAP				0x02
#define 	Pg_POINT_CAP				0x03

/*
 * Line dashing flags
 *	PgSetLineDash 
 */
#define		Pg_DASH_INVERT				0x40
#define		Pg_DASH_SLOPE_ADJ			0x80

/*
 * Text Underline Flags
 */

#define Pg_DOUBLE_UNDERLINE	0x10

/*
 * Extended Text Flags
 * 0x01 is reserved for _PgGC_ExtendedFlagsSet.
 */
#define Pg_TEXT_SIMPLE_METRICS  0x02

/*
 * Text Justification Flags
 */

#define Pg_TEXT_UTF16CHAR (0x04 << 8)

/*******************************************************/
/* Fix a misunderstanding.                             */
/* It is either UTF-8, UTF-16 (UCS2), or UTF-32 (UCS2) */
/*******************************************************/

#define       Pg_TEXT_UTF2CHAR Pg_TEXT_UTF16CHAR  /* This is wrong, but history prevails. */
/*#define     Pg_TEXT_UTF32CHAR       (0x02 << 8)*/

#define       Pg_TEXT_WIDECHAR        (Pg_TEXT_UTF16CHAR)
/*#define     Pg_TEXT_VWIDECHAR       (Pg_TEXT_UTF32CHAR) */
 
/*#define	Pg_TEXT_TERMCHAR	(0x06 << 8) */
#define	Pg_TEXT_SIZE_HINT	(0x02 << 8)
#define	Pg_TEXT_AREA		(0x08 << 8)

#define	Pg_TEXT_ELLIPSIS		0x01
#define	Pg_TEXT_ELLIPSIS_MIDDLE	0x02
#define	Pg_TEXT_ELLIPSIS_INVERT	0x04

#define Pg_TEXT_LEFT	(0x10 << 8)
#define Pg_TEXT_RIGHT	(0x20 << 8)
#define Pg_TEXT_CENTER	( Pg_TEXT_LEFT | Pg_TEXT_RIGHT )
#define Pg_TEXT_TOP		(0x40 << 8)
#define Pg_TEXT_BOTTOM	(0x80 << 8)
#define Pg_TEXT_MIDDLE	( Pg_TEXT_TOP | Pg_TEXT_BOTTOM )

typedef struct {
	unsigned int			c:16;
	unsigned int			FGColor:4;
	unsigned int			BGColor:4;
	unsigned int			Highlight:1;
	unsigned int			Blinking:1;
	unsigned int			Underline:1;
	unsigned int			ReverseVideo:1;
	unsigned int			Italic:1;
	unsigned int			Bold:1;
	unsigned int			User:1;
	unsigned int			Selected:1;
} PgTermChar_t;

/*
 * Color compare operators, Photon.mach specific
 *	PgSetAuxFn
 */
#define		Pg_OVRFN_FALSE				0		/* default */
#define		Pg_OVRFN_TRUE				1		/* don't draw */
#define		Pg_OVRFN_GE					2
#define		Pg_OVRFN_LT					3
#define		Pg_OVRFN_NE					4
#define		Pg_OVRFN_EQ					5
#define		Pg_OVRFN_LE					6
#define		Pg_OVRFN_GT					7

typedef struct {
	short		x1, x2;
	short		y;
} PgSpan_t;

typedef struct {
	signed char		x, y;
} PgTinyPoint_t;

/*
 * Cursor definition structure (for use with PgSetCursorBitmap)
 * An array of upto 2 of these may be used to define a cursor
 */
typedef struct {
	char		*Image;
	PhPoint_t	Size;
	PhPoint_t	Offset;
	PgColor_t	Color;
	char		BytesPerLine;
	char		Spare[3];
} PgCursorDef_t;

/* Limits */
#define _Pg_MAX_FONT_LEN		MAX_FONT_TAG
#define _Pg_MAX_SHMEM_NAME_LEN	32
#define _Pg_MAX_DATA_MX			63
#define _Pg_MAX_DASH_LIST		16
#define _Pg_MAX_PALETTE			256

/*
 * Graphics context "set" flags. (short)
 */
#define	_PgGC_DitherSet				0x0001
#define	_PgGC_TranspSet				0x0002
#define _PgGC_ScaleSet				0x0004
#define _PgGC_TranslationSet		0x0008
#define _PgGC_RotationSet			0x0010
#define _PgGC_UserClipSet			0x0020
#define _PgGC_SoftPaletteSet		0x0040
#define _PgGC_AuxClipSet			0x0080
#define	_PgGC_XORColorSet			0x0100
#define _PgGC_AlphaSet				0x0200
#define _PgGC_ChromaSet				0x0400
#define _PgGC_GradientSet			0x0800
#define _PgGC_ColorModelSet			0x1000

#define _PgGC_ExtendedFlagsSet		0x0001

#define Pg_CHROMA_VALID				0x80000000	

/*
 * Alpha OP defines.
 */
/* Alpha Mode */
#define Pg_ALPHA_VALID				0x80000000			/* Alpha is valid...apply it */
#define	Pg_ALPHA_OP_TEST			0x00010000			/* Doing a test, not a blend operation */
#define Pg_ALPHA_OP_SRC_PIXEL		0					/* As is retrieved from the pixel */
#define Pg_ALPHA_OP_SRC_GLOBAL		0x00040000			/* As is equal to the global alpha value */
#define Pg_ALPHA_OP_SRC_MAP			0x00080000			/* As is retrieved from the alpha map */
#define Pg_ALPHA_OP_SRC_GRADIENT	0x00100000			/* As is retrieved from the alpha gradient */
#define Pg_ALPHA_OP_DST_PIXEL		0					/* Ad is retrieved from the pixel */
#define Pg_ALPHA_OP_DST_GLOBAL		0x00020000			/* Ad is equal to the global alpha value */
#define Pg_ALPHA_OP_DEST_PIXEL		Pg_ALPHA_OP_DST_PIXEL
#define Pg_ALPHA_OP_DEST_GLOBAL		Pg_ALPHA_OP_DST_GLOBAL

/* Alpha Blends -- Comments give examples of usage in an ARGB color model; d means destination and s means source,
 * 	so Rd means the Red component of the destination pixel.
 * 
 * formula for alpha blending
 * 
 * src_multiplier is one of Pg_BLEND_SRC_xxx
 * dst_multiplier is one of Pg_BLEND_DST_xxx
 * 
 * Sm = src_pixel * src_multiplier
 * Dm = dst_pixel * dst_multiplier
 * dst_pixel = Sm + Dm
 */

/* Source pixel is multiplied by.... */
#define Pg_BLEND_SRC_MASK					0x0000FF00

#define Pg_BLEND_SRC_0						0x0000		/* (0,0,0,0) */
#define Pg_BLEND_SRC_1						0x0100		/* (1,1,1,1) */
#define Pg_BLEND_SRC_D						0x0200		/* (Ad,Rd,Gd,Bd) */
#define Pg_BLEND_SRC_1mD 					0x0300		/* (1-Ad,1-Rd,1-Gd,1-Bd) */
#define Pg_BLEND_SRC_As						0x0400		/* (As,As,As,As) */
#define Pg_BLEND_SRC_1mAs					0x0500		/* (1-As,1-As,1-As,1-As) */
#define Pg_BLEND_SRC_Ad						0x0600		/* (Ad,Ad,Ad,Ad) */
#define Pg_BLEND_SRC_1mAd					0x0700	    /* (1-Ad,1-Ad,1-Ad,1-Ad) */
#define Pg_BLEND_SRC_A1As					0x0800		/* (1,As,As,As) */
#define Pg_BLEND_SRC_1mA1As					0x0900		/* (1-1,1-As,1-As,1-As) */
#define Pg_BLEND_SRC_A1Ad					0x0A00		/* (1,Ad,Ad,Ad) */
#define Pg_BLEND_SRC_1mA1Ad					0x0B00		/* (1-1,1-Ad,1-Ad,1-Ad) */
#define Pg_BLEND_SRC_A0As					0x0C00		/* (0,As,As,As) */
#define Pg_BLEND_SRC_1mA0As					0x0D00		/* (1-0,1-As,1-As,1-As) */
#define Pg_BLEND_SRC_A0Ad					0x0E00		/* (0,Ad,Ad,Ad) */
#define Pg_BLEND_SRC_1mA0Ad					0x0F00		/* (1-0,1-Ad,1-Ad,1-Ad) */

#define Pg_BLEND_SRC_ZERO					Pg_BLEND_SRC_0
#define Pg_BLEND_SRC_ONE					Pg_BLEND_SRC_1
#define Pg_BLEND_SRC_DST_COLOR				Pg_BLEND_SRC_D
#define Pg_BLEND_SRC_ONE_MINUS_DST_COLOR	Pg_BLEND_SRC_1mD
#define Pg_BLEND_SRC_SRC_ALPHA				Pg_BLEND_SRC_As
#define Pg_BLEND_SRC_ONE_MINUS_SRC_ALPHA 	Pg_BLEND_SRC_1mAs
#define Pg_BLEND_SRC_DST_ALPHA				Pg_BLEND_SRC_Ad
#define Pg_BLEND_SRC_ONE_MINUS_DST_ALPHA 	Pg_BLEND_SRC_1mAd

/* destination pixel is multiplied by.... */
#define Pg_BLEND_DST_MASK					0x000000FF

#define Pg_BLEND_DST_0						0x00		/* (0,0,0,0) */
#define Pg_BLEND_DST_1						0x01		/* (1,1,1,1) */
#define Pg_BLEND_DST_S						0x02		/* (Ad,Rd,Gd,Bd) */
#define Pg_BLEND_DST_1mS 					0x03		/* (1-Ad,1-Rd,1-Gd,1-Bd) */
#define Pg_BLEND_DST_As						0x04		/* (As,As,As,As) */
#define Pg_BLEND_DST_1mAs					0x05		/* (1-As,1-As,1-As,1-As) */
#define Pg_BLEND_DST_Ad						0x06		/* (Ad,Ad,Ad,Ad) */
#define Pg_BLEND_DST_1mAd					0x07	    /* (1-Ad,1-Ad,1-Ad,1-Ad) */
#define Pg_BLEND_DST_A1As					0x08		/* (1,As,As,As) */
#define Pg_BLEND_DST_1mA1As					0x09		/* (1-1,1-As,1-As,1-As) */
#define Pg_BLEND_DST_A1Ad					0x0A		/* (1,Ad,Ad,Ad) */
#define Pg_BLEND_DST_1mA1Ad					0x0B		/* (1-1,1-Ad,1-Ad,1-Ad) */
#define Pg_BLEND_DST_A0As					0x0C		/* (0,As,As,As) */
#define Pg_BLEND_DST_1mA0As					0x0D		/* (1-0,1-As,1-As,1-As) */
#define Pg_BLEND_DST_A0Ad					0x0E		/* (0,Ad,Ad,Ad) */
#define Pg_BLEND_DST_1mA0Ad					0x0F		/* (1-0,1-Ad,1-Ad,1-Ad) */

#define Pg_BLEND_DST_ZERO					Pg_BLEND_DST_0
#define Pg_BLEND_DST_ONE					Pg_BLEND_DST_1
#define Pg_BLEND_DST_SRC_COLOR				Pg_BLEND_DST_S
#define Pg_BLEND_DST_ONE_MINUS_SRC_COLOR	Pg_BLEND_DST_1mS
#define Pg_BLEND_DST_SRC_ALPHA				Pg_BLEND_DST_As
#define Pg_BLEND_DST_ONE_MINUS_SRC_ALPHA 	Pg_BLEND_DST_1mAs
#define Pg_BLEND_DST_DST_ALPHA				Pg_BLEND_DST_Ad
#define Pg_BLEND_DST_ONE_MINUS_DST_ALPHA 	Pg_BLEND_DST_1mAd

/* Alpha Tests									Pixels are written in destination */
#define Pg_TEST_NEVER				0x00		/* Never */
#define Pg_TEST_ALWAYS				0x01		/* Always */
#define Pg_TEST_LESS_THAN			0x02		/* if As < Ad */
#define Pg_TEST_LESS_THAN_OR_EQUAL	0x03		/* if As <= Ad */
#define Pg_TEST_EQUAL				0x04		/* if As == Ad */
#define Pg_TEST_GREATER_THAN_OR_EQUAL 0x05		/* if As >= Ad */
#define Pg_TEST_GREATER_THAN		0x06		/* if As > Ad */
#define Pg_TEST_NOT_EQUAL			0x07		/* if As != Ad */

/*
 * The graphics context
 */
typedef	struct _Pg_common_gc {
	PgColor_t		primary, secondary;
	char			dither_pattern[8];
	char			transp_pattern[8];
	unsigned long	flags;
	long			spare;
} _PgCommonGC_t;

typedef struct _Pg_stroke_gc {
	_PgCommonGC_t	com;
	long			width;
	char			join;
	char			cap;
	char			spareB[2];
	char			dash_list[_Pg_MAX_DASH_LIST];
	long			dash_flags;
	long			dash_scale;
	long			spare[4];
} _PgStrokeGC_t;

typedef struct _Pg_fill_gc {
	_PgCommonGC_t	com;
} _PgFillGC_t;

typedef struct _Pg_text_gc {
	_PgCommonGC_t	com;
	char			font[_Pg_MAX_FONT_LEN];
	PgColor_t		underline[2];
	unsigned short	underline_flags;
	unsigned short	extended_flags;
    long            uline; /* This could be smaller */
} _PgTextGC_t;

typedef struct _Pg_map {
	PhDim_t	dim;
	short unsigned bpl;
	short unsigned bpp;
	char unsigned *map;
} PgMap_t;


typedef struct _Pg_gradient {
	int gradient_type;		/* Pg_GRAD_NOGRADIENT, Pg_GRAD_VECTOR, Pg_GRAD_RADIAL etc. */
	int transition_type;	/* Pg_GRAD_TABLE, Pg_GRAD_LINEAR etc. */
	int rotation;			/* Rotation of the gradient band in degrees. 0 means that the gradient */
							/* band is perpendicular to the gradient vector. Rotation only effects */
							/* vector gradients. */
    PhPoint_t start_point;	/* The start-point of the gradient vector or the center for radial gradients. */
							/* The effective start_point of the gradient vector is automatically recomputed */
							/* if a non-zero rotation is specified. */
    PhPoint_t end_point;	/* The end-point of the gradient vector  / end.x == radius for radial gradients */
	PgColor_t start_color;	/* Color at the start-point of the gradient vector. */
	PgColor_t end_color;	/* Color at the end-point of the gradient vector. */
	int table_size;			/* Number of entries in the transition table. */
	char unsigned * transition_table; /* table[i-1] = percentage of end-color at the start of the i-th color segment. 0% - 100% */
} PgGradient_t;


typedef struct _Pg_alpha {
	long unsigned	alpha_op;
	PgMap_t		src_alpha_map;
	PgGradient_t	src_alpha_gradient;
	char unsigned	src_global_alpha;
	char unsigned	dest_global_alpha;
	unsigned char	spare[2];  /* Align to word boundary */
	unsigned int	spare2[12]; /* Pad to the full 104 byte sizeof */
} PgAlpha_t;


typedef struct _Pg_chroma {
	int unsigned		color;
	long unsigned		op;
} _PgChroma_t;

typedef _PgChroma_t PgChroma_t;

typedef struct _Pg_palette {
	long		palette_id;			/* Palette identifier */
	PgColor_t	*palette;			/* Palette colors */
	unsigned short	num_colors;			/* Number of colors in the palette */
	unsigned short	start_color;			/* First index the palette starts at */
	unsigned short	palette_flags;			/* Palette flags */
	long		palette_tag;			/* Palette tag - used for remote caching */
	unsigned long	palette_max;			/* Palette maximum */
	unsigned long	palette_changed;		/* palette change counter */
} _PgPalette_t;

typedef struct _Ph_Draw_Context PhDrawContext_t;

#define PhGC_DONT_RESET_PLANE_MASK	0x00000001

typedef struct Ph_gc {
	int		dc_ref_count;			/* Number of DC's referencing the GC */
	_PgStrokeGC_t	stroke;				/* Stroke properties */
	_PgFillGC_t	fill;				/* Fill properties */
	_PgTextGC_t	text;				/* Text properties */
	PgAlpha_t	alpha;				/* Alpha properties */
	_PgChroma_t	chroma;				/* Chroma properties */
	_PgPalette_t	palette;			/* Palette Properties */
	unsigned long	plane_mask;			/* Plane mask */
	unsigned short	draw_mode;			/* Raster operation */
	uint32_t	color_model_id;			/* Color model */
	PhPoint_t	translation;			/* Translation */
	PhTile_t	*clip_tiles;			/* Clipping rectangles */
	unsigned short	max_clip_rects;			/* Maximum number of clipping rectangles */
	PhRect_t	*user_clip_rects;		/* User clipping rectangles */
	unsigned short	n_user_clip_rects;
	unsigned short	max_user_clip_rects;
	PhTile_t	*user_clip_tiles;	
	PhRect_t	aux_clip_rect;			/* Aux clip rect */
	int		aux_clip_valid;			/* Is the aux clip rect valid? */
	PhRect_t	total_clip_extent;		/* Sum of all clip rects */
	PhTile_t	*cur_clip_tiles;
	unsigned long	context_set_flags;
	unsigned long	control_flags;
	uint32_t	spare_array[9];
} PhGC_t;

/* Simple font metrics */
/* This is also defined in PhInternal.h ??? */
struct _Ph_font_widths {
	char			face[20];
	PhRect_t		extent;
	ushort_t		valid;
	ushort_t		ascii_offset;
	ushort_t		ascii_length;
	char			widths[256];
};

struct _Ph_font_widths2 {
	char			face[20];
	PhRect_t		extent;
	ushort_t		valid;
	ushort_t		ascii_offset;
	ushort_t		ascii_length;
	char			*widths;
};

#ifdef NEW_FONT_CACHE
typedef struct {
	int 		CurFontRangeL;
	int			CurFontRangeH;
	char 		*ScriptBasePtr;
	char 		*ScriptPtr;
	char 		*ScriptRuleFlags;
	int 		ScriptNRules;
	int 		ScriptSize;
} FontAliasInfoType;
#endif

/* Graphics library state */
typedef struct _Ph_g_info {
	unsigned long				cmd_buffer_size;
	long						*cmd_buffer;
	long						*cmd_ptr;
	long						*cmd_base_ptr;
	unsigned 					cmd_buf_limit; 
	unsigned 					data_buf_len;
	#ifdef __QNXNTO__
		struct iovec 			data_mx[_Ph_MAX_DATA_MX + 1];
	#else
		struct _mxfer_entry 	data_mx[_Ph_MAX_DATA_MX + 1];
	#endif
	unsigned					mx_offsets[_Ph_MAX_DATA_MX + 1];
	unsigned					n_data_mx;
	unsigned					context_len;
	unsigned					n_fonts;
#ifdef NEW_FONT_CACHE
	long						spare[2];
	uint32_t					cur_cmd_len;
	FontAliasInfoType			*falias_ctrl;
	struct _Ph_font_widths2		*fonts;
#else
	long						spare[3];
	uint32_t					cur_cmd_len;
	struct _Ph_font_widths		**fonts;
#endif
    PhRid_t         rid;                    /* Draw events will be emitted from this region */
    PhRid_t         target_rid;             /* Draw events are to go to this rid */
    pid_t           target_pid;             /* Service messages are going to this pid */
} __Ph_g_info_t; 

/*
 *  Shared memory reference record structure (embedded in the draw buffer)
 */

typedef struct {
	short			rec_size;
	short			rec_type;
	unsigned long	offset;
	unsigned long	limit;
	unsigned long	obj_size;
	long			spare;
	char			name[_Pg_MAX_SHMEM_NAME_LEN];
} _PgShmemRefStruct;

#define	Pg_XADDR_SHMEM		0
#define	Pg_XADDR_INLINE		1

/* 
 * Draw command opcodes (embedded in the draw buffer)
 */
 
/* #define	Pg_CMD_ADDR_EXTENDED		0x00010000 */
/* #define	Pg_CMD_ADDR_INDIRECT		0x00020000 */

#define	Pg_CMD_CMD_SIZE_MASK		0xFFFC0000
#define	Pg_CMD_CAH_COUNT_MASK		0x00030000
#define	Pg_CMD_CAH_COUNT_UNIT		0x00010000
#define	Pg_CMD_CAH_COUNT_1			0x00010000
#define	Pg_CMD_CAH_COUNT_2			0x00020000
#define	Pg_CMD_CAH_COUNT_3			0x00030000

typedef struct {
	unsigned long		flags;
	unsigned short		inline_offset;
	unsigned short		inline_size;
	char				*shmem_name;
	unsigned long		shmem_limit;
	unsigned long		shmem_offset;
	unsigned long		srce_tag;
	unsigned long		srce_offset;
	unsigned long		srce_size;
} CAHinfo_t;

#define	Pg_CAH_RECORD_SIZE_MASK		0x0000003F
#define	Pg_CAH_INLINE_OFF_SIZE		0x00000040
#define	Pg_CAH_SHMEM_NAME			0x00000080
#define	Pg_CAH_SHMEM_LIMIT			0x00000100
#define	Pg_CAH_SHMEM_OFFSET			0x00000200
#define	Pg_CAH_SRCE_TAG				0x00000400
#define	Pg_CAH_SRCE_OFFSET			0x00000800
#define	Pg_CAH_SRCE_SIZE			0x00001000
#define	Pg_CAH_RELAY_TAGGED			0x00002000
#define Pg_CAH_POINTER				0x00004000 /* Usefull for renderers that are 
												  in the apps address space (eg: memory contexts) */




/*
 *  General set opcodes
 */

#define	Pg_END_OF_DRAW				0x00
#define	Pg_SET_DEFAULT_STATE		0x01
#define Pg_SET_DRAW_MODE			0x02
#define Pg_SET_PLANE_MASK			0x03
#define Pg_SET_XDRAW_MODE			0x04
#define	Pg_SET_USER_CLIP			0x06
#define	Pg_SET_AUX_CLIP				0x07
#define	Pg_SET_PALETTE				0x08
#define	Pg_SET_TRANSLATION			0x09
#define	Pg_SET_SCALE				0x0A
#define	Pg_SET_ROTATION				0x0B
#define Pg_SET_EXCLUSION_CLIP		0x0C
#define Pg_SET_ALPHA				0x0D
#define Pg_SET_CHROMA_MODE			0x0E
#define Pg_INCOMPLETE_STREAM		0x0F

/*
 *  Stroke set opcodes
 */

#define	Pg_SET_STROKE_COLOR			0x10
#define	Pg_SET_STROKE_XOR_COLOR		0x11
#define	Pg_SET_STROKE_DITHER		0x12
#define	Pg_SET_STROKE_TRANSP		0x13
#define	Pg_SET_STROKE_WIDTH			0x14
#define	Pg_SET_STROKE_CAP			0x15
#define	Pg_SET_STROKE_JOIN			0x16
#define	Pg_SET_STROKE_DASH			0x17

/*
 *  Extension draw commands.
 */
#define Pg_TARGET_STREAM			0x18
#define Pg_DRAW_GRADIENT			0x19
#define Pg_SYNC						0x1a
#define Pg_SWAP_DISPLAY				0x1b
#define Pg_DRAW_XBEVELBOX			0x1c
#define Pg_SET_TARGET_TRANSLATION	0x1d	/* This translation is "sticky" on the target */
#define Pg_SET_COLOR_MODEL			0x1e

#define Pg_PLUGIN_STREAM			0xD0
#define Pg_ENDIAN_TEST				0xD5

#define Pg_SWAP_BLIT				0x00000001	/* Blit after moving the crtc */
#define Pg_SWAP_VSYNC				0x00000020	/* Wait For Vsync during swap */

/*
 *  Fill set opcodes
 */
#define	Pg_SET_FILL_COLOR			0x20
#define	Pg_SET_FILL_XOR_COLOR		0x21
#define	Pg_SET_FILL_DITHER			0x22
#define	Pg_SET_FILL_TRANSP			0x23

/*
 *  Text (and bitmap) set opcodes
 */
#define	Pg_SET_TEXT_COLOR			0x30
#define	Pg_SET_TEXT_XOR_COLOR		0x31
#define	Pg_SET_TEXT_DITHER			0x32
#define	Pg_SET_TEXT_TRANSP			0x33
#define	Pg_SET_TEXT_FONT			0x34
#define	Pg_SET_TEXT_UNDERLINE		0x35
#define Pg_SET_TEXT_EXTENDED_FLAGS	0x36

/*
 *  Simple draw opcodes
 */
#define	Pg_DRAW_POINT				0x40
#define	Pg_DRAW_POINT_ARRAY			0x41
#define	Pg_DRAW_LINE				0x42
#define	Pg_DRAW_TEXT				0x43
#define	Pg_DRAW_BITMAP				0x44
#define	Pg_DRAW_IMAGE				0x45
#define	Pg_DRAW_BITBLT				0x46
#define	Pg_DRAW_BITBLIT				0x46
#define	Pg_DRAW_GRID				0x47
#define	Pg_DRAW_TREND				0x48
#define	Pg_DRAW_VECTOR				0x49
#define	Pg_OFFSCREEN_BLIT			0x4A
#define Pg_MOVE_DISPLAY				0x4D
#define	Pg_DRAW_GETIMAGE			0x4F

/*
 *  Fill and/or Stroke draw opcodes
 *   OR with Pg_DRAW_FILL, Pg_DRAW_STROKE or Pg_DRAW_FILL_STROKE
 */
/* are actually in 0x50 - 0x77 range
 * 0x_8 - 0x_f available in each range... 
 */

#define	Pg_DRAW_POLYGON				0x40
#define	Pg_DRAW_RECT				0x41
#define	Pg_DRAW_RRECT				0x42
#define	Pg_DRAW_ELLIPSE				0x43
#define	Pg_DRAW_ARC					0x44
#define	Pg_DRAW_BEVELBOX			0x45
#define	Pg_DRAW_SPAN				0x46
#define	Pg_DRAW_BEZIER				0x47

#define	Pg_DRAW_STROKE				0x10
#define	Pg_DRAW_FILL				0x20
#define	Pg_DRAW_FILL_STROKE			(Pg_DRAW_FILL | Pg_DRAW_STROKE)
#define	Pg_DRAW_STROKE_FILL			Pg_DRAW_FILL_STROKE


#define Pg_DELETE_CURSOR			0x80
#define Pg_SET_CURSOR_POSITION		0x81
#define Pg_SET_CURSOR_CHAR			0x82
#define Pg_SET_CURSOR_BITMAP		0x83
#define Pg_SET_DRAG_CURSOR			0x84

	
/*
 * Printer drawstream commands.
 */
#define Pg_PRINTER_CMD				0xF1

/*
 *	What to test before drawing
 */
#define	Pg_TEST_STROKE				(Pg_DRAW_STROKE)
#define	Pg_TEST_FILL				(Pg_DRAW_FILL)
#define	Pg_TEST_FILL_STROKE			(Pg_DRAW_FILL | Pg_DRAW_STROKE)
#define Pg_TEST_TEXT				1		/* 0x0100	 0x1 */
#define	Pg_TEST_BITMAP				2		/* 0x0200	 0x2 */
/* #define	Pg_TEST_PALETTE				0x1000	 unused?? */

#define	Pg_SETGAMMA_Factor			0x0001
#define	Pg_SETGAMMA_CFactor			0x0002
#define	Pg_SETGAMMA_CBlack			0x0004
#define	Pg_SETGAMMA_CWhite			0x0008
#pragma pack()


typedef struct Ph_grafx_detail
{
	ulong_t 	valid_fields;
	ulong_t		reserved;
	ulong_t		video_opt;
	ulong_t		driver_opt;
	ulong_t		gui_opt;
	ulong_t		cardspec_opt;
	ulong_t 	card_type;
	ulong_t 	card_sub_type;
	PhPoint_t	presolution;
	PhPoint_t	vresolution;
	ulong_t		vram_size;
	ushort_t	num_cursor;
	ushort_t	num_palette;
	ulong_t		pointbuf_size;
	ulong_t		workspace_size;
	ulong_t		spareA[2];
	ulong_t		bytes_per_line;
	ulong_t		bits_per_pixel;
	uchar_t		bits_blue, bits_green, bits_red, bits_overlay;
	uchar_t		bpos_blue, bpos_green, bpos_red, bpos_overlay;
	uchar_t		dac_size;
	uchar_t		spareC[3];
	ulong_t		spareB[2];
} PhGrafxDetail_t;

#define	Ph_GFXVAL_VOPT			0x00000001
#define	Ph_GFXVAL_DOPT			0x00000002
#define	Ph_GFXVAL_GOPT			0x00000004
#define	Ph_GFXVAL_COPT			0x00000008
#define	Ph_GFXVAL_CARDTYPE		0x00000010
#define	Ph_GFXVAL_CARDSUBTYPE	0x00000020
#define	Ph_GFXVAL_PRES			0x00000100
#define	Ph_GFXVAL_VRES			0x00000200
#define	Ph_GFXVAL_VRAMSIZE		0x00000800
#define	Ph_GFXVAL_NCURSOR		0x00001000
#define	Ph_GFXVAL_NPALETTE		0x00002000
#define	Ph_GFXVAL_POINTBS		0x00004000
#define	Ph_GFXVAL_WORKSPACES	0x00008000
#define	Ph_GFXVAL_BPL			0x00100000
#define	Ph_GFXVAL_BPP			0x00200000
#define	Ph_GFXVAL_BITPOS		0x00400000
#define	Ph_GFXVAL_DACSIZE		0x00800000

/* video_opt */
#define	Ph_GFXV_MONOCHROME		0x00000001
#define	Ph_GFXV_PALETTE16		0x00000002
#define	Ph_GFXV_PALETTE256		0x00000004
#define	Ph_GFXV_DIRECT			0x00000010
#define	Ph_GFXV_OVERLAY			0x00000020
#define	Ph_GFXV_VIDEO_READABLE	0x00001000
#define	Ph_GFXV_NONINTERLACED	0x00002000

/* driver_opt */
#define	Ph_GFXD_VPANNING		0x00000001
#define	Ph_GFXD_HARDROT			0x00000002
#define	Ph_GFXD_SCALEING		0x00000004
#define	Ph_GFXD_DITHERSTROKE	0x00000008

/* gui_opt */
#define	Ph_GFXG_HWCURSOR		 0x00000001
#define	Ph_GFXG_HWBITBLT		 0x00000002
#define	Ph_GFXG_MASKBLIT		 0x00000004
#define	Ph_GFXG_OFFSCREEN		 0x00000008
#define	Ph_GFXG_DMXOR			 0x00000010
#define	Ph_GFXG_DMANDOR			 0x00000020
#define	Ph_GFXG_DMEXTENDED		 0x00000040
#define Ph_GFXG_HWBITBLT_CHROMA  0x00000080
#define Ph_GFXG_HWBITBLT_STRETCH 0x00000100
#define Ph_GFXG_ALPHA			 0x00000200
#define Ph_GFXG_CHROMA			 0x00000400
#define Ph_GFXG_TERN_ROPS		 0x00000800
#define Ph_GFXG_OVERLAY			 0x00001000

typedef struct Ph_grafx_detail_region_data
{
	PhRegionDataHdr_t	hdr;
	PhGrafxDetail_t		detail;
} PhGrafxDetailRegionData_t;

typedef struct PgVidMem
{
	int type;			/*How Memory is to be interpreted (8-bit palette, 16-bit Direct Color, etc) */
	int bpl;			/*Bytes Per Line */
	int bpp;			/*Bits Per Pixel */
	PhDim_t size;		/*Width and Height of the Video Memory */
	unsigned long tag;	/*ID, do not mess with this!  The Video Driver sets it up and requires it unchanged! */

	volatile unsigned char *vm_ptr8;		/*8-bit pointer to Video memory for this area */
	volatile unsigned short *vm_ptr16;		/*16-bit pointer to Video memory for this area */
	volatile unsigned long *vm_ptr32;		/*32-bit pointer to Video memory for this area */
} PgVidMem_t;

typedef struct pg_dll {
	int dll_tag;
	int gid;
	} PgDll_t;

typedef struct PhImage
{
	int			type;			/* image type ( milti, pseudo, direct ) */
								/* bitmap type (backfilled, transparent fill)*/
	ulong_t		image_tag;		/* image data tag */
	int			bpl;			/* image bytes per line */
	PhDim_t		size;			/* image size */
	ulong_t		palette_tag;	/* palette data tag */
	int			colors;			/* number of colors in image */
	PgAlpha_t	*alpha;			/* image alpha map used if src alpha map option enabled */
	PgColor_t	transparent;	/* color to mask out when drawing */
	char		format;			/* graphic format */
	char		flags;			/* image flags */
	char 		ghost_bpl;		/* bpl for ghosting bitmap ghost_bitmap */
	char		spare1;			/* reserved */
	char		*ghost_bitmap;	/* transparency bitmap for ghosting a image */
	int			mask_bpl;		/* bytes per line for transparency mask */
	char		*mask_bm;		/* pointer to transparency mask bitmap */
	PgColor_t	*palette;		/* image palette */
	char		*image;			/* image bitmap data */
} PhImage_t;

/* PhImage_t flags bits */
#define	Ph_RELEASE_IMAGE				0x01
#define Ph_RELEASE_PALETTE				0x02
#define Ph_RELEASE_TRANSPARENCY_MASK	0x04
#define	Ph_RELEASE_GHOST_BITMAP			0x08
#define Ph_RELEASE_ALPHA				0x10
#define	Ph_RELEASE_IMAGE_ALL			0x1F
#define Ph_USE_TRANSPARENCY				0x80

#ifndef __PH_GLIB_PG_GRADIENT_H_INCLUDED
#include <photon/PgGradient.h>
#endif

typedef struct {
	unsigned		mode;
	int 			xres, yres, refresh;
	unsigned		flags;
	unsigned long   reserved[22];
}	PgDisplaySettings_t;

	typedef struct pg_VideoModeInfo
PgVideoModeInfo_t;
	struct pg_VideoModeInfo
		{
		unsigned short width;
		unsigned short height;
		unsigned short bits_per_pixel;
		unsigned short bytes_per_scanline;
		unsigned long type;
		unsigned long mode_capabilities1;
		unsigned long mode_capabilities2;
		unsigned long mode_capabilities3;
		unsigned long mode_capabilities4;
		unsigned long mode_capabilities5;
		unsigned long mode_capabilities6;
		unsigned char refresh_rates[20];
		};

/* Capabilities Per Mode Defines */

/* 1 - General Capabilities */
#define PgVM_MODE_CAP1_OFFSCREEN		0x00000001	/* There is Offscreen Support */
#define PgVM_MODE_CAP1_2D_ACCEL		0x00000002	/* The 2D accelerator works in this mode */
#define PgVM_MODE_CAP1_3D_ACCEL		0x00000004	/* The 3D accelerator works in this mode */
#define PgVM_MODE_CAP1_VIDEO_OVERLAY 0x00000008	/* Video Overlay is available */
#define PgVM_MODE_CAP1_LINEAR		0x00000010	/* Flat Memory */
#define PgVM_MODE_CAP1_DOUBLE_BUFFER	0x00000020	/* This mode can be Double Buffered */
#define PgVM_MODE_CAP1_TRIPLE_BUFFER 0x00000040	/* This mode can be Triple Buffered */
#define PgVM_MODE_CAP1_REFRESH_RATE  0x00000080 /* This mode supports multiple refresh rates */

/* 2- 2D Acceleration Capabilities */
#define PgVM_MODE_CAP2_BITBLT		0x00000001	/* HW BitBlts */
#define PgVM_MODE_CAP2_RECTANGLE		0x00000002	/* HW Rectangles */
#define PgVM_MODE_CAP2_LINES			0x00000004	/* HW Lines */
#define PgVM_MODE_CAP2_POLYGONS		0x00000008	/* HW Polygons */
#define PgVM_MODE_CAP2_FULL_ROPS		0x00000010	/* All 256 ROPS in HW */
#define PgVM_MODE_CAP2_PATTERN		0x00000020	/* HW Stipples, Color Expansion, etc. */
#define PgVM_MODE_CAP2_CHROMA		0x00000040	/* HW Chroma Key */
#define PgVM_MODE_CAP2_ALPHA_BLEND	0x00000080	/* HW Alpha Blending */
#define PgVM_MODE_CAP2_ALPHA_TEST	0x00000100	/* HW Alpha Testing */
#define PgVM_MODE_CAP2_PLANE_MASK	0x00000200	/* HW Plane Mask */
#define PgVM_MODE_CAP2_IMAGE_CONVERSION	0x00000400	/* HW Image Conversion */
#define PgVM_MODE_CAP2_DWORD			0x00000800	/* Accelerated DWORD Alignment */
#define PgVM_MODE_CAP2_WORD			0x00001000	/* Accelerated WORD Alignment */
#define PgVM_MODE_CAP2_BYTE			0x00002000	/* Accelerated BYTE Alignment */
#define PgVM_MODE_CAP2_SCALED_BLIT  0x00004000  /* HW scaled blit */
#define PgVM_MODE_CAP2_SYSTEM_RAM		0x40000000	/* Transfers to and from System Ram */
#define PgVM_MODE_CAP2_VIDEO_RAM		0x80000000	/* Transfers to and from Video Ram */

/* 3 - 3D Acceleration Capabilities */
#define PgVM_MODE_CAP3_TRIANGLE		0x00000001	/* HW 3D Triangles */
#define PgVM_MODE_CAP3_RECTANGLE		0x00000002	/* HW 3D Rectangles */
#define PgVM_MODE_CAP3_LINES			0x00000004	/* HW 3D Lines */
#define PgVM_MODE_CAP3_RECTANGLES	0x00000008	/* HW 3D Rectangles */
#define PgVM_MODE_CAP3_CHROMA		0x00000010	/* HW Chroma Key */
#define PgVM_MODE_CAP3_ALPHA_BLEND	0x00000020	/* HW Alpha Blending */
#define PgVM_MODE_CAP3_ALPHA_TESTING 0x00000040	/* HW Alpha Testing */
#define PgVM_MODE_CAP3_GAROUD		0x00000080	/* HW Garoud Shading */
#define PgVM_MODE_CAP3_SPECULAR		0x00000100	/* HW Specular Highlighting */
#define PgVM_MODE_CAP3_FOG			0x00000200	/* HW Fogging */
#define PgVM_MODE_CAP3_TEXTURE_MAP	0x00000400	/* HW Texture Mapping */
#define PgVM_MODE_CAP3_MIP_MAP		0x00000800	/* HW Mip Mapping */
#define PgVM_MODE_CAP3_BUMP_MAP		0x00001000	/* HW Bump Mapping */
#define PgVM_MODE_CAP3_BILINEAR_FILTER	0x00002000	/* HW Bilinear Filtering */
#define PgVM_MODE_CAP3_TRILINEAR_FILTER	0x00004000	/* HW Trilinear Filtering */
#define PgVM_MODE_CAP3_ZBUFFER_16	0x00008000	/* HW 16 bit Z-Buffer */
#define PgVM_MODE_CAP3_ZBUFFER_32	0x00010000	/* HW 32 bit Z-Buffer */
#define PgVM_MODE_CAP3_SYTEM_RAM		0x40000000	/* Transfers to and from System Ram */
#define PgVM_MODE_CAP3_VIDEO_RAM		0x80000000	/* Transfers to and from Video Ram */

/* 4 - Texture Map Definitions */
#define PgVM_MODE_CAP4_TEXTURE_PALETTE_8	0x00000001	/* HW 8bit Palette */
#define PgVM_MODE_CAP4_TEXTURE_4444		0x00000100	/* HW A:4 R:4 G:4 B:4 */
#define PgVM_MODE_CAP4_TEXTURE_1555		0x00000200	/* HW A:1 R:5 G:5 B:5 */
#define PgVM_MODE_CAP4_TEXTURE_565		0x00000400	/* HW A:0 R:5 G:6 B:5 */
#define PgVM_MODE_CAP4_TEXTURE_888		0x00000800	/* HW A:0 R:8 G:8 B:8 */
#define PgVM_MODE_CAP4_TEXTURE_8888		0x00001000	/* HW A:8 R:8 G:8 B:8 */
/* Some dimensional flags? */

/* 5 - Image Conversion Table */
#define PgVM_MODE_CAP5_DIRECT_DIRECT		0x00000001 /* Convert betweeen Direct Color formats */
#define PgVM_MODE_CAP5_DIRECT_PALETTE	0x00000002 /* Direct to Palette */
#define PgVM_MODE_CAP5_PALETTE_DIRECT	0x00000004 /* Palette to Direct */
#define PgVM_MODE_CAP5_PALETTE_PALETTE	0x00000008 /* Palette to Palette */
#define PgVM_MODE_CAP5_YUV_DIRECT		0x00000010 /* YUV to Direct */
#define PgVM_MODE_CAP5_DIRECT_YUV		0x00000020 /* Direct to YUV */
#define PgVM_MODE_CAP5_YUV_PALETTE		0x00000040 /* YUV to Palette */
#define PgVM_MODE_CAP5_PALETTE_YUV		0x00000080 /* Palette to YUV */
#define PgVM_MODE_CAP5_YUV_YUV			0x00000100 /* YUV to YUV */

#define Pg_HWCAPS_MAX_MODES 127

	typedef struct g_vmodes
PgVideoModes_t;
	struct g_vmodes
		{
		short unsigned num_modes;
		short unsigned modes[Pg_HWCAPS_MAX_MODES];
		};

	typedef struct g_hwcaps
PgHWCaps_t;

	struct g_hwcaps
		{
		unsigned short current_video_mode;		
		unsigned char current_rrate;
		unsigned char current_mode_flags;
		unsigned long rasteriser_version;
		unsigned long driver_version;
		unsigned long total_video_ram;
		unsigned long total_crtc_ram;
		unsigned long total_non_crtc_ram;
		unsigned long currently_available_video_ram;
		unsigned long currently_available_crtc_ram;
		unsigned long currently_available_non_crtc_ram;
		unsigned long card_capabilities;
		unsigned short min_pitch;
		unsigned short max_pitch;
		unsigned short mult_pitch;
		unsigned short reserved;
		unsigned char chip_name[40];
		};

#define Pg_2D_ACCELERATOR   		   0x00000001 /* This video card has a 2D accelerator.  */
#define Pg_3D_ACCELERATOR			   0x00000002 /* This video card has a 3D accelerator.  */
#define Pg_VIDEO_OVERLAY    		   0x00000004 /* This video card has video-overlay support. */
#define Pg_OFFSCREEN 				   0x00000008 /* This video card can use offscreen video memory/ */
#define Pg_LINEAR_FRAME_BUFFER_CAPABLE 0x00000010 /* This video card can use a linear frame buffer. */

#define Pg_CM_DOUBLE_BUFFERED		   0x00000001


/*** Video overlay and capture support structs and defines ***/

#define Pg_VIDEO_CHANNEL_SCALER		0x00000001
#define Pg_VIDEO_CHANNEL_CAPTURE	0x00000002

/* RGB data formats */
#define Pg_VIDEO_FORMAT_RGB555		0x00000001
#define Pg_VIDEO_FORMAT_RGB565		0x00000002
#define Pg_VIDEO_FORMAT_RGB8888		0x00000004
#define Pg_VIDEO_FORMAT_RGB888		0x00000008

/* YUV data formats			FourCC		   Layout		H sample (YUV)	V sample (YUV)	BPP */
#define Pg_VIDEO_FORMAT_IYU1		0x31555949	/* U2Y2Y2V2Y2Y2		144		111		12  */
#define Pg_VIDEO_FORMAT_IYU2		0x32555949	/* U4Y4V4U4Y4V4		111		111		24  */
#define Pg_VIDEO_FORMAT_UYVY		0x59565955	/* U8Y8V8Y8		122		111		16  */
#define Pg_VIDEO_FORMAT_YUY2		0x32595559	/* Y8U8Y8V8		122		111		16  */
#define Pg_VIDEO_FORMAT_YVYU		0x55595659	/* Y8V8Y8U8		122		111		16  */
#define Pg_VIDEO_FORMAT_V422		0x56343232	/* V8Y8U8Y8		122		111		16  */
#define Pg_VIDEO_FORMAT_CLJR		0x524a4c43	/* V6U6Y5Y5Y5Y5		133		111		8   */

#define Pg_VIDEO_FORMAT_YVU9		0x39555659	/* Planar YVU		144		144		9   */
#define Pg_VIDEO_FORMAT_YV12		0x32315659	/* Planar YUV		122		122		12  */

/* There seems to be no FourCC that matches this */
#define Pg_VIDEO_FORMAT_YUV420		0x00000100	/* Planar YUV		122		111		16  */

/* These formats are the same as YV12, except the U and V planes do not have to contiguously follow the Y plane */
/* but they're all the same to us, since we always have 3 plane pointers */
#define Pg_VIDEO_FORMAT_CLPL	Pg_VIDEO_FORMAT_YV12	/* Cirrus Logic Planar format */
#define Pg_VIDEO_FORMAT_VBPL	Pg_VIDEO_FORMAT_YV12	/* VooDoo Banshee planar format */

/* Video Scaler capabilities flags */
#define Pg_SCALER_CAP_DST_CHROMA_KEY	0x00001000	/* Video viewport supports chroma-keying on desktop data */
#define	Pg_SCALER_CAP_DOUBLE_BUFFER	0x00010000	/* Scaler channel can be double-buffered */
#define	Pg_SCALER_CAP_BRIGHTNESS_ADJUST	0x00080000	/* Brightnesss of video viewport can be adjusted */
#define	Pg_SCALER_CAP_CONTRAST_ADJUST	0x00100000	/* Contrast of video viewport can be adjusted */
#define	Pg_SCALER_CAP_SATURATION_ADJUST	0x00200000
#define	Pg_SCALER_CAP_HUE_ADJUST	0x00400000

/* Video Scaler property flags */
#define	Pg_SCALER_PROP_CHROMA_ENABLE		0x00000010
#define	Pg_SCALER_PROP_CHROMA_SPECIFY_KEY_MASK	0x00000020
#define	Pg_SCALER_PROP_SCALER_ENABLE		0x00000100
#define	Pg_SCALER_PROP_DOUBLE_BUFFER		0x00000200
#define	Pg_SCALER_PROP_DISABLE_FILTERING	0x00000400
#define	Pg_SCALER_PROP_TO_FRONT			0x00001000	/* Overlay should be positioned "on top" of other video scalers */
#define	Pg_SCALER_PROP_TO_BACK			0x00002000	/* Overlay should be positioned "underneath" other video scalers */
#define Pg_SCALER_PROP_DRAW_TARGETABLE		0x00004000	/* App wants to be able to target the scaler Offscreen Contexts for drawing */

/* Video Capture property flags */
#define Pg_CAPTURE_PROP_AFT_ON			0x00000001	/* Auto fine-tuning */
#define Pg_CAPTURE_PROP_RUNNING			0x00000002	/* Enable capturing */
#define Pg_CAPTURE_PROP_DOUBLE_BUFFER		0x00000004	/* Capture frames into alternate buffers */
#define Pg_CAPTURE_PROP_SYNC_WITH_SCALER	0x00000008	/* Only effective when double buffering; the overlay scaler automatically "follows" the video-in buffer */

/* Video Capture property update flags */
#define Pg_CAPTURE_UPDATE_VIDEO_SOURCE		0x00000001	/* "video_source" has changed */
#define Pg_CAPTURE_UPDATE_AUDIO_SOURCE		0x00000002	/* "audio_source" has changed */
#define Pg_CAPTURE_UPDATE_INPUT_FORMAT		0x00000004	/* "input_format" has changed */
#define Pg_CAPTURE_UPDATE_OUTPUT_FORMAT		0x00000008	/* "output_format" has changed */
#define Pg_CAPTURE_UPDATE_TUNER			0x00000010	/* "tuner_channel" and/or "Fif" and/or "radio_modulation" has changed */
#define Pg_CAPTURE_UPDATE_OUTPUT_SIZE		0x00000020	/* one or more of "crop_top", "crop bottom", "crop_left", "crop_right", "dst_width" and "dst_height" has changed */
#define Pg_CAPTURE_UPDATE_BRIGHTNESS		0x00000040	/* "brightness" has changed */
#define Pg_CAPTURE_UPDATE_CONTRAST		0x00000080	/* "contrast" has changed */
#define Pg_CAPTURE_UPDATE_SATURATION		0x00000100	/* "u_saturation" and/or "v_saturation" has changed */
#define Pg_CAPTURE_UPDATE_HUE			0x00000200	/* "hue" has changed */
#define Pg_CAPTURE_UPDATE_VOLUME		0x00000400	/* "volume" has changed */
#define Pg_CAPTURE_UPDATE_OUTPUT_TARGET		0x00000800	/* one or more of ?plane? members have changed */

/* Video Capture device capabilities */
#define Pg_CAPTURE_CAP_SOURCE_TUNER		0x00000001
#define Pg_CAPTURE_CAP_SOURCE_SVIDEO		0x00000002
#define Pg_CAPTURE_CAP_SOURCE_COMPOSITE		0x00000004
#define Pg_CAPTURE_CAP_BRIGHTNESS_ADJUST	0x00000008
#define Pg_CAPTURE_CAP_CONTRAST_ADJUST		0x00000010
#define Pg_CAPTURE_CAP_SATURATION_ADJUST	0x00000020
#define Pg_CAPTURE_CAP_HUE_ADJUST		0x00000040
#define Pg_CAPTURE_CAP_VOLUME_ADJUST		0x00000080
#define Pg_CAPTURE_CAP_AUDIO_SOURCE_MUTE	0x00000100
#define Pg_CAPTURE_CAP_AUDIO_SOURCE_TUNER	0x00000200
#define Pg_CAPTURE_CAP_AUDIO_SOURCE_EXTERNAL	0x00000400	/* Line in */
#define Pg_CAPTURE_CAP_TEMPORAL_DECIMATION	0x00000800
#define Pg_CAPTURE_CAP_DOWNSCALING		0x00001000
#define Pg_CAPTURE_CAP_UPSCALING		0x00002000
#define Pg_CAPTURE_CAP_CROPPING			0x00004000
#define Pg_CAPTURE_CAP_DOUBLE_BUFFER		0x00008000
#define Pg_CAPTURE_CAP_SYNC_WITH_SCALER		0x00010000

#define Pg_CAPTURE_STATUS_TUNED			0x00000001	/* Tuner PLL has locked */
#define Pg_CAPTURE_STATUS_CHANNEL_PRESENT	0x00000002	/* Good signal detected on current Radio or TV channel */
#define Pg_CAPTURE_STATUS_VIDEO_PRESENT		0x00000004	/* Video signal detected */
#define Pg_CAPTURE_STATUS_STEREO		0x00000008	/* Stereo audio signal */

/* Input sources for Video Capture */
#define Pg_CAPTURE_SOURCE_TUNER			Pg_CAPTURE_CAP_SOURCE_TUNER
#define Pg_CAPTURE_SOURCE_SVIDEO		Pg_CAPTURE_CAP_SOURCE_SVIDEO
#define Pg_CAPTURE_SOURCE_COMPOSITE		Pg_CAPTURE_CAP_SOURCE_COMPOSITE

/* Audio sources for Video Capture */
#define Pg_CAPTURE_AUDIO_SOURCE_MUTE		Pg_CAPTURE_CAP_AUDIO_SOURCE_MUTE
#define Pg_CAPTURE_AUDIO_SOURCE_TUNER		Pg_CAPTURE_CAP_AUDIO_SOURCE_TUNER
#define Pg_CAPTURE_AUDIO_SOURCE_EXTERNAL	Pg_CAPTURE_CAP_AUDIO_SOURCE_EXTERNAL

/* Audio modulation types */
#define Pg_CAPTURE_MODULATION_AM		0x00000000
#define Pg_CAPTURE_MODULATION_FM		0x00000001

/* Audio output destination */
#define Pg_CAPTURE_AUDIO_OUT_SPEAKER		0x00000000
#define Pg_CAPTURE_AUDIO_OUT_HEADPHONE		0x00000001

/* Video Capture signal types */
#define Pg_CAPTURE_SIGNAL_NTSC		0x00000000
#define Pg_CAPTURE_SIGNAL_NTSC_JAPAN	0x00000001
#define Pg_CAPTURE_SIGNAL_PAL		0x00000002
#define Pg_CAPTURE_SIGNAL_PAL_M		0x00000003
#define Pg_CAPTURE_SIGNAL_PAL_N		0x00000004
#define Pg_CAPTURE_SIGNAL_PAL_N_COMBO	0x00000005
#define Pg_CAPTURE_SIGNAL_SECAM		0x00000006

typedef struct {
	unsigned char	src_alpha, dst_alpha;
	unsigned 	alpha_mode;
	unsigned short	x1, y1, x2, y2;
} PgVideoAlpha_t;

typedef struct {
	unsigned 	size;
	unsigned	flags;
	PgColor_t	color_key;
	unsigned	reserved0;
	PgColor_t	color_key_mask;
	PhRect_t	viewport;	/* Where on the display the video appears */
	PhDim_t		src_dim;	/* Dimensions of the video data source */
	unsigned	format;		/* Pg_VIDEO_FORMAT_ */
	int		brightness;
	int		contrast;
	PgVideoAlpha_t	alpha[4];
	unsigned	reserved[10];
} PgScalerProps_t;

typedef struct {
	unsigned 	size;
	unsigned	flags;
	unsigned	video_source;		/* Device to capture from */
	unsigned	audio_source;
	unsigned	input_format;		/* PAL, NTSC etc. */
	unsigned	output_format;		/* YUV, RGB etc. */
	int		tuner_channel;		/* In Hz */
	int		Fif;			/* Intermediate Frequency of picture carrier in Hz (region dependant) */
	short		dst_width;		/* Output width of scaled image */
	short		dst_height;		/* Output height of scaled image */
	short		crop_top;		/* Lines to skip at top of pre-scaled source image */
	short		crop_bottom;		/* Lines to skip at bottom of pre-scaled source image */
	short		crop_left;		/* Samples to skip at left of pre-scaled source image */
	short		crop_right;		/* Samples to skip at right of pre-scaled source image */
	short		brightness;		/* signed, 0 == normal */
	short		contrast;		/* signed, 0 == normal */
	short		u_saturation;		/* color (blue) signed, 0 == normal */
	short		v_saturation;		/* color (red) signed, 0 == normal */
	short		hue;			/* signed, 0 == normal */
	unsigned short	volume;			/* 0 == silent */
	unsigned short	audio_output;		/* Speaker, headphones etc. */
	short		radio_modulation;	/* AM FM etc */

	/* The offscreen contexts to which the data should be streamed */
	PgVidMemTag_t	yplane1;
	PgVidMemTag_t	uplane1;
	PgVidMemTag_t	vplane1;
	PgVidMemTag_t	yplane2;
	PgVidMemTag_t	uplane2;
	PgVidMemTag_t	vplane2;

	unsigned	update_flags;		/* Which members in this structure have changed since the last call */

	unsigned	reserved1[7];
} PgCaptureProps_t;

/* General capabilities of a Video Scaler */
typedef struct scaler_caps {
	unsigned 	size;
	unsigned	format;
	unsigned	flags;
	short		src_max_x;
	short		src_max_y;
	short		max_mag_factor_x;
	short		max_mag_factor_y;
	short		max_shrink_factor_x;
	short		max_shrink_factor_y;
	unsigned	reserved[10];
} PgScalerCaps_t;

/* Status of a Video Frame Capture device */
typedef struct capture_status {
	unsigned 	size;
	unsigned	flags;
	unsigned	current_channel;	/* In Hz */
	unsigned	reserved[12];
} PgCaptureStatus_t;

/* Video capture device's capabilities for a given video format */
typedef struct capture_caps {
	unsigned 	size;
	unsigned	flags;

	/*  Info regarding capture unit input */
	unsigned	signal_format;		/* PAL, NTSC etc. */
	unsigned	frame_width;		/* Unscaled width of frames output by capture unit */
	unsigned	frame_height;		/* Unscaled height of frames output by capture unit */
	unsigned	frame_rate;		/* Frames (not fields) per second */

	/*  Info regarding capture unit output */
	unsigned	output_format;		/* YUV, RGB etc. */
	unsigned	stride_granularity;	/* Output buffer stride must be a multiple of this */

	unsigned	reserved[12];
} PgCaptureCaps_t;

/* Do not use */
typedef union pg_video_addrs {
	struct {
		unsigned long YAddr[2];
		unsigned long YStride;
		/* Following ignored for packed formats */
		unsigned long UAddr[2];
		unsigned long UStride;
		unsigned long VAddr[2];		
		unsigned long VStride;
	} yuv;
	struct {
		unsigned long Addr[2];
		unsigned long Stride;
	} rgb;
} PgVideoAddrs_t;

typedef struct pg_scaler_channel {
	struct pdoffscreencontext 	*yplane1;
	struct pdoffscreencontext	*uplane1;
	struct pdoffscreencontext	*vplane1;
	struct pdoffscreencontext	*yplane2;
	struct pdoffscreencontext	*uplane2;
	struct pdoffscreencontext	*vplane2;
	unsigned			flags;
	int				chid;
} PgVideoChannel_t;

typedef struct pg_tv_frequency_table {
	int		channel_start;
	int		channel_end;
	int		start_frequency;
	int		increment;
	unsigned	reserved[8];
} PgTvFrequencyTable_t;

typedef struct pg_tv_region {
	char			*name;
	int			Fif;		/* In Hz */
	unsigned		signal_format;	/* PAL, NTSC etc. */
	PgTvFrequencyTable_t	*table;
	int			max_channel;
	unsigned		reserved[8];
} PgTvRegion_t;

#define Pg_SCALER_CHANNEL_FLAG_BUFFERS_CHANGED	0x00000002	/* Location of buffers moved since last call to Configure */
#define Pg_SCALER_CHANNEL_FLAG_UV_VALID		0x00000004	/* U and V plane buffers valid */

/* Not visible to app */
typedef struct pg_video_objects {
	PgVidMemDesc_t	yplane1;
	PgVidMemDesc_t	uplane1;
	PgVidMemDesc_t	vplane1;
	PgVidMemDesc_t	yplane2;
	PgVidMemDesc_t	uplane2;
	PgVidMemDesc_t	vplane2;
	int		flags;	/* Pg_SCALER_OBJECT_FLAGS_* */
	PhRid_t		rid;
	unsigned	chid;	/* Scaler channel ID */
} PgVideoObjects_t;

/* Offscreen Context Flags */
#define Pg_OSC_CRTC_SAFE	 0x00000001	 /* ensure that the crtc can be pointed at it */
#define Pg_OSC_MAIN_DISPLAY	 0x00000002  /* create an offscreen context out of 
										    the main display -- NOT the same as Dup(NULL),
										    this one is actually the display, implies 
										    CRTC_SAFE. */
#define Pg_OSC_MEM_PAGE_ALIGN 0x00000008 /* Align the offscreen memory to __PAGESIZE */

#define Pg_OSC_MEM_SYS_ONLY         0x00000004  /* This context can *ONLY* live in system ram. */
#define Pg_OSC_MEM_2D_WRITABLE      0x00000010  /* Context must be targetable by the 2D engine. */
#define Pg_OSC_MEM_2D_READABLE      0x00000020  /* Context must be readable by the 2D engine. */

#define Pg_OSC_MEM_HINT_CPU_READ    0x00000100  /* Hint. Allocate this RAM so that it is 
                                                   optimized for reading by the CPU. */
#define Pg_OSC_MEM_HINT_CPU_WRITE   0x00000200  /* Hint. Allocate this RAM so that it is
                                                   optimized for writing by the CPU. */
#define Pg_OSC_GF_SID				0x00000400  /* This osc is wrapped around gf sid specified by type field. */
#define Pg_OSC_MEM_LINEAR_ACCESSIBLE            0x00000800  /* Context must target linear addressable memory. */

/* misc offscreen flags */
#define __Pg_OSC_INTERNAL_OSC_CREATED 0x00010000
#define Pg_OSC_NO_SURF				  0x00020000	/* Create and offscreen context but do not allocate any memory on the server side */
#define Pg_OSC_MEM_3D_WRITABLE	0x00040000	/* Context must be targetable by the 3D engine */

/* Flags for PdSetOffscreenSurface */
#define Pg_OSC_FLUSH_IF_CURRENT		0x00000001		/* call PgFlush() if the offscreen context is the current context */

/* Offscreen Context Lock related flags */

/* -- creation / type */
#define Pg_OSC_LOCK_SIG     0x00000001  /* signal lock flag */

/* -- lock params */
#define PG_OSC_LOCK_TIMEOUT  0x00000010  /* Time out if lock cannot be obtained */

/* -- return codes */
#define Pg_OSC_LOCK_OK		 		0x00000000	/* No error */
#define Pg_OSC_LOCK_INVALID  		0x00000001  /* lock is invalid */
#define Pg_OSC_LOCK_TIMED_OUT		0x00000002  /* lock couldn't be acquired...timeout */
#define Pg_OSC_NOT_LOCKED 			0x00000003  /* context was already in an unlocked state */
#define Pg_OSC_LOCK_ALREADY_CREATED 0x00000004  /* context already has locks created for it */
#define Pg_OSC_CREATE_LOCK_FAILED   0x00000005  /* lock couldn't be created */
#define Pg_OSC_LOCKED				0x00000006  /* context is locked */
#define Pg_OSC_LOCK_DEADLOCK		0x00000007	/* attempting to lock the context resulted in a dead lock */

/* max # channels in a color model */

#define Pg_CM_MAX_CHANNELS	4

/* color converion fn return values */

#define Pg_CM_SUCCESS	0	/* color mapped cleanly */
#define Pg_CM_WARNING	1	/* color mapped to nearest match */
#define Pg_CM_ERROR		-1	/* error occurred, no mapping performed */

typedef int32_t PgColorChannel_t;

typedef struct pg_channel_info
{
	char *name;
	PgColorChannel_t minimum;
	PgColorChannel_t maximum;
	ushort_t flags;
	ushort_t padding;
	
} PgColorChannelInfo_t;

/* flags for color channels */

#define Pg_CC_BASE_1		0x1	/* float (between 0.0= min and 1.0=max) entry permitted */
#define Pg_CC_DECIMAL		0x2	/* decimal entry permitted */
#define Pg_CC_HEX			0x4	/* hexadecimal entry permitted */
#define Pg_CC_PERCENT		0x8	/* percentage entry permitted */
#define Pg_CC_ENTRY_MODES	0xf

typedef struct pg_color_model
{
	char *name;												/* Color model name */
	int (*compose_f)(PgColorChannel_t const*,PgColor_t*);	/* Builds an RGB value from channel info */
	int (*decompose_f)(PgColor_t,PgColorChannel_t *);		/* Converts an RGB into consituent channels */
	PgColorChannelInfo_t *channels;							/* specs for individual channels */
	uint8_t nchannels;										/* number of channels (not including alpha) */
	uint8_t id;												/* Numeric id for color model */
	uint16_t padding;

} PgColorModel_t;

typedef struct pg_palette
{
	char *name;
	char **color_names;
	PgColorChannel_t *color_data;
	uint16_t flags;
	uint16_t ncolors;
	PgColorModel_t *model;
} PgPalette_t;

/* palette flags */

#define Pg_PALETTE_RELEASE_NAME			0x1
#define Pg_PALETTE_RELEASE_COLOR_NAMES	0x2
#define Pg_PALETTE_RELEASE_COLOR_DATA	0x4
#define Pg_PALETTE_RELEASE_COLOR_MODEL	0x8
#define Pg_PALETTE_RELEASE_ALL			0xf

/*
 * LAYERS
 */
typedef struct {
    unsigned int    op;
    unsigned int    salpha;
    unsigned int    dalpha;
} PgLayerAlpha_t;

typedef struct {
    unsigned int    format;
    long            owner;

    unsigned int    caps;
    unsigned int    alpha_caps;
    unsigned int    alpha_combine_caps;
    unsigned int    chroma_caps;
    
    /* data range */
    int     max_data_width;
    int     max_data_height;

    /* viewport ranges */
    int     max_src_width;
    int     max_src_height;

    int     max_dst_width;
    int     max_dst_height;
    int     min_dst_width;
    int     min_dst_height;

    /* max difference between src/dst viewports */
    int     max_x_scale;
    int     max_y_scale;
    int     min_x_scale;
    int     min_y_scale;

	unsigned long	format_flags;

    unsigned long   reserved[3];
} PgLayerCaps_t;

/* Layer formats (DISP_LAYER_FORMAT_*) */
#define Pg_LAYER_FORMAT_PAL8            0x00000000
#define Pg_LAYER_FORMAT_ARGB1555        0x00000001
#define Pg_LAYER_FORMAT_RGB565          0x00000002
#define Pg_LAYER_FORMAT_RGB888          0x00000003
#define Pg_LAYER_FORMAT_ARGB8888        0x00000004
#define Pg_LAYER_FORMAT_YUY2            0x00010000
#define Pg_LAYER_FORMAT_UYVY            0x00010001
#define Pg_LAYER_FORMAT_YVYU            0x00010002
#define Pg_LAYER_FORMAT_V422            0x00010003
#define Pg_LAYER_FORMAT_YVU9            0x00020000
#define Pg_LAYER_FORMAT_YV12            0x00020001
#define Pg_LAYER_FORMAT_YUV420          0x00020002
#define	Pg_LAYER_FORMAT_YUV_NV12		0x00030000
#define	Pg_LAYER_FORMAT_YUV_AYUV		0x00030001

/* Layer format flags */
#define	Pg_LAYER_FORMAT_PKLE			0x00000001
#define	Pg_LAYER_FORMAT_PKBE			0x00000002
#define	Pg_LAYER_FORMAT_PACK			(Pg_LAYER_FORMAT_PKLE|Pg_LAYER_FORMAT_PKBE)
#define	Pg_LAYER_FORMAT_BO_BGRA			0x00000100
#define	Pg_LAYER_FORMAT_BO_ARGB			0x00000200

/* General Capabilities (DISP_LAYER_CAP_*) */
#define Pg_LAYER_CAP_FILTER             0x00000001
#define Pg_LAYER_CAP_SCALE_REPLICATE    0x00000002
#define Pg_LAYER_CAP_PAN_SOURCE         0x00000004
#define Pg_LAYER_CAP_SIZE_DEST          0x00000008
#define Pg_LAYER_CAP_PAN_DEST           0x00000010
#define Pg_LAYER_CAP_EDGE_CLAMP         0x00000020
#define Pg_LAYER_CAP_EDGE_WRAP          0x00000040
#define Pg_LAYER_CAP_DISABLE            0x00000080
#define Pg_LAYER_CAP_SET_BRIGHTNESS     0x00000100
#define Pg_LAYER_CAP_SET_CONTRAST       0x00000200
#define Pg_LAYER_CAP_SET_SATURATION     0x00000400
#define Pg_LAYER_CAP_ALPHA_WITH_CHROMA  0x00000800
#define Pg_LAYER_CAP_MAIN_DISPLAY       0x80000000

/* Alpha Combine Capabilities (DISP_ALPHA_BLEND_CAP_*) */
#define Pg_LAYER_ALPHA_COMBINE_CAP_SPP_WITH_DG  0x00000001  /* Source Per-pixel with Dest global supported */
#define Pg_LAYER_ALPHA_COMBINE_CAP_SG_WITH_DPP  0x00000002  /* Source global with Dest Per-pixel supported */
#define Pg_LAYER_ALPHA_COMBINE_CAP_SPP_WITH_DPP 0x00000004  /* Source per-pixel with Dest per-pixel supported */

/* Alpha Operations (DISP_ALPHA_* | DISP_BLEND_*) */
#define Pg_LAYER_ALPHA_M1_SRC_PIXEL_ALPHA   0x00010000
#define Pg_LAYER_ALPHA_M1_DST_PIXEL_ALPHA   0x00020000
#define Pg_LAYER_ALPHA_M1_GLOBAL            0x00040000
#define Pg_LAYER_ALPHA_M1_MAP               0x00080000
#define Pg_LAYER_ALPHA_M2_SRC_PIXEL_ALPHA   0x01000000
#define Pg_LAYER_ALPHA_M2_DST_PIXEL_ALPHA   0x02000000
#define Pg_LAYER_ALPHA_M2_GLOBAL            0x04000000
#define Pg_LAYER_ALPHA_M2_MAP               0x08000000

#define Pg_LAYER_BLEND_SRC_M1_ALPHA             0x0100
#define Pg_LAYER_BLEND_SRC_ONE_MINUS_M1_ALPHA   0x0200
#define Pg_LAYER_BLEND_SRC_M2_ALPHA             0x0400
#define Pg_LAYER_BLEND_SRC_ONE_MINUS_M2_ALPHA   0x0800

#define Pg_LAYER_BLEND_DEST_M1_ALPHA            0x0001
#define Pg_LAYER_BLEND_DEST_ONE_MINUS_M1_ALPHA  0x0002
#define Pg_LAYER_BLEND_DEST_M2_ALPHA            0x0004
#define Pg_LAYER_BLEND_DEST_ONE_MINUS_M2_ALPHA  0x0008

/* Chromakey Capabilities (see DISP_LAYER_CHROMAKEY_CAP_*) */
#define Pg_LAYER_CHROMAKEY_CAP_SRC_SINGLE   0x00000001
#define Pg_LAYER_CHROMAKEY_CAP_DST_SINGLE   0x00000100
#define Pg_LAYER_CHROMAKEY_CAP_SHOWTHROUGH  0x00000800
#define Pg_LAYER_CHROMAKEY_CAP_BLOCK        0x00001000

/* Edge modes */
#define Pg_LAYER_EDGE_UNDEFINED     0
#define Pg_LAYER_EDGE_WRAP          1
#define Pg_LAYER_EDGE_CLAMP         2

/* Filter modes */
#define Pg_LAYER_NO_FILTER          0
#define Pg_LAYER_FILTER             1

/* PgSetLayerArg() parameters */
#define Pg_LAYER_ARG_ACTIVE         1
#define Pg_LAYER_ARG_FORMAT_INDEX   2
#define Pg_LAYER_ARG_SRC_VIEWPORT   3
#define Pg_LAYER_ARG_DST_VIEWPORT   4
#define Pg_LAYER_ARG_BRIGHTNESS     5
#define Pg_LAYER_ARG_SATURATION     6
#define Pg_LAYER_ARG_CONTRAST       7
#define Pg_LAYER_ARG_CHROMA         8
#define Pg_LAYER_ARG_ALPHA          9
#define Pg_LAYER_ARG_EDGE_MODE      10
#define Pg_LAYER_ARG_FILTER_MODE    11
#define Pg_LAYER_ARG_LIST_BEGIN     12
#define Pg_LAYER_ARG_LIST_END       13

/*
 *
 * PROTOS
 *
 */

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#include <photon/PgRGB.h>
#include <photon/PgHSB.h>
#include <photon/PgHLS.h>
#include <photon/PgCMYK.h>

#endif /* __PH_GLIB_H_ */

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/Pg.h $ $Rev: 224048 $" )
#endif
