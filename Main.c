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
	uint8_t obstDirectie = OBSTACOL_DREAPTA;
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
				viteza = decideVitezaDrumSimplu(linie);
				directie = decideDirectiaDrumSimplu(linie);
				SetareUnghi(directie + SERVOMOTOR_STRAIGHT_ERR);
				break;
			case STATE_DRUM_OBSTACOL_FATA:
				stare = decideStareDrumObstacolFata(stare, distantaC, distantaD, distantaS);
				viteza = decideVitezaObstacolFata(distantaC);			
				break;
			case STATE_DRUM_OBSTACOL_DIAG:
				viteza = MOTOARE_VITEZA_OBSTACOL;
				if(distantaD < DISTANTA_THRESHOLD)
				{
					obstDirectie = OBSTACOL_DREAPTA;
					SetareUnghi(1);
				}
				else if(distantaS < DISTANTA_THRESHOLD)
				{
					obstDirectie = OBSTACOL_STANGA;
					SetareUnghi(-1);
				}
				if(distantaC >= DISTANTA_THRESHOLD)
				{
					stare = STATE_DRUM_OBSTACOL_LAT;
				}
				break;
			case STATE_DRUM_OBSTACOL_LAT:
				if(obstDirectie == OBSTACOL_DREAPTA)
				{
					if(distantaD > DISTANTA_THREHOLD_LAT_MAX)
					{
						SetareUnghi(1);
					}
					if(distantaD < DISTANTA_THREHOLD_LAT_MIN)
					{
						SetareUnghi(-1);
					}
				}
				else
				{
					if(distantaS > DISTANTA_THREHOLD_LAT_MAX)
					{
						SetareUnghi(-1);
					}
					if(distantaS < DISTANTA_THREHOLD_LAT_MIN)
					{
						SetareUnghi(1);
					}
				}
				if(DISTANTA_THRESHOLD > distantaS)
					stare = STATE_DRUM_FARA_OBSTACOL;
				break;
			default:
				break;
		}
	}
}

 
