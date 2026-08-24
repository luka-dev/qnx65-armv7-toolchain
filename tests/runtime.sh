#!/bin/sh
# Run C tests ON the target and check they produce the right ANSWER, not just
# that they compile.
#
# This is the gap the other suites leave: gcc.c-torture and libstdc++ are
# compile-only here, and the bug this whole toolchain effort started from
# compiled perfectly and silently returned a wrong number. Only execution
# catches that class.
#
# All binaries go into ONE IFS with a runner script, so QEMU boots once per
# batch - 1507 separate boots would take about twelve hours.
#
#   tests/runtime.sh [variant] [batch-size] [limit]
#       variant     default 8.5
#       batch-size  tests per QEMU boot, default 200
#       limit       stop after N tests (0 = all), default 0
set -eu
HERE=$(cd "$(dirname "$0")" && pwd)
VAR=${1:-8.5}; BATCH=${2:-200}; LIMIT=${3:-0}
IMG=qnx65-armv7-toolchain:$VAR
GCC_VER=8.5.0
CACHE="$HERE/.cache"
SUITE="$CACHE/gcc-$GCC_VER/gcc/testsuite/gcc.c-torture/execute"
Q="$HERE/qemu"
[ -d "$SUITE" ] || { echo "suite missing - run tests/c-torture.sh first" >&2; exit 1; }
command -v qemu-system-arm >/dev/null || { echo "qemu-system-arm not installed" >&2; exit 1; }

WORK=$(mktemp -d)
# RUNTIME_KEEP=<dir> preserves the batch dirs (build logs, IFS, qemu output).
if [ -n "${RUNTIME_KEEP:-}" ]; then
    mkdir -p "$RUNTIME_KEEP"; WORK=$RUNTIME_KEEP; echo ">> keeping work in $WORK"
else
    trap 'rm -rf "$WORK"' EXIT
fi
# store bare names: the list is read inside the container, where the suite is
# mounted at /suite - host paths would not exist there.
(cd "$SUITE" && ls *.c) | sort > "$WORK/all.list"
[ "$LIMIT" -gt 0 ] && { head -"$LIMIT" "$WORK/all.list" > "$WORK/l"; mv "$WORK/l" "$WORK/all.list"; }
total=$(wc -l < "$WORK/all.list" | tr -d ' ')
echo ">> $total tests, batches of $BATCH, variant $VAR"

split -l "$BATCH" "$WORK/all.list" "$WORK/batch."
sum_pass=0; sum_fail=0; sum_build=0; sum_nobuild=0; nb=0
run_batch() {
    b=$1
    nb=$((nb+1)); B="$WORK/b$nb"; mkdir -p "$B"
    docker run --rm --platform=linux/amd64 -v "$SUITE":/suite:ro -v "$b":/list:ro \
        -v "$B":/out -v "$HERE/runtime-inner.sh":/inner.sh:ro -e OPT="${OPT:--O2}" \
        "$IMG" /inner.sh /list /out > "$B/build.log" 2>&1
    built=$(sed -n 's/^built=//p' "$B/build.log")
    nobuild=$(( $(wc -l < "$b" | tr -d ' ') - built ))
    for f2 in "$B"/bin/*; do [ -f "$f2" ] && basename "$f2"; done >> "$WORK/built.all" 2>/dev/null || true

    # one IFS holding every binary in the batch
    cp "$Q/startup-virt" "$Q/libstartup.a" "$Q/devc-serdebug" "$B/"
    for f in "$B"/bin/*; do [ -f "$f" ] && cp "$f" "$B/t_$(basename "$f")"; done
    {
        cat "$HERE/qemu/ifs-header.build"
        # Run the tests straight from .script rather than from a shell. ksh in
        # this minimal IFS wedges after the first child (no pipe manager, no
        # /dev/null, no job control), and procnto already prints
        # "Process N (name) exited status=X" for every one of them, which is
        # exactly the result we need.
        echo "[+script] .script = {"
        echo "    procmgr_symlink ../../proc/boot/libc.so.3 /usr/lib/ldqnx.so.2"
        echo "    devc-serdebug -e -F -S"
        echo "    waitfor /dev/ser1 4"
        echo "    reopen /dev/ser1"
        echo "    display_msg @@BATCH-START@@"
        for f in "$B"/t_*; do [ -f "$f" ] && echo "    $(basename "$f")"; done
        echo "    display_msg @@BATCH-END@@"
        echo "}"
        echo "[type=link] /usr/lib/ldqnx.so.2=/proc/boot/libc.so.3"
        echo "[perms=+r,+x]"
        echo "libc.so.3"; echo "libm.so.2"; echo "libsocket.so.3"
        echo "procnto-smp"; echo "devc-serdebug"
        for f in "$B"/t_*; do [ -f "$f" ] && basename "$f"; done
    } > "$B/test.build"

    docker run --rm --platform=linux/amd64 -v "$B":/w -w /w "$IMG" sh -c '
T=/opt/qnx650/target/qnx6/armle-v7
cp $T/lib/libc.so.3 $T/lib/libm.so.2 $T/lib/libsocket.so.3 $T/bin/ksh $T/boot/sys/procnto-smp /w/
export MKIFS_PATH=/w:$T/boot/sys:$T/bin:$T/lib:$T/usr/lib
mkifs test.build ifs.bin' > "$B/mkifs.log" 2>&1
    [ -f "$B/ifs.bin" ] || { echo "  batch $nb: mkifs failed"; tail -3 "$B/mkifs.log"; continue; }

    mkdir -p "$B/fat"; mv "$B/ifs.bin" "$B/fat/"
    ( printf '\n'; sleep 4; printf 'virtio scan\n'; sleep 2
      printf 'fatload virtio 0:1 0x40200000 ifs.bin\n'; sleep 3
      printf 'go 0x40200000\n'; sleep "${RUN_SECS:-120}" ) | \
      timeout "${RUN_TIMEOUT:-200}" qemu-system-arm -M virt -m 1024 -cpu cortex-a15 \
        -bios "$Q/u-boot.bin" -drive file=fat:rw:"$B/fat",format=raw,media=disk \
        -display none -serial stdio > "$B/qemu.log" 2>&1 || true

    if ! grep -q '@@BATCH-START@@' "$B/qemu.log"; then
        echo "  batch $nb: never booted"; continue
    fi
    # "Process 7 (t_foo) exited status=0." - one line per test, from procnto.
    sed -n 's/.*Process [0-9]* (t_\([^)]*\)) exited status=\([0-9]*\).*/\1 \2/p' \
        "$B/qemu.log" | sort -u > "$B/results.txt"
    # A crashing test prints "terminated SIGSEGV" and no exit status at all.
    # Without this it would land in "never reported" together with tests that
    # merely ran out of time - two very different things.
    sed -n 's/.*Process [0-9]* (t_\([^)]*\)) terminated \(SIG[A-Z]*\).*/\1 \2/p' \
        "$B/qemu.log" | sort -u > "$B/crashes.txt"
    cut -d' ' -f1 "$B/crashes.txt" >> "$WORK/crashed.txt" || true
    awk '$2==0{print $1}' "$B/results.txt" >> "$WORK/ok.all"
    p=$(awk '$2==0' "$B/results.txt" | wc -l | tr -d ' ')
    f=$(awk '$2!=0' "$B/results.txt" | wc -l | tr -d ' ')
    # A binary that was built but never reported an exit status either hung or
    # the batch ran out of time. Silence here would look like success.
    for f2 in "$B"/t_*; do [ -f "$f2" ] && basename "$f2" | sed 's/^t_//'; done | sort > "$B/expected.txt"
    cat "$B/results.txt" "$B/crashes.txt" | cut -d' ' -f1 | sort -u > "$B/got.txt"
    comm -23 "$B/expected.txt" "$B/got.txt" >> "$WORK/noreport.txt" || true
    awk '$2!=0{print $1}' "$B/results.txt" >> "$WORK/failures.txt" || true
    if ! grep -q '@@BATCH-END@@' "$B/qemu.log"; then
        # A test that dies takes .script down with it, so everything after it
        # never runs - which is why the missing names come in an alphabetical
        # block rather than scattered. The first unreported test IS the culprit;
        # record it as a crash and re-run the rest.
        first_missing=$(comm -23 "$B/expected.txt" "$B/got.txt" | head -1)
        if [ -n "$first_missing" ]; then
            echo "$first_missing" >> "$WORK/crashed.txt"
            echo "  batch $nb: stopped at $first_missing (crashed) - requeueing the rest"
            comm -23 "$B/expected.txt" "$B/got.txt" | tail -n +2 | sed 's/$/.c/' > "$WORK/requeue.$nb"
        else
            echo "  batch $nb: INCOMPLETE - ran $((p+f)) of $built, no culprit identified"
        fi
    fi
    sum_pass=$((sum_pass+p)); sum_fail=$((sum_fail+f))
    echo "  batch $nb: built $built/$((built+nobuild))  ran pass=$p fail=$f"
}

for b in "$WORK"/batch.*; do run_batch "$b"; done
rm -f "$WORK"/batch.*

# Re-run whatever a crash cut short, repeatedly - each pass can uncover the next
# crasher. Bounded so a pathological suite cannot loop forever.
round=0
while ls "$WORK"/requeue.* >/dev/null 2>&1 && [ $round -lt 12 ]; do
    round=$((round+1))
    cat "$WORK"/requeue.* | sort -u > "$WORK/rq.list"; rm -f "$WORK"/requeue.*
    n=$(wc -l < "$WORK/rq.list" | tr -d ' ')
    [ "$n" -eq 0 ] && break
    echo ">> requeue round $round: $n tests left after a crash"
    split -l "$BATCH" "$WORK/rq.list" "$WORK/batch."
    for b in "$WORK"/batch.*; do run_batch "$b"; done
    rm -f "$WORK"/batch.*
done

# Resolve the sets once, so requeued tests are not counted twice and anything
# that eventually ran is no longer listed as missing.
sort -u "$WORK/built.all" 2>/dev/null > "$WORK/built.u" || : > "$WORK/built.u"
sort -u "$WORK/ok.all"    2>/dev/null > "$WORK/ok.u"    || : > "$WORK/ok.u"
sort -u "$WORK/crashed.txt" 2>/dev/null > "$WORK/crashed.u" || : > "$WORK/crashed.u"
sort -u "$WORK/failures.txt" 2>/dev/null > "$WORK/bad.u" || : > "$WORK/bad.u"
sort -u "$WORK/ok.u" "$WORK/crashed.u" "$WORK/bad.u" > "$WORK/accounted.u"
comm -23 "$WORK/built.u" "$WORK/accounted.u" > "$WORK/missing.u"

echo "=================================================="
echo "compiled : $(wc -l < "$WORK/built.u" | tr -d ' ') (could not build: $((total - $(wc -l < "$WORK/built.u" | tr -d ' '))))"
echo "ran ok   : $(wc -l < "$WORK/ok.u" | tr -d ' ')"
echo "wrong    : $(wc -l < "$WORK/bad.u" | tr -d ' ')"
echo "crashed  : $(wc -l < "$WORK/crashed.u" | tr -d ' ')"
echo "no result: $(wc -l < "$WORK/missing.u" | tr -d ' ')"
echo "=================================================="
[ -f "$WORK/crashed.txt" ] && { echo "--- crashed (took the batch down with them) ---"
    sort -u "$WORK/crashed.txt" | tr '\n' ' ' | fold -s -w 100; echo; }
[ -f "$WORK/failures.txt" ] && { echo "--- ran but returned nonzero ---"; sort "$WORK/failures.txt" | head -40; }
if [ -s "$WORK/missing.u" ]; then
    echo "--- no result at all (hung, or never reached) ---"
    tr '\n' ' ' < "$WORK/missing.u" | fold -s -w 100; echo
    cp "$WORK/missing.u" "${NOREPORT_OUT:-/tmp/noreport.txt}"
fi
