#include "MKL25Z4.h"
#include "Motoare.h"
#include "PortsSetup.h"
#include "Camera.h"
#include "SistemDecizional.h"
#include "SenzoriDistanta.h"
#include "Uart.h"
#include "PID.h"

extern uint8_t linie;

extern float volatile viteza;

extern float volatile distantaS;
extern float volatile distantaD;
extern float volatile distantaC;

uint8_t lastObst = 2;

static uint8_t stare = STATE_DRUM_FARA_OBSTACOL;

static long double directie;

int main (void) {
	//Se initializeaza toate modulele si variabilele necesare
	directie = 0;
	SIMSetup();
	
	initializarePID(PID_TS, PID_KP, PID_KI, PID_KD);
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
			
				//Daca dorim sa nu folosim functionalitatea de ocolire de obstacole se poate seta macrodefinitia la valoarea 1
				#if (DEZACTIVARE_MODUL_DIST == 0)
					if(distantaC<DISTANTA_THRESHOLD_MIJLOC || distantaD < DISTANTA_THRESHOLD || distantaS < DISTANTA_THRESHOLD)
					{
						stare = STATE_DRUM_OBSTACOL;
						viteza = 0;
					}
				#endif
				break;
			#if (DEZACTIVARE_MODUL_DIST == 0)
				case STATE_DRUM_OBSTACOL:
					viteza = MOTOARE_VITEZA_OBSTACOL;
				
					//Daca avem obstacol pe laterale ne departam de cel mai apropiat
					if(distantaD < DISTANTA_THRESHOLD || distantaS < DISTANTA_THRESHOLD)
					{
						if(distantaD < distantaS)
						{
							lastObst = 0;
							SetareUnghi(-1);
						}
						else
						{
							lastObst = 1;
							SetareUnghi(1);
						}
						break;
					}
					//Daca nu avem niciun obstacol pe nicio directie se revine la detectarea liniei si mentinerea drumului
					if(distantaC > DISTANTA_THRESHOLD_MIJLOC)
					{
						if(lastObst == 0)
							SetareUnghi(0.1f);
						if(lastObst == 1)
							SetareUnghi(-0.1f);
						stare = STATE_DRUM_FARA_OBSTACOL;
						lastObst = 2;
					}
					
					break;
			#endif
			default:
				break;
		}
	}
}

 
