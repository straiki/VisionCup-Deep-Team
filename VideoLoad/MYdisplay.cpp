#include "MYdisplay.h"
#include <iostream>
MYdisplay::MYdisplay()
{
    //ctor
}

MYdisplay::~MYdisplay()
{
    //dtor
}


// bez odkliknuti
char MYdisplay::ShowImage(IplImage * image, const char * winName, int x, int y){
    if( image != NULL){
        cvShowImage(winName, image);
        cvMoveWindow(winName, x, y);
    }
}

char MYdisplay::ShowImage(IplImage * image, char cvKey, const char * winName,int x, int y){
    if( image != NULL){
        cvShowImage(winName, image);
        cvMoveWindow(winName, x, y);
        if(cvKey == 0){
            cvWaitKey(0);
            return cvKey;
        }
        else if(cvKey == -1){
            return cvKey;
        }
        else{
            while(1){
                char keystroke = cvWaitKey();
                if( keystroke == cvKey){
                    return cvKey;
                }
            }
        }
    }
}

void MYdisplay::DrawPoint(IplImage * image, CvPoint P, int delka, int tloustka, CvScalar barva){
    cvLine(image,cvPoint(P.x-delka,P.y),cvPoint(P.x+delka,P.y),barva,tloustka,8,0);
    cvLine(image,cvPoint(P.x,P.y-delka),cvPoint(P.x,P.y+delka),barva,tloustka,8,0);
}

int MYdisplay::LoadImage(IplImage** image,const char * imgPath){
    *image = cvLoadImage(imgPath);
    if(!image){
        std::cerr << "Nelze nacist obrazek";
        return 1;
    }
    return 0;
}
