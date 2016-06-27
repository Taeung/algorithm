#!/bin/bash
#
# TEST ENVIRONMENT
# gcc version: gcc (Ubuntu 5.2.1-22ubuntu2) 5.2.1 20151010
# gcc options: gcc -ggdb cheese.c -ansi -fno-asm -O2 -Wall -lm --static
# os: Linux-4.5.0-rc4+-x86_64-with-Ubuntu-15.10-wily

echo -e "0 3 5 4 6 9 2 7 8\n\
7 8 2 1 0 5 6 0 9\n\
0 6 0 2 7 8 1 3 5\n\
3 2 1 0 4 6 8 9 7\n\
8 0 4 9 1 3 5 0 6\n\
5 9 6 8 2 0 4 1 3\n\
9 1 7 6 5 2 0 8 0\n\
6 0 3 7 0 1 9 5 2\n\
2 5 8 3 9 4 7 6 0\n" | ./$1
