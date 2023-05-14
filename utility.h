
const int N = 1024;
const int BLOCK = 32;

uint64_t get_time_nanos() {
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    return (uint64_t)start.tv_sec * 1000000000 + (uint64_t)start.tv_nsec;
}

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
