#include "lab_1.h"
#include <iostream>
using namespace std;

int main()
{
    // Create data
    data_t A[3] = {190, 232, 1123};
    data_t B[3] = {87, 45, 0};
    data_t C[3] = {905, 15, 274};

    // Benchmark
    data_t gnd_truth[3] = {0};

    for (int i = 0; i < 3; i++)
    {
        gnd_truth[i] = A[i] + 2 * B[i] - C[i];
    }

    // PL output
    data_t out[3] = {0};

    for (int i = 0; i < 3; i++)
    {
        lab_1(A[i], B[i], C[i], out[i]);
    }

    // Check if BM and PL output match
    int ret_val = 0;
    for (int i = 0; i < 3; i++)
    {
        if (gnd_truth[i] != out[i])
        {
            ret_val++;
        }
    }

    cout << "There were " << ret_val << " errors.\n";

    return ret_val;
}