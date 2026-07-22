// Copyright 2026 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// QNX 6.5 system calls via libc.so.3 (libc-call model, like solaris/aix).
// The //go:cgo_import_dynamic + sysvicall6 bridge funnels through
// runtime.syscall_sysvicall6.

package syscall

import (
	"internal/oserror"
	"runtime"
	"unsafe"
)

// sysvicall6 and rawSysvicall6 are implemented in asm_qnx_arm.s (they JMP into
// runtime.syscall_sysvicall6 / _rawsysvicall6).
func sysvicall6(trap, nargs, a1, a2, a3, a4, a5, a6 uintptr) (r1, r2 uintptr, err Errno)
func rawSysvicall6(trap, nargs, a1, a2, a3, a4, a5, a6 uintptr) (r1, r2 uintptr, err Errno)

// libc.so.3 bindings.
//
//go:cgo_import_dynamic libc_open open "libc.so.3"
//go:cgo_import_dynamic libc_close close "libc.so.3"
//go:cgo_import_dynamic libc_read read "libc.so.3"
//go:cgo_import_dynamic libc_write write "libc.so.3"
//go:cgo_import_dynamic libc_pread pread "libc.so.3"
//go:cgo_import_dynamic libc_pwrite pwrite "libc.so.3"
//go:cgo_import_dynamic libc_lseek lseek "libc.so.3"
//go:cgo_import_dynamic libc_fcntl fcntl "libc.so.3"
//go:cgo_import_dynamic libc_stat stat "libc.so.3"
//go:cgo_import_dynamic libc_lstat lstat "libc.so.3"
//go:cgo_import_dynamic libc_fstat fstat "libc.so.3"
//go:cgo_import_dynamic libc_mkdir mkdir "libc.so.3"
//go:cgo_import_dynamic libc_rmdir rmdir "libc.so.3"
//go:cgo_import_dynamic libc_unlink unlink "libc.so.3"
//go:cgo_import_dynamic libc_rename rename "libc.so.3"
//go:cgo_import_dynamic libc_chdir chdir "libc.so.3"
//go:cgo_import_dynamic libc_ftruncate ftruncate "libc.so.3"
//go:cgo_import_dynamic libc_fsync fsync "libc.so.3"
//go:cgo_import_dynamic libc_dup dup "libc.so.3"
//go:cgo_import_dynamic libc_dup2 dup2 "libc.so.3"
//go:cgo_import_dynamic libc_pipe pipe "libc.so.3"
//go:cgo_import_dynamic libc_getcwd getcwd "libc.so.3"
//go:cgo_import_dynamic libc_readlink readlink "libc.so.3"
//go:cgo_import_dynamic libc_symlink symlink "libc.so.3"
//go:cgo_import_dynamic libc_link link "libc.so.3"
//go:cgo_import_dynamic libc_chmod chmod "libc.so.3"
//go:cgo_import_dynamic libc_getdents readdir_r "libc.so.3"
//go:cgo_import_dynamic libc_getrlimit getrlimit "libc.so.3"
//go:cgo_import_dynamic libc_setrlimit setrlimit "libc.so.3"
//go:cgo_import_dynamic libc_socket socket "libsocket.so.3"
//go:cgo_import_dynamic libc_bind bind "libsocket.so.3"
//go:cgo_import_dynamic libc_connect connect "libsocket.so.3"
//go:cgo_import_dynamic libc_listen listen "libsocket.so.3"
//go:cgo_import_dynamic libc_accept accept "libsocket.so.3"
//go:cgo_import_dynamic libc_getsockname getsockname "libsocket.so.3"
//go:cgo_import_dynamic libc_getpeername getpeername "libsocket.so.3"
//go:cgo_import_dynamic libc_getsockopt getsockopt "libsocket.so.3"
//go:cgo_import_dynamic libc_setsockopt setsockopt "libsocket.so.3"
//go:cgo_import_dynamic libc_recvfrom recvfrom "libsocket.so.3"
//go:cgo_import_dynamic libc_sendto sendto "libsocket.so.3"
//go:cgo_import_dynamic libc_recvmsg recvmsg "libsocket.so.3"
//go:cgo_import_dynamic libc_sendmsg sendmsg "libsocket.so.3"
//go:cgo_import_dynamic libc_socketpair socketpair "libsocket.so.3"
//go:cgo_import_dynamic libc_shutdown shutdown "libsocket.so.3"
//go:cgo_import_dynamic libc_wait4 wait4 "libc.so.3"
//go:cgo_import_dynamic libc_kill kill "libc.so.3"
//go:cgo_import_dynamic libc_mmap mmap "libc.so.3"
//go:cgo_import_dynamic libc_munmap munmap "libc.so.3"
//go:cgo_import_dynamic libc_getpid getpid "libc.so.3"
//go:cgo_import_dynamic libc_getppid getppid "libc.so.3"
//go:cgo_import_dynamic libc_writev writev "libc.so.3"
//go:cgo_import_dynamic libc_fchmod fchmod "libc.so.3"
//go:cgo_import_dynamic libc_fchown fchown "libc.so.3"
//go:cgo_import_dynamic libc_fchdir fchdir "libc.so.3"

//go:linkname libc_open libc_open
//go:linkname libc_close libc_close
//go:linkname libc_read libc_read
//go:linkname libc_write libc_write
//go:linkname libc_pread libc_pread
//go:linkname libc_pwrite libc_pwrite
//go:linkname libc_lseek libc_lseek
//go:linkname libc_fcntl libc_fcntl
//go:linkname libc_stat libc_stat
//go:linkname libc_lstat libc_lstat
//go:linkname libc_fstat libc_fstat
//go:linkname libc_mkdir libc_mkdir
//go:linkname libc_rmdir libc_rmdir
//go:linkname libc_unlink libc_unlink
//go:linkname libc_rename libc_rename
//go:linkname libc_chdir libc_chdir
//go:linkname libc_ftruncate libc_ftruncate
//go:linkname libc_fsync libc_fsync
//go:linkname libc_dup libc_dup
//go:linkname libc_dup2 libc_dup2
//go:linkname libc_pipe libc_pipe
//go:linkname libc_getcwd libc_getcwd
//go:linkname libc_readlink libc_readlink
//go:linkname libc_symlink libc_symlink
//go:linkname libc_link libc_link
//go:linkname libc_chmod libc_chmod
//go:linkname libc_getdents libc_getdents
//go:linkname libc_getrlimit libc_getrlimit
//go:linkname libc_setrlimit libc_setrlimit
//go:linkname libc_socket libc_socket
//go:linkname libc_bind libc_bind
//go:linkname libc_connect libc_connect
//go:linkname libc_listen libc_listen
//go:linkname libc_accept libc_accept
//go:linkname libc_getsockname libc_getsockname
//go:linkname libc_getpeername libc_getpeername
//go:linkname libc_getsockopt libc_getsockopt
//go:linkname libc_setsockopt libc_setsockopt
//go:linkname libc_recvfrom libc_recvfrom
//go:linkname libc_sendto libc_sendto
//go:linkname libc_recvmsg libc_recvmsg
//go:linkname libc_sendmsg libc_sendmsg
//go:linkname libc_socketpair libc_socketpair
//go:linkname libc_shutdown libc_shutdown
//go:linkname libc_wait4 libc_wait4
//go:linkname libc_kill libc_kill
//go:linkname libc_mmap libc_mmap
//go:linkname libc_munmap libc_munmap
//go:linkname libc_getpid libc_getpid
//go:linkname libc_getppid libc_getppid
//go:linkname libc_writev libc_writev
//go:linkname libc_fchmod libc_fchmod
//go:linkname libc_fchown libc_fchown
//go:linkname libc_fchdir libc_fchdir

var (
	libc_open, libc_close, libc_read, libc_write, libc_pread, libc_pwrite,
	libc_lseek, libc_fcntl, libc_stat, libc_lstat, libc_fstat, libc_mkdir,
	libc_rmdir, libc_unlink, libc_rename, libc_chdir, libc_ftruncate, libc_fsync,
	libc_dup, libc_dup2, libc_pipe, libc_getcwd, libc_readlink, libc_symlink,
	libc_link, libc_chmod, libc_getdents, libc_getrlimit, libc_setrlimit,
	libc_socket, libc_bind, libc_connect, libc_listen, libc_accept,
	libc_getsockname, libc_getpeername, libc_getsockopt, libc_setsockopt,
	libc_recvfrom, libc_sendto, libc_recvmsg, libc_sendmsg, libc_socketpair,
	libc_shutdown, libc_wait4, libc_kill, libc_mmap, libc_munmap,
	libc_getpid, libc_getppid, libc_writev, libc_fchmod, libc_fchown,
	libc_fchdir libcFunc
)

type libcFunc uintptr

func fnptr(f *libcFunc) uintptr { return uintptr(unsafe.Pointer(f)) }

// ---- primitives ----

func RawSyscall(trap, a1, a2, a3 uintptr) (r1, r2 uintptr, err Errno) {
	// No raw-syscall path on QNX (message-passing microkernel). Fail loudly.
	return 0, 0, ENOSYS
}

// mmap/munmap: kept for the linkname hall-of-shame (see linkname_unix.go) and
// used by anyone reaching into syscall directly.
func mmap(addr uintptr, length uintptr, prot int, flag int, fd int, pos int64) (ret uintptr, err error) {
	r1, _, e := sysvicall6(fnptr(&libc_mmap), 6, addr, length, uintptr(prot), uintptr(flag), uintptr(fd), uintptr(pos))
	if e != 0 {
		return 0, e
	}
	return r1, nil
}

func munmap(addr uintptr, length uintptr) error {
	_, _, e := sysvicall6(fnptr(&libc_munmap), 2, addr, length, 0, 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

// ---- file ops ----

func Open(path string, mode int, perm uint32) (fd int, err error) {
	p, err := BytePtrFromString(path)
	if err != nil {
		return -1, err
	}
	r1, _, e := sysvicall6(fnptr(&libc_open), 3, uintptr(unsafe.Pointer(p)), uintptr(mode), uintptr(perm), 0, 0, 0)
	if e != 0 {
		return -1, e
	}
	return int(r1), nil
}

func Close(fd int) error {
	_, _, e := sysvicall6(fnptr(&libc_close), 1, uintptr(fd), 0, 0, 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

func read(fd int, p []byte) (n int, err error) {
	var buf unsafe.Pointer
	if len(p) > 0 {
		buf = unsafe.Pointer(&p[0])
	}
	r1, _, e := sysvicall6(fnptr(&libc_read), 3, uintptr(fd), uintptr(buf), uintptr(len(p)), 0, 0, 0)
	n = int(r1)
	if e != 0 {
		err = e
	}
	return
}

func write(fd int, p []byte) (n int, err error) {
	var buf unsafe.Pointer
	if len(p) > 0 {
		buf = unsafe.Pointer(&p[0])
	}
	r1, _, e := sysvicall6(fnptr(&libc_write), 3, uintptr(fd), uintptr(buf), uintptr(len(p)), 0, 0, 0)
	n = int(r1)
	if e != 0 {
		err = e
	}
	return
}

func readlen(fd int, p *byte, np int) (n int, err error) {
	r1, _, e := sysvicall6(fnptr(&libc_read), 3, uintptr(fd), uintptr(unsafe.Pointer(p)), uintptr(np), 0, 0, 0)
	n = int(r1)
	if e != 0 {
		err = e
	}
	return
}

func pread(fd int, p []byte, offset int64) (n int, err error) {
	var buf unsafe.Pointer
	if len(p) > 0 {
		buf = unsafe.Pointer(&p[0])
	}
	r1, _, e := sysvicall6(fnptr(&libc_pread), 5, uintptr(fd), uintptr(buf), uintptr(len(p)), uintptr(offset), uintptr(offset>>32), 0)
	n = int(r1)
	if e != 0 {
		err = e
	}
	return
}

func pwrite(fd int, p []byte, offset int64) (n int, err error) {
	var buf unsafe.Pointer
	if len(p) > 0 {
		buf = unsafe.Pointer(&p[0])
	}
	r1, _, e := sysvicall6(fnptr(&libc_pwrite), 5, uintptr(fd), uintptr(buf), uintptr(len(p)), uintptr(offset), uintptr(offset>>32), 0)
	n = int(r1)
	if e != 0 {
		err = e
	}
	return
}

func Seek(fd int, offset int64, whence int) (newoffset int64, err error) {
	r1, r2, e := sysvicall6(fnptr(&libc_lseek), 4, uintptr(fd), uintptr(offset), uintptr(offset>>32), uintptr(whence), 0, 0)
	if e != 0 {
		return 0, e
	}
	return int64(r1) | int64(r2)<<32, nil
}

func fcntl(fd int, cmd int, arg int) (val int, err error) {
	r1, _, e := sysvicall6(fnptr(&libc_fcntl), 3, uintptr(fd), uintptr(cmd), uintptr(arg), 0, 0, 0)
	val = int(r1)
	if e != 0 {
		err = e
	}
	return
}

func Fstat(fd int, stat *Stat_t) error {
	_, _, e := sysvicall6(fnptr(&libc_fstat), 2, uintptr(fd), uintptr(unsafe.Pointer(stat)), 0, 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

func Stat(path string, stat *Stat_t) error {
	p, err := BytePtrFromString(path)
	if err != nil {
		return err
	}
	_, _, e := sysvicall6(fnptr(&libc_stat), 2, uintptr(unsafe.Pointer(p)), uintptr(unsafe.Pointer(stat)), 0, 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

func Lstat(path string, stat *Stat_t) error {
	p, err := BytePtrFromString(path)
	if err != nil {
		return err
	}
	_, _, e := sysvicall6(fnptr(&libc_lstat), 2, uintptr(unsafe.Pointer(p)), uintptr(unsafe.Pointer(stat)), 0, 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

func Mkdir(path string, mode uint32) error { return path1(&libc_mkdir, path, uintptr(mode)) }
func Rmdir(path string) error              { return path1(&libc_rmdir, path, ^uintptr(0)) }
func Unlink(path string) error             { return path1(&libc_unlink, path, ^uintptr(0)) }
func Chmod(path string, mode uint32) error { return path1(&libc_chmod, path, uintptr(mode)) }
func Chdir(path string) error              { return path1(&libc_chdir, path, ^uintptr(0)) }

func path1(fn *libcFunc, path string, arg uintptr) error {
	p, err := BytePtrFromString(path)
	if err != nil {
		return err
	}
	nargs := uintptr(2)
	if arg == ^uintptr(0) {
		nargs, arg = 1, 0
	}
	_, _, e := sysvicall6(fnptr(fn), nargs, uintptr(unsafe.Pointer(p)), arg, 0, 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

func Ftruncate(fd int, length int64) error {
	_, _, e := sysvicall6(fnptr(&libc_ftruncate), 3, uintptr(fd), uintptr(length), uintptr(length>>32), 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

func Fchmod(fd int, mode uint32) error {
	_, _, e := sysvicall6(fnptr(&libc_fchmod), 2, uintptr(fd), uintptr(mode), 0, 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

func Fchown(fd int, uid, gid int) error {
	_, _, e := sysvicall6(fnptr(&libc_fchown), 3, uintptr(fd), uintptr(uid), uintptr(gid), 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

func Fchdir(fd int) error {
	_, _, e := sysvicall6(fnptr(&libc_fchdir), 1, uintptr(fd), 0, 0, 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

// writev is pulled by internal/poll via linkname; bless the handshake.
//
//go:linkname writev
func writev(fd int, iovs []Iovec) (uintptr, error) {
	var p unsafe.Pointer
	if len(iovs) > 0 {
		p = unsafe.Pointer(&iovs[0])
	}
	r1, _, e := sysvicall6(fnptr(&libc_writev), 3, uintptr(fd), uintptr(p), uintptr(len(iovs)), 0, 0, 0)
	if e != 0 {
		return r1, e
	}
	return r1, nil
}

// Getdents reads directory entries. On QNX the filesystem resource manager
// returns struct dirent records directly from read() on a directory fd.
// ponytail: assumes the wire dirent matches syscall.Dirent; verify on first
// ReadDir over a real filesystem.
func Getdents(fd int, buf []byte) (n int, err error) {
	return read(fd, buf)
}

func ReadDirent(fd int, buf []byte) (n int, err error) {
	return Getdents(fd, buf)
}

func Fsync(fd int) error {
	_, _, e := sysvicall6(fnptr(&libc_fsync), 1, uintptr(fd), 0, 0, 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

func Dup(fd int) (int, error) {
	r1, _, e := sysvicall6(fnptr(&libc_dup), 1, uintptr(fd), 0, 0, 0, 0, 0)
	if e != 0 {
		return -1, e
	}
	return int(r1), nil
}

func Dup2(old, new int) error {
	_, _, e := sysvicall6(fnptr(&libc_dup2), 2, uintptr(old), uintptr(new), 0, 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

func Pipe(p []int) error {
	if len(p) != 2 {
		return EINVAL
	}
	var pp [2]int32
	_, _, e := sysvicall6(fnptr(&libc_pipe), 1, uintptr(unsafe.Pointer(&pp[0])), 0, 0, 0, 0, 0)
	if e != 0 {
		return e
	}
	p[0], p[1] = int(pp[0]), int(pp[1])
	return nil
}

func Getrlimit(which int, lim *Rlimit) error {
	_, _, e := rawSysvicall6(fnptr(&libc_getrlimit), 2, uintptr(which), uintptr(unsafe.Pointer(lim)), 0, 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

func setrlimit(which int, lim *Rlimit) error {
	_, _, e := rawSysvicall6(fnptr(&libc_setrlimit), 2, uintptr(which), uintptr(unsafe.Pointer(lim)), 0, 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

// ---- dirent helpers ----

func direntIno(buf []byte) (uint64, bool) {
	return readInt(buf, unsafe.Offsetof(Dirent{}.Ino), unsafe.Sizeof(Dirent{}.Ino))
}
func direntReclen(buf []byte) (uint64, bool) {
	return readInt(buf, unsafe.Offsetof(Dirent{}.Reclen), unsafe.Sizeof(Dirent{}.Reclen))
}
func direntNamlen(buf []byte) (uint64, bool) {
	return readInt(buf, unsafe.Offsetof(Dirent{}.Namelen), unsafe.Sizeof(Dirent{}.Namelen))
}

// ---- time helpers ----

func setTimespec(sec, nsec int64) Timespec { return Timespec{Sec: int32(sec), Nsec: int32(nsec)} }
func setTimeval(sec, usec int64) Timeval   { return Timeval{Sec: int32(sec), Usec: int32(usec)} }

// ---- sockets ----

func socket(domain, typ, proto int) (fd int, err error) {
	r1, _, e := rawSysvicall6(fnptr(&libc_socket), 3, uintptr(domain), uintptr(typ), uintptr(proto), 0, 0, 0)
	if e != 0 {
		return -1, e
	}
	return int(r1), nil
}

func socketpair(domain, typ, proto int, fd *[2]int32) error {
	_, _, e := rawSysvicall6(fnptr(&libc_socketpair), 4, uintptr(domain), uintptr(typ), uintptr(proto), uintptr(unsafe.Pointer(fd)), 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

func bind(fd int, sa unsafe.Pointer, salen _Socklen) error {
	_, _, e := sysvicall6(fnptr(&libc_bind), 3, uintptr(fd), uintptr(sa), uintptr(salen), 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

func connect(fd int, sa unsafe.Pointer, salen _Socklen) error {
	_, _, e := sysvicall6(fnptr(&libc_connect), 3, uintptr(fd), uintptr(sa), uintptr(salen), 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

func Listen(fd, backlog int) error {
	_, _, e := sysvicall6(fnptr(&libc_listen), 2, uintptr(fd), uintptr(backlog), 0, 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

func getsockopt(fd, level, opt int, val unsafe.Pointer, vallen *_Socklen) error {
	_, _, e := sysvicall6(fnptr(&libc_getsockopt), 5, uintptr(fd), uintptr(level), uintptr(opt), uintptr(val), uintptr(unsafe.Pointer(vallen)), 0)
	if e != 0 {
		return e
	}
	return nil
}

func setsockopt(fd, level, opt int, val unsafe.Pointer, vallen uintptr) error {
	_, _, e := sysvicall6(fnptr(&libc_setsockopt), 5, uintptr(fd), uintptr(level), uintptr(opt), uintptr(val), vallen, 0)
	if e != 0 {
		return e
	}
	return nil
}

func getpeername(fd int, rsa *RawSockaddrAny, addrlen *_Socklen) error {
	_, _, e := sysvicall6(fnptr(&libc_getpeername), 3, uintptr(fd), uintptr(unsafe.Pointer(rsa)), uintptr(unsafe.Pointer(addrlen)), 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

func getsockname(fd int, rsa *RawSockaddrAny, addrlen *_Socklen) error {
	_, _, e := sysvicall6(fnptr(&libc_getsockname), 3, uintptr(fd), uintptr(unsafe.Pointer(rsa)), uintptr(unsafe.Pointer(addrlen)), 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

func Getsockname(fd int) (sa Sockaddr, err error) {
	var rsa RawSockaddrAny
	var len _Socklen = SizeofSockaddrAny
	if err = getsockname(fd, &rsa, &len); err != nil {
		return
	}
	return anyToSockaddr(&rsa)
}

func recvfrom(fd int, p []byte, flags int, from *RawSockaddrAny, fromlen *_Socklen) (n int, err error) {
	var buf unsafe.Pointer
	if len(p) > 0 {
		buf = unsafe.Pointer(&p[0])
	}
	r1, _, e := sysvicall6(fnptr(&libc_recvfrom), 6, uintptr(fd), uintptr(buf), uintptr(len(p)), uintptr(flags), uintptr(unsafe.Pointer(from)), uintptr(unsafe.Pointer(fromlen)))
	n = int(r1)
	if e != 0 {
		err = e
	}
	return
}

func sendto(fd int, p []byte, flags int, to unsafe.Pointer, tolen _Socklen) error {
	var buf unsafe.Pointer
	if len(p) > 0 {
		buf = unsafe.Pointer(&p[0])
	}
	_, _, e := sysvicall6(fnptr(&libc_sendto), 6, uintptr(fd), uintptr(buf), uintptr(len(p)), uintptr(flags), uintptr(to), uintptr(tolen))
	if e != 0 {
		return e
	}
	return nil
}

func recvmsg(fd int, msg *Msghdr, flags int) (n int, err error) {
	r1, _, e := sysvicall6(fnptr(&libc_recvmsg), 3, uintptr(fd), uintptr(unsafe.Pointer(msg)), uintptr(flags), 0, 0, 0)
	n = int(r1)
	if e != 0 {
		err = e
	}
	return
}

func sendmsg(fd int, msg *Msghdr, flags int) (n int, err error) {
	r1, _, e := sysvicall6(fnptr(&libc_sendmsg), 3, uintptr(fd), uintptr(unsafe.Pointer(msg)), uintptr(flags), 0, 0, 0)
	n = int(r1)
	if e != 0 {
		err = e
	}
	return
}

func recvmsgRaw(fd int, p, oob []byte, flags int, rsa *RawSockaddrAny) (n, oobn int, recvflags int, err error) {
	var msg Msghdr
	msg.Name = (*byte)(unsafe.Pointer(rsa))
	msg.Namelen = uint32(SizeofSockaddrAny)
	var iov Iovec
	if len(p) > 0 {
		iov.Base = &p[0]
		iov.SetLen(len(p))
	}
	var dummy byte
	if len(oob) > 0 {
		if len(p) == 0 {
			iov.Base = &dummy
			iov.SetLen(1)
		}
		msg.Control = &oob[0]
		msg.SetControllen(len(oob))
	}
	msg.Iov = &iov
	msg.Iovlen = 1
	if n, err = recvmsg(fd, &msg, flags); err != nil {
		return
	}
	oobn = int(msg.Controllen)
	recvflags = int(msg.Flags)
	return
}

func sendmsgN(fd int, p, oob []byte, ptr unsafe.Pointer, salen _Socklen, flags int) (n int, err error) {
	var msg Msghdr
	msg.Name = (*byte)(unsafe.Pointer(ptr))
	msg.Namelen = uint32(salen)
	var iov Iovec
	if len(p) > 0 {
		iov.Base = &p[0]
		iov.SetLen(len(p))
	}
	var dummy byte
	if len(oob) > 0 {
		if len(p) == 0 {
			iov.Base = &dummy
			iov.SetLen(1)
		}
		msg.Control = &oob[0]
		msg.SetControllen(len(oob))
	}
	msg.Iov = &iov
	msg.Iovlen = 1
	if n, err = sendmsg(fd, &msg, flags); err != nil {
		return 0, err
	}
	if len(oob) > 0 && len(p) == 0 {
		n = 0
	}
	return n, nil
}

func Accept(fd int) (nfd int, sa Sockaddr, err error) {
	var rsa RawSockaddrAny
	var len _Socklen = SizeofSockaddrAny
	r1, _, e := sysvicall6(fnptr(&libc_accept), 3, uintptr(fd), uintptr(unsafe.Pointer(&rsa)), uintptr(unsafe.Pointer(&len)), 0, 0, 0)
	if e != 0 {
		return -1, nil, e
	}
	nfd = int(r1)
	sa, err = anyToSockaddr(&rsa)
	if err != nil {
		Close(nfd)
		nfd = -1
	}
	return
}

func Shutdown(fd, how int) error {
	_, _, e := sysvicall6(fnptr(&libc_shutdown), 2, uintptr(fd), uintptr(how), 0, 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

// ---- process / wait ----

func Getpid() int {
	r1, _, _ := rawSysvicall6(fnptr(&libc_getpid), 0, 0, 0, 0, 0, 0, 0)
	return int(r1)
}

func Getppid() int {
	r1, _, _ := rawSysvicall6(fnptr(&libc_getppid), 0, 0, 0, 0, 0, 0, 0)
	return int(r1)
}

func Kill(pid int, sig Signal) error {
	_, _, e := sysvicall6(fnptr(&libc_kill), 2, uintptr(pid), uintptr(sig), 0, 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

func Wait4(pid int, wstatus *WaitStatus, options int, rusage *Rusage) (wpid int, err error) {
	var status int32
	r1, _, e := sysvicall6(fnptr(&libc_wait4), 4, uintptr(pid), uintptr(unsafe.Pointer(&status)), uintptr(options), uintptr(unsafe.Pointer(rusage)), 0, 0)
	if e != 0 {
		return -1, e
	}
	if wstatus != nil {
		*wstatus = WaitStatus(status)
	}
	return int(r1), nil
}

// runtime symbols the package expects.
func runtime_entersyscall()
func runtime_exitsyscall()

// keep imports used
var _ = runtime.GOOS
var _ = oserror.ErrNotExist
