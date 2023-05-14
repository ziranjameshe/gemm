
void cache_aware_matrix_multiplication(float A[N][N], float B[N][N], float C[N][N]) {

    uint64_t start_time_nano, end_time_nano, used_time_nano;
    start_time_nano = get_time_nanos();

    for (int y = 0; y < N; y++) {
        for (int k = 0; k < N; k++) {
            for (int x = 0; x < N; x++) {
                C[y][x] += A[y][k] * B[k][x];
            }
        }
    }

    end_time_nano  = get_time_nanos();

    used_time_nano = end_time_nano - start_time_nano;

    double flop  = N * N * 2.0 * N;
    double flops = flop / (used_time_nano / 1e9);

    printf("%.2f GFLOP/S\n", flops / 1e9);

}
