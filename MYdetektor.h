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

class MYdetektor
{
    public:
        MYdetektor(IplImage *);
        virtual ~MYdetektor();

        /** @var IplImage * MyFrame
        *   @brief Obrazek daneho framu, ve kterem se hledaji obliceje
        */
        IplImage * MyFrame;

        /**
        *   Metoda, ktera v obrazku zvyrazni obliceje
        *   podle klasifikatoru nejakeho z OpenCV
        */
        int DrawFaces();

    protected:
    private:

        /** @var
        *   @brief
        */
};

#endif // MYDETEKTOR_H
