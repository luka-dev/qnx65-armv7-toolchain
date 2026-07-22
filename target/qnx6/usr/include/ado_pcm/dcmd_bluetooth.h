/*
 * Copyright 2009, QNX Software Systems Ltd. All Rights Reserved.
 *
 * This source code may contain confidential information of QNX Software
 * Systems Ltd.  (QSSL) and its licensors. Any use, reproduction,
 * modification, disclosure, distribution or transfer of this software,
 * or any software which includes or is based upon any of this code, is
 * prohibited unless expressly authorized by QSSL by written agreement. For
 * more information (including whether this source code file has been
 * published) please email licensing@qnx.com.
 */

/*
 *
 *      dmcd_bluetooth.h
 *        
 */

#ifndef DCMD_BLUETOOTH_H_INCLUDED
#define DCMD_BLUETOOTH_H_INCLUDED

#include <ioctl.h>

typedef struct _bt_isoch {
	_Uint32t		sco_hdl;
	_Uint32t		rsvd[10];
} bt_isoch_t;

#define DCMD_BT_ISOC_ENABLE			_IOW( 'Z', 0x01, struct _bt_isoch )	
#define DCMD_BT_ISOC_DISABLE		_IOW( 'Z', 0x02, struct _bt_isoch )	

#endif

//__SRCVERSION( "$URL$ $Rev$" )
