#include "MKL25Z4.h"
#include "Defines.h"
#include "Motoare.h"

void decidePas(void); // Functie care va lua decizia urmatoare
double decideDirectia(uint8_t linie); // Functie care ia decizia pentru servomotor
void decideViteza(void); // Functie care ia decizia pentru motoare