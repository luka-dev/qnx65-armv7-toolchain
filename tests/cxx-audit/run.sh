#!/usr/bin/env bash
# Audit installed headers/runtime, without patching the image or sysroot.
# Known broken images are expected to return nonzero. Logs survive in .cache.
set -euo pipefail
root=$(cd "$(dirname "$0")/../.." && pwd)
cd "$root"
image=${QNX_AUDIT_IMAGE:-qnx65-armv7-toolchain:latest}
out=${QNX_AUDIT_OUT:-tests/.cache/cxx-audit}
variant=${QNX_AUDIT_GUEST_VARIANT:-8.5}
mkdir -p "$out"
out=$(cd "$out" && pwd)
docker image inspect "$image" --format '{{.Id}} {{.Created}}' > "$out/image.txt"
python3 tests/cxx-audit/generate-math.py "$out/math-generated.cpp"
docker run --rm --platform=linux/amd64 \
    -v "$root":/src -v "$out":/out -w /src "$image" sh -eu -c '
    p=arm-unknown-nto-qnx6.5.0eabi
    $p-g++ --version > /out/compiler.txt
    python3 tests/cxx-audit/compile-probes.py /out/headers > /out/headers.log
    $p-g++ -std=c++17 -O2 -fno-exceptions -fno-rtti -Itests/cxx-audit \
        -c /out/math-generated.cpp -o /out/math.o
    $p-gcc /out/math.o -lm -o /out/math-audit
    $p-objdump -drC /out/math.o > /out/math-arm.txt
    $p-g++ -std=c++17 -O2 tests/cxx-audit/runtime.cpp \
        -static-libstdc++ -static-libgcc -lm -o /out/runtime-raw
    $p-g++ -std=c++17 -O2 tests/cxx-audit/runtime.cpp \
        -static-libgcc -lm -o /out/runtime-shared
    $p-g++ -std=c++17 -O2 -D_GTHREAD_USE_MUTEX_INIT_FUNC tests/cxx-audit/runtime.cpp \
        -static-libstdc++ -static-libgcc -lm -o /out/runtime-init
    $p-g++ -std=c++17 -O2 tests/cxx-audit/clock.cpp \
        -static-libstdc++ -static-libgcc -o /out/clock-audit
    $p-objdump -dC /out/clock-audit > /out/clock-arm.txt
' > "$out/build.log" 2>&1 || { cat "$out/build.log"; exit 2; }

cat "$out/headers.log"
failed=0
python3 - "$out/headers/results.json" <<'PY' || failed=1
import json, sys
sys.exit(any(not row['ok'] for row in json.load(open(sys.argv[1]))))
PY
if [[ ${QNX_AUDIT_RUN_QEMU:-1} == 1 ]]; then
    for name in math-audit runtime-raw runtime-shared runtime-init clock-audit; do
        if QEMU_RUN_SECS=12 QEMU_TIMEOUT=26 QEMU_KEEP_LOG="$out/$name-qemu.log" \
            bash tests/qemu-run.sh "$out/$name" "$variant" > "$out/$name.log" 2>&1; then
            echo "PASS $name"
        else
            echo "FAIL $name (see $out/$name.log)"
            failed=1
        fi
        tail -6 "$out/$name.log"
    done
else
    echo "QNX runtime execution skipped (QNX_AUDIT_RUN_QEMU=0)"
fi
echo "Artifacts: $out"
exit "$failed"
