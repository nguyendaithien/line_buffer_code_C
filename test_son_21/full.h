// full.h
#ifndef FULL_H
#define FULL_H

#include <hls_stream.h>
#include <stdint.h>
#include "ap_fixed.h"


typedef ap_fixed<32,4> data_t;


void conv1(int padding, int width, int height, hls::stream<data_t> &src_img, hls::stream<data_t> &dst_img);
void pool1(int width, int height, hls::stream<data_t> &in_pl1, hls::stream<data_t> &out_pl1);
void conv2(int padding,int width, int height, hls::stream<data_t> &src_conv1, hls::stream<data_t> &dst_conv1);
void full(hls::stream<data_t> &full_in, hls::stream<data_t> &full_out);

#endif
