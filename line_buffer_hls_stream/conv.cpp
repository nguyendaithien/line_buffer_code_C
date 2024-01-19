#include<stdio.h>
#include"conv.h"

template<typename T, int K>
static void convolution( int width, int hight ,hls::stream<T> &image,const T kernel[NUMBER_FILTER][K][K],hls::stream<T> &output) {
 int conv_size = K;
 T window_buffer[conv_size][conv_size];
 static T line_buffer_0[IMAGE_WIDTH];
 static T line_buffer_1[IMAGE_WIDTH];
 static T line_buffer_2[IMAGE_WIDTH];

#pragma HLS ARRAY_PARTITION variable=line_buffer_0 dim=1 complete
#pragma HLS ARRAY_PARTITION variable=line_buffer_1 dim=1 complete
#pragma HLS ARRAY_PARTITION variable=line_buffer_2 dim=1 complete
#pragma HLS ARRAY_PARTITION variable=kernel dim=1 complete
// push pixel to 1 line buffer
//
Push_pixel: for( int i = 0 ; i < hight; i++ ) {
#pragma HLS DEPENDENCE variable=line_buffer_0 inter false
#pragma HLS DEPENDENCE variable=line_buffer_1 inter false
#pragma HLS DEPENDENCE variable=line_buffer_2 inter false
#pragma HLS PIPELINE
    for( int j = 0 ; j < width; j++ ) { 
      line_buffer_0[j] = line_buffer_1[j];
      line_buffer_1[j] = line_buffer_2[j];
      line_buffer_2[j] = image.read();
    }
    if(i>1){
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
Shift_win_right:for( int b = 0; b < width -2  ; b++) {
#pragma HLS DEPENDENCE variable=line_buffer_0 inter false
#pragma HLS DEPENDENCE variable=line_buffer_1 inter false
#pragma HLS DEPENDENCE variable=line_buffer_2 inter false
#pragma HLS PIPELINE
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
    T sum = 0;
    convolution:for (int m = 0; m < K; ++m) {
//#pragma HLS PIPELINE
#pragma HLS UNROLL
        for (int n = 0; n < K; ++n) {
            sum += window_buffer[m][n] * kernel[m*3+n];
        }
    }
	output << sum;
    }
	    }
}
}
void filter3x3_orig( int width, int hight,hls::stream<int> &image,hls::stream<int> &output) {

#pragma HLS INTERFACE axis port = image 
#pragma HLS INTERFACE axis port = output
#pragma HLS INLINE
#pragma DATAFLOW
	const int kernel[9] = {1,0,1,1,0,1,1,0,1};
 convolution<int,3>(int width, int hight, image,kernel,output);
}
