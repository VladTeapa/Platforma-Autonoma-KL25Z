#include "SistemDecizional.h"

inline long double decideDirectiaDrumSimplu(uint8_t linie) //Se va modifica pentru obstacole si curbe
{
	//In functie de linie se calculeaza o valoare pentru unghi intre -1 si 1
	long double temp = 128;
	temp-=2*SERVOMOTOR_THRESHOLD;
	temp=(linie - SERVOMOTOR_THRESHOLD)/temp;
	temp*=2;
	temp-=1;
	return temp;
}

inline float decideVitezaDrumSimplu(uint8_t linie)
{
	//In functie de pozitia liniei, platforma se va deplasa mai repede sau mai incet
	if(linie>=63 + LINE_MAX_ERROR_FOR_SPEED || linie<=64 - LINE_MAX_ERROR_FOR_SPEED)
	{
		return MOTOARE_VITEZA_CURBA_MS;
	}
	else
	{
		return MOTOARE_VITEZA_MAX_MS;
	}
}

