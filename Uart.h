#include "Defines.h"
#include "MKL25Z4.h"
void trimiteDate(uint8_t data); //Trimite un singur caracter pe interfata UART
uint8_t primesteDate(void); //Asteapta un singur caracter pana primeste
void uartInit(uint32_t baud); //Initializare modul UART