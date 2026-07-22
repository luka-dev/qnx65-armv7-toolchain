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
 *	PgVector.h	
 *		Manifests and data structures for the Pgv-lib
 *

 */
#ifndef __PH_GLIB_VECTOR_H_INCLUDED
#define __PH_GLIB_VECTOR_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

#ifndef __PH_GLIB_H_INCLUDED
#include <photon/Pg.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" 
{
#endif

#if 0
 0  Xtype
 1   
 2   
 3	Ytype
 4	 
 5	 
 6	Ztype
 7	 
 8	 
 9	Color type
10	 
11	 
12	Translation type
13	 
14	Z Translation
15	spare
16	Translation type
17	 
18	 
19	Include delta
20	Perspective type
21	 
22	 
23	 
24	Include Operand type
25	 
26	spare
27	 
28	spare
29	 
30	 
31	 
#endif
  
#define		_Pgv_I_TMatMASK			0x00070000
#define		_Pgv_I_TMatScale		0x00010000
#define		_Pgv_I_TMat2D			0x00020000
#define		_Pgv_I_TMat3D			0x00030000
#define		_Pgv_I_Delta			0x00080000

#define		Pgv_X_MASK				0x00000007
#define		Pgv_X_UseDelta			0x00000001
#define		Pgv_X_Char				0x00000002
#define		Pgv_X_Short				0x00000003
#define		Pgv_X_LFixed			0x00000004

#define		Pgv_Y_MASK				(Pgv_X_MASK << 3)
#define		Pgv_Y_UseDelta			(Pgv_X_UseDelta << 3)
#define		Pgv_Y_Char				(Pgv_X_Char << 3)
#define		Pgv_Y_Short				(Pgv_X_Short << 3)
#define		Pgv_Y_LFixed			(Pgv_X_LFixed << 3)

#define		Pgv_Z_MASK				(Pgv_X_MASK << 6)
#define		Pgv_Z_UseDelta			(Pgv_X_UseDelta << 6)
#define		Pgv_Z_Char				(Pgv_X_Char << 6)
#define		Pgv_Z_Short				(Pgv_X_Short << 6)
#define		Pgv_Z_LFixed			(Pgv_X_LFixed << 6)

#define		Pgv_C_MASK				0x00000E00
#define		Pgv_C_StrokePen			0x00000000
#define		Pgv_C_DStrokePen		0x00000200
#define		Pgv_C_Direct			0x00000400
#define		Pgv_C_ByteIndex			0x00000600
#define		Pgv_C_ByteFlag			0x00000800		/* 0-move   !0-draw */

#define		Pgv_T_MASK				0x00003000
#define		Pgv_T_PreTrans			0x00001000
#define		Pgv_T_PostTrans			0x00002000

#define		Pgv_T_ZTrans			0x00004000

#define		Pgv_P_MASK				0x00F00000
#define		Pgv_P_Simple			0x00100000
#define		Pgv_P_Color				0x00200000

#define		Pgv_O_MASK				0x03000000
#define		Pgv_O_FixedLine			0x00000000
#define		Pgv_O_Variable			0x01000000

#define		Pgv_OP_NOP				0x00
#define		Pgv_OP_Line				0x01
#define		Pgv_OP_Point			0x02
#define		Pgv_OP_Glyph			0x80


typedef struct {
						/* fixed portion */
	unsigned		Flags;
	PhPoint_t		Trans;
	short			DRecNum;
	u_char			DRecSize;
	u_char			DRecOffX;
	u_char			DRecOffY;
	u_char			DRecOffZ;
	u_char			DRecOffColor;
	u_char			DRecOffOp;
						/* variable portion */
	long			Delta;
	long			PFactor;
	long			TTrans[3];
	long			TMat[3][3];
} PgVectorCtrlStruct;

typedef struct {
	u_char			OP;			/* Must be Pgv_OP_Glyph */
	u_char			spare;
	u_short			Flags;
	ulong_t			Code;
} PgvGlyphCtrl_t;

int PgDrawVectormx( void *dptr, PgVectorCtrlStruct *VPtr );

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif /* __PH_GLIB_VECTOR_H_ */

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PgVector.h $ $Rev: 219996 $" )
