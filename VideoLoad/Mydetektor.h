#ifndef MYDETEKTOR_H
#define MYDETEKTOR_H

#include <cv.h>
#include <highgui.h>

#include <iostream>
#include <vector>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>


class Mydetektor
{
    public:
        Mydetektor();
        virtual ~Mydetektor();
    protected:

    private:
        /** @var IplImage * MyFrame
        *   @brief Obrazek daneho framu, ve kterem se hledaji obliceje
        */
        IplImage * MyFrame;
        /** @var
        *   @brief
        */

};

#endif // MYDETEKTOR_H
///home/xsimur01/progr/VisionCup-Deep-Team/VideoLoad/src