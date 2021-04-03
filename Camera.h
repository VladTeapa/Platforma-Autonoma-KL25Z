#pragma once

#include "MKL25Z4.h"
#include "Defines.h"

void initializarePIT(void); // Initializare modul pit
void initializareCamera(void); // Initializare pini camera

int calibrareADC(void); // Initializare modul ADC
void startCamera(void); // Pornire camera

void ADC0_IRQHandler(void); // Intrerupere ADC
void PIT_IRQHandler(void); // Intrerupere pit pentru camera

void prelucrareImagine(void); // Copiere din vector temporar in vectorul care va fi folosit pentru decizie
void trimiteLinie(uint8_t c);

uint8_t cautaLinie(void);