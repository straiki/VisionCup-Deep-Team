#include "MYoblicej.h"
#include "MYdisplay.h"

#include "stdhead.h"
using namespace std;
//konstruktor
MYoblicej::MYoblicej(CvRect Face, CvRect rEye1, CvRect rEye2){
    this->sour_x = Face.x;
    this->sour_y = Face.y;
    this->vyska = Face.height;
    this->sirka = Face.width;

//prorirazeni Ok
    this->Reye = rEye1;
    this->Leye = rEye2;
    swapEyes(&this->Reye,&this->Leye);

    _CenterPoint(Face);

    vypocti_klicove_body();
    _Eyes(this->Reye,this->Leye);
    _Moustache();
    _Hat(Face);
}

//destruktor
MYoblicej::~MYoblicej(){

}

void MYoblicej::swapEyes(CvRect * R, CvRect * L){
        if( R->x < L->x){ // R je vice v levo
            CvRect temp;
            temp = *R;
            *R = *L;
            *L = temp;
        }
}
void MYoblicej::DrawOblicej(IplImage * img){
        CvPoint h1 = cvPoint(sour_x,sour_y);
        CvPoint h2 = cvPoint(sour_x+sirka,sour_y+vyska);

        cvRectangle(img,h1,h2,CV_RGB(128,0,0), 1, 8, 0);

    	//Vykresleni Oci
        h1 = cvPoint(Reye.x,Reye.y);
        h2 = cvPoint(Reye.x + Reye.width,Reye.y + Reye.height);
    	cvRectangle(img,h1,h2,CV_RGB(0,0,128), 1, 8, 0);

        h1 = cvPoint(Leye.x,Leye.y);
        h2 = cvPoint(Leye.x + Leye.width,Leye.y + Leye.height);
    	cvRectangle(img,h1,h2,CV_RGB(0,128,128), 1, 8, 0);
}

void MYoblicej::DrawHighPoints(IplImage * img){

    MYdisplay::DrawPoint(img,Pcent,5,2,CV_RGB(0,0,0));
    MYdisplay::DrawPoint(img,PeyeL,5,2,CV_RGB(0,128,128));
    MYdisplay::DrawPoint(img,PeyeR,5,2,CV_RGB(0,0,128));
    MYdisplay::DrawPoint(img,Peyes,5,2,CV_RGB(128,0,128));

    MYdisplay::DrawPoint(img,Pmoust,5,2,CV_RGB(255,255,128));

    MYdisplay::DrawPoint(img,Phead,6,2,CV_RGB(255,0,0));

}

void MYoblicej::_CenterPoint(CvRect F){
    Pcent.x = F.x + F.width/2;
    Pcent.y = F.y + F.height/2;
}

void MYoblicej::_Eyes(CvRect R, CvRect L){
    PeyeL = cvPoint(L.x+L.width/2,L.y+L.height/2);
    PeyeR = cvPoint(R.x+R.width/2,R.y+R.height/2);

    //! @todo  doplnit vypocet stredu mezi ocima
    Peyes = cvPoint(this->mezi_oci_x,this->mezi_oci_y);

   // cout << mezi_oci_x << " xpakx " << mezi_oci_y << endl;
}

void MYoblicej::_Moustache(){
    Pmoust = cvPoint(this->knirek_x,this->knirek_y);
}

void MYoblicej::_Hat(CvRect F){
    Phead = cvPoint(F.x + F.width/2,F.y);

}
//vypocte klicove body
void MYoblicej::vypocti_klicove_body(){

    prave_oko_x = PeyeR.x;
    prave_oko_y = PeyeR.y;

    leve_oko_x = PeyeL.x;
    leve_oko_y = PeyeL.y;

    if(prave_oko_x<leve_oko_x){
		int pomoc_x = prave_oko_x;
		int pomoc_y = prave_oko_y;
		prave_oko_x = leve_oko_x;
		prave_oko_y = leve_oko_y;
		leve_oko_x = pomoc_x;
		leve_oko_y = pomoc_y;
	}

	printf("pocitam klicove body\n");
	//rozdil mezi ocima
	delta_x = prave_oko_x-leve_oko_x;
	delta_y = prave_oko_y-leve_oko_y;

	//stred mezi ocima
	float mensi = 0;
	if(prave_oko_x<leve_oko_x) mensi = prave_oko_x;
	else mensi = leve_oko_x;
	mezi_oci_x = fabs((prave_oko_x-leve_oko_x)/2.0)+mensi;

	if(prave_oko_y<leve_oko_y) mensi = prave_oko_y;
	else mensi = leve_oko_y;
	mezi_oci_y = fabs((prave_oko_y-leve_oko_y)/2.0)+mensi;

	//uhel
	uhel = atan((float)delta_y/(float)delta_x);
	if     ((delta_x>0)&&(delta_y>0)) uhel += 0;
	else if((delta_x<0)&&(delta_y>0)) uhel +=M_PI;
	else if((delta_x<0)&&(delta_y<0)) uhel +=M_PI;
	else if((delta_x>0)&&(delta_y<0)) uhel +=2*M_PI;

    vzdalenost_oci = sqrt(delta_x*delta_x+delta_y*delta_y);
	knirek_x = sin(uhel)*vzdalenost_oci*0.8;
	knirek_x*=-1;
	knirek_x += mezi_oci_x;
	knirek_y = cos(uhel)*vzdalenost_oci*0.8;
	knirek_y += mezi_oci_y;

	pusa_x = sin(uhel)*vzdalenost_oci*1.2;
	pusa_x*=-1;
	pusa_x += mezi_oci_x;
	pusa_y = cos(uhel)*vzdalenost_oci*1.2;
	pusa_y += mezi_oci_y;

    stred_obliceje_x = mezi_oci_x;
	stred_obliceje_y = mezi_oci_y-10;

    cout << knirek_x << " x " << knirek_x << endl;
	//knirek_y -= 70;//kaja gott
//	this->uhel = (uhel/(2*M_PI))*360.0;
}

void MYoblicej::zeroesOblicej(MYoblicej * o){
    o->sour_x = 0;
    o->sour_y = 0;

    o->prave_oko_x = 0;
    o->leve_oko_x = 0;
    o->leve_oko_y = 0;
    o->prave_oko_y = 0;


}
