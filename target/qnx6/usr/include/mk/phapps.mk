# This file should be included in a Makefile located the root 
# of every Photon app.

ifndef QBUILDLIST
QBUILDLIST=buildlist.mk
ifdef QCONFIG
qbdir=$(dir $(QCONFIG))
endif
endif
include $(qbdir)$(QBUILDLIST)

ifeq (,$(OSLIST))
OSLIST:=$(HOST_SYSTEM)
endif

ifeq (nto, $(findstring nto, $(OSLIST)))
ifneq (,$(CPULIST))
ifneq (,$(VARIANTLIST))
DIRS:=$(sort $(patsubst gcc_ntox86%,gcc_ntox86,$(foreach cpu,$(CPULIST),$(foreach variant,$(VARIANTLIST),gcc_nto$(cpu)$(variant)))))
else
DIRS:=$(foreach cpu,$(CPULIST),gcc_nto$(cpu)*)
endif
else
DIRS:=gcc_nto*
endif
endif

ifeq (win32, $(findstring win32, $(OSLIST)))
DIRS+=gcc_cygwin
endif

ifeq (qnx4, $(findstring qnx4, $(OSLIST)))
DIRS+=wcc_qnx4
endif

DIRSLIST:=$(patsubst %/Makefile,%, $(wildcard $(foreach dir,$(DIRS),src/$(dir)/Makefile)))
EARLY_DIRS:=$(patsubst %/Makefile,%, $(wildcard $(foreach dir,$(EARLY_DIRS),$(dir)/Makefile)))
LATE_DIRS:=$(patsubst %/Makefile,%, $(wildcard $(foreach dir,$(LATE_DIRS),$(dir)/Makefile)))

MAKECMD=$(MAKE) -C$(dir) $(if $(MAKECMDGOALS),$@,all)

$(filter-out all,$(MAKECMDGOALS)) all:
	$(foreach dir, $(EARLY_DIRS) $(DIRSLIST) $(LATE_DIRS), $(MAKECMD);)
