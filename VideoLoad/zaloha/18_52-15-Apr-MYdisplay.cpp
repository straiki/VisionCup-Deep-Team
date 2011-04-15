#include "MYdisplay.h"

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
