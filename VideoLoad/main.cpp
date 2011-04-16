#include "MYdetektor.h"
#include "MYdisplay.h"
#include "MYvideo.h"

#include <iostream>
#include <vector>

int main( int argc, char** argv )
{

MYdetektor *detect;

cout << "PRO DALSI SNIMEK STISTKNI KLAVESU q" << endl;


MYvideo *video;
    video = new MYvideo();
    video->open("../videos/deep/new/Video 11.wmv");
    video->writeInit();
int counter = 0 ;

detect = new MYdetektor(NULL); // zpracuj frame
double tta = (double)cvGetTickCount();

MYoblicej *pre_ksicht=NULL;
MYoblicej *ksicht;

    for(;;){
        IplImage *image = video->next_frame();

        if( image == NULL) break;//Pri nacteni prazdneho FRAMU == konec videa

        //Zpracovani snimku
        detect->setFrame(image);

        double tt = (double)cvGetTickCount();
        if(counter >= 0){
//            detect->FindFaces();
//            detect->DrawSezOblic();
            detect->FindFaces();

// pokud nenajde face nic nevykresli
            if(!detect->sX.empty()){
                //! Vyprazdnit seznam kdyz si neco vyzvednu
                ksicht = new MYoblicej(detect->sX.at(0).rFace,detect->sX.at(0).eye1,detect->sX.at(0).eye2);
                ksicht->ber_v_uvahu(pre_ksicht);
                detect->sX.clear();
                ksicht->DrawOblicej(image);

//                ksicht->DrawVodiciObdel(image);
//                ksicht->DrawHighPoints(image);

                delete pre_ksicht;
                pre_ksicht = ksicht;

                MYdisplay::ShowImage(image,(char)-1);
            }
//            while(facec !epmt){ Myoblice(display->nextface);
//
//            v
//            }
        }

        tt = (double)cvGetTickCount() - tt;
        cout << tt/(cvGetTickFrequency()*1000.) << " ms" << endl;

        char c = cvWaitKey(33);
        if(c == 27) break;
        video->writeFrame(image);

        cout << endl << counter << " - takovy snimek" << endl;
        counter++;
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
