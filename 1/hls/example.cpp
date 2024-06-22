#include "example1.h"

void example1(data_t A, data_t B, data_t C, data_t &Y)
{
//#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE s_axilite port=A bundle=control
#pragma HLS INTERFACE s_axilite port=B bundle=control
#pragma HLS INTERFACE s_axilite port=C bundle=control
#pragma HLS INTERFACE s_axilite port=Y bundle=control
	Y = A + 2*B - C;
}
