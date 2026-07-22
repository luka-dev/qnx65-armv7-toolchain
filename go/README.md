# Go → QNX 6.5 / ARMv7 (GOOS=qnx GOARCH=arm)

Goal: a `gc`-toolchain Go port so Tailscale (full stdlib Go) can build for the
MHI2Q head unit (QNX 6.5.0, ARMv7-A). This is a **new-GOOS port**, not a
cross-compile of existing code — QNX is not a supported GOOS today (no upstream,
no fork, verified 2026-07).

## The one hard fact that shapes everything
Go's Linux runtime makes **raw syscalls** (SVC/SYSCALL, bypassing libc). QNX is
a message-passing microkernel: **the only way into the kernel is through
`libc.so.3`**. So a "linux-style" port is impossible. The template is the
**libc-call ports already in the tree — `aix/ppc64` and `solaris/amd64`** — whose
runtimes call libc via `asmcgocall`/`libcall` instead of raw syscalls.

New wrinkle vs those: both libc ports are 64-bit (ppc64, amd64). **QNX 6.5 is
armv7 (32-bit).** No existing port pairs the libc-call model with 32-bit ARM, so
the asm bridge `sys_qnx_arm.s` is **written from scratch** (darwin/arm64's
`sys_libc.go` + `sys_darwin_arm64.s` are the closest mechanism reference).

## Assets → role  (same VM as rust-qnx65)
| Asset | Use |
|---|---|
| QNX x86 VM `root@192.168.64.16` (`../../qnx_ssh.sh`) | 6.5 armv7 toolchain: `arm-unknown-nto-qnx6.5.0eabi-gcc-4.4.2`, `ntoarm-ld 2.19`, sysroot `/usr/qnx650/target/qnx6/armle-v7`. Source of **all struct/constant values** for `defs_qnx_arm.go` and the **external linker** (Go emits `.o`, QNX gcc links the ELF). |
| `Tools/qnx-gl-passthrough` QEMU (cortex-a15, real procnto + libc.so.3) | on-device test bed — same one rust-qnx65 used for its milestones. |
| `Refferences/qnx_source` (QNX 6.3.0 src) | reference for libc struct layouts / ucontext / sigset. |

## libc symbol reality (measured on the VM, 2026-07)
libc.so.3 has almost everything the runtime needs: `pthread_create`,
`pthread_key_*`, `sem_*`(check), `mmap`, `munmap`, `sigaction`, `sigprocmask`,
`clock_gettime`, `nanosleep`, `posix_spawn`, sockets. Missing (shim in Go/asm):
`pipe2`, `accept4`, `dup3`, `getrandom`, `arc4random`. `/dev/random` exists.
(Full list: `../tailscale`-thread recon; same deltas as the Rust path.)

## STATUS
- [x] **Milestone 0 — workspace** (2026-07): `goroot/` = writable git copy of
      go1.26.4, rebuilds clean via `make.bash` (GOROOT_BOOTSTRAP = host go), 41s.
- [x] **Milestone 1 — GOOS plumbing end-to-end** (2026-07): `GOOS=qnx GOARCH=arm`
      is now a recognized target through the *entire* front half of the toolchain.
      Registered in: `internal/syslist` (KnownOS+UnixOS), `internal/goos`
      (regenerated zgoos_*, added `zgoos_qnx.go`), `cmd/dist/build.go`
      (okgoos, unixOS, `cgoEnabled["qnx/arm"]=false`), `internal/platform/zosarch.go`
      (regenerated, `qnx/arm` in distInfo), `cmd/internal/objabi/head.go`
      (`Hqnx` headtype, ELF family). `go tool dist list` shows `qnx/arm`; build
      passes target validation, compiler accepts the GOOS, and stops **exactly at
      the runtime OS layer** — the intended cheap wall:
      ```
      runtime2.go: undefined: sigset, mOS
      os_unix_nonlinux.go: undefined: sigctxt
      signal_unix.go: undefined: _SIGURG, _NSIG
      ```
      Total front-half cost: ~1 day. Everything past here is the runtime port.
- [x] **Milestone 1.5 — defs + sigctxt** (2026-07): `defs_qnx_arm.go` (all consts +
      structs, values pulled from the real 6.5 sysroot — see `NOTES-qnx-defs.md`) and
      `signal_qnx_arm.go` (sigctxt over ARM `gpr[16]`/`spsr`). Both parse; the runtime
      wall is now down to the OS-layer functions: `mOS`, `cputicks`, `osyield`,
      `getCPUCount`, `setThreadCPUProfiler` (+ more behind the 10-error cap:
      sema*/osinit/newosproc/mmap/nanotime and the libc asm bridge). Front of the
      runtime compiles; the OS layer + `sys_qnx_arm.s` is what remains.
- [x] **Milestone 2 — Go OS layer compiles** (2026-07): the entire Go-side runtime
      for qnx/arm compiles clean. Added `os_qnx.go` (mOS + solaris-style `sysvicall`
      libc bridge + libc.so.3 bindings + sema via `sem_t` + nanotime/walltime/mmap/
      read/write/minit/…), `signal_qnx.go` (setsig/sigaction/sigaltstack-stub/
      sigaddset), `sigtab_qnx.go` (QNX signal table). Wired qnx into the build-tag
      graph mirroring solaris (lock_sema, mem_bsd, excluded from mmap/stubs2/stubs3/
      timestub2; netpoll→stub like plan9; signal_arm += qnx). The ONLY remaining
      compile error is the ABI0 boundary:
      ```
      signal_qnx.go: FuncPCABI0 expects ABI0 function, sigtramp is defined as ABIInternal
      ```
      i.e. everything now waits on `sys_qnx_arm.s` (the asm libc bridge: asmsysvicall6,
      sigtramp, rt0, tlsg). Known landmines deferred to M4 and documented inline:
      no sigaltstack, no madvise, getCPUCount=1 (syspage later), newosproc stubbed.
- [x] **Milestone 2.9 — Go builds a QNX ARM ELF end-to-end** (2026-07):
      `sys_qnx_arm.s` (asmsysvicall6 EABI libc bridge + sigtramp/sigfwd/
      publicationBarrier), `rt0_qnx_arm.s`, `os_qnx_arm.go` (checkgoarm). cmd/link
      taught Hqnx: TLS offset, arm archinit/Elfinit, asmbElf, UsesLibc, and
      `PT_INTERP=/usr/lib/ldqnx.so.2` (new `ELFArch.Qnxdynld`).
      `GOOS=qnx GOARCH=arm GOARM=7 go build hello.go` now emits:
      `ELF 32-bit LSB executable, ARM, dynamically linked, interpreter /usr/lib/ldqnx.so.2`.
      ⚠ **M3 blocker found**: the internal linker emits NO `DT_NEEDED libc.so.3` and
      no dynamic symbols — `//go:cgo_import_dynamic` isn't wired to real dynamic
      imports for Hqnx yet (`.dynamic` STRSZ=1, 0 relocs). So the binary loads its
      interp but can't resolve libc. Fix path = external link via the QNX arm gcc on
      the VM (`-linkmode=external -extld=…`, the rust-qnx65 approach) OR finish
      internal dynimport wiring. Next milestone.
- [x] **Milestone 2.95 — internal dynamic linking to libc.so.3 works** (2026-07):
      the DT_NEEDED gap is fixed via three changes (QNX/armv7 is the first 32-bit
      libc-call Go target, so this path was unexercised):
      1. `os_qnx.go`: `//go:linkname libc_X libc_X` so `cgo_import_dynamic` binds
         the vars → SDYNIMPORT (not zero data / null fn ptr).
      2. `cmd/link/internal/arm/asm.go`: R_ADDR from TEXT→SDYNIMPORT via GOT +
         R_ARM_GLOB_DAT (arm only handled the DATA case; mirrors amd64).
      3. `cmd/link/internal/ld/elf.go`: emit DT_NEEDED in the ELF32 branch of
         `elfadddynsym` (block existed only in the ELF64 branch).
      Now `GOOS=qnx GOARCH=arm CGO_ENABLED=0 go build` → ELF 32-bit ARM, interp
      ldqnx.so.2, **DT_NEEDED libc.so.3**, 21 UND libc dynsyms + GLOB_DAT relocs.
      Pure internal linking = self-contained cross-compiler (no QNX toolchain to
      link). NOTE: `go build` caches the final link — use `-a` or a clean
      `make.bash` after linker edits, or you observe stale binaries.
      Next: **M3 run** — mkifs + QEMU cortex-a15 (copy of Tools/qnx-gl-passthrough),
      read `println` off the serial. First real on-device Go.

## REMAINING — the runtime port (the person-months)
Create the OS layer (clone solaris/aix template, retarget to arm, real QNX values):

| File | Contents | Hard? |
|---|---|---|
| `defs_qnx_arm.go` / `defs1_qnx_arm.go` | signal nums, `_NSIG`, `_SIG*`, mmap/errno consts, `sigset`, `siginfo`, `mcontext`/`ucontext`, `timespec` — **exact values from VM sysroot headers** | medium (mechanical but must be exact) |
| `sys_qnx_arm.s` | ARM asm bridge runtime→libc (`asmcgocall`→`libcall`), `rt0`, `sigtramp`, `tlsg` | **HARD — new code, no arm template** |
| `os_qnx.go` / `os2_qnx.go` / `os3_qnx.go` | `mOS`, `semacreate/sleep/wakeup` (libc sem or pthread cond), `osinit`, `newosproc` via `pthread_create`, `sigprocmask`, `minit/unminit` | HARD |
| `signal_qnx.go` / `signal_qnx_arm.go` | `sigctxt` type + register accessors off ucontext | medium |
| `syscall_qnx.go` / `syscall2_qnx.go` | `//go:cgo_import_dynamic` libc bindings + shims (pipe2/accept4/dup3/getrandom) | medium |
| `netpoll_qnx.go` | poll/select-based netpoll (QNX has no epoll/kqueue; use `/dev/socket` + poll) | medium-HARD |
| `rt0_qnx_arm.s` | process entry | low |
| cmd/link ELF/QNX | interpreter `/usr/lib/ldqnx.so.2`, QNX ELF notes, external-link default | medium |
| syscall + os + net std pkgs | `zerrors_qnx_arm.go`, `ztypes`, `syscall_qnx.go`, socket/os shims | medium (volume) |

Milestone ladder after this (mirrors rust-qnx65):
- **M2** runtime compiles with stubbed OS layer (panics at runtime OK).
- **M3** `println("hi")` links (external QNX gcc) + runs in QEMU → **on-device Go real**.
- **M4** goroutines + GC + channels run (scheduler/threads/TLS proven).
- **M5** `net` + `os` work → the primitives Tailscale needs.
- **M6** build tailscaled.

## Reproduce Milestone 1
```
cd goroot/src
export GOROOT="$(cd .. && pwd)" GOROOT_BOOTSTRAP=/opt/homebrew/Cellar/go/1.26.4/libexec
./make.bash                       # rebuild toolchain with qnx plumbing
cd "$GOROOT"
printf 'package main\nfunc main(){ println("hi") }\n' > /tmp/hw.go
GOOS=qnx GOARCH=arm GOARM=7 CGO_ENABLED=0 ./bin/go build /tmp/hw.go   # → runtime wall
```

## Honest comparison to the Rust path (`../mhi2-carplay/tools/rust-qnx65`)
Rust already **runs on this exact QNX 6.5** (sockets, alloc, pthread, TLS — all
milestones passed). Go is strictly behind: the whole runtime OS layer + a
from-scratch ARM libc bridge is still ahead, and only *then* do you get to fight
Tailscale's stdlib surface. Go-port is pursued here by explicit request; the
lazy-correct route to a tunnel on QNX remains boringtun-on-Rust.

## Milestone 3 debugging log (2026-07) — reached libc init, root-caused the crash
Full trace of where a Go binary dies on real QNX 6.5 (QEMU cortex-a15):

1. **procnto accepts+execs the binary** after 3 ELF-format fixes (e_flags EABI5,
   no PT_TLS, rodata folded into text = 2 PT_LOAD). Process starts.
2. **ldqnx (=libc.so.3) couldn't parse our .dynamic** (link_map+44 == NULL) because
   Go emits its build-id NOTE phdr BEFORE .text; QNX's phdr scan chokes on the early
   NOTE. Workaround: build with `-ldflags="-B none -buildid="` (drops the NOTE phdr).
   Real fix TODO: suppress/relocate the early NOTE in cmd/link for Hqnx.
3. Fixed our own bug: `&libc_X` must resolve to the PLT stub (callable), not the GOT
   slot. arm/asm.go uses addpltsym now. Also emit DT_INIT/FINI/INIT_ARRAY/FINI_ARRAY
   (QNX walks the full lifecycle set) and STT_FUNC for the libc imports.
4. **Current wall**: `DL_DEBUG=debug,bindings` + `qemu -d int,cpu` root-caused the
   crash exactly:
   - It is inside **libc.so.3's OWN init** (which ldqnx runs before our entry).
   - Divergence vs stock ls: ls does ...ConnectAttach, memmove, __get_barena... (sets
     up the malloc arena, runs). Ours does ...ConnectAttach, __ker_err, MsgSendvnc → crash.
   - Prefetch Abort, IFAR=0xfffffffe. Faulting instr = the `pop {r4, pc}` return of a
     syscall stub at libc+0x379b8, kernel call **#12 = __KER_MSG_SENDVNC (MsgSendvnc)**.
     The reply from the resource manager **overwrote the saved return address on the
     stack with 0xffffffff** → return faults. Regs at fault: R12=0x0c (syscall#),
     R2=0xffffffc8(-56), R14=0x0101d174 (correct caller in libc), reply-IOV on stack.
   So: libc's init sends a message to a resmgr and the reply corrupts the stack — for
   OUR process, not for stock ls. Something about our process setup makes the resmgr
   interaction return unexpected/oversized data.
   - Note: stock ls has a QNX-specific NOTE (name="QNX", type 3, desc {0,0x1000}) that
     we lack; but `sh` runs with only 1 note, so the QNX note is likely not required.
   Next: reverse the libc caller at 0x1d174 (how it sizes the MsgSendvnc reply IOV), or
   QEMU-gdb to read the IOV args live and see why the reply overflows for our process.

## M3 debug (cont.) — crash root-caused to a failing libc resmgr connect
Via `qemu -d int,cpu` I read the exact faulting MsgSendvnc arguments:
  R00=0x40000000 (coid)  R01=R03=stack buf  R02=-56 (send)  R04=-24 (reply)
  fault: saved return address on the stack overwritten with 0xffffffff.
- Ruled OUT stack/binary overlap: rebuilt at -T 0x800000 (stack moved to 0x7fec00,
  below the binary at 0x7ff000, no overlap) — still crashes identically.
- coid 0x40000000 == _NTO_SIDE_CHANNEL — a placeholder, i.e. the real connection
  was never established. DL_DEBUG showed our path takes the __ker_err (kernel error)
  branch where stock ls takes memmove/__get_barena (malloc arena set up OK).
- The libc init sequence (_syspage_time -> nsec2timespec -> div -> open -> _connect
  -> ConnectAttach) plus strings "/tmp//000000", "/dev/shmem", "__get_barena" says:
  libc creates a shared-memory object (time-named) to back the malloc arena, and the
  open/ConnectAttach FAILS for our process (succeeds for ls), leaving a bogus coid;
  the subsequent MsgSendvnc corrupts the stack.
Hypotheses for WHY the connect fails for our process (next session):
  * our process can't reach the system page (_syspage_time) -> bad temp name; check
    if our ELF layout keeps procnto from mapping the syspage.
  * missing QNX ELF note (ls has name="QNX" type=3 desc{0,0x1000}) that configures
    the process; add it in cmd/link and retest.
  * namespace/permission difference in how procnto starts our (Go-linked) process.
Next: reverse UP the libc chain to the open()/path, or gdb-break at ConnectAttach
to read its args + return for our process vs ls.

## M3 debug (gdb + caller reverse) — down to the exact _MEM_MAP message
Reversed the libc caller (0x1d0f8 = a MsgSendv wrapper) and used arm-none-eabi-gdb
against the QEMU gdbstub (hbreak *0x10379b4, condition r0==0x40000000 && r1==<our buf>)
to read the exact failing message. It is a **_MEM_MAP (type 0x40) to procnto**, i.e.
libc's mmap() for the malloc arena. The smoking-gun difference:
  successful early process:  _MEM_MAP len = 0x8000  (32 KB)
  OUR (crashing) process:    _MEM_MAP len = 0x40000 (256 KB), prot=RW, ANON|PRIVATE, fd=-1
Before the svc the stack is clean (saved LR = 0x0101d174 valid); the crash is a later
`pop {r4,pc}` two frames up (SP 0x7fecfc, saved LR slot 0x7fed00) returning 0xffffffff.
Working theory: the 256 KB anon arena mmap gets placed by procnto overlapping our
main-thread stack (our binary is huge -> fragmented address space), and libc's arena
init then writes over the saved return address. ls's 32 KB arena lands clear.
Tried MALLOC_ARENA_SIZE=8192 env -> no change (not honored / not the arena var).
Next: (a) find why our process's first libc arena is 256 KB vs 32 KB (proportional to
our large data/BSS?); (b) check whether procnto places the arena over the stack (gdb:
read the _MEM_MAP reply address); (c) add the QNX ELF note / a proper stack reservation
so the stack is carved out before the arena mmap.
TOOLS READY for next session: m3run.sh (cksum-gated), qemu -d int,cpu, arm-none-eabi-gdb
scripts /tmp/gdb*.txt, llvm-mc offline disassembly of libc.so.3.

## ✅ MILESTONE 3 COMPLETE (2026-07) — Go RUNS on QNX 6.5 armv7
A Go program built with our from-scratch GOOS=qnx port executes on real QNX 6.5:
```
GOHELLO: hello from Go on QNX 6.5 armv7
GOHELLO: runtime is alive
Process exited status=0.
```
The final chain of fixes after the ELF/loader work:
1. sys_qnx_arm.s asmsysvicall6: fixed EABI stack-arg placement (was writing the 5th
   C arg over Go's saved LR at 0(SP) -> 0xffffffff return). Found via gdb backtrace
   (mmap <- runtime.sysAlloc). This unblocked the whole runtime.
2. os_qnx.go: set m0.perrno in osinit (early mmap MAP_FAILED path read nil perrno).
3. sigtab_qnx.go: size sigtable to _NSIG (initsig indexed past a 32-entry table).
4. newosproc via pthread_create + tstart trampoline (sys_qnx_arm.s) — real threads.
Working end to end: libc-call bridge, internal dynamic link to libc.so.3, mmap/heap,
GC, signals, scheduler, sysmon thread, clean exit. Build with
`-ldflags="-R 0x1000 -B none -buildid="` (4KB pages, drop the early NOTE phdr).
Deferred (not needed for hello, matter for Tailscale): TLS via CP15 in tstart (skipped;
g stays in R10), sigaltstack, netpoll (stubbed), getCPUCount=1.

## ✅ MILESTONE 4 (2026-07) — syscall + os (files) + netpoll, HARDWARE-VERIFIED
Ported the `syscall` package and the `os` file layer for GOOS=qnx GOARCH=arm, then
wired a real poll(2)-based network poller. Verified on real QNX 6.5 in QEMU:
```
GOFIO: pid=3 uid=0 euid=0
GOFIO: hostname="localhost"
GOFIO: WriteFile ok
GOFIO: stat name=gofio.txt size=36 mode=-rw-r--r-- isdir=false
GOFIO: read back 36 bytes: "hello from Go os package on QNX 6.5\n"
GOFIO: roundtrip OK
Process exited status=0.
```
What landed:
- `syscall`: zerrors/ztypes from the 6.5 sysroot headers (errno, S_IF*, O_*, sockaddr
  BSD-layout with sa_len, struct stat 32-bit hi/lo split — layout confirmed correct by
  the stat output above). syscall_qnx.go/qnx2.go: file/socket/id/time libc bindings via
  the sysvicall6 bridge (asm_qnx_arm.s -> runtime.syscall_sysvicall6). WaitStatus,
  sockaddr encode/decode, writev, ReadDirent, Getpid/uid/gid, Gethostname, UtimesNano.
  exec (fork) is stubbed ENOSYS (QNX uses spawn(), not fork()).
- `internal/syscall/unix`: QNX has NO *at() family (predates POSIX.1-2008), so at_qnx.go
  emulates the dirfd==AT_FDCWD case via the plain path-based libc calls (Openat, Fstatat,
  Unlinkat, faccessat, ...); a real dirfd returns ENOSYS.
- Shared `unix`-tagged files reused by adding `|| qnx`: forkpipe, sockcmsg, iovec,
  sys_cloexec, fd_writev_libc, fd_fsync_posix, dir_unix, wait_unimp, eloop_other,
  executable_path (argv0-based), statat_other (path-join, no fstatat).
- `os`: stat_qnx.go (fillFileStatFromSys, int32 time_t), dirent_qnx.go, sys_qnx.go.
- `runtime` netpoll: real poll(2) backend (netpoll_qnx.go, cloned from the AIX design)
  now that internal/poll is pulled in; netpoll.go de-excludes qnx, netpoll_stub.go drops
  it. os_qnx.go gains pipe()/setNonblock() + libc_pipe/libc_poll bindings.

Ceilings (ponytail-marked, revisit when needed):
- QNX `pipe()` needs the pipe resource manager, absent on the minimal QEMU image.
  netpollinit degrades gracefully: negative wake-fd (poll ignores fd<0) + capped 10ms
  poll timeout so timers/netpollBreak still fire. On a full head-unit image with the
  pipe manager, the self-pipe wake path activates automatically.
- os.ReadDir returns 0 entries: read() on a directory fd yields no dirents on this image
  (Getdents == read()). Needs a QNX-native dir-read path; not on the file-I/O critical
  path.
- O_DIRECTORY/O_NOFOLLOW = 0 (QNX lacks them) — os.Root symlink hardening is weakened.

NEXT: `net` — sockopt constants (SO_TYPE, IP_*/IPV6_*), sysSocket, interfaceTable
enumeration, setDefault*Sockopts, keepalive setters, and the Getsockname wrapper
signature. syscall socket primitives (socket/bind/connect/accept/recv/send) are already
in place; net is the remaining glue.

## ✅ MILESTONE 5 (2026-07) — net + crypto/tls + net/http COMPILE, net path runs on HW
Ported the `net` glue on top of the syscall socket primitives. `net`, `crypto/tls`,
and `net/http` now build for GOOS=qnx GOARCH=arm, and the net code path executes on
real QNX 6.5 (QEMU):
```
GONET: start
GONET: Listen err=listen tcp 127.0.0.1:0: socket: errno 247 (io-pkt not running?)
GONET: net code path executed without crashing — done
Process exited status=0.
```
errno 247 = EAFNOSUPPORT: the minimal QEMU IFS has no io-pkt (TCP/IP stack), so
AF_INET socket() is refused — but the whole path (dynamic link to libsocket.so.3,
socket() bridge, Go error translation) works and fails cleanly instead of crashing.

What landed:
- syscall: socket/tcp/ip sockopt constants (SO_TYPE, SOCK_SEQPACKET, TCP_NODELAY,
  TCP_KEEPALIVE, IP_*/IPV6_* multicast+membership, IPV6_V6ONLY, EALREADY, SOMAXCONN)
  from the 6.5 headers. High-level Getsockname(fd)->(Sockaddr,error); Getpeername is
  generic. **Socket bindings point at libsocket.so.3, not libc.so.3** — on QNX the BSD
  socket API lives in libsocket (this was the "Unresolved symbol socket" loader error).
  The internal linker emits DT_NEEDED for both libc.so.3 and libsocket.so.3.
- net: sockopt_qnx.go (setDefault*Sockopts, cloned from solaris), tcpsockopt_qnx.go
  (setKeepAliveIdle -> TCP_KEEPALIVE; interval/count are no-ops — QNX 6.5 lacks the
  granular knobs). Reused shared files via || qnx: sys_cloexec (sysSocket, no accept4),
  sockoptip4_bsdvar, sock_stub (maxListenerBacklog), unixsock_readmsg_cloexec.
  interface_stub (interfaceTable) — see ceiling.
- crypto/internal/sysrand: rand_qnx.go -> /dev/urandom fallback (no getrandom syscall).
- crypto/x509: root_qnx.go (cert file/dir probe list) + || qnx on root_unix.go.
- qemu/gohello.build: bundle libsocket.so.3 (staged from the SDP armle-v7 sysroot) into
  /proc/boot so the loader can resolve the socket symbols.

Ceilings (ponytail-marked):
- **io-pkt not in the QEMU IFS**: real TCP/UDP needs the QNX TCP/IP stack (io-pkt-v6-hc
  + a NIC driver like devnp-*) running. Bringing that up in the virt IFS is the next
  infra step; until then socket() returns EAFNOSUPPORT. On a real head unit with io-pkt
  already running, the same binary should get working sockets.
- interface enumeration is stubbed (interfaceTable returns nil) — needs SIOCGIFCONF/
  getifaddrs. Tailscale will need this; revisit with io-pkt.
- TCP keepalive interval/count are no-ops (QNX has only TCP_KEEPALIVE idle seconds).

NEXT: io-pkt bring-up in the test IFS (NIC + stack + ifconfig) to exercise real
sockets, then interface enumeration, then start building Tailscale itself against this
toolchain.

## ✅ MILESTONE 6 (2026-07) — VALIDATED ON THE REAL MHI2q HEAD UNIT; full std builds
Ran Go binaries directly on the actual Audi head unit (root@10.173.189.1):
`QNX mmx 6.5.0 APQ8064 armle` (Qualcomm Snapdragon, Harman MHI2q), io-pkt-v6-hc live.

**TCP works end to end on real hardware:**
```
GONET: listening on 127.0.0.1:65478
GONET: server got "ping"   GONET: client got "pong"
GONET: TCP loopback roundtrip OK      (exit 0)
```
**DNS + TCP + TLS handshake all work** (HTTPS to example.com over the real network):
```
GOHTTP: DNS example.com -> [172.66.147.243 104.20.23.154 2606:4700:10::6814:179a ...]
GOHTTP: GET err=... tls: failed to verify certificate: x509: certificate has expired
        or is not yet valid: current time 1970-01-01T00:08:16Z is before 2026-05-31
```
The only failure is the unit's RTC sitting at epoch (1970) — x509 correctly rejects a
valid cert against a 1970 clock. That is a device-config issue, not a port defect: the
pure-Go resolver, outbound TCP, and the TLS handshake + certificate parsing all ran.
File I/O also verified on the unit (WriteFile/Stat/ReadFile roundtrip, hostname="mmx").

**THE netpoll bug (critical):** `poll_runtime_pollWait` only calls `netpollarm()` for
level-triggered pollers — its GOOS list was solaris/illumos/aix/wasip1. QNX uses the
same poll(2) backend, so without qnx in that list, registered fds were never armed for
POLLIN/POLLOUT and every async connect/accept/read/write timed out. Added qnx →
sockets sprang to life. (Found by instrumenting netpoll on-device: fds opened but no
`arm` calls, poll returning ETIMEDOUT.)

Also: whole Go **standard library builds** for GOOS=qnx GOARCH=arm (`go build std` clean)
— added os.Pipe (|| qnx), archive/tar atime (int32 time_t), syscall.Getrusage/RUSAGE_SELF.

Deploy note: strip binaries (`-ldflags="-s -w ..."`) — the head unit's /tmp is /dev/shmem
(RAM); a 7.8 MB unstripped binary was truncated (exec RC=126), the 5.5 MB stripped one ran.

NEXT: build Tailscale itself against this toolchain (interface enumeration + a couple of
syscalls may surface); set the unit clock for TLS; wire posix_spawn if os/exec is needed.

## ✅ MILESTONE 7 (2026-07) — TAILSCALE DAEMON RUNS ON THE AUDI HEAD UNIT
Built real Tailscale (`cmd/tailscaled`, tailscale.com @ 1.101.0-dev) against the qnx/arm
toolchain and ran it on the actual MHI2q unit (QNX 6.5.0 APQ8064 armle).

`tailscaled --version` on-device:
```
1.101.0-dev20260718   go version: go1.26.4   (exit 0)
```
`tailscaled --tun=userspace-networking` on-device — the daemon core comes up:
```
wgengine.NewUserspaceEngine(tun "userspace-networking") ...
magicsock: disco key = d:8f1c19820ce96923
magicsock: SetNetworkUp(false)
Starting network monitor...
```
WireGuard userspace engine, magicsock UDP4/UDP6 sockets, disco crypto key, and the
network monitor all initialize. (UDP buffer setsockopt returns ENOBUFS for the 7 MB
request — QNX caps it; Tailscale logs and continues.)

Port surface (small — tailscale/wireguard/gvisor have good `_other` fallbacks + userspace
netstack): go.mod go 1.26.5→1.26.4; local `replace` patches for wireguard-go (uapi_fake
+qnx, tun_qnx CreateTUN stub), golang.org/x/sys/unix (unix_qnx.go poll/fd/sockopt shim
over the ported std syscall), djherbis/times (32-bit time_t); tailscale posture
serialnumber_stub +qnx; crypto rand_qnx + x509 root_qnx. Full recipe: ../BUILD_TAILSCALE_QNX.md.

**Two load-bearing runtime fixes (both committed in goroot):**
1. netpoll level-triggered arming for qnx (else all async sockets time out).
2. FIPS-140 drbg drops its 32 MiB static entropy buffer on qnx — procnto commits BSS at
   exec, so the 32 MiB reserve made tailscaled unloadable (ENOMEM).

**Exec size ceiling (this unit):** 32-bit QNX exec fails >~15 MB. Full tailscaled is ~21 MB;
trimmed to 14.9 MB with `ts_omit_*` tags it loads and runs. All unit storage is qnet; only
/tmp (→ /dev/shmem) is mmap-capable for exec, so run from there.

NEXT: `tailscale up` (auth/login flow) — needs the unit RTC set (TLS cert validation is at
1970) and interface enumeration (currently stubbed); then a real tailnet join.

## ✅ MILESTONE 8 (2026-07) — interface enumeration + network time; daemon brings the network UP
On-device progress toward `tailscale up`:
- **Network time (SNTP):** the unit RTC is dead (boots at 1970), so a tiny SNTP client
  (UDP to pool.ntp.org) + syscall.ClockSettime sets the clock from the network. Verified:
  `SNTP: set clock ... -> 2026-07-18T...Z`. Setting the clock advanced TLS from
  "certificate expired/not yet valid" to normal chain verification.
- **Interface enumeration:** net/interface_qnx.go implements net.Interfaces()/InterfaceAddrs()
  via getifaddrs(3) (libsocket). Verified on-device — all 7 interfaces with correct
  IPs/MACs/MTU (mmx0 10.0.0.15, uap0 10.173.189.1, ecm0/1, mlan0 wifi, lo0, pflog0).
- **Result:** tailscaled now logs `link state: ifs={ecm0,ecm1,mmx0,uap0} v4=true`, brings
  WireGuard up, starts magicsock (UDP4/UDP6) + the network monitor, and the control client
  reports `HostInfo {OS:"qnx", GoArch:"arm", Userspace:true}` — state reaches NeedsLogin.
- Built the `tailscale` CLI too (12 MB): added unix.Getsid + Stat/Major/Minor/Mkdev to the
  x/sys shim, isatty_qnx (IsTerminal=false).

Remaining for a full `tailscale up` login:
- The 32-bit exec ceiling (~15 MB) means only ONE ~15 MB binary loads at a time, and
  repeatedly exec'ing them exhausts contiguous memory → the unit degrades (even a 2 MB
  binary then fails to exec) and needs a **reboot**. Deploy as a single persistent
  tailscaled; don't spawn multiple heavy binaries.
- Confirm the clock stays set (the unit may re-zero it) — set it immediately before the
  control TLS dial, or run SNTP as a periodic sync.
- Then `tailscale up` should reach controlplane.tailscale.com (bakedroots verify it) and
  print the auth URL.

Two more goroot commits: syscall Poll/ClockSettime/Getsid/getifaddrs; net interface_qnx.

## 🎉 MILESTONE 9 (2026-07) — `tailscale up` REACHES CONTROL; auth URL issued on-device
Full end-to-end on the real Audi MHI2q unit, one session:
```
SNTP: now = 2026-07-18T03:10:28Z
tailscale up -> To authenticate, visit:
	https://login.tailscale.com/a/1573566701a4f0
```
The daemon connected to controlplane.tailscale.com over TLS (baked-in roots verified the
cert against the SNTP-set clock), registered the node, and returned a real login URL.
Visiting it adds the head unit to a tailnet. **Tailscale runs on QNX 6.5 / ARMv7.**

Diagnosis correction: the unit is healthy (819 MB free, small binaries exec fine, no
leftover procs). The earlier "Not enough memory" confusion was two separate things:
(1) the real ~15 MB exec ceiling for large binaries, and (2) /tmp is /dev/shmem (volatile
RAM) which the head unit clears between sessions — binaries copied in an earlier ssh
session had simply vanished, so SNTP never ran and the clock stayed at 1970. The fix is
operational, not code: run the whole flow (SNTP -> tailscaled -> tailscale up) in ONE
session with fresh copies, keep tailscaled <=15 MB, and set the clock right before the
control dial.

Deploy sketch (single session): scp sntp_qnx + tailscaled(<=15MB) + tailscale to /tmp;
`sntp_qnx`; `tailscaled --tun=userspace-networking --statedir=<persist> --socket=/tmp/ts.sock &`;
`tailscale --socket=/tmp/ts.sock up`; open the printed URL.
