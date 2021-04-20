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
	pid = initializarePID(PID_TS, PID_KP, PID_KI, PID_KD);
	SIMSetup();
	InitializarePiniParteMecanica();
	initializareCamera();
	initializarePIT();
	initializareSenzorTuratie();
	initializareSenzoriDistanta();
	startCamera();
	
	//9900 pentru XBEE, 115200 pentru UART prin cablu
	uartInit(9900);

	//Unghiul initial este de 0 grade
	SetareUnghi(SERVOMOTOR_STRAIGHT_ERR); 
	
	while(1){
		
		//Se testeaza aparitia unei curbe
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
			
			//Pentru drumul drept setam o viteza mai mare si unghiul corespunzator
			case STATE_DRUM_DREPT:
				viteza = MOTOARE_VITEZA_MAX_MS;
				SetareUnghi(SERVOMOTOR_STRAIGHT_ERR);
				break;
			
			//Pentru curbe, in caz ca nu este una foarte brusca nu are sens sa incetinim
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

 
