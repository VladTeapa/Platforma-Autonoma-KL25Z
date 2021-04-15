#include "Uart.h"

uint32_t osr = 15;
uint16_t sbr;
uint8_t temp;

extern uint8_t cameraPixels[128];

void UartInit(uint32_t baud){	
	// Activam ceasul pentru modulul UART0
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK; 			
	
	// Dezactivam RX, TX pentru configurare
	UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK; 	

	// Setam ceasul
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(01);
	SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;
	
	// Setam pinii folositi
	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);
	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);
	
	
	sbr = (uint16_t)((BUS_CLOCK)/(baud * osr+1));
	temp = UART0->BDH & ~(UART0_BDH_SBR(0x1F));
	UART0->BDH = temp | UART_BDH_SBR(((sbr & 0x1F00) >> 8));
	UART0->BDL = (uint8_t)(sbr & UART_BDL_SBR_MASK);
	UART0->C4 |= UART0_C4_OSR(osr);												
	
	// Mentinem majoritatea pe default
	UART0->C1 = 0;
	
	UART0->C3 = 0;
	UART0->MA1 = 0;
	UART0->MA2 = 0;
	UART0->S1 |= 0x00;
	UART0->S2 = 0x00;
	
	//Activam UART0
	UART0->C2 |= UART0_C2_TE_MASK | UART0_C2_RE_MASK;			
}

void trimiteDate(uint8_t data)
{
	while(!(UART0->S1 & UART_S1_TDRE_MASK));
	UART0->D = data;
}

uint8_t primesteDate(void)
{
	while(!(UART0->S1 & UART_S1_RDRF_MASK));
	return UART0->D;
}

