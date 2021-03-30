#include "SistemDecizional.h"

extern uint8_t cameraPixels[128];

uint8_t unghiThreshold = 30;


void decideDirectia(uint8_t linie) //Se va modifica pentru obstacole si curbe
{
	uint8_t temp;
	if(linie<63)
	{
		if(linie<unghiThreshold)
		{	
			SetareUnghi(-1);
			return;
		}
		temp = linie-unghiThreshold;
		SetareUnghi(-(63-unghiThreshold)/temp);
	}
	else
	{
		if(linie>127-unghiThreshold)
		{	
			SetareUnghi(1);
			return;
		}
		temp = linie-63;
		SetareUnghi((127-unghiThreshold-63)/temp);
	}
}
void decideViteza(void)
{
	//Se va modifica pentru obstacole
}