#!/bin/bash
file="main"
cd src
./compile.sh
cd ..
gcc ${file}.c -o bin/${file} -L./src -lMYNET
./bin/${file}