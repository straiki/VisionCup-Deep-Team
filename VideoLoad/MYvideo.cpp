/*
 * =====================================================================================
 *
 *       Filename:  MYvideo.cpp
 *
 *    Description:  MYvideo class
 *
 *        Version:  1.0
 *        Created:  04/15/2011 02:25:28 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Tomas Vahalik (TV), xvahal02@stud.fit.vutbr.cz, tomas@vahalik.cz
 *        Company:  FiT
 *
 * =====================================================================================
 */

#include "MYvideo.h"
#include "MYoblicej.h"

MYvideo::MYvideo(){
    this->capture = 0;
}

MYvideo::~MYvideo(){
    cvReleaseCapture(&this->capture);
}
/**
 * @var file - vstuppni soubor
 */
void MYvideo::open(string file){
    this->capture = 0;
    if(!(capture = cvCaptureFromFile(file.c_str()))){
        cerr << "Obrazek nenalezen" << endl;
        return;
    }
   // this->writeInit();
}
/**
 * @var cam - cislo kamery
 */
void MYvideo::open(int cam = -1){
    this->capture = 0;
    if(!(capture = cvCaptureFromCAM(cam))){
        cerr << "Nelze spojit s kamerou" << endl;
        return;
    }
    this->writeInit();
}
void MYvideo::writeInit(){
    string name = "vystup.avi";
    double fps = -1;
    //if((fps = cvGetCaptureProperty(this->capture, CV_CAP_PROP_FPS))==0)
        fps = 10; // nelze vytahnout fps
	cout << "Nastavuji " << fps << " FPS" << endl;
	CvSize size = cvSize((int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH),(int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT));
	this->writer = cvCreateVideoWriter(name.c_str(), CV_FOURCC('D', 'I', 'V', 'X'), fps, size);

}
/**
 * Funkce ktera vraci dalsi snimek z kamery/videa
 */
IplImage* MYvideo::next_frame(){
    this->img = cvQueryFrame(this->capture);
    return this->img;
}

#define PUSA 0
#define KNIR 1
#define KAJA 2
#define KLOBOUK 3
IplImage* MYvideo::addMask(IplImage *frame, MYmaska *mask,int typ){
//    cvSetImageROI(frame, cvRect(mezi_oci_x - mask->rotated->width/2,
  //                              mezi_oci_y - mask->rotated->height/2));


  int start_y = 0;
  int start_x = 0;

    const int Thres = 100;
    const int HT = 50;
    int x,y,i,j;

    if(typ == KNIR){
        start_y = mask->oblicej->sour_y + mask->oblicej->knirek_y - mask->rotated->height/2;
        start_x = mask->oblicej->sour_x + mask->oblicej->knirek_x - mask->rotated->width/2;
    }
    else if(typ == PUSA){
        start_y = mask->oblicej->sour_y + mask->oblicej->pusa_y - mask->rotated->height/2;
        start_x = mask->oblicej->sour_x + mask->oblicej->pusa_x - mask->rotated->width/2;
    }
    else if(typ == KAJA){
        start_y = mask->oblicej->sour_y + mask->oblicej->stred_obliceje_y - mask->rotated->height/2;
        start_x = mask->oblicej->sour_x + mask->oblicej->stred_obliceje_x - mask->rotated->width/2;
    }
    else if(typ == KLOBOUK){
        start_y = mask->oblicej->sour_y -45 - mask->rotated->height/2;
        start_x = mask->oblicej->sour_x + mask->oblicej->stred_obliceje_x - mask->rotated->width/2;
    }

    for (i = start_y; i < start_y + mask->rotated->height; i++) {
        for (j = start_x; j < start_x + mask->rotated->width; j++) {
			if(CV_IMAGE_ELEM( mask->rotated, uchar, i - start_y, (j - start_x)*3)   < Thres &&
			   CV_IMAGE_ELEM( mask->rotated, uchar, i - start_y, (j - start_x)*3+1) > 255-HT &&
			   CV_IMAGE_ELEM( mask->rotated, uchar, i - start_y, (j - start_x)*3+2) < Thres) {

				continue;
            }
            else{
                ((uchar*)(frame->imageData + i * frame->widthStep))[j*3]   = CV_IMAGE_ELEM( mask->rotated, uchar, i - start_y, (j - start_x)*3); //b
                ((uchar*)(frame->imageData + i * frame->widthStep))[j*3+1] = CV_IMAGE_ELEM( mask->rotated, uchar, i - start_y, (j - start_x)*3+1); //g
                ((uchar*)(frame->imageData + i * frame->widthStep))[j*3+2] = CV_IMAGE_ELEM( mask->rotated, uchar, i - start_y, (j - start_x)*3+2); //r

            }
        }
    }

    return frame;
}

void MYvideo::writeFrame(IplImage *image){
    cvWriteFrame(this->writer, image);
}
