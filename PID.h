#include "Defines.h"

typedef struct PID{
	double a1;
	double a2;
	double a3;
	double errorK1;
	double errorK2;
	double errorK3;
}PID;

struct PID initializarePID(double TS, double KP, double KI, double KD);

float getNextPid(struct PID* pid, float referinta, float output, float semnalComanda);