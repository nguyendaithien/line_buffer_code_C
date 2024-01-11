#ifndef CONV_TOP_H
#define CONV_TOP_H

#include <stdio.h>
#include <stdint.h>

typedef int pixel;

#define IMG_HEIGHT      8
#define IMG_WIDTH       8
#define KER_HEIGHT      3
#define KER_WIDTH       3
#define CONV_HEIGHT     (IMG_HEIGHT - 2 * (KER_HEIGHT / 2))
#define CONV_WIDTH      (IMG_WIDTH - 2 * (KER_WIDTH / 2))


void init(pixel window_init[KER_HEIGHT][KER_WIDTH], pixel img_init[IMG_HEIGHT * IMG_WIDTH],pixel line_buffer_0[IMG_WIDTH], pixel line_buffer_1[IMG_WIDTH], pixel line_buffer_2[IMG_WIDTH]);
void process(pixel img_pr[IMG_HEIGHT * IMG_WIDTH], pixel kernel_pr[KER_HEIGHT][KER_WIDTH], pixel window_pr[KER_HEIGHT][KER_WIDTH], pixel line_buffer_0[IMG_WIDTH],pixel line_buffer_1[IMG_WIDTH], pixel line_buffer_2[IMG_WIDTH], pixel output_pr[CONV_HEIGHT][CONV_WIDTH]);

#endif // CONV_TOP_H
