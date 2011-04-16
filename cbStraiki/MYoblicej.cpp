#include "MYoblicej.h"
#include "MYdisplay.h"
#include "MYvideo.h"

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

    this->prave_oko_x = Reye.x;
    this->prave_oko_y = Reye.y;

    this->leve_oko_x = Leye.x;
    this->leve_oko_y = Leye.y;

    _CenterPoint(Face);

    _Eyes(this->Reye,this->Leye);
    vypocti_klicove_body();
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
void MYoblicej::DrawOblicej(IplImage * img,int typ){


    switch (typ)
    {
    	case KLOBOUK:{

            MYmaska *mask = new MYmaska(img);
            mask->vytvorKlobouk(this);
            mask->addMask(img,KLOBOUK);
            delete mask;

    		break;
    	}
    	case KAJA:{

            MYmaska *mask = new MYmaska(img);
            mask->vytvorKaju(this);
            mask->addMask(img,KAJA);
            delete mask;

    		break;
    	}
    	case PUSA:{

            MYmaska *mask = new MYmaska(img);
            mask->vytvorPusu(this);
            mask->addMask(img,PUSA);
            delete mask;

    		break;
    	}
    	case KNIR:{

            MYmaska *mask = new MYmaska(img);
            mask->vytvorKnirek(this);
            mask->addMask(img,KNIR);
            delete mask;

    		break;
    	}
    	case OCI:{

            MYmaska *mask = new MYmaska(img);
            mask->skryjOci(this);
            mask->addMask(img,OCI);
            delete mask;

    		break;
    	}
    	case ROHY:{
            MYmaska *mask = new MYmaska(img);
            mask->vytvorRohy(this);
            mask->addMask(img,ROHY);
            break;
    	}
    	default:
    		break;
    }


//       MYmaska *mask = new MYmaska(img);
//            mask->vytvorKnirek(this);
//            mask->addMask(img,0);
//            delete mask;
//
//    MYmaska *maska2 = new MYmaska(img);
//            maska2->vytvorKnirek(this);
//            maska2->addMask(img,1);
//            delete maska2;

}

void MYoblicej::DrawHighPoints(IplImage * img){
    MYdisplay::DrawPoint(img,Pcent,5,2,CV_RGB(0,0,0));
    MYdisplay::DrawPoint(img,PeyeL,5,2,CV_RGB(0,128,128));
    MYdisplay::DrawPoint(img,PeyeR,5,2,CV_RGB(0,0,128));
    MYdisplay::DrawPoint(img,Peyes,5,2,CV_RGB(128,128,128));

    MYdisplay::DrawPoint(img,Pmoust,5,2,CV_RGB(255,255,128));

    MYdisplay::DrawPoint(img,Phead,6,2,CV_RGB(255,0,0));

}

void MYoblicej::DrawVodiciObdel(IplImage * img){

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

void MYoblicej::_CenterPoint(CvRect F){
    Pcent.x = F.x + F.width/2;
    Pcent.y = F.y + F.height/2;
}

void MYoblicej::_Eyes(CvRect R, CvRect L){
    PeyeL = cvPoint(L.x+L.width/2,L.y+L.height/2);
    PeyeR = cvPoint(R.x+R.width/2,R.y+R.height/2);

    Peyes = cvPoint(PeyeL.x+abs(PeyeR.x-PeyeL.x)/2,PeyeL.y + abs(PeyeR.y-PeyeL.y)/2);

   // cout << mezi_oci_x << " xpakx " << mezi_oci_y << endl;
}

void MYoblicej::_Moustache(){
  //  Pmoust = cvPoint(this->knirek_x,this->knirek_y);
}

void MYoblicej::_Hat(CvRect F){
   // Phead = cvPoint(F.x + F.width/2,F.y);

}

void MYoblicej::_makeMoustache(){
//    IplImage * Tmoust;
//    MYdisplay::LoadImage( &Tmoust, "../masks/mustache.png");
//    MYdisplay::ShowImage(Tmoust,'x');

}
//vypocte klicove body
void MYoblicej::vypocti_klicove_body(){

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
	knirek_x += Peyes.x;
	knirek_y = cos(uhel)*vzdalenost_oci*0.8;
	knirek_y += Peyes.y;

//	Pkaja.x = -sin(uhel)*vzdalenost_oci*0.1;
//	Pkaja.x*=-1;
//	Pkaja.x = Peyes.x;

	Pkaja = cvPoint(+sin(uhel)*this->sirka*0.12+Pcent.x,-cos(uhel)*this->sirka*0.12+Pcent.y);
    Phead = cvPoint(+sin(uhel)*this->sirka*0.75+Pcent.x,-cos(uhel)*this->sirka*0.75+Pcent.y);
    Pmoust = cvPoint(-sin(uhel)*this->sirka*0.3+Pcent.x,+cos(uhel)*this->sirka*0.3+Pcent.y);
    Prohy = cvPoint(+sin(uhel)*this->sirka*1.10+Pcent.x,-cos(uhel)*this->sirka*1.1+Pcent.y);
//	Pkaja.y = -cos(uhel)*vzdalenost_oci*0.1;
//	Pkaja.y = Peyes.y;

//	pusa_x = sin(uhel)*vzdalenost_oci*1.2;
//	pusa_x*=-1;
////	pusa_x += mezi_oci_x;
//	pusa_y = cos(uhel)*vzdalenost_oci*1.2;
////	pusa_y += mezi_oci_y;

	stred_obliceje_x = -sin(uhel)*vzdalenost_oci*1.3;
	stred_obliceje_x*=-1;
	stred_obliceje_x += mezi_oci_x;
	stred_obliceje_y = -cos(uhel)*vzdalenost_oci*1.3;
	stred_obliceje_y += mezi_oci_y;

    //cout << Pkaja.x << " x " << Pkaja.y << endl;
	//knirek_y -= 70;//kaja gott
//	this->uhel = (uhel/(2*M_PI))*360.0;
}

void MYoblicej::ber_v_uvahu(MYoblicej *pre_ksicht){

    if(pre_ksicht==NULL) return;

    if(this->uhel>3.1415926535){
        this->uhel -= 6.283185307;
    }
    if(pre_ksicht->uhel>3.1415926535){
        pre_ksicht->uhel -= 6.283185307;
    }

    this->uhel = (pre_ksicht->uhel+pre_ksicht->uhel+this->uhel)/3.0;
    this->sirka = (pre_ksicht->sirka+this->sirka)/2.0;
    this->vyska = (pre_ksicht->vyska+this->vyska)/2.0;
    this->prave_oko_x = (pre_ksicht->prave_oko_x+this->prave_oko_x)/2.0;
    this->prave_oko_y = (pre_ksicht->prave_oko_y+this->prave_oko_y)/2.0;
    this->leve_oko_x = (pre_ksicht->leve_oko_x+this->leve_oko_x)/2.0;
    this->leve_oko_y = (pre_ksicht->leve_oko_y+this->leve_oko_y)/2.0;


}
