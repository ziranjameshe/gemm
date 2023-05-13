

#include <stdio.h>
#include <iostream>

const int N     = 1024;
const int BLOCK = 32;

float A[N][N];
float B[N][N];
float C[N][N];
float C_python[N][N];

void validate_results(float C_C[N][N], float C_python[N][N]) {

    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {

            if (fabs(C_C[y][x] - C_python[y][x]) > 1e-3) {
                printf("MISMATCH AT [%d][%d], %f != %f\n", y, x, C_C[y][x], C_python[y][x]);
                exit(-1);
            }

        }
    }
    printf("MATCH!\n\n");
}

void read_matrix_data(float A[N][N], float B[N][N], float C[N][N], float C_python[N][N]) {

    FILE *read_file = fopen("/tmp/gemm_data", "rb");
    if (read_file == NULL) {
        printf("please pregenerate python /tmp/gemm_data file\n");
        exit(1);
    }

    fread(A,        1, sizeof(float) * N * N, read_file);
    fread(B,        1, sizeof(float) * N * N, read_file);
    fread(C_python, 1, sizeof(float) * N * N, read_file);

    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            C[y][x] = 0.0;
        }
    }

    fclose(read_file);

}

uint64_t get_time_nanos() {
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    return (uint64_t)start.tv_sec * 1000000000 + (uint64_t)start.tv_nsec;
}

void simple_matrix_multiplication(float A[N][N], float B[N][N], float C[N][N]) {

    uint64_t start_time_nano, end_time_nano, used_time_nano;
    start_time_nano = get_time_nanos();

    float acc;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            acc = 0;
            for (int k = 0; k < N; k++) {
                acc += A[y][k] * B[k][x];
            }
            C[y][x] = acc;
        }
    }

    end_time_nano  = get_time_nanos();

    used_time_nano = end_time_nano - start_time_nano;

    double flop  = N * N * 2.0 * N;
    double flops = flop / (used_time_nano / 1e9);

    printf("%.2f GFLOP/S\n", flops / 1e9);

}

void block_matrix_multiplication(float A[N][N], float B[N][N], float C[N][N]) {

    uint64_t start_time_nano, end_time_nano, used_time_nano;
    start_time_nano = get_time_nanos();

    float acc;
    for (int by = 0; by < N; by += BLOCK) {
        for (int bx = 0; bx < N; bx += BLOCK) {
            for (int bk = 0; bk < N; bk += BLOCK) {

                for (int y = by; y < by + BLOCK; y++) {
                    for (int x = bx; x < bx + BLOCK; x++) {
                        acc = 0;
                        for (int k = bk; k < bk + BLOCK; k++) {
                            acc += A[y][k] * B[k][x];
                        }
                        C[y][x] += acc;
                    }
                }

            }
        }
    }

    end_time_nano  = get_time_nanos();

    used_time_nano = end_time_nano - start_time_nano;

    double flop  = N * N * 2.0 * N;
    double flops = flop / (used_time_nano / 1e9);

    printf("%.2f GFLOP/S\n", flops / 1e9);

}

int main() {

    assert(N % BLOCK == 0);

    printf("C++: %d * %d Matrix Multiplication\n", N, N);

    double flop  = N * N * 2.0 * N;
    printf("%.2f GFLOP\n\n", flop / 1e9);

    printf("Simple Matrix Multiplication\n");
    for (int i = 0; i < 2; i++){
        read_matrix_data(A, B, C, C_python);
        simple_matrix_multiplication(A, B, C);
    }
    validate_results(C, C_python);

    printf("Block Matrix Multiplication\n");
    for (int i = 0; i < 2; i++){
        read_matrix_data(A, B, C, C_python);
        block_matrix_multiplication(A, B, C);
    }
    validate_results(C, C_python);

}
