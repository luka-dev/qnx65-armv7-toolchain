/* nl_langinfo(CODESET) -> "UTF-8"; all other items -> "". */
#include "langinfo.h"
char *nl_langinfo(nl_item item) { return (char *)(item == CODESET ? "UTF-8" : ""); }
