#include "SistemDecizional.h"

extern uint8_t cameraPixels[128];

uint8_t unghiThreshold = 30;


double decideDirectia(uint8_t linie) //Se va modifica pentru obstacole si curbe
{
	uint8_t temp;
	if(linie<63)
	{
		if(linie<unghiThreshold)
		{	
			return - 1;
		}
		temp = linie-unghiThreshold;
		return (-(63-unghiThreshold)/temp);
	}
	else
	{
		if(linie>127-unghiThreshold)
		{	
			return 1;
		}
		temp = linie-63;
		return ((127-unghiThreshold-63)/temp);
	}
}
void decideViteza(void)
{
	//Se va modifica pentru obstacole
}