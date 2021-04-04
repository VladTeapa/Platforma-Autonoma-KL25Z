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

#define SensMotorInainte					1
#define SensMotorInSpate					-1

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
#define PITSIClock								PITHalfClock*(256+8)
#define CAMERA_START							0
#define	CAMERA_SET_CLK						1
#define CAMERA_CLEAR_SI						2
#define CAMERA_FINAL							3
#define CAMERA_FIRST_IMAGE_TRUE		1
#define CAMERA_FIRST_IMAGE_FALSE	1
#define CAMERA_IGNORE_EDGE_VAL		40

/**********************Matematica*********************/

#define COEFFICIENT_PIXELI_CUT		2
#define PIXELI_CUT_LOW_VAL				20
#define PIXELI_CUT_HIGH_VAL				40
#define LINE_MAX_ERROR_MID				4

/**********************Pini UART**********************/

#define PortUartRX								PORTA->PCR[1]
#define PortUartTX								PORTA->PCR[2]
#define PortUartRXMux							2
#define PortUartTXMux							2

/********************Valori UART**********************/

#define BUS_CLOCK									DEFAULT_SYSTEM_CLOCK

/***********************Debug************************/

#define CAMERA_DEBUG							1
#define CAMERA_EDGE_VAL						0xFF

/***********************Stari************************/

#define NO_OBSTACLE_STRAIGHT			0
#define NO_OBSTACLE_CURVE					1
#define OBSTACLE_LEFT							2
#define OBSTACLE_RIGHT						3