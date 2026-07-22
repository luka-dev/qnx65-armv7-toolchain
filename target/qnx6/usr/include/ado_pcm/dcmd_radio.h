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
 *      dmcd_radio.h
 *        
 */

#ifndef DCMD_RADIO_H_INCLUDED
#define DCMD_RADIO_H_INCLUDED

#include <devctl.h>

typedef struct _radio_tuner {
	char			name[32];
#define RADIO_CAP_MONO		0x01
#define RADIO_CAP_STEREO	0x02
#define RADIO_CAP_VOLUME	0x04
#define RADIO_CAP_RDS		0x08
#define RADIO_CAP_SEEK		0x10
#define RADIO_CAP_PRESETS	0x20
#define RADIO_CAP_ATTR_SAVE	0x40
	_Uint32t		cap;
	_Uint32t		attr;				// RADIO_ATTR_MONO, RADIO_ATTR_STEREO
	_Uint32t		volume;				// percent
#define RADIO_SPACING_200KHZ		200000
#define RADIO_SPACING_100KHZ		100000
#define RADIO_SPACING_50KHZ			50000
	_Uint32t		spacing;			// 50kHz, 100kHz (Europe, Japan), 200kHz (USA, Australia)
	_Uint32t		current;
#define RADIO_BAND_EU_LOW			87500000
#define RADIO_BAND_EU_HIGH			108000000
#define RADIO_BAND_JAPAN_LOW		76000000
#define RADIO_BAND_JAPAN_HIGH		90000000
#define RADIO_BAND_JAPAN_WIDE_LOW	76000000
#define RADIO_BAND_JAPAN_WIDE_HIGH	108000000
	_Uint32t		band_low;
	_Uint32t		band_high;
	_Uint32t		presets[12];
	_Uint32t		rsvd[10];
} RadioTuner_t;

typedef struct _radio_tune {
#define RADIO_TUNE_FREQ		0x00
#define RADIO_TUNE_PRESET	0x01
#define RADIO_SEEK_UP		0x02
#define RADIO_SEEK_DOWN		0x04
#define RADIO_SEEK_WRAP		0x08
	_Uint32t		op;
	_Uint32t		arg;				// frequency/preset num
#define RADIO_DFLT_TIMEOUT	0
	_Uint32t		timeout;			// timeout in seconds
	_Uint32t		rsvd[5];
} RadioTune_t;

typedef struct _radio_freq {
	_Uint32t		attr;				// signal attibutes (RADIO_ATTR_MONO, RADIO_ATTR_STEREO)
	_Uint32t		ssi;				// signal strength indicator (percent)
	_Uint32t		frequency;			// currently tuned frequency
	_Uint32t		rsvd[5];
} RadioFreq_t;

typedef struct _radio_attr {
#define RADIO_ATTR_MONO			0x01
#define RADIO_ATTR_STEREO		0x02
#define RADIO_ATTR_VOLUME		0x04
#define RADIO_ATTR_BAND			0x08	// data[0] = band low, data[1] = band high
#define RADIO_ATTR_SPACING		0x10	// data[0] = spacing
#define RADIO_ATTR_PRESETS		0x20	// data[0] = preset[0] ... preset[11]
#define RADIO_ATTR_SAVE			0x40
	_Uint32t		attr;
	_Uint32t		attr_data[20];
} RadioAttr_t;

typedef struct _radio_rds_group {
	_Uint8t			bler[4];
	_Uint16t		blocks[4];
} RadioRdsGroup_t;

typedef struct _radio_rds {
	_Uint32t		length;
	RadioRdsGroup_t	groups[128];
} RadioRds_t;

#define DCMD_RADIO_INFO			_IOR( 'Z', 0x01, struct _radio_tuner )	
#define DCMD_RADIO_CTRL			_IOW( 'Z', 0x02, struct _radio_attr )	
#define DCMD_RADIO_TUNE			_IOW( 'Z', 0x03, struct _radio_tune )	
#define DCMD_RADIO_FREQ			_IOR( 'Z', 0x04, struct _radio_freq )
#define DCMD_RADIO_RDS			_IOR( 'Z', 0x05, struct _radio_rds )

#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/services/audio/public/include/ado_pcm/dcmd_radio.h $ $Rev: 219613 $" )
