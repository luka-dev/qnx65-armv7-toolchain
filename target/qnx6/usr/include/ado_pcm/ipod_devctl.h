
/*
 * Copyright 2008, QNX Software Systems Ltd. All Rights Reserved.
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
 *      ipod_devctl.h
 *        
 */

#ifndef _IPOD_DEVCTL_H_INCLUDED_
#define _IPOD_DEVCTL_H_INCLUDED_


#define	EXCHANGE_VERSION	0x1000


struct	ipod_stream_data
{
	uint16_t		rate;
	uint32_t		xxx;
};

/* to be called before begining initailization commands and called with the param of EXCHANGE_VERSION */
/* if the version doesn't match in audio a return code of EPROTO will be returned */
#define		IPOD_DEVCTL_INIT_BEGIN		_IOW ('Z', 0x01, int)	
/* to be called after completing initailization commands, allows audio to accept client connections */
#define		IPOD_DEVCTL_INIT_END		_IOW ('Z', 0x02, int)	

/* to be called to de-select the streaming audio alternate interface */
#define     IPOD_DEVCTL_SELECT_ZERO_BANDWIDTH_IFACE _IOW ('Z', 0x10, int)

/* to be called in the initailization phase, between start & end, to selecet the audio alternate interface */
#define		IPOD_DEVCTL_SELECT_IFACE	_IOW ('Z', 0x20, int)	

/* called to inform audio of stream changes */
#define		IPOD_DEVCTL_STREAM_INFO		_IOW ('Z', 0xF0, struct  ipod_stream_data)	

#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/services/audio/public/include/ado_pcm/ipod_devctl.h $ $Rev: 238059 $" )
