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
 *      ado_mixer.h
 *              The main header for the mixer devices.
 */

#ifndef _ADO_MIXER_H_INCLUDED_
#define _ADO_MIXER_H_INCLUDED_


/***** typedefs *************/
typedef struct ado_mixer				ado_mixer_t;
typedef struct ado_mixer_dgroup			ado_mixer_dgroup_t;
typedef struct ado_mixer_devent			ado_mixer_devent_t;
typedef struct ado_mixer_devents		ado_mixer_devents_t;

typedef int32_t (ado_mixer_dll_init_t) (MIXER_CONTEXT_T **context, ado_mixer_t *mixer, void *params, void *callbacks, int dll_version);
typedef int32_t (ado_mixer_reset_t) (MIXER_CONTEXT_T *context);
typedef int32_t (ado_mixer_destroy_t) (MIXER_CONTEXT_T *context);
typedef	int32_t (ado_mixer_dgroup_control_t)(MIXER_CONTEXT_T *context, ado_mixer_dgroup_t *group, uint8_t set, snd_mixer_group_t *data, void *instance_data );


/***** typedefs *************/
typedef	struct	ado_mixer_delement	ado_mixer_delement_t;
typedef int32_t (element_info_t) (resmgr_context_t * ctp, int32_t offset, ado_mixer_t * mixer, ado_mixer_delement_t * delement, snd_mixer_element_info_t * info);
typedef int32_t (element_control_t) (resmgr_context_t * ctp, int32_t offset, ado_mixer_t * mixer, ado_mixer_delement_t * delement, uint8_t set, snd_mixer_element_t * element);

typedef int32_t (ado_mixer_delement_control_sw1_t)(MIXER_CONTEXT_T *context, ado_mixer_delement_t *element, uint8_t set, uint32_t *bitmap, void *instance_data);
typedef int32_t (ado_mixer_delement_control_sw2_t)(MIXER_CONTEXT_T *context, ado_mixer_delement_t *element, uint8_t set, uint32_t *val, void *instance_data);
typedef int32_t (ado_mixer_delement_control_sw3_t)(MIXER_CONTEXT_T *context, ado_mixer_delement_t *element, uint8_t set, uint32_t *bitmap, void *instance_data);
typedef int32_t (ado_mixer_delement_control_volume1_t)(MIXER_CONTEXT_T *context, ado_mixer_delement_t *element, uint8_t set, uint32_t *volumes, void *instance_data);
typedef int32_t (ado_mixer_delement_control_accu3_t)(MIXER_CONTEXT_T *context, ado_mixer_delement_t *element, uint8_t set, uint32_t *voices, void *instance_data);
typedef int32_t (ado_mixer_delement_control_mux1_t)(MIXER_CONTEXT_T *context, ado_mixer_delement_t *element, uint8_t set, ado_mixer_delement_t **inelements, void *instance_data);
typedef int32_t (ado_mixer_delement_control_mux2_t)(MIXER_CONTEXT_T *context, ado_mixer_delement_t *element, uint8_t set, ado_mixer_delement_t **inelement, void *instance_data);
typedef int32_t (ado_mixer_delement_control_tonecontrol1_t)(MIXER_CONTEXT_T *context, ado_mixer_delement_t *element, uint8_t set, struct snd_mixer_element_tone_control1 *tc1, void *instance_data);
typedef int32_t (ado_mixer_delement_control_pancontrol1_t)(MIXER_CONTEXT_T *context, ado_mixer_delement_t *element, uint8_t set, uint32_t *pan, void *instance_data);
typedef int32_t (ado_mixer_delement_control_3deffect1_t)(MIXER_CONTEXT_T *context, ado_mixer_delement_t *element, uint8_t set, struct snd_mixer_element_3d_effect1 *effect1, void *instance_data);


/*** function prototypes ****/

/* mixer.c */
void ado_mixer_set_name ( ado_mixer_t *mixer , char *name );
void ado_mixer_set_reset_func ( ado_mixer_t *mixer , ado_mixer_reset_t *reset );
void ado_mixer_set_destroy_func ( ado_mixer_t *mixer , ado_mixer_destroy_t *destroy );
MIXER_CONTEXT_T *ado_mixer_get_context ( ado_mixer_t *mixer );
void *ado_mixer_get_dll_handle (ado_mixer_t * mixer);
void *ado_mixer_get_element_instance_data ( ado_mixer_delement_t *delement );
int32_t ado_mixer_element_vol_range_min ( ado_mixer_delement_t *delement );
int32_t ado_mixer_element_vol_range_max ( ado_mixer_delement_t *delement );
int32_t ado_mixer_lock ( ado_mixer_t *mixer );
int32_t ado_mixer_unlock ( ado_mixer_t *mixer );
int32_t ado_mixer_create ( ado_card_t *card , char *id , ado_mixer_t **rmixer , MIXER_CONTEXT_T *context );
ado_mixer_dgroup_t *ado_mixer_playback_group_create ( ado_mixer_t *mixer , char *name , uint32_t channels , ado_mixer_delement_t *vol_elem , ado_mixer_delement_t *mute_elem );
ado_mixer_dgroup_t *ado_mixer_capture_group_create ( ado_mixer_t *mixer , char *name , uint32_t channels , ado_mixer_delement_t *vol_elem , ado_mixer_delement_t *mute_elem , ado_mixer_delement_t *cap_elem , ado_mixer_delement_t *mux_in_elem );
void ado_mixer_group_destroy ( ado_mixer_t *mixer , ado_mixer_dgroup_t *dgroup );
ado_mixer_dgroup_t *ado_mixer_find_group ( ado_mixer_t *mixer , char *name , int32_t index );
ado_dswitch_t *ado_mixer_switch_new ( ado_mixer_t *mixer , char *name , uint32_t type , uint32_t subtype , int32_t (*sw_read )(MIXER_CONTEXT_T *context ,ado_dswitch_t *dswitch ,snd_switch_t *cswitch ,void *instance_data ), int32_t (*sw_write )(MIXER_CONTEXT_T *context ,ado_dswitch_t *dswitch ,snd_switch_t *cswitch ,void *instance_data ), void *instance_data , void (*instance_free )(void *data ));
void ado_mixer_switch_destroy ( ado_mixer_t *mixer , ado_dswitch_t *dswitch );
int32_t ado_mixer_dll ( ado_card_t *card , char *mixer_dll , uint32_t dll_version , void *params , void *callbacks , ado_mixer_t **rmixer );

/* mixer_elem.c */
ado_mixer_delement_t *ado_mixer_find_element ( ado_mixer_t *mixer , int32_t type , char *name , int32_t index );
ado_mixer_delement_t *ado_mixer_element_io ( ado_mixer_t *mixer , char *name , int32_t type , uint32_t attrib , uint32_t number_of_voices , snd_mixer_voice_t *voices );
ado_mixer_delement_t *ado_mixer_element_pcm1 ( ado_mixer_t *mixer , char *name , int32_t type , uint32_t number_of_devices , int32_t *devices );
ado_mixer_delement_t *ado_mixer_element_pcm2 ( ado_mixer_t *mixer , char *name , uint32_t type , int32_t device , int32_t subdevice );
ado_mixer_delement_t *ado_mixer_element_converter ( ado_mixer_t *mixer , char *name , uint32_t type , uint32_t resolution );
ado_mixer_delement_t *ado_mixer_element_sw1 ( ado_mixer_t *mixer , char *name , uint32_t number_of_switches , ado_mixer_delement_control_sw1_t *control , void *instance_data , void (*instance_free )(void *data ));
ado_mixer_delement_t *ado_mixer_element_sw2 ( ado_mixer_t *mixer , char *name , ado_mixer_delement_control_sw2_t *control , void *instance_data , void (*instance_free )(void *data ));
ado_mixer_delement_t *ado_mixer_element_sw3 ( ado_mixer_t *mixer , char *name , uint32_t type , uint32_t number_of_voices , snd_mixer_voice_t *voices , ado_mixer_delement_control_sw3_t *control , void *instance_data , void (*instance_free )(void *data ));
ado_mixer_delement_t *ado_mixer_element_volume1 ( ado_mixer_t *mixer , char *name , uint32_t number_of_voices , struct snd_mixer_element_volume1_range *ranges , ado_mixer_delement_control_volume1_t *control , void *instance_data , void (*instance_free )(void *data ));
ado_mixer_delement_t *ado_mixer_element_accu1 ( ado_mixer_t *mixer , char *name , int32_t attenuation );
ado_mixer_delement_t *ado_mixer_element_accu2 ( ado_mixer_t *mixer , char *name , int32_t attenuation );
ado_mixer_delement_t *ado_mixer_element_accu3 ( ado_mixer_t *mixer , char *name , uint32_t number_of_voices , struct snd_mixer_element_accu3_range *ranges , ado_mixer_delement_control_accu3_t *control , void *instance_data , void (*instance_free )(void *data ));
ado_mixer_delement_t *ado_mixer_element_mux1 ( ado_mixer_t *mixer , char *name , uint32_t attrib , uint32_t number_of_voices , ado_mixer_delement_control_mux1_t *control , void *instance_data , void (*instance_free )(void *data ));
ado_mixer_delement_t *ado_mixer_element_mux2 ( ado_mixer_t *mixer , char *name , uint32_t attrib , ado_mixer_delement_control_mux2_t *control , void *instance_data , void (*instance_free )(void *data ));
ado_mixer_delement_t *ado_mixer_element_tone_control1 ( ado_mixer_t *mixer , char *name , struct snd_mixer_element_tone_control1_info *info , ado_mixer_delement_control_tonecontrol1_t *control , void *instance_data , void (*instance_free )(void *data ));
ado_mixer_delement_t *ado_mixer_element_pan_control1 ( ado_mixer_t *mixer , char *name , int32_t number_of_pans , struct snd_mixer_element_pan_control1_range *ranges , ado_mixer_delement_control_pancontrol1_t *control , void *instance_data , void (*instance_free )(void *data ));
ado_mixer_delement_t *ado_mixer_element_3d_effect1 ( ado_mixer_t *mixer , char *name , struct snd_mixer_element_3d_effect1_info *info , ado_mixer_delement_control_3deffect1_t *control , void *instance_data , void (*instance_free )(void *data ));
void ado_mixer_element_notify ( ado_mixer_t *mixer , ado_mixer_delement_t *delement , uint32_t cmd , ado_ocb_t *ocb );
void ado_mixer_element_destroy ( ado_mixer_t *mixer , ado_mixer_delement_t *delement );
int32_t ado_mixer_element_route_add ( ado_mixer_t *mixer , ado_mixer_delement_t *elem_before , ado_mixer_delement_t *elem );


void version (int *major, int *minor, char *date);
int32_t mixer_dll_init (MIXER_CONTEXT_T **context, ado_mixer_t *mixer, void *params, void *callbacks, int dll_version);
int	mixer_devctl (uint32_t cmd, uint8_t *msg, uint16_t *msg_size, MIXER_CONTEXT_T *context);

#endif /* _ADO_MIXER_H_INCLUDED_ */

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/services/audio/public/include/ado_mixer.h $ $Rev: 222059 $" )
