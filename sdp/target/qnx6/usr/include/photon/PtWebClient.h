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





#ifndef __PT_WEBCLIENT_H_INCLUDED
#define __PT_WEBCLIENT_H_INCLUDED

#ifndef __PT_CLIENT_H_INCLUDED
	#include <photon/PtClient.h>
	#include <photon/PtConnectionClient.h>
	#include <photon/PpT.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtWebClient public
 */
extern PtWidgetClassRef_t *PtWebClient;

/* Resources */

#define Pt_ARG_WEB_GET_URL				Pt_RESOURCE( 100,  0 )
#define Pt_ARG_WEB_NAVIGATE_PAGE		Pt_RESOURCE( 100,  1 )
#define Pt_ARG_WEB_NAVIGATE_FRAME		Pt_RESOURCE( 100,  2 )
#define Pt_ARG_WEB_NAVIGATE_LINK		Pt_RESOURCE( 100,  3 )
#define Pt_ARG_WEB_STATUS				Pt_RESOURCE( 100,  5 )
#define Pt_ARG_WEB_RELOAD				Pt_RESOURCE( 100,  6 )
#define Pt_ARG_WEB_STOP					Pt_RESOURCE( 100,  7 )
#define Pt_ARG_WEB_SERVER				Pt_RESOURCE( 100,  9 )
#define Pt_ARG_WEB_GET_HISTORY			Pt_RESOURCE( 100, 10 )
#define Pt_ARG_WEB_OPTION				Pt_RESOURCE( 100, 12 )
#define Pt_ARG_WEB_ACTIVATE_LINK		Pt_RESOURCE( 100, 13 )
#define Pt_ARG_WEB_AUTHENTICATE			Pt_RESOURCE( 100, 14 )
#define Pt_ARG_WEB_HELPER				Pt_RESOURCE( 100, 15 )
#define Pt_ARG_WEB_UNKNOWN_RESP			Pt_RESOURCE( 100, 16 )
#define Pt_ARG_WEB_PRINT				Pt_RESOURCE( 100, 17 )
#define Pt_ARG_WEB_STARTUP_ERRNO		Pt_RESOURCE( 100, 18 )
#define Pt_ARG_WEB_COMMAND				Pt_RESOURCE( 100, 19 )
#define Pt_ARG_WEB_VERSION	 			Pt_RESOURCE( 100, 20 )			
#define Pt_ARG_WEB_BUILD_DATE			Pt_RESOURCE( 100, 21 )			
#define Pt_ARG_WEB_DATA					Pt_RESOURCE( 100, 22 )			
#define Pt_ARG_WEB_GET_CONTEXT			Pt_RESOURCE( 100, 23 )			
#define Pt_ARG_WEB_DOWNLOAD				Pt_RESOURCE( 100, 24 )			
#define Pt_ARG_WEB_H_ERRNO				Pt_RESOURCE( 100, 25 )			
#define Pt_ARG_WEB_ENCODING				Pt_RESOURCE( 100, 26 )			
#define Pt_ARG_WEB_SSL_RESPONSE			Pt_RESOURCE( 100, 27 )			
#define Pt_ARG_WEB_SERVER_PID			Pt_RESOURCE( 100, 28 )
#define Pt_ARG_WEB_TIMER_CTRL			Pt_RESOURCE( 100, 29 )
#define Pt_ARG_WEB_CAN_DO_COMMAND		Pt_RESOURCE( 100, 30 )
#define Pt_ARG_WEB_GET_URL2             Pt_RESOURCE( 100, 31 )	
#define Pt_ARG_WEB_JS_RESPONSE          Pt_RESOURCE( 100, 32 )
#define Pt_ARG_WEB_GET_CERTIFICATES			Pt_RESOURCE( 100, 33 )
#define Pt_ARG_WEB_IMPORT_CERTIFICATE		Pt_RESOURCE( 100, 34 )
#define Pt_ARG_WEB_DELETE_CERTIFICATE		Pt_RESOURCE( 100, 35 )

#define Pt_CB_WEB_COMPLETE				Pt_RESOURCE( 100,100 )
#define Pt_CB_WEB_METADATA				Pt_RESOURCE( 100,101 )
#define Pt_CB_WEB_URL					Pt_RESOURCE( 100,102 )
#define Pt_CB_WEB_PROGRESS				Pt_RESOURCE( 100,103 )
#define Pt_CB_WEB_STATUS				Pt_RESOURCE( 100,104 )
#define Pt_CB_WEB_ERROR					Pt_RESOURCE( 100,105 )
#define Pt_CB_WEB_UNKNOWN				Pt_RESOURCE( 100,106 )
#define Pt_CB_WEB_START					Pt_RESOURCE( 100,107 )
#define Pt_CB_WEB_NEED_SCROLL			Pt_RESOURCE( 100,108 )
#define Pt_CB_WEB_AUTHENTICATE			Pt_RESOURCE( 100,109 )
#define Pt_CB_WEB_PAGE_INFO				Pt_RESOURCE( 100,110 )
#define Pt_CB_WEB_DATA_REQ				Pt_RESOURCE( 100,111 )
#define Pt_CB_WEB_CONTEXT				Pt_RESOURCE( 100,112 )
#define Pt_CB_WEB_NEW_WINDOW			Pt_RESOURCE( 100,113 )
#define Pt_CB_WEB_SSL_ERROR				Pt_RESOURCE( 100,114 )
#define Pt_CB_WEB_CLOSE_WINDOW			Pt_RESOURCE( 100,115 )
#define Pt_CB_WEB_SSL_CERTNONTRUSTED	Pt_RESOURCE( 100,117 )
#define Pt_CB_WEB_SSL_CERTINFO			Pt_RESOURCE( 100,118 )
#define Pt_CB_WEB_NEW_AREA				Pt_RESOURCE( 100,119 )
#define Pt_CB_WEB_JS_PROMPT             Pt_RESOURCE( 100,120 )
#define Pt_CB_WEB_DOWNLOAD             Pt_RESOURCE( 100,121 )
#define	Pt_CB_WEB_SSL_CLIENT_CERT_SELECT	Pt_RESOURCE( 100, 122 )
#define Pt_CB_WEB_IMPORT_CERTIFICATE			Pt_RESOURCE( 100, 123 )
#define Pt_CB_WEB_UNKNOWN_WITH_NAME				Pt_RESOURCE( 100,124 )

/* 'action' for various callbacks (abort would mean to abort a previous callback) */
#define Pt_WEB_ACTION_OK            1
#define Pt_WEB_ACTION_CANCEL        2
#define Pt_WEB_ACTION_ABORT         3
	
/* flags to Pt_ARG_WEB_GET_URL */	
#define Pt_WEB_ACTION_DISPLAY 		0x0001
#define Pt_WEB_ACTION_SAVEAS 		0x0002
#define Pt_WEB_NO_MEMORY_CACHE		0x0010
#define Pt_WEB_NO_DISK_CACHE		0x0020
#define Pt_WEB_NO_SITE_HISTORY		0x0040
#define Pt_WEB_NO_PAGE_HISTORY		0x0080
#define Pt_WEB_STRICT_FILE_ACCESS	0x0100
	
/* flags to Pt_ARG_WEB_PRINT */
#define Pt_WEB_PRINT_FROM_CACHE	    0x0001
#define Pt_WEB_PRINT_ALL_FRAMES	    0x0002

/* flags to start/unknown callback */
#define Pt_WEB_POST_REQUEST         0x0001
	
/* values for Pt_ARG_WEB_NAVIGATE_PAGE/FRAME/LINK */
#define Pt_WEB_DIRECTION_UP 		1
#define Pt_WEB_DIRECTION_DOWN 		2
#define Pt_WEB_DIRECTION_LEFT 		3
#define Pt_WEB_DIRECTION_RIGHT 	    4
#define Pt_WEB_DIRECTION_FWD 		5
#define Pt_WEB_DIRECTION_BACK 		6
#define Pt_WEB_DIRECTION_CANCEL     7 /* cancel image map navigation */

/* additional values for Pt_ARG_WEB_NAVIGATE_LINK */
#define Pt_WEB_DIRECTION_FIRST		8
#define Pt_WEB_DIRECTION_LAST		9

typedef struct {
	char	*url;
	long    zero;
} PtWebStartCallback_t;
	
typedef struct {
	short 	type;
	short 	length;
	char	*url;
} PtWebDataReqCallback_t;

/* 'type' for PtWebDataReqCallback_t/PtWebClient2Data_t */
#define Pt_WEB_DATA_HEADER	        1
#define Pt_WEB_DATA_BODY	        2
#define Pt_WEB_DATA_CLOSE	        3

typedef struct {
	char	*url;
} PtWebCompleteCallback_t;

typedef struct {
	char    *url;
	char	*name;
	char	*value;
} PtWebMetaDataCallback_t;

typedef struct {
	char	*url;
} PtWebUrlCallback_t;

typedef struct {
	short	type;
	short   zero;
	char	*desc;
	char	*url;
} PtWebStatusCallback_t;

/* 'type' for PtWebStatusCallback_t */
#define Pt_WEB_STATUS_MOUSE        1
#define	Pt_WEB_STATUS_CONNECT      2
#define	Pt_WEB_STATUS_PROGRESS     3
#define	Pt_WEB_STATUS_INFO         4
#define	Pt_WEB_STATUS_PRINT        5
#define	Pt_WEB_STATUS_DEFAULT      6
#define	Pt_WEB_STATUS_CONTENTS     7
		
typedef struct {
	short	type;
	short   zero;
	long	reason;
	char *description;
	char	*url;
} PtWebErrorCallback_t;

/* 'type' for PtWebErrorCallback_t */
#define Pt_WEB_ERROR_SERVER_EXIT 	-999
#define Pt_WEB_ERROR_TOPVIEW	 	0
#define Pt_WEB_ERROR_SUBVIEW	 	1
#define Pt_WEB_ERROR_FILE		    2
#define Pt_WEB_ERROR_NOTIFY	 	  3
#define Pt_WEB_ERROR_WML				4

typedef struct {
	PhArea_t area;
	unsigned int flags;
} PtWebNewAreaCallback_t;

/* 'flags' for PtWebNewAreaCallback_t */
#define Pt_WEB_NEW_AREA_SET_SIZE		0x1
#define Pt_WEB_NEW_AREA_SET_POSITION	0x2
#define Pt_WEB_NEW_AREA_SET_AREA		0x4
	
typedef struct {
	short	action;
	short   flags;
	char	*content_type;
	long	content_length;
	char	*url;
} PtWebUnknownCallback_t;

typedef struct {
	short	action;
	short   flags;
	char	*content_type;
	long	content_length;
	char	*url;
	char *suggested_filename;
} PtWebUnknownWithNameCallback_t;

typedef struct {
	int download_ticket;
	int type;
	int current;
	int total;
	char *url;
	char *message;
} PtWebDownloadCallback_t;

/* 'type' for PtWebDownloadCallback_t */
#define Pt_WEB_DOWNLOAD_ERROR				0
#define Pt_WEB_DOWNLOAD_DONE				1
#define Pt_WEB_DOWNLOAD_PROGRESS		2
#define Pt_WEB_DOWNLOAD_CANCEL			3


typedef struct {
	short	dir;
} PtWebNeedScrollCallback_t;

typedef struct {
	short	type;
	short	action;
	char	*realm;
	char	*url;
} PtWebAuthenticateCallback_t;

/* 'type' for PtWebAuthenticationCallback_t */	
#define Pt_WEB_BASIC_AUTHENTICATION 	1
#define Pt_WEB_DIGEST_AUTHENTICATION 	2
#define Pt_WEB_PROXY_AUTHENTICATION 	3
#define Pt_WEB_IMPORT_CERT_AUTHENTICATION 	4
	
typedef struct {
	long	vheight;
	long	vwidth;
	long	height;
	long	width;
	long    ypos, xpos;
} PtWebPageInfoCallback_t;

typedef struct {
	long		context;
	PhPoint_t	pos;
} PtWebContextCallback_t;

#define Pt_WEB_CONTEXT_ANCHOR	0x0001
#define Pt_WEB_CONTEXT_OBJECT	0x0002
#define Pt_WEB_CONTEXT_BKGD		0x0004
#define Pt_WEB_CONTEXT_INPUT    0x0008
#define Pt_WEB_CONTEXT_TEXT     0x0010	

typedef struct {
	PhDim_t 	size;
	long		flags;
	char        *url;
} PtWebWindowCallback_t;

/* 'flags' for PtWebWindowCallback_t */
#define Pt_WEB_SHOW_TOOLBAR  	0x00000001
#define Pt_WEB_SHOW_MENUBAR	    0x00000002
#define Pt_WEB_RESIZEABLE	    0x00000004
#define Pt_WEB_SHOW_STATUS	    0x00000008
#define Pt_WEB_SHOW_LOCATION    0x00000010
#define Pt_WEB_SHOW_DIRECTORIES 0x00000020
#define Pt_WEB_USER_REQUEST     0x00000040

typedef struct {
	short  certerr;
	short  trusted;
	char   *url;
	int		 reason;
} PtWebSSLErrorCallback_t;

#define	Pt_WEB_ERROR_CertNoError			0
#define	Pt_WEB_ERROR_CertChainInvalid		1	/* error cannot be overidden, no correct server should provide a certificate chain which creates this error */
#define	Pt_WEB_ERROR_CertExpired 			2	
#define	Pt_WEB_ERROR_CertNamesNotEqual	 	3
#define	Pt_WEB_ERROR_CertChainIncomplete 	4	/* equivalent to receiving a certificate with an unknown and untrusted root certificate */
#define	Pt_WEB_ERROR_InvalidSignature		5
#define Pt_WEB_ERROR_CertNotYetValid		6
#define Pt_WEB_ERROR_GeneralFailure		    7	/* an error occurred in the handshaking process */
#define Pt_WEB_ERROR_ClientCertInvalid		8	/* there is a problem with the local client certificate */
#define	Pt_WEB_ERROR_TSW_PW_SE_BADSTORE	    16	/* Invalid or corrupt keyfile; also possible for wrong keyfile pw */
#define	Pt_WEB_ERROR_TSW_PW_SE_VERSION		17	/* Wrong version of the keyfile; also possible for wrong keyfile pw */
#define	Pt_WEB_ERROR_BasicConstraints			18 /* access browser SLIM_CERT_E_BASIC_CONSTRAINTS */
#define	Pt_WEB_ERROR_FailedVerify					19 /* access browser SLIM_CERT_E_VERIFY */
#define	Pt_WEB_ERROR_RootCertificateNotValid				20 /* access browser SLIM_CERT_E_TRUST */
#define Pt_WEB_ERROR_IncorrectKeyUsage							21 /* access browser SLIM_CERT_E_KEY_USAGE */
#define Pt_WEB_ERROR_WML_AccessDenied								22
#define Pt_WEB_ERROR_WML_InvalidVariableReference		23
#define Pt_WEB_ERROR_WML_InfiniteLoop								24
#define Pt_WEB_ERROR_WML_Unknown										25
#define Pt_WEB_ERROR_WML_SAX												26
		

/* for the "reason" field in  PtWebSSLErrorCallback_t and PtWebSSLCertNonTrustedCallback_t */
#define Pt_WEB_SSL_AUTHENTICATE											0
#define Pt_WEB_SSL_IMPORT_CERT											1

typedef struct {
	char *name;
	char *subject;
	char *issuer;
	char *cert_serial;
	char *version;
	char *signature_algorithm;
	char *basic_constraints;
	char *extended_key_usage;
	int rsa_public_key_bits;
	time_t	valid_begin, valid_end;
	} PtWebSSLCertInfo_t;

typedef struct {
	short	action;					/* Abort dialog? */
	short	ncert;
	char	*url;
	char	*status;
	int reason;
	PtWebSSLCertInfo_t info[1];
	} PtWebSSLCertNonTrustedCallback_t;

typedef struct {
	int reason;
	char *description;
	} PtWebImportCertificateCallback_t;

/* for the "reason" field in PtWebImportCertificateCallback_t */
#define Pt_WEB_IMPORT_CERTIFICATE_OK				0
#define Pt_WEB_IMPORT_CERTIFICATE_ERROR			1

typedef struct {
	int ncert;
	char *url;
	int reserved1;
	int reserved2;
	PtWebSSLCertInfo_t info[1];
	} PtWebSSLClientCertCallback_t;

typedef PtWebSSLClientCertCallback_t PtWebSSLClientCertificates_t;


typedef struct {
	int type;
	char *path;
	} PtWebImportCertificate_t;

/* for the "type" field in the PtWebImportCertificate_t structure */
#define Pt_WEB_CERT_TYPE_DER			0
#define Pt_WEB_CERT_TYPE_PKCS7		1
#define Pt_WEB_CERT_TYPE_PKCS12		2

typedef struct {
	char			*url;
	char			*cipher_kind;
	short			is_sgc;
	short			version;
	unsigned long	flags;
	struct {
		char		*serial;
		char		*subject;
		char		*issuer;
	}				certinfo;
	time_t	valid_begin, valid_end;
	char	*status;
	char	*extensions;
} PtWebSSLCertInfoCallback_t;

#define Pt_WEB_JS_ALERT    1
#define Pt_WEB_JS_PROMPT   2
#define Pt_WEB_JS_CONFIRM  3
	
typedef struct {	
	short   type;
	short   zero;
	char    *title;
	char    *message;
	char    *prompt;
} PtWebJSPromptCallback_t;
	
/* 'reponse' for various resources */
#define Pt_WEB_RESPONSE_OK         1
#define Pt_WEB_RESPONSE_CANCEL     2	
#define Pt_WEB_RESPONSE_CONTINUE   3	

typedef struct {
	char *url;
	char *target;
	char *referer;
	char *filename;
	char *post_data;
	int  pdata_len;
} PtWebClientUrlInfo_t;
	
typedef struct {
	short num;
	short offset;
} PtWebClientHistory_t;

typedef struct {
	char	*title;
	char	*url;
	time_t  lastvisited;
} PtWebClientHistoryData_t;

typedef struct {
	int		response;
	char	*url;
} PtWebClient2SSLResponse_t;

typedef struct {
	short	response;
	short	type;
	char	*userid;
	char	*password;
	char	*url;
} PtWebClient2AuthenticationData_t;

typedef struct {
	short	response;
	short zero;
	int download_ticket;
	char	*filename;
	char	*url;
} PtWebClient2UnknownData_t;

typedef struct {	
	int response;
	char *prompt;
} PtWebClientJSResponse_t;

/* 'action' type for PtWebClient2HelperData_t */
#define	Pt_WEB_ACTION_ADD      1
#define Pt_WEB_ACTION_DELETE   2	

typedef struct {
	short	action;
	char	*mimetype;
	char	*suffixes;
	char	*encoding;
	char	*helperapp;
} PtWebClient2HelperData_t;

typedef struct {
	int 	type;
	char	*url;
	int		length;
	char 	*data;
} PtWebClient2Data_t;

#define Pt_WEB_COMMAND_CUT                  1
#define Pt_WEB_COMMAND_COPY		            2
#define Pt_WEB_COMMAND_PASTE	            3
#define Pt_WEB_COMMAND_CLEAR	            4
#define Pt_WEB_COMMAND_UNDO		            5
#define Pt_WEB_COMMAND_SELECTALL            6
#define Pt_WEB_COMMAND_FIND		            7
#define Pt_WEB_COMMAND_LOADMISSING          8
#define Pt_WEB_COMMAND_SAVEAS	            9
#define Pt_WEB_COMMAND_SCROLLTO	           10
#define Pt_WEB_COMMAND_PLAY		           11
#define Pt_WEB_COMMAND_STOP		           12
#define Pt_WEB_COMMAND_RESET_OPT           13
#define Pt_WEB_COMMAND_PURGE_CACHE         14
#define Pt_WEB_COMMAND_RESET_HISTORY       15
#define Pt_WEB_COMMAND_LOADMISSING_CONTEXT 16
#define Pt_WEB_COMMAND_CLEAR_DISK_CACHE	   17
#define Pt_WEB_COMMAND_FIND_RESULT	       18
#define Pt_WEB_COMMAND_SET_WIDGET	       19

/* flags to Pt_ARG_WEB_COMMAND Pt_WEB_COMMAND_FIND */
#define Pt_WEB_FIND_START_AT_TOP    0x0001
#define	Pt_WEB_FIND_MATCH_CASE	    0x0002
#define	Pt_WEB_FIND_GO_BACKWARDS		0x0004
#define	Pt_WEB_FIND_MATCH_WHOLE_WORDS	0x0008
	
#define Pt_WEB_CAN_DO_FALSE	        0
#define Pt_WEB_CAN_DO_TRUE          1
#define	Pt_WEB_CAN_DO_UNKNOWN       2
	
typedef union {
	struct {
		char	*filename;
	} SaveasInfo;
	struct {
		char *string;
		unsigned long flags;
	} FindInfo;
	struct {
		char *string;
		int number;
	} SetWidgetInfo;
	struct {
		int	input_group;
	} ClipboardInfo;
	char	*scroll_to;
	int		reset_type;
	int		num_purge;
} PtWebClient2Command_t;

typedef struct {
	PtClientWidget_t	client;
	char				*server;
	int					retries;
	char                *url;
	char				*status;
	PtWebClientHistoryData_t *history;
	PtWebSSLClientCertificates_t *certificates;
	pid_t				server_pid;
	int					start_errno;
	int					h_errno;
	int					retry;
	int					can_do;
	char				*name;
	long                response_long;
	char                *response;
	int                 response_size;
	long				cb_mask;
	PtCallbackList_t	*complete_cb;
	PtCallbackList_t	*metadata_cb;
	PtCallbackList_t	*url_cb;
	PtCallbackList_t	*progress_cb;
	PtCallbackList_t 	*status_cb;
	PtCallbackList_t	*error_cb;
	PtCallbackList_t	*unknown_cb;
	PtCallbackList_t	*unknown_with_name_cb;
	PtCallbackList_t	*start_cb;
	PtCallbackList_t	*scroll_cb;
	PtCallbackList_t	*auth_cb;
	PtCallbackList_t	*pageinfo_cb;
	PtCallbackList_t	*datareq_cb;
	PtCallbackList_t	*context_cb;
	PtCallbackList_t	*new_window_cb;
	PtCallbackList_t	*ssl_error_cb;
	PtCallbackList_t	*ssl_certnontrusted_cb;
	PtCallbackList_t	*ssl_certinfo_cb;
	PtCallbackList_t	*close_window_cb;
	PtCallbackList_t	*new_area_cb;
	PtCallbackList_t	*prompt_cb;
	PtCallbackList_t	*download_cb;
	PtCallbackList_t	*ssl_clientcertselect_cb;
	PtCallbackList_t	*import_cert_cb;
} PtWebClientWidget_t;

/* Widget union */
typedef union {
	PtWidget_t				core;
	PtBasicWidget_t			basic;
	PtContainerWidget_t		cntnr;
	PtClientWidget_t		clnt;
	PtWebClientWidget_t		web;
} PtWebClientUnion_t;

#ifdef __cplusplus
};
#endif

#endif

#ifdef __QNXNTO__
#include <sys/srcversion.h>
__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/ptweb/public/photon/PtWebClient.h $ $Rev: 219996 $" )
#endif
