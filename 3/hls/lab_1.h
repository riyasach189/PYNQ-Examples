#ifndef _LAB_1_
#define _LAB_1_
#define __gmp_const const

#include <ap_int.h>

typedef ap_int<32> data_t; // allows us to create integers of variable bit size; efficient bit optimization

void lab_1(data_t A, data_t B, data_t C, data_t &Y); // output is passed by reference

#endif
