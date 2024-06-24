#include "lab_1.h"

void lab_1(data_t A, data_t B, data_t C, data_t &Y)
{

#pragma HLS INTERFACE s_axilite port = A bundle = control
#pragma HLS INTERFACE s_axilite port = B bundle = control
#pragma HLS INTERFACE s_axilite port = C bundle = control
#pragma HLS INTERFACE s_axilite port = Y bundle = control

    Y = A + B / 2 - C;
}
