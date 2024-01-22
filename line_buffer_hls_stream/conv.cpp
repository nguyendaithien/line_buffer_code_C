#include<stdio.h>
#include"conv.h"
#include"activation.h"


data_t bias_conv1[16]={0.000998553, 0.08829625,0.07215472,0.04322089,0.000511708,-0.000338764,
    0.33033448,0.08273578,0.029430622,0.032025397,0.000527582,0.29062834,0.07009841,
    -0.000225344,0.000493296,0.050996434};

template<typename T, int K, int NUMBER_KERNEL>
static void convolution( int padding, int width, int hight ,hls::stream<T> &image,const T *kernel,hls::stream<T> &output) {
 int conv_size = K;
 int padding_size = padding ;
   
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
Push_pixel: for( int i = 0 ; i < hight + padding_size; i++ ) {
//#pragma HLS DEPENDENCE variable=line_buffer_0 inter false
//#pragma HLS DEPENDENCE variable=line_buffer_1 inter false
//#pragma HLS DEPENDENCE variable=line_buffer_2 inter false
//#pragma HLS PIPELINE
    if(i<hight){
    for( int j = 0 ; j < width; j++ ) { 
      line_buffer_0[j] = line_buffer_1[j];
      line_buffer_1[j] = line_buffer_2[j];
      line_buffer_2[j] = image.read();
    }
    }
    if(i > 1){
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
    }
 // shift window to right
Shift_win_right:for( int b = -(padding_size) ; b < width-2+padding_size ; b++) {
//#pragma HLS DEPENDENCE variable=line_buffer_0 inter false
//#pragma HLS DEPENDENCE variable=line_buffer_1 inter false
//#pragma HLS DEPENDENCE variable=line_buffer_2 inter false
//#pragma HLS PIPELINE
   if(i > 0){
    if(i == 1 || i > hight -2 + padding_size ) {
        window_buffer[0][0] = 0;
        window_buffer[1][0] = 0;
        window_buffer[2][0] = 0;
        window_buffer[0][1] = 0;
        window_buffer[1][1] = 0;
        window_buffer[2][1] = 0;
        window_buffer[0][2] = 0;
        window_buffer[1][2] = 0;
        window_buffer[2][2] = 0;
    }
    else if( i>1 && b >= 0){
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
    }	


// convolution caculate    
T sum = 0;
      for( int num_filters = 0; num_filters < NUMBER_KERNEL; num_filters ++) {
 COnv:for (int m = 0; m < K; ++m) {
//#pragma HLS PIPELINE
//#pragma HLS UNROLL
      for (int n = 0; n < K; ++n) {
         sum += window_buffer[m][n] * kernel[num_filters*9 + m*3+n];
        }
	 }
     // sum += bias_conv1[num_filters];
	if(b == -(padding_size)  || b == width - 3 + padding_size){
		output << 0;
	    }
	else{
	output << relu(sum);
	}
      }
   }
 }
}
}


template<typename T, int K>
static void max_pooling(int width, int hight, hls::stream<T> &input, hls::stream<T> &output) {
    //const int pool_size = K - 1;  // Pooling window size

    T line_buffer_0[IMAGE_WIDTH];
    T line_buffer_1[IMAGE_WIDTH];
    T window_buffer[K-1][K-1];

    for ( int i = 0 ; i < hight ; i ++ ) { 
	    for ( int j = 0 ; j < width ; j++ ) {
		    line_buffer_0[j] = line_buffer_1[j];
		    line_buffer_1[j] = input.read();
	    }
    if(i%2 == 1 ){
    for(int a = 0; a < (width)/(K-1); a++){
          window_buffer[0][0] = line_buffer_0[a*2];
          window_buffer[0][1] = line_buffer_0[a*2+1];
          window_buffer[1][0] = line_buffer_1[a*2];
          window_buffer[1][1] = line_buffer_1[a*2+1];

	  T max_val = window_buffer[0][0];
		 max_val = ( max_val > window_buffer[0][1])?max_val:window_buffer[0][1];
		 max_val = ( max_val > window_buffer[1][0])?max_val:window_buffer[1][0];
		 max_val = ( max_val > window_buffer[1][1])?max_val:window_buffer[1][1];

		 output<<max_val;
		    }
                }
	    }
    }




void filter_orig( int padding, int width, int hight,hls::stream<int> &image,hls::stream<int> &output) {
//#pragma HLS INTERFACE axis port = image 
//#pragma HLS INTERFACE axis port = output
//#pragma HLS INLINE
//#pragma DATAFLOW
	const int kernel[9*16] = {1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1};
 convolution<int,3,16>(padding, width, hight, image, kernel, output);
 //max_pooling<int,3>(width, hight, output, output_pooling);
}
