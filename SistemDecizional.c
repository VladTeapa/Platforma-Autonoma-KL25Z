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