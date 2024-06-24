#define __gmp_const const
#include <stdio.h>
#include <hls_stream.h>
#include "ap_axi_sdata.h"

#define MATSIZE 8
#define solution1 // active solution

union fp_int
{
    int i;
    float fp;
};

// Define the data type for matrix input and output
#ifdef solution1
typedef fp_int Mat_Dtype;
#endif

// Define the axis data structure
typedef ap_axis<32, 2, 5, 6> transPkt;

void matrixmul_1(hls::stream<transPkt> &in_A, hls::stream<transPkt> &out_C);
