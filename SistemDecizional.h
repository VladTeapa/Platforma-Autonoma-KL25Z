#include "MKL25Z4.h"
#include "Defines.h"
#include "Motoare.h"

void decidePas(void); // Functie care va lua decizia urmatoare
double decideDirectiaDrumSimplu(uint8_t linie); // Functie care ia decizia pentru servomotor
double decideVitezaDrumSimplu(uint8_t linie); // Functie care ia decizia pentru motoare