#ifndef MYMASKA_H
#define MYMASKA_H

#include "stdhead.h"
#include "MYoblicej.h"
using namespace std;


class MYmaska
{

//promenne
private:


//funkce
public:
	MYmaska();	//konstruktor
	virtual ~MYmaska();	//destruktor
	void open(string);

    IplImage *source;
    IplImage *edited;
    IplImage *rotated;
    MYoblicej *oblicej;
	void changeSize(float);
    void rotateImage(float);
    void vytvorKnirek(MYoblicej*);
};

#endif // MYMASKA_H
