#include <stdio.h>
#include <iostream>
#include <math.h>
#include <simd/matrix.h>
#include <simd/math.h>
#include <cassert>


#include "utility.h"

#include "algo/V000_simple_matrix_multiplication.hpp"
#include "algo/V001_cache_aware_matrix_multiplication.hpp"
#include "algo/V002_block_matrix_multiplication.hpp"
#include "algo/V003_apple_silicon_AMX_matrix_multiplication.hpp"
#include "algo/V004_simd_muladd_with_simd_float16.hpp"
#include "algo/V005_simd_muladd_with_simd_float16_v2.hpp"
#include "algo/V006_vDSP_mmul.hpp"
#include "algo/V007_simd_tiling.hpp"

float matrix_A[N * N] __attribute__ ((aligned(64)));
float matrix_B[N * N] __attribute__ ((aligned(64)));
float matrix_C_cpp[N * N] __attribute__ ((aligned(64)));
float matrix_C_python[N * N] __attribute__ ((aligned(64)));

// float matrix_A[N * N];
// float matrix_B[N * N];
// float matrix_C_cpp[N * N];
// float matrix_C_python[N * N];

static_assert(N % BLOCK == 0);

int main() {

    printf("C++: %d * %d Matrix Multiplication\n", N, N);

    double flop  = N * N * 2.0 * N;
    printf("%.2f GFLOP\n\n", flop / 1e9);

    // printf("V000_simple_matrix_multiplication\n");
    // for (int i = 0; i < 1; i++) {
    //     read_matrix_data(matrix_A, matrix_B, matrix_C_cpp, matrix_C_python);
    //     V000_simple_matrix_multiplication(matrix_A, matrix_B, matrix_C_cpp);
    // }
    // validate_results(matrix_C_cpp, matrix_C_python);

    // printf("V001_cache_aware_matrix_multiplication\n");
    // for (int i = 0; i < NUM_TEST; i++) {
    //     read_matrix_data(matrix_A, matrix_B, matrix_C_cpp, matrix_C_python);
    //     V001_cache_aware_matrix_multiplication(matrix_A, matrix_B, matrix_C_cpp);
    // }
    // validate_results(matrix_C_cpp, matrix_C_python);

    // printf("V002_block_matrix_multiplication\n");
    // for (int i = 0; i < NUM_TEST; i++) {
    //     read_matrix_data(matrix_A, matrix_B, matrix_C_cpp, matrix_C_python);
    //     V002_block_matrix_multiplication(matrix_A, matrix_B, matrix_C_cpp);
    // }
    // validate_results(matrix_C_cpp, matrix_C_python);

    // printf("V003_apple_silicon_AMX_matrix_multiplication\n");
    // for (int i = 0; i < NUM_TEST; i++) {
    //     read_matrix_data(matrix_A, matrix_B, matrix_C_cpp, matrix_C_python);
    //     V003_apple_silicon_AMX_matrix_multiplication(matrix_A, matrix_B, matrix_C_cpp);
    // }
    // validate_results(matrix_C_cpp, matrix_C_python);

    // printf("V004_simd_muladd_with_simd_float16\n");
    // for (int i = 0; i < NUM_TEST; i++) {
    //     read_matrix_data(matrix_A, matrix_B, matrix_C_cpp, matrix_C_python);
    //     V004_simd_muladd_with_simd_float16(matrix_A, matrix_B, matrix_C_cpp);
    // }
    // validate_results(matrix_C_cpp, matrix_C_python);

    // // printf("V005_simd_muladd_with_simd_float16_v2\n");
    // // for (int i = 0; i < NUM_TEST; i++) {
    // //     read_matrix_data(matrix_A, matrix_B, matrix_C_cpp, matrix_C_python);
    // //     V005_simd_muladd_with_simd_float16_v2(matrix_A, matrix_B, matrix_C_cpp);
    // // }
    // // validate_results(matrix_C_cpp, matrix_C_python);

    // printf("V006_vDSP_mmul\n");
    // for (int i = 0; i < NUM_TEST; i++) {
    //     read_matrix_data(matrix_A, matrix_B, matrix_C_cpp, matrix_C_python);
    //     V006_vDSP_mmul(matrix_A, matrix_B, matrix_C_cpp);
    // }
    // validate_results(matrix_C_cpp, matrix_C_python);

    printf("V007_simd_tiling\n");
    for (int i = 0; i < NUM_TEST; i++) {
        read_matrix_data(matrix_A, matrix_B, matrix_C_cpp, matrix_C_python);
        V007_simd_tiling(matrix_A, matrix_B, matrix_C_cpp);
    }
    validate_results(matrix_C_cpp, matrix_C_python);

}
