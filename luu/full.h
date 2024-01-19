// full.h
#ifndef FULL_H
#define FULL_H

#include <hls_stream.h>
#include <stdint.h>

#define IMG_HEIGHT 8
#define IMG_WIDTH 8
#define K 3
#define CONV1_HEIGHT (IMG_HEIGHT - K + 1)
#define CONV1_WIDTH (IMG_WIDTH - K + 1)
#define POOL_SIZE 2
#define POOL1_HEIGHT (CONV1_HEIGHT / POOL_SIZE)
#define POOL1_WIDTH (CONV1_WIDTH / POOL_SIZE)
#define NUM_FILTERS 4

typedef uint32_t data_t;



void conv1(int width, int height, hls::stream<data_t> &src_img, hls::stream<data_t> &dst_img);
void pool1(int width, int height, hls::stream<data_t> &in_pl1, hls::stream<data_t> &out_pl1);
void full(hls::stream<data_t> &full_in, hls::stream<data_t> &full_out);

#endif
