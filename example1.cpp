#include "example1.h"

void example1(data_t A, data_t B, data_t C, data_t &Y)
{
	// #pragma HLS INTERFACE s_axilite port=A
	Y = A + 2*B - C;
}
