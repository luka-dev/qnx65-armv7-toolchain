#!/bin/sh
# Prepend every /opt/tools/*/bin to PATH so any toolchain dropped into
# /opt/tools (newer gcc, go, rust, ...) is found. Runs at container start,
# so it picks up both baked-in COPYs and runtime `-v host/tools:/opt/tools`.
for d in /opt/tools/*/bin; do
    [ -d "$d" ] && PATH="$d:$PATH"
done
export PATH
[ "$#" -eq 0 ] && exec bash
exec "$@"
