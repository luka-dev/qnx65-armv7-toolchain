// Copyright 2026 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// On QNX the .noptrbss scratch buffer used by the FIPS 140-3 jitter entropy
// source (32 MiB) is committed by procnto at exec time rather than demand-paged,
// which makes large binaries fail to load. FIPS 140-3 mode is off by default and
// getEntropy is only reached when it is explicitly enabled, so exclude the static
// buffer here (mirrors the Wasm handling).

//go:build qnx

package drbg

func getEntropy() *[SeedSize]byte {
	panic("FIPS 140-3 entropy generation is not supported on QNX")
}
