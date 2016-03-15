#!/bin/bash
#
# TEST ENVIRONMENT
# gcc version: gcc (Ubuntu 5.2.1-22ubuntu2) 5.2.1 20151010
# gcc options: gcc -ggdb cheese.c -ansi -fno-asm -O2 -Wall -lm --static
# os: Linux-4.5.0-rc4+-x86_64-with-Ubuntu-15.10-wily

echo -e "4 14\n\
2 40\n\
5 110\n\
10 200\n\
3 50\n" | ./a.out
