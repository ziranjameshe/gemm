// simd_float16
// __tg_fma
// simd_muladd

void V005_simd_muladd_with_simd_float16_v2(float *matrix_A, float *matrix_B, float *matrix_C_cpp) {

    uint64_t start_time_nano, end_time_nano, used_time_nano;
    start_time_nano = get_time_nanos();

    for (int y = 0; y < N; y++) {

        for (int x = 0; x < N; x++) {

            float acc = 0;

            simd_float16 temp = {};

            for (int k = 0; k < N / 16; k++) {

                temp = simd_muladd(matrix_A[y * N / 16 + k], matrix_B[x * N / 16 + k], temp);

            }

            for (int index = 0; index < 16; index++) {

                acc += temp[index];
            }

            matrix_C_cpp[y * N + x] = acc;
        }

    }

    end_time_nano  = get_time_nanos();

    used_time_nano = end_time_nano - start_time_nano;

    double flop  = N * N * 2.0 * N;
    double flops = flop / (used_time_nano / 1e9);

    printf("%.2f GFLOP/S\n", flops / 1e9);

}
