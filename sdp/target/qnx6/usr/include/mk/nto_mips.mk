ifneq ($(COMPILER_DRIVER),qcc)
ifeq ($(strip $(CCVFLAG_shared)),)
CCVFLAG_shared = -fpic -D__PIC__
ASVFLAG_shared = -Wa,--defsym -Wa,__PIC__=1 -D__PIC__
endif


CCVFLAG_be += -D__BIGENDIAN__
ASVFLAG_be += -D__BIGENDIAN__
CCVFLAG_le += -D__LITTLEENDIAN__
ASVFLAG_le += -D__LITTLEENDIAN__
CCVFLAG_a =

ifeq ($(BUILDENV),ion)
CCVFLAG_shared = -fpic -mabicalls -G 0
ASVFLAG_shared = -D__PIC__ -D__GAS__ -mabicalls -fpic -G 0 
PICFLAG_PIC = -fpic -mabicalls -G 0 -D__PIC__ -D__MIPS_ABICALLS__ -D__GAS__ -Wa,--defsym,__MIPS_ABICALLS__=1 -Wa,--defsym,__PIC__=1 -mfast-local-calls
PICFLAG_nonPIC =
endif

ifeq ($(BUILDENV),iox)
CCVFLAG_shared = -D__SLIB_DATA_INDIRECT -G 0
ASVFLAG_shared = -D__SLIB_DATA_INDIRECT -G 0
CCVFLAG_sharedstaticlib = -D__SLIB_DATA_INDIRECT -G 0
ASVFLAG_sharedstaticlib = -D__SLIB_DATA_INDIRECT -G 0
LDVFLAGS_dll =
CCVFLAG_dll = -G 0 -D__SLIB_DATA_INDIRECT
ASVFLAG_dll = -D__SLIB_DATA_INDIRECT -G 0
endif
endif

OPTIMIZE_TIME_gcc=-O
OPTIMIZE_SIZE_gcc=-O
OPTIMIZE_NONE_gcc=
OPTIMIZE__gcc=$(OPTIMIZE_SIZE_gcc)

ifneq ($(BUILDENV),iox)
CC_nto_mips_gcc += -Wall -fno-builtin -fno-inline-functions -pipe -mcpu=r4000 -mips2 $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc)
AS_nto_mips_gcc += -Wall -fno-builtin -fno-inline-functions -pipe -mcpu=r4000 -mips2 $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc) -D__ASM__ $(addprefix -D,$(VARIANT_NAMES))
else
CC_nto_mips_gcc += -Wall -fno-builtin -fno-inline-functions -pipe $(MIPS_ABI_OPT) -mips2 $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc)
AS_nto_mips_gcc += -Wall -fno-builtin -fno-inline-functions -pipe $(MIPS_ABI_OPT) -mips2 $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc) -D__ASM__ $(addprefix -D,$(VARIANT_NAMES))
endif

AR_nto_mips_gcc += -r
LD_nto_mips_gcc += -mips2 -Wl,--no-keep-memory
# bootstrap executable linker
LDBOOTSTRAP_nto_mips_gcc  = $(LR_nto_mips_gcc) -Wl,--no-keep-memory -nostartfiles -Wl,-u_start
LDBOOTSTRAPPOST_nto_mips_gcc  = $(LRPOST_nto_mips_gcc)

CC_nto_mips_gcc_qcc += -Wc,-Wall -Wc,-fno-builtin -Wc,-fno-inline-functions $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc)
AS_nto_mips_gcc_qcc += $(OPTIMIZE_$(OPTIMIZE_TYPE)_gcc) -D__ASM__ $(addprefix -D,$(VARIANT_NAMES))
LD_nto_mips_gcc_qcc += -Wl,--no-keep-memory
# bootstrap executable linker
LDBOOTSTRAP_nto_mips_gcc_qcc  = $(LR_nto_mips_gcc_qcc) -Wl,--no-keep-memory -nostartup -Wl,-u_start
LDBOOTSTRAPPOST_nto_mips_gcc_qcc  = $(LRPOST_nto_mips_gcc_qcc)

#
# if "-mabicalls" is in the command line, we always want to use the
# -fpic compiled version of libraries
#
libmunge=$(if $(findstring -mabicalls,$(COMPILE_c_o)),$(1)S,$(1))
