#!/bin/bash
echo  "Some text in the file." > file
gcc 11.c
./a.out file
od -c file
cat file
rm a.out file