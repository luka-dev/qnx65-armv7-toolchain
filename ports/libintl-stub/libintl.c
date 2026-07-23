/* No-op libintl: return each message id unchanged (NLS disabled). */
#include "libintl.h"

int _nl_msg_cat_cntr = 0;

char *gettext(const char *m) { return (char *)m; }
char *dgettext(const char *d, const char *m) { (void)d; return (char *)m; }
char *dcgettext(const char *d, const char *m, int c) { (void)d; (void)c; return (char *)m; }
char *ngettext(const char *m1, const char *m2, unsigned long n) { return (char *)(n == 1 ? m1 : m2); }
char *dngettext(const char *d, const char *m1, const char *m2, unsigned long n) { (void)d; return (char *)(n == 1 ? m1 : m2); }
char *dcngettext(const char *d, const char *m1, const char *m2, unsigned long n, int c) { (void)d; (void)c; return (char *)(n == 1 ? m1 : m2); }
char *textdomain(const char *d) { return (char *)(d ? d : "messages"); }
char *bindtextdomain(const char *d, const char *dir) { (void)d; return (char *)dir; }
char *bind_textdomain_codeset(const char *d, const char *cs) { (void)d; return (char *)cs; }
