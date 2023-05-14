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
                            // acc = fmaf(A[y][k], B[k][x], acc);
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
