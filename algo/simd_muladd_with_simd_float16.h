// simd_float16
// __tg_fma
// simd_muladd
void simd_muladd_with_simd_float16(float A[N][N], float B[N][N], float C[N][N]) {

    uint64_t start_time_nano, end_time_nano, used_time_nano;
    start_time_nano = get_time_nanos();

    simd_float16 A_f16, B_f16, C_f16;

    for (int y = 0; y < N; y++) {

        for (int simd_k = 0; simd_k < N; simd_k += 16) {
            for (int simd_x = 0; simd_x < N; simd_x += 16) {

                // Load A_f16
                for (int k = simd_k; k < simd_k + 16; k++) {

                    A_f16[k - simd_k] = A[y][k];
                }

                for (int x = simd_x; x < simd_x + 16; x++) {

                    C_f16[x - simd_x] = C[y][x];

                }

                // Load B_f16 and C_f16
                for (int k = simd_k; k < simd_k + 16; k++) {

                    for (int x = simd_x; x < simd_x + 16; x++) {

                        B_f16[x - simd_x] = B[k][x];

                    }

                    // Compute
                    C_f16 = simd_muladd(A_f16, B_f16, C_f16);
                }

                // Store
                for (int x = simd_x; x < simd_x + 16; x++) {

                    C[y][x] = C_f16[x - simd_x];

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

