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
    this->writeInit();
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
    if((fps = cvGetCaptureProperty(this->capture, CV_CAP_PROP_FPS))==0)
        fps = 5; // nelze vytahnout fps
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

IplImage* MYvideo::addMask(IplImage *frame, MYmaska *mask){
//    cvSetImageROI(frame, cvRect(mezi_oci_x - mask->rotated->width/2,
  //                              mezi_oci_y - mask->rotated->height/2));

    int x,y,i,j;
    int start_y = mask->oblicej->knirek_y - mask->rotated->height/2;
    int start_x = mask->oblicej->knirek_x - mask->rotated->width/2;
    for (i = start_y; i < start_y + mask->rotated->height; i++) {
        for (j = start_x; j < start_x + mask->rotated->width; j++) {
			if(CV_IMAGE_ELEM( mask->rotated, uchar, i - start_y, (j - start_x)*3)   == 0 &&
			   CV_IMAGE_ELEM( mask->rotated, uchar, i - start_y, (j - start_x)*3+1) == 255 &&
			   CV_IMAGE_ELEM( mask->rotated, uchar, i - start_y, (j - start_x)*3+2) == 0) {

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
