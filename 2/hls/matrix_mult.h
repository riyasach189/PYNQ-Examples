#include <stdio.h>
#include <hls_stream.h>
#include <ap_int.h>

#define MATSIZE 8
#define solution1  //active solution

// Define the data type for matrix input and output
#ifdef solution1
typedef float Mat_Dtype;
#endif

// Define the axis data structure
struct axis_data
{
	Mat_Dtype data;
	ap_uint<1> last;
};

void matrixmul_1(hls::stream<axis_data> &in_A, hls::stream<axis_data> &out_C);
