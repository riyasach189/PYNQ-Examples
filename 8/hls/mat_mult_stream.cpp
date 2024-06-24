#include "mat_mult_stream.h"

void matrixmul_1(hls::stream<transPkt> &in_A, hls::stream<transPkt> &out_C)
{

#pragma HLS INTERFACE axis port = in_A
#pragma HLS INTERFACE axis port = out_C

#pragma HLS INTERFACE mode = s_axilite port = return

    // local input and output matrices
    Mat_Dtype input_A[MATSIZE][MATSIZE];
    Mat_Dtype input_B[MATSIZE][MATSIZE];
    Mat_Dtype output_C[MATSIZE][MATSIZE];

    int row, col, idx;
    transPkt local_stream;

// saving stream data to respective variables
loop_input_A1:
    for (row = 0; row < MATSIZE; row++)
    {
    loop_input_A2:
        for (col = 0; col < MATSIZE; col++)
        {
            local_stream = in_A.read();

            // Use integer type to read from the AXIS packets
            input_A[row][col].i = local_stream.data;
        }
    }

loop_input_B1:
    for (row = 0; row < MATSIZE; row++)
    {
    loop_input_B2:
        for (col = 0; col < MATSIZE; col++)
        {
            local_stream = in_A.read();

            // Use integer type to read from the AXIS packets
            input_B[row][col].i = local_stream.data;
        }
    }

// matrix multiplication
loop1:
    for (row = 0; row < MATSIZE; row++)
    {
    loop2:
        for (col = 0; col < MATSIZE; col++)
        {
            // Do the calculation s with floating points
            Mat_Dtype res;
            res.fp = 0;

        loop3:
            for (idx = 0; idx < MATSIZE; idx++)
            {
                res.fp += input_A[row][idx].fp * input_B[idx][col].fp;
            }

            output_C[row][col].fp = res.fp;
        }
    }

// stream output data
// AXIS output packets are expecting integer type
loop_input_C1:
    for (row = 0; row < MATSIZE; row++)
    {
    loop_input_C2:
        for (col = 0; col < MATSIZE; col++)
        {
            local_stream.data = output_C[row][col].i;

            if ((row == MATSIZE - 1) && (col == MATSIZE - 1))
            {
                local_stream.last = 1;
            }

            else
            {
                local_stream.last = 0;
            }

            out_C.write(local_stream);
        }
    }
}
