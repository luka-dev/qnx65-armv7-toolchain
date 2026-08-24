# Historical stock QNX 6.5 GCC 4.4.2 reference

Stock QNX 6.5 GCC 4.4.2 is a reference-only baseline. Its proprietary host
binaries, qcc profiles, and QNX license are not distributed. It is not an image
variant and cannot be rebuilt from this tree.

The supported compiler variants are GCC 4.9.4 and GCC 8.5.0. The bundled
`tools/qcc/bin/qcc` is a compatibility shim and is not the stock QNX driver.

## Provenance fingerprints

These hashes identify the exact binaries used for the comparison; the binaries
themselves are not part of the repository.

| component | size | SHA-256 |
|---|---:|---|
| QNX 6.5 stock `qcc` (Linux i386 host binary) | 1,084,664 bytes | `bca50b50b02ef251f924ddc8ff88a9e6fb3fc8e35bcf2958123d35e5463c86fc` |
| `arm-unknown-nto-qnx6.5.0eabi-gcc-4.4.2` | 196,600 bytes | `6bdfa7ca5f7e33c9a848892252269253cea8ac74865e8a01df3c7f990cd86235` |
| stock `ntoarm-as-2.19` | 964,870 bytes | `a9ae74a45e77e83f9e390bf6edc9b1323a9e279f4447a4b72455769c72203faf` |

## Recorded comparison

The compiler was run against the same GCC 8.5.0 `gcc.c-torture/execute`
sources used for the maintained variants, at `-O2 -w -lm`:

- compiled and linked: **1458/1507**;
- expected compile failures: **49**;
- runtime suite: not run;
- Go/Rust: not supported as image variants.

The exact expected-failure names are preserved in
`stock-gcc-4.4.2-c-torture.fails` beside this file. They are historical data,
not an active regression baseline.

The stock driver also established two behaviors used when validating the qcc
shim:

- qcc profiles select C versus C++ and translate QNX-specific driver options;
- the stock GCC 4.4.2 driver prints an `unrecognized option` warning for
  `-pthread` and `-rdynamic`, ignores the option, and exits successfully. Go
  treats that stderr output as a compiler failure.

The maintained shim's supported translation table is documented in
`tools/README.md` and in the script itself. Re-running a comparison against the
proprietary driver requires an externally supplied, properly licensed QNX 6.5
SDP.
