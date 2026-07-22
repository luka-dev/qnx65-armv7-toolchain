use crate::prelude::*;

pub type wchar_t = u32;
// QNX 6.5 <sys/target_nto.h>: __TIME_T = _Uint32t (32-bit, unsigned) on 32-bit ARM.
pub type time_t = u32;

s! {
    // <arm/context.h> ARM_CPU_REGISTERS
    pub struct arm_cpu_registers {
        pub gpr: [u32; 16],
        pub spsr: u32,
    }

    // <arm/context.h> arm_fpu_registers: a union whose largest member is X[32] u64,
    // followed by fpscr/fpexc/fpinst/fpinst2. Represent flat (largest layout).
    pub struct arm_fpu_registers {
        pub reg: [u64; 32],
        pub fpscr: u32,
        pub fpexc: u32,
        pub fpinst: u32,
        pub fpinst2: u32,
    }

    pub struct mcontext_t {
        pub cpu: crate::arm_cpu_registers,
        pub fpu: crate::arm_fpu_registers,
    }

    pub struct stack_t {
        pub ss_sp: *mut c_void,
        pub ss_size: size_t,
        pub ss_flags: c_int,
    }
}
