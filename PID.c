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

double getNextPid(struct PID pid, double referinta, double output, long double semnalComanda)
{
	long double res;
	pid.errorK[2] = pid.errorK[1];
	pid.errorK[1] = pid.errorK[0];
	pid.errorK[0] = referinta - output;
	res = semnalComanda + pid.a1*pid.errorK[0] + pid.a2*pid.errorK[1] + pid.a3*pid.errorK[2];
	return res;
}

/*switch (stare)
		{
			case STATE_START:
				stare = STATE_DRUM_DREPT;
				break;
			case STATE_DRUM_CURBA:
				vitezaMS = decideVitezaDrumSimplu(linie);
				viteza = getNextPid(pid, vitezaMS, vitezaCurenta, viteza);
				directie = decideDirectiaDrumSimplu(linie);
				SetareUnghi(directie);
				if(viteza > 0)
				{
					if(sens == MOTOARE_SENS_SPATE)
					{
						SetareViteza(0);
						sens = MOTOARE_SENS_INAITE;
					}
					SetareSens(sens);
				}
				else
				{
					if(sens == MOTOARE_SENS_INAITE)
					{
						SetareViteza(0);
						sens = MOTOARE_SENS_SPATE;
					}
					SetareSens(sens);
				}
				SetareViteza(viteza);
				if(linie <= 63+LINE_MAX_ERROR_MID || linie>=64-LINE_MAX_ERROR_MID)
				{
					stare = STATE_DRUM_CURBATODREPT;
				}
				break;
			case STATE_DRUM_CURBATODREPT:
				viteza = 0;
				sens = MOTOARE_SENS_INAITE;
				SetareSens(sens);
				SetareViteza(viteza);
				stare = STATE_DRUM_DREPT;
				break;
			
			
			case STATE_DRUM_DREPT:
				viteza = getNextPid(pid, MOTOARE_VITEZA_MAX_MS, vitezaCurenta,viteza);
				if(viteza > 0)
				{
					if(sens == MOTOARE_SENS_SPATE)
					{
						SetareViteza(0);
						sens = MOTOARE_SENS_INAITE;
					}
					SetareSens(sens);
				}
				else
				{
					if(sens == MOTOARE_SENS_INAITE)
					{
						SetareViteza(0);
						sens = MOTOARE_SENS_SPATE;
					}
					SetareSens(sens);
				}
				SetareUnghi(0);
				SetareViteza(viteza);
				if(linie>63+LINE_MAX_ERROR_MID || linie<64-LINE_MAX_ERROR_MID)
				{
					stare = STATE_DRUM_CURBA;
					viteza = 0;
					SetareViteza(viteza);	
				}
				break;
			
			default:
				break;
		}*/