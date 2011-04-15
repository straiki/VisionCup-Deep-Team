#ifndef MYMASKA_H
#define MYMASKA_H

#include "stdhead.h"

class MYmaska
{

//promenne
private:


//funkce
public:
	MYmaska();	//konstruktor
	virtual ~MYmaska();	//destruktor

    IplImage *source;

	void changeSize(float);

};

#endif // MYMASKA_H
