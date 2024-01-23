#ifndef __ACTIVATIONS_H
#define __ACTIVATIONS_H

#include "ap_fixed.h"
typedef ap_fixed<32,4> data_t;

data_t relu(data_t a)
{
	return a > (data_t)0 ? a : (data_t)0;
}

#endif