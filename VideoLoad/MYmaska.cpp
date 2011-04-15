#include "MYmaska.h"
#include "MYoblicej.h"
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
    //cvCopy(this->edited, this->source);
    //cvReleaseImage(&this->edited);
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
	//float angleRadians = angleDegrees * ((float)CV_PI / 180.0f);
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
	this->rotated = cvCreateImage( sizeRotated,
		this->edited->depth, this->edited->nChannels );

	// Transform the image
	cvGetQuadrangleSubPix( this->edited, this->rotated, &M);

    //cvCopy(this->edited, this->source);
    //cvReleaseImage(&this->edited);
}

void MYmaska::vytvorKnirek(MYoblicej *oblicej){

    this->oblicej = oblicej;
    this->open("../masks/gott2.png");
    this->changeSize(0.5);
    this->rotateImage(this->oblicej->uhel);
    printf("knirek ok/n");
}
