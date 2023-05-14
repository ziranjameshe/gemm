#!/usr/bin/env python3

import time
import os

# os.environ['OPENBLAS_NUM_THREADS'] = '1'
import numpy as np

N = 1024

# N^2
A = np.random.randn(N, N).astype(np.float32)
# N^2
B = np.random.randn(N, N).astype(np.float32)

# floating point operation
flop = N * N * 2 * N
print(f'Numpy Python: {N} * {N} Matrix Multiplication')
print(f'{flop / 1e9:.2f} GFLOP')

for i in range(2):
    start_time = time.monotonic()
    C = A @ B
    end_time   = time.monotonic()
    used_time  = end_time - start_time
    print(f'{flop / used_time / 1e9:.2f} GFLOP/S')

print()

with open("/tmp/gemm_data", "wb") as write_file:
    write_file.write(A.data)
    write_file.write(B.data)
    write_file.write(C.data)
