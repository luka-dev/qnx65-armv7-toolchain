# CMake toolchain for QNX Neutrino 6.5.0 armle-v7 (ARMv7-A, EABI5, softfp).
#   cmake -DCMAKE_TOOLCHAIN_FILE=/opt/qnx-cross/qnx-armv7.cmake <src>
# (or use the qnx-cmake host wrapper, which passes this for you).

set(CMAKE_SYSTEM_NAME QNX)
set(CMAKE_SYSTEM_VERSION 6.5.0)
set(CMAKE_SYSTEM_PROCESSOR armv7)

set(_tc arm-unknown-nto-qnx6.5.0eabi)
set(CMAKE_C_COMPILER   ${_tc}-gcc)
set(CMAKE_CXX_COMPILER ${_tc}-g++)
set(CMAKE_ASM_COMPILER ${_tc}-gcc)
set(CMAKE_AR           ${_tc}-ar)
set(CMAKE_RANLIB       ${_tc}-ranlib)
set(CMAKE_STRIP        ${_tc}-strip)
set(CMAKE_NM           ${_tc}-nm)
set(CMAKE_OBJCOPY      ${_tc}-objcopy)
set(CMAKE_OBJDUMP      ${_tc}-objdump)

# gcc already bakes in this sysroot + the armle-v7 -L dirs (see gcc/port); pass
# it to cmake so find_* and pkg-config resolve against the QNX tree, not the host.
set(CMAKE_SYSROOT /opt/qnx650/target/qnx6)
set(CMAKE_FIND_ROOT_PATH /opt/qnx650/target/qnx6 /opt/qnx650/target/qnx6/armle-v7)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# pkg-config: look only inside the sysroot so host .pc files don't leak in.
set(ENV{PKG_CONFIG_SYSROOT_DIR} /opt/qnx650/target/qnx6)
set(ENV{PKG_CONFIG_LIBDIR} /opt/qnx650/target/qnx6/armle-v7/usr/lib/pkgconfig)

# Cross: target binaries can't run at configure time. Projects that use
# try_run()/check_*_runs() must pre-seed the result in the cache - there is no
# QNX emulator installed here. Most projects don't need it.
