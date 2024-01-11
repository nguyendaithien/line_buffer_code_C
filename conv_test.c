#include "conv_top.h"

int window[KER_HEIGHT][KER_WIDTH];
int buffer[KER_HEIGHT - 1][IMG_WIDTH];
int output[CONV_HEIGHT][CONV_WIDTH];
pixel kernel[KER_HEIGHT][KER_WIDTH] = {
    {1, 0, 1},
    {1, 0, 1},
    {1, 0, 1}
};
pixel img[IMG_HEIGHT * IMG_WIDTH] = {
    0, 1, 2, 3, 4, 5, 6, 7,
    8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23,
    24, 25, 26, 27, 28, 29, 30, 31,
    32, 33, 34, 35, 36, 37, 38, 39,
    40, 41, 42, 43, 44, 45, 46, 47,
    48, 49, 50, 51, 52, 53, 54, 55,
    56, 57, 58, 59, 60, 61, 62, 63
};


int main() {
    // Gọi hàm process
    process(img, kernel, window, buffer, output);
        // In giá trị của output array
    printf("Output array:\n");
    for (int i = 0; i < CONV_HEIGHT; i++) {
        for (int j = 0; j < CONV_WIDTH; j++) {
            printf("%d ", output[i][j]);
        }
        printf("\n");
    }
    return 0;
}
