// Copyright 2026 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// QNX 6.5 has no epoll/kqueue and no integrated event port, so the network
// poller is built on poll(2) — the same design the AIX port uses. A self-pipe
// wakes poll() for arming changes and netpollBreak.

package runtime

import (
	"internal/runtime/atomic"
	"unsafe"
)

//go:nosplit
func poll(pfds *pollfd, npfds uintptr, timeout uintptr) (int32, int32) {
	r, err := sysvicall3Err(&libc_poll, uintptr(unsafe.Pointer(pfds)), npfds, timeout)
	return int32(r), int32(err)
}

// struct pollfd (QNX sys/poll.h): int fd; short events; short revents.
type pollfd struct {
	fd      int32
	events  int16
	revents int16
}

// QNX poll event bits (sys/poll.h). POLLIN = POLLRDNORM | POLLRDBAND.
const (
	_POLLIN  = 0x0001 | 0x0004
	_POLLOUT = 0x0002
	_POLLERR = 0x0020
	_POLLHUP = 0x0040
)

var (
	pfds           []pollfd
	pds            []*pollDesc
	mtxpoll        mutex
	mtxset         mutex
	rdwake         int32
	wrwake         int32
	pendingUpdates int32

	netpollWakeSig atomic.Uint32 // avoids duplicate netpollBreak wakeups
)

func netpollinit() {
	// The wake mechanism is a self-pipe. QNX implements pipe() via a separate
	// "pipe" resource manager, which is not guaranteed to be running on a
	// minimal image. If it is absent, degrade gracefully: use a negative wake
	// fd (poll(2) ignores fds < 0) and a capped poll timeout so timers and
	// netpollBreak still take effect within pollNoWakeCapMs.
	// ponytail: capped-timeout fallback; a native pulse/ionotify wake would
	// remove the latency ceiling.
	r, w, errno := nonblockingPipe()
	if errno != 0 {
		rdwake = -1
		wrwake = -1
	} else {
		rdwake = r
		wrwake = w
	}

	pfds = make([]pollfd, 1, 128)
	pfds[0].fd = rdwake // -1 when no pipe: poll() ignores it
	pfds[0].events = _POLLIN

	pds = make([]*pollDesc, 1, 128)
	pds[0] = nil
}

// pollNoWakeCapMs bounds how long netpoll blocks when there is no wake pipe,
// so netpollBreak and new timers are noticed within this window.
const pollNoWakeCapMs = 10

func netpollIsPollDescriptor(fd uintptr) bool {
	return fd == uintptr(rdwake) || fd == uintptr(wrwake)
}

// netpollwakeup writes on wrwake to wake poll before any changes.
func netpollwakeup() {
	if wrwake < 0 {
		return // no wake pipe; netpoll uses a capped timeout instead
	}
	if pendingUpdates == 0 {
		pendingUpdates = 1
		b := [1]byte{0}
		write(uintptr(wrwake), unsafe.Pointer(&b[0]), 1)
	}
}

func netpollopen(fd uintptr, pd *pollDesc) int32 {
	lock(&mtxpoll)
	netpollwakeup()

	lock(&mtxset)
	unlock(&mtxpoll)

	pd.user = uint32(len(pfds))
	pfds = append(pfds, pollfd{fd: int32(fd)})
	pds = append(pds, pd)
	unlock(&mtxset)
	return 0
}

func netpollclose(fd uintptr) int32 {
	lock(&mtxpoll)
	netpollwakeup()

	lock(&mtxset)
	unlock(&mtxpoll)

	for i := 0; i < len(pfds); i++ {
		if pfds[i].fd == int32(fd) {
			pfds[i] = pfds[len(pfds)-1]
			pfds = pfds[:len(pfds)-1]

			pds[i] = pds[len(pds)-1]
			pds[i].user = uint32(i)
			pds = pds[:len(pds)-1]
			break
		}
	}
	unlock(&mtxset)
	return 0
}

func netpollarm(pd *pollDesc, mode int) {
	lock(&mtxpoll)
	netpollwakeup()

	lock(&mtxset)
	unlock(&mtxpoll)

	switch mode {
	case 'r':
		pfds[pd.user].events |= _POLLIN
	case 'w':
		pfds[pd.user].events |= _POLLOUT
	}
	unlock(&mtxset)
}

// netpollBreak interrupts a poll.
func netpollBreak() {
	if wrwake < 0 {
		return // capped-timeout fallback notices the break on its own
	}
	if !netpollWakeSig.CompareAndSwap(0, 1) {
		return
	}
	b := [1]byte{0}
	write(uintptr(wrwake), unsafe.Pointer(&b[0]), 1)
}

// netpoll checks for ready network connections.
//
// delay < 0: blocks indefinitely
// delay == 0: does not block, just polls
// delay > 0: block for up to that many nanoseconds
//
//go:nowritebarrierrec
func netpoll(delay int64) (gList, int32) {
	var timeout uintptr
	if delay < 0 {
		timeout = ^uintptr(0)
	} else if delay == 0 {
		return gList{}, 0
	} else if delay < 1e6 {
		timeout = 1
	} else if delay < 1e15 {
		timeout = uintptr(delay / 1e6)
	} else {
		timeout = 1e9
	}
	// Without a wake pipe, never block longer than pollNoWakeCapMs so timers
	// and netpollBreak are noticed promptly.
	if wrwake < 0 && (timeout == ^uintptr(0) || timeout > pollNoWakeCapMs) {
		timeout = pollNoWakeCapMs
	}
retry:
	lock(&mtxpoll)
	lock(&mtxset)
	pendingUpdates = 0
	unlock(&mtxpoll)

	n, e := poll(&pfds[0], uintptr(len(pfds)), timeout)
	if n < 0 {
		if e != _EINTR {
			println("errno=", e, " len(pfds)=", len(pfds))
			throw("poll failed")
		}
		unlock(&mtxset)
		if timeout > 0 {
			return gList{}, 0
		}
		goto retry
	}
	if n != 0 && pfds[0].revents&(_POLLIN|_POLLHUP|_POLLERR) != 0 {
		if delay != 0 {
			var b [1]byte
			for read(rdwake, unsafe.Pointer(&b[0]), 1) == 1 {
			}
			netpollWakeSig.Store(0)
		}
		n--
	}
	var toRun gList
	delta := int32(0)
	for i := 1; i < len(pfds) && n > 0; i++ {
		pfd := &pfds[i]

		var mode int32
		if pfd.revents&(_POLLIN|_POLLHUP|_POLLERR) != 0 {
			mode += 'r'
			pfd.events &= ^int16(_POLLIN)
		}
		if pfd.revents&(_POLLOUT|_POLLHUP|_POLLERR) != 0 {
			mode += 'w'
			pfd.events &= ^int16(_POLLOUT)
		}
		if mode != 0 {
			pds[i].setEventErr(pfd.revents == _POLLERR, 0)
			delta += netpollready(&toRun, pds[i], mode)
			n--
		}
	}
	unlock(&mtxset)
	return toRun, delta
}
