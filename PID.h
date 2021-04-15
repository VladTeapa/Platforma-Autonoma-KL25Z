#include "Defines.h"

typedef struct PID{
	double a1;
	double a2;
	double a3;
	double errorK[3];
}PID;

struct PID initializarePID(double TS, double KP, double KI, double KD);

double getNextPid(struct PID pid, double referinta, double output, long double semnalComanda);