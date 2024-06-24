#include "example.h"

void example(hls::stream<transPkt_input> &input, hls::stream<transPkt_output> &output)
{
#pragma HLS INTERFACE axis port = input
#pragma HLS INTERFACE axis port = output
#pragma HLS INTERFACE mode = s_axilite port = return

    amp_ctrl ac;
#pragma HLS aggregate variable = ac compact = bit

    transPkt_input input_stream;
    transPkt_output output_stream;

    for (int i = 0; i < 8; i++)
    {
        input_stream = input.read();
        ac.arr[i] = input_stream.data.to_int();
    }

    ap_uint<256> concatenated_data = 0;
    for (int i = 0; i < 8; i++)
    {
        concatenated_data.range((i + 1) * 32 - 1, i * 32) = ac.arr[i];
    }

    output_stream.data = concatenated_data;
    output_stream.last = 1;

    output.write(output_stream);
}
