#include "MKL25Z4.h"
#include "Defines.h"
#include "Motoare.h"
long double decideDirectiaDrumSimplu(uint8_t linie); //Functie care returneaza o valoare a unghiului in functie de linie
float decideVitezaDrumSimplu(uint8_t linie);
float decideVitezaObstacolFata(float distantaC);
uint8_t decideStareDrumObstacolFata(uint8_t stare, float distantaC, float distantaD, float distantaS);