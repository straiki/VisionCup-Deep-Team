#include "MYdetektor.h"


#include <iostream>
#include <vector>

int main( int argc, char** argv )
{

MYdetektor *detect;
MYvideo *video;
    video = new MYvideo();
    video->open("../videos/L1 - JH.avi");
    for(;;){
        IplImage *image = video->next_frame();
        cvShowImage(WinName, image);
            double tt = (double)cvGetTickCount();
        detect = new detect(image); // zpracuj frame
            tt = (double)cvGetTickCount() - tt;
            cout << tt/(cvGetTickFrequency()*1000.) << "ms" << endl;
        char c = cvWaitKey(33);
        if(c == 27) break;
        video->writeFrame(image);
    }

  //  detect.DrawSezOblic();
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
