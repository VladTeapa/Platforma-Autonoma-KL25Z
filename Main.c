#include "MKL25Z4.h"
#include "Motoare.h"
#include "PortsSetup.h"
#include "Camera.h"
#include "SistemDecizional.h"
#include "Uart.h"
#include "PID.h"
#include "math.h"


extern long double vitezaCurenta;
extern uint8_t linie;

extern long double volatile viteza;
extern struct PID pid;

extern int8_t volatile sens;


static volatile uint8_t stare = STATE_START;



int main (void) {
	
	long double directie;

	for(int i=0;i<100000000;i++)
		{i=i+1;
			directie = i;
		}
	directie = 0;
	pid = initializarePID(PID_TS, PID_KP, PID_KI, PID_KD);
	SIMSetup();
	InitializarePiniParteMecanica();
	initializareCamera();
	initializarePIT();
	startCamera();
	UartInit(9900);
	int aux=0;
	SetareUnghi(SERVOMOTOR_STRAIGHT_ERR);
	while(1){
		if(linie>=63 - LINE_MAX_ERROR_MID || linie<=64+LINE_MAX_ERROR_MID)
		{
			if(stare!=STATE_DRUM_DREPT && stare!=STATE_DRUM_CURBATODREPT)
			{
					stare = STATE_DRUM_CURBATODREPT;
			}
		}
		else
		{
			if(stare!=STATE_DRUM_DREPTTOCURBA && stare!=STATE_DRUM_CURBA)
			{
				stare = STATE_DRUM_DREPTTOCURBA;
			}
		}
	  switch(stare)
		{
			case STATE_DRUM_DREPT:
				break;
			case STATE_DRUM_CURBATODREPT:
				viteza = MOTOARE_VITEZA_MAX_MS;
				SetareUnghi(SERVOMOTOR_STRAIGHT_ERR);
				stare = STATE_DRUM_DREPT;
				break;
			case STATE_DRUM_DREPTTOCURBA:
				viteza = -1;
				directie = decideDirectiaDrumSimplu(linie);
				SetareUnghi(directie);
				stare = STATE_DRUM_CURBA;
				break;
			case STATE_DRUM_CURBA:
				viteza = MOTOARE_VITEZA_FRANARE_MS;
				directie = decideDirectiaDrumSimplu(linie);
				SetareUnghi(directie);
				break;
			default:
				break;
		}
	}
}

 
