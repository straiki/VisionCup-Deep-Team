#include "MYdetektor.h"
#include "MYdisplay.h"
#include "MYvideo.h"

#include <iostream>
#include <vector>

int main( int argc, char** argv )
{

MYdetektor *detect;

IplImage * img = cvLoadImage(argv[1]);
            double tt = (double)cvGetTickCount();
        detect = new MYdetektor(img); // zpracuj frame
        detect->FindFaces();
            tt = (double)cvGetTickCount() - tt;
            cout << tt/(cvGetTickFrequency()*1000.) << "ms" << endl;



cout << "PRO DALSI SNIMEK STISTKNI KLAVESU q" << endl;
double tta = (double)cvGetTickCount();

MYvideo *video;
    video = new MYvideo();
    video->open("../videos/L2 - RK.avi");
    for(;;){
        IplImage *image = video->next_frame();
        //MYdisplay::ShowImage(image);
            double tt = (double)cvGetTickCount();
        detect = new MYdetektor(image); // zpracuj frame
        detect->FindFaces();
            tt = (double)cvGetTickCount() - tt;
            cout << tt/(cvGetTickFrequency()*1000.) << "ms" << endl;
            MYdisplay::ShowImage(detect->MyFrame,'q');
        //break;
        char c = cvWaitKey(33);
        if(c == 27) break;
        video->writeFrame(image);
       // MYdisplay::ShowImage(image,'q');
    }
            tta = (double)cvGetTickCount() - tta;
            cout << tta/(cvGetTickFrequency()*1000.) << " -- CELKOVY CAS ms" << endl;
  //  detect.DrawSezOblic();
//img = cvLoadImage("test/1.jpg");
//    detect.setFrame(img);
//    detect.DrawFaces();


    // Release the image
   // cvReleaseImage(&image);

    // Destroy the window previously created with filename: "result"
    cvDestroyWindow("result");

    // return 0 to indicate successfull execution of the program
    return 0;
}
