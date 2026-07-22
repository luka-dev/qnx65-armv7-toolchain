// Copyright 2026 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

//go:build qnx

// Process creation for QNX. A microkernel has no useful fork(); processes are
// created with posix_spawn(), which does the fork+exec atomically inside libc.
// That means — unlike the classic Unix forkAndExecInChild that runs in a forked
// child under strict nosplit/no-alloc rules — this runs entirely in the parent
// as an ordinary function.
//
// The syscall/exec_unix.go framework calls us holding ForkLock, after creating a
// close-on-exec status pipe (p[1]==pipe). posix_spawn's child inherits the pipe
// (CLOEXEC) only until it execs, at which point the pipe closes and the parent's
// read of p[0] returns EOF == success; on posix_spawn failure we return the errno
// directly, which the framework surfaces.

package syscall

import "unsafe"

//go:cgo_import_dynamic libc_posix_spawn posix_spawn "libc.so.3"
//go:cgo_import_dynamic libc_posix_spawn_file_actions_init posix_spawn_file_actions_init "libc.so.3"
//go:cgo_import_dynamic libc_posix_spawn_file_actions_destroy posix_spawn_file_actions_destroy "libc.so.3"
//go:cgo_import_dynamic libc_posix_spawn_file_actions_adddup2 posix_spawn_file_actions_adddup2 "libc.so.3"
//go:cgo_import_dynamic libc_posix_spawnattr_init posix_spawnattr_init "libc.so.3"
//go:cgo_import_dynamic libc_posix_spawnattr_destroy posix_spawnattr_destroy "libc.so.3"
//go:cgo_import_dynamic libc_posix_spawnattr_setflags posix_spawnattr_setflags "libc.so.3"
//go:cgo_import_dynamic libc_posix_spawnattr_setpgroup posix_spawnattr_setpgroup "libc.so.3"

//go:linkname libc_posix_spawn libc_posix_spawn
//go:linkname libc_posix_spawn_file_actions_init libc_posix_spawn_file_actions_init
//go:linkname libc_posix_spawn_file_actions_destroy libc_posix_spawn_file_actions_destroy
//go:linkname libc_posix_spawn_file_actions_adddup2 libc_posix_spawn_file_actions_adddup2
//go:linkname libc_posix_spawnattr_init libc_posix_spawnattr_init
//go:linkname libc_posix_spawnattr_destroy libc_posix_spawnattr_destroy
//go:linkname libc_posix_spawnattr_setflags libc_posix_spawnattr_setflags
//go:linkname libc_posix_spawnattr_setpgroup libc_posix_spawnattr_setpgroup

var (
	libc_posix_spawn                     libcFunc
	libc_posix_spawn_file_actions_init   libcFunc
	libc_posix_spawn_file_actions_destroy libcFunc
	libc_posix_spawn_file_actions_adddup2 libcFunc
	libc_posix_spawnattr_init            libcFunc
	libc_posix_spawnattr_destroy         libcFunc
	libc_posix_spawnattr_setflags        libcFunc
	libc_posix_spawnattr_setpgroup       libcFunc
)

const _POSIX_SPAWN_SETPGROUP = 0x1

func forkAndExecInChild(argv0 *byte, argv, envv []*byte, chroot, dir *byte, attr *ProcAttr, sys *SysProcAttr, pipe int) (pid int, err Errno) {
	// posix_spawn on QNX 6.5 can't do these; fail cleanly rather than silently
	// producing a mis-configured child.
	if sys.Chroot != "" || sys.Credential != nil || sys.Setsid || sys.Setctty || sys.Foreground {
		return 0, ENOSYS
	}
	_ = chroot
	_ = pipe // handled by CLOEXEC on the status pipe

	var fa uintptr // posix_spawn_file_actions_t (opaque, pointer-sized)
	if _, _, e := sysvicall6(fnptr(&libc_posix_spawn_file_actions_init), 1, uintptr(unsafe.Pointer(&fa)), 0, 0, 0, 0, 0); e != 0 {
		return 0, e
	}
	defer sysvicall6(fnptr(&libc_posix_spawn_file_actions_destroy), 1, uintptr(unsafe.Pointer(&fa)), 0, 0, 0, 0, 0)

	var sa uintptr // posix_spawnattr_t (opaque)
	if _, _, e := sysvicall6(fnptr(&libc_posix_spawnattr_init), 1, uintptr(unsafe.Pointer(&sa)), 0, 0, 0, 0, 0); e != 0 {
		return 0, e
	}
	defer sysvicall6(fnptr(&libc_posix_spawnattr_destroy), 1, uintptr(unsafe.Pointer(&sa)), 0, 0, 0, 0, 0)

	// Wire the child's fd i to attr.Files[i]. adddup2(fd, fd) is well-defined: it
	// clears CLOEXEC so an unchanged fd is still inherited.
	for i := 0; i < len(attr.Files); i++ {
		if _, _, e := sysvicall6(fnptr(&libc_posix_spawn_file_actions_adddup2), 3,
			uintptr(unsafe.Pointer(&fa)), attr.Files[i], uintptr(i), 0, 0, 0); e != 0 {
			return 0, e
		}
	}

	if sys.Setpgid {
		sysvicall6(fnptr(&libc_posix_spawnattr_setflags), 2, uintptr(unsafe.Pointer(&sa)), _POSIX_SPAWN_SETPGROUP, 0, 0, 0, 0)
		sysvicall6(fnptr(&libc_posix_spawnattr_setpgroup), 2, uintptr(unsafe.Pointer(&sa)), uintptr(sys.Pgid), 0, 0, 0, 0)
	}

	// QNX posix_spawn has no chdir file action, so change directory in the parent
	// (safe: the caller holds ForkLock) and restore it before returning.
	if dir != nil {
		var wd [4096]byte
		if r, _, _ := sysvicall6(fnptr(&libc_getcwd), 2, uintptr(unsafe.Pointer(&wd[0])), uintptr(len(wd)), 0, 0, 0, 0); r != 0 {
			defer sysvicall6(fnptr(&libc_chdir), 1, uintptr(unsafe.Pointer(&wd[0])), 0, 0, 0, 0, 0)
		}
		if _, _, e := sysvicall6(fnptr(&libc_chdir), 1, uintptr(unsafe.Pointer(dir)), 0, 0, 0, 0, 0); e != 0 {
			return 0, e
		}
	}

	// posix_spawn(pid, path, file_actions, attr, argv, envp) returns the errno as
	// its value (0 == success), not via the errno global.
	var childpid int32
	r, _, _ := sysvicall6(fnptr(&libc_posix_spawn), 6,
		uintptr(unsafe.Pointer(&childpid)),
		uintptr(unsafe.Pointer(argv0)),
		uintptr(unsafe.Pointer(&fa)),
		uintptr(unsafe.Pointer(&sa)),
		uintptr(unsafe.Pointer(&argv[0])),
		uintptr(unsafe.Pointer(&envv[0])))
	if r != 0 {
		return 0, Errno(r)
	}
	return int(childpid), 0
}

func forkAndExecFailureCleanup(attr *ProcAttr, sys *SysProcAttr) {}
