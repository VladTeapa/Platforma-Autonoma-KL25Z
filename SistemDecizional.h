#include "MKL25Z4.h"
#include "Defines.h"
#include "Motoare.h"

long double decideDirectiaDrumSimplu(uint8_t linie); // Functie care ia decizia pentru servomotor
double decideVitezaDrumSimplu(uint8_t linie); // Functie care ia decizia pentru motoare