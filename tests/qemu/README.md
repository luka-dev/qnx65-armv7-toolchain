# QEMU boot pieces

Prebuilt bits needed to run an armle-v7 binary on real QNX under QEMU
(`tests/qemu-run.sh`). They come from the QEMU BSP in Refferences, which is not
part of this repo, so the results are committed rather than rebuilt.

| file | what |
|---|---|
| `startup-virt`  | the board's startup, built from the BSP with the timer fix below |
| `libstartup.a`  | BSP startup library; mkifs relinks the relocatable startup with it |
| `devc-serdebug` | serial driver, so the program's stdout reaches the console |
| `u-boot.bin`    | loads the IFS at 0x40200000 and jumps to it |

## Two things that are NOT obvious

**1. libstartup must be the BSP's, not the SDP's.** The 2010 SDP library has no
Cortex-A15 support - the core postdates it - so `armv_chip_detect()` finds
nothing and the boot dies with "Unsupported CPUID". Build the board directory
before the library and the linker silently picks the SDP one.

**2. The BSP's timer interrupt number is wrong** (`timer-intr.patch`). It ships

    qtime->intr = 1;    /* GPT1 irq */

The comment gives it away: copied from another BSP. On QEMU's virt board the
timer is the ARM generic VIRTUAL timer (the callouts use `mrrc p15, 3, ..., c14`
= CNTV_CVAL), whose interrupt is GIC PPI 11, i.e. IRQ 27. IRQ 1 is an SGI, so
the tick never arrived. Effects, all silent:

  - `clock_gettime()` returns success and zero, forever
  - `sleep()` never returns
  - Go dies at startup with "fatal error: nanotime returning zero"

`ClockCycles()` keeps working throughout, because reading the counter does not
need the interrupt - which is what makes this look like a working system.

This is a defect in the BSP itself, not in our toolchain: the stock
bsp-qemu-virt.bin image has the same fault, and startup built by GCC 4.9 and by
GCC 8.5 behaves identically. With IRQ 27 the clock advances and Go runs.

## Rebuilding startup

    cp -R <Refferences>/QNX_QEMU_BSP/bsp-qnx65-qemu-virt-a15 /tmp/bsp
    patch -d /tmp/bsp -p1 < tests/qemu/timer-intr.patch
    docker run --rm --platform=linux/amd64 -v /tmp/bsp:/bsp -w /bsp \
        qnx65-armv7-toolchain:8.5 sh -c '
      export QNX_HOST=/opt/qnx650/host/linux/x86 QNX_TARGET=/opt/qnx650/target/qnx6
      export MAKEFLAGS=-I$QNX_TARGET/usr/include
      cd src/hardware/startup/lib && make -j4
      cp arm/a.le.v7/libstartup.a $QNX_TARGET/armle-v7/usr/lib/libstartup.a
      cd ../boards/virt && make'
