#include "lab_1.h"
#include <iostream>
using namespace std;

int main()
{
    // Create data
    data_t A[3] = {19.0, 23.2, 11.23};
    data_t B[3] = {8.7, 4.5, 0};
    data_t C[3] = {9.05, 1.5, 2.74};

    // BM output
    data_t gnd_truth[3] = {0};

    for (int i = 0; i < 3; i++)
    {
        gnd_truth[i] = A[i] + B[i] / 2 - C[i];
    }

    // PL output
    data_t out[3] = {0.0};

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
