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
 * PpProto.h	
 *		Prototypes for the Photon Pp functions
 *

 */
#ifndef __PP_PROTO_H_INCLUDED
#define __PP_PROTO_H_INCLUDED


#ifndef __PPCTRL_H_INCLUDED
#include <photon/PpT.h>
#endif

#ifndef __PT_CONNECTION_SERVER_H_INCLUDED
#include <photon/PtConnectionServer.h>
#endif

#ifndef __PT_CONNECTION_CLIENT_H_INCLUDED
#include <photon/PtConnectionClient.h>
#endif


#ifndef _STDIO_H_INCLUDED
#include <stdio.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 
 * For 1.14 compatibility
 */
#ifndef _NO_1XX_Pp_FUNCTIONS

#define PpPrintSetPC( __pc, __unused, __lock, __member, __data )\
			PpSetPC( __pc, __member, __data, __lock )
#define PpPrintGetPC( __pc, __member, __data )\
			PpGetPC( __pc, __member, __data )
#define PpPrintAllocatePC PpAllocatePC
#define PpPrintCreatePC   PpCreatePC
#define PpPrintReleasePC  PpReleasePC
#define PpPrintStart      PpContinueJob
#define PpPrintOpen       PpStartJob
#define PpPrintStop       PpSuspendJob
#define PpPrintClose      PpEndJob

#endif

#define PpSetPC( _arg, _member, _data, _lock)  (PpSetPC)(_arg, _member, (void *)_data, _lock)
#define PpGetPC( _arg, _member, _data)  (PpGetPC)(_arg, _member, (const void **)_data)

extern int 				 PpLoadPrinter( PpPrintContext_t *pc, char const *printer_name );
extern int 				 PpLoadDefaultPrinter( PpPrintContext_t *pc );
extern char 		   **PpLoadPrinterList( void );
extern void 		     PpFreePrinterList( char **list );
extern int 				 (PpSetPC)( PpPrintContext_t *pc, int member, void const * const data, int lockit );
extern void				*(PpGetPC)( PpPrintContext_t * const pc, int member, void const ** data );
extern PpPrintContext_t *PpAllocatePC( void );
extern PpPrintContext_t *PpCreatePC( void );
extern void 			 PpReleasePC( PpPrintContext_t *pc );
extern PhDrawContext_t 	*PpContinueJob( PpPrintContext_t *PC );
extern int 				 PpStartJob( PpPrintContext_t *pc );
extern void 			 PpSuspendJob( PpPrintContext_t *PC );
extern int 				 PpEndJob( PpPrintContext_t *pc );

extern int				 PpPrintNewPage( PpPrintContext_t *PC );
extern void				 PpCopyPC( PpPrintContext_t * dest, PpPrintContext_t * const src);

/*
 *  PpGetCanvas gets the size of the current drawing area
 *  taking into account the non-printable area, margins, scale
 *  and either the current source_resolution,
 *          or the current source_size
 *  If neither a source resolution nor source size is previously
 *  defined, a (semi-arbitrary) value of 100dpi is used,
 *  The PC structure is appropriately filled.
 *         (Pp_PC_SOURCE_SIZE, Pp_PC_SOURCE_RESOLUTION)
 *
 *  Return:  { 0 , 0 } :   'pc' not valid.
 *           Otherwise: Size of the rectangle.
 */
extern PhDim_t           PpGetCanvas( PpPrintContext_t *pc );
extern PhDim_t           PpSetCanvas( PpPrintContext_t *pc , PhDim_t source_size );

#define PpLoadDefaultPrinter( pc ) PpLoadPrinter( pc, NULL )


/*
 *  Properties App
 */
#ifdef __QNXNTO__
extern int PpPrintMsgReply(PtConnectionServer_t *connection,iov_t *msg,int nparts,PpPrintContext_t *pc);
extern int PpPrintMsgRead(PtConnectionClient_t *connection, const void *msg, int nparts, PpPrintContext_t *pc);
#else
extern int PpPrintMsgReply(int rcvid, iov_t *msg, int nparts, PpPrintContext_t *pc);
extern int PpPrintMsgRead(int rcvid, iov_t *msg, int nparts, PpPrintContext_t *pc);
#endif


#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>


#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PpProto.h $ $Rev: 219996 $" )
#endif
