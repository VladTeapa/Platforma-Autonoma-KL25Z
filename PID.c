#include "PID.h"
#include "Uart.h"

static float kp = 0;
static float kd = 0;
static float ki = 0;
static float a1 = 0;
static float a2 = 0;
static float a3 = 0;
static float eroare = 0;
static float eroare1 = 0;
static float eroare2 = 0;
static float integral = 0;
static float semnalComandaVechi = 0;

void initializarePID(float TS, float KP, float KI, float KD)
{
	//Se initializeaza coeficientii a1,a2,a3
	a1 = KP + KI*(TS)/2 + KD/TS;
	a2 = -KP + KI*TS/2 - 2*KD/TS;
	a3 = KD/TS;
	eroare = eroare2 = eroare1 = 0;
	semnalComandaVechi = 0;
}

float getNextPid(float referinta, float output, float semnalComanda)
{
	float res;
	//Se calculeaza valoarea urmatoare a semnalului
	eroare2 = eroare1;
	eroare1 = eroare;
	eroare = referinta - output;
	res = semnalComandaVechi + a1*eroare + a2*eroare1 + a3*eroare2;
	semnalComandaVechi = semnalComanda;
	return res;
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

inline float getNextPidv2(float referinta, float output)
{
	//Se calculeaza valoarea noua a semnalului
	float up, ud, e;
	e = referinta - output;
	up = e * kp;
	integral += ki * eroare;
	ud = kd * (e - eroare);
	eroare = e;
	return up + ud + integral;
}