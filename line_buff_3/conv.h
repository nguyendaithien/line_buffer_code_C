#ifndef CONV_H
#define CONV_H

#include <stdio.h>
#include <stdint.h>


const int IMAGE_WIDTH= 8;
const int IMAGE_HIGHT= 8;
const int IMAGE_SIZE = 8;
const int KERNEL_SIZE =3;
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

void convolution(int image[IMAGE_HIGHT][IMAGE_WIDTH], int window_buffer[KERNEL_SIZE][KERNEL_SIZE], int line_buffer_0[IMAGE_WIDTH], int line_buffer_1[IMAGE_WIDTH], int line_buffer_2[IMAGE_WIDTH], int output[IMAGE_HIGHT - 2][IMAGE_WIDTH - 2]) ;
int process(int kernel[KERNEL_SIZE][KERNEL_SIZE], int window_buffer[KERNEL_SIZE][KERNEL_SIZE]); 
void init(int image[IMAGE_HIGHT][IMAGE_WIDTH], int window_buffer[KERNEL_SIZE][KERNEL_SIZE], int line_buffer_0[IMAGE_WIDTH], int line_buffer_1[IMAGE_WIDTH], int line_buffer_2[IMAGE_WIDTH]);
void print_line_buffer(int LineBuffer[IMAGE_WIDTH]);
void print_window_buffer(int window_buffer[KERNEL_SIZE][KERNEL_SIZE]);
void print_output(int output[IMAGE_HIGHT - 2][IMAGE_WIDTH - 2]);
#endif
