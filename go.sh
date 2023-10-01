#/usr/bin/env bash

set -e
# export OPENBLAS_NUM_THREADS=0
# ./gemm.py
export OPENBLAS_NUM_THREADS=1
./gemm.py

g++ -std=c++17 -Wall -O3 -ffast-math -march=native -framework Accelerate gemm.cpp -o a.out
objdump -d a.out > a.s
./a.out
