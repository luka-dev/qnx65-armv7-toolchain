/* Copyright 2009, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to 
 * QNX Software Systems before you may reproduce, modify or distribute this 
 * software, or any work that includes all or part of this software.  Free 
 * development licenses are available for evaluation and non-commercial purposes.  
 * For more information visit http://licensing.qnx.com or email licensing@qnx.com.
 * 
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 */
/* PhAB resource editors plugin API */

#if !defined(RES_PLUGIN_API_H_INCLUDED)
#define RES_PLUGIN_API_H_INCLUDED
 
#include <Pt.h>
#include <photon/PtWidget.h>

#if defined(__cplusplus)
  extern "C" {
#endif


/* the enumeration of possible datatypes */
typedef enum {
	RES_DATATYPE_STRING,
	RES_DATATYPE_MULTI,
	RES_DATATYPE_CODE,
	RES_DATATYPE_FONT,
	RES_DATATYPE_COLOR,
	RES_DATATYPE_DOUBLE,
	RES_DATATYPE_NUMERIC,
	RES_DATATYPE_CHOICE,
	RES_DATATYPE_FLAG,
	RES_DATATYPE_PATTERN,
	RES_DATATYPE_LIST,
	RES_DATATYPE_PIXMAP,
	RES_DATATYPE_ALLOC,

	RES_DATATYPE_LIMIT
	} ResDatatype_t;


/* values for the argument of PhABExportSetStateF_t */
typedef enum  {
	RESPLUGIN_STATE_DISABLED,
	RESPLUGIN_STATE_MATCH_DEFAULT,
	RESPLUGIN_STATE_MATCH_MASTER,
	RESPLUGIN_STATE_MATCH_DEFAULT_MASTER,
	RESPLUGIN_STATE_NO_MATCH,
	RESPLUGIN_STATE_BLOCKED,
	RESPLUGIN_STATE_UNBLOCKED
	} ResFullWindowState_t;

typedef enum {
	RESPLUGIN_ACTION_DEFAULT,
	RESPLUGIN_ACTION_CLOSE,
	RESPLUGIN_ACTION_APPLY
	} ResPluginAction_t;


/* handles */
typedef struct ResPluginHandle_ * ResPluginHandle_t;
typedef struct PhABHandle_ * PhABHandle_t;
typedef struct PhabResWindowHandle_ * PhabResWindowHandle_t;

typedef struct ResPluginCommon_ ResPluginCommon_t;
typedef struct ResPluginFrugalEditor_ ResPluginFrugalEditor_t;
typedef struct ResPluginFullEditor_ ResPluginFullEditor_t;
typedef struct PhABResExportCommon_ PhABResExportCommon_t;
typedef struct PhABResExportFrugal_ PhABResExportFrugal_t;
typedef struct PhABResExportFull_ PhABResExportFull_t;
typedef struct ResPluginFormatData_	ResPluginFormatData_t;



/* the loading DLL / unloading DLL methods */
typedef int ResPluginLoadingF_t ( const char *path );
typedef void ResPluginUnloadingF_t( void );

/* the methods in the ResPluginCommon_t, common to the full editor and to the frugal editor */
typedef void ResPluginSetDataF_t( ResPluginHandle_t handle, int n, const void *value, const ResPluginFormatData_t *format );
typedef void ResPluginDestroyF_t( ResPluginHandle_t handle );

/* the methods specific for the frugal editor */
typedef ResPluginHandle_t
			ResPluginFrugalCreateF_t 
				( PhABHandle_t phab , const PhABResExportFrugal_t *exp,
					const ResPluginFormatData_t *format, 
					int n_default, const void *default_value,
					PtWidget_t *parent,
					int n, const void *value );


/* the methods specific for the full editor */
typedef ResPluginHandle_t
			ResPluginFullCreateF_t
				( PhABHandle_t phab , const PhABResExportFull_t *exp,
					const ResPluginFormatData_t *format,
					int n_default, const void *default_value,
					PhArea_t *area, char *caption,
					int n, const void *value );
typedef void ResPluginDisableF_t ( ResPluginHandle_t handle );
typedef void ResPluginBlockF_t ( ResPluginHandle_t handle, int block );
typedef void ResPluginToFrontF_t ( ResPluginHandle_t handle );
typedef int ResPluginAnyChangesF_t ( ResPluginHandle_t handle );
typedef void ResPluginGetChangesF_t ( ResPluginHandle_t handle, int *pn, void **pvalue );
typedef void ResPluginGetAreaF_t ( ResPluginHandle_t handle, PhArea_t *area );

/* functions exported from phab to the plugin, used by both editors */
typedef int PhABExportApplyF_t ( PhABHandle_t phab, int n, void *value );
typedef void PhABExportGetResF_t ( ResDatatype_t type, char *abstract_name_editor, ResPluginFrugalEditor_t **pfrugal_editor, ResPluginFullEditor_t **pfull_editor );

/* functions exported from phab to the plugin, used by the frugal editor only */
typedef void PhABExportOpenF_t  ( PhABHandle_t phab );

/* functions exported from phab to the plugin, used by the full editor only */
typedef void PhABExportClosingF_t  ( PhABHandle_t phab );
typedef void PhABExportAnswerChangesF_t ( PhABHandle_t phab, int answer, int n, void *pvalue );

typedef void ResPluginActionNotifyF_t ( ResPluginAction_t action, void *notify_data );

/* convenience functions exported from phab to the full editor plugin */
typedef PhabResWindowHandle_t PhABExportCreateWindowF_t
												(	PhArea_t *area,
													char *caption,
													unsigned int flags,
													PtWidget_t **container,
													ResPluginActionNotifyF_t *notify,
													void *notify_data );
typedef void PhABExportSetStateF_t ( PhabResWindowHandle_t wnd, ResFullWindowState_t state );
typedef void PhABExportToFrontF_t ( PhabResWindowHandle_t wnd );
typedef void PhABExportGetAreaF_t ( PhabResWindowHandle_t wnd, PhArea_t *area );
typedef void PhABExportDestroyF_t ( PhabResWindowHandle_t wnd );

/* memory allocation functions */
typedef char* PhABExportAllocMemF_t ( int size );
typedef void PhABExportFreeMemF_t ( char *p );
typedef PhImage_t* PhABExportAllocImageF_t  ( PhImage_t *src, int flags );
typedef void PhABExportFreeImageF_t ( PhImage_t *p );
typedef int PhABExportCmpF_t ( ResDatatype_t type, int n1, void *v1, int n2, void *v2 );
typedef void PhABExportDupF_t ( ResDatatype_t type, int n, void *v, int *dest_n, void **dest_value );
typedef void PhABExportFreeF_t ( ResDatatype_t type, int n, void *v );
typedef int PhABExportMessageF_t ( char *message, char *button1, char *button2, char *button3, int default_button );

typedef struct ResPlugin_ {
  ResPluginLoadingF_t *loading;
  ResPluginUnloadingF_t *unloading;
  int n_full_editors;
  const ResPluginFullEditor_t* full_editors;
  int n_frugal_editors;
  const ResPluginFrugalEditor_t* frugal_editors;
  } ResPlugin_t;


/* structure used by both editors */
struct ResPluginCommon_ {
  const char *name;
  ResDatatype_t datatype;
  int datatype_version;

  /* the common functions */
  const ResPluginSetDataF_t *set_data;
  const ResPluginDestroyF_t *destroy;

  };


/* the frugal editor structure */
struct ResPluginFrugalEditor_ {

  /* the common stuff */
  ResPluginCommon_t common;

  /* the frugal editor */
  ResPluginFrugalCreateF_t *create;

  };


/* the full editor structure */
struct ResPluginFullEditor_ {

  /* the common stuff */
  ResPluginCommon_t common;

  /* the full editor */
  ResPluginFullCreateF_t *create;
  ResPluginDisableF_t *disable;
  ResPluginBlockF_t *block;
  ResPluginToFrontF_t *to_front;
  ResPluginAnyChangesF_t *any_changes;
  ResPluginGetChangesF_t *get_changes;
  ResPluginGetAreaF_t *get_area;

  };


/* the phab exported structure, common to both editors */
struct PhABResExportCommon_ {
  PhABExportApplyF_t *apply;

	/* ATENTIE remove these */
  PhABExportAllocMemF_t *alloc_mem;
  PhABExportFreeMemF_t *free_mem;

	/* ATENTIE remove these */
  PhABExportAllocImageF_t *alloc_image;
  PhABExportFreeImageF_t *free_image;

	PhABExportCmpF_t *cmp;
	PhABExportDupF_t *dup;
	PhABExportFreeF_t *free;

	PhABExportGetResF_t *get_res;
	PhABExportMessageF_t *message;
  };


/* the phab exported structure, used by the frugal editor */
struct PhABResExportFrugal_ {
  PhABResExportCommon_t common;

  PhABExportOpenF_t *open;
  };

/* the phab exported structure, used by the full editor */
struct PhABResExportFull_ {
  PhABResExportCommon_t common;

  PhABExportClosingF_t *closing;
  PhABExportAnswerChangesF_t *answer_changes;

  PhABExportCreateWindowF_t *create_window;
  PhABExportSetStateF_t *set_state;
  PhABExportToFrontF_t *to_front;
	PhABExportGetAreaF_t *get_area;
	PhABExportDestroyF_t *destroy;
  };

/* format data structure */
struct ResPluginFormatData_ {
	int n;
	const void *value;
	};

/* format for numeric datatype */
typedef struct {
	int64_t min;
	int64_t max;
	} ResPluginNumericFormat_t;

/* format for choice datatype */
typedef struct {
	char *name;
	long value;
	} ResPluginChoiceFormat_t;

/* format for flag datatype */
typedef struct {
	char *name;
	unsigned long value;
	unsigned long mask;
	} ResPluginFlagFormat_t;

/* format for double datatype */
typedef struct {
	double min;
	double max;
	} ResPluginDoubleFormat_t;

/* format for code datatype */
typedef struct {
	char *prototype;
	} ResPluginCodeFormat_t;

/* format for pixmap datatype */
typedef struct {
	unsigned int preferred_w;
	unsigned int preferred_h;
	} ResPluginPixmapFormat_t;

/* values used by ResPluginAnyChangesF_t and PhABExportAnswerChangesF_t */
#define	RESPLUGIN_NO_CHANGES		0
#define	RESPLUGIN_CHANGES				1
#define	RESPLUGIN_WAIT					2

/* flag values for PhABExportAllocImageF_t */
#define	RESPLUGIN_IMAGE_ALPHA_MAP					0x01
#define RESPLUGIN_IMAGE_TRANSPARENT_MAP		0x02

/* flag values for PhABExportCreateWindowF_t */
#define RESPLUGIN_FIXED_SIZE							0x1

/* for the font format */
#define RES_DATATYPE_FONT_FIXED   0x1

/* this api's version, used in the AOInterface_t declaration */
#define RESPLUGIN_VERSION     			202

/* the datatype_version */
#define RESPLUGIN_DATATYPE_VERSION  1

#if defined(__cplusplus)
  }
#endif

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ap/public/photon/res_plugin_api.h $ $Rev: 224582 $" )
#endif
