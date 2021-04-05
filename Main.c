#include "MKL25Z4.h"
#include "Motoare.h"
#include "PortsSetup.h"
#include "Camera.h"
#include "SistemDecizional.h"
#include "Uart.h"
#include "PID.h"
#include "math.h"


extern double vitezaCurenta;
extern double motoareInputCurent;
extern uint8_t linie;

static volatile uint8_t stare = STATE_START;
double vitezaDeplasare=0;

static void debugFunctieTransferMatlab(void)
{
	double pwm=0;
	double temp = 1;
	unsigned int i;
	while(1)
	{
		if(pwm>1)
			pwm = 0;
		SetareViteza(pwm);
		pwm+=0.1;
		trimiteDate((uint8_t)(pwm*10));
		for(i=0;i<0xFFFFFF;i++)
					temp++;
		trimiteDate((uint8_t)vitezaCurenta);
		for(i=0;i<0xFFFFFF;i++)
					temp++;
	}
}

int main (void) {
	double directie;
	double viteza=0;
	double vitezaMS = 0;

	int8_t sens = MOTOARE_SENS_INAITE;
	struct PID pid;
	pid = initializarePID(PID_TS, PID_KP, PID_KI, PID_KD);
	SIMSetup();
	InitializarePiniParteMecanica();
	initializareCamera();
	initializarePIT();
	startCamera();
	UartInit(9600);
	//if(TURATIE_DEBUG_FUNCTIE_TR == 1)
	//	debugFunctieTransferMatlab();
	while(1){
		/*switch (stare)
		{
			case STATE_START:
				stare = STATE_DRUM_DREPT;
				break;
			case STATE_DRUM_CURBA:
				vitezaMS = decideVitezaDrumSimplu(linie);
				viteza = getNextPid(pid, vitezaMS, vitezaCurenta, viteza);
				directie = decideDirectiaDrumSimplu(linie);
				SetareUnghi(directie);
				if(viteza > 0)
				{
					if(sens == MOTOARE_SENS_SPATE)
					{
						SetareViteza(0);
						sens = MOTOARE_SENS_INAITE;
					}
					SetareSens(sens);
				}
				else
				{
					if(sens == MOTOARE_SENS_INAITE)
					{
						SetareViteza(0);
						sens = MOTOARE_SENS_SPATE;
					}
					SetareSens(sens);
				}
				SetareViteza(viteza);
				if(linie <= 63+LINE_MAX_ERROR_MID || linie>=64-LINE_MAX_ERROR_MID)
				{
					stare = STATE_DRUM_CURBATODREPT;
				}
				break;
			case STATE_DRUM_CURBATODREPT:
				viteza = 0;
				sens = MOTOARE_SENS_INAITE;
				SetareSens(sens);
				SetareViteza(viteza);
				stare = STATE_DRUM_DREPT;
				break;
			
			
			case STATE_DRUM_DREPT:
				viteza = getNextPid(pid, MOTOARE_VITEZA_MAX_MS, vitezaCurenta,viteza);
				if(viteza > 0)
				{
					if(sens == MOTOARE_SENS_SPATE)
					{
						SetareViteza(0);
						sens = MOTOARE_SENS_INAITE;
					}
					SetareSens(sens);
				}
				else
				{
					if(sens == MOTOARE_SENS_INAITE)
					{
						SetareViteza(0);
						sens = MOTOARE_SENS_SPATE;
					}
					SetareSens(sens);
				}
				SetareUnghi(0);
				SetareViteza(viteza);
				if(linie>63+LINE_MAX_ERROR_MID || linie<64-LINE_MAX_ERROR_MID)
				{
					stare = STATE_DRUM_CURBA;
					viteza = 0;
					SetareViteza(viteza);	
				}
				break;
			
			default:
				break;
		}*/
		
	}
}

 
