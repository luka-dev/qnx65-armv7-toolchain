// Copyright 2026 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// QNX 6.5 has no *at() family (it predates POSIX.1-2008). We emulate the
// dirfd == AT_FDCWD case — the only one the os package uses in practice — by
// calling the plain path-based libc entry points. A real (non-AT_FDCWD) dirfd
// returns ENOSYS.
//
// ponytail: AT_FDCWD-only; add /proc/<pid>/fd-relative resolution if os ever
// starts opening dir handles on this target.

package unix

import (
	"syscall"
	"unsafe"
)

// bridge into runtime (see asm_qnx.s).
func syscall6(trap, nargs, a1, a2, a3, a4, a5, a6 uintptr) (r1, r2 uintptr, err syscall.Errno)
func rawSyscall6(trap, nargs, a1, a2, a3, a4, a5, a6 uintptr) (r1, r2 uintptr, err syscall.Errno)

//go:cgo_import_dynamic libc_open open "libc.so.3"
//go:cgo_import_dynamic libc_stat stat "libc.so.3"
//go:cgo_import_dynamic libc_lstat lstat "libc.so.3"
//go:cgo_import_dynamic libc_unlink unlink "libc.so.3"
//go:cgo_import_dynamic libc_rmdir rmdir "libc.so.3"
//go:cgo_import_dynamic libc_mkdir mkdir "libc.so.3"
//go:cgo_import_dynamic libc_chmod chmod "libc.so.3"
//go:cgo_import_dynamic libc_chown chown "libc.so.3"
//go:cgo_import_dynamic libc_lchown lchown "libc.so.3"
//go:cgo_import_dynamic libc_readlink readlink "libc.so.3"
//go:cgo_import_dynamic libc_symlink symlink "libc.so.3"
//go:cgo_import_dynamic libc_link link "libc.so.3"
//go:cgo_import_dynamic libc_rename rename "libc.so.3"
//go:cgo_import_dynamic libc_access access "libc.so.3"

//go:linkname libc_open libc_open
//go:linkname libc_stat libc_stat
//go:linkname libc_lstat libc_lstat
//go:linkname libc_unlink libc_unlink
//go:linkname libc_rmdir libc_rmdir
//go:linkname libc_mkdir libc_mkdir
//go:linkname libc_chmod libc_chmod
//go:linkname libc_chown libc_chown
//go:linkname libc_lchown libc_lchown
//go:linkname libc_readlink libc_readlink
//go:linkname libc_symlink libc_symlink
//go:linkname libc_link libc_link
//go:linkname libc_rename libc_rename
//go:linkname libc_access libc_access

var (
	libc_open, libc_stat, libc_lstat, libc_unlink, libc_rmdir, libc_mkdir,
	libc_chmod, libc_chown, libc_lchown, libc_readlink, libc_symlink,
	libc_link, libc_rename, libc_access uintptr
)

// Sentinel + flags we own (QNX defines none of these).
const (
	AT_FDCWD            = -0x64 // -100
	AT_EACCESS          = 0x4
	AT_REMOVEDIR        = 0x1
	AT_SYMLINK_NOFOLLOW = 0x2

	UTIME_OMIT = -0x2
)

func atfd(dirfd int) error {
	if dirfd != AT_FDCWD {
		return syscall.ENOSYS
	}
	return nil
}

func fnref(p *uintptr) uintptr { return uintptr(unsafe.Pointer(p)) }

func Openat(dirfd int, path string, flags int, perm uint32) (int, error) {
	if err := atfd(dirfd); err != nil {
		return 0, err
	}
	p, err := syscall.BytePtrFromString(path)
	if err != nil {
		return 0, err
	}
	fd, _, errno := syscall6(fnref(&libc_open), 3, uintptr(unsafe.Pointer(p)), uintptr(flags), uintptr(perm), 0, 0, 0)
	if errno != 0 {
		return 0, errno
	}
	return int(fd), nil
}

func Fstatat(dirfd int, path string, stat *syscall.Stat_t, flags int) error {
	if err := atfd(dirfd); err != nil {
		return err
	}
	p, err := syscall.BytePtrFromString(path)
	if err != nil {
		return err
	}
	fn := &libc_stat
	if flags&AT_SYMLINK_NOFOLLOW != 0 {
		fn = &libc_lstat
	}
	_, _, errno := syscall6(fnref(fn), 2, uintptr(unsafe.Pointer(p)), uintptr(unsafe.Pointer(stat)), 0, 0, 0, 0)
	if errno != 0 {
		return errno
	}
	return nil
}

func Unlinkat(dirfd int, path string, flags int) error {
	if err := atfd(dirfd); err != nil {
		return err
	}
	p, err := syscall.BytePtrFromString(path)
	if err != nil {
		return err
	}
	fn := &libc_unlink
	if flags&AT_REMOVEDIR != 0 {
		fn = &libc_rmdir
	}
	_, _, errno := syscall6(fnref(fn), 1, uintptr(unsafe.Pointer(p)), 0, 0, 0, 0, 0)
	if errno != 0 {
		return errno
	}
	return nil
}

func Readlinkat(dirfd int, path string, buf []byte) (int, error) {
	if err := atfd(dirfd); err != nil {
		return 0, err
	}
	p0, err := syscall.BytePtrFromString(path)
	if err != nil {
		return 0, err
	}
	var p1 unsafe.Pointer
	if len(buf) > 0 {
		p1 = unsafe.Pointer(&buf[0])
	} else {
		p1 = unsafe.Pointer(&_zero)
	}
	n, _, errno := syscall6(fnref(&libc_readlink), 3, uintptr(unsafe.Pointer(p0)), uintptr(p1), uintptr(len(buf)), 0, 0, 0)
	if errno != 0 {
		return 0, errno
	}
	return int(n), nil
}

func Mkdirat(dirfd int, path string, mode uint32) error {
	if err := atfd(dirfd); err != nil {
		return err
	}
	p, err := syscall.BytePtrFromString(path)
	if err != nil {
		return err
	}
	_, _, errno := syscall6(fnref(&libc_mkdir), 2, uintptr(unsafe.Pointer(p)), uintptr(mode), 0, 0, 0, 0)
	if errno != 0 {
		return errno
	}
	return nil
}

func Fchmodat(dirfd int, path string, mode uint32, flags int) error {
	if err := atfd(dirfd); err != nil {
		return err
	}
	p, err := syscall.BytePtrFromString(path)
	if err != nil {
		return err
	}
	_, _, errno := syscall6(fnref(&libc_chmod), 2, uintptr(unsafe.Pointer(p)), uintptr(mode), 0, 0, 0, 0)
	if errno != 0 {
		return errno
	}
	return nil
}

func Fchownat(dirfd int, path string, uid, gid int, flags int) error {
	if err := atfd(dirfd); err != nil {
		return err
	}
	p, err := syscall.BytePtrFromString(path)
	if err != nil {
		return err
	}
	fn := &libc_chown
	if flags&AT_SYMLINK_NOFOLLOW != 0 {
		fn = &libc_lchown
	}
	_, _, errno := syscall6(fnref(fn), 3, uintptr(unsafe.Pointer(p)), uintptr(uid), uintptr(gid), 0, 0, 0)
	if errno != 0 {
		return errno
	}
	return nil
}

func Renameat(olddirfd int, oldpath string, newdirfd int, newpath string) error {
	if err := atfd(olddirfd); err != nil {
		return err
	}
	if err := atfd(newdirfd); err != nil {
		return err
	}
	oldp, err := syscall.BytePtrFromString(oldpath)
	if err != nil {
		return err
	}
	newp, err := syscall.BytePtrFromString(newpath)
	if err != nil {
		return err
	}
	_, _, errno := syscall6(fnref(&libc_rename), 2, uintptr(unsafe.Pointer(oldp)), uintptr(unsafe.Pointer(newp)), 0, 0, 0, 0)
	if errno != 0 {
		return errno
	}
	return nil
}

func Linkat(olddirfd int, oldpath string, newdirfd int, newpath string, flag int) error {
	if err := atfd(olddirfd); err != nil {
		return err
	}
	if err := atfd(newdirfd); err != nil {
		return err
	}
	oldp, err := syscall.BytePtrFromString(oldpath)
	if err != nil {
		return err
	}
	newp, err := syscall.BytePtrFromString(newpath)
	if err != nil {
		return err
	}
	_, _, errno := syscall6(fnref(&libc_link), 2, uintptr(unsafe.Pointer(oldp)), uintptr(unsafe.Pointer(newp)), 0, 0, 0, 0)
	if errno != 0 {
		return errno
	}
	return nil
}

func Symlinkat(oldpath string, newdirfd int, newpath string) error {
	if err := atfd(newdirfd); err != nil {
		return err
	}
	oldp, err := syscall.BytePtrFromString(oldpath)
	if err != nil {
		return err
	}
	newp, err := syscall.BytePtrFromString(newpath)
	if err != nil {
		return err
	}
	_, _, errno := syscall6(fnref(&libc_symlink), 2, uintptr(unsafe.Pointer(oldp)), uintptr(unsafe.Pointer(newp)), 0, 0, 0, 0)
	if errno != 0 {
		return errno
	}
	return nil
}

// faccessat backs internal/syscall/unix/eaccess.go. QNX's access() checks the
// real uid; AT_EACCESS (effective uid) is ignored — fine for a single-user
// embedded target. ponytail: real-uid check only.
func faccessat(dirfd int, path string, mode uint32, flags int) error {
	if err := atfd(dirfd); err != nil {
		return err
	}
	p, err := syscall.BytePtrFromString(path)
	if err != nil {
		return err
	}
	_, _, errno := syscall6(fnref(&libc_access), 2, uintptr(unsafe.Pointer(p)), uintptr(mode), 0, 0, 0, 0)
	if errno != 0 {
		return errno
	}
	return nil
}
