#include "MYoblicej.h"
#include "stdhead.h"
using namespace std;
//konstruktor
MYoblicej::MYoblicej(){
	printf("vytvoren oblicej\n");
}

//destruktor
MYoblicej::~MYoblicej(){
	printf("znicen oblicej\n");
}

//vypocte klicove body
void MYoblicej::vypocti_klicove_body(){

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
