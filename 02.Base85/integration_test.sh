#!/usr/bin/env bash

set -euo pipefail

if command -v python3 >/dev/null 2>&1; then
  PYTHON=python3
elif command -v python >/dev/null 2>&1; then
  PYTHON=python
else
  echo "python not found" >&2
  exit 1
fi

tmpdir=$(mktemp -d)
trap 'rm -rf "$tmpdir"' EXIT
status=0

check_case()
{
  local input=$1
  local name=$2

  "$PYTHON" -c 'import sys, base64; sys.stdout.buffer.write(base64.b85encode(sys.stdin.buffer.read()))' \
    <"$input" >"$tmpdir/$name.ref.b85"

  ./base85 -e <"$input" >"$tmpdir/$name.test.b85"
  ./base85 -d <"$tmpdir/$name.ref.b85" >"$tmpdir/$name.test.bin"

  if cmp -s "$tmpdir/$name.ref.b85" "$tmpdir/$name.test.b85"; then
    echo "$name encoder ok"
  else
    echo "$name encoder failed" >&2
    status=1
  fi

  if cmp -s "$input" "$tmpdir/$name.test.bin"; then
    echo "$name decoder ok"
  else
    echo "$name decoder failed" >&2
    status=1
  fi
}

: >"$tmpdir/empty.bin"
printf '1234567890abcdef short text for base85 test' >"$tmpdir/text.bin"
dd bs=512 count=1 if=/dev/urandom of="$tmpdir/random.bin" 2>/dev/null

check_case "$tmpdir/empty.bin" empty
check_case "$tmpdir/text.bin" text
check_case "$tmpdir/random.bin" random

exit "$status"
