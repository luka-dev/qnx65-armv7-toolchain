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
 *      ado_pcm.h
 *              The main header for the pcm devices.
 */

#ifndef _ADO_PCM_H_INCLUDED_
#define _ADO_PCM_H_INCLUDED_

#ifndef _MIXER_H_INCLUDED_
#include <ado_mixer.h>
#endif


/***** typedefs *************/
typedef struct ado_pcm_cap					ado_pcm_cap_t;
typedef struct ado_pcm_hw					ado_pcm_hw_t;
typedef struct ado_pcm_dmabuf				ado_pcm_dmabuf_t;
typedef struct ado_pcm_mmap					ado_pcm_mmap_t;
typedef struct ado_pcm						ado_pcm_t;
typedef struct ado_pcm_chn					ado_pcm_chn_t;
typedef struct ado_pcm_config				ado_pcm_config_t;
typedef struct ado_pcm_subchn				ado_pcm_subchn_t;
typedef struct ado_pcm_subchn_mixer 		ado_pcm_subchn_mixer_t;
typedef struct ado_pcm_subchn_mixer_config	ado_pcm_subchn_mixer_config_t;

enum	pcm_chn_type
{
	ADO_PCM_CHANNEL_PLAYBACK 	= SND_PCM_CHANNEL_PLAYBACK, 
	ADO_PCM_CHANNEL_CAPTURE		= SND_PCM_CHANNEL_CAPTURE,
};

enum pcm_status
{
	ADO_PCM_STATUS_NOTREADY 	= SND_PCM_STATUS_NOTREADY,
	ADO_PCM_STATUS_READY 		= SND_PCM_STATUS_READY,
	ADO_PCM_STATUS_PREPARED 	= SND_PCM_STATUS_PREPARED,
	ADO_PCM_STATUS_RUNNING		= SND_PCM_STATUS_RUNNING,
	ADO_PCM_STATUS_UNDERRUN 	= SND_PCM_STATUS_UNDERRUN,
	ADO_PCM_STATUS_OVERRUN		= SND_PCM_STATUS_OVERRUN,
	ADO_PCM_STATUS_PAUSED 		= SND_PCM_STATUS_PAUSED,
};

enum pcm_transfer_mode
{
	ADO_PCM_MODE_UNKNOWN	= SND_PCM_MODE_UNKNOWN,
	ADO_PCM_MODE_BLOCK		= SND_PCM_MODE_BLOCK,
	ADO_PCM_MODE_STREAM		= SND_PCM_MODE_STREAM,
};

enum pcm_start_mode
{
	ADO_PCM_START_DATA	= SND_PCM_START_DATA,
	ADO_PCM_START_FULL	= SND_PCM_START_FULL,
	ADO_PCM_START_GO	= SND_PCM_START_GO,
};

enum pcm_stop_mode
{
	ADO_PCM_STOP_STOP		= SND_PCM_STOP_STOP,
	ADO_PCM_STOP_ROLLOVER	= SND_PCM_STOP_ROLLOVER,
};

enum pcm_trigger
{
	ADO_PCM_TRIGGER_STOP,
	ADO_PCM_TRIGGER_GO,
	ADO_PCM_TRIGGER_SYNC_GO
};

enum pcm_pause
{
	ADO_PCM_PAUSE_RESUME = ADO_PCM_TRIGGER_GO,
	ADO_PCM_PAUSE_PAUSE = ADO_PCM_TRIGGER_GO + 100,
};

#define PCM_SUBCHN_TIME		(1<<0)
#define PCM_SUBCHN_UST_TIME	(1<<1)


/***** structures ***********/
struct	ado_pcm_cap
{
	uint32_t chn_flags;			/* SND_PCM_CHNINFO_* */
	uint32_t formats;			/* SND_PCM_FMT_* */
	uint32_t rates;				/* SND_PCM_RATE_* */
	uint32_t min_rate;			/* min rate */
	uint32_t max_rate;			/* max rate */
	struct	ratelist			/* used when SND_PCM_RATE_KNOT specified in rates */
	{
		int32_t		*list;
		uint32_t	list_len;
		void (*list_free)(void *data);
	}	ratelist;
	uint32_t min_voices;		/* min voices */
	uint32_t max_voices;		/* max voices */
	uint64_t voices_excluded;	/* excluded from range above */
	uint32_t min_fragsize;		/* min frag size */
	uint32_t max_fragsize;		/* max frag size */
	uint32_t max_dma_size;		/* maximum dma buffer size 0 == no limit */
	uint32_t max_frags;			/* maximum fragments 0 == no limit */
	uint32_t reserved[32];		/* reserved for future use */
};


struct	ado_pcm_hw
{
	int32_t	(*capabilities)(HW_CONTEXT_T *hw_context, snd_pcm_channel_info_t *info );
	int32_t	(*aquire)(HW_CONTEXT_T *hw_context, PCM_SUBCHN_CONTEXT_T **PCM_SUBCHN_CONTEXT, ado_pcm_config_t *config, ado_pcm_subchn_t *subchn, uint32_t *why_failed );
	int32_t	(*release)(HW_CONTEXT_T *hw_context, PCM_SUBCHN_CONTEXT_T *PCM_SUBCHN_CONTEXT, ado_pcm_config_t *config);
	int32_t (*prepare)(HW_CONTEXT_T *hw_context, PCM_SUBCHN_CONTEXT_T *PCM_SUBCHN_CONTEXT, ado_pcm_config_t *config);
	int32_t (*trigger)(HW_CONTEXT_T *hw_context, PCM_SUBCHN_CONTEXT_T *PCM_SUBCHN_CONTEXT, uint32_t cmd);
	uint32_t (*position)(HW_CONTEXT_T *hw_context, PCM_SUBCHN_CONTEXT_T *PCM_SUBCHN_CONTEXT, ado_pcm_config_t *config);
	int32_t (*reconstitute)(ado_pcm_config_t * config, int8_t *dmaptr, size_t size);
	int32_t	(*capabilities2)(HW_CONTEXT_T *hw_context, ado_pcm_t *pcm, snd_pcm_channel_info_t *info );
	uint32_t (*position2)(HW_CONTEXT_T *hw_context, PCM_SUBCHN_CONTEXT_T *PCM_SUBCHN_CONTEXT, ado_pcm_config_t *config);
	int32_t (*pause)(HW_CONTEXT_T *hw_context, PCM_SUBCHN_CONTEXT_T *PCM_SUBCHN_CONTEXT, uint32_t cmd);
	int32_t	(*subchn_capabilities)(HW_CONTEXT_T *hw_context, ado_pcm_subchn_t *subchn, snd_pcm_channel_info_t *info );
	void   	(*reserved_19)();		/* reserved for future use */
	void   	(*reserved_18)();		/* reserved for future use */
	void   	(*reserved_17)();		/* reserved for future use */
	void   	(*reserved_16)();		/* reserved for future use */
	void   	(*reserved_15)();		/* reserved for future use */
	void   	(*reserved_14)();		/* reserved for future use */
	void   	(*reserved_13)();		/* reserved for future use */
	void   	(*reserved_12)();		/* reserved for future use */
	void   	(*reserved_11)();		/* reserved for future use */
	void   	(*reserved_10)();		/* reserved for future use */
	void   	(*reserved_09)();		/* reserved for future use */
	void   	(*reserved_08)();		/* reserved for future use */
	void   	(*reserved_07)();		/* reserved for future use */
	void   	(*reserved_06)();		/* reserved for future use */
	void   	(*reserved_05)();		/* reserved for future use */
	void   	(*reserved_04)();		/* reserved for future use */
	void   	(*reserved_03)();		/* reserved for future use */
	void   	(*reserved_02)();		/* reserved for future use */
	void   	(*reserved_01)();		/* reserved for future use */
	void   	(*reserved_00)();		/* reserved for future use */
};


struct	ado_pcm_mmap	{
		snd_pcm_mmap_control_t	*control;
		size_t					size;
		char					name[QNX_SHM_NAME_LEN];
		uint32_t reserved[8];	/* reserved for future use */
};


struct	ado_pcm_dmabuf	{
		int8_t			*addr;
		size_t			size;
		uint32_t		flags; 		/* SEE ADO_SHMBUF_DMA_???? */
		off64_t			phys_addr;
		char			name[QNX_SHM_NAME_LEN];
		struct			cache_ctrl	*cache_ctrl;
		uint32_t		reserved[16];	/* reserved for future use */
};


struct	ado_pcm_config	{
	enum	pcm_transfer_mode	trans_mode;
	snd_pcm_format_t			format;
	union
	{
		struct
		{
			int32_t 		frag_size;
			int32_t			frags_min;
			int32_t			frags_max;
			int32_t			frags_total;
			ado_pcm_mmap_t	mmap;
			int32_t			spare[8];				/* reserved for future use */
		} 	block;
		struct
		{
			int32_t			queue_size;
			int32_t			fill;
			int32_t			max_fill;
		}	stream;
	}							mode;
	ado_pcm_dmabuf_t			dmabuf;
	int32_t						mixer_device;	/* mixer device */
	snd_mixer_eid_t				mixer_eid;		/* pcm subchn source element */
	snd_mixer_gid_t 			mixer_gid;		/* lowest level mixer group subchn specific */
	char					sw_mixer_subchn_name[32];	/* sw_mixer subchn name override */
	uint32_t				reserved[24];		/* reserved for future use */
};


struct ado_pcm_subchn_mixer_config
{
	HW_CONTEXT_T		 				*hw_context;
	PCM_SUBCHN_CONTEXT_T 				*pcm_sc_context;
	uint32_t							channel_mask;
	uint32_t							volume_jointly:1;
	snd_mixer_element_volume1_range_t	volume_range;
	uint32_t							mute_jointly:1;
	uint32_t							spare_1[16];
	void		(*volume_set) (HW_CONTEXT_T * hw_context, PCM_SUBCHN_CONTEXT_T * pcm_sc_context, uint32_t * volumes, int32_t mute, ado_pcm_subchn_mixer_config_t *config);
	void		(*mute_set) (HW_CONTEXT_T * hw_context, PCM_SUBCHN_CONTEXT_T * pcm_sc_context,  uint32_t * volumes, int32_t mute, ado_pcm_subchn_mixer_config_t *config);
	uint32_t							spare_2[16];
};


/*** function prototypes ****/

/* pcm.c */
int32_t ado_pcm_create ( ado_card_t *card , const char *name , uint32_t flags , const char *id , uint32_t play_subchns , ado_pcm_cap_t *play_cap , ado_pcm_hw_t *play_hw , uint32_t cap_subchns , ado_pcm_cap_t *cap_cap , ado_pcm_hw_t *cap_hw , ado_pcm_t **rpcm );
void ado_pcm_chn_mixer ( ado_pcm_t *pcm , enum pcm_chn_type type , ado_mixer_t *mixer , ado_mixer_delement_t *delement , ado_mixer_dgroup_t *dgroup );
void ado_pcm_subchn_mixer ( ado_pcm_subchn_t *subchn , ado_mixer_t *mixer , ado_mixer_delement_t *delement , ado_mixer_dgroup_t *dgroup );
uint32_t ado_pcm_playback_stop_artifact_protection( ado_pcm_subchn_t *subchn , uint16_t samples );
void dma_interrupt ( ado_pcm_subchn_t *subchn );
int32_t ado_pcm_symname ( ado_pcm_t *pcm , enum pcm_chn_type type , char *name );
int32_t ado_pcm_error ( ado_pcm_subchn_t *subchn , int32_t status );

/* pcm_helper.c */
uint32_t ado_pcm_dma_int_size ( ado_pcm_config_t *config );
ado_pcm_cap_t *ado_pcm_subchn_caps ( ado_pcm_subchn_t *subchn );
int32_t ado_pcm_subchn_is_channel ( ado_pcm_subchn_t *subchn , ado_pcm_t *pcm , enum pcm_chn_type chn_type );
size_t ado_pcm_format_bit_width ( int32_t format );
size_t ado_pcm_sample_bytes ( ado_pcm_config_t *config );
void ado_pcm_silence_fill ( void *buf , size_t length , int32_t format );
uint32_t ado_pcm_rate2flag ( uint32_t rate );
uint32_t ado_pcm_flag2rate ( uint32_t flag );
const char * ado_pcm_format_str (int format);

/* pcm_sw_mix.c */
int32_t ado_pcm_sw_mix ( ado_card_t *card , ado_pcm_t *pcm , ado_mixer_t *mixer );

/* pcm_subchn_mixer.c */
void ado_pcm_subchn_mixer_destroy ( ado_pcm_subchn_mixer_t *sc_mixer );
ado_pcm_subchn_mixer_t *ado_pcm_subchn_mixer_create ( ado_pcm_subchn_t *subchn , ado_mixer_t *mixer , ado_pcm_subchn_mixer_config_t *config );

int	pcm_devctl (uint32_t cmd, uint8_t *msg, uint16_t *msg_size, HW_CONTEXT_T *context, ado_pcm_t *pcm, PCM_SUBCHN_CONTEXT_T *PCM_SUBCHN_CONTEXT);

#endif /* _ADO_PCM_H_INCLUDED_ */

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/services/audio/public/include/ado_pcm.h $ $Rev: 230354 $" )
