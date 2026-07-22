ifneq ($(COMPILER_DRIVER),qcc)
ifneq ($(BUILDENV),iox)
CCVFLAG_shared = -fpic -D__PIC__
ASVFLAG_shared = -fpic -Wa,--defsym,__PIC__=1
else
CCVFLAG_shared = -D__SLIB_DATA_INDIRECT -G 0
ASVFLAG_shared = -D__SLIB_DATA_INDIRECT -G 0
CCVFLAG_sharedstaticlib = -D__SLIB_DATA_INDIRECT -G 0
ASVFLAG_sharedstaticlib = -D__SLIB_DATA_INDIRECT -G 0
endif

CCVFLAG_be += -mbig-endian -D__BIGENDIAN__
ASVFLAG_be += -mbig-endian -D__BIGENDIAN__
CCVFLAG_le += -mlittle-endian -D__LITTLEENDIAN__
ASVFLAG_le += -mlittle-endian -D__LITTLEENDIAN__
CCVFLAG_a =
endif

OPTIMIZE_TIME_gcc=-O
OPTIMIZE_SIZE_gcc=-O
OPTIMIZE_NONE_gcc=
OPTIMIZE__gcc=$(OPTIMIZE_SIZE_gcc)

CC_nto_ppc_gcc += -pipe $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc) -Wall   
AS_nto_ppc_gcc += -pipe $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc) $(addprefix -Wa$(comma), $(addprefix -I, $(INCVPATH)) $(foreach v, $(VARIANT_NAMES), --defsym$(comma)$v=1))
AR_nto_ppc_gcc += -r
LD_nto_ppc_gcc += -Wl,--no-keep-memory
LDBOOTSTRAP_nto_ppc_gcc  = $(LR_nto_ppc_gcc) -Wl,--no-keep-memory -nostartfiles -u_start
LDBOOTSTRAPPOST_nto_ppc_gcc  = $(LRPOST_nto_ppc_gcc) 

CC_nto_ppc_gcc_qcc += $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc) -Wc,-Wall   
AS_nto_ppc_gcc_qcc += $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc) $(addprefix -Wa$(comma), $(addprefix -I, $(INCVPATH)) $(foreach v, $(VARIANT_NAMES), --defsym$(comma)$v=1))
LD_nto_ppc_gcc_qcc += -Wl,--no-keep-memory
LDBOOTSTRAP_nto_ppc_gcc_qcc  = $(LR_nto_ppc_gcc_qcc) -Wl,--no-keep-memory -nostartup -Wl,-u_start
LDBOOTSTRAPPOST_nto_ppc_gcc_qcc  = $(LRPOST_nto_ppc_gcc_qcc) 

silent_variants_ppc += spe
VFLAG_ppc_spe += -me500v2
CPUVARDIR_SUFFIX = $(if $(filter ppcspe,$(CPU)$(filter spe,$(VARIANTS))),-spe)
