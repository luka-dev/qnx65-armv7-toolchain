ifndef DEFCOMPILER_TYPE
DEFCOMPILER_TYPE = gcc
endif

ifneq (Linux,$(shell cd / && uname -s))
USE_ROOT_linux := $(USE_ROOT_linux)/$(CPUDIR)
INSTALL_ROOT_linux := $(INSTALL_ROOT_linux)/$(CPUDIR)
endif

USE_ROOT_INCLUDE=$(call mk_use_list, usr/local/include usr/include)
USE_ROOT_LIB=$(call mk_use_list, usr/lib)

INSTALL_ROOT_AR=$(INSTALL_ROOT_linux)
INSTALL_ROOT_EX=$(INSTALL_ROOT_linux)
INSTALL_ROOT_SO=$(INSTALL_ROOT_linux)
INSTALL_ROOT_HDR=$(INSTALL_ROOT_linux)/usr/include

IMAGE_PREF_AR=lib
IMAGE_SUFF_AR=.a

IMAGE_PREF_EX=
IMAGE_SUFF_EX=

IMAGE_PREF_SO=lib
IMAGE_SUFF_SO=.so
