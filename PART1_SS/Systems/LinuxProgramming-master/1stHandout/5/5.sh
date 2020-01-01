#!/bin/bash
gcc 5.c
./a.out &
PID=$!
echo "PID of the process $PID"
sleep 1
ls -l /proc/$PID/fd/
sleep 1
echo "Killing process $PID"
kill -9 $PID
rm file* a.out
echo "Done!"
