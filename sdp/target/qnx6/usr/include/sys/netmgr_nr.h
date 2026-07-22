/*
 * $QNXLicenseC: $
*/


#ifndef _NETMGR_NR_H_INCLUDED
#define _NETMGR_NR_H_INCLUDED

#ifndef __PLATFORM_H_INCLUDED
#include <sys/platform.h>
#endif

__BEGIN_DECLS

struct _dispatch;
typedef struct {
	struct _dispatch	*dpp;
	int					coid;
	void				*data;
} nr_attr_t;

struct netmgr_name_resolver {
	unsigned	data_size;
	int			(*init)(nr_attr_t *__attr, const char *__parm);
	void		(*resolve)(void *__data, int __nd, const char *__name, const char *__domain,
					 int (*__wait_func)(void *__wait_hdl, const void *__iface, int __status),
					 void *__wait_hdl);
	void		(*fini)(void *__data);
};

struct netmgr_iface_funcs {
	unsigned		nfuncs;
	char			*(*parse_iface)(char *__src, void *__iface);
	int				(*string_iface)(const void *__iface, char *__buf, int __size);
};
#define _NETMGR_IFACE_NFUNCS	((sizeof(struct netmgr_iface_funcs)-sizeof(unsigned))/sizeof(void *))

__END_DECLS

#endif

__SRCVERSION( "$URL: http://svn/product/branches/6.5.0/trunk/lib/io-pkt/sys/lsm/qnet/public/include/sys/netmgr_nr.h $ $Rev: 233581 $" )
