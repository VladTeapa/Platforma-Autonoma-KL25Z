#include "MKL25Z4.h"

/****************Pini Senzor Turatie******************/

#define PortSenzorTuratie					PORTC->PCR[1] //FTM0_CH0
#define	PortSenzorTuratieMux			4

/**************Valori Senzor Turatie******************/

#define NUMBER_OF_MAGNETS					6
#define DIAMETER_OF_WHEEL					0.05
#define PI												3.14
#define COEFFICIENT_MEASURE_TIME	0.2

/********************Pini Motor***********************/

#define PortMotorStanga						PORTA->PCR[5] //FTM0_CH2
#define PortMotorDreapta					PORTD->PCR[1] //FTM0_CH1

#define PortMotorActivareDreapta	PORTD->PCR[2]
#define PortMotorActivareStanga		PORTD->PCR[3]
#define PortSensMotor							PORTD->PCR[5]

#define GPIODirMotorDreapta				GPIOD_PDDR
#define GPIODirMotorStanga				GPIOD_PDDR
#define GPIODirSensMotor					GPIOD_PDDR

#define GPIOSMotorDreapta					GPIOD_PSOR
#define GPIOSMotorStanga					GPIOD_PSOR
#define GPIOSSensMotor						GPIOD_PSOR

#define GPIOCMotorDreapta					GPIOD_PCOR
#define GPIOCMotorStanga					GPIOD_PCOR
#define GPIOCSensMotor						GPIOD_PCOR

#define GPIOPinMotorDreapta				3
#define GPIOPinMotorStanga				2
#define GPIOPinSensMotor					5

#define PortMotorStangaMux				3
#define PortMotorDreaptaMux				4

#define PortMotorActivareDreaptaM	1
#define PortMotorActivareStangaM	1
#define PortSensMotorMux					1

#define MotorMaxCount							0xEA60

/********************Pini ServoMotor******************/

#define PortServoMotor						PORTD->PCR[4] //FTM0_CH4

#define PortServoMux							4

#define ServoMaxCount							0xEA60
#define	ServoMinVal								ServoMaxCount*0.025
#define	ServoMaxVal								ServoMaxCount*0.125

/********************Pini TPM*************************/

#define TPMDivider								4

#define TPMClockSource						1
#define TPMPLLFLLSELValue					0

/********************Pini Camera**********************/

#define PortAOCamera							PORTB->PCR[0] //ADC0_SE8
#define PortAOCameraMux						0
#define PortSICamera							PORTC->PCR[6]
#define PortSICameraMux						1
#define PortCLKCamera							PORTC->PCR[7]
#define PortCLKCameraMux					1

#define GPIOPinSICamera						6
#define GPIOPinCLKCamera					7

#define GPIODirSICamera						GPIOC_PDDR
#define GPIODirCLKCamera					GPIOC_PDDR

#define GPIOSSICamera							GPIOC_PSOR
#define GPIOSCLKCamera						GPIOC_PSOR

#define GPIOCSICamera							GPIOC_PCOR
#define GPIOCCLKCamera						GPIOC_PCOR

#define GPIOTCLKCamera						GPIOC_PTOR

/*********************Pini ADC************************/

#define ADCCameraResult						ADC0_RA
#define ADCCameraCFG1							ADC0_CFG1
#define ADCCameraCFG2							ADC0_CFG2
#define	ADCCameraPG								ADC0_PG
#define ADCCameraMG								ADC0_MG
#define ADCCameraSC1A							ADC0_SC1A
#define ADCCameraSC1B							ADC0_SC1B
#define ADCCameraSC1							ADC0_SC1
#define ADCCameraSC2							ADC0_SC2
#define ADCCameraSC3							ADC0_SC3

/******************Valori pentru camera***************/

#define CAMERA_TERMINAT						1
#define CAMERA_PROCESARE					0
#define NumberOfClocks						256
#define PITHalfClock							0x8FF
#define PITQuarterClock						PITHalfClock/2
#define PITSIClock								PITHalfClock*(256+20)
#define CAMERA_START							0
#define	CAMERA_SET_CLK						1
#define CAMERA_CLEAR_SI						2
#define CAMERA_FINAL							3
#define CAMERA_FIRST_IMAGE_TRUE		1
#define CAMERA_FIRST_IMAGE_FALSE	1
#define CAMERA_IGNORE_EDGE_VAL		30

/**********************Matematica*********************/

//--------------------Camera---------------------

#define COEFFICIENT_PIXELI_CUT		2
#define PIXELI_CUT_LOW_VAL				20
#define PIXELI_CUT_HIGH_VAL				40
#define LINE_MAX_ERROR_MID				5

//--------------------Motoare--------------------

#define MOTOARE_VITEZA_MAXIMA_SIG 0.5L
#define MOTOARE_SENS_INAITE				1
#define MOTOARE_SENS_SPATE				-1
#define MOTOARE_VITEZA_MAX_MS			1
#define MOTOARE_VITEZA_FRANARE_MS	0.25L
#define SERVOMOTOR_STRAIGHT_ERR		-0.02L
#define SERVOMOTOR_THRESHOLD			30

//----------------------PID----------------------

#define PID_TS										200
#define PID_KP										1
#define PID_KI										1
#define PID_KD										1

/**********************Pini UART**********************/

#define PortUartRX								PORTA->PCR[1]
#define PortUartTX								PORTA->PCR[2]
#define PortUartRXMux							2
#define PortUartTXMux							2

/********************Valori UART**********************/

#define BUS_CLOCK									DEFAULT_SYSTEM_CLOCK

/***********************Debug************************/

#define CAMERA_DEBUG_LINE_SCAN		1
#define CAMERA_DEBUG_LINE					0
#define VITEZA_DEBUG_VITEZA_CUR		0
#define TURATIE_DEBUG_FUNCTIE_TR	0
#define CAMERA_EDGE_VAL						0xFF


/***********************Stari************************/

#define STATE_DRUM_DREPT					0
#define STATE_DRUM_CURBA					1
#define STATE_DRUM_CURBATODREPT		2
#define STATE_OBSTACOL_DREAPTA		3
#define STATE_OBSTACOL_STANGA			4
#define	STATE_START								5
#define STATE_DRUM_DREPTTOCURBA		6