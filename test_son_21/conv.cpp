#include "conv.h"
#include <iostream>
#include <hls_stream.h>
#include "defines.h"
#include "activation.h"

int count_img =0;
int count_conv1 =0;

data_t bias_conv1[16]={0.000998553, 0.08829625,0.07215472,0.04322089,0.000511708,-0.000338764,
    0.33033448,0.08273578,0.029430622,0.032025397,0.000527582,0.29062834,0.07009841,
    -0.000225344,0.000493296,0.050996434};

// Convolution function
template<typename T>
void sp_conv(int padding, int width, int height, hls::stream<T> &src, T ker[NUM_FILTERS][K][K], hls::stream<T> &dst) {
    height = height + 2*padding;
    width  = width + 2*padding;
    T linebuf[K - 1][IMG_HEIGHT+2];
    #pragma HLS ARRAY_PARTITION variable=linebuf complete dim=1
    T win[K][K];
    #pragma HLS ARRAY_PARTITION variable=win complete dim=0
    #pragma HLS ARRAY_PARTITION variable=ker complete dim=0
    #pragma HLS INLINE // Into a DATAFLOW region

    ImgH: for (int img_row = 0; img_row < height; img_row++) {
        ImgW: for (int img_col = 0; img_col < width; img_col++) {
            // count_img ++;
            //#pragma HLS DEPENDENCE variable=linebuf inter false 
            //#pragma HLS PIPELINE
            T in_val;
            if (img_row == 0 || img_col == 0 || img_row == (IMG_HEIGHT+1) || img_col == (IMG_WIDTH+1)) {
                in_val = 0;
            } else {
                in_val = src.read();
            }

            if (img_row >= K - 1) {
                // Shift values in the window horizontally
                ShiftWindowH: for (int win_row = 0; win_row < K; win_row++) {
                    ShiftWindowW: for (int win_col = 0; win_col < K; win_col++) {
                     //   #pragma HLS PIPELINE
                        if (win_row < K - 1) {
                            win[win_row][win_col] = (win_col < K - 1) ? win[win_row][win_col + 1] : linebuf[win_row][win_col];
                        } else if (win_row == K - 1) {
                            win[win_row][win_col] = (win_col < K - 1) ? win[win_row][win_col + 1] : in_val;
                        }
                    }
                }
            Filters:for (int num_filters = 0; num_filters < NUM_FILTERS; num_filters++) {
                // Convolution operation
                Conv: if (img_col >= K - 1) {
                    data_t data = 0;
                    ConvH: for (int win_row = 0; win_row < K; win_row++) {
                        ConvW: for (int win_col = 0; win_col < K; win_col++) {
                            //#pragma HLS PIPELINE
                            data += win[win_row][win_col] * ker[num_filters][win_row][win_col];
                        }
                    }
                    data += bias_conv1[num_filters];  
                    dst << relu(data);
                    count_conv1 ++;
                }
            }
        }

            // Shift values in line buffer vertically
            ShiftLineBuffer: for (int i = 0; i < K - 1; i++) {
               // #pragma HLS PIPELINE
                T temp = (i < K - 2) ? linebuf[i + 1][img_col] : in_val;
                linebuf[i][img_col] = temp;
            }
           // dst << in_val;
        }
    }
    // std::cout << "count_img:" <<count_img << "\n";
    // std::cout << "count_conv1:" <<count_conv1<<"\n";
}

void conv(int padding, int width, int height, hls::stream<data_t> &src_img, hls::stream<data_t> &dst_img) {
    // #pragma HLS INLINE
    // #pragma HLS DATAFLOW
    
    data_t kernel[16][3][3] = {{{0.26878357, 0.13682392, 0.14143483},{0.041244872, -0.056742575, 0.07255097},{-0.20083077, -0.06319027, 0.19562164}},
                              {{0.262159, 0.048926,0.113912},{0.134031, 0.049518, -0.01861},{0.233836,0.225131,0.216009}},
                              {{0.170158, 0.323119, 0.083648},{-0.0418,-0.01711,0.104751},{0.092267,-0.04681,0.068806}},
                              {{-0.07462,-0.00294,0.052896},{0.080241,0.201689,0.012011},{0.093008,0.165827,0.066039}},
                              {{0.144896,0.365466,0.175033},{0.133105,-0.05184,0.028626},{-0.12203,-0.08221,-0.21684}},
                              {{0.053726,-0.16872,-0.20054},{0.175617,-0.01545,-0.19214},{0.373429,0.280117,-0.18149}},
                              {{0.152278, -0.13943,0.045464},{-0.22118,-0.18075,-0.10976},{0.133282,-0.08897,-0.01688}},
                              {{-0.30172,-0.44044,-0.02828},{0.410465,-0.18189,0.471532},{-0.13206,-0.4399,-0.18287}},
                              {{0.110461, -0.0077,0.019517},{0.515985,-0.02636,0.061304},{0.019339,0.022866,0.124711}},
                              {{0.136073,0.120423,0.214156},{-0.00825,0.077444,0.220693},{0.010431,0.052618,0.044809}},
                              {{-0.23956,-0.29566,-0.29709},{-0.13178, 0.143908,0.090842},{-0.58858,-0.03457,0.398524}},
                              {{0.143174,-0.03095,-0.24716},{0.045321,-0.01908,-0.17395},{-0.10383,-0.08255,-0.16143}},
                              {{-0.51567,-0.29,-0.03668},{0.225079,0.018415,-0.07848},{0.291674,0.216459,0.10563}},
                              {{-0.43961,-0.02349,0.056404},{-0.24579,0.030505,0.272878},{-0.05315,0.191454,0.248561}},
                              {{-0.30465,0.135672,0.381617},{-0.22824,0.128932,0.206503},{-1.05318,-0.27693,-0.36825}},
                              {{0.092631,0.026808,0.078882},{-0.03647,0.607406,-0.02246},{-0.01523,0.162064,0.018575}}};



    sp_conv<data_t>(padding, width, height, src_img, kernel, dst_img);
}
