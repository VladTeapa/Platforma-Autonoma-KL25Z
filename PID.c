#include "PID.h"


struct PID initializarePID(double TS, double KP, double KI, double KD)
{
	struct PID pid;
	pid.a1 = KP + KI*(TS)/2 + KD/TS;
	pid.a2 = -KP + KI*TS/2 - 2*KD/TS;
	pid.a3 = KD/TS;
	pid.errorK1=pid.errorK2=pid.errorK3=0;
	return pid;
}

inline float getNextPid(struct PID* pid, float referinta, float output, float semnalComanda)
{
	pid->errorK3 = pid->errorK2;
	pid->errorK2 = pid->errorK1;
	pid->errorK1 = referinta - output;
	return semnalComanda + pid->a1*pid->errorK1 + pid->a2*pid->errorK2 + pid->a3*pid->errorK3;
}
