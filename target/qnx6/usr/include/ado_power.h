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
 *      ado_power.h
 *              The main header for the power management.
 */

#ifndef _ADO_POWER_H_INCLUDED_
#define _ADO_POWER_H_INCLUDED_


/***** typedefs *************/
typedef struct ado_hw_power			ado_hw_pwr_t;

enum	ado_pm_ops
{
	ADO_PM_OP_CODEC_STATE_GET	= (1<<0),
	ADO_PM_OP_CODEC_STATE_SET	= (1<<1),
	ADO_PM_OP_CTRL_STATE_GET	= (1<<4),
	ADO_PM_OP_CTRL_STATE_SET	= (1<<5),
	ADO_PM_OP_STREAM_PLAY		= (1<<8),
	ADO_PM_OP_STREAM_CAP		= (1<<9),
};

#define	PWR_MD_FLG_PWR_LOST		(1<<0)			/* power to device may have been lost in previous mode */

#define ADO_MODE_DEF(p,lm,pm,flg,op)	{	pmd_mode_attr_t *ptr = p;			\
											(ptr)->mode=PM_DEVICE_MODE(lm,pm);	\
											(ptr)->flags=flg;					\
											(ptr)->drvprivate.flags=op; }

/***** structures ***********/

struct	ado_hw_power
{
	pmd_mode_attr_t		*modes;
	int					num_modes;
	ps_objid_t			ps_name;
	int					num_ps_objs;
	size_t				*ps_sizes;
	int32_t				(*load_persistent) (POWER_CONTEXT_T *pwr_context, ps_handle_t **ps_handles);
	int32_t				(*save_persistent) (POWER_CONTEXT_T *pwr_context, ps_handle_t **ps_handles);
	int32_t				(*setmode) (POWER_CONTEXT_T *pwr_context, const pmd_mode_attr_t *mode_attr, uint32_t pwr_md_flgs);
	int32_t			 	reserved[8];		/* reserved for future use */
};

/*** function prototypes ****/

/* power.c */
int32_t ado_add_powermgt ( ado_card_t *card , POWER_CONTEXT_T *context , ado_hw_pwr_t *power );
ps_objid_t *ado_ps_obj_id_from_addr32 ( uint32_t addr , ps_objid_t *objid );
ps_objid_t *ado_ps_obj_id_from_io32 ( uint32_t addr , ps_objid_t *objid );
ps_objid_t *ado_ps_obj_id_from_pci ( void *handle , ps_objid_t *objid );
size_t ado_persistent_read ( ps_handle_t *hdl , void *buffer , size_t size );
size_t ado_persistent_write ( ps_handle_t *hdl , void *buffer , size_t size );

#endif /* _ADO_POWER_H_INCLUDED_ */

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/services/audio/public/include/ado_power.h $ $Rev: 219613 $" )
