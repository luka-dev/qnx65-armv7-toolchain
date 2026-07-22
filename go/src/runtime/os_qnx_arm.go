// Copyright 2026 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

//go:build qnx && arm

package runtime

func checkgoarm() {
	// osinit not called yet, so numCPUStartup is not set: use getCPUCount directly.
	if getCPUCount() > 1 && goarm < 7 {
		print("runtime: this system has multiple CPUs and must use\n")
		print("atomic synchronization instructions. Recompile using GOARM=7.\n")
		exit(1)
	}
}
