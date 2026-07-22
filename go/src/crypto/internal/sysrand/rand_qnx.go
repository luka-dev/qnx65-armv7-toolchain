// Copyright 2026 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// QNX 6.5 has no getrandom syscall; entropy comes from the "random" service's
// /dev/urandom (or /dev/random). ponytail: requires the random resource manager
// to be running on the target image.

package sysrand

func read(b []byte) error {
	return urandomRead(b)
}
