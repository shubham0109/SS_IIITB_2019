#!/bin/bash
if [ $# -ne 1 ]
then
	echo "Usage: $0 <file_name>"
	exit 2
fi
gcc 10.c
./a.out $1
od -c $1