#ifndef _EXAMPLE1_
#define _EXAMPLE1_

#include <ap_int.h>

typedef ap_int<32> data_t;    // allows us to create integers of variable bit size; efficient bit optimization

void example1(data_t A, data_t B, data_t C, data_t &Y);  //output is passed by reference

#endif
