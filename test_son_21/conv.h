#ifndef CONV_H
#define CONV_H

#include <hls_stream.h>
#include "ap_fixed.h"



//template <typename T>
//void sp_conv(int padding, int width, int height, hls::stream<T> &src, T ker[K][K], hls::stream<T> &dst);

typedef ap_fixed<32,4> data_t;

void conv(int padding, int width, int height, hls::stream<data_t> &src_img, hls::stream<data_t> &dst_img);

// data_t kernel[3][3]= {0.077291004, 0.016202895, -0.031321477, 0.029635014, 0.2397271, 0.12857132, 0.093713164, 0.17668854, 0.08295359},
#endif