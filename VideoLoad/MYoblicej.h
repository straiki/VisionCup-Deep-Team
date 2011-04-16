#ifndef MYOBLICEJ_H
#define MYOBLICEJ_H

class MYoblicej
{

//promenne
private:


//funkce
public:
	MYoblicej();	//konstruktor
	virtual ~MYoblicej();	//destruktor
	void vypocti_klicove_body();
    static void zeroesOblicej(MYoblicej *);

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
};

#endif // MYOBLICEJ_H
