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
extern volatile PIDv2 pid;

extern float volatile distantaS;
extern float volatile distantaD;
extern float volatile distantaC;

static uint8_t stare = STATE_DRUM_FARA_OBSTACOL;

static long double directie;

static void testSenzorDistanta(void)
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

static void testCamera(void)
{
	while(1)
	{
		directie = decideDirectiaDrumSimplu(linie);
		SetareUnghi(directie + SERVOMOTOR_STRAIGHT_ERR);
	}
}

static void testDrumRudimentar(void)
{
	
	while(1)
	{
		viteza = 1.5;
		directie = decideDirectiaDrumSimplu(linie);
		SetareUnghi(directie + SERVOMOTOR_STRAIGHT_ERR);
	}
}

int main (void) {

	//Se initializeaza toate modulele si variabilele necesare
	directie = 0;
	initializarePIDv2(PID_TS, PID_KP, PID_KI, PID_KD);
	SIMSetup();
	InitializarePiniParteMecanica();
	initializareCamera();
	initializarePIT();
	initializareSenzorTuratie();
	initializareSenzoriDistanta();
	startCamera();
	
	//9900 pentru XBEE, 115200 pentru UART prin cablu
	uartInit(9600);

	//Unghiul initial este de 0 grade
	SetareUnghi(SERVOMOTOR_STRAIGHT_ERR); 
	
	for(int i=0;i<10000000;i++){
		viteza = 0;
	}
	while(1){
		
		
	  switch(stare)
		{
			
			case STATE_DRUM_FARA_OBSTACOL:
				if(linie>=63 + LINE_MAX_ERROR_FOR_SPEED || linie<=64 - LINE_MAX_ERROR_FOR_SPEED)
				{
					viteza = MOTOARE_VITEZA_CURBA_MS;
				}
				else
				{
					viteza = MOTOARE_VITEZA_MAX_MS;
				}
				
				directie = decideDirectiaDrumSimplu(linie);
				SetareUnghi(directie + SERVOMOTOR_STRAIGHT_ERR);
				break;
			case STATE_DRUM_OBSTACOL_FATA:
				if(distantaC >= DISTANTATHRESHOLD)
					if(distantaD >= DISTANTATHRESHOLD && distantaS >= DISTANTATHRESHOLD)
					{
						stare = STATE_DRUM_FARA_OBSTACOL;
						break;
					}
				viteza = ((int) (MAX_VITEZA_MULTIPLIER * (distantaC / DISTANTATHRESHOLD))) * NRINPUTCOEFF;
				if(distantaD < DISTANTATHRESHOLD || distantaS < DISTANTATHRESHOLD)
				{
					stare = STATE_DRUM_OBSTACOL_DIAG;
				}
				break;
			case STATE_DRUM_OBSTACOL_DIAG:
				viteza = NRINPUTCOEFF * MIN_VITEZA_MULTIPLIER / 2;
				if(distantaD < DISTANTATHRESHOLD)
				{
					SetareUnghi(1);
				}
				else if(distantaS < DISTANTATHRESHOLD)
				{
					SetareUnghi(-1);
				}
				if(distantaC >= DISTANTATHRESHOLD)
				{
					stare = STATE_DRUM_OBSTACOL_LAT;
				}
				break;
			case STATE_DRUM_OBSTACOL_LAT:
				break;
			default:
				break;
		}
	}
}

 
