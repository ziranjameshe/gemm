
#include <vecLib/vDSP.h>
void V006_vDSP_mmul(float *matrix_A, float *matrix_B, float *matrix_C_cpp) {

    uint64_t start_time_nano, end_time_nano, used_time_nano;
    start_time_nano = get_time_nanos();

    vDSP_mmul(matrix_A, 1, matrix_B, 1, matrix_C_cpp, 1, N, N, N);

    end_time_nano  = get_time_nanos();

    used_time_nano = end_time_nano - start_time_nano;

    double flop  = N * N * 2.0 * N;
    double flops = flop / (used_time_nano / 1e9);

    printf("%.2f GFLOP/S\n", flops / 1e9);

}
