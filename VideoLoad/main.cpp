// Sample Application to demonstrate how Face detection can be done as a part of your source code.

// Include header files
#include "MYdetektor.h"

#include <iostream>
#include <vector>

int main( int argc, char** argv )
{

    // Create a sample image
    IplImage *img = cvLoadImage(argv[1]);

// nejaky comment
    double tt = (double)cvGetTickCount();
    // Call the function to detect and draw the face positions
//    detect_and_draw(img);
    tt = (double)cvGetTickCount() - tt;
    cout << tt/(cvGetTickFrequency()*1000.) << "ms" << endl;
    // Wait for user input before quitting the program
    cvWaitKey();

    // Release the image
    cvReleaseImage(&img);

    // Destroy the window previously created with filename: "result"
    cvDestroyWindow("result");

    // return 0 to indicate successfull execution of the program
    return 0;
}
