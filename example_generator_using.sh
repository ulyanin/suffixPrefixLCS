#!/usr/bin/bash

mkdir build
mkdir tests
cd build
cmake ..
make
./generate_tests 'tests/' 0 10 2000 2000
cd ..

