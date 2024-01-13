#ifndef CONV_H
#define CONV_H

#include <stdio.h>
#include <stdint.h>
#include <hls_stream.h>
#include <assert.h>


#define IMAGE_WIDTH= 8;

#define IMAGE_HIGHT= 8;
#define IMAGE_SIZE = 8;
#define KERNEL_SIZE = 3;

#define TEST_IMAGE_ROWS 15
#define TEST_IMAGE_COLS 15

int kernel[3][3] = 
	{{ 1,0,1},
	 { 1,0,1},
	 {1,0,1}
	};

int image[IMAGE_SIZE][IMAGE_SIZE]= 
       {{1,  2,  3,  4,  5,  6,  7,  8}, 
        {9, 10, 11, 12, 13, 14, 15, 16},
        {17, 18, 19, 20, 21, 22, 23, 24},
        {25, 26, 27, 28, 29, 30, 31, 32},
        {33, 34, 35, 36, 37, 38, 39, 40},
        {41, 42, 43, 44, 45, 46, 47, 48},
        {49, 50, 51, 52, 53, 54, 55, 56},
        {57, 58, 59, 60, 61, 62, 63, 64} 
  };  

void convolution(int image[IMAGE_HIGHT][IMAGE_WIDTH], int output[IMAGE_HIGHT - 2][IMAGE_WIDTH - 2]) ;
void filter3x3_orig( const int image[IMAGE_HIGHT][IMAGE_WIDTH], const int output[IMAGE_HIGHT - 2][IMAGE_WIDTH - 2]);
#endif
