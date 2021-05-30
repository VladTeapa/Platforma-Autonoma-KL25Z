#include "Defines.h"
typedef struct PID{ //Structura care va contine coeficientii pentru PID
	double a1;
	double a2;
	double a3;
	double errorK1;
	double errorK2;
	double errorK3;
}PID;

typedef struct PIDv2{
	double KP;
	double KI;
	double KD;
	double ui;
	double eroare;
}PIDv2;


PID initializarePID(double TS, double KP, double KI, double KD); //Functie care initializeaza o instanta de tip PID
float getNextPid(PID* pid, float referinta, float output, float semnalComanda); //Functie care calculeaza urmatorul semnal

void initializarePIDv2(float TS, float KP, float KI, float KD); //Functie care initializeaza o instanta de tip PIDv2
float getNextPidv2(float referinta, float output); //Functie care calculeaza urmatorul semnal cu ajutorul la PIDv2