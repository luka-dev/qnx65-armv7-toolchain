/* No-op getmntent family: QNX 6.5 has no mount enumeration -> empty list. */
#include "mntent.h"

FILE *setmntent(const char *f, const char *m) { (void)f; (void)m; return NULL; }
struct mntent *getmntent(FILE *s) { (void)s; return NULL; }
int endmntent(FILE *s) { (void)s; return 1; }
