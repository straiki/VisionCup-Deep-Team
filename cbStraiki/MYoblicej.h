#ifndef MYOBLICEJ_H
#define MYOBLICEJ_H

#include <cv.h>


class MYoblicej
{

//promenne
private:
    /**
    *   Vypocita stred obliceje
    */
    void _CenterPoint(CvRect);
    void _Eyes(CvRect,CvRect);
    void _Moustache();
    void _Hat(CvRect);

    void _makeMoustache();
    void _drawTexture();


//funkce
public:
	MYoblicej(CvRect,CvRect,CvRect);	//konstruktor
	virtual ~MYoblicej();	//destruktor
	void vypocti_klicove_body();
    static void zeroesOblicej(MYoblicej *);


    CvRect Reye, Leye;
    CvPoint PeyeR,PeyeL,Peyes,Pmouth,Pmoust,Pcent,Phead,Pkaja,Prohy,Pscream;
    int sour_x,sour_y;
	int vyska, sirka;
	int prave_oko_x, prave_oko_y;
	int leve_oko_x,  leve_oko_y;
	int mezi_oci_x,  mezi_oci_y;
	int delta_x, delta_y;
	float uhel;
    int knirek_x, knirek_y;
    int pusa_x, pusa_y;
    int stred_obliceje_x, stred_obliceje_y;
	float vzdalenost_oci;


	void DrawOblicej(IplImage *,int typ=0);
	void swapEyes(CvRect *, CvRect*);
	/**
	*   VYkresli dulezite, vypocitane body z obliceje
	*/
	void DrawHighPoints(IplImage *);
	void DrawVodiciObdel(IplImage *);

	void ber_v_uvahu(MYoblicej*);
};

#define PUSA 0
#define KNIR 1
#define KAJA 2
#define KLOBOUK 3
#define OCI 4
#define ROHY 5
#define BRYLE 6
#define BRYLE2 7
#define PIRAT 8
#define SCREAM 9
#define ROUBIK 10

#endif // MYOBLICEJ_H
