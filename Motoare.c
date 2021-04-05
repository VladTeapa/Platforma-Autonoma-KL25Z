#include "Motoare.h"
#include "Uart.h"
#include "PID.h"

struct PID pid;

long double vitezaCurenta = 0;

long double volatile viteza=0;

long double semnal=0;

int8_t volatile sens=MOTOARE_SENS_INAITE;

uint32_t nrInput = 0;

void TPM0_IRQHandler(void)
{
	if(TPM0->CONTROLS[0].CnSC & TPM_CnSC_CHF_MASK)
	{
			nrInput++;
			TPM0->CONTROLS[0].CnSC |= TPM_CnSC_CHF_MASK;
	}
	if((TPM0_SC & TPM_SC_TOF_MASK))
	{
			vitezaCurenta = (1.0L * nrInput/NUMBER_OF_MAGNETS) * PI * DIAMETER_OF_WHEEL / COEFFICIENT_MEASURE_TIME;
			if(VITEZA_DEBUG_VITEZA_CUR == 1)
				trimiteDate(vitezaCurenta);
			nrInput = 0;
			TPM0_SC |= TPM_SC_TOF_MASK;
			semnal = getNextPid(pid, viteza, vitezaCurenta, semnal);
			if(semnal < 0)
			{
				if(sens == MOTOARE_SENS_INAITE)
				{
					SetareViteza(0);
					SetareSens(MOTOARE_SENS_SPATE);
					sens = MOTOARE_SENS_SPATE;
				}
				SetareViteza(semnal);
			}
			else
			{
				if(sens == MOTOARE_SENS_SPATE)
				{
					SetareViteza(0);
					SetareSens(MOTOARE_SENS_INAITE);
					sens = MOTOARE_SENS_INAITE;
				}
				SetareViteza(semnal);
			}
	}
}

void InitializarePiniParteMecanica(void){

	//Setare multiplexor pentru porturi
	PortMotorDreapta |= PORT_PCR_MUX(PortMotorDreaptaMux);
	PortMotorStanga |= PORT_PCR_MUX(PortMotorStangaMux);
	
	PortSenzorTuratie |= PORT_PCR_MUX(PortSenzorTuratieMux);
	
	PortMotorActivareDreapta |= PORT_PCR_MUX(PortMotorActivareDreaptaM);
	PortMotorActivareStanga |= PORT_PCR_MUX(PortMotorActivareStangaM);
	
	PortSensMotor |= PORT_PCR_MUX(PortSensMotorMux);
	
	PortServoMotor |= PORT_PCR_MUX(PortServoMux);
	
	//Configurare pini GPIO
	PortMotorActivareDreapta |= PORT_PCR_PE(1) & (~PORT_PCR_PS(1));
	PortMotorActivareStanga |= PORT_PCR_PE(1) & (~PORT_PCR_PS(1));
	PortSensMotor |= PORT_PCR_PE(1) & (~PORT_PCR_PS(1));
	
	GPIODirMotorDreapta |= 1<<GPIOPinMotorDreapta;
	GPIODirMotorStanga |= 1<<GPIOPinMotorStanga;
	GPIODirSensMotor |= 1<<GPIOPinSensMotor;
	
	GPIOSMotorDreapta |= 1<<GPIOPinMotorDreapta;
	GPIOSMotorStanga |= 1<<GPIOPinMotorStanga;
	GPIOCSensMotor |= 1<<GPIOPinSensMotor;
	
	//Setare divizor frecventa
	TPM0->SC |= TPM_SC_PS(TPMDivider);
	
	//Setare mod de numarare
	TPM0->SC &= ~TPM_SC_CPWMS_MASK;
	
	//Setare modulo
	TPM0->CNT = 0;
	TPM0->MOD = MotorMaxCount;
	
	//Setare intrerupere
	TPM0->SC |= TPM_SC_TOIE_MASK;
	
	//Setare mod Edge-Aligned PMW
	TPM0->CONTROLS[4].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;
	
	TPM0->CONTROLS[2].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;
	
	TPM0->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;
	
	//Setare mod input capture
	TPM0->CONTROLS[0].CnSC = TPM_CnSC_ELSA_MASK | TPM_CnSC_CHIE_MASK;
	
	//Activare intrerupere
	NVIC_SetPriority(TPM0_IRQn, 128);
	NVIC_ClearPendingIRQ(TPM0_IRQn); 
	NVIC_EnableIRQ(TPM0_IRQn);	
	
	//Setare mod trigger
	TPM0->CONF |= TPM_CONF_TRGSEL(0x8);
	
	//Setare factor de umplere
	
	TPM0->CONTROLS[4].CnV = ServoMaxCount*0.075f;
	
	TPM0->CONTROLS[2].CnV = 0;
	
	TPM0->CONTROLS[1].CnV = 0;
	
	//Activare TPM
	TPM0->SC |= TPM_SC_CMOD(1);
}

void SetareSens(int sens)
{
	if(sens == MOTOARE_SENS_INAITE) // Setare sens inainte
	{
		GPIOCSensMotor |= 1<<GPIOPinSensMotor;
	}
	else if(sens == MOTOARE_SENS_SPATE) // Setare sens inapoi
	{
		GPIOSSensMotor |= 1<<GPIOPinSensMotor;
	} //Daca nu este niciuna dintre ele nu se modifica sensul
}

void SetareViteza(double vitezaMotor)
{
	if(vitezaMotor < 0)
		vitezaMotor = 0;
	if(vitezaMotor > 1)
		vitezaMotor = 1;
	
	TPM0->CONTROLS[2].CnV = MotorMaxCount*vitezaMotor;
	
	TPM0->CONTROLS[1].CnV = MotorMaxCount*vitezaMotor;
	
}

void SetareUnghi(double unghi)
{
	if(unghi<-0.9 || unghi>0.9) // Se verifica daca valoarea unghilui este setata corect
		return;
	unghi++;	// Se aduce valoarea la intervalul 0-2
	unghi /= 2;	// Se aduce valoarea la intervalul 0-1
	unghi*=0.8;
	unghi+=0.1;
	TPM0->CONTROLS[4].CnV = (ServoMaxVal-ServoMinVal)*unghi + ServoMinVal;
}