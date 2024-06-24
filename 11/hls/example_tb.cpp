#include "example.h"

int main()
{
    int input_arr[] = {1, 2, 3, 4, 5, 6, 7, 8};

    ap_uint<256> gnd_truth =
        (ap_uint<256>(0x00000008) << 224) |
        (ap_uint<256>(0x00000007) << 192) |
        (ap_uint<256>(0x00000006) << 160) |
        (ap_uint<256>(0x00000005) << 128) |
        (ap_uint<256>(0x00000004) << 96) |
        (ap_uint<256>(0x00000003) << 64) |
        (ap_uint<256>(0x00000002) << 32) |
        ap_uint<256>(0x00000001);

    ap_uint<256> ip_output;

    transPkt_input input_stream;
    transPkt_output output_stream;
    hls::stream<transPkt_input> input;
    hls::stream<transPkt_output> output;

    for (int i = 0; i < 8; i++)
    {
        input_stream.data = input_arr[i];
        input_stream.last = (i == 7) ? 1 : 0;
        input.write(input_stream);
    }

    example(input, output);

    output_stream = output.read();
    ip_output = output_stream.data;

    std::cout << "ip_output  : " << ip_output.to_string(16) << std::endl;
    std::cout << "gnd_truth  : " << gnd_truth.to_string(16) << std::endl;

    if (ip_output == gnd_truth)
    {
        std::cout << "Test Passed!" << std::endl;
        return 0;
    }

    std::cout << "Test Failed!" << std::endl;
    return 1;
}
