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





#ifndef __PT_WEBSERVER_H_INCLUDED
#define __PT_WEBSERVER_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <photon/PtWebClient.h>

#define Pt_WEB_SERVER_MODE   0x0001

/* 'opt' value to res_func */	
#define Pt_WEB_GET_RESOURCE 1
#define Pt_WEB_SET_RESOURCE 2
	
typedef struct {
	int type;
	int (*res_func)(PtWidget_t *, int op, PtArg_t *, void *data);
} PtWebServerRes_t;

int PtWebServerInit( char *ServerName, int flags, int (*connect_func)(PtWidget_t *, void *), void *data );
void PtWebServerDestroy( char * ServerName );
int PtWebServerRegResources( PtWidget_t *widget, PtWebServerRes_t *arr, int narr, void *data);
int PtWebServerAddResource(PtWidget_t *widget, int type, int (*func)(PtWidget_t *, int op, PtArg_t *, void *data), void *data);
int PtWebServerRemoveResource(PtWidget_t *widget, int id);
	
int PtWebReportStatus ( PtWidget_t *widget, const char *message, int type, const char *url );
int PtWebReportUrl ( PtWidget_t *widget, const char *url );
int PtWebReportComplete ( PtWidget_t *widget, const char *url );
int PtWebReportMetaData ( PtWidget_t *widget, const char *name, const char *value, const char *url );
int PtWebReportStart ( PtWidget_t *widget, const char *url );
int PtWebReportNeedScroll ( PtWidget_t *widget, int dir );
int PtWebReportError ( PtWidget_t *widget, int target, int reason, const char *url, const char *description );
int PtWebReportDebug ( PtWidget_t *widget, char *msg );
int PtWebFlush ( void );
int PtWebReportUnknown( PtWidget_t *widget, const char *content_type, int content_len, const char *url, int action );
int PtWebReportUnknownWithName( PtWidget_t *widget, const char *content_type, int content_len, const char *url, const char *suggested_filename, int action );
int PtWebReportNewWindow( PtWidget_t *widget, int, int, long, const char *url );
int PtWebDoContextMenu( PtWidget_t *widget, int, int, int );
int PtWebReportWindowClose( PtWidget_t *widget );
int PtWebReply( PtWidget_t *widget );
int PtWebReportAuthentication ( PtWidget_t *widget, int, int, const char *, const char * );
int PtWebReportNewArea( PtWidget_t *widget, PhArea_t *area, int flags );
int PtWebReportPostData( PtWidget_t *widget, int *response );	
int PtWebReportClientData( PtWidget_t *widget, int type, int len, char *url );
int PtWebReportPageInfo( PtWidget_t *widget, int vheight, int vwidth, int height, int width, int offt, int offl );
int PtWebReportSSLError( PtWidget_t *widget, const char *url, int cert_err, int trusted_cert, int reason );
int PtWebReportSSLCertNonTrusted( PtWidget_t *widget, PtWebSSLCertNonTrustedCallback_t *x_ssl_cb );
int PtWebReportSSLCertInfo( PtWidget_t *widget, PtWebSSLCertInfoCallback_t *x_ssl_cb );
int PtWebReportDownload( PtWidget_t *widget, char *url, int download_ticket, int type, int current, int total, char *message );
int PtWebSupportCallback(PtWidget_t *widget, int cb_res);
int PtWebReportSSLClientCertSelect( PtWidget_t *widget, PtWebSSLClientCertCallback_t *x_ssl_cb );
int PtWebReportImportCertificate( PtWidget_t *widget, int reason, char *description );
	
int PtWebAlert( PtWidget_t *widget, const char *title, const char *message );
int PtWebConfirm( PtWidget_t *widget, const char *title, const char *message);
int PtWebPrompt( PtWidget_t *widget, const char *title, const char *message, const char *prompt);
int PtWebException( PtWidget_t *widget, const char *description, int line, const char *souceline, int character );
int PtWebBlock( PtWidget_t *widget, int flag );
#ifdef __cplusplus
};
#endif

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ptweb/public/photon/PtWebServer.h $ $Rev: 219996 $" )
#endif
