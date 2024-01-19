#include"full.h"
#include <iostream>
#include <hls_stream.h>

template<typename T>
void sp_conv(int width, int height, hls::stream<T> &src,T ker[NUM_FILTERS][K][K], hls::stream<T> &dst) {
    T linebuf[K - 1][IMG_WIDTH];
    #pragma HLS ARRAY_PARTITION variable=linebuf complete dim=1
    T win[K][K];
    #pragma HLS ARRAY_PARTITION variable=win complete dim=0
    #pragma HLS ARRAY_PARTITION variable=ker complete dim=0
    #pragma HLS INLINE // Into a DATAFLOW region

     ImgH:for (int img_row = 0; img_row < height; img_row++) {
        ImgW:for (int img_col = 0; img_col < width; img_col++) {
            #pragma HLS DEPENDENCE variable=linebuf inter false 
            #pragma HLS PIPELINE
            T temp;
            T in_val = src.read();

            if (img_row >= K - 1){

            // Shift values in the window horizontally
            
             ShiftWindowH:for (int win_row = 0; win_row < K; win_row++) {
                 ShiftWindowW:for (int win_col = 0; win_col < K; win_col++) {
                    #pragma HLS PIPELINE
                    if (win_row < K - 1) {
                        win[win_row][win_col] = (win_col < K - 1) ? win[win_row][win_col + 1] : linebuf[win_row][img_col];
                    } else if (win_row == K - 1) {
                        win[win_row][win_col] = (win_col < K - 1) ? win[win_row][win_col + 1] : in_val;
                    }
                }
            }
            
            // Convolution operation
            Filters:for (int num_filters = 0; num_filters < NUM_FILTERS; num_filters++) {
                Conv:if (img_col >= K - 1) {
                    T data = 0;
                    ConvH:for (int win_row = 0; win_row < K; win_row++) {
                        ConvW:for (int win_col = 0; win_col < K; win_col++) {
                            #pragma HLS PIPELINE
                            data += win[win_row][win_col] * ker[num_filters][win_row][win_col];
                        }
                    }
                    dst << data;
                }
            }
        }

            // Shift values in line buffer vertically
            ShiftLineBuffer:for (int i = 0; i < K ; i++) {
                #pragma HLS PIPELINE
                temp = (i < K - 1) ? linebuf[i][img_col] : in_val;
                linebuf[i-1][img_col] = temp;
            }
        }
    }
}

void conv1(int width, int height, hls::stream<data_t> &src_img, hls::stream<data_t> &dst_img) {
    #pragma HLS DATAFLOW
    data_t filters[NUM_FILTERS][K][K] = {
    {{1, 0, 1},
     {1, 0, 1},
     {1, 0, 1}},

    {{0, 1, 0},
     {1, 1, 1},
     {0, 1, 0}},

    {{1, 1, 1},
     {1, 0, 1},
     {1, 1, 1}},

    {{0, 1, 0},
     {1, 0, 1},
     {0, 1, 0}}
};

   sp_conv<data_t>(width, height, src_img, filters, dst_img);

}

void pool1(int width, int height, hls::stream<data_t> &in_pl1, hls::stream<data_t> &out_pl1) {
    data_t pool_buf[NUM_FILTERS][CONV1_WIDTH];
    data_t pool_win[NUM_FILTERS][K - 1][K - 1];
    
    for (int pool_row = 0; pool_row < height; pool_row++) {
        for (int pool_col = 0; pool_col < width; pool_col++) {
            #pragma HLS PIPELINE
            for (int num_filters = 0; num_filters < NUM_FILTERS; num_filters++) {
                data_t temp = 0;
                data_t in_pool_val = in_pl1.read();
                
                if (pool_row >= K - 2) {
                    for (int pool_win_row = 0; pool_win_row < POOL_SIZE; pool_win_row++) {
                        for (int pool_win_col = 0; pool_win_col < POOL_SIZE; pool_win_col++) {
                            #pragma HLS PIPELINE
                            if (pool_win_row < K - 2) {
                                pool_win[num_filters][pool_win_row][pool_win_col] = (pool_win_col < K - 2) ? pool_win[num_filters][pool_win_row][pool_win_col + 1] : pool_buf[num_filters][pool_col];
                            } else if (pool_win_row == K - 2) {
                                pool_win[num_filters][pool_win_row][pool_win_col] = (pool_win_col < K - 2) ? pool_win[num_filters][pool_win_row][pool_win_col + 1] : in_pool_val;
                            }
                        }
                    }

                    if (pool_col % (K - 1) == 1 && pool_row % (K - 1) == 1) {
                        for (int pool_win_row = 0; pool_win_row < POOL_SIZE; pool_win_row++) {
                            for (int pool_win_col = 0; pool_win_col < POOL_SIZE; pool_win_col++) {
                                #pragma HLS PIPELINE
                                if (temp <= pool_win[num_filters][pool_win_row][pool_win_col]) {
                                    temp = pool_win[num_filters][pool_win_row][pool_win_col];
                                }
                            }
                        }
                        out_pl1 << temp;
                    }
                }
                pool_buf[num_filters][pool_col] = in_pool_val;
            }
        }
    }
}

void full(hls::stream<data_t> &full_in,hls::stream<data_t> &full_out){
    
    hls::stream<data_t> conv1_out("conv1_out");
    conv1(IMG_WIDTH, IMG_HEIGHT,full_in, conv1_out);
    //sp_conv1<data_t>(IMG_WIDTH, IMG_HEIGHT, src_img, filters, conv1_out);
        //     while (!conv1_out.empty()) {
        //     data_t value = conv1_out.read();
        //     std::cout << value << "\t";
        // }

    // for(int n=0;n<NUM_FILTERS;n++){
    //     for (int i = 0; i < CONV1_HEIGHT; i++) {
    //         for (int j = 0; j < CONV1_WIDTH; j++) {
    //             data_t pix_val = (i * CONV1_WIDTH + j);
    //             conv1_out << pix_val;
    //         }
    //     }
    // }

   pool1(CONV1_WIDTH,CONV1_HEIGHT,conv1_out,full_out);
    //pool1(CONV1_WIDTH,CONV1_HEIGHT,full_in,full_out);

}
