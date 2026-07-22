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
/* Photon shelf manager plugin API */

#if !defined(SHELFMAN_H_INCLUDED)
#define SHELFMAN_H_INCLUDED

#include <photon/PtWidget.h>

#if defined(__cplusplus)
	extern "C" {
#endif

#if !defined(PSH_PLUGIN_HANDLE)
	#define PSH_PLUGIN_HANDLE struct PshPluginHandle
#endif
#if !defined(PSH_SHELFMAN_HANDLE)
	#define PSH_SHELFMAN_HANDLE struct PshShelfmanHandle
#endif

typedef PSH_SHELFMAN_HANDLE *PshShelfmanHandle_t; /* The shelf manager's object poiner   */
typedef PSH_PLUGIN_HANDLE   *PshPluginHandle_t;   /* The plugin's object pointer         */

typedef enum PshPluginPropsFlags {
	PSH_IS_VERTICAL        = 0x01,
	PSH_WIDTH_FIXED        = 0x02,
	PSH_HEIGHT_FIXED       = 0x04,
	}
		PshPluginPropsFlags_t;

typedef struct PshPluginProps {
	PshPluginPropsFlags_t lflags;
	PhDim_t size;                      /* The size the plugin would like to be           */
	PhDim_t minsize;                   /* The minimum size the plugin can accept         */
	PhDim_t maxsize;                   /* The maximum size the plugin can accept         */
	const char *name;                  /* Instance name (R/O)                            */
	}
		PshPluginProps_t;

typedef struct PshCfgFileR PshCfgFileR_t; /* Pseudo-file descriptor for reading config   */
typedef struct PshCfgFileW PshCfgFileW_t; /* Pseudo-file descriptor for writing config   */

/* Plugin's calls and callbacks: */
typedef struct PshShelfmanCalls      PshShelfmanCalls_t;
typedef struct PshPluginCalls        PshPluginCalls_t;
typedef struct PshCfgReaders         PshCfgReaders_t;
typedef struct PshCfgWriters         PshCfgWriters_t;
typedef struct PshShelfmanToolFuns   PshShelfmanToolFuns_t;
typedef struct PshShelfmanCallbacks  PshShelfmanCallbacks_t;

typedef int   PshPluginLoadedF_t( const char *path, PshShelfmanCalls_t const *cbs );
typedef void  PshPluginUnloadingF_t( void );
typedef PshPluginHandle_t PshPluginInitF_t( PshShelfmanHandle_t shandle, PshCfgFileR_t *cfg, PshShelfmanCalls_t const *cbs );
typedef void  PshPluginExitF_t(     PshPluginHandle_t phandle );
typedef int   PshPluginSaveF_t(     PshPluginHandle_t phandle, PshCfgFileW_t *cfg, PshCfgWriters_t const *writers );
typedef void  PshPluginGetPropsF_t( PshPluginHandle_t phandle, PshPluginProps_t *props, PshShelfmanToolFuns_t const *tools );
typedef int   PshPluginPopulateF_t( PshPluginHandle_t phandle, PshPluginProps_t const *props, PtWidget_t *pane );
typedef void *PshPluginCfgInitF_t(  PshPluginHandle_t phandle, PtWidget_t *pane );
typedef void  PshPluginCfgApplyF_t( PshPluginHandle_t phandle, void *cfghandle );

struct PshPluginCalls {
	const char            *name;          /* A description of your plugin                         */
	PshPluginLoadedF_t    *loaded;        /* Called after DLL is loaded                           */
	PshPluginUnloadingF_t *unloading;     /* Called before DLL is unloaded                        */
	PshPluginInitF_t      *init;          /* Initialize a new object, read config if cfg != NULL  */
	PshPluginExitF_t      *exit;          /* Destroy the object                                   */
	PshPluginSaveF_t      *save;          /* Save config                                          */
	PshPluginGetPropsF_t  *getprops;      /* Get preferred size, flags, etc                       */
	PshPluginPopulateF_t  *populate;      /* Put widgets in the PtPane                            */
	PshPluginCfgInitF_t   *cfginit;       /* Put widgets in the config dialog                     */
	PshPluginCfgApplyF_t  *cfgapply;      /* Apply settings from config dialog                    */
	};

struct PshCfgReaders {
	int (*c)( PshCfgFileR_t *fp );
	int (*n)( PshCfgFileR_t *fp, void *data, unsigned len );
	int (*mark)( PshCfgFileR_t *fp );
	int (*back)( PshCfgFileR_t *fp );
	};

struct PshCfgWriters {
	int (*c)( PshCfgFileW_t *fp, unsigned char ch );
	int (*n)( PshCfgFileW_t *fp, void const *data, unsigned len );
	};

struct PshShelfmanToolFuns {
	PtWidget_t *(*tmpwgt)( void );
	PtWidget_t *(*mktmpwgt)( void );
	void (*rmtmpwgt)( PtWidget_t * );
	void (*popopn)( PshShelfmanHandle_t );
	void (*popcls)( PshShelfmanHandle_t );
	};

struct PshShelfmanCallbacks {
	void (*action)( PshShelfmanHandle_t shandle );
	};

struct PshShelfmanCalls {
	PshCfgReaders_t         read;
	PshCfgWriters_t         write;
	PshShelfmanToolFuns_t   tools;
	PshShelfmanCallbacks_t  cb;
	};

#if !defined(PSH_STATIC_PLUGIN)
	#define PSH_STATIC_PLUGIN 0
#endif

#define PshCallsTable PshCallsTab100

#define PSH_GLUE_STRINGS( a, b ) a ## b
#define PSH_GLUE_MACROS( a, b ) PSH_GLUE_STRINGS( a, b )
#define PSH_STATIC_TABLE_NAME( suffix ) PSH_GLUE_MACROS( PshCalls_, suffix )
#define PSH_ADD_SUFFIX( prefix ) PSH_GLUE_MACROS( prefix, PSH_PLUGIN_NAME )

#if PSH_STATIC_PLUGIN
	#if defined(PSH_PLUGIN_NAME)
		#undef PshCallsTable
		#define PshCallsTable PSH_STATIC_TABLE_NAME( PSH_PLUGIN_NAME )
	#endif

	#if defined(PSH_PLUGIN_NAME)
		/* Tricks for PhAB plugins */
		#include <Ap.h>

		#define main PSH_ADD_SUFFIX( main_ )
		#define ApOptions PSH_ADD_SUFFIX( ApOptions_ )
		#define AbContext PSH_ADD_SUFFIX( AbContext_ )
		#define AbInternalLinks PSH_ADD_SUFFIX( AbIl_ )
	
		extern ApContext_t AbContext;
		extern ApEventLink_t AbInternalLinks[];
	#endif
#endif


/* Defined by the plugin */
extern const PshPluginCalls_t PshCallsTable;

#if defined(__cplusplus)
	}
#endif

#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/apps/shelf/src/shelfman.h $ $Rev: 224568 $" )
