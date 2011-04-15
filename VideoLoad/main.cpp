#include "MYdetektor.h"


#include <iostream>
#include <vector>

int main( int argc, char** argv )
{
// nacte obrazek
    IplImage *img = cvLoadImage(argv[1]);

    double tt = (double)cvGetTickCount();


    MYdetektor detect(img);
    detect.DrawFaces();

    tt = (double)cvGetTickCount() - tt;
    cout << tt/(cvGetTickFrequency()*1000.) << "ms" << endl;
    // Wait for user input before quitting the program

    detect.DrawSezOblic();
//img = cvLoadImage("test/1.jpg");
//    detect.setFrame(img);
//    detect.DrawFaces();


    // Release the image
    cvReleaseImage(&img);

    // Destroy the window previously created with filename: "result"
    cvDestroyWindow("result");

    // return 0 to indicate successfull execution of the program
    return 0;
}
