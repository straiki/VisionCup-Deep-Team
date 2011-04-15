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

IplImage* MYvideo::addMask(IplImage *frame, IplImage *mask){

}

void MYvideo::writeFrame(IplImage *image){
    cvWriteFrame(this->writer, image);
}
