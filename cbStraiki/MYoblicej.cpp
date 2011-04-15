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

	this->uhel = (uhel/(2*M_PI))*360.0;
}
