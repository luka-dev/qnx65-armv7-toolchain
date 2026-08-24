#!/bin/sh
# Runs INSIDE the container. Compiles a batch of C tests, builds ONE IFS holding
# all of them plus a runner script, so QEMU boots once for the whole batch
# instead of once per test (1507 separate boots would be ~12 hours).
#   $1 = file listing test source paths, $2 = output dir
set -u
LIST=$1; OUT=$2
CC=arm-unknown-nto-qnx6.5.0eabi-gcc
mkdir -p "$OUT/bin"
built=0; failed_build=""
while read -r name; do
    n=${name%.c}
    f=/suite/$name
    if $CC ${OPT:--O2} -w "$f" -o "$OUT/bin/$n" -lm >/dev/null 2>&1; then
        built=$((built+1))
    else
        failed_build="$failed_build $n"
    fi
done < "$LIST"
echo "built=$built"
[ -n "$failed_build" ] && { echo "BUILDFAIL$failed_build" ; }

# The in-target runner: execute each binary, report its exit status. QNX's sh
# is ksh; keep it to plain POSIX so it behaves the same.
{
    echo '#!/proc/boot/ksh'
    echo 'pass=0; fail=0'
    # plain glob, NOT $(ls ...): command substitution needs a pipe, and the
    # pipe manager is not running in this minimal IFS ("can't create pipe").
    echo 'for t in /proc/boot/t_*; do'
    # no >/dev/null: this minimal IFS has no /dev/null. c-torture tests are
    # silent anyway - what matters is the exit status.
    echo '  $t'
    echo '  if [ $? -eq 0 ]; then pass=$((pass+1)); else fail=$((fail+1)); echo "FAIL ${t#/proc/boot/t_}"; fi'
    echo 'done'
    echo 'echo "@@RESULT pass=$pass fail=$fail@@"'
} > "$OUT/runtests"
chmod +x "$OUT/runtests"
