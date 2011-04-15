#include "MYmaska.h"
#include "stdhead.h"
using namespace std;
//konstruktor
MYmaska::MYmaska(){
	cout << "vytvorena maska" << endl;
}

//destruktor
MYmaska::~MYmaska(){
	cout << "znicena maska" << endl;
}

void MYmaska::changeSize(float size){
   // IplImage *source = cvLoadImage("obrazek.png");

    IplImage *destination = cvCreateImage(cvSize((int)(this->source->width*size),
                                                 (int)(this->source->height*size)),
                                          source->depth,
                                          source->nChannels);
    cvResize(source, destination);
}
