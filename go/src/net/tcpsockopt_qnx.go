// Copyright 2026 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// QNX 6.5 exposes only TCP_KEEPALIVE (idle seconds before probing); it has no
// separate probe-interval or probe-count knobs. So setKeepAliveIdle maps to
// TCP_KEEPALIVE and the interval/count setters are accepted but no-ops.
// ponytail: interval/count unsupported by the kernel; upgrade if QNX ever adds
// TCP_KEEPINTVL/TCP_KEEPCNT.

package net

import (
	"runtime"
	"syscall"
	"time"
)

func setKeepAliveIdle(fd *netFD, d time.Duration) error {
	if d == 0 {
		d = defaultTCPKeepAliveIdle
	} else if d < 0 {
		return nil
	}
	secs := int(roundDurationUp(d, time.Second))
	err := fd.pfd.SetsockoptInt(syscall.IPPROTO_TCP, syscall.TCP_KEEPALIVE, secs)
	runtime.KeepAlive(fd)
	return wrapSyscallError("setsockopt", err)
}

func setKeepAliveInterval(fd *netFD, d time.Duration) error {
	// No probe-interval control on QNX 6.5. Accept d>=0 silently; reject only
	// obviously bad callers is unnecessary — the net API treats this as best
	// effort.
	runtime.KeepAlive(fd)
	return nil
}

func setKeepAliveCount(fd *netFD, n int) error {
	// No probe-count control on QNX 6.5.
	runtime.KeepAlive(fd)
	return nil
}
