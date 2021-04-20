#include "SenzoriDistanta.h"
#include "Uart.h"

long double volatile distantaS = 100;
long double volatile distantaD = 100;
long double volatile distantaC = 100;

void PORTA_IRQHandler(void)
{
	NVIC_ClearPendingIRQ(PORTA_IRQn); 
	uint32_t value = TPM0->CNT;
	if(PORTA_ISFR & 1<<PortSenzorDistantaCPin)
	{
		
		//Se calculeaza distanta fata de senzor
		distantaC = FACTORMULDISTANTA * value;
		PORTA_ISFR |= 1<<PortSenzorDistantaCPin;
		distantaC -= DISTANTAEROARE;
	}
	if(SENZOR_DISTANTA_DEBUG_C == 1)
		trimiteDate(distantaC);
}

void PORTD_IRQHandler(void)
{
	NVIC_ClearPendingIRQ(PORTD_IRQn); 
	uint32_t value = TPM0->CNT;
	if(PORTD_ISFR & 1<<PortSenzorDistantaSPin)
	{
		
		//Se calculeaza distanta fata de senzor
		distantaS = FACTORMULDISTANTA * value;
		PORTD_ISFR |= 1<<PortSenzorDistantaSPin;
		distantaS -= DISTANTAEROARE;
		if(SENZOR_DISTANTA_DEBUG_S == 1)
			trimiteDate(distantaS);
	}
	if(PORTD_ISFR & 1<<PortSenzorDistantaDPin)
	{
		
		//Se calculeaza distanta fata de senzor
		distantaD = FACTORMULDISTANTA * value;
		PORTD_ISFR |= 1<<PortSenzorDistantaDPin;
		distantaD -= DISTANTAEROARE;
		if(SENZOR_DISTANTA_DEBUG_D == 1)
			trimiteDate(distantaD);
	}
}

void initializareSenzoriDistanta(void)
{
	//Configurare pin trigger
	PortSenzorDistantaTrig |= PORT_PCR_MUX(PortSenzorDistantaTrigMux);
	PortSenzorDistantaTrig |=  PORT_PCR_PE(1) & (~PORT_PCR_PS(1));
	
	//Configuram pinii pentru echo
	PortSenzorDistantaEchoS |= PORT_PCR_MUX(PortSenzorDistantaEchoSM);
	PortSenzorDistantaEchoD |= PORT_PCR_MUX(PortSenzorDistantaEchoDM);
	PortSenzorDistantaEchoC |= PORT_PCR_MUX(PortSenzorDistantaEchoCM);
	
	PortSenzorDistantaEchoS |=  PORT_PCR_PE(1) & (~PORT_PCR_PS(1));
	PortSenzorDistantaEchoD |=  PORT_PCR_PE(1) & (~PORT_PCR_PS(1));
	PortSenzorDistantaEchoC |=  PORT_PCR_PE(1) & (~PORT_PCR_PS(1));
	
	PortSenzorDistantaEchoS |= PORT_PCR_IRQC(0xA);
	PortSenzorDistantaEchoD |= PORT_PCR_IRQC(0xA);
	PortSenzorDistantaEchoC |= PORT_PCR_IRQC(0xA);
	
	//Dezactivare modul pe timpul configurarii
	TPM0->SC &= ~(TPM_SC_CMOD(1));
	
	//Setare mod Edge-Aligned PWM
	TPM0->CONTROLS[4].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;

	//Setare factor de umplere
	TPM0->CONTROLS[4].CnV = SENZORDISTANTAPWM;
	
	//Activare modul TPM0
	TPM0->SC |= TPM_SC_CMOD(1);
	
	NVIC_SetPriority(PORTA_IRQn, 128);
	NVIC_ClearPendingIRQ(PORTA_IRQn); 
	NVIC_EnableIRQ(PORTA_IRQn);	

	NVIC_SetPriority(PORTD_IRQn, 128);
	NVIC_ClearPendingIRQ(PORTD_IRQn); 
	NVIC_EnableIRQ(PORTD_IRQn);
}