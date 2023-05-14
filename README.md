# gemm

## BenchMark
```
[0h:1m:49s] ✅ (master) gemm/> ./go.sh 
Numpy Python: 1024 * 1024 Matrix Multiplication Multi-Thread
2.15 GFLOP
234.70 GFLOP/S
200.03 GFLOP/S
227.90 GFLOP/S
131.97 GFLOP/S

Numpy Python: 1024 * 1024 Matrix Multiplication Single-Thread
2.15 GFLOP
100.54 GFLOP/S
99.46 GFLOP/S
101.80 GFLOP/S
101.15 GFLOP/S

C++: 1024 * 1024 Matrix Multiplication
2.15 GFLOP

Simple Matrix Multiplication
1.81 GFLOP/S
1.85 GFLOP/S
1.85 GFLOP/S
1.80 GFLOP/S
MATCH!

Cache Aware Matrix Multiplication
27.38 GFLOP/S
27.46 GFLOP/S
27.39 GFLOP/S
27.42 GFLOP/S
MATCH!

Block Matrix Multiplication
24.13 GFLOP/S
24.09 GFLOP/S
23.63 GFLOP/S
24.00 GFLOP/S
MATCH!

Apple Silicon AMX Matrix Multiplication
23.12 GFLOP/S
23.12 GFLOP/S
23.15 GFLOP/S
23.11 GFLOP/S
MATCH!

SIMD MULADD AVX Matrix Multiplication
33.40 GFLOP/S
33.43 GFLOP/S
33.38 GFLOP/S
33.42 GFLOP/S
MATCH!


```
