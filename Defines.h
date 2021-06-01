#include "MKL25Z4.h"

/****************Pini Senzori Distanta****************/

#define PortSenzorDistantaTrig		PORTD->PCR[4] //FTM0_CH4
#define PortSenzorDistantaTrigMux	4
#define PortSenzorDistantaEchoS		PORTD->PCR[6]
#define PortSenzorDistantaSPin		6
#define PortSenzorDistantaEchoSM	1
#define PortSenzorDistantaEchoD		PORTD->PCR[7]
#define PortSenzorDistantaDPin		7
#define PortSenzorDistantaEchoDM	1
#define PortSenzorDistantaEchoC		PORTA->PCR[17]
#define PortSenzorDistantaCPin		17
#define PortSenzorDistantaEchoCM	1


/*****************Valori Senzor Distanta***************/

#define SENZOR_DISTANTA_PWM				0xF
#define	FACTORMULDISTANTA					0.01122f //cm/percount
#define DISTANTAEROARE						8.1f //cm
#define DISTANTATHRESHOLD					45 //cm

/*****************Pini Senzor Turatie*****************/

#define PortSenzorTuratie					PORTB->PCR[3] //FTM2_CH1
#define	PortSenzorTuratieMux			3
#define SenzorTuratieMOD					0xB71B

/**************Valori Senzor Turatie******************/

#define NUMBER_OF_MAGNETS					6
#define DIAMETER_OF_WHEEL					0.05f // metri
#define PI												3.14f
#define COEFFICIENT_MEASURE_TIME	0.125f
#define NRINPUTCOEFF							(PI * DIAMETER_OF_WHEEL / COEFFICIENT_MEASURE_TIME) / NUMBER_OF_MAGNETS

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

#define MotorMaxCount							0x8CA0

/********************Pini ServoMotor******************/

#define PortServoMotor						PORTA->PCR[12] //FTM1_CH0

#define PortServoMux							3

#define ServoMaxCount							0xEA60
#define	ServoMinVal								0x5DC
#define	ServoMaxVal								0x1D4C

/*********************Valori TPM**********************/

#define TPMDIVIDERSERVO						4
#define TPMDIVIDERTURATIE					7
#define TPMDIVIDERMOTOARE					5
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
#define CAMERA_IGNORE_EDGE_VAL		18

/**********************Matematica*********************/

//--------------------Camera---------------------

#define COEFFICIENT_PIXELI_CUT		2
#define PIXELI_CUT_LOW_VAL				20
#define PIXELI_CUT_HIGH_VAL				40
#define LINE_MAX_ERROR_MID				3
#define LINE_MAX_ERROR_FOR_SPEED	6

//--------------------Motoare--------------------

#define MOTOARE_VITEZA_MAXIM_SIG  0.8f
#define SERVOMOTOR_MAXIM_SIG			0.4L
#define MOTOARE_SENS_INAITE				1
#define MOTOARE_SENS_SPATE				-1
#define MAX_VITEZA_MULTIPLIER			6
#define MIN_VITEZA_MULTIPLIER			4
#define MOTOARE_VITEZA_MAX_MS			NRINPUTCOEFF * MAX_VITEZA_MULTIPLIER
#define MOTOARE_VITEZA_CURBA_MS	  NRINPUTCOEFF * MIN_VITEZA_MULTIPLIER
#define SERVOMOTOR_STRAIGHT_ERR		-0.07f //-0.07f
#define SERVOMOTOR_THRESHOLD			13

//----------------------PID----------------------

#define PID_TS										COEFFICIENT_MEASURE_TIME
#define PID_KP										0.185f
#define PID_KI										0.001f
#define PID_KD										0.045f


/**********************Pini UART**********************/

#define PortUartRX								PORTA->PCR[1]
#define PortUartTX								PORTA->PCR[2]
#define PortUartRXMux							2
#define PortUartTXMux							2

/********************Valori UART**********************/

#define BUS_CLOCK									DEFAULT_SYSTEM_CLOCK

/***********************Debug*************************/

#define CAMERA_DEBUG_LINE_SCAN		0
#define SERVO_DEBUG_ANGLE					0
#define VITEZA_DEBUG_VITEZA_CUR		0
#define SENZOR_TUR_SEMNAL_DEBUG		0
#define SENZOR_DISTANTA_DEBUG_S		0
#define SENZOR_DISTANTA_DEBUG_D		0
#define SENZOR_DISTANTA_DEBUG_C		0
#define	DEZACTIVARE_PID_DEBUG			0

#define CAMERA_EDGE_VAL						0xFF
#define VITEZA_SEMNAL_TIME_DEBUG	25

/***********************Stari************************/

#define STATE_DRUM_FARA_OBSTACOL	0
#define STATE_DRUM_OBSTACOL_FATA	1
#define STATE_DRUM_OBSTACOL_LAT		2
#define STATE_DRUM_OBSTACOL_DIAG	3
