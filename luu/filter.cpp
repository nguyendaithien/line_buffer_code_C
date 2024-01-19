
#include"filter.h"

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
            
            // Convolution operation q
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

void filter(int width, int height, hls::stream<data_t> &src_img, hls::stream<data_t> &dst_img) {
    #pragma HLS INLINE
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

