#ifndef DEFINES_H
#define DEFINES_H

#define IMG_HEIGHT 28
#define IMG_WIDTH 28
#define K 3
#define CONV1_HEIGHT IMG_HEIGHT 
#define CONV1_WIDTH IMG_WIDTH
#define POOL_SIZE 2
#define POOL1_HEIGHT (CONV1_HEIGHT / POOL_SIZE)
#define POOL1_WIDTH (CONV1_WIDTH / POOL_SIZE)
#define NUM_FILTERS_1 16
#define NUM_FILTERS_2 8
#define NUM_KERNEL_2 16

#endif
