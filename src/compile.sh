#!/bin/bash
gcc -c MYNET.c -o MYNET.o
gcc -c MYHTTP.c -o MYHTTP.o
ar -rcs libMYNET.a MYNET.o MYHTTP.o 
rm MYHTTP.o
rm MYNET.o