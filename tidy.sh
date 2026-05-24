#!/usr/bin/env bash

set -eo pipefail

CHECKS='-*,clang-analyzer-*,performance-*,bugprone-*'

if ! command -v clang-tidy >/dev/null 2>&1; then
  echo "clang-tidy not found, skipping"
  exit 0
fi

FILES=()
while IFS= read -r -d '' file; do
  FILES+=("$file")
done < <(find . -maxdepth 1 -type f \( -name '*.cpp' -o -name '*.cxx' -o -name '*.cc' \) -print0)

if [[ ${#FILES[@]} -eq 0 ]]; then
  echo "No source files to analyze."
  exit 0
fi

for f in "${FILES[@]}"; do
  echo "Running clang-tidy on $f"
  clang-tidy -checks="$CHECKS" "$f" -- -std=c++17 -I. -I.. 2>&1
done
