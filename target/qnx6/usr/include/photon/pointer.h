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
 *  pointer.h
 *

 */

#ifndef _SYS_POINTER_H_INCLUDED
#define _SYS_POINTER_H_INCLUDED

#ifndef _TIME_H_INCLUDED
 #include <time.h>
#endif

#ifndef _INTERACT_H_INCLUDED
#include <photon/interact.h>
#endif

#include <photon/PhPack.h>

#define _POINTER_FLAG_PROPERTIES    0x000088ff      /* Properties mask */
#define _POINTER_FLAG_ABSOLUTE      0x00000001      /* Absolute co-ordinates (proximity) */
#define _POINTER_FLAG_BUTTON        0x00000002      /* buttons is non-zero */
#define _POINTER_FLAG_COORD         0x00000800      /* num_coord is non-zero */
#define _POINTER_FLAG_PRESSURE      0x00008000      /* num_pressure is non-zero */
#define _POINTER_FLAG_VALUE         (_POINTER_FLAG_COORD|_POINTER_FLAG_PRESSURE)

#define _POINTER_FLAG_CSCALE        0x00000700      /* Unit scale mask (for coords) */
#define _POINTER_FLAG_CUNITY        0x00000000      /* Units are not world related */
#define _POINTER_FLAG_CMETRIC       0x00000100      /* each unit is a number of micrometers (meter / 1000000) */
#define _POINTER_FLAG_CIMPERIAL     0x00000200      /* each unit is a number of microns (inch / 1000000) */
#define _POINTER_FLAG_CSCREEN       0x00000300      /* each unit is relitave to screen */

#define _POINTER_FLAG_PSCALE        0x00007000      /* Unit scale mask (for pressure) */
#define _POINTER_FLAG_PUNITY        0x00000000      /* Units are not world related */

#define _POINTER_FLAG_TOUCH         (_POINTER_FLAG_ABSOLUTE|_POINTER_FLAG_COORD|_POINTER_FLAG_CSCREEN)
#define _POINTER_FLAG_MOUSE         (_POINTER_FLAG_COORD)

#define _POINTER_MODE_COMPRESSED    0x0001          /* Data is compressed */

#define _POINTER_BUTTON_1           0x00000001
#define _POINTER_BUTTON_2           0x00000002
#define _POINTER_BUTTON_3           0x00000004
#define _POINTER_BUTTON_4           0x00000008
#define _POINTER_BUTTON_5           0x00000010
#define _POINTER_BUTTON_6           0x00000020
#define _POINTER_BUTTON_7           0x00000040
#define _POINTER_BUTTON_8           0x00000080
#define _POINTER_BUTTON_RIGHT       _POINTER_BUTTON_1
#define _POINTER_BUTTON_MIDDLE      _POINTER_BUTTON_2
#define _POINTER_BUTTON_LEFT        _POINTER_BUTTON_3

#define _POINTER_MAX_POINTS   6       /* Maximum number of data points available with ioctl(), otherwise use qnx_ioctl() */

struct _pointer_packet_hdr {                /* start of struct returned from read() */
    struct timespec         time;
    unsigned long           buttons;        /* Currently depressed buttons */
};

struct _pointer_packet {                    /* returned from read() (variable number of data items) */
    struct _pointer_packet_hdr hdr;
    long                    data[1];        /* variable amount of data (first coord, then pressure) */
};

struct _pointer_ctrl {
    struct _interact_device type;           /* Device type */
    unsigned long           flags;          /* Device type flags (read only) */
    unsigned char           num_coord;      /* Number of coordinats (first range values) */
    unsigned char           num_pressure;   /* Number of pressures (after coord values) */
    unsigned short          mode;           /* Mode of currently read packets */
    unsigned long           buttons;        /* Buttons available bitmap */
    struct _pointer_range {
        long                    min;
        long                    max;
        unsigned long           units;      /* Microns or micrometer per unit (if used) */
    }                       range[_POINTER_MAX_POINTS];
};

typedef union {
    long                    number;         /* number to perform operations on */
    struct {
        short                   integer;    /* integer component of number */
        unsigned short          frac;       /* fractional component of number */
    }                       component;
} hex_frac_t;

struct _pointer_matrix {
    hex_frac_t              xscale,  xy;
    hex_frac_t              yx,      yscale;
    hex_frac_t              xoffset, yoffset;
};

struct _pointer_transform {
    struct _pointer_matrix  xy_coord;       /* Only the first two coordinats are transformed */
    struct _pointer_scale {
        long                    min;
        long                    max;
    }                       pressure[_POINTER_MAX_POINTS];
};

#include <photon/PhPackPop.h>

#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ph/public/photon/pointer.h $ $Rev: 219996 $" )
