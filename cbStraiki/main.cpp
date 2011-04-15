// Sample Application to demonstrate how Face detection can be done as a part of your source code.

// Include header files
#include "stdhead.h"
#include "MYdetektor.h"
#include "MYmaska.h"
#include "MYvideo.h"

#include <iostream>
#include <vector>

int main( int argc, char** argv )
{

    // Create a sample image
    IplImage *img = cvLoadImage(argv[1]);

    double tt = (double)cvGetTickCount();
    // Call the function to detect and draw the face positions
    //    detect_and_draw(img);
    tt = (double)cvGetTickCount() - tt;
    cout << tt/(cvGetTickFrequency()*1000.) << "ms" << endl;
    // Wait for user input before quitting the program


    ///Vahyho sekce
    const char * WinName = "Debug";
    cvNamedWindow(WinName, CV_WINDOW_AUTOSIZE);
    cvMoveWindow(WinName, 100, 100);
    MYmaska *maska;
    maska = new MYmaska();
    maska->open("../masks/moustache.png");
    maska->changeSize(0.5);
    maska->rotateImage(1);
    cvShowImage(WinName, maska->rotated);
    cvWaitKey();
/*
    MYvideo *video;
    video = new MYvideo();
    video->open("../videos/L1 - JH.avi");
    for(;;){
        IplImage *image = video->next_frame();
        cvShowImage(WinName, image);
        char c = cvWaitKey(33);
        if(c == 27) break;
        video->writeFrame(image);
    }
*/
    cvDestroyWindow(WinName);
    // Release the image
    //cvReleaseImage(&img);

    // Destroy the window previously created with filename: "result"
    //cvDestroyWindow("result");

    // return 0 to indicate successfull execution of the program
    return 0;
}
