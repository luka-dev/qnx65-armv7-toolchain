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
** File: f3s_flash.h
**
** Description:
**
** This file contains the flash definitions for the f3s resource manager for
** Neutrino
**
** Ident: $Id: f3s_flash.h 219996 2009-05-04 18:47:03Z keith $
*/

/*
** Include Loop Prevention
*/

#ifndef __F3S_FLASH_H_INCLUDED
#define __F3S_FLASH_H_INCLUDED

#ifdef __F3S_FLASH_H_V3_INCLUDED
#error Cannot include old and new flash file system headers
#endif

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

#ifndef __F3S_SOCKET_H_INCLUDED
#include _NTO_HDR_(sys/f3s_socket.h)
#endif

/*
** Constant Definitions
*/

/* Capabilities Definitions */

#define F3S_ERASE_FOR_READ   0x00000001  /* erase suspend for read */
#define F3S_ERASE_FOR_WRITE  0x00000002  /* erase suspend for write */
#define F3S_ERASE_FOR_ALL    0x00000003  /* erase suspend for read and write */
#define F3S_WRITE_BUFFER     0x00000004  /* write buffers */
#define F3S_INTER_ERASE      0x00000008  /* erase interrupts */
#define F3S_INTER_BUFFER     0x00000010  /* buffer interrupts */
#define F3S_LIST_ALL         0x00000080  /* list all dbases */
#define F3S_VERIFY_WRITE     0x00000100  /* write verify */
#define F3S_VERIFY_ERASE     0x00000200  /* erase verify */
#define F3S_VERIFY_ALL       0x00000300  /* all verify */
#define F3S_LOCK_UNIT        0x00000400  /* lock unit */
#define F3S_UNLOCK_UNIT      0x00000800  /* unlock unit */
#define F3S_ECC_CODE         0x00001000  /* error correction */
#define F3S_CALIBRATE        0x00002000  /* calibrate poll loop */
#define F3S_NAND_CLE         0x00010000  /* nand command latch enable */
#define F3S_NAND_ALE         0x00020000  /* nand address latch enable */
#define F3S_NAND_CE_         0x00040000  /* nand not chip enable */
#define F3S_NAND_WP_         0x00080000  /* nand not write protect */
#define F3S_POLL_BUSY        0x00100000  /* busy polling */

/*
** Structure Definitions
*/

/* Flash Services Geometry */
typedef struct f3s_geo_s
{
  _Uint16t unit_num;   /* number of erase units for geometry */
  _Uint16t unit_pow2;  /* power 2 size of a unit */
}
f3s_geo_t;

/* Flash Services Database */

typedef struct f3s_dbase_s
{
  _Uint16t struct_size;      /* size of complete structure with geometries */
  _Uint16t status;           /* status of structure */
  _Uint16t jedec_hi;         /* jedec id number high */
  _Uint16t jedec_lo;         /* jedec id number low */
  _Uint8t *name;             /* name of driver */
  _Uint32t flags;            /* flags for capabilities */
  _Uint16t chip_inter;       /* interleave for chips on bus */
  _Uint16t chip_width;       /* width of chip */
  _Uint32t typ_write_nano;   /* typical write time for cell */
  _Uint32t typ_erase_nano;   /* typical erase time for unit */
  _Uint32t volt_read_mili;   /* read mode voltage needed */
  _Uint32t volt_write_mili;  /* program mode voltage needed */
  _Uint32t cycle_num;        /* number of erase cycles */
  _Uint32t poll_timeout;     /* poll count timeout */
  _Uint16t queue_depth;      /* depth of erase queue per chip */
  _Uint16t buffer_num;       /* number of write buffers per chip */
  _Uint16t buffer_size;      /* size of write buffers */
  _Uint16t geo_num;          /* number of geometries in vector */
  f3s_geo_t geo_vect[8];     /* geometry vector */
}
f3s_dbase_t;

/* Flash services callouts */

typedef struct f3s_flash_s
{
  _Uint32t struct_size;                          /* size of this structure */
  _Int32t (*ident)(f3s_dbase_t *dbase,           /* mandatory */
                   f3s_access_t *access,
                   _Uint32t flags,
                   _Uint32t text_offset);
  void (*reset)(f3s_dbase_t *dbase,              /* mandatory */
                f3s_access_t *access,
                _Uint32t flags,
                _Uint32t text_offset);
  _Int32t (*read)(f3s_dbase_t *dbase,            /* optional */
                  f3s_access_t *access,
                  _Uint32t flags,
                  _Uint32t text_offset,
                  _Int32t buffer_size,
                  _Uint8t *buffer);
  _Int32t (*write)(f3s_dbase_t *dbase,           /* mandatory */
                   f3s_access_t *access,
                   _Uint32t flags,
                   _Uint32t text_offset,
                   _Int32t buffer_size,
                   _Uint8t *buffer);
  void (*erase)(f3s_dbase_t *dbase,              /* mandatory */
                f3s_access_t *access,
                _Uint32t flags,
                _Uint32t text_offset,
                _Int32t size);
  _Int32t (*suspend)(f3s_dbase_t *dbase,         /* optional */
                     f3s_access_t *access,
                     _Uint32t flags,
                     _Uint32t text_offset);
  void (*resume)(f3s_dbase_t *dbase,             /* optional */
                 f3s_access_t *access,
                 _Uint32t flags,
                 _Uint32t text_offset);
  _Int32t (*sync)(f3s_dbase_t *dbase,            /* mandatory */
                  f3s_access_t *access,
                  _Uint32t flags,
                  _Uint32t text_offset,
                  _Int32t size);
}
f3s_flash_t;

#endif /* __F3S_FLASH_H_INCLUDED */

/*
** End
*/

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/fs-flash/public/sys/f3s_flash.h $ $Rev: 219996 $" )
