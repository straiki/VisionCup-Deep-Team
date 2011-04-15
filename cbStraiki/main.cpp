// Sample Application to demonstrate how Face detection can be done as a part of your source code.

// Include header files
#include "stdhead.h"
#include "MYdetektor.h"
#include "MYmaska.h"
#include "MYvideo.h"
#include "MYoblicej.h"

#include <iostream>
#include <vector>

int main( int argc, char** argv )
{

    // Create a sample image
    IplImage *img = cvLoadImage("../img/obr.jpg");

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
    /*
/// oblicej
    MYoblicej *oblicej = new MYoblicej;

	//nastaveni
	oblicej->sour_x = 0;
	oblicej->sour_y = 0;
	oblicej->sirka = img->width;
	oblicej->vyska = img->height;
	oblicej->leve_oko_x  = 116;	oblicej->leve_oko_y  = 191;
	oblicej->prave_oko_x = 205;	oblicej->prave_oko_y = 190;

	oblicej->vypocti_klicove_body();

///maska
    MYmaska *maska;
    maska = new MYmaska();
    maska->vytvorKnirek(oblicej);


    MYvideo *video;
    video = new MYvideo();
    cvShowImage(WinName, video->addMask(img,maska));

   // cvShowImage(WinName, maska->rotated);
    cvWaitKey();
    */
    ///endmask

    MYvideo *video;
    video = new MYvideo();
    video->open("video.avi");
    int i = 0;
    //video->open("../videos/L1 - JH.avi");
    for(;;){
        //stringstream num;
        //num << i;
       // string nazev = "obrazky/pusa/vzorky/";
       // nazev.append(num.str());
        //nazev.append(".jpg");

        IplImage *image = video->next_frame();//cvLoadImage(nazev.c_str());//video->next_frame();
        // ker zpracovani pajou
        // tady bude maska
        // vlozit masku do obrazu
        cvShowImage(WinName, image);
        char c = cvWaitKey(33);
        if(c == 27) break;
        ///i++;
        //if(i == 20)
       //     break;
        //cvSaveImage(nazev.c_str(), image);
        if(i==0){
            for(int j = 0; j < 20; j++)
                video->writeFrame(image);
        }else{
            for(int j = 0; j < 5; j++)
                video->writeFrame(image);
        }
    i++;
        //cvReleaseImage(&image);
    }
/**/
    cvDestroyWindow(WinName);
    // Release the image
    //cvReleaseImage(&img);

    // Destroy the window previously created with filename: "result"
    //cvDestroyWindow("result");

    // return 0 to indicate successfull execution of the program
    return 0;
}
