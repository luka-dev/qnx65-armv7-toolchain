# This file should be included in a Makefile located the root 
# of every Photon app.

ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)


CWD := $(subst \,/,$(shell $(PWD_HOST)))
roots:=$(filter $(ROOT_DIR) cvs src qssl, $(subst /, ,$(CWD)))
root:=$(firstword $(roots))
SRC_ROOT := $(patsubst %/,%,$(subst !,/,$(dir $(subst $(root)!,$(root)/, $(subst /,!, $(CWD))))))

ifndef QCONF_OVERRIDE
QCONF_OVERRIDE=$(SRC_ROOT)/qconf-override.mk
endif
-include $(QCONF_OVERRIDE)

BDIR:=$(notdir $(CWD))

ifneq (,$(findstring nto,$(BDIR)))
 OS:=nto
 VAR:=$(patsubst gcc_nto%,%,$(BDIR))
 CPU:=$(subst be,,$(subst le,,$(VAR)))
else 
 ifneq (,$(findstring cygwin,$(BDIR)))
  OS:=win32
  VAR:=x86
  NAMEEXT:=.exe
 else
  ifneq (,$(findstring qnx4,$(BDIR)))
   OS:=qnx4
  else 
   ifeq (default,$(BDIR))
    OS:=qnx4
   else
    OS:=$(HOST_SYSTEM)
   endif
  endif
 endif
endif

USE_ROOT:=$(if $(USE_INSTALL_ROOT),$(INSTALL_ROOT_$(OS)),$(USE_ROOT_$(OS)))
CFLAGS:=-I$(USE_ROOT)/usr/include -I$(USE_ROOT)/usr/include/photon $(CFLAGS)
LDFLAGS:=-L$(USE_ROOT)/$(VAR)/lib -L$(USE_ROOT)/$(VAR)/usr/lib -L$(USE_ROOT)/$(VAR)/usr/photon/lib -Wl,--rpath-link,$(USE_ROOT)/$(VAR)/lib:$(USE_ROOT)/$(VAR)/usr/lib:$(USE_ROOT)/$(VAR)/usr/photon/lib $(LDFLAGS)
SDFLAGS:=-L$(USE_ROOT)/$(VAR)/lib -L$(USE_ROOT)/$(VAR)/usr/lib -L$(USE_ROOT)/$(VAR)/usr/photon/lib -Wl,--rpath-link,$(USE_ROOT)/$(VAR)/lib:$(USE_ROOT)/$(VAR)/usr/lib:$(USE_ROOT)/$(VAR)/usr/photon/lib $(SDFLAGS)
ifndef INSTALL_DIRECTORY
  INSTALL_DIRECTORY=$(INSTALL_ROOT_$(OS))/$(VAR)/usr/photon/bin/
endif

ifndef NAME
D=$(filter-out $(BDIR) src, $(subst /, ,$(CWD)))
NAME:=$(word $(words $(D)),$(D))
endif


-include ../../pinfo.mk

ECHO_HOST=echo 

ifndef PINFO_STATE
PINFO_STATE=Experimental
endif
ifndef PINFO_USER
PINFO_USER=$(shell $(USER_HOST))
endif
ifndef PINFO_HOST
PINFO_HOST=$(shell $(HOST_HOST))
endif
ifndef PINFO_DATE
PINFO_DATE=$(shell $(DATE_HOST))
endif

ifndef PINFO_TAGID
PINFO_TAGID=$(word 2, $(subst _, ,$(BRANCH_TAG)))
endif	

pinfo_name=$(NAME).pinfo

define ADD_PINFO
	@$(RM_HOST) $(NAME).pinfo
	@$(ECHO_HOST)  >$(pinfo_name) STATE=$(PINFO_STATE)
	@$(ECHO_HOST) >>$(pinfo_name) INSTALLDIR=$(subst $(INSTALL_ROOT_$(OS))/$(VAR)/,,$(INSTALL_DIRECTORY))
	@$(ECHO_HOST) >>$(pinfo_name) INSTALLNAME=$(NAME)$(NAMEEXT)
	@$(ECHO_HOST) >>$(pinfo_name) NAME=$(NAME)$(NAMEEXT)
	@$(ECHO_HOST) >>$(pinfo_name) USER=$(PINFO_USER)
	@$(ECHO_HOST) >>$(pinfo_name) HOST=$(PINFO_HOST)
	@$(ECHO_HOST) >>$(pinfo_name) DATE=$(PINFO_DATE)
	@$(if $(VERSION_REL),$(ECHO_HOST) >>$(pinfo_name) VERSION=$(VERSION_REL))
	@$(if $(PINFO_TAGID),$(ECHO_HOST) >>$(pinfo_name) TAGID=$(PINFO_TAGID))
	@$(if $(FILE_INFO),$(ECHO_HOST) >>$(pinfo_name) FINFO=$(FILE_INFO))
	@$(subst PINFO, $(ECHO_HOST) >>$(pinfo_name), $(PINFO))
endef

%.o: %.c 
	$(CC) -c $(CFLAGS) $< $@

%.o: %.cc 
	$(CXX) -c $(CXXFLAGS) $< $@

all: shr pinfo

hinstall: # nothing to do

install: shr pinfo
	$(CP_HOST) $(NAME)$(NAMEEXT) $(INSTALL_DIRECTORY)
ifeq ($(OS),win32)
	$(CP_HOST) $(NAME).res $(INSTALL_DIRECTORY)
endif

clean: 
	$(RM_HOST) *.o *.err *.map *.pinfo $(NAME)$(NAMEEXT) *.res *.a

#Using $(NEWLINE) will cause a single newline character to be added
define NEWLINE 


endef

tag_list=VERSION TAGID $(subst PINFO-,,$(filter PINFO-%,$(subst =, ,$(subst PINFO ,PINFO-,$(subst $(NEWLINE), ,$(PINFO))))))

pinfo: 
	$(ADD_PINFO)
ifneq ($(OS),win32)
	usemsg $(addprefix -i,$(tag_list)) -f $(NAME).pinfo $(NAME)
endif
	$(POST_BUILD)
