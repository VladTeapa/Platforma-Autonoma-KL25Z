#include "PID.h"


struct PID initializarePID(double TS, double KP, double KI, double KD)
{
	struct PID pid;
	pid.a1 = KP + KI*(TS)/2 + KD/TS;
	pid.a2 = -KP + KI*TS/2 - 2*KD/TS;
	pid.a3 = KD/TS;
	pid.errorK[0]=pid.errorK[1]=pid.errorK[2]=0;
	return pid;
}

double getNextPid(struct PID pid, double referinta, double output, double semnalComanda)
{
	double res;
	pid.errorK[2] = pid.errorK[1];
	pid.errorK[1] = pid.errorK[0];
	pid.errorK[0] = referinta - output;
	res = semnalComanda + pid.a1*pid.errorK[0] + pid.a2*pid.errorK[1] + pid.a3*pid.errorK[2];
	return res;
}