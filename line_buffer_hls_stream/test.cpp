#include"conv.h"
#include<iostream>
#include<cstdlib>

using namespace std;
int main(void){
	 hls::stream<int> image;
	 hls::stream<int> output;
	 int err_cnt = 0;
	 int ret_val = 20;
	 const int check[]= {60,66,72,78,84,90,108,114,120,126,132,138,156,162,168,174,180,186,204,210,216,222,228,234,252,258,264,270,276,282,300,306,312,318,324,330};
    int const data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
                  21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
                  41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
                  61, 62, 63, 64};

    for (int i = 0; i < 64 ; ++i) {
        image.write(data[i]);
    }
		
		filter3x3_orig(image,output);
		for (int i = 0; i < (IMAGE_SIZE -2) ; i++) {
        for (int j = 0; j < (IMAGE_SIZE - 2); j++) {
            int dut_val = output.read();
	    cout<< " " << dut_val;
            int ref_val = check[i*(IMAGE_SIZE - 2) + j];
            if (dut_val != ref_val) {
                err_cnt++;
#if 0
                cout << "!!! ERROR: Mismatch detected at coord(" << i;
                cout << ", " << j << " ) !!!";
                cout << endl;
#endif
            }
        }
    }
    cout << endl;

    if (err_cnt == 0) {
        cout << "*** TEST PASSED ***" << endl;
        ret_val = 0;
    } else {
        cout << "!!! TEST FAILED - " << err_cnt << " mismatches detected !!!";
        cout << endl;
        ret_val = -1;
    }

		return 0;
	}
//
//int * const src_img = new data_t[IMAGE_SIZE*IMAGE_SIZE];
//int * const src_img = new data_t[IMAGE_SIZE*IMAGE_SIZE];
//hls::stream<data_t> src_img_stream("src_img_stream");
//hls::stream<data_t> dut_img_stream("dut_img_stream");
//int err_cnt = 0;
//int ret_val = 20;



