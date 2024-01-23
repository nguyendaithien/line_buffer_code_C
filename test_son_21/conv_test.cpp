#include "conv.h"
#include <iostream>
#include <hls_stream.h>
#include "defines.h"
#include "weights.h"

int main() {

    data_t output[CONV1_HEIGHT][CONV1_WIDTH];
    //data_t m=0.000998553;
    hls::stream<data_t> src_img_strm("src_img_strm");
    hls::stream<data_t> dut_img_strm("dut_img_strm");

    // Generate the source image with a fixed test pattern - checker-board
    for (int i = 0; i < IMG_HEIGHT; i++) {
        for (int j = 0; j < IMG_WIDTH; j++) {
            src_img_strm << img[i*IMG_WIDTH+j];
        }
    }
    // for (int i = 0; i < IMG_HEIGHT; i++) {
    // 	for (int j = 0; j < IMG_WIDTH; j++) {
    //         int c = i*IMG_WIDTH+j;
    //         if(c > 195 && c < 225){
    //         // std::cout << "img:"
    //         std::cout << "img:" << img[c]<< "\t";
    //         }
    //     }
    //     std::cout << std::endl;
    // }

    //Perform convolution
    conv(1, IMG_WIDTH, IMG_HEIGHT, src_img_strm, dut_img_strm);
    int cnt_conv_main =0;
    // Collect the result into the output array
    
        std::cout << "filter:";
    for (int i = 0; i < IMG_HEIGHT; i++) {
    	for (int j = 0; j < IMG_WIDTH; j++) {
            for(int m =0;m <NUM_FILTERS; m++){
            data_t value = dut_img_strm.read();
            //std::cout << value << "\t";
            // dut_img_strm >> output[i][j];
             cnt_conv_main ++;
               // if(cnt_conv_main> 28 && cnt_conv_main <57){
                std::cout << value << "\t";
            //}
            // std::cout << output[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    }
    // while (!dut_img_strm.empty()) {
    //     data_t value = dut_img_strm.read();
    //     std::cout << value << "\t";
    //     cnt_conv_main ++;
    // }
        std::cout << "cnt_conv_main:" <<cnt_conv_main << "\n";

    return 0;
}
