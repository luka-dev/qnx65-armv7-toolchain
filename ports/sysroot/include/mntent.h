/* Minimal <mntent.h> for QNX 6.5 (QNX has no getmntent family). Lets mc's
 * gnulib mountlist.c compile its getmntent branch; the stub returns an empty
 * mount list, so mc's "all filesystems" panel is empty but everything else
 * works (per-path free space still comes from statvfs). */
#ifndef _MNTENT_H
#define _MNTENT_H 1
#include <stdio.h>

#define MNTTAB        "/etc/fstab"
#define MOUNTED       "/etc/mtab"
#define _PATH_MOUNTED "/etc/mtab"
#define _PATH_MNTTAB  "/etc/fstab"

struct mntent {
    char *mnt_fsname;
    char *mnt_dir;
    char *mnt_type;
    char *mnt_opts;
    int   mnt_freq;
    int   mnt_passno;
};

#ifdef __cplusplus
extern "C" {
#endif
extern FILE *setmntent(const char *__file, const char *__mode);
extern struct mntent *getmntent(FILE *__stream);
extern int endmntent(FILE *__stream);
#ifdef __cplusplus
}
#endif
#endif /* _MNTENT_H */
