

#ifndef CONV2_H
#define CONV2_H

#include <hls_stream.h>
#include <stdio.h>
#include <stdint.h>

#define IMG_HEIGHT 8
#define IMG_WIDTH 8
#define K 3
#define CONV1_HEIGHT IMG_HEIGHT 
#define CONV1_WIDTH IMG_WIDTH
#define POOL_SIZE 2
#define POOL1_HEIGHT (CONV1_HEIGHT / POOL_SIZE)
#define POOL1_WIDTH (CONV1_WIDTH / POOL_SIZE)
#define NUM_FILTERS_1 4
#define CHANNELS_CONV1  1
#define CHANNELS_CONV2  NUM_FILTERS_1

typedef int data_t;

// static data_t linebuf[K - 1][IMG_WIDTH];
// static data_t win[K][K];


// data_t img_array[IMG_HEIGHT][IMG_WIDTH];
// data_t pool_buf[CONV1_WIDTH];
// data_t pool_win[K - 1][K - 1];


// Convolution function

void filter(int channels,int  width, int height, hls::stream<data_t> &src_img, hls::stream<data_t> &dst_img);


#endif