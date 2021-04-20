#include "MKL25Z4.h"
#include "Defines.h"
void initializarePIT(void); //Initializare modul pit
void initializareCamera(void); //Initializare pini camera
void startCamera(void); //Pornire camera
void ADC0_IRQHandler(void); //Intrerupere ADC
void PIT_IRQHandler(void); //Intrerupere pit pentru camera
static void debugLineScanCamera(void); //Copiere din vector temporar in vectorul care va fi folosit pentru decizie
static int calibrareADC(void); //Initializare modul ADC
