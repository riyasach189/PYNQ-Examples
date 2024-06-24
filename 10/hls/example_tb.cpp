/*
 * Copyright 2021 Xilinx, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define __gmp_const const
#include <iostream>
#include "ap_axi_sdata.h"
#include "hls_stream.h"
using namespace std;

#include "example.h"

void example(hls::stream<outSdCh> &A, hls::stream<outSdCh> &B);

int main()
{
    int i = 100;

    hls::stream<outSdCh> A, B;

    outSdCh tmp1, tmp2;

    for (int j = 0; j < 100; j++)
    {
        tmp1.data = (float)i;
        tmp1.keep = 1;
        tmp1.strb = 1;
        tmp1.user = 1;
        if (j = 99)
        {
            tmp1.last = 1;
        }
        else
        {
            tmp1.last = 0;
        }
        tmp1.id = 0;
        tmp1.dest = 1;

        A.write(tmp1);
        example(A, B);
        B.read(tmp2);

        printf("%d\n", tmp2.last.to_int());

        if ((tmp2.data - 100.5) > 0.0001)
        {
            cout << "ERROR: results mismatch" << endl;
            return 1;
        }
    }
    cout << "Success: results match" << endl;
    return 0;
}
