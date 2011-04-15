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

struct xicht{
    CvPoint a,b;
};

/** Cesty k haarcascades*/



class MYdetektor
{
    public:
        MYdetektor(IplImage *);
        virtual ~MYdetektor();

        /** @var IplImage * MyFrame
        *   @brief Obrazek daneho framu, ve kterem se hledaji obliceje
        */
        IplImage * MyFrame;

        /** @var deque<int> sezOblic
        *   @brief Seznam vsech nalezenych oblizeju
        */
        deque<xicht> sezOblic;

        /**
        *   Metoda, ktera v obrazku zvyrazni obliceje
        *   podle klasifikatoru nejakeho z OpenCV
        */
        int DrawFaces();
        /**
        *   Metoda, ktera najde oblicej v obrazku
        */
        int FindFaces();

        int FindEyes(IplImage *);

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
        void OrezPic(CvPoint, CvPoint);
        /**
        *   Setter - nasteveni vsech pouzivanych cascades
        */
        void _setHaars();
        /**
        *  Vsechny Pouzivane Cascady
        */
        const char* cascFace;
        const char* cascEyes;

        /** @var
        *   @brief
        */
};

#endif // MYDETEKTOR_H
