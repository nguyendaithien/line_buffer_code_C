#ifndef CONV_H
#define CONV_H

#include <stdio.h>
#include <stdint.h>
#include <hls_stream.h>
#include <assert.h>


#define IMAGE_WIDTH 8

#define IMAGE_HIGHT 8
#define IMAGE_SIZE  8
#define KERNEL_SIZE  3

#define TEST_IMAGE_ROWS 15
#define TEST_IMAGE_COLS 15


//void convolution(int image[IMAGE_HIGHT][IMAGE_WIDTH], int output[IMAGE_HIGHT - 2][IMAGE_WIDTH - 2]) ;
void filter3x3_orig( hls::stream<int> &image,hls::stream<int> &output );
#endif
