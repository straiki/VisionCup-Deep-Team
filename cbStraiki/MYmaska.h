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

	void changeSize(float);


};

#endif // MYMASKA_H
