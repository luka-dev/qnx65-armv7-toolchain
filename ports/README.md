# ports/ — cross-compiled dependencies for QNX 6.5 armle-v7

A small ports tree for libraries that apps (nano, mc, …) need but the QNX 6.5
SDP sysroot doesn't provide. Each dep is a folder with a pristine upstream
tarball (or authored source, for stubs) + a `build.sh`. Everything installs into
the shared staging prefix **`sysroot/`** (`sysroot/include`, `sysroot/lib`), which
acts as an overlay on top of `/opt/qnx650` — apps build with
`-I ports/sysroot/include -L ports/sysroot/lib`.

Apps themselves live in their own `Tools/<app>-qnx/` dir (not here) and link
against this sysroot.

## How to (re)build

Run from this `ports/` dir, mounted at `/ports`:

```sh
docker run --rm --platform=linux/amd64 -v "$PWD":/ports -w /ports \
    qnx65-armv7-toolchain sh /ports/<dep>/build.sh [version]
```

Build order matters (later deps use earlier ones):

1. `libiconv/`      — GNU libiconv 1.14 (QNX libc has no iconv())
2. `libintl-stub/`  — no-op gettext (QNX libc has no gettext); authored here
3. `langinfo-stub/` — nl_langinfo(CODESET) → UTF-8 (no <langinfo.h> on QNX)
4. `mntent-stub/`   — empty getmntent (QNX can't enumerate mounts)
5. `glib/`          — glib 2.40.2, core + gmodule only (no gobject/gio → no libffi)

Steps 2–4 are tiny stubs we wrote: QNX genuinely lacks these APIs, and the
consumers (glib, mc) only need them to link when built with NLS off. They are
real ports — source we author — not configure wrappers.

## Toolchain gotchas (apply to every port)

- **`-include stddef.h`** in CFLAGS — QNX Dinkum headers don't pull `<stddef.h>`
  transitively, so `size_t` goes missing. Do NOT `-D__SIZE_T` (it suppresses
  GCC's own size_t definition).
- **Build in the container FS**, never on the bind mount — conftest races under
  amd64 emulation on Apple Silicon. `make install` to a mounted prefix is fine.
- **`-lsocket`** for res_query / networking symbols (not in libc).
