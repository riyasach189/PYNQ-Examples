#define __gmp_const const
#include <stdio.h>
#include <hls_stream.h>
#include <ap_int.h>
#include "ap_axi_sdata.h"

#define MATSIZE 8
#define solution1 // active solution

// Define the data type for matrix input and output
#ifdef solution1
typedef float Mat_Dtype;
#endif

// Define the axis data structure
typedef hls::axis<float, 0, 0, 0> outSdCh;

void matrixmul_1(hls::stream<outSdCh> &in_A, hls::stream<outSdCh> &out_C);