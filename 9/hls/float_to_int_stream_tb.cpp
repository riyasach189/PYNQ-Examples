#include <iostream>
#include "float_to_int_stream.h"
#include "hls_stream.h"
#include "ap_axi_sdata.h"

void print_stream(hls::stream<transPkt> &stream)
{
    while (!stream.empty())
    {
        transPkt pkt = stream.read();
        fp_int data;
        data.i = pkt.data;
        std::cout << data.fp << " ";
    }
    std::cout << std::endl;
}

int main()
{
    hls::stream<transPkt> A;
    hls::stream<transPkt> B;
    hls::stream<transPkt> C;

    // Initialize test data
    fp_int testDataA[LEN];
    fp_int testDataB[LEN];
    for (int i = 0; i < LEN; ++i)
    {
        testDataA[i].fp = static_cast<float>(i) * 1.1f;
        testDataB[i].fp = static_cast<float>(i) * 2.2f;
    }

    // Fill the streams with test data
    for (int i = 0; i < LEN; ++i)
    {
        transPkt pktA, pktB;
        pktA.data = testDataA[i].i;
        pktB.data = testDataB[i].i;
        A.write(pktA);
        B.write(pktB);
    }

    // Call the example function
    example(A, B, C);

    // Print the results
    std::cout << "Output stream C:" << std::endl;
    print_stream(C);

    return 0;
}
