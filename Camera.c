#include "Camera.h"
#include "Uart.h"
#include "SistemDecizional.h"
#include "Motoare.h"

static int cameraState=0;
static int clockCycles=0;

static volatile uint8_t tempPixels[128];
static volatile uint8_t max;
static volatile uint8_t min;


uint8_t cameraPixels[128];
uint8_t linie=63;
uint8_t linieStatus = 1;
uint8_t primaImagine = CAMERA_FIRST_IMAGE_TRUE;

static uint8_t cautaLinieLocal(uint8_t punct)
{
	uint8_t i=punct;
	uint8_t l,r;
	l=r=i;
	while(l>CAMERA_IGNORE_EDGE_VAL)
	{
		if(cameraPixels[l] == PIXELI_CUT_HIGH_VAL)
			break;
		l--;
	}
	while(r<128-CAMERA_IGNORE_EDGE_VAL)
	{
		if(cameraPixels[r] == PIXELI_CUT_HIGH_VAL)
			break;
		r++;
	}
	return (r+l)/2;
}

uint8_t cautaLinie(void)
{
	uint8_t linieTemp = linie;
	uint8_t i,left,right;
	uint8_t flag = 0;
	for(i=0;i<127;i++)
	{
		flag = 0;
		left = linieTemp - i;
		right = linieTemp + i;
		if(left>CAMERA_IGNORE_EDGE_VAL)
		{
			if(cameraPixels[left] == PIXELI_CUT_LOW_VAL)
			{
				return cautaLinieLocal(left);
			}
		}
		else
			flag++;
		if(right<128-CAMERA_IGNORE_EDGE_VAL)
		{
			if(cameraPixels[right] == PIXELI_CUT_LOW_VAL)
			{
				return cautaLinieLocal(right);
			}
		}
		else
			flag++;
		if(flag == 2)
			return linie;
		
	}
	return linie;
}

void prelucrareImagine(void)
{
	/*if(primaImagine == CAMERA_FIRST_IMAGE_TRUE)
	{
		primaImagine = CAMERA_FIRST_IMAGE_FALSE;
		return;
	}*/
	uint8_t tempMax=(max-min)/COEFFICIENT_PIXELI_CUT + min;
	register uint8_t i=0;
	for(i=0;i<128;i++)
	{
		if(tempPixels[i]>tempMax)
			cameraPixels[i]=PIXELI_CUT_HIGH_VAL;
		else
			cameraPixels[i]=PIXELI_CUT_LOW_VAL;
	}
	if(CAMERA_DEBUG_LINE_SCAN == 1)
	{
		cameraPixels[0] = CAMERA_EDGE_VAL;
		cameraPixels[127] = CAMERA_EDGE_VAL;
		cameraPixels[CAMERA_IGNORE_EDGE_VAL] = CAMERA_EDGE_VAL-0x10;
		cameraPixels[127-CAMERA_IGNORE_EDGE_VAL] = CAMERA_EDGE_VAL-0x10;
	
		for(i=0;i<128;i++)
			trimiteDate(cameraPixels[i]);
	}
	linie = cautaLinie();
	if(CAMERA_DEBUG_LINE == 1)
	{
		trimiteDate(linie);
	}
}

void ADC0_IRQHandler(void)
{
	uint8_t value;
	ADCCameraSC1A &= ~ADC_SC1_AIEN_MASK;
	value =(uint8_t)ADCCameraResult;
	if(clockCycles < NumberOfClocks)
	{	
		tempPixels[clockCycles/2] = (uint8_t)value;
		if((uint8_t)value>max && clockCycles/2>CAMERA_IGNORE_EDGE_VAL && clockCycles/2<127-CAMERA_IGNORE_EDGE_VAL)
			max = (uint8_t)value;
		if((uint8_t)value<min && clockCycles/2>CAMERA_IGNORE_EDGE_VAL && clockCycles/2<127-CAMERA_IGNORE_EDGE_VAL)
			min = (uint8_t)value;
	}
}

void PIT_IRQHandler(void)
{
	NVIC_ClearPendingIRQ(PIT_IRQn);
	if(PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK)
	{
		PIT_TCTRL0 = 0;
		PIT_TCTRL1 = 0;
		switch(cameraState)
		{
			case CAMERA_START:
				GPIOCCLKCamera = 1<<GPIOPinCLKCamera;
				prelucrareImagine();
				GPIOSSICamera = 1<<GPIOPinSICamera;
				clockCycles = 1;
				cameraState = CAMERA_SET_CLK;
				PIT->CHANNEL[0].LDVAL = PITQuarterClock;
				max = 0;
				min = 0xFF;
				break;
			case CAMERA_SET_CLK:
				GPIOSCLKCamera |= 1<<GPIOPinCLKCamera;
				cameraState = CAMERA_CLEAR_SI;
				break;
			case CAMERA_CLEAR_SI:
				GPIOCSICamera |= 1<<GPIOPinSICamera;
				cameraState = CAMERA_FINAL;
				break;
			case CAMERA_FINAL:
				GPIOCCLKCamera |= 1<<GPIOPinCLKCamera;
				PIT->CHANNEL[0].LDVAL = PITSIClock;
				ADCCameraSC1A = ADC_SC1_ADCH(8) | ADC_SC1_AIEN_MASK;
				PIT->CHANNEL[1].TCTRL = PIT_TCTRL_TEN_MASK | PIT_TCTRL_TIE_MASK;
				cameraState = CAMERA_START;
				break;
		}
		PIT->CHANNEL[0].TFLG &= PIT_TFLG_TIF_MASK;
		PIT->CHANNEL[1].TFLG &= PIT_TFLG_TIF_MASK;
		PIT->CHANNEL[0].TCTRL = PIT_TCTRL_TEN_MASK | PIT_TCTRL_TIE_MASK;
	}
	else if(PIT->CHANNEL[1].TFLG & PIT_TFLG_TIF_MASK)
	{
		if(clockCycles%2 == 0)
			ADCCameraSC1A = ADC_SC1_ADCH(8) | ADC_SC1_AIEN_MASK;	
		PIT->CHANNEL[1].TFLG &= PIT_TFLG_TIF_MASK;
		GPIOTCLKCamera |= 1<<GPIOPinCLKCamera;
		clockCycles++;
	}
}
void startCamera(void)
{
	
	PIT_MCR &= ~(PIT_MCR_MDIS_MASK);				
	PIT_LDVAL0 = PITQuarterClock;		// set pit0 to quarter of a CLK period initially
	PIT_LDVAL1 = PITHalfClock;		// set pit1 to half CLK period   
	PIT_TCTRL0 = PIT_TCTRL_TEN_MASK | PIT_TCTRL_TIE_MASK; //enable pit0
	PIT_MCR = 1;		
	cameraState = CAMERA_START;
}

void initializarePIT(void) 
{
	
	//Se activeaza modulul
	PIT->MCR &= ~PIT_MCR_MDIS_MASK;
	
	//Se configureaza canalul 0
	PIT->CHANNEL[0].LDVAL = PIT_LDVAL_TSV(PITHalfClock);

	PIT->CHANNEL[0].TCTRL &= PIT_TCTRL_CHN_MASK;
	
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;

	//Se seteaza intreruperile
	NVIC_SetPriority(PIT_IRQn, 128);
	NVIC_ClearPendingIRQ(PIT_IRQn); 
	NVIC_EnableIRQ(PIT_IRQn);	
}

void initializareCamera(void)
{
	
	//Configurare pini CLK si SI
	PortSICamera |= PORT_PCR_MUX(PortSICameraMux);
	PortCLKCamera |= PORT_PCR_MUX(PortCLKCameraMux);
	
	PortSICamera |=  PORT_PCR_PE(1) & (~PORT_PCR_PS(1));
	PortCLKCamera |=  PORT_PCR_PE(1) & (~PORT_PCR_PS(1));
	
	//Configurare pini GPIO
	GPIODirSICamera |= 1<<GPIOPinSICamera;
	GPIODirCLKCamera |= 1<<GPIOPinCLKCamera;

	GPIOSCLKCamera |= 1<<GPIOPinCLKCamera;
	GPIOCSICamera |= 1<<GPIOPinSICamera;
	
	//Configurare pin pentru AO
	PortAOCamera |= PORT_PCR_MUX(PortAOCameraMux);
	
	if(calibrareADC()==-1)
		return;
	
	ADCCameraCFG1 = 0;
	ADCCameraCFG2 = 0;
	ADCCameraSC1A = 0x1F;
	ADCCameraSC2 = 0;
	ADCCameraSC3 &= 0xF;

	NVIC_SetPriority(ADC0_IRQn, 128);
	NVIC_ClearPendingIRQ(ADC0_IRQn); 
	NVIC_EnableIRQ(ADC0_IRQn);	
}

int calibrareADC(void)
{
	unsigned short calVar;
	ADCCameraSC2 &= ~ADC_SC2_ADTRG_MASK;
	ADCCameraSC3 &= (~ADC_SC3_ADCO_MASK & ~ADC_SC3_AVGS_MASK);
	ADCCameraSC3 |= ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(3);
	ADCCameraSC3 |= ADC_SC3_CAL_MASK;
	
	while(!(ADCCameraSC1A & ADC_SC1_COCO_MASK));
	
	if(ADCCameraSC3 & ADC_SC3_CALF_MASK)
		return -1;
	calVar = 0;
	
	calVar +=ADC0_CLP0;
	calVar +=ADC0_CLP1;
	calVar +=ADC0_CLP2;
	calVar +=ADC0_CLP3;
	calVar +=ADC0_CLP4;
	calVar +=ADC0_CLPS;
	
	calVar /= 2;
	calVar |= 0x8000;
	
	ADCCameraPG = ADC_PG_PG(calVar);
	
	calVar = 0;
	
	calVar += ADC0_CLM0;
	calVar += ADC0_CLM1;
	calVar += ADC0_CLM2;
	calVar += ADC0_CLM3;
	calVar += ADC0_CLM4;
	calVar += ADC0_CLMS;
	
	calVar /= 2;
	calVar |= 0x8000;
	
	ADCCameraMG = ADC_MG_MG(calVar);
	
	ADCCameraSC3 &= ~(ADC_SC3_CAL_MASK);

	return 0;
}