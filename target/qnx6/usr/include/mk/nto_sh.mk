ifneq ($(COMPILER_DRIVER),qcc)
CCVFLAG_shared = -fpic -D__PIC__
ASVFLAG_shared = -fpic -Wa,--defsym -Wa,__PIC__=1
endif

OPTIMIZE_TIME_gcc=-O
OPTIMIZE_SIZE_gcc=-O
OPTIMIZE_NONE_gcc=
OPTIMIZE__gcc=$(OPTIMIZE_SIZE_gcc)

CC_nto_sh_gcc += -m4 -pipe $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc) -Wall   
AS_nto_sh_gcc += -m4 -pipe $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc) $(addprefix -Wa$(comma)-I$, $(INCVPATH)) $(foreach var,$(VARIANT_NAMES), -Wa$(comma)--defsym$(comma)$(var)=1)
AR_nto_sh_gcc += -r
LD_nto_sh_gcc += -m4 -Wl,--no-keep-memory
LDBOOTSTRAP_nto_sh_gcc  = $(LR_nto_sh_gcc) -Wl,--no-keep-memory -nostartfiles -Wl,-u_start
LDBOOTSTRAPPOST_nto_sh_gcc  = $(LRPOST_nto_sh_gcc) 

CC_nto_sh_gcc_qcc += $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc) -Wc,-Wall   
AS_nto_sh_gcc_qcc += $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc) $(addprefix -Wa$(comma)-I$, $(INCVPATH)) $(foreach var,$(VARIANT_NAMES), -Wa$(comma)--defsym$(comma)$(var)=1)
LD_nto_sh_gcc_qcc += -Wl,--no-keep-memory
LDBOOTSTRAP_nto_sh_gcc_qcc  = $(LR_nto_sh_gcc_qcc) -Wl,--no-keep-memory -nostartup -Wl,-u_start
LDBOOTSTRAPPOST_nto_sh_gcc_qcc  = $(LRPOST_nto_sh_gcc_qcc) 
