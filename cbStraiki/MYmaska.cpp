#include "MYmaska.h"
#include "MYoblicej.h"
#include "stdhead.h"

#include "MYvideo.h"
using namespace std;
//konstruktor
MYmaska::MYmaska(IplImage *frame){

	cout << "vytvorena maska" << endl;
	this->frame = frame;
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
								 IPL_DEPTH_8U,
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
    this->open("../masks/mustache.png");
    this->open_mask("../masks/mustache_mask.png");
    this->changeSize(0.5);
    this->rotateImage(this->oblicej->uhel);

}

void MYmaska::vytvorKaju(MYoblicej *oblicej){

    this->oblicej = oblicej;
    this->open("../masks/gott.png");
    this->open_mask("../masks/gott_mask2.png");
    this->changeSize(0.5);
    this->rotateImage(this->oblicej->uhel);

}
void MYmaska::vytvorKlobouk(MYoblicej *oblicej){

    this->oblicej = oblicej;
    this->open("../masks/klobouk.png");
    this->open_mask("../masks/klobouk_mask.png");
    this->changeSize(oblicej->vzdalenost_oci*4/source->width);

    this->rotateImage(this->oblicej->uhel);

}

void MYmaska::vytvorPusu(MYoblicej * oblic){
    static int i = 1;
    this->oblicej = oblic;


    MYvideo *prd = new MYvideo();
        prd->open("../masks/pusa.avi");
        this->open_mask("../masks/pusa_mask.png");

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
uchar MYmaska::interpolate(uchar *barva, uchar *barva2, int krok, int pocet_kroku){
    if(barva < barva2){
        return ((*barva2 - *barva)*(krok/pocet_kroku)) + *barva;
    }else{
        return ((*barva - *barva2)*(1 - (krok/pocet_kroku))) + *barva2;
    }
}

void MYmaska::skryjOci(MYoblicej *oblicej, IplImage *img){
    this->oblicej = oblicej;

    this->source = cvCreateImage(cvSize(img->width,img->height),IPL_DEPTH_8U, 3);
    this->mask = cvCreateImage(cvSize(img->width,img->height),IPL_DEPTH_8U, 3);
    cvCopy(img, this->mask);
    // naalokovan prostor

    for(int i = 0; i < this->source->height; i++ ){
        for(int j = 0 ; j < this->source->width; j++){
            CV_IMAGE_ELEM( this->source, uchar, i, (j)*3)   = 255 - CV_IMAGE_ELEM( img, uchar, i, (j)*3); //b
            CV_IMAGE_ELEM( this->source, uchar, i, (j)*3+1) = 255 - CV_IMAGE_ELEM( img, uchar, i, (j)*3+1); //g
            CV_IMAGE_ELEM( this->source, uchar, i, (j)*3+2) = 255 - CV_IMAGE_ELEM( img, uchar, i, (j)*3+2); //r
        }
    }
    this->changeSize(1.0);
    this->rotateImage(this->oblicej->uhel);
}



#define PUSA 0
#define KNIR 1
#define KAJA 2
#define KLOBOUK 3
#define OCI 4
IplImage* MYmaska::addMask(IplImage *frame,int typ){
//    cvSetImageROI(frame, cvRect(mezi_oci_x - mask->rotated->width/2,
  //                              mezi_oci_y - mask->rotated->height/2));


  int start_y = 0;
  int start_x = 0;

    const int Thres = 100;
    const int HT = 50;
    int x,y,i,j;

    if(typ == KNIR){
        start_y = this->oblicej->sour_y + this->oblicej->knirek_y - this->rotated->height/2;
        start_x = this->oblicej->sour_x + this->oblicej->knirek_x - this->rotated->width/2;
    }
    else if(typ == PUSA){
        start_y = this->oblicej->sour_y + this->oblicej->pusa_y - this->rotated->height/2;
        start_x = this->oblicej->sour_x + this->oblicej->pusa_x - this->rotated->width/2;
    }
    else if(typ == KAJA){
        start_y = this->oblicej->sour_y + this->oblicej->stred_obliceje_y - this->rotated->height/2;
        start_x = this->oblicej->sour_x + this->oblicej->stred_obliceje_x - this->rotated->width/2;
    }
    else if(typ == KLOBOUK){
        start_y = this->oblicej->sour_y -45 - this->rotated->height/2;
        start_x = this->oblicej->sour_x + this->oblicej->stred_obliceje_x - this->rotated->width/2;
    }
    else if(typ == OCI){
        start_y = this->oblicej->sour_y + this->oblicej->mezi_oci_y - this->rotated->height/2;
        start_x = this->oblicej->sour_x + this->oblicej->mezi_oci_x - this->rotated->width/2;
    }

    for (i = start_y; i < start_y + this->rotated->height; i++) {
        for (j = start_x; j < start_x + this->rotated->width; j++) {


			float vaha_r = 1.0-(CV_IMAGE_ELEM( this->mask3, uchar, i - start_y, (j - start_x)*3+0)/255.0);
			float vaha_g = 1.0-(CV_IMAGE_ELEM( this->mask3, uchar, i - start_y, (j - start_x)*3+1)/255.0);
			float vaha_b = 1.0-(CV_IMAGE_ELEM( this->mask3, uchar, i - start_y, (j - start_x)*3+2)/255.0);

            //cout << "vaha: " << vaha_r << endl;

			int barva_r = 0;
			int barva_g = 0;
			int barva_b = 0;


			barva_r = vaha_r*CV_IMAGE_ELEM( this->rotated, uchar, i - start_y, (j - start_x)*3+0) + (1.0-vaha_r)*CV_IMAGE_ELEM( frame, uchar, i, j*3+0);
			barva_g = vaha_g*CV_IMAGE_ELEM( this->rotated, uchar, i - start_y, (j - start_x)*3+1) + (1.0-vaha_g)*CV_IMAGE_ELEM( frame, uchar, i, j*3+1);
			barva_b = vaha_b*CV_IMAGE_ELEM( this->rotated, uchar, i - start_y, (j - start_x)*3+2) + (1.0-vaha_b)*CV_IMAGE_ELEM( frame, uchar, i, j*3+2);

			if(barva_r>255) barva_r = 255;
			if(barva_g>255) barva_g = 255;
			if(barva_b>255) barva_b = 255;

			if(barva_r<0) barva_r = 0;
			if(barva_g<0) barva_g = 0;
			if(barva_b<0) barva_b = 0;

			((uchar*)(frame->imageData + i * frame->widthStep))[j*3+0]   = (uchar)barva_r;
			((uchar*)(frame->imageData + i * frame->widthStep))[j*3+1]   = (uchar)barva_g;
			((uchar*)(frame->imageData + i * frame->widthStep))[j*3+2]   = (uchar)barva_b;


//			if(CV_IMAGE_ELEM( mask->mask3, uchar, i - start_y, (j - start_x)*3)   < Thres &&
//			   CV_IMAGE_ELEM( mask->mask3, uchar, i - start_y, (j - start_x)*3+1) > 255-HT &&
//			   CV_IMAGE_ELEM( mask->mask3, uchar, i - start_y, (j - start_x)*3+2) < Thres) {
//
//				continue;
//            }
//            else{
//                ((uchar*)(frame->imageData + i * frame->widthStep))[j*3]   = CV_IMAGE_ELEM( mask->rotated, uchar, i - start_y, (j - start_x)*3); //b
//                ((uchar*)(frame->imageData + i * frame->widthStep))[j*3+1] = CV_IMAGE_ELEM( mask->rotated, uchar, i - start_y, (j - start_x)*3+1); //g
//                ((uchar*)(frame->imageData + i * frame->widthStep))[j*3+2] = CV_IMAGE_ELEM( mask->rotated, uchar, i - start_y, (j - start_x)*3+2); //r
//
//            }
        }
    }

    return frame;
}


