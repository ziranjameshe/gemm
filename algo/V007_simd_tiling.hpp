
static_assert(N % TILING_BLOCK == 0, "N must be a multiple of TILING_BLOCK");

void V007_simd_tiling(float *matrix_A, float *matrix_B, float *matrix_C_cpp) {

    uint64_t start_time_nano, end_time_nano, used_time_nano;
    start_time_nano = get_time_nanos();


    simd_float16 A_f16, B_f16, C_f16;

    // Each row
    for (int i = 0; i < N; i++) {

        // Each batch per row
        for (int j = 0; j < N; j += TILING_BLOCK) {

            // Make C
            for (int k = 0; k < TILING_BLOCK; k++) {
                C_f16[k] = 0.0f;
            }


            for (int x = 0; x < N; x++) {
                // Load A
                for (int k = 0; k < TILING_BLOCK; k++) {
                    A_f16[k] = matrix_A[i * N + x];
                }

                // Load B
                for (int k = 0; k < TILING_BLOCK; k++) {
                    B_f16[k] = matrix_B[x * N + j + k];
                }

                // Compute
                C_f16 = simd_muladd(A_f16, B_f16, C_f16);

            }

            // Store C
            for (int k = 0; k < TILING_BLOCK; k++) {
                matrix_C_cpp[i * N + j + k] = C_f16[k];
            }

        }


    }

    end_time_nano  = get_time_nanos();

    used_time_nano = end_time_nano - start_time_nano;

    double flop  = N * N * 2.0 * N;
    double flops = flop / (used_time_nano / 1e9);

    printf("%.2f GFLOP/S\n", flops / 1e9);

}
