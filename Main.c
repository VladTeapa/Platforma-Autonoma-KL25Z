#include "MKL25Z4.h"
#include "Motoare.h"
#include "PortsSetup.h"
#include "Camera.h"
#include "SistemDecizional.h"
#include "Uart.h"
#include "math.h"

extern double viteza;
extern double vitezaCurenta;
extern double motoareInputCurent;
extern uint8_t linie;

double directie;
int main (void) {

	SIMSetup();
	InitializarePiniParteMecanica();
	initializareCamera();

	initializarePIT();
	startCamera();
	UartInit(9600);
	viteza = 1;
	double x = 0;
	while(1){
		directie = decideDirectia(linie);
		SetareUnghi(directie);
		/*SetareUnghi(sin(x));
		x+=0.0001;*/
	}
}

 
