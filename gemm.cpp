#include <stdio.h>
#include <iostream>
#include <math.h>
#include <simd/matrix.h>

#include "utility.h"
#include "algo/simple_matrix_multiplication.h"
#include "algo/block_matrix_multiplication.h"
#include "algo/apple_silicon_AMX_matrix_multiplication.h"

float A[N][N];
float B[N][N];
float C[N][N];
float C_python[N][N];

int main() {

    assert(N % BLOCK == 0);

    printf("C++: %d * %d Matrix Multiplication\n", N, N);

    double flop  = N * N * 2.0 * N;
    printf("%.2f GFLOP\n\n", flop / 1e9);

    // printf("Simple Matrix Multiplication\n");
    // for (int i = 0; i < 2; i++){
    //     read_matrix_data(A, B, C, C_python);
    //     simple_matrix_multiplication(A, B, C);
    // }
    // validate_results(C, C_python);

    printf("Block Matrix Multiplication\n");
    for (int i = 0; i < 2; i++){
        read_matrix_data(A, B, C, C_python);
        block_matrix_multiplication(A, B, C);
    }
    validate_results(C, C_python);

    printf("Apple Silicon AMX Matrix Multiplication\n");
    for (int i = 0; i < 2; i++){
        read_matrix_data(A, B, C, C_python);
        apple_silicon_AMX_matrix_multiplication(A, B, C);
    }
    validate_results(C, C_python);

}
