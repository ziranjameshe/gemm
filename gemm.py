#!/usr/bin/env python3

import time
import os
import numpy as np

DEBUG = False

with open('data_type.hpp', 'r') as read_file:
    for each_line in read_file.readlines():
        if each_line.startswith('#define N '):
            N = int(each_line.split(' ')[-1])
            break

with open('data_type.hpp', 'r') as read_file:
    for each_line in read_file.readlines():
        if each_line.startswith('#define DEBUG'):
            DEBUG = bool(each_line.split(' ')[-1])
            break

print(f'N = {N}')
print(f'DEBUG = {DEBUG}')

if DEBUG == True:
    # N^2
    A = np.full((N, N), 1).astype(np.float32)
    # N^2
    B = np.full((N, N), 1).astype(np.float32)
    count = 0
    for y in range(N):
        for x in range(N):
            A[y][x] = count
            B[y][x] = count
            count += 1
    C = A @ B
    print(A)
    print(B)
    print(C)

else:
    # N^2
    A = np.random.randn(N, N).astype(np.float32)
    # N^2
    B = np.random.randn(N, N).astype(np.float32)

# floating point operation
flop = N * N * 2 * N

if 'OPENBLAS_NUM_THREADS' in os.environ and os.environ['OPENBLAS_NUM_THREADS'] == '1':
    print(f'Numpy Python: {N} * {N} Matrix Multiplication Single-Thread')
else:
    print(f'Numpy Python: {N} * {N} Matrix Multiplication Multi-Thread')

print(f'{flop / 1e9:.2f} GFLOP')

print()

for i in range(4):
    start_time = time.monotonic()
    C = A @ B
    end_time   = time.monotonic()
    used_time  = end_time - start_time
    print(f'{flop / used_time / 1e9:.2f} GFLOP/S')

with open("/tmp/gemm_data", "wb") as write_file:
    write_file.write(A.data)
    write_file.write(B.data)
    write_file.write(C.data)
