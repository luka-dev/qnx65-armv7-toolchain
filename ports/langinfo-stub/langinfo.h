/* Minimal <langinfo.h> for QNX 6.5 (no langinfo/nl_types). mc only calls
 * nl_langinfo(CODESET) to pick the terminal charset; the stub reports UTF-8
 * (override on-device via mc's charset menu). */
#ifndef _LANGINFO_H
#define _LANGINFO_H 1

typedef int nl_item;
#define CODESET 1

#ifdef __cplusplus
extern "C" {
#endif
extern char *nl_langinfo(nl_item __item);
#ifdef __cplusplus
}
#endif
#endif /* _LANGINFO_H */
