#ifndef MYOBLICEJ_H
#define MYOBLICEJ_H

class MYoblicej
{

//promenne
private:
	int sour_x,sour_y;
	int vyska, sirka;
	int prave_oko_x, prave_ok_y;
	int leve_oko_x,  leve_oko_y;
	float uhel;

//funkce
public:
	MYoblicej();	//konstruktor
	virtual ~MYoblicej();	//destruktor
	void vypocti_klicove_body();
	
};

#endif // MYOBLICEJ_H
