#include "Motoare.h"
#include "Uart.h"
#include "PID.h"

struct PID pid;

float volatile vitezaCurenta = 0;

float volatile viteza=0;

float volatile semnal=0;

uint16_t volatile nrInput = 0;

void TPM2_IRQHandler(void)
{
	const float nrInputCoeff = (PI * DIAMETER_OF_WHEEL / COEFFICIENT_MEASURE_TIME) / NUMBER_OF_MAGNETS;
	NVIC_ClearPendingIRQ(TPM2_IRQn);
	if(TPM2->CONTROLS[1].CnSC & TPM_CnSC_CHF_MASK)
	{
			nrInput++;
			TPM2->CONTROLS[1].CnSC |= TPM_CnSC_CHF_MASK;
	}
	if((TPM2_SC & TPM_SC_TOF_MASK))
	{
			vitezaCurenta = nrInput*nrInputCoeff;
			trimiteDate(vitezaCurenta*10);
			TPM2_SC |= TPM_SC_TOF_MASK;
			if(ACTIVARE_PID_DEBUG == 0)
			{
				nrInput = 0;
			} 
			else 
			{
				if(viteza == 0 && vitezaCurenta == 0)
					semnal = 0;
				else
					semnal = getNextPid(&pid, viteza, vitezaCurenta, semnal);
				if(semnal > 1)
					semnal = 1;
				if(semnal < -1)
					semnal = -1;
				if(semnal < 0)
				{
						SetareSens(MOTOARE_SENS_SPATE);
						SetareViteza(-semnal);
				}
				else
				{
						SetareSens(MOTOARE_SENS_INAITE);
						SetareViteza(semnal);
				}
				nrInput = 0;
				trimiteDate((semnal+1)*100);
			}
	}
}

void InitializarePiniParteMecanica(void){

	//Setare multiplexor pentru porturi
	PortMotorDreapta |= PORT_PCR_MUX(PortMotorDreaptaMux);
	PortMotorStanga |= PORT_PCR_MUX(PortMotorStangaMux);
	
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
	TPM0->SC |= TPM_SC_PS(TPMDIVIDERMOTOARE);
	TPM1->SC |= TPM_SC_PS(TPMDIVIDERSERVO);
	
	//Setare mod de numarare
	TPM0->SC &= ~TPM_SC_CPWMS_MASK;
	TPM1->SC &= ~TPM_SC_CPWMS_MASK;
	
	//Setare modulo
	TPM0->CNT = 0;
	TPM0->MOD = MotorMaxCount;
	TPM1->CNT = 0;
	TPM1->MOD = ServoMaxCount;
	
	
	//Setare mod Edge-Aligned PMW
	TPM1->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;
	TPM0->CONTROLS[2].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;
	TPM0->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;
	
	
	//Setare mod trigger
	TPM0->CONF |= TPM_CONF_TRGSEL(0x8);
	TPM1->CONF |= TPM_CONF_TRGSEL(0x9);
	
	//Setare factor de umplere
	TPM1->CONTROLS[0].CnV = ServoMaxCount*0.075f;
	TPM0->CONTROLS[2].CnV = 0;
	TPM0->CONTROLS[1].CnV = 0;
	
	//Activare TPM
	TPM0->SC |= TPM_SC_CMOD(1);
	TPM1->SC |= TPM_SC_CMOD(1);
}

void initializareSenzorTuratie(void)
{
	PortSenzorTuratie |= PORT_PCR_MUX(PortSenzorTuratieMux);
	PortSenzorTuratie |= PORT_PCR_PE(1) & (~PORT_PCR_PS(1));
	
	//Setare divizor frecventa
	TPM2->SC |= TPM_SC_PS(TPMDIVIDERTURATIE);
	
	//Setare mod de numarare
	TPM2->SC &= ~TPM_SC_CPWMS_MASK;
	
	TPM2->SC |= TPM_SC_TOIE_MASK;
	
	//Setare modulo
	TPM2->CNT = 0;
	TPM2->MOD = SenzorTuratieMOD;
	
	//Setare trigger
	TPM2->CONF |= TPM_CONF_TRGSEL(0xA);
	
	//Setare mod input capture
	TPM2->CONTROLS[1].CnSC = TPM_CnSC_ELSB_MASK | TPM_CnSC_CHIE_MASK;

	
	//Activare intrerupere
	NVIC_SetPriority(TPM2_IRQn, 128);
	NVIC_ClearPendingIRQ(TPM2_IRQn); 
	NVIC_EnableIRQ(TPM2_IRQn);	
	
	TPM2->SC |= TPM_SC_CMOD(1);
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
	if(vitezaMotor > MOTOARE_VITEZA_MAXIMA_SIG)
		vitezaMotor = MOTOARE_VITEZA_MAXIMA_SIG;
	
	TPM0->CONTROLS[2].CnV = MotorMaxCount*vitezaMotor;
	
	TPM0->CONTROLS[1].CnV = MotorMaxCount*vitezaMotor;
	
}


void SetareUnghi(long double unghi)
{
	if(unghi == 0)
	{
		unghi = SERVOMOTOR_STRAIGHT_ERR;
		return;
	}
	if(unghi<-0.4) // Se verifica daca valoarea unghilui este setata corect
	{
		unghi = -0.4;
	}
	if (unghi > 0.4)
	{
		unghi = 0.4;
	}
	unghi++;	// Se aduce valoarea la intervalul 0-2
	unghi /= 2;	// Se aduce valoarea la intervalul 0-1
	unghi = (ServoMaxVal-ServoMinVal)*unghi;
	unghi = unghi + ServoMinVal;
	TPM1->CONTROLS[0].CnV = unghi;
}