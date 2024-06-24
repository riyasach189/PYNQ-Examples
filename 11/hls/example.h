#define __gmp_const const
#include "ap_int.h"
#include <iostream>
#include "ap_axi_sdata.h"
#include "hls_stream.h"

typedef ap_axis<32, 2, 5, 6> transPkt_input;
typedef ap_axis<256, 2, 5, 6> transPkt_output;

typedef struct
{
    int arr[8];
} amp_ctrl;

void example(hls::stream<transPkt_input> &input, hls::stream<transPkt_output> &output);
