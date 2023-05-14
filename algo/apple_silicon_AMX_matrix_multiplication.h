void apple_silicon_AMX_matrix_multiplication(float A[N][N], float B[N][N], float C[N][N]) {

    uint64_t start_time_nano, end_time_nano, used_time_nano;
    start_time_nano = get_time_nanos();

    simd_float4x4 simd_a, simd_b, simd_c, simd_acc;

    for (int by = 0; by < N; by += AMX_BLOCK) {
        for (int bx = 0; bx < N; bx += AMX_BLOCK) {

            // Load simd_a
            // for (int y = by; y < by + AMX_BLOCK; y++) {
            //     for (int x = bx; x < bx + AMX_BLOCK; x++) {
            //         simd_a.columns[x - bx][y - by] = A[y][x];
            //     }
            // }
            simd_acc = {};

            // Load simd_b
            // k is really y for B
            // x is also   x for B
            for (int bk = 0; bk < N; bk += AMX_BLOCK) {

                for (int y = by; y < by + AMX_BLOCK; y++) {
                    for (int k = bk; k < bk + AMX_BLOCK; k++) {
                        for (int x = bx; x < bx + AMX_BLOCK; x++) {
                            simd_a.columns[k - bk][y - by] = A[y][k];
                            simd_b.columns[x - bx][k - bk] = B[k][x];
                        }
                    }
                }
                // print_simd_float4x4(simd_b);

                simd_c   = matrix_multiply(simd_a, simd_b);
                simd_acc = simd_add(simd_acc, simd_c);
            }

            // Store
            for (int y = by; y < by + AMX_BLOCK; y++) {
                for (int x = bx; x < bx + AMX_BLOCK; x++) {
                    // C[y][x] = simd_acc.columns[x - bx][y - by];
                    C[y][x] = simd_acc.columns[x - bx][y - by];
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
