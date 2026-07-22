// Copyright 2026 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// QNX Neutrino 6.5 OS layer. libc-call model (like solaris/aix): the runtime
// never issues raw QNX kernel calls, it calls libc.so.3 via asmcgocall ->
// asmsysvicall6 (sys_qnx_arm.s). Scaffolding cloned from os_solaris.go.

//go:build qnx

package runtime

import (
	"internal/abi"
	"internal/runtime/atomic"
	"internal/runtime/sys"
	"unsafe"
)

type mscratch struct {
	v [6]uintptr
}

type mOS struct {
	waitsema uintptr // semaphore for parking on locks
	perrno   uintptr // TLS errno pointer (from __get_errno_ptr); uintptr avoids write barriers in minit
	// Kept off the G stack so the stack can move during the libc call.
	libcall libcall
	ts      timespec
	scratch mscratch
}

// sem_t == sync_t == { int __count; unsigned __owner } (8 bytes).
type semt struct {
	count int32
	owner uint32
}

type libcFunc uintptr

//go:linkname asmsysvicall6x runtime.asmsysvicall6
var asmsysvicall6x libcFunc // name to take addr of asmsysvicall6

func asmsysvicall6() // declared for vet; implemented in sys_qnx_arm.s

//go:nosplit
func sysvicall0(fn *libcFunc) uintptr {
	gp := getg()
	var mp *m
	if gp != nil {
		mp = gp.m
	}
	if mp != nil && mp.libcallsp == 0 {
		mp.libcallg.set(gp)
		mp.libcallpc = sys.GetCallerPC()
		mp.libcallsp = sys.GetCallerSP()
	} else {
		mp = nil
	}
	var libcall libcall
	libcall.fn = uintptr(unsafe.Pointer(fn))
	libcall.n = 0
	libcall.args = uintptr(unsafe.Pointer(fn))
	asmcgocall(unsafe.Pointer(&asmsysvicall6x), unsafe.Pointer(&libcall))
	if mp != nil {
		mp.libcallsp = 0
	}
	return libcall.r1
}

//go:nosplit
func sysvicall1(fn *libcFunc, a1 uintptr) uintptr {
	r1, _ := sysvicall1Err(fn, a1)
	return r1
}

//go:nosplit
func sysvicall1Err(fn *libcFunc, a1 uintptr) (r1, err uintptr) {
	gp := getg()
	var mp *m
	if gp != nil {
		mp = gp.m
	}
	if mp != nil && mp.libcallsp == 0 {
		mp.libcallg.set(gp)
		mp.libcallpc = sys.GetCallerPC()
		mp.libcallsp = sys.GetCallerSP()
	} else {
		mp = nil
	}
	var libcall libcall
	libcall.fn = uintptr(unsafe.Pointer(fn))
	libcall.n = 1
	libcall.args = uintptr(noescape(unsafe.Pointer(&a1)))
	asmcgocall(unsafe.Pointer(&asmsysvicall6x), unsafe.Pointer(&libcall))
	if mp != nil {
		mp.libcallsp = 0
	}
	return libcall.r1, libcall.err
}

//go:nosplit
func sysvicall2(fn *libcFunc, a1, a2 uintptr) uintptr {
	r1, _ := sysvicall2Err(fn, a1, a2)
	return r1
}

//go:nosplit
//go:cgo_unsafe_args
func sysvicall2Err(fn *libcFunc, a1, a2 uintptr) (uintptr, uintptr) {
	gp := getg()
	var mp *m
	if gp != nil {
		mp = gp.m
	}
	if mp != nil && mp.libcallsp == 0 {
		mp.libcallg.set(gp)
		mp.libcallpc = sys.GetCallerPC()
		mp.libcallsp = sys.GetCallerSP()
	} else {
		mp = nil
	}
	var libcall libcall
	libcall.fn = uintptr(unsafe.Pointer(fn))
	libcall.n = 2
	libcall.args = uintptr(noescape(unsafe.Pointer(&a1)))
	asmcgocall(unsafe.Pointer(&asmsysvicall6x), unsafe.Pointer(&libcall))
	if mp != nil {
		mp.libcallsp = 0
	}
	return libcall.r1, libcall.err
}

//go:nosplit
func sysvicall3(fn *libcFunc, a1, a2, a3 uintptr) uintptr {
	r1, _ := sysvicall3Err(fn, a1, a2, a3)
	return r1
}

//go:nosplit
//go:cgo_unsafe_args
func sysvicall3Err(fn *libcFunc, a1, a2, a3 uintptr) (r1, err uintptr) {
	gp := getg()
	var mp *m
	if gp != nil {
		mp = gp.m
	}
	if mp != nil && mp.libcallsp == 0 {
		mp.libcallg.set(gp)
		mp.libcallpc = sys.GetCallerPC()
		mp.libcallsp = sys.GetCallerSP()
	} else {
		mp = nil
	}
	var libcall libcall
	libcall.fn = uintptr(unsafe.Pointer(fn))
	libcall.n = 3
	libcall.args = uintptr(noescape(unsafe.Pointer(&a1)))
	asmcgocall(unsafe.Pointer(&asmsysvicall6x), unsafe.Pointer(&libcall))
	if mp != nil {
		mp.libcallsp = 0
	}
	return libcall.r1, libcall.err
}

//go:nosplit
//go:cgo_unsafe_args
func sysvicall4(fn *libcFunc, a1, a2, a3, a4 uintptr) uintptr {
	gp := getg()
	var mp *m
	if gp != nil {
		mp = gp.m
	}
	if mp != nil && mp.libcallsp == 0 {
		mp.libcallg.set(gp)
		mp.libcallpc = sys.GetCallerPC()
		mp.libcallsp = sys.GetCallerSP()
	} else {
		mp = nil
	}
	var libcall libcall
	libcall.fn = uintptr(unsafe.Pointer(fn))
	libcall.n = 4
	libcall.args = uintptr(noescape(unsafe.Pointer(&a1)))
	asmcgocall(unsafe.Pointer(&asmsysvicall6x), unsafe.Pointer(&libcall))
	if mp != nil {
		mp.libcallsp = 0
	}
	return libcall.r1
}

//go:nosplit
//go:cgo_unsafe_args
func sysvicall5(fn *libcFunc, a1, a2, a3, a4, a5 uintptr) uintptr {
	gp := getg()
	var mp *m
	if gp != nil {
		mp = gp.m
	}
	if mp != nil && mp.libcallsp == 0 {
		mp.libcallg.set(gp)
		mp.libcallpc = sys.GetCallerPC()
		mp.libcallsp = sys.GetCallerSP()
	} else {
		mp = nil
	}
	var libcall libcall
	libcall.fn = uintptr(unsafe.Pointer(fn))
	libcall.n = 5
	libcall.args = uintptr(noescape(unsafe.Pointer(&a1)))
	asmcgocall(unsafe.Pointer(&asmsysvicall6x), unsafe.Pointer(&libcall))
	if mp != nil {
		mp.libcallsp = 0
	}
	return libcall.r1
}

//go:nosplit
//go:cgo_unsafe_args
func sysvicall6(fn *libcFunc, a1, a2, a3, a4, a5, a6 uintptr) uintptr {
	gp := getg()
	var mp *m
	if gp != nil {
		mp = gp.m
	}
	if mp != nil && mp.libcallsp == 0 {
		mp.libcallg.set(gp)
		mp.libcallpc = sys.GetCallerPC()
		mp.libcallsp = sys.GetCallerSP()
	} else {
		mp = nil
	}
	var libcall libcall
	libcall.fn = uintptr(unsafe.Pointer(fn))
	libcall.n = 6
	libcall.args = uintptr(noescape(unsafe.Pointer(&a1)))
	asmcgocall(unsafe.Pointer(&asmsysvicall6x), unsafe.Pointer(&libcall))
	if mp != nil {
		mp.libcallsp = 0
	}
	return libcall.r1
}

// libc.so.3 bindings (all verified present via nm -D on the 6.5 sysroot).
//
//go:cgo_import_dynamic libc_malloc malloc "libc.so.3"
//go:cgo_import_dynamic libc_exit exit "libc.so.3"
//go:cgo_import_dynamic libc_close close "libc.so.3"
//go:cgo_import_dynamic libc_read read "libc.so.3"
//go:cgo_import_dynamic libc_write write "libc.so.3"
//go:cgo_import_dynamic libc_open open "libc.so.3"
//go:cgo_import_dynamic libc_mmap mmap "libc.so.3"
//go:cgo_import_dynamic libc_munmap munmap "libc.so.3"
//go:cgo_import_dynamic libc_sem_init sem_init "libc.so.3"
//go:cgo_import_dynamic libc_sem_wait sem_wait "libc.so.3"
//go:cgo_import_dynamic libc_sem_post sem_post "libc.so.3"
//go:cgo_import_dynamic libc_sem_timedwait sem_timedwait "libc.so.3"
//go:cgo_import_dynamic libc_sched_yield sched_yield "libc.so.3"
//go:cgo_import_dynamic libc_clock_gettime clock_gettime "libc.so.3"
//go:cgo_import_dynamic libc_nanosleep nanosleep "libc.so.3"
//go:cgo_import_dynamic libc_pthread_attr_init pthread_attr_init "libc.so.3"
//go:cgo_import_dynamic libc_pthread_attr_setstacksize pthread_attr_setstacksize "libc.so.3"
//go:cgo_import_dynamic libc_pthread_attr_setdetachstate pthread_attr_setdetachstate "libc.so.3"
//go:cgo_import_dynamic libc_pthread_create pthread_create "libc.so.3"
//go:cgo_import_dynamic libc_sigaction sigaction "libc.so.3"
//go:cgo_import_dynamic libc_sigprocmask sigprocmask "libc.so.3"
//go:cgo_import_dynamic libc_kill kill "libc.so.3"
//go:cgo_import_dynamic libc_getpid getpid "libc.so.3"
//go:cgo_import_dynamic libc_fcntl fcntl "libc.so.3"
//go:cgo_import_dynamic libc_pipe pipe "libc.so.3"
//go:cgo_import_dynamic libc_poll poll "libc.so.3"
//go:cgo_import_dynamic libc_get_errno_ptr __get_errno_ptr "libc.so.3"

// _init_libc initializes QNX libc (TLS/__tls(), errno, malloc, thread setup).
// crt1.o's _start calls it before main; the internal-linked static Go binary has
// no crt, so _rt0_arm_qnx calls it before rt0_go (see rt0_qnx_arm.s).
//
//go:cgo_import_dynamic libc__init_libc _init_libc "libc.so.3"

// The cgo_import_dynamic directive above binds to an unqualified symbol name
// (e.g. "libc_malloc"). Our vars are runtime.libc_malloc; //go:linkname makes
// the linker names match so the dynamic import actually attaches (-> SDYNIMPORT
// -> DT_NEEDED libc.so.3). Without this the vars stay as zero data (null fn ptr).
//
//go:linkname libc_malloc libc_malloc
//go:linkname libc_exit libc_exit
//go:linkname libc_close libc_close
//go:linkname libc_read libc_read
//go:linkname libc_write libc_write
//go:linkname libc_open libc_open
//go:linkname libc_mmap libc_mmap
//go:linkname libc_munmap libc_munmap
//go:linkname libc_sem_init libc_sem_init
//go:linkname libc_sem_wait libc_sem_wait
//go:linkname libc_sem_post libc_sem_post
//go:linkname libc_sem_timedwait libc_sem_timedwait
//go:linkname libc_sched_yield libc_sched_yield
//go:linkname libc_clock_gettime libc_clock_gettime
//go:linkname libc_nanosleep libc_nanosleep
//go:linkname libc_pthread_attr_init libc_pthread_attr_init
//go:linkname libc_pthread_attr_setstacksize libc_pthread_attr_setstacksize
//go:linkname libc_pthread_attr_setdetachstate libc_pthread_attr_setdetachstate
//go:linkname libc_pthread_create libc_pthread_create
//go:linkname libc_sigaction libc_sigaction
//go:linkname libc_sigprocmask libc_sigprocmask
//go:linkname libc_kill libc_kill
//go:linkname libc_getpid libc_getpid
//go:linkname libc_fcntl libc_fcntl
//go:linkname libc_pipe libc_pipe
//go:linkname libc_poll libc_poll
//go:linkname libc_get_errno_ptr libc_get_errno_ptr
//go:linkname libc__init_libc libc__init_libc

var (
	libc__init_libc                 libcFunc
	libc_malloc                     libcFunc
	libc_exit                       libcFunc
	libc_close                      libcFunc
	libc_read                       libcFunc
	libc_write                      libcFunc
	libc_open                       libcFunc
	libc_mmap                       libcFunc
	libc_munmap                     libcFunc
	libc_sem_init                   libcFunc
	libc_sem_wait                   libcFunc
	libc_sem_post                   libcFunc
	libc_sem_timedwait              libcFunc
	libc_sched_yield                libcFunc
	libc_clock_gettime              libcFunc
	libc_nanosleep                  libcFunc
	libc_pthread_attr_init          libcFunc
	libc_pthread_attr_setstacksize  libcFunc
	libc_pthread_attr_setdetachstate libcFunc
	libc_pthread_create             libcFunc
	libc_sigaction                  libcFunc
	libc_sigprocmask                libcFunc
	libc_kill                       libcFunc
	libc_getpid                     libcFunc
	libc_fcntl                      libcFunc
	libc_pipe                       libcFunc
	libc_poll                       libcFunc
	libc_get_errno_ptr              libcFunc
)

//go:nosplit
func semacreate(mp *m) {
	if mp.waitsema != 0 {
		return
	}
	// Allocate the sem on the C heap (libc malloc) so it survives stack moves.
	mp.libcall.fn = uintptr(unsafe.Pointer(&libc_malloc))
	mp.libcall.n = 1
	mp.scratch = mscratch{}
	mp.scratch.v[0] = unsafe.Sizeof(semt{})
	mp.libcall.args = uintptr(unsafe.Pointer(&mp.scratch))
	asmcgocall(unsafe.Pointer(&asmsysvicall6x), unsafe.Pointer(&mp.libcall))
	sem := (*semt)(unsafe.Pointer(mp.libcall.r1))
	if sysvicall3(&libc_sem_init, uintptr(unsafe.Pointer(sem)), 0, 0) != 0 {
		throw("sem_init")
	}
	mp.waitsema = uintptr(unsafe.Pointer(sem))
}

//go:nosplit
func semasleep(ns int64) int32 {
	mp := getg().m
	if ns >= 0 {
		// QNX sem_timedwait uses an ABSOLUTE CLOCK_REALTIME deadline.
		sysvicall2(&libc_clock_gettime, _CLOCK_REALTIME, uintptr(unsafe.Pointer(&mp.ts)))
		sec := ns/1e9 + int64(mp.ts.tv_sec)
		nsec := ns%1e9 + int64(mp.ts.tv_nsec)
		if nsec >= 1e9 {
			sec++
			nsec -= 1e9
		}
		mp.ts.tv_sec = int32(sec)
		mp.ts.tv_nsec = int32(nsec)
		r := sysvicall2(&libc_sem_timedwait, mp.waitsema, uintptr(unsafe.Pointer(&mp.ts)))
		if r != 0 {
			e := *(*int32)(unsafe.Pointer(mp.perrno))
			if e == _ETIMEDOUT || e == _EAGAIN || e == _EINTR {
				return -1
			}
			throw("sem_timedwait")
		}
		return 0
	}
	for {
		r, _ := sysvicall1Err(&libc_sem_wait, mp.waitsema)
		if r == 0 {
			break
		}
		if *(*int32)(unsafe.Pointer(mp.perrno)) == _EINTR {
			continue
		}
		throw("sem_wait")
	}
	return 0
}

//go:nosplit
func semawakeup(mp *m) {
	if sysvicall1(&libc_sem_post, mp.waitsema) != 0 {
		throw("sem_post")
	}
}

//go:nosplit
func osyield_no_g() { sysvicall0(&libc_sched_yield) }

//go:nosplit
func osyield() { sysvicall0(&libc_sched_yield) }

func getCPUCount() int32 {
	// ponytail: QNX has no _SC_NPROCESSORS_ONLN; read _syspage_ptr->num_cpu later.
	return 1
}

//go:nosplit
func cputicks() int64 {
	// ponytail: no cheap per-core cycle counter exposed on armv7 QNX 6.5; nanotime
	// is monotonic and good enough for the profiler's relative sampling.
	return nanotime()
}

//go:nosplit
func nanotime1() int64 {
	var ts timespec
	sysvicall2(&libc_clock_gettime, _CLOCK_MONOTONIC, uintptr(unsafe.Pointer(&ts)))
	return int64(ts.tv_sec)*1e9 + int64(ts.tv_nsec)
}

// qnxWallOffset is a process-local wall-clock correction in nanoseconds (int64
// stored as uint64 bits), added to every walltime() reading. It lets a program
// fix time.Now() from an external source (e.g. SNTP) when the unit's RTC is wrong
// (QNX head units boot at 1970) WITHOUT touching the system clock and without
// perturbing the monotonic clock. Set via runtime.setQnxWallOffset.
var qnxWallOffset uint64

//go:nosplit
func walltime() (sec int64, nsec int32) {
	var ts timespec
	sysvicall2(&libc_clock_gettime, _CLOCK_REALTIME, uintptr(unsafe.Pointer(&ts)))
	off := int64(atomic.Load64(&qnxWallOffset))
	if off == 0 {
		return int64(ts.tv_sec), ts.tv_nsec
	}
	t := (int64(ts.tv_sec)*1e9 + int64(ts.tv_nsec)) + off
	return t / 1e9, int32(t % 1e9)
}

// setQnxWallOffset sets the process-local wall-clock offset (nanoseconds) applied
// by walltime(). Application code reaches it with
//
//	//go:linkname setQnxWallOffset runtime.setQnxWallOffset
//
//go:linkname setQnxWallOffset
func setQnxWallOffset(nsec int64) {
	atomic.Store64(&qnxWallOffset, uint64(nsec))
}

//go:nosplit
func usleep(usec uint32) {
	var ts timespec
	ts.tv_sec = int32(usec / 1e6)
	ts.tv_nsec = int32((usec % 1e6) * 1000)
	sysvicall2(&libc_nanosleep, uintptr(unsafe.Pointer(&ts)), 0)
}

//go:nosplit
func usleep_no_g(usec uint32) { usleep(usec) }

//go:nosplit
func write1(fd uintptr, p unsafe.Pointer, n int32) int32 {
	return int32(sysvicall3(&libc_write, fd, uintptr(p), uintptr(n)))
}

//go:nosplit
func read(fd int32, p unsafe.Pointer, n int32) int32 {
	r, err := sysvicall3Err(&libc_read, uintptr(fd), uintptr(p), uintptr(n))
	if int32(r) < 0 {
		return -int32(err)
	}
	return int32(r)
}

//go:nosplit
func closefd(fd int32) int32 { return int32(sysvicall1(&libc_close, uintptr(fd))) }

//go:nosplit
func open(name *byte, mode, perm int32) int32 {
	return int32(sysvicall3(&libc_open, uintptr(unsafe.Pointer(name)), uintptr(mode), uintptr(perm)))
}

//go:nosplit
func exit(r int32) { sysvicall1(&libc_exit, uintptr(r)) }

//go:nosplit
func exitThread(wait *atomic.Uint32) {
	// ponytail: pthreads are detached; returning from mstart's thread func exits it.
	// Signal completion so the runtime can reuse the stack.
	wait.Store(0)
}

// mmap/munmap for mem_bsd.go. madvise is a no-op (QNX 6.5 lacks it).
//
//go:nosplit
func mmap(addr unsafe.Pointer, n uintptr, prot, flags, fd int32, off uint32) (unsafe.Pointer, int) {
	r := sysvicall6(&libc_mmap, uintptr(addr), n, uintptr(prot), uintptr(flags), uintptr(fd), uintptr(off))
	if r == ^uintptr(0) { // MAP_FAILED
		return nil, int(*(*int32)(unsafe.Pointer(getg().m.perrno)))
	}
	return unsafe.Pointer(r), 0
}

//go:nosplit
func munmap(addr unsafe.Pointer, n uintptr) {
	sysvicall2(&libc_munmap, uintptr(addr), n)
}

//go:nosplit
func madvise(addr unsafe.Pointer, n uintptr, flags int32) {
	// ponytail: QNX 6.5 has no madvise(MADV_DONTNEED/FREE); scavenging is a no-op.
}

//go:nosplit
func getRandomData(r []byte) {
	// ponytail: /dev/random exists on QNX 6.5 (verified); getrandom() does not.
	fd := open(&_dev_random[0], _O_RDONLY, 0)
	if fd < 0 {
		return
	}
	n := read(fd, unsafe.Pointer(&r[0]), int32(len(r)))
	closefd(fd)
	_ = n
}

var _dev_random = [...]byte{'/', 'd', 'e', 'v', '/', 'r', 'a', 'n', 'd', 'o', 'm', 0}

func readRandom(r []byte) int {
	getRandomData(r)
	return len(r)
}

//go:nosplit
func fcntl(fd, cmd, arg int32) (ret int32, errno int32) {
	r, err := sysvicall3Err(&libc_fcntl, uintptr(fd), uintptr(cmd), uintptr(arg))
	return int32(r), int32(err)
}

// QNX fcntl command constants not covered by os_unix.go.
const (
	_F_GETFL = 3
	_F_SETFL = 4
)

//go:nosplit
func pipe() (r, w int32, errno int32) {
	var fds [2]int32
	// pipe() returns 0 on success, -1 on failure — errno is only meaningful
	// on -1 (it may hold a stale value after success).
	ret, err := sysvicall1Err(&libc_pipe, uintptr(unsafe.Pointer(&fds[0])))
	if int32(ret) == -1 {
		return -1, -1, int32(err)
	}
	return fds[0], fds[1], 0
}

//go:nosplit
func setNonblock(fd int32) {
	flags, _ := fcntl(fd, _F_GETFL, 0)
	if flags != -1 {
		fcntl(fd, _F_SETFL, flags|_O_NONBLOCK)
	}
}

//go:nosplit
func raise(sig uint32) {
	pid := sysvicall0(&libc_getpid)
	sysvicall2(&libc_kill, pid, uintptr(sig))
}

//go:nosplit
func raiseproc(sig uint32) { raise(sig) }

//go:nosplit
func signalM(mp *m, sig int) {
	// ponytail: per-thread signal delivery needs QNX pthread_kill / SignalKill;
	// stubbed until preemption milestone (M4).
}

//go:nosplit
func sigprocmask(how int32, new, old *sigset) {
	sysvicall3(&libc_sigprocmask, uintptr(how), uintptr(unsafe.Pointer(new)), uintptr(unsafe.Pointer(old)))
}

func setitimer(mode int32, new, old *itimerval) {
	// ponytail: SIGPROF-based CPU profiling wired at M4; no-op keeps runtime alive.
}

func osinit() {
	numCPUStartup = getCPUCount()
	physPageSize = 4096
	// Cache the TLS errno pointer for m0 now: mallocinit runs early libc mmaps
	// before minit, and their MAP_FAILED path reads m.perrno.
	getg().m.perrno = sysvicall0(&libc_get_errno_ptr)
}

func goenvs() { goenvs_unix() }

func mpreinit(mp *m) {
	mp.gsignal = malg(32 * 1024)
	mp.gsignal.m = mp
}

//go:nosplit
func minit() {
	// Cache the TLS errno pointer for this thread (used by nosplit libc wrappers).
	getg().m.perrno = sysvicall0(&libc_get_errno_ptr)
	minitSignals()
}

func unminit() { unminitSignals() }

// libpreinit and newosproc0 are only reachable through the c-shared/c-archive
// library entry (_rt0_arm_lib in asm_arm.s). QNX buildmode=shared uses the
// normal crt _start -> main -> rt0_go path, so this entry is never taken; these
// exist solely to satisfy the linker's references from that dead asm.
func libpreinit() { initsig(true) }

func newosproc0(stacksize uintptr, fn unsafe.Pointer) {
	throw("newosproc0 not implemented on qnx")
}

//go:nosplit
func mdestroy(mp *m) {}

type pthread uint32 // QNX pthread_t is an int thread id

type pthreadattr struct {
	// struct _thread_attr (target_nto.h): flags,stacksize,stackaddr,exitfunc,
	// policy,sched_param,guardsize,prealloc,spare[2]. Pad generously.
	_ [64]byte
}

const _PTHREAD_CREATE_DETACHED = 0x1

// tstart is the pthread entry trampoline (sys_qnx_arm.s): sets g=mp.g0, stack
// bounds, then calls mstart.
func tstart()

func newosproc(mp *m) {
	var attr pthreadattr
	var oset sigset
	var tid pthread

	if sysvicall1(&libc_pthread_attr_init, uintptr(unsafe.Pointer(&attr))) != 0 {
		throw("pthread_attr_init")
	}
	if sysvicall2(&libc_pthread_attr_setstacksize, uintptr(unsafe.Pointer(&attr)), 0x200000) != 0 {
		throw("pthread_attr_setstacksize")
	}
	if sysvicall2(&libc_pthread_attr_setdetachstate, uintptr(unsafe.Pointer(&attr)), _PTHREAD_CREATE_DETACHED) != 0 {
		throw("pthread_attr_setdetachstate")
	}

	// Start the new thread with all signals blocked; minit unblocks them.
	sigprocmask(_SIG_SETMASK, &sigset_all, &oset)
	ret := sysvicall4(&libc_pthread_create,
		uintptr(unsafe.Pointer(&tid)),
		uintptr(unsafe.Pointer(&attr)),
		abi.FuncPCABI0(tstart),
		uintptr(unsafe.Pointer(mp)))
	sigprocmask(_SIG_SETMASK, &oset, nil)
	if ret != 0 {
		print("runtime: pthread_create failed (errno=", ret, ")\n")
		throw("newosproc")
	}
}

// Profiling / security stubs.
func setProcessCPUProfiler(hz int32) {}
func setThreadCPUProfiler(hz int32)  {}
func validSIGPROF(mp *m, c *sigctxt) bool { return true }

//go:nosplit
func (c *sigctxt) fixsigcode(sig uint32) {}

//go:nosplit
func initSecureMode() {}

//go:nosplit
func isSecureMode() bool { return false }

func sysauxv() {}

// Per-thread syscall machinery is a Linux-only feature; assign a bogus signal.
const sigPerThreadSyscall = 1 << 31

func runPerThreadSyscall() { throw("runPerThreadSyscall only valid on linux") }
