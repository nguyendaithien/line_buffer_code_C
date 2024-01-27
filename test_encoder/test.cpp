#include <iostream>
#include <fstream>
#include"weights.h"
#include"CNN.h"

using namespace std;

int main(void) {
    hls::stream<double> image("image");
    hls::stream<double> output_conv1("output_1");
    hls::stream<double> output_pooling1("output_pool1");
    hls::stream<double> output_conv2("output_pool2");
    hls::stream<double> output_pooling2("output_2");
    hls::stream<double> output_conv3("output_conv3");
    hls::stream<double> output_pooling3("output_pool3");
    hls::stream<double> output_conv4("output_conv4");
    hls::stream<double> output_pooling4("output_pool4");
    hls::stream<double> output_conv5("output_conv5");
    hls::stream<double> output_pooling5("output_pool5");
    hls::stream<double> output_conv6("output_conv6");
    hls::stream<double> output_pooling6("output_pool6");
    hls::stream<double> output_conv7("output_conv7");
    hls::stream<double> output_pooling7("output_decoder");

    for (int i = 0; i < 28*28 ; i++) {
        image.write(img[i]);
    }

    //CNN(1, 28, 28, image, output_conv1, output_pooling1, output_conv2,output_pooling2,output_conv3, output_pooling3,output_conv4, output_pooling4,output_conv5, output_pooling5,output_conv6, output_pooling6,output_conv7, output_pooling7);
    CNN(1, 28, 28, image, output_conv1, output_pooling1, output_conv2,output_pooling2,output_conv3, output_pooling3);


        for (int i = 0; i < 16 ; i++) {
            for (int j = 0; j < 8; j++) {
                double dut_val = output_pooling3.read();
                cout << " " << dut_val;
            }
	    cout << "\n";
        }

    return 0;
}

