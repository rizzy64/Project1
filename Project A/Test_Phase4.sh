#!/bin/bash
gcc -Wall -pthread Phase4.c -o phase4
for i in {1..100}; do
  if ! timeout 1 ./phase4 >/dev/null; then
    echo "Hang at iteration $i"
    exit 1
  fi
done
echo "All 100 runs completed without deadlock."