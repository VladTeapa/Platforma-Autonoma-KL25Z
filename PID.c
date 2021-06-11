#include "PID.h"
#include "Uart.h"

static float kp = 0;
static float kd = 0;
static float ki = 0;
static float eroare = 0;
static float integral = 0;

void initializarePID(float TS, float KP, float KI, float KD)
{
	//Se initializeaza pidul
	kp = KP;
	ki = KI*TS;
	kd = KD/TS;
	integral = 0;
	eroare = 0;
}

float getNextPid(float referinta, float output)
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