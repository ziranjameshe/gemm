export OPENBLAS_NUM_THREADS=0
./gemm.py
export OPENBLAS_NUM_THREADS=1
./gemm.py
g++ -std=c++17 -Wall -O3 gemm.cpp -S
g++ -std=c++17 -Wall -O3 gemm.cpp -o a.out && ./a.out
