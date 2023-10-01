// simd_float16
// __tg_fma
// simd_muladd

void V004_simd_muladd_with_simd_float16(float *matrix_A, float *matrix_B, float *matrix_C_cpp) {

    uint64_t start_time_nano, end_time_nano, used_time_nano;
    start_time_nano = get_time_nanos();

    simd_float16 A_f16, B_f16, C_f16;

    for (int y = 0; y < N; y++) {

        for (int simd_k = 0; simd_k < N; simd_k += SIMD_SIZE) {
            for (int simd_x = 0; simd_x < N; simd_x += SIMD_SIZE) {

                // Load C_f16
                for (int x = simd_x; x < simd_x + SIMD_SIZE; x++) {
                    C_f16[x - simd_x] = matrix_C_cpp[y * N + x];
                }

                // Load A_f16, B_f16
                for (int k = simd_k; k < simd_k + SIMD_SIZE; k++) {
                    for (int x = simd_x; x < simd_x + SIMD_SIZE; x++) {
                        A_f16[x - simd_x] = matrix_A[y * N + k];
                        B_f16[x - simd_x] = matrix_B[k * N + x];
                    }

                    // Compute
                    C_f16 = simd_muladd(A_f16, B_f16, C_f16);
                }

                // Store
                for (int x = simd_x; x < simd_x + SIMD_SIZE; x++) {
                    matrix_C_cpp[y * N + x] = C_f16[x - simd_x];
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

