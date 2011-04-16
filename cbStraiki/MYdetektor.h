#ifndef MYDETEKTOR_H
#define MYDETEKTOR_H

#include <cv.h>
#include <highgui.h>

#include <deque>

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

#include "MYoblicej.h"


/** Cesty k haarcascades*/

struct Xicht{
    CvRect rFace, eye1,eye2;
};

class MYdetektor
{
    public:
        MYdetektor(IplImage *);
        virtual ~MYdetektor();

        /** @var IplImage * MyFrame
        *   @brief Obrazek daneho framu, ve kterem se hledaji obliceje
        */
        IplImage * MyFrame;

        /** @var deque<Xicht> sXichts
        *   @brief Seznam vsech nalezenych oblizeju
        */
        deque<Xicht> sX;

        Xicht Xakt;

        /**
        *   Metoda, ktera v obrazku zvyrazni obliceje
        *   podle klasifikatoru nejakeho z OpenCV
        */
        int DrawFaces();

        /**
        *   Metoda, ktera najde oblicej v obrazku
        */
        int FindFaces();
        int FindEyes(CvRect Roi);
        int FindMouth(IplImage *);

        int Fpokus();
        int Epokus();
        /**
        *   Vykresli obdelniky kolem nalezenych obliceju
        */
        void DrawSezOblic();

        /**
        *   Metoda Setter pro zmenu obrazku
        * @param ukazatel na obrazek, ktery chci nacist
        */
        void setFrame(IplImage *);
    protected:
    private:

        int _prusecik(CvRect,CvRect);
        int _prekriz(CvRect,CvRect,CvRect);

        void OrezPic(CvPoint, CvPoint);
        /**
        *   Setter - nasteveni vsech pouzivanych cascades
        */
        void _setHaars();

        CvPoint _findEyeCenter(CvPoint, CvPoint);
        /**
        *  Vsechny Pouzivane Cascady
        */
        const char* cascFace;
        const char* cascEyes;
        const char* cascMouth;

        /** @var
        *   @brief
        */
};

#endif // MYDETEKTOR_H
