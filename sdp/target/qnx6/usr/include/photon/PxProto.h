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



#ifndef PX_PROTO_INCLUDED
#define PX_PROTO_INCLUDED

/*
 * PxProto.h	
 *		Prototypes for the Photon Extended (Px) library
 *

 */

#ifdef __WATCOMC__
#if __WATCOMC__ < 1000
#define __NO_MBSTRING_H__
#endif
#endif

#ifndef _STDLIB_H_INCLUDED
#include <stdlib.h>
#endif

#ifndef _LIMITS_H_INCLUDED
#include <limits.h>
#endif

#ifndef __PT_T_H_INCLUDED
#include <photon/PtT.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define PXCONFIG_READ	0x00
#define PXCONFIG_WRITE	0x01
#define PXCONFIG_CLEAR	0x04
#define PXCONFIG_CREATE	PXCONFIG_CLEAR
#define PXCONFIG_UNLINK	0x08
#define PXCONFIG_HOME	0x10
#define PXCONFIG_GLOBAL	0x20
#define	PXCONFIG_DUPKEY	0x40

#define PXCONFIG_FMT_BOOL_ON		1
#define PXCONFIG_FMT_BOOL_YES		2
#define PXCONFIG_FMT_BOOL_TRUE		3
#define PXCONFIG_FMT_CHAR_CHAR		11
#define PXCONFIG_FMT_CHAR_HEX		12
#define PXCONFIG_FMT_INT_DECIMAL	21
#define PXCONFIG_FMT_INT_HEX		22
#define PXCONFIG_FMT_STRING			31
#define PXCONFIG_FMT_DOUBLE			41

typedef struct px_cfg_context PxCfgContext_t;

extern PxCfgContext_t	*PxConfigGetCx(void);
extern int				PxConfigSetCx(PxCfgContext_t *cx);

#define PxConfigOpen(f,m)			(((PxConfigSetCx(NULL) || Pt_TRUE) && PxConfigSetCx(PxConfigOpenCx(f,m)) && PxConfigGetCx()) ? Pt_TRUE : Pt_FALSE)
#define PxConfigClose()				PxConfigSetCx(NULL)
#define PxConfigSection(s)			PxConfigSectionCx(PxConfigGetCx(),s)
#define PxConfigFirstSection()		PxConfigFirstSectionCx(PxConfigGetCx())
#define PxConfigNextSection()		PxConfigNextSectionCx(PxConfigGetCx())
#define PxConfigNextString(v,m)		PxConfigNextStringCx(PxConfigGetCx(),v,m)
#define	PxConfigNextArgs(v,m,a,ma,n)	PxConfigNextArgsCx(PxConfigGetCx(),v,m,a,ma,n)
#define PxConfigNextEntry(v)			PxConfigNextEntryCx(PxConfigGetCx(),v)
#define PxConfigReadBool(s,e,d,v)	PxConfigReadBoolCx(PxConfigGetCx(),s,e,d,v)
#define PxConfigReadChar(s,e,d,v)	PxConfigReadCharCx(PxConfigGetCx(),s,e,d,v)
#define PxConfigReadShort(s,e,d,v)	PxConfigReadShortCx(PxConfigGetCx(),s,e,d,v)
#define PxConfigReadInt(s,e,d,v)		PxConfigReadIntCx(PxConfigGetCx(),s,e,d,v)
#define PxConfigReadLong(s,e,d,v)	PxConfigReadLongCx(PxConfigGetCx(),s,e,d,v)
#define PxConfigReadLLong(s,e,d,v)	PxConfigReadLLongCx(PxConfigGetCx(),s,e,d,v)
#define PxConfigReadDouble(s,e,d,v)	PxConfigReadDoubleCx(PxConfigGetCx(),s,e,d,v)
#define PxConfigReadString(s,e,d,v,m)	PxConfigReadStringCx(PxConfigGetCx(),s,e,d,v,m)
#define PxConfigReadArgs(s,e,d,v,m,a,ma,n)	PxConfigReadArgsCx(PxConfigGetCx(),s,e,d,v,m,a,ma,n)
#define PxConfigWriteBool(s,e,f,v)	PxConfigWriteBoolCx(PxConfigGetCx(),s,e,f,v)
#define PxConfigWriteChar(s,e,f,v)	PxConfigWriteCharCx(PxConfigGetCx(),s,e,f,v)
#define PxConfigWriteShort(s,e,f,v)	PxConfigWriteShortCx(PxConfigGetCx(),s,e,f,v)
#define PxConfigWriteInt(s,e,f,v)	PxConfigWriteIntCx(PxConfigGetCx(),s,e,f,v)
#define PxConfigWriteLong(s,e,f,v)	PxConfigWriteLongCx(PxConfigGetCx(),s,e,f,v)
#define PxConfigWriteLLong(s,e,f,v)	PxConfigWriteLLongCx(PxConfigGetCx(),s,e,f,v)
#define PxConfigWriteDouble(s,e,f,v)	PxConfigWriteDoubleCx(PxConfigGetCx(),s,e,f,v)
#define PxConfigWriteString(s,e,f,v)	PxConfigWriteStringCx(PxConfigGetCx(),s,e,f,v)
#define	PxConfigWriteArgs(s,e,a,n)		PxConfigWriteArgsCx(PxConfigGetCx(),s,e,a,n)
#define PxConfigForceEmptySection(s)	PxConfigForceEmptySectionCx(PxConfigGetCx(),s)
#define PxConfigDeleteSection(s)		PxConfigDeleteSectionCx(PxConfigGetCx(),s)
#define PxConfigDeleteEntry(s,e)		PxConfigDeleteEntryCx(PxConfigGetCx(),s,e)
#define	PxConfigGetCount(s,e)			PxConfigGetCountCx( PxConfigGetCx(), s, e)

extern PxCfgContext_t	*PxConfigOpenCx(const char *cfgfile,int mode);
extern int				PxConfigCloseCx(PxCfgContext_t *cx);
extern int				PxConfigSectionCx(PxCfgContext_t *cx,const char *section);
extern const char		*PxConfigFirstSectionCx(PxCfgContext_t *cx);
extern const char		*PxConfigNextSectionCx(PxCfgContext_t *cx);
extern const char		*PxConfigNextStringCx(PxCfgContext_t *cx,char *value,size_t maxlen);
extern const char		*PxConfigNextArgsCx(PxCfgContext_t *cx,char *value,size_t maxlen,char *args[],int max_args, int *n_args);
extern const char		*PxConfigNextEntryCx(PxCfgContext_t *cx,const char **value);
extern int				PxConfigReadBoolCx(PxCfgContext_t *cx,const char *section,const char *entry,int dflt,int *value);
extern int				PxConfigReadCharCx(PxCfgContext_t *cx,const char *section,const char *entry,char dflt,char *value);
extern int				PxConfigReadShortCx(PxCfgContext_t *cx,const char *section,const char *entry,short dflt,short *value);
extern int				PxConfigReadIntCx(PxCfgContext_t *cx,const char *section,const char *entry,int dflt,int *value);
extern int				PxConfigReadLongCx(PxCfgContext_t *cx,const char *section,const char *entry,long dflt,long *value);
extern int				PxConfigReadLLongCx(PxCfgContext_t *cx,const char *section,const char *entry,long long dflt,long long *value);
extern int				PxConfigReadDoubleCx(PxCfgContext_t *cx,const char *section,const char *entry,double dflt,double *value);
extern int				PxConfigReadStringCx(PxCfgContext_t *cx,const char *section,const char *entry,const char *dflt,char *value,size_t maxlen);
extern int				PxConfigReadArgsCx(PxCfgContext_t *cx,const char *section,const char *entry,const char *dflt,char *value,size_t maxlen,char *args[],int max_args, int *n_args);
extern int				PxConfigWriteBoolCx(PxCfgContext_t *cx,const char *section,const char *entry,int format,int value);
extern int				PxConfigWriteCharCx(PxCfgContext_t *cx,const char *section,const char *entry,int format,char value);
extern int				PxConfigWriteShortCx(PxCfgContext_t *cx,const char *section,const char *entry,int format,short value);
extern int				PxConfigWriteIntCx(PxCfgContext_t *cx,const char *section,const char *entry,int format,int value);
extern int				PxConfigWriteLongCx(PxCfgContext_t *cx,const char *section,const char *entry,int format,long value);
extern int				PxConfigWriteLLongCx(PxCfgContext_t *cx,const char *section,const char *entry,int format,long long value);
extern int				PxConfigWriteDoubleCx(PxCfgContext_t *cx,const char *section,const char *entry,int format,double value);
extern int				PxConfigWriteStringCx(PxCfgContext_t *cx,const char *section,const char *entry,int format,const char *value);
extern int				PxConfigForceEmptySectionCx(PxCfgContext_t *cx,const char *section);
extern int				PxConfigWriteArgsCx(PxCfgContext_t *cx,const char *section, const char *entry, const char **args, int n_args);
extern int				PxConfigDeleteSectionCx(PxCfgContext_t *cx,const char *section);
extern int				PxConfigDeleteEntryCx(PxCfgContext_t *cx,const char *section,const char *entry);
extern int				PxConfigGetCountCx(PxCfgContext_t *cx,const char *section,const char *entry);

typedef struct
{
	char description[PATH_MAX + 1];
	char mime[PATH_MAX + 1];
} PxDescription_t;

extern int PxLookupTranslation(char const *name,PxDescription_t *desc);

struct PxTransCtrl;
extern struct PxTransCtrl	*PxTranslateSet(struct PxTransCtrl *ctrl, const char *charset);
extern struct PxTransCtrl	*PxTranslateSetInternal(struct PxTransCtrl *ctrl, const char *charset, const char *type, const void *data, int size);
extern int					PxTranslateUnknown(struct PxTransCtrl *ctrl, uint16_t to, uint16_t from);
extern int					PxTranslateListAlloc(char ***items);
extern void					PxTranslateListFree(char **items, int num);
extern int					PxTranslateList(PtWidget_t *widget, char const *none);
extern int					PxTranslateToUTF(struct PxTransCtrl *ctrl, const char *src, int maxsrc, int *srctaken, char *dst, int maxdst, int *dstmade);
extern int					PxTranslateFromUTF(struct PxTransCtrl *ctrl, const char *src, int maxsrc, int *srctaken, char *dst, int maxdst, int *dstmade);
extern int PxTranslateStateToUTF(struct PxTransCtrl *ctrl, const char *src, int maxsrc, int *consumed, char *dst, int maxdst);
extern int	PxTranslateStateFromUTF(struct PxTransCtrl *ctrl, const char *src, int maxsrc, int *consumed, char *dst, int maxdst);

long PxCRC( const char *buffer, int nbytes );

#ifdef __cplusplus
};
#endif

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/phexlib/public/photon/PxProto.h $ $Rev: 219996 $" )
#endif
