// full_test.cpp
#include "full.h"
#include <iostream>
#include <hls_stream.h>
#include "defines.h"
#include "weights.h"
int main() {

    hls::stream<data_t> src_img("src_img");
    hls::stream<data_t> stream_out("stream_out");

 
        for (int i = 0; i < IMG_HEIGHT; i++) {
            for (int j = 0; j < IMG_WIDTH; j++) {
                src_img << img[i*IMG_WIDTH+j];
            }
        }

    // for(int n=0;n<NUM_FILTERS;n++){
    //     for (int i = 0; i < CONV1_HEIGHT; i++) {
    //         for (int j = 0; j < CONV1_WIDTH; j++) {
    //             data_t pix_val = (i * CONV1_WIDTH + j);
    //             src_img << pix_val;
    //         }
    //     }
    // }
    

    full(src_img,stream_out);


        // In ra các phần tử của stream_out
        while (!stream_out.empty()) {
            data_t value = stream_out.read();
            std::cout << value << "\t";
        }

    return 0;
}
