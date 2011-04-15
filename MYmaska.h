#ifndef MYMASKA_H
#define MYMASKA_H

#include "stdhead.h"

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
	void changeSize(float);
    void rotateImage(float);

};

#endif // MYMASKA_H
