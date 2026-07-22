// Copyright 2026 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

//go:build qnx

// QNX 6.5 / ARM: poll(2) and a few extra socket/fd wrappers that golang.org/x/
// sys/unix expects but the standard syscall package doesn't expose elsewhere.

package syscall

import "unsafe"

//go:cgo_import_dynamic libc_poll poll "libc.so.3"
//go:cgo_import_dynamic libc_clock_settime clock_settime "libc.so.3"
//go:linkname libc_poll libc_poll
//go:linkname libc_clock_settime libc_clock_settime

var (
	libc_poll          libcFunc
	libc_clock_settime libcFunc
)

const CLOCK_REALTIME = 0

// ClockSettime sets the given clock (CLOCK_REALTIME=0). Requires privilege.
func ClockSettime(clockid int32, ts *Timespec) error {
	_, _, e := sysvicall6(fnptr(&libc_clock_settime), 2, uintptr(clockid), uintptr(unsafe.Pointer(ts)), 0, 0, 0, 0)
	if e != 0 {
		return e
	}
	return nil
}

// ---- interface enumeration (getifaddrs, in libsocket) ----

//go:cgo_import_dynamic libc_getifaddrs getifaddrs "libsocket.so.3"
//go:cgo_import_dynamic libc_freeifaddrs freeifaddrs "libsocket.so.3"
//go:cgo_import_dynamic libc_if_nametoindex if_nametoindex "libsocket.so.3"
//go:linkname libc_getifaddrs libc_getifaddrs
//go:linkname libc_freeifaddrs libc_freeifaddrs
//go:linkname libc_if_nametoindex libc_if_nametoindex

var (
	libc_getifaddrs     libcFunc
	libc_freeifaddrs    libcFunc
	libc_if_nametoindex libcFunc
)

// Ifaddrs mirrors struct ifaddrs (QNX 6.5, 32-bit).
type Ifaddrs struct {
	Next    *Ifaddrs
	Name    *byte
	Flags   uint32
	Addr    *RawSockaddr
	Netmask *RawSockaddr
	Dstaddr *RawSockaddr
	Data    unsafe.Pointer
}

// AF_LINK and interface flag values (QNX net/if.h).
const (
	AF_LINK         = 18
	IFF_UP          = 0x1
	IFF_BROADCAST   = 0x2
	IFF_LOOPBACK    = 0x8
	IFF_POINTOPOINT = 0x10
	IFF_RUNNING     = 0x40
	IFF_MULTICAST   = 0x8000
)

// RawSockaddrDatalink mirrors struct sockaddr_dl (AF_LINK).
type RawSockaddrDatalink struct {
	Len    uint8
	Family uint8
	Index  uint16
	Type   uint8
	Nlen   uint8
	Alen   uint8
	Slen   uint8
	Data   [12]int8
}

// Getifaddrs returns the head of the interface address list. Free it with
// Freeifaddrs.
func Getifaddrs() (head *Ifaddrs, err error) {
	r1, _, e := sysvicall6(fnptr(&libc_getifaddrs), 1, uintptr(unsafe.Pointer(&head)), 0, 0, 0, 0, 0)
	if int32(r1) != 0 {
		return nil, e
	}
	return head, nil
}

func Freeifaddrs(head *Ifaddrs) {
	sysvicall6(fnptr(&libc_freeifaddrs), 1, uintptr(unsafe.Pointer(head)), 0, 0, 0, 0, 0)
}

func IfNametoindex(name string) int {
	p, err := BytePtrFromString(name)
	if err != nil {
		return 0
	}
	r1, _, _ := sysvicall6(fnptr(&libc_if_nametoindex), 1, uintptr(unsafe.Pointer(p)), 0, 0, 0, 0, 0)
	return int(r1)
}

// PollFd matches struct pollfd (QNX sys/poll.h): int fd; short events; short revents.
type PollFd struct {
	Fd      int32
	Events  int16
	Revents int16
}

const (
	POLLIN     = 0x0001 | 0x0004 // POLLRDNORM | POLLRDBAND
	POLLPRI    = 0x0008
	POLLOUT    = 0x0002
	POLLERR    = 0x0020
	POLLHUP    = 0x0040
	POLLNVAL   = 0x1000
	POLLRDNORM = 0x0001
	POLLRDBAND = 0x0004
	POLLWRNORM = 0x0002
	POLLWRBAND = 0x0010
)

// Poll waits for events on the given descriptors. timeout is in milliseconds.
func Poll(fds []PollFd, timeout int) (n int, err error) {
	var p unsafe.Pointer
	if len(fds) > 0 {
		p = unsafe.Pointer(&fds[0])
	}
	r1, _, e := sysvicall6(fnptr(&libc_poll), 3, uintptr(p), uintptr(len(fds)), uintptr(timeout), 0, 0, 0)
	n = int(r1)
	if e != 0 {
		err = e
	}
	return
}
