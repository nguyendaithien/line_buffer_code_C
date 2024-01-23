
#include"filter.h"

template<typename T>
void sp_conv(int channels, int width, int height, hls::stream<T> &src,T ker[NUM_FILTERS_1][K][K], hls::stream<T> &dst) {
        T linebuf[channels][K - 1][IMG_WIDTH];
        #pragma HLS ARRAY_PARTITION variable=linebuf complete dim=1
        T win[channels][K][K];
        #pragma HLS ARRAY_PARTITION variable=win complete dim=0
        #pragma HLS ARRAY_PARTITION variable=ker complete dim=0
        #pragma HLS INLINE // Into a DATAFLOW region
        ImgH:for (int img_row = 0; img_row < height; img_row++) {
            ImgW:for (int img_col = 0; img_col < width; img_col++) {
                T data[num_filters] = {0};
                CHANNELS:for(int cnt_channels = 0;cnt_channels <channels;cnt_channels++){
                    #pragma HLS DEPENDENCE variable=linebuf inter false 
                    #pragma HLS PIPELINE
                    T in_val = src.read();
                    // Shift values in line buffer vertically
                    ShiftLineBuffer:for (int i = 0; i < K ; i++) {
                        #pragma HLS PIPELINE
                        T temp = (i < K - 1) ? linebuf[channels][i][img_col] : in_val;
                        linebuf[channels][i-1][img_col] = temp;
                        }

                    if (img_row >= K - 1){

                    // Shift values in the window horizontally
                    
                    ShiftWindowH:for (int win_row = 0; win_row < K; win_row++) {
                        ShiftWindowW:for (int win_col = 0; win_col < K; win_col++) {
                            #pragma HLS PIPELINE
                                    win[channels][win_row][win_col] = (win_col < K - 1) ? win[channels][win_row][win_col + 1] : in_val;
                            }
                        }
                    }
                    
                    // Convolution operation q
                    Filters:for (int num_filters = 0; num_filters < NUM_FILTERS_1; num_filters++) {
                        Conv:if (img_col >= K - 1) {
                                ConvH:for (int win_row = 0; win_row < K; win_row++) {
                                    ConvW:for (int win_col = 0; win_col < K; win_col++) {
                                        #pragma HLS PIPELINE
                                        data[num_filters] += win[channels][win_row][win_col] * ker[num_filters][win_row][win_col];
                                    }
                                }
                        //   dst << data;
                        }
                    }
                }
                // 
                if (img_row >= K - 1 ){
                    Conv:if (img_col >= K - 1) {  
                        Filters:for (int num_filters = 0; num_filters < NUM_FILTERS_1; num_filters++) {
                        dst << data[num_filters];
                    }
                }
            }
        }
    }
}


void filter(int channels, int width, int height, hls::stream<data_t> &src_img, hls::stream<data_t> &dst_img) {
    #pragma HLS INLINE
    #pragma HLS DATAFLOW

     data_t filters[NUM_FILTERS_1][K][K] = {
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

   sp_conv<data_t>(channels, height, src_img, filters, dst_img);

}

