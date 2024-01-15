
#include <iostream>
#include <cstdlib>

#include "convolution.h"

using namespace std;

#define TEST_IMG_ROWS 8
#define TEST_IMG_COLS 8
int main(void)
{
    data_t ref_img[TEST_IMG_ROWS-2][TEST_IMG_COLS-2 ]
	    = {{ 60,66,72,84,90,108},
    	      {114,120,126,132,138,156}
    	     ,{162,168,174,180,186,204}
             ,{210,216,222,228,234,252}
             ,{258,264,270,276,282,300}
             ,{306,312,318,324,330}};
    data_t output_data[TEST_IMG_ROWS-2][TEST_IMG_COLS-2];

    hls::stream<data_t> src_img_strm("src_img_strm");
    hls::stream<data_t> dut_img_strm("dut_img_strm");
    const data_t max_pix_val = 255;
    const data_t min_pix_val = 0;
    int err_cnt = 0;
    int ret_val = 20;
    // Generate the source image with a fixed test pattern - checker-board
    for (int i = 0; i < TEST_IMG_ROWS; i++) {
        for (int j = 1; j <= TEST_IMG_COLS; j++) {
            src_img_strm << i*8 + j;
        }
    }
    // Generate DUT convolution image
    filter11x11_strm(TEST_IMG_COLS, TEST_IMG_ROWS, src_img_strm, dut_img_strm);
    // Check DUT vs reference result
    for (int i = 0; i < TEST_IMG_ROWS; i++) {
        for (int j = 0; j < TEST_IMG_COLS; j++) {
	    data_t ref_val = ref_img[i][j];
            data_t dut_val = dut_img_strm.read();
	    output_data[i][j] = dut_img_strm.read();
	    cout << " , " << output_data[i][j];
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
