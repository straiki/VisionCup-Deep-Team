#include "MYmaska.h"
#include "MYoblicej.h"
#include "stdhead.h"

#include "MYvideo.h"
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

void MYmaska::open_mask(string name){
    this->mask = cvLoadImage(name.c_str());
}

void MYmaska::changeSize(float size){
	
	//zmena originalu
    this->edited = cvCreateImage(cvSize((int)(this->source->width*size),
										(int)(this->source->height*size)),
								 source->depth,
								 source->nChannels);
    cvResize(this->source, this->edited);
	
	//zmena masky
    this->mask2 = cvCreateImage(cvSize((int)(this->mask->width*size),
										(int)(this->mask->height*size)),
								 mask->depth,
								 mask->nChannels);
    cvResize(this->mask, this->mask2);
	
}

// Rotate the image clockwise (or counter-clockwise if negative).
// Remember to free the returned image.
void MYmaska::rotateImage(float angleRadians)
{
	// Create a map_matrix, where the left 2x2 matrix
	// is the transform and the right 2x1 is the dimensions.
	float m[6];
	CvMat M = cvMat(2, 3, CV_32F, m);
	int w = this->edited->width;
	int h = this->edited->height;
	
	m[0] = (float)( cos(angleRadians) );
	m[1] = (float)( sin(angleRadians) );
	m[3] = -m[1];
	m[4] = m[0];
	m[2] = w*0.5f;
	m[5] = h*0.5f;

	// Make a spare image for the result
	CvSize sizeRotated;

	sizeRotated.width = cvRound(MAX(w,h));
	sizeRotated.height = cvRound(MAX(w,h));

	// Rotate
	this->rotated = cvCreateImage(sizeRotated,
								  this->edited->depth,
								  this->edited->nChannels );
	
	this->mask3 = cvCreateImage(sizeRotated,
								this->mask2->depth,
								this->mask2->nChannels );

	// Transform the image
	cvGetQuadrangleSubPix( this->edited, this->rotated, &M);
	
	cvGetQuadrangleSubPix( this->mask2, this->mask3, &M);

}

void MYmaska::vytvorKnirek(MYoblicej *oblicej){

    this->oblicej = oblicej;
    this->open("../masks/moustache.png");
    this->changeSize(0.5);
    this->rotateImage(this->oblicej->uhel);

}

void MYmaska::vytvorKaju(MYoblicej *oblicej){

    this->oblicej = oblicej;
    this->open("../masks/gott.png");
    this->open_mask("../masks/gott_mask.png");
    this->changeSize(0.5);
    this->rotateImage(this->oblicej->uhel);

}
void MYmaska::vytvorKlobouk(MYoblicej *oblicej){

    this->oblicej = oblicej;
    this->open("../masks/klobouk.png");
    this->changeSize(oblicej->vzdalenost_oci*4/source->width);

    this->rotateImage(this->oblicej->uhel);

}

void MYmaska::vytvorPusu(MYoblicej * oblic){
    static int i = 1;
    this->oblicej = oblic;


    MYvideo *prd = new MYvideo();
        prd->open("../masks/pusa.avi");

        IplImage * akt;
        for(int j = 0; j < i ; j++){
        	 akt = prd->next_frame();
        	 if( i >= 100) i = 1;
        }
        this->source = akt;
        i++;

    this->changeSize(0.5);
    this->rotateImage(this->oblicej->uhel);
}
