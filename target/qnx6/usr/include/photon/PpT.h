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
 * PpT.h	
 *
 *		Photon Printer context structure
 *

 */
#ifndef __PPCTRL_H_INCLUDED
#define __PPCTRL_H_INCLUDED
#include <photon/PhInternal.h>
#ifndef _LIMITS_H_INCLUDED
#include <limits.h>
#endif

#include <photon/PhPack.h>

#define PpVERSION 200
#define PRINTER_NAME_MAX NAME_MAX

typedef struct 
	{
	char 		*name;
	char		*location;
	char 		*device;
	char		*filter;
	PhRect_t 	non_printable_area;
	char		*properties_app;
	char		*preview_app;
	char      *fontmap_name;
/* 	ulong_t		spare; */
	} PpPCPrinter_spec_t;

typedef struct {
	int	from;		/* Special cases:  0,0==ALL   -1,-1==PrintSelection */
	int	to;
} PpPageRange_t;

typedef struct 
	{
	char 		*output_filename;
	char 		*job_name;
	char 		*comment;
	char		*date;
	char		*user_id;
	char		*author;
	char		*manager_app;
	ulong_t		page;	
	PpPageRange_t pagerange;
	ulong_t		spare;
	} PpPCSession_t;

#define Pp_PC_FLAGSIZE  8
#define Pp_testbit( array, bit )  (array[bit/8] & ( 1<<(bit%8) ))
#define Pp_setbit( array, bit )  (array[bit/8] |= ( 1<<(bit%8) ))
#define Pp_clearbit( array, bit )  (array[bit/8] &= (0xff ^ ( 1<<(bit%8) )))
#define Pp_resetbits( array )  memset(array, '0', Pp_PC_FLAGSIZE)

typedef struct 
	{
	int 		fd;
	ulong_t		cur_dest_size; /* this many bytes written to the target. */
	char		changed_prop[Pp_PC_FLAGSIZE];
	char		locked_prop[Pp_PC_FLAGSIZE];
	char		emitted_prop[Pp_PC_FLAGSIZE];
	char 		*tmp_target;
	char 		do_preview;
	char		pc_flags;  /* Pp_CF_ABORTED, Pp_CF_ACTIVE, maybe others... */
	char		spare_char[2];
	ulong_t		spare;
	} PpPCControl_t;


#define Pp_CF_SHMEM_TARGET		0x80 /*(r/o)*/
#define Pp_CF_ABORTED			0x40 /*(r/o)*/
#define Pp_CF_ACTIVE			0x20 /*(r/o)*/
#define Pp_CF_PS_OUTPUT_FILE	0x01 /* PostScript output file when set, PHS output otherwise */


typedef struct 
	{
	PhPoint_t	source_offset;
	PhDim_t		source_dim;
	PhDim_t		source_resolution; /*dpi ( w & h ) */
	ulong_t		source_colors; 
	PhPoint_t	scale;
	PhRect_t	margins;
	ulong_t		intensity; /* (0 - 100000) in thousanths of a percent */
	PhDim_t		printer_resolution; /* dpi ( w & h ) */
	PhDim_t		paper_size;
	char		collating_mode;
	char		dithering;
	char		copies;
	char		orientation;
	char		duplex;
	char		paper_type;
	char		paper_source;
	char		inktype;
	char		color_mode;
	char    	order;
	char		spare1[2];
	ulong_t		max_dest_size; /* Dont allow cur_dest_size to exceed this. */
	} PpPCOutput_spec_t;

typedef struct printer_context PpPrintContext_t;
struct printer_context {
	PhDrawContext_t		dc;
	PhGrafxInfo_t 		*graphics_info;
	PpPCPrinter_spec_t  printer_spec;
	PpPCSession_t 		session;
	PpPCControl_t		control;
	PpPCOutput_spec_t 	output_spec;
	};

/* For Printer context modify function */
#define Pp_PC_MODIFY 3

/* Printer Context changed bits */
/* used in PpPrintModifyPC() to specify which member */
/* is to be modified in the provide PC. */
#define Pp_PC_NAME 					0 
#define Pp_PC_LOCATION		 		1
#define Pp_PC_DEVICE 				2
#define Pp_PC_FILTER 				3
#define Pp_PC_DRIVER 				3
#define Pp_PC_NONPRINT_MARGINS 		4
#define Pp_PC_PROP_APP		 		5
#define Pp_PC_PREVIEW_APP			6
#define Pp_PC_FILENAME				7
#define Pp_PC_COMMENT 				8
#define Pp_PC_DATE 					9
#define Pp_PC_USER_ID	 			10
#define Pp_PC_PAGE_RANGE			11
#define Pp_PC_SOURCE_OFFSET 		12
#define Pp_PC_SOURCE_SIZE 			13
#define Pp_PC_SOURCE_RESOLUTION 	14
#define Pp_PC_SOURCE_COLORS 		15
#define Pp_PC_SCALE 				16
#define Pp_PC_MARGINS 				17
#define Pp_PC_INTENSITY 			18
#define Pp_PC_PRINTER_RESOLUTION	19
#define Pp_PC_PAPER_SIZE	 		20
#define Pp_PC_COLLATING_MODE 		21
#define Pp_PC_DITHERING 			22
#define Pp_PC_COPIES 				23
#define Pp_PC_ORIENTATION 			24
#define Pp_PC_DUPLEX 				25
#define Pp_PC_PAPER_TYPE 			26
#define Pp_PC_PAPER_SOURCE 			27
#define Pp_PC_INKTYPE	 			28
#define Pp_PC_COLOR_MODE 			29
#define Pp_PC_DO_PREVIEW 			30
#define Pp_PC_JOB_NAME	 			31
#define Pp_PC_CONTROL	 			32 /* read only, and no changed bit. */
#define Pp_PC_MAX_DEST_SIZE			33 /* no changed bit */
#define Pp_PC_PAGE_NUM				34
#define Pp_PC_AUTHOR				35
#define Pp_PC_MANAGER_APP			36
#define Pp_PC_REVERSED				37
#define Pp_PC_FONTMAP_NAME			38

/* PpPrintModify "data" values. */
#define Pp_PM_CLOSE		0
#define Pp_FORCE_CLOSE	 	0
#define Pp_CHANGED_DEVICE 	1

/* Print Properties Message subtypes */
#define Pp_MSG_REQUEST 				0
#define Pp_MSG_REQUEST_REPLY_LOC 	1
#define Pp_MSG_REQUEST_REPLY_INT 	2
#define Pp_MSG_UPDATE				3
#define Pp_MSG_UPDATE_REPLY 		4
#define Pp_MSG_CANCEL				5
#define Pp_MSG_CANCEL_REPLY 		6


/* For use with PpPrintWidget() */
#define Pt_PP_RESIZE_WIDGET	0
#define Pt_PP_RESIZE_PC		1
#define Pt_PP_NO_RESIZE		2

/* Print Properties Message header */
typedef struct 
{
	short type;
	short subtype;
} PpPrintMsgHeader_t;

#include <photon/PhPackPop.h>

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/PpT.h $ $Rev: 219996 $" )
#endif
