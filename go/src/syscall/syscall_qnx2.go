// Copyright 2026 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

//go:build qnx

// QNX 6.5 / ARM: remaining path, id, and time syscalls the os package needs.

package syscall

import "unsafe"

//go:cgo_import_dynamic libc_truncate truncate "libc.so.3"
//go:cgo_import_dynamic libc_chown chown "libc.so.3"
//go:cgo_import_dynamic libc_lchown lchown "libc.so.3"
//go:cgo_import_dynamic libc_utimes utimes "libc.so.3"
//go:cgo_import_dynamic libc_access access "libc.so.3"
//go:cgo_import_dynamic libc_getuid getuid "libc.so.3"
//go:cgo_import_dynamic libc_geteuid geteuid "libc.so.3"
//go:cgo_import_dynamic libc_getgid getgid "libc.so.3"
//go:cgo_import_dynamic libc_getegid getegid "libc.so.3"
//go:cgo_import_dynamic libc_getgroups getgroups "libc.so.3"
//go:cgo_import_dynamic libc_gethostname gethostname "libc.so.3"
//go:cgo_import_dynamic libc_getrusage getrusage "libc.so.3"
//go:cgo_import_dynamic libc_getsid getsid "libc.so.3"
//go:cgo_import_dynamic libc_umask umask "libc.so.3"

//go:linkname libc_truncate libc_truncate
//go:linkname libc_chown libc_chown
//go:linkname libc_lchown libc_lchown
//go:linkname libc_utimes libc_utimes
//go:linkname libc_access libc_access
//go:linkname libc_getuid libc_getuid
//go:linkname libc_geteuid libc_geteuid
//go:linkname libc_getgid libc_getgid
//go:linkname libc_getegid libc_getegid
//go:linkname libc_getgroups libc_getgroups
//go:linkname libc_gethostname libc_gethostname
//go:linkname libc_getrusage libc_getrusage
//go:linkname libc_getsid libc_getsid
//go:linkname libc_umask libc_umask

var (
	libc_truncate, libc_chown, libc_lchown, libc_utimes, libc_access,
	libc_getuid, libc_geteuid, libc_getgid, libc_getegid, libc_getgroups,
	libc_gethostname, libc_getrusage, libc_getsid, libc_umask libcFunc
)

// Umask sets the file mode creation mask and returns the previous value.
func Umask(mask int) (oldmask int) {
	r1, _, _ := rawSysvicall6(fnptr(&libc_umask), 1, uintptr(mask), 0, 0, 0, 0, 0)
	return int(r1)
}

func Getsid(pid int) (sid int, err error) {
	r1, _, e := rawSysvicall6(fnptr(&libc_getsid), 1, uintptr(pid), 0, 0, 0, 0, 0)
	if e != 0 {
		return -1, e
	}
	return int(r1), nil
}

const ImplementsGetwd = true

const (
	RUSAGE_SELF     = 0
	RUSAGE_CHILDREN = -1
)

func Getrusage(who int, rusage *Rusage) error {
	_, _, e := rawSysvicall6(fnptr(&libc_getrusage), 2, uintptr(who), uintptr(unsafe.Pointer(rusage)), 0, 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

// ---- path ops backed by libc symbols already bound in syscall_qnx.go ----

func Rename(from, to string) error {
	f, err := BytePtrFromString(from)
	if err != nil {
		return err
	}
	t, err := BytePtrFromString(to)
	if err != nil {
		return err
	}
	_, _, e := sysvicall6(fnptr(&libc_rename), 2, uintptr(unsafe.Pointer(f)), uintptr(unsafe.Pointer(t)), 0, 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

func Link(from, to string) error {
	f, err := BytePtrFromString(from)
	if err != nil {
		return err
	}
	t, err := BytePtrFromString(to)
	if err != nil {
		return err
	}
	_, _, e := sysvicall6(fnptr(&libc_link), 2, uintptr(unsafe.Pointer(f)), uintptr(unsafe.Pointer(t)), 0, 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

func Symlink(from, to string) error {
	f, err := BytePtrFromString(from)
	if err != nil {
		return err
	}
	t, err := BytePtrFromString(to)
	if err != nil {
		return err
	}
	_, _, e := sysvicall6(fnptr(&libc_symlink), 2, uintptr(unsafe.Pointer(f)), uintptr(unsafe.Pointer(t)), 0, 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

func Readlink(path string, buf []byte) (n int, err error) {
	p, err := BytePtrFromString(path)
	if err != nil {
		return 0, err
	}
	var b unsafe.Pointer
	if len(buf) > 0 {
		b = unsafe.Pointer(&buf[0])
	} else {
		b = unsafe.Pointer(&_zero)
	}
	r1, _, e := sysvicall6(fnptr(&libc_readlink), 3, uintptr(unsafe.Pointer(p)), uintptr(b), uintptr(len(buf)), 0, 0, 0)
	n = int(r1)
	if e != 0 {
		err = e
	}
	return
}

func Truncate(path string, length int64) error {
	p, err := BytePtrFromString(path)
	if err != nil {
		return err
	}
	_, _, e := sysvicall6(fnptr(&libc_truncate), 3, uintptr(unsafe.Pointer(p)), uintptr(length), uintptr(length>>32), 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

func Chown(path string, uid, gid int) error {
	p, err := BytePtrFromString(path)
	if err != nil {
		return err
	}
	_, _, e := sysvicall6(fnptr(&libc_chown), 3, uintptr(unsafe.Pointer(p)), uintptr(uid), uintptr(gid), 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

func Lchown(path string, uid, gid int) error {
	p, err := BytePtrFromString(path)
	if err != nil {
		return err
	}
	_, _, e := sysvicall6(fnptr(&libc_lchown), 3, uintptr(unsafe.Pointer(p)), uintptr(uid), uintptr(gid), 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

func Access(path string, mode uint32) error {
	p, err := BytePtrFromString(path)
	if err != nil {
		return err
	}
	_, _, e := sysvicall6(fnptr(&libc_access), 2, uintptr(unsafe.Pointer(p)), uintptr(mode), 0, 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

func Getwd() (string, error) {
	var buf [4096]byte
	r1, _, e := sysvicall6(fnptr(&libc_getcwd), 2, uintptr(unsafe.Pointer(&buf[0])), uintptr(len(buf)), 0, 0, 0, 0)
	if e != 0 {
		return "", e
	}
	// getcwd returns the buffer pointer on success.
	_ = r1
	n := 0
	for n < len(buf) && buf[n] != 0 {
		n++
	}
	return string(buf[:n]), nil
}

// UtimesNano sets file times; QNX has microsecond utimes(), so nanoseconds are
// truncated. ponytail: microsecond resolution only.
func UtimesNano(path string, ts []Timespec) error {
	p, err := BytePtrFromString(path)
	if err != nil {
		return err
	}
	if len(ts) != 2 {
		return EINVAL
	}
	var tv [2]Timeval
	tv[0] = Timeval{Sec: ts[0].Sec, Usec: ts[0].Nsec / 1000}
	tv[1] = Timeval{Sec: ts[1].Sec, Usec: ts[1].Nsec / 1000}
	_, _, e := sysvicall6(fnptr(&libc_utimes), 2, uintptr(unsafe.Pointer(p)), uintptr(unsafe.Pointer(&tv[0])), 0, 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

// utimensat is pulled by internal/syscall/unix via //go:linkname. QNX 6.5 has
// no *at syscalls, so only _AT_FDCWD is supported; times are truncated to the
// microsecond resolution of utimes(). nil times means "set to current time".
func utimensat(dirfd int, path string, times *[2]Timespec, flag int) error {
	if dirfd != _AT_FDCWD || flag != 0 {
		return ENOSYS
	}
	p, err := BytePtrFromString(path)
	if err != nil {
		return err
	}
	var tvp uintptr
	var tv [2]Timeval
	if times != nil {
		tv[0] = Timeval{Sec: times[0].Sec, Usec: times[0].Nsec / 1000}
		tv[1] = Timeval{Sec: times[1].Sec, Usec: times[1].Nsec / 1000}
		tvp = uintptr(unsafe.Pointer(&tv[0]))
	}
	_, _, e := sysvicall6(fnptr(&libc_utimes), 2, uintptr(unsafe.Pointer(p)), tvp, 0, 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

const _AT_FDCWD = -100

func Gethostname() (name string, err error) {
	var buf [256]byte
	_, _, e := sysvicall6(fnptr(&libc_gethostname), 2, uintptr(unsafe.Pointer(&buf[0])), uintptr(len(buf)), 0, 0, 0, 0)
	if e != 0 {
		return "", e
	}
	n := 0
	for n < len(buf) && buf[n] != 0 {
		n++
	}
	return string(buf[:n]), nil
}

// ---- ids ----

func Getuid() int { r, _, _ := rawSysvicall6(fnptr(&libc_getuid), 0, 0, 0, 0, 0, 0, 0); return int(r) }
func Geteuid() int {
	r, _, _ := rawSysvicall6(fnptr(&libc_geteuid), 0, 0, 0, 0, 0, 0, 0)
	return int(r)
}
func Getgid() int { r, _, _ := rawSysvicall6(fnptr(&libc_getgid), 0, 0, 0, 0, 0, 0, 0); return int(r) }
func Getegid() int {
	r, _, _ := rawSysvicall6(fnptr(&libc_getegid), 0, 0, 0, 0, 0, 0, 0)
	return int(r)
}

func Getgroups() (gids []int, err error) {
	n, _, e := rawSysvicall6(fnptr(&libc_getgroups), 2, 0, 0, 0, 0, 0, 0)
	if e != 0 {
		return nil, e
	}
	if n == 0 {
		return nil, nil
	}
	a := make([]uint32, n)
	r1, _, e := rawSysvicall6(fnptr(&libc_getgroups), 2, uintptr(len(a)), uintptr(unsafe.Pointer(&a[0])), 0, 0, 0, 0)
	if e != 0 {
		return nil, e
	}
	gids = make([]int, r1)
	for i := range gids {
		gids[i] = int(a[i])
	}
	return gids, nil
}
