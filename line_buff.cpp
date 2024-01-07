 #include<stdio.h>
 const int IMAGE_WIDTH = 4;
 
 const int IMAGE_HEIGHT = 4;
 const int IMAGE_SIZE  = 4 ;
   const  int image[IMAGE_SIZE][IMAGE_SIZE] = {
         {1, 2, 3, 4},
         {5, 6, 7, 8},
         {9, 10, 11, 12},
         {13, 14, 15, 16}
     };
 //void printLineBuffers( int [3][4]);
 void printLineBuffers(int LineBuffer[3][IMAGE_WIDTH]) {
     for (int i = 0; i < 3; ++i) {
         for (int j = 0; j < IMAGE_WIDTH; ++j) {
             printf("%d ", LineBuffer[i][j]);
         }
         printf("\n");
     }
     printf("\n");
 }
 void printWindowBuffers(int LineBuffer[3][3]) {
     for (int i = 0; i < 3; ++i) {
         for (int j = 0; j < 3; ++j) {
             printf("%d ", LineBuffer[i][j]);
         }
         printf("\n");
     }
     printf("\n");
 }
 
 void line_buff( int LineBuffer[3][IMAGE_WIDTH], int WindowBuffer[3][3]){
 for ( int i = 0; i<IMAGE_HEIGHT; i++){
   for( int j = 0; j < IMAGE_WIDTH ; j++ ){
     #pragma pipeline
     LineBuffer[0][j]=LineBuffer[1][j];
     LineBuffer[1][j]=LineBuffer[2][j];
     LineBuffer[2][j]=image[i][j];
     }
 for(int n = 0 ; n < 3 ; n++) {
     WindowBuffer[n][0] = LineBuffer[n][0];
     WindowBuffer[n][1] = LineBuffer[n][1];
     WindowBuffer[n][2] = LineBuffer[n][2];}
 printLineBuffers(LineBuffer);
               for(int k = 0; k < 3; k++){
                 WindowBuffer[k][2] = WindowBuffer[k][1];
                 WindowBuffer[k][1] = WindowBuffer[k][0];
 
                 printWindowBuffers(WindowBuffer);
     }
 }
 }
 int main() {
   //  int outputImage[IMG_SIZE][IMG_SIZE] = {0};
     int LineBuffer[3][IMAGE_WIDTH] = {0};
     int WindowBuffer[3][3] = {0};
 
     // Initialize ConvolutionLayer
    // initializeConvolutionLayer(&convLayer);
 
     // Perform convolution
     line_buff( LineBuffer,WindowBuffer);
 
     return 0;
 }
 //void convolution(int WindowBuffer[3][3] ){
 //int conv;
 // for(int col = 0; col < IMAGE_HEIGHT; col++) {
 //        for(int row = 0; row < IMAGE_WIDTH; row++) {
 //#pragma HLS PIPELINE
 //            for(int i = 0; i < 3; i++) {
 //                out_val +=WindowBuffer[col][row] * kernel[col][val];
 //            }
 //            if (row >= 3)
 //                conv << out_val;
 //        }
 //    } 
 

