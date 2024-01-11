#include "conv_top.h"

void init(pixel window_init[KER_HEIGHT][KER_WIDTH], pixel img_init[IMG_HEIGHT * IMG_WIDTH], pixel buffer_init[KER_HEIGHT - 1][IMG_WIDTH]) {
    // init window
    for (int i = 0; i < KER_HEIGHT; i++) {
        for (int j = 0; j < KER_WIDTH; j++) {
            window_init[i][j] = img_init[i * IMG_WIDTH + j];
        }
    }

    // init buffer
    uint8_t img_row, img_col;
    for (int img_row = 0; img_row < KER_HEIGHT - 1; img_row++) {
        for (int img_col = 0; img_col < IMG_WIDTH; img_col++) {
            buffer_init[img_row][img_col] = img_init[img_row * IMG_WIDTH + img_col];
        }
    }

    for (int img_col = 0; img_col < KER_WIDTH; img_col++) {
        buffer_init[0][img_col] = buffer_init[1][img_col];
        buffer_init[1][img_col] = img_init[(KER_HEIGHT - 1) * IMG_WIDTH + img_col];
    }
}

pixel pixel_weighted_average(pixel kernel[KER_HEIGHT][KER_WIDTH], pixel kern_sum, pixel kern_off, pixel window[KER_HEIGHT][KER_WIDTH]) {
    int out_temp = 0;

    // dot product
    for (int ker_row = 0; ker_row < KER_HEIGHT; ker_row++) {
        for (int ker_col = 0; ker_col < KER_WIDTH; ker_col++) {
            out_temp += window[ker_row][ker_col] * kernel[ker_row][ker_col];
        }
    }
    printf("out_temp: %d\n", out_temp);

    // update output, normalize and add offset
    return ((out_temp / kern_sum) + kern_off);
}

void process(pixel img_pr[IMG_HEIGHT * IMG_WIDTH], pixel kernel_pr[KER_HEIGHT][KER_WIDTH], pixel window_pr[KER_HEIGHT][KER_WIDTH], pixel buffer_pr[KER_HEIGHT - 1][IMG_WIDTH], pixel output_pr[CONV_HEIGHT][CONV_WIDTH]) {
    
    // Initialize the window and buffer
    init(window_pr, img_pr, buffer_pr);

    pixel ker_row, ker_col, img_col, img_row;
    pixel result = pixel_weighted_average(kernel_pr, 1, 0, window_pr);
    output_pr[0][0] = result;

    // Iterate through the image pixels
    for (int img_row = 2; img_row < IMG_HEIGHT; img_row++) {
        for (int img_col = (img_row == 2) ? 3 : 0; img_col < IMG_WIDTH; img_col++) {

            // Shift processing window
            for (int ker_row = 0; ker_row < KER_HEIGHT; ker_row++) {
                for (int ker_col = 0; ker_col < KER_WIDTH - 1; ker_col++) {
                    window_pr[ker_row][ker_col] = window_pr[ker_row][ker_col + 1];
                }
            }

            // Copy KER_HEIGHT - 1 values from line_buffer to processing window
            for (int ker_row = 0; ker_row < KER_HEIGHT - 1; ker_row++) {
                window_pr[ker_row][KER_WIDTH - 1] = buffer_pr[ker_row][img_col];
            }

            // Shift line buffer up
            for (int ker_row = 0; ker_row < KER_HEIGHT - 2; ker_row++) {
                buffer_pr[ker_row][img_col] = buffer_pr[ker_row + 1][img_col];
            }

            // Read new input pixel, update processing window, and line buffer
            pixel in_temp = img_pr[img_row * IMG_WIDTH + img_col];
            window_pr[KER_HEIGHT - 1][KER_WIDTH - 1] = in_temp;
            buffer_pr[KER_HEIGHT - 2][img_col] = in_temp;
              // save result
            if(img_col>1){
            // Call pixel_weighted_average
             result = pixel_weighted_average(kernel_pr, 1, 0, window_pr);
            // Save result to output array
            output_pr[img_row - 2][img_col - 2] = result;
            printf("Result at img[%d][%d]: %d\n", img_row - 2, img_col - 2, result);
            }
        }
    }
}
