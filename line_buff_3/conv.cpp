#include<stdio.h>
#include"conv.h"

//int image[IMAGE_SIZE][IMAGE_SIZE]= 
//       {{1,  2,  3,  4,  5,  6,  7,  8}, 
//        {9, 10, 11, 12, 13, 14, 15, 16},
//        {17, 18, 19, 20, 21, 22, 23, 24},
//        {25, 26, 27, 28, 29, 30, 31, 32},
//        {33, 34, 35, 36, 37, 38, 39, 40},
//        {41, 42, 43, 44, 45, 46, 47, 48},
//        {49, 50, 51, 52, 53, 54, 55, 56},
//        {57, 58, 59, 60, 61, 62, 63, 64} 
//  };  
void print_line_buffer( int LineBuffer[IMAGE_WIDTH] ){
  for( int i = 0 ; i < IMAGE_WIDTH ; i++ ) { 
    printf("%d  ", LineBuffer[i]);
    }   
    printf("\n");
  }

void print_window_buffer( int window_buffer[KERNEL_SIZE][KERNEL_SIZE] ){
  printf("sliding window \n");
  for( int  i = 0; i < KERNEL_SIZE; i++) {
    for( int j = 0 ; j < KERNEL_SIZE; j++){
      printf("%d  ", window_buffer[i][j]);
    }   
    printf("\n");
  }
}
void print_output( int output[IMAGE_HIGHT - 2][IMAGE_WIDTH - 2] ){
  printf("ma tran output: \n");
  for( int  i = 0; i < IMAGE_HIGHT - 2; i++) {
    for( int j = 0 ; j < IMAGE_WIDTH - 2; j++){
      printf("%d  ", output[i][j]);
    }   
    printf("\n");
  }
}

int process(int kernel[KERNEL_SIZE][KERNEL_SIZE], int window_buffer[KERNEL_SIZE][KERNEL_SIZE]) {
    int sum = 0;
    for (int m = 0; m < KERNEL_SIZE; ++m) {
        for (int n = 0; n < KERNEL_SIZE; ++n) {
            sum += window_buffer[m][n] * kernel[m][n];
        }
    }
		return sum;
}
void init_line_buffer(int image[IMAGE_HIGHT][IMAGE_WIDTH], int line_buffer_0[IMAGE_WIDTH], int line_buffer_1[IMAGE_WIDTH], int line_buffer_2[IMAGE_WIDTH]){
  for( int i = 0 ; i < 2 ; i++ ) { 
    for( int j = 0 ; j < IMAGE_WIDTH; j++ ) { 
      line_buffer_0[j] = line_buffer_1[j];
      line_buffer_1[j] = line_buffer_2[j];
      line_buffer_2[j] = image[i][j];
   }    
	}
}
 
void init_window_buffer(int image[IMAGE_HIGHT][IMAGE_WIDTH], int window_buffer[KERNEL_SIZE][KERNEL_SIZE],int line_buffer_0[IMAGE_WIDTH], int line_buffer_1[IMAGE_WIDTH], int line_buffer_2[IMAGE_WIDTH]){
				window_buffer[0][0] = 0;
        window_buffer[1][0] = 0;
        window_buffer[2][0] = 0;
        window_buffer[0][1] = line_buffer_0[0];
        window_buffer[1][1] = line_buffer_1[0];
        window_buffer[2][1] = line_buffer_2[0];
        window_buffer[0][2] = line_buffer_0[1];
        window_buffer[1][2] = line_buffer_1[1];
        window_buffer[2][2] = line_buffer_2[1];
}
void setup(int window_buffer[KERNEL_SIZE][KERNEL_SIZE], int line_buffer_0[IMAGE_WIDTH], int line_buffer_1[IMAGE_WIDTH], int line_buffer_2[IMAGE_WIDTH]){
	for( int i = 0 ; i < 3; i++ ) {
			window_buffer[0][i] = line_buffer_0[i];
			window_buffer[1][i] = line_buffer_1[i];
			window_buffer[2][i] = line_buffer_2[i];
	}
}
void convolution(int image[IMAGE_HIGHT][IMAGE_WIDTH],int output[IMAGE_HIGHT - 2][IMAGE_WIDTH - 2]) {
 int window_buffer[KERNEL_SIZE][KERNEL_SIZE];
 int line_buffer_0[IMAGE_WIDTH];
 int line_buffer_1[IMAGE_WIDTH];
 int line_buffer_2[IMAGE_WIDTH];

  init_line_buffer(image, line_buffer_0, line_buffer_1, line_buffer_2);
  for( int i = 2 ; i < IMAGE_HIGHT; i++ ) { 
    for( int j = 0 ; j < IMAGE_WIDTH; j++ ) { 
      line_buffer_0[j] = line_buffer_1[j];
      line_buffer_1[j] = line_buffer_2[j];
      line_buffer_2[j] = image[i][j];
    }   
  init_window_buffer( image, window_buffer, line_buffer_0, line_buffer_1, line_buffer_2);
    print_line_buffer( line_buffer_0);
    print_line_buffer( line_buffer_1);
    print_line_buffer( line_buffer_2);
    printf("\n");
      for( int b = 0; b < IMAGE_WIDTH - 2  ; b ++) {
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
				print_window_buffer(window_buffer);
				output[i-2][b] = process(kernel, window_buffer);
      }   
}
		print_output(output);
}

int main() {
	int output[IMAGE_HIGHT - 2][IMAGE_WIDTH - 2];
  convolution( image, output);
  return 0;
}


