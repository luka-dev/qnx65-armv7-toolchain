# Drop-in toolchains

Anything you put here shows up on `PATH` inside the container. One folder per
toolchain, each with a `bin/` subdir - that's the only rule.

```
tools/
  go/        -> /opt/tools/go/bin    (go, gofmt)
  rust/      -> /opt/tools/rust/bin  (rustc, cargo)
  gcc13/     -> /opt/tools/gcc13/bin (gcc, g++)
```

Add one: unpack a **linux/amd64** release into a subdir here.

```sh
# Go
curl -sL https://go.dev/dl/go1.22.5.linux-amd64.tar.gz | tar xz -C tools/   # makes tools/go/

# Rust (standalone, no rustup)
curl -sL https://static.rust-lang.org/dist/rust-1.79.0-x86_64-unknown-linux-gnu.tar.gz | tar xz
mv rust-1.79.0-*/  tools/rust/       # its bin/ has rustc+cargo
```

Remove one: delete its folder. No archive to rebuild.

## Two ways to use them

Bake into the image (self-contained, rebuild on change):

    docker build --platform=linux/amd64 -t qnx65-armv7 .

Or mount at runtime (no rebuild - add/remove folders and just re-run):

    docker run --rm -it --platform=linux/amd64 \
        -v "$PWD/tools":/opt/tools -v "$PWD":/src qnx65-armv7 bash

Binaries must be `linux/amd64` (the image runs under amd64, emulated on Apple Silicon).
