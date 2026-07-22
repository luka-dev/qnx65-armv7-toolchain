// Copyright 2026 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package x509

// Possible certificate files; stop after finding one. QNX has no standard
// system trust store, so we probe the common OpenSSL locations a target image
// is likely to ship. Callers can override with SSL_CERT_FILE / SSL_CERT_DIR.
// ponytail: bundle a cacert.pem with the app if the head unit has none.
var certFiles = []string{
	"/etc/ssl/certs/ca-certificates.crt",
	"/etc/ssl/cert.pem",
	"/etc/ssl/cacert.pem",
	"/system/etc/ssl/certs/ca-certificates.crt",
}

// Possible directories with certificate files; all will be read.
var certDirectories = []string{
	"/etc/ssl/certs",
}
