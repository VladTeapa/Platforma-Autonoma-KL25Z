#include "Defines.h"
void initializarePID(float TS, float KP, float KI, float KD); //Functie care initializeaza o instanta de tip PID
float getNextPid(float referinta, float output); //Functie care calculeaza urmatorul semnal cu ajutorul la PID