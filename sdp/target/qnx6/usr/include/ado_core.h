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
 *      ado_core.h
 *              The core header for audio drivers.
 */

#ifndef _ADO_CORE_H_INCLUDED_
#define _ADO_CORE_H_INCLUDED_


/***** defines **************/
#define ADO_MAJOR_VERSION 			5



/***** typedefs **************/
#ifndef	HW_CONTEXT_T
typedef	struct hw_context HW_CONTEXT_T;
#endif

#ifndef	PCM_SUBCHN_CONTEXT_T
typedef	struct pcm_subchn_context PCM_SUBCHN_CONTEXT_T;
#endif

#ifndef	MIXER_CONTEXT_T
typedef	struct mixer_context MIXER_CONTEXT_T;
#endif

#ifndef	POWER_CONTEXT_T
typedef	HW_CONTEXT_T POWER_CONTEXT_T;
#endif

typedef struct ado_card				ado_card_t;
typedef struct ado_dswitch			ado_dswitch_t;

typedef void (ado_dll_version_t) (int *major, int *minor, char *date);
typedef int32_t (ado_ctrl_dll_init_t) (HW_CONTEXT_T **hw_context, ado_card_t * card, char *args);
typedef int32_t (ado_ctrl_dll_destroy_t) (HW_CONTEXT_T *hw_context);




/***** structures ************/
struct	global_options
{
int32_t		db_lvl;
int32_t		config_write_delay;			/* seconds 0=immediate,-1=never */
uint32_t	max_dma_buf_size;
uint16_t	status_accuracy;			/* required accuracy in ms */
uint16_t	disable_sw_mixer;			/* 0 to enable sw-mixer, 1 to disable */
uint32_t	intr_thread_prio;			/* priority of the interrupt thread */
uint32_t	sw_mixer_samples;	
enum 		{ SWMIX_RM_FAHQ, SWMIX_RM_FA, SWMIX_RM_LOCKED } sw_mixer_rate_method;
uint32_t	sw_mixer_rate_rate;
};



/***** externs  **************/
extern	struct	global_options global_options;



/*** function prototypes ****/

/* intr.c */
int32_t ado_attach_interrupt ( ado_card_t *card , int32_t irq , void (*handler )(HW_CONTEXT_T *hw_context ,int32_t ), HW_CONTEXT_T *hw_context );
void ado_detach_interrupts ( ado_card_t *card );

void ctrl_version (int *major, int *minor, char *date);
int32_t ctrl_init (HW_CONTEXT_T **hw_context, ado_card_t * card, char *args);
int32_t ctrl_destroy (HW_CONTEXT_T *hw_context);
int	ctrl_devctl (uint32_t cmd, uint8_t *msg, uint16_t *msg_size, HW_CONTEXT_T *context);

paddr_t mphys(void *addr);	/* this is an obsolute call but useful for debugging (it may disappear ) */

#endif	 /* _ADO_CORE_H_INCLUDED_ */

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/services/audio/public/include/ado_core.h $ $Rev: 219613 $" )
