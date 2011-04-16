#ifndef MYMASKA_H
#define MYMASKA_H

#include "stdhead.h"
#include "MYoblicej.h"
using namespace std;


class MYmaska
{

//promenne
private:
    uchar interpolate(uchar*, uchar*, int, int);

//funkce
public:
	MYmaska(IplImage*);	//konstruktor
	virtual ~MYmaska();	//destruktor
	void open(string);
	void open_mask(string);

    IplImage *frame;
    IplImage *mask;
    IplImage *mask2;
    IplImage *mask3;
    IplImage *source;
    IplImage *edited;
    IplImage *rotated;
    MYoblicej *oblicej;
	void changeSize(float);
    void rotateImage(float);
    void vytvorKnirek(MYoblicej*);
    void vytvorPusu(MYoblicej*);
    void vytvorKaju(MYoblicej*);
    void vytvorKlobouk(MYoblicej*);
    void skryjOci(MYoblicej*, IplImage*);
    IplImage *addMask(IplImage *,int);
};

#endif // MYMASKA_H
