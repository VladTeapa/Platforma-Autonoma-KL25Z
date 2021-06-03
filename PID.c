#include "PID.h"
#include "Uart.h"

static float kp = 0;
static float kd = 0;
static float ki = 0;
static float eroare = 0;
static float integral = 0;

PID initializarePID(double TS, double KP, double KI, double KD)
{
	//Se initializeaza coeficientii a1,a2,a3
	PID pid;
	pid.a1 = KP + KI*(TS)/2 + KD/TS;
	pid.a2 = -KP + KI*TS/2 - 2*KD/TS;
	pid.a3 = KD/TS;
	pid.errorK1 = pid.errorK2 = pid.errorK3 = 0;
	return pid;
}

inline float getNextPid(PID* pid, float referinta, float output, float semnalComanda)
{
	//Se calculeaza valoarea urmatoare a semnalului
	pid->errorK3 = pid->errorK2;
	pid->errorK2 = pid->errorK1;
	pid->errorK1 = referinta - output;
	return semnalComanda + pid->a1*pid->errorK1 + pid->a2*pid->errorK2 + pid->a3*pid->errorK3;
}

void initializarePIDv2(float TS, float KP, float KI, float KD)
{
	//Se initializeaza pidul
	kp = KP;
	ki = KI*TS;
	kd = KD/TS;
	integral = 0;
	eroare = 0;
}

float getNextPidv2(float referinta, float output)
{
	//Se calculeaza valoarea noua a semnalului
	float up, ud, e;
	e = referinta - output;
	up = e * kp;
	integral += ki * (e + eroare) / 2;
	ud = kd * (e - eroare);
	eroare = e;
	return up + ud + integral;
}