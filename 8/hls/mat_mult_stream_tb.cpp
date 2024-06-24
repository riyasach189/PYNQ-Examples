#include "mat_mult_stream.h"
#include <stdio.h>
#include <math.h>

void matrix_mult_bm(double input_A[MATSIZE][MATSIZE],
                    double input_B[MATSIZE][MATSIZE], double output_C[MATSIZE][MATSIZE]);

int main()
{
    fp_int input_A[MATSIZE][MATSIZE];
    fp_int input_B[MATSIZE][MATSIZE];
    fp_int output_C_HW[MATSIZE][MATSIZE];

    double input_A_BM[MATSIZE][MATSIZE];
    double input_B_BM[MATSIZE][MATSIZE];
    double output_C_BM[MATSIZE][MATSIZE];

    int row, col, idx;

// Generate test data
loop_input_1:
    for (row = 0; row < MATSIZE; row++)
    {
    loop_input_2:
        for (col = 0; col < MATSIZE; col++)
        {
            input_A[row][col].fp = static_cast<float>(rand() % 10) * 1.1;
            input_B[row][col].fp = static_cast<float>(rand() % 10) * 1.1;

            input_A_BM[row][col] = input_A[row][col].fp;
            input_B_BM[row][col] = input_B[row][col].fp;
        }
    }

    // Call benchmark function
    matrix_mult_bm(input_A_BM, input_B_BM, output_C_BM);

    transPkt local_stream;
    hls::stream<transPkt> in_A, out_C;

// Generate stream input A for hardware function
loop_input_A1:
    for (row = 0; row < MATSIZE; row++)
    {
    loop_input_A2:
        for (col = 0; col < MATSIZE; col++)
        {
            local_stream.data = input_A[row][col].i;

            if ((row == MATSIZE - 1) && (col == MATSIZE - 1))
            {
                local_stream.last = 1;
            }

            else
            {
                local_stream.last = 0;
            }

            in_A.write(local_stream);
        }
    }

// Generate stream input B for hardware function
loop_input_B1:
    for (row = 0; row < MATSIZE; row++)
    {
    loop_input_B2:
        for (col = 0; col < MATSIZE; col++)
        {
            local_stream.data = input_B[row][col].i;

            if ((row == MATSIZE - 1) && (col == MATSIZE - 1))
            {
                local_stream.last = 1;
            }

            else
            {
                local_stream.last = 0;
            }

            in_A.write(local_stream);
        }
    }

#ifdef solution1
    matrixmul_1(in_A, out_C);
#endif

// Receive stream output C from hardware function
loop_output_C1:
    for (row = 0; row < MATSIZE; row++)
    {
    loop_output_C2:
        for (col = 0; col < MATSIZE; col++)
        {
            local_stream = out_C.read();
            output_C_HW[row][col].i = local_stream.data;
        }
    }

// Compare Benchmark and Hardware
loop_compare_C1:
    for (row = 0; row < MATSIZE; row++)
    {
    loop_compare_C2:
        for (col = 0; col < MATSIZE; col++)
        {
            printf("HW: %f    ", output_C_HW[row][col].fp);
            printf("BM: %f\n", output_C_BM[row][col]);

            if (fabs(output_C_HW[row][col].fp - output_C_BM[row][col]) > 0.01)
            {
                printf("Error at row index %d and column index %d", row, col);
                return 1;
            }
        }
    }

    return 0;
}

void matrix_mult_bm(double input_A[MATSIZE][MATSIZE], double input_B[MATSIZE][MATSIZE], double output_C[MATSIZE][MATSIZE])
{
    int row, col, idx;

loop1:
    for (row = 0; row < MATSIZE; row++)
    {
    loop2:
        for (col = 0; col < MATSIZE; col++)
        {
            double res = 0;

        loop3:
            for (idx = 0; idx < MATSIZE; idx++)
            {
                res += input_A[row][idx] * input_B[idx][col];
            }

            output_C[row][col] = res;
        }
    }
}
