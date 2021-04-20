#include "MKL25Z4.h"
#include "Motoare.h"
#include "PortsSetup.h"
#include "Camera.h"
#include "SistemDecizional.h"
#include "SenzoriDistanta.h"
#include "Uart.h"
#include "PID.h"
#include "math.h"


extern long double vitezaCurenta;
extern uint8_t linie;

extern float volatile viteza;
extern struct PID pid;

extern long double volatile distantaS;
extern long double volatile distantaD;
extern long double volatile distantaC;

static uint8_t stare = STATE_START;

static long double directie;

void testSenzorDistanta(void)
{
	while(1)
	{
		viteza=0;
		continue;
		if(distantaD < 8)
		{
			viteza = 0;
		}
		else if(distantaD < 60)
		{
			viteza = distantaD/100;
		}
		else if(distantaD > 10)
		{
			viteza = 1;
		}
		if(viteza>3)
			viteza = 3;
	}
}

void testCamera(void)
{
	while(1)
	{
		directie = decideDirectiaDrumSimplu(linie);
		SetareUnghi(directie + SERVOMOTOR_STRAIGHT_ERR);
	}
}

void testDrumRudimentar(void)
{
	
	while(1)
	{
		viteza = 1.5;
		directie = decideDirectiaDrumSimplu(linie);
		SetareUnghi(directie + SERVOMOTOR_STRAIGHT_ERR);
	}
}

int main (void) {

	directie = 0;
	pid = initializarePID(PID_TS, PID_KP, PID_KI, PID_KD);
	SIMSetup();
	InitializarePiniParteMecanica();
	initializareCamera();
	initializarePIT();
	initializareSenzorTuratie();
	initializareSenzoriDistanta();
	startCamera();
	UartInit(9900); //9900
	SetareUnghi(SERVOMOTOR_STRAIGHT_ERR); 
	// testDrumRudimentar();
	//testCamera();
	//testSenzorDistanta(); 
	
	while(1){
		if(linie>=63 + LINE_MAX_ERROR_MID || linie<=64 - LINE_MAX_ERROR_MID)
		{
			stare = STATE_DRUM_CURBA;
		}
		else
		{
			stare = STATE_DRUM_DREPT;
		}
	  switch(stare)
		{
			case STATE_DRUM_DREPT:
				viteza = MOTOARE_VITEZA_MAX_MS;
				SetareUnghi(SERVOMOTOR_STRAIGHT_ERR);
				break;
			case STATE_DRUM_CURBA:
				if(linie>=63 + LINE_MAX_ERROR_FOR_SPEED || linie<=64 - LINE_MAX_ERROR_FOR_SPEED)
				{
					viteza = MOTOARE_VITEZA_CURBA_MS;
				}
				else
				{
					viteza = MOTOARE_VITEZA_MAX_MS;
				}
				viteza = MOTOARE_VITEZA_CURBA_MS;
				directie = decideDirectiaDrumSimplu(linie);
				SetareUnghi(directie);
				break;
			default:
				break;
		}
	}
}

 
