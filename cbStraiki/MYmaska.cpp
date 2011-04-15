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

void MYmaska::open(string name){
    this->source = cvLoadImage(name.c_str());
}

void MYmaska::changeSize(float size){
   // IplImage *source = cvLoadImage("obrazek.png");

    this->edited = cvCreateImage(cvSize((int)(this->source->width*size),
                                                 (int)(this->source->height*size)),
                                          source->depth,
                                          source->nChannels);
    cvResize(this->source, this->edited);
}

