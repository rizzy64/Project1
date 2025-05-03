#!/bin/bash
gcc -Wall -pthread Phase3.c -o phase3
# try to complete within 2 s
if timeout 2 ./phase3; then
  echo "✅ Completed"
else
  echo "⛔ Deadlock detected (hung)"
fi