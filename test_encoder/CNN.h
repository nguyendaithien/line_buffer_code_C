#include<stdio.h>
#include<hls_stream.h>
#include<stdint.h>

using namespace std;
typedef double data_t;
// top module CNN
void CNN( int padding, int width, int hight,  hls::stream<double> &image, hls::stream<data_t> &output, hls::stream<data_t> &output_pooling_1,hls::stream<data_t> &output_conv2,hls::stream<data_t> &output_pooling2,hls::stream<data_t> &output_conv3,hls::stream<data_t> &output_pooling3 );


// relu function
static data_t relu(data_t a)
{
	return a > (data_t)0 ? a : (data_t)0;
}
//convolution function
template <typename INPUT_DATA_TYPE
         ,typename OUTPUT_DATA_TYPE
	 ,typename KERNEL_TYPE
	 ,typename PADDING_TYPE
	 ,int CONV_DATA_XSIZE
	 ,int CONV_DATA_YSIZE
	 ,int CONV_NUM_CHANNEL
	 ,int CONV_NUM_KERNEL
	 ,int CONV_DATA_OUT_XSIZE
	 ,int CONV_DATA_OUT_YSIZE
	 ,int KERNEL_XSIZE
	 ,int KERNEL_YSIZE
	 ,int CONV_STRICE
	 ,int CONV_PADDING_SIZE
	 >
void convolution( int padding, int width, int hight ,INPUT_DATA_TYPE bias[CONV_NUM_CHANNEL], hls::stream<INPUT_DATA_TYPE> &image,const KERNEL_TYPE *kernel,hls::stream<OUTPUT_DATA_TYPE> &output) {
 hight = CONV_DATA_YSIZE + 2*padding;
 width = CONV_DATA_XSIZE + 2*padding;
   
 INPUT_DATA_TYPE window_buffer[KERNEL_XSIZE][KERNEL_YSIZE];
 static INPUT_DATA_TYPE line_buffer_0[CONV_DATA_XSIZE];
 static INPUT_DATA_TYPE line_buffer_1[CONV_DATA_XSIZE];
 static INPUT_DATA_TYPE line_buffer_2[CONV_DATA_XSIZE];

// push pixel to 1 line buffer
Push_pixel: for( int i = 0 ; i < hight ; i++ ) {
    for( int j = 0 ; j < width; j++ ) { 
      line_buffer_0[j] = line_buffer_1[j];
      line_buffer_1[j] = line_buffer_2[j];
      if( i == 0 || i == hight - 1 || j == 0 || j == width - 1 ){
	      line_buffer_2[j] = 0;
      }
      else {
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
 // shift window to right
Shift_win_right:for( int b = 0 ; b < width - 2 ; b++) {
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
      for( int num_ker= 0 ; num_ker < CONV_NUM_KERNEL ; num_ker ++){
INPUT_DATA_TYPE sum = 0;
          for (int m = 0; m < KERNEL_XSIZE; m++) {
             for (int n = 0; n < KERNEL_YSIZE; n++) {
             sum += window_buffer[m][n] * kernel[  num_ker * CONV_NUM_KERNEL + m*3 + n];
            }
	  }
	  sum += bias[num_ker];
          output << relu(sum);
	}
		}
    }
  }
}

template<typename DATA_IN_TYPE
	,typename DATA_OUT_TYPE
	,int NUM_CHANNEL
        ,int DATA_IN_XSIZE
        ,int DATA_IN_YSIZE
        ,int DATA_OUT_XSIZE
        ,int DATA_OUT_YSIZE
	,int POOLING_SIZE
	,int STRICE_SIZE 
	>
static void max_pooling(int width, int hight, hls::stream<DATA_IN_TYPE> &input, hls::stream<DATA_OUT_TYPE> &output) {
    //const int pool_size = K - 1;  // Pooling window size

    DATA_IN_TYPE line_buffer_0[DATA_IN_XSIZE];
    DATA_IN_TYPE line_buffer_1[DATA_IN_XSIZE];
    DATA_IN_TYPE window_buffer[POOLING_SIZE][POOLING_SIZE];

    for( int num_fil1 = 0 ; num_fil1 < NUM_CHANNEL ; num_fil1++){
    for ( int i = 0 ; i < hight ; i ++ ) {
	    for ( int j = 0 ; j < width ; j++ ) {
		    line_buffer_0[j] = line_buffer_1[j];
		    line_buffer_1[j] = input.read();
	    }
    if(i%2 == 1 ){
    for(int a = 0; a < DATA_OUT_YSIZE ; a++){
          window_buffer[0][0] = line_buffer_0[a*2];
          window_buffer[0][1] = line_buffer_0[a*2+1];
          window_buffer[1][0] = line_buffer_1[a*2];
          window_buffer[1][1] = line_buffer_1[a*2+1];

	  DATA_IN_TYPE max_val = window_buffer[0][0];
		 max_val = ( max_val > window_buffer[0][1])?max_val:window_buffer[0][1];
		 max_val = ( max_val > window_buffer[1][0])?max_val:window_buffer[1][0];
		 max_val = ( max_val > window_buffer[1][1])?max_val:window_buffer[1][1];

		 output<<max_val;
		    }
                }
	    }
    }
}
// pooling function
//template<typename DATA_IN_TYPE
//	,typename DATA_OUT_TYPE
//	,int NUM_CHANNEL
//        ,int DATA_IN_XSIZE
//        ,int DATA_IN_YSIZE
//        ,int DATA_OUT_XSIZE
//        ,int DATA_OUT_YSIZE
//	,int POOLING_SIZE
//	,int STRICE_SIZE 
//	>
//void max_pooling(int width, int hight, hls::stream<DATA_IN_TYPE> &in_pl1, hls::stream<DATA_OUT_TYPE> &out_pl1) {
//    data_t pool_buf[NUM_CHANNEL][DATA_IN_XSIZE];
//    data_t pool_win[NUM_CHANNEL][POOLING_SIZE][POOLING_SIZE];
//    width = DATA_IN_XSIZE;
//    hight = DATA_IN_YSIZE;
//    int count_pool1 =0;
//    for (int pool_row = 0; pool_row < hight; pool_row++) {
//        for (int pool_col = 0; pool_col < width; pool_col++) {
//            for (int num_filters = 0; num_filters < NUM_CHANNEL; num_filters++) {
//                data_t temp = 0;
//                data_t in_pool_val = in_pl1.read();
//
//                if (pool_row >= POOLING_SIZE - 1 ) {
//                    for (int pool_win_row = 0; pool_win_row < POOLING_SIZE; pool_win_row++) {
//                        for (int pool_win_col = 0; pool_win_col < POOLING_SIZE; pool_win_col++) {
//                            if (pool_win_row < POOLING_SIZE - 1) {
//                                pool_win[num_filters][pool_win_row][pool_win_col] = (pool_win_col < POOLING_SIZE - 1) ? pool_win[num_filters][pool_win_row][pool_win_col + 1] : pool_buf[num_filters][pool_col];
//                            } else if (pool_win_row == POOLING_SIZE - 1) {
//                                pool_win[num_filters][pool_win_row][pool_win_col] = (pool_win_col <  POOLING_SIZE - 1) ? pool_win[num_filters][pool_win_row][pool_win_col + 1] : in_pool_val;
//                            }
//                        }
//                    }
//
//                    if (pool_col % POOLING_SIZE == 1 && pool_row % POOLING_SIZE == 1) {
//                        for (int pool_win_row = 0; pool_win_row < POOLING_SIZE; pool_win_row++) {
//                            for (int pool_win_col = 0; pool_win_col < POOLING_SIZE; pool_win_col++) {
//                                if (temp <= pool_win[num_filters][pool_win_row][pool_win_col]) {
//                                    temp = pool_win[num_filters][pool_win_row][pool_win_col];
//                                }
//                            }
//                        }
//                        out_pl1 << temp;
//                        count_pool1 ++;
//                    }
//                }
//                pool_buf[num_filters][pool_col] = in_pool_val;
//            }
//        }
//    }
//}







