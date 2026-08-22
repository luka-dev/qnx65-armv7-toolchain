#!/bin/sh
# A/B the SDP's gas 2.19 against our gas 2.38 over binutils' own ARM testsuite.
#
# We replaced the assembler because 2.19 mis-encodes the VFP multiply-accumulate
# family (see binutils/build.sh). That was found the hard way, from corrupted
# output. This answers the obvious follow-up - "where ELSE do they disagree?" -
# by assembling every arm test with both and diffing the disassembly.
#
# LIMIT, worth knowing: this suite does NOT cover the bug we actually shipped
# around. Its vmla/vmls tests are ARMv8.2-FP16 and MVE, which 2.19 rejects
# outright, so they never reach the comparison - there is no ARMv7-VFP test of
# the mla family in UAL spelling that 2.19 would accept. That is why the bug
# survived to 2026, and why host-scripts/qnx-selftest.sh checks those four
# mnemonics explicitly rather than relying on this run.
#
# Runs inside the :8.5 image, the only one carrying both assemblers.
#   tests/asm-ab.sh [binutils-version]     (default 2.38, the one we ship)
set -eu
VER=${1:-2.38}
IMG=qnx65-armv7-toolchain:8.5
docker image inspect "$IMG" >/dev/null 2>&1 || {
    echo "$IMG not built - run: host-scripts/qnx-run.sh build 8.5" >&2; exit 1; }

exec docker run --rm --platform=linux/amd64 -e VER="$VER" "$IMG" sh -c '
# NOT set -e: an assembler rejecting a test is normal data here, not an error.
set -u
B=/opt/qnx650/host/linux/x86/usr/bin/arm-unknown-nto-qnx6.5.0eabi
A19=$B-as-2.19; A38=$B-as-2.38; OD=$B-objdump
for t in "$A19" "$A38" "$OD"; do
    [ -x "$t" ] || { echo "missing $t" >&2; exit 1; }
done

cd /tmp
echo "fetching binutils-$VER testsuite ..." >&2
curl -fsSL "https://ftp.gnu.org/gnu/binutils/binutils-$VER.tar.xz" -o b.tar.xz || {
    echo "download failed" >&2; exit 1; }
tar -xf b.tar.xz "binutils-$VER/gas/testsuite/gas/arm" || {
    echo "extract failed" >&2; exit 1; }
TS=/tmp/binutils-$VER/gas/testsuite/gas/arm
mkdir -p /tmp/ab && cd /tmp/ab

tot=0 both=0 same=0 diffn=0 only38=0 neither=0 neg=0 negcaught=0 regress=0
for s in "$TS"/*.s; do
    n=$(basename "$s" .s); d="$TS/$n.d"; tot=$((tot+1))
    # honour the flags the testsuite itself uses (#as: line in the .d file)
    fl=""; [ -f "$d" ] && fl=$(sed -n "s/^#as: *//p" "$d" | head -1)
    if $A19 $fl "$s" -o a19.o >/dev/null 2>&1; then r19=0; else r19=1; fi
    if $A38 $fl "$s" -o a38.o >/dev/null 2>&1; then r38=0; else r38=1; fi

    # A test with a .l file is a NEGATIVE test: the source is deliberately
    # invalid and rejecting it is the correct behaviour. Comparing encodings
    # there is meaningless - what matters is who noticed the error.
    if [ -f "$TS/$n.l" ]; then
        neg=$((neg+1))
        if [ $r19 -eq 0 ] && [ $r38 -ne 0 ]; then
            negcaught=$((negcaught+1)); echo "$n" >> NEG_2_19_ACCEPTED
        fi
        continue
    fi

    if [ $r19 -ne 0 ] && [ $r38 -ne 0 ]; then neither=$((neither+1)); continue; fi
    if [ $r19 -ne 0 ]; then only38=$((only38+1)); continue; fi   # 2.19 too old
    if [ $r38 -ne 0 ]; then
        regress=$((regress+1)); echo "$n" >> REGRESSIONS; continue
    fi
    both=$((both+1))
    # compare encodings via one disassembler, so only the bytes differ
    $OD -d a19.o | tail -n +4 > x19.txt
    $OD -d a38.o | tail -n +4 > x38.txt
    if cmp -s x19.txt x38.txt; then same=$((same+1)); else
        diffn=$((diffn+1)); echo "$n" >> DIFFS
        { echo "=== $n (flags: ${fl:-none}) ==="; diff x19.txt x38.txt | head -12; } >> DIFF_DETAIL
    fi
done

echo "======================================================"
echo "arm tests in suite          : $tot"
echo "  negative (invalid on purpose): $neg"
echo "    2.19 accepted, 2.38 caught : $negcaught"
echo "  positive, assembled by both  : $both"
echo "    identical encoding         : $same"
echo "    DIFFERENT encoding         : $diffn"
echo "  2.38 only (2.19 too old)     : $only38"
echo "  neither (needs harness)      : $neither"
echo "  REGRESSIONS (2.38 lost)      : $regress"
echo "======================================================"
if [ -f NEG_2_19_ACCEPTED ]; then
    echo "--- invalid asm that gas 2.19 assembled anyway ---"; cat NEG_2_19_ACCEPTED; echo
fi
if [ -f REGRESSIONS ]; then
    echo "--- REAL regressions: valid asm 2.38 refuses ---"; cat REGRESSIONS; echo
fi
[ -f DIFFS ] || { echo "no encoding differences"; exit 0; }
echo "--- tests whose encoding differs ---"; cat DIFFS
echo; echo "--- detail ---"; cat DIFF_DETAIL
'
