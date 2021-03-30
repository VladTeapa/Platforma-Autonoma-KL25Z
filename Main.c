#include "MKL25Z4.h"
#include "Motoare.h"
#include "PortsSetup.h"
#include "Camera.h"
#include "SistemDecizional.h"
#include "Uart.h"

extern double viteza;
extern double vitezaCurenta;
extern double motoareInputCurent;
int main (void) {

	SIMSetup();
	InitializarePiniParteMecanica();
	initializareCamera();

	initializarePIT();
	startCamera();
	UartInit(115200);
	viteza = 1;
	while(1){
	
	}
}

 
