#include "SistemDecizional.h"

long double decideDirectiaDrumSimplu(uint8_t linie) //Se va modifica pentru obstacole si curbe
{
	long double temp = 128;
	temp-=2*SERVOMOTOR_THRESHOLD;
	temp=(linie - SERVOMOTOR_THRESHOLD)/temp;
	temp*=2;
	temp-=1;
	/*
	long double temp;
	if(linie<63)
	{
		if(linie<SERVOMOTOR_THRESHOLD)
		{	
			return - 1;
		}
		temp = linie-SERVOMOTOR_THRESHOLD;
		return -(temp/(63-SERVOMOTOR_THRESHOLD));
	}
	else
	{
 		if(linie>127-SERVOMOTOR_THRESHOLD)
		{	
			return 1;
		}
		temp = linie-63;
		return (temp/(127-SERVOMOTOR_THRESHOLD-63));
	}
	*/
	return temp;
}
double decideVitezaDrumSimplu(uint8_t linie)
{
	double temp;
	if(linie<63)
	{
		if(linie<SERVOMOTOR_THRESHOLD)
		{	
			return 0;
		}
		temp = 63-linie;
		temp = (temp/(63-SERVOMOTOR_THRESHOLD));
	}
	else
	{
		if(linie>127-SERVOMOTOR_THRESHOLD)
		{	
			return 0;
		}
		temp = linie-63;
		temp = (temp/(127-SERVOMOTOR_THRESHOLD-63));
	}
	temp *= MOTOARE_VITEZA_MAX_MS;
	return temp;
}