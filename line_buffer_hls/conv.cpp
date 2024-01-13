#include<stdio.h>
#include"conv.h"


template<typename T, int K>
static void convolution(int image[IMAGE_HIGHT][IMAGE_WIDTH],int output[IMAGE_HIGHT - 2][IMAGE_WIDTH - 2]) {
 int window_buffer[KERNEL_SIZE][KERNEL_SIZE];
 int line_buffer_0[IMAGE_WIDTH];
 int line_buffer_1[IMAGE_WIDTH];
 int line_buffer_2[IMAGE_WIDTH];

// push pixel to 1 line buffer
Push_pixel: for( int i = 0 ; i < IMAGE_HIGHT; i++ ) { 
    for( int j = 0 ; j < IMAGE_WIDTH; j++ ) { 
      line_buffer_0[j] = line_buffer_1[j];
      line_buffer_1[j] = line_buffer_2[j];
      line_buffer_2[j] = image[i][j];
    }   
		// initial window buffer
        window_buffer[0][0] = 0;
        window_buffer[1][0] = 0;
        window_buffer[2][0] = 0;
        window_buffer[0][1] = line_buffer_0[0];
        window_buffer[1][1] = line_buffer_1[0];
        window_buffer[2][1] = line_buffer_2[0];
        window_buffer[0][2] = line_buffer_0[1];
        window_buffer[1][2] = line_buffer_1[1];
        window_buffer[2][2] = line_buffer_2[1];

 // shift window to right
Shift_win_right:for( int b = 0; b < IMAGE_WIDTH - 2  ; b ++) {
        for( int n = 0 ; n < 3; n++) {
          window_buffer[n][0] = window_buffer[n][1];
          window_buffer[n][1] = window_buffer[n][2];
          if( n == 0) {
            window_buffer[n][2] = line_buffer_0[b+2];
          }
          if( n == 1) {
            window_buffer[n][2] = line_buffer_1[b+2];
          }
          if( n == 2) {
            window_buffer[n][2] = line_buffer_2[b+2];
          }
        }

// convolution caculate
				if( i >= 2 ){ 
    int sum = 0;
    convolution:for (int m = 0; m < KERNEL_SIZE; ++m) {
        for (int n = 0; n < KERNEL_SIZE; ++n) {
            sum += window_buffer[m][n] * kernel[m][n];
        }
    }
				output[i-2][b] = sum;
				}
      }   
}
		print_output(output);
}

void filter3x3_orig( int image[IMAGE_HIGHT][IMAGE_WIDTH],int output[IMAGE_HIGHT - 2][IMAGE_WIDTH - 2]) {

#pragma HLS INTERFACE m_axi port = image depth=8
#pragma HLS INTERFACE m_axi port = output depth=8

#pragma HLS INLINE
#pragma DATAFLOW

convulution(image,output);
}


