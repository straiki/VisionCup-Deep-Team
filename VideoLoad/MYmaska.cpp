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
    if(this->source) cvReleaseImage(&this->source);
    if(this->edited) cvReleaseImage(&this->edited);
    if(this->rotated) cvReleaseImage(&this->rotated);
    if(this->mask) cvReleaseImage(&this->mask);
    if(this->mask2) cvReleaseImage(&this->mask2);
    if(this->mask3) cvReleaseImage(&this->mask3);
}

void MYmaska::open(string name){
    this->source = cvLoadImage(name.c_str());
}

void MYmaska::open_mask(string name){
    this->mask = cvLoadImage(name.c_str());
}

void MYmaska::changeSize(float size){

cout << size << endl;
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
    float velikost = ((oblicej->sirka)*0.9)/(source->width*1.0);
    this->changeSize(velikost);
    this->rotateImage(this->oblicej->uhel);

}

void MYmaska::vytvorKaju(MYoblicej *oblicej){

    this->oblicej = oblicej;
    this->open("../masks/gott.png");
    this->open_mask("../masks/gott_mask2.png");
    float velikost = ((oblicej->sirka)*1.5)/(source->width*1.0);
    this->changeSize(velikost);
    this->rotateImage(this->oblicej->uhel);

}

void MYmaska::vytvorKlobouk(MYoblicej *oblicej){

    this->oblicej = oblicej;
    this->open("../masks/klobouk.png");
    this->open_mask("../masks/klobouk_mask.png");
    float velikost = ((oblicej->sirka)*1.5)/(source->width*1.0);
    this->changeSize(velikost);
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
        this->source = cvCreateImage(cvGetSize(akt),
                               akt->depth,
                               akt->nChannels);
        cvCopy(akt,this->source);
        cout << "ok" << endl;

        i+=5;

    float velikost = ((oblicej->sirka)*0.9)/(source->width*1.0);
    this->changeSize(velikost);
    this->rotateImage(this->oblicej->uhel);

    delete prd;
    //cvReleaseImage(&akt);
}
uchar MYmaska::interpolate(int barva2, int barva, int krok, int pocet_kroku){
   // return (krok % 2) ? (barva) : (barva2);

    //if(barva < barva2){

        return (uchar)(((float)(barva2 - barva)*(1 - krok/(float)pocet_kroku)) + (float)barva);
    //}else{
    //    return ((barva - barva2)*((krok/(float)pocet_kroku))) + barva2;
    //}

}

void MYmaska::skryjOci(MYoblicej *oblicej){

    int prodluz = 30;

    this->oblicej = oblicej;

    this->open("../masks/oko.png"); //this->source = cvCreateImage(cvSize(img->width,img->height),IPL_DEPTH_8U, 3);
    this->open_mask("../masks/oko_mask.png");
    this->changeSize(0.1);
    this->rotateImage(this->oblicej->uhel);
    //this->mask = cvCreateImage(cvSize(img->width,img->height),IPL_DEPTH_8U, 3);
    //cvCopy(img, this->mask);
    // naalokovan prostor
   // CvRect rect = cvRect(oblicej->leve_oko_x + oblicej->sour_x - sirka/2, oblicej->leve_oko_y + oblicej->sour_y - vyska/2, sirka, vyska);
   CvRect rect = this->oblicej->Leye;
   rect.x -= prodluz/2;
   rect.y -= prodluz/2;
   rect.width  = this->oblicej->Leye.width+prodluz;
   rect.height = this->oblicej->Leye.height+prodluz;
    cvSetImageROI(this->frame, rect);//jsem na levem oku
int k;
    for(int i = rect.x; i < (rect.x + rect.width); i++ ){
        int bod1B = CV_IMAGE_ELEM( this->frame, uchar, rect.y, (i)*3);//+rect.height-1
        int bod1G = CV_IMAGE_ELEM( this->frame, uchar, rect.y, (i)*3+1);
        int bod1R = CV_IMAGE_ELEM( this->frame, uchar, rect.y, (i)*3+2);
        int bod2B = CV_IMAGE_ELEM( this->frame, uchar, rect.y+rect.height-1, (i)*3);//
        int bod2G = CV_IMAGE_ELEM( this->frame, uchar, rect.y+rect.height-1, (i)*3+1);
        int bod2R = CV_IMAGE_ELEM( this->frame, uchar, rect.y+rect.height-1, (i)*3+2);
        k=0;
        for(int j = rect.y; j < (rect.y + rect.height); j++){
            CV_IMAGE_ELEM( this->frame, uchar, j, (i)*3)   = this->interpolate(bod1B,bod2B,k,rect.height); //b
            CV_IMAGE_ELEM( this->frame, uchar, j, (i)*3+1) = this->interpolate(bod1G,bod2G,k,rect.height); //g
            CV_IMAGE_ELEM( this->frame, uchar, j, (i)*3+2) = this->interpolate(bod1R,bod2R,k,rect.height); //r
             k++;
        }
    }
    cvResetImageROI(this->frame);


    rect = this->oblicej->Reye;
   rect.x -= prodluz/2;
   rect.y -= prodluz/2;
   rect.width  = this->oblicej->Reye.width+prodluz;
   rect.height = this->oblicej->Reye.height+prodluz;
    cvSetImageROI(this->frame, rect);//jsem na levem oku

    for(int i = rect.x; i < (rect.x + rect.width); i++ ){
        int bod1B = CV_IMAGE_ELEM( this->frame, uchar, rect.y, (i)*3);//+rect.height-1
        int bod1G = CV_IMAGE_ELEM( this->frame, uchar, rect.y, (i)*3+1);
        int bod1R = CV_IMAGE_ELEM( this->frame, uchar, rect.y, (i)*3+2);
        int bod2B = CV_IMAGE_ELEM( this->frame, uchar, rect.y+rect.height-1, (i)*3);//
        int bod2G = CV_IMAGE_ELEM( this->frame, uchar, rect.y+rect.height-1, (i)*3+1);
        int bod2R = CV_IMAGE_ELEM( this->frame, uchar, rect.y+rect.height-1, (i)*3+2);
        k=0;
        for(int j = rect.y; j < (rect.y + rect.height); j++){
            CV_IMAGE_ELEM( this->frame, uchar, j, (i)*3)   = this->interpolate(bod1B,bod2B,k,rect.height); //b
            CV_IMAGE_ELEM( this->frame, uchar, j, (i)*3+1) = this->interpolate(bod1G,bod2G,k,rect.height); //g
            CV_IMAGE_ELEM( this->frame, uchar, j, (i)*3+2) = this->interpolate(bod1R,bod2R,k,rect.height); //r
             k++;
        }
    }
    cvResetImageROI(this->frame);

}


IplImage* MYmaska::addMask(IplImage *frame,int typ){
//    cvSetImageROI(frame, cvRect(mezi_oci_x - mask->rotated->width/2,
  //                              mezi_oci_y - mask->rotated->height/2));


  int start_y = 0;
  int start_x = 0;

    const int Thres = 100;
    const int HT = 50;
    int x,y,i,j;

    if(typ == KNIR){
    //    start_y = this->oblicej->sour_y + this->oblicej->knirek_y - this->rotated->height/2;
    //    start_x = this->oblicej->sour_x + this->oblicej->knirek_x - this->rotated->width/2;
    start_x = this->oblicej->Pmoust.x - this->rotated->height/2;
    start_y = this->oblicej->Pmoust.y - this->rotated->height/2;
    }
    else if(typ == PUSA){
    //    start_y = this->oblicej->sour_y + this->oblicej->pusa_y - this->rotated->height/2;
    //    start_x = this->oblicej->sour_x + this->oblicej->pusa_x - this->rotated->width/2;

    start_x = this->oblicej->Pmoust.x - this->rotated->height/2;
    start_y = this->oblicej->Pmoust.y - this->rotated->height/2;

    }
    else if(typ == KAJA){
        start_y = this->oblicej->Pkaja.y - this->rotated->height/2;
        start_x = this->oblicej->Pkaja.x - this->rotated->width/2;
    }
    else if(typ == KLOBOUK){
//        start_y = this->oblicej->sour_y - 45 - this->rotated->height/2;
//        start_x = this->oblicej->sour_x -- this->rotated->height/2;
    start_x = this->oblicej->Phead.x - this->rotated->height/2;
    start_y = this->oblicej->Phead.y - this->rotated->height/2;
    }
    else if(typ == OCI){
    start_x = this->oblicej->Peyes.x - this->rotated->height/2;
    start_y = this->oblicej->Peyes.y - this->rotated->height/2;
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


