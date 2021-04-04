#include "SistemDecizional.h"

extern uint8_t cameraPixels[128];

uint8_t unghiThreshold = 30;


double decideDirectia(uint8_t linie) //Se va modifica pentru obstacole si curbe
{
	double temp;
	if(linie<63)
	{
		if(linie<unghiThreshold)
		{	
			return - 1;
		}
		temp = linie-unghiThreshold;
		return -(temp/(63-unghiThreshold));
	}
	else
	{
 		if(linie>127-unghiThreshold)
		{	
			return 1;
		}
		temp = linie-63;
		return (temp/(127-unghiThreshold-63));
	}
}
void decideViteza(void)
{
	//Se va modifica pentru obstacole
}