
#include "data_type.hpp"

uint64_t get_time_nanos() {
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    return (uint64_t)start.tv_sec * 1000000000 + (uint64_t)start.tv_nsec;
}


void read_matrix_data(float *matrix_A, float *matrix_B, float *matrix_C_cpp, float *matrix_C_python) {

    FILE *read_file = fopen("/tmp/gemm_data", "rb");

    if (read_file == NULL) {
        printf("please pregenerate python /tmp/gemm_data file\n");
        exit(1);
    }

    fread(matrix_A,        sizeof(float), N * N, read_file);
    fread(matrix_B,        sizeof(float), N * N, read_file);
    fread(matrix_C_python, sizeof(float), N * N, read_file);

    memset(matrix_C_cpp, 0.0, sizeof(float) * N * N);

    fclose(read_file);

}

void validate_results(float *matrix_C_cpp, float *matrix_C_python) {

    bool match = true;

    for (int i = 0; i < N * N; i++) {
        if (fabs(matrix_C_cpp[i] - matrix_C_python[i]) > 1e-3 || isnan(*(matrix_C_cpp + i)) == true) {
            printf(
                "MISMATCH AT [%d], %.3f != %.3f, difference = %.3f\n",
                i,
                matrix_C_cpp[i],
                matrix_C_python[i],
                fabs(matrix_C_cpp[i] - matrix_C_python[i])
            );
            match = false;
            #ifndef DEBUG
                exit(-1);
            #endif
        } else {
            #ifdef DEBUG
                printf("AT [%d], C++ %.3f == PYTHON %.3f\n", i, matrix_C_cpp[i], matrix_C_python[i]);
            #endif
        }
    }

    if (match == true) {
        printf("MATCH!\n\n");
    } else {
        printf("MISMATCH!\n\n");
    }
}
