#include "filter.h"
#include <iostream>




int main() {


    data_t output[NUM_FILTERS][CONV1_HEIGHT][CONV1_WIDTH];

    hls::stream<data_t> src_img_strm("src_img_strm");
    hls::stream<data_t> dut_img_strm("dut_img_strm");

    // Generate the source image with a fixed test pattern - checker-board
    for (int i = 0; i < IMG_HEIGHT; i++) {
        for (int j = 0; j < IMG_WIDTH; j++) {
            data_t pix_val = i * IMG_WIDTH + j;
            src_img_strm << pix_val;
        }
    }

    // Perform convolution
    filter(IMG_WIDTH, IMG_HEIGHT, src_img_strm, dut_img_strm);

    // Collect the result into the output array
    while (!dut_img_strm.empty()) {
        data_t value = dut_img_strm.read();
        std::cout << value << "\t";
    }
    // for (int i = 0; i < CONV1_HEIGHT ;i++) {
    //     for (int j = 0; j < CONV1_WIDTH;j++) {
    //         for(int m=0;m<NUM_FILTERS;m++){
    //         dut_img_strm >> output[m][i][j];
    //         }
    //     }
    // }
    // for(int m=0;m<NUM_FILTERS;m++){
    // 	std::cout <<"num:";
    //     for (int i = 0; i < CONV1_HEIGHT ;i++) {
    //         for (int j = 0; j < CONV1_WIDTH; j++) {
    //             std::cout << output[m][i][j] << "\t";
    //         }
    //         std::cout << std::endl;
    //     }
    //     std::cout << std::endl;
    // }
    return 0;
}
