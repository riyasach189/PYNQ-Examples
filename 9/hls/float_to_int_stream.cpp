#include "float_to_int_stream.h"
#include <math.h>

void example(hls::stream<transPkt> &A, hls::stream<transPkt> &B, hls::stream<transPkt> &C)
{
#pragma HLS INTERFACE mode = axis port = A, B, C
#pragma HLS INTERFACE mode = s_axilite port = return

    fp_int Adata, Bdata, Cdata;
    transPkt Apkt, Bpkt;

    for (unsigned int i = 0; i < LEN; i++)
    {
        Apkt = A.read();
        Bpkt = B.read();

        // Use integer type to read from the AXIS packets
        Adata.i = Apkt.data;
        Bdata.i = Bpkt.data;

        // Do the calculation s with floating points
        Cdata.fp = Adata.fp + Bdata.fp;

        // AXIS output packets are expecting integer type
        Apkt.data = Cdata.i;
        C.write(Apkt);
    }
}
