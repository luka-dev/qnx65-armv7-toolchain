#!/usr/bin/env bash
# Re-apply the QNX-6.5 std-port deltas that live OUTSIDE this repo (the nightly
# toolchain's vendored libc registry copy + rustlib std source). Idempotent:
# safe to run repeatedly. Needed once per machine / after a toolchain update.
#
# Deltas kept in-repo as source of truth:
#   vendor/libc/src/unix/nto/arm.rs   (new: 32-bit ARM nto arch module)
#   vendor/libc/src/unix/nto/mod.rs   (arm arch wired in + regex not linked on nto65)
# Std source patches (time_t is u32 on 6.5 armv7, std assumes i64) applied below.
set -euo pipefail
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
# In-image these point at /opt/{cargo,rustup}; on a dev box they default to $HOME.
CARGO="${CARGO_HOME:-$HOME/.cargo}"
RUSTUP="${RUSTUP_HOME:-$HOME/.rustup}"

# --- 1) libc: sync our nto fork into the registry copy build-std actually reads
REG=$(find "$CARGO/registry/src" -maxdepth 2 -type d -name 'libc-0.2.185' 2>/dev/null | head -1 || true)
if [ -z "$REG" ]; then
  # Self-seed. A consumer pointing CARGO_HOME at a fresh directory (project-
  # local caches do this) starts with an empty registry; without seeding, the
  # first build compiles pristine crates.io libc and fails 30 ways on time_t.
  # Prefer the .crate tarball already in this CARGO_HOME's cache; fall back to
  # the image's baked (already patched) registry copy.
  crate=$(find "$CARGO/registry/cache" -maxdepth 2 -name 'libc-0.2.185.crate' 2>/dev/null | head -1 || true)
  if [ -n "$crate" ]; then
    dest="$CARGO/registry/src/$(basename "$(dirname "$crate")")"
    mkdir -p "$dest"
    tar -xzf "$crate" -C "$dest"
    printf '{"v":1}' > "$dest/libc-0.2.185/.cargo-ok"
    REG="$dest/libc-0.2.185"
    echo "libc-0.2.185 seeded from $crate"
  else
    baked=$(find /opt/cargo/registry/src -maxdepth 2 -type d -name 'libc-0.2.185' 2>/dev/null | head -1 || true)
    if [ -n "$baked" ] && [ "$CARGO" != "/opt/cargo" ]; then
      dest="$CARGO/registry/src/$(basename "$(dirname "$baked")")"
      mkdir -p "$dest"
      cp -R "$baked" "$dest/"
      REG="$dest/libc-0.2.185"
      echo "libc-0.2.185 seeded from image registry ($baked)"
    fi
  fi
fi
[ -n "$REG" ] || { echo "libc-0.2.185 not in cargo registry and nothing to seed from; run a build once first"; exit 1; }
cp "$HERE/vendor/libc/src/unix/nto/arm.rs" "$REG/src/unix/nto/arm.rs"
cp "$HERE/vendor/libc/src/unix/nto/mod.rs" "$REG/src/unix/nto/mod.rs"
echo "libc nto fork -> $REG"

# --- 2) std source: 32-bit time_t fixes (idempotent perl, guarded on marker)
# Patch the ACTIVE toolchain's std src (rustc respects rust-toolchain.toml), not
# a random `find` hit - the image may hold more than one nightly, and build-std
# reads the one selected here.
STD="$(rustc --print sysroot)/lib/rustlib/src/rust/library/std/src/sys"
[ -d "$STD" ] || { echo "rustlib std src not found at $STD (need rust-src component)"; exit 1; }

# time.rs: TIMESPEC_MAX_CAPPED uses `as i64` -> width-agnostic `as _`
perl -0pi -e 's/(tv_sec: \(u64::MAX \/ NSEC_PER_SEC\) as )i64/$1_/;
              s/(tv_nsec: \(u64::MAX % NSEC_PER_SEC\) as )i64/$1_/' \
  "$STD/pal/unix/time.rs"

# fs/unix.rs: QNX 6.5's struct stat has NO st_*tim timespec - only the 32-bit
# st_*time fields, which our libc binding exposes as __old_st_*time (those are
# the real, libc-filled fields; the binding's st_*tim timespec sits PAST the end
# of the 6.5 struct, so fstat never writes it and reading st_*tim.tv_sec yields
# zero/garbage - wrong file timestamps). The upstream nto block reads
# st_*tim.tv_sec/.tv_nsec, so redirect those reads to the real __old_st_*time
# fields (nsec = 0; 6.5 file times have no sub-second precision).
perl -0pi -e 's/self\.stat\.st_mtim\.tv_sec/self.stat.__old_st_mtime as i64/g;
              s/self\.stat\.st_atim\.tv_sec/self.stat.__old_st_atime as i64/g;
              s/self\.stat\.st_ctim\.tv_sec/self.stat.__old_st_ctime as i64/g;
              s/self\.stat\.st_mtim\.tv_nsec/0/g;
              s/self\.stat\.st_atim\.tv_nsec/0/g;
              s/self\.stat\.st_ctim\.tv_nsec/0/g' \
  "$STD/fs/unix.rs"

# random: QNX /dev/random EAGAINs before its pool is primed + no /dev/urandom;
# replace fill_bytes with a WouldBlock-retrying version (stored copy is source of truth).
cp "$HERE/port/patches/std_random_unix_legacy.rs" "$STD/random/unix_legacy.rs"

# current_exe: QNX 6.5 has no /proc/self/exefile; use libc _cmdname (reads the
# AT_EXEFILE auxv - works on 6.5 and 7.x). (stored copy is source of truth.)
cp "$HERE/port/patches/std_paths_unix.rs" "$STD/paths/unix.rs"

echo "std time_t + random + current_exe patches -> $STD"
echo "done. now: ./build_std.sh <crate-dir>"
