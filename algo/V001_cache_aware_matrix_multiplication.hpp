
void V001_cache_aware_matrix_multiplication(float *matrix_A, float *matrix_B, float *matrix_C_cpp) {

    uint64_t start_time_nano, end_time_nano, used_time_nano;
    start_time_nano = get_time_nanos();

    for (int y = 0; y < N; y++) {
        for (int k = 0; k < N; k++) {
            for (int x = 0; x < N; x++) {
                matrix_C_cpp[y * N + x] += matrix_A[y * N + k] * matrix_B[k * N + x];
            }
        }
    }

    end_time_nano  = get_time_nanos();

    used_time_nano = end_time_nano - start_time_nano;

    double flop  = N * N * 2.0 * N;
    double flops = flop / (used_time_nano / 1e9);

    printf("%.2f GFLOP/S\n", flops / 1e9);

}
