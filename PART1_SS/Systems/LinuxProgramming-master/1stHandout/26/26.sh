#!/bin/bash
gcc hello.c -o hello
gcc 26.c
echo "==>Executing ./hello Jagmeet"
./a.out ./hello Jagmeet
echo "==>Executing ls -lh"
./a.out ls -lh
rm a.out hello