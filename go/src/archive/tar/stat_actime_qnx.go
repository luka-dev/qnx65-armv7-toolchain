// Copyright 2026 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// QNX 6.5 struct stat carries st_atime/st_ctime as 32-bit time_t seconds
// (no nanosecond timespec), so read them directly.

package tar

import (
	"syscall"
	"time"
)

func statAtime(st *syscall.Stat_t) time.Time {
	return time.Unix(int64(st.Atim), 0)
}

func statCtime(st *syscall.Stat_t) time.Time {
	return time.Unix(int64(st.Ctim), 0)
}
