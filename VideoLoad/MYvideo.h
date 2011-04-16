/*
 * =====================================================================================
 *
 *       Filename:  MYvideo.h
 *
 *    Description:  headfile
 *
 *        Version:  1.0
 *        Created:  04/15/2011 02:25:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Tomas Vahalik (TV), xvahal02@stud.fit.vutbr.cz, tomas@vahalik.cz
 *        Company:  FiT
 *
 * =====================================================================================
 */

#include "stdhead.h"
#include "MYmaska.h"

using namespace cv;
using namespace std;

class MYvideo {

public:
    MYvideo();

    ~MYvideo();

    IplImage *img;
    CvVideoWriter *writer;
    CvCapture *capture;


    IplImage *next_frame();
    void open(int);
    void open(string);
    void writeInit();
    void writeFrame(IplImage*);
    static IplImage *addMask(IplImage*,MYmaska*,int);

private:

};
