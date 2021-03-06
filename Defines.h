#include "MKL25Z4.h"

/****************Pini Senzori Distanta****************/

#define PortSenzorDistantaTrig		PORTD->PCR[4] //TPM0_CH4
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
#define	FACTOR_MUL_DISTANTA				0.01133f //cm/percount
#define DISTANTA_EROARE						8.1f //cm
#define DISTANTA_THRESHOLD				30 //cm
#define DISTANTA_THRESHOLD_MIJLOC	45 //cm

/*****************Pini Senzor Turatie*****************/

#define PortSenzorTuratie					PORTB->PCR[3] //TPM2_CH1
#define	PortSenzorTuratieMux			3
#define SenzorTuratieMOD					0xB71B

/**************Valori Senzor Turatie******************/

#define NUMBER_OF_MAGNETS					6
#define DIAMETER_OF_WHEEL					0.05f // metri
#define PI												3.14f
#define COEFFICIENT_MEASURE_TIME	0.125f
#define NR_INPUT_COEFF						(PI * DIAMETER_OF_WHEEL / COEFFICIENT_MEASURE_TIME) / NUMBER_OF_MAGNETS

/********************Pini Motor***********************/

#define PortMotorStanga						PORTA->PCR[5] //TPM0_CH2
#define PortMotorDreapta					PORTD->PCR[1] //TPM0_CH1

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

/********************Valori Motor*********************/


#define MOTOARE_VITEZA_MAXIM_SIG  0.85f
#define SERVOMOTOR_MAXIM_SIG			0.4L
#define MOTOARE_SENS_INAITE				1
#define MOTOARE_SENS_SPATE				-1
#define MAX_VITEZA_MULTIPLIER			5.5f
#define MIN_VITEZA_MULTIPLIER			2.75f
#define MAX_VITEZA_OBS_MULTIPLIER	1.75f
#define MOTOARE_VITEZA_MAX_MS			NR_INPUT_COEFF * MAX_VITEZA_MULTIPLIER
#define MOTOARE_VITEZA_CURBA_MS	  NR_INPUT_COEFF * MIN_VITEZA_MULTIPLIER
#define MOTOARE_VITEZA_OBSTACOL		NR_INPUT_COEFF * MAX_VITEZA_OBS_MULTIPLIER

/********************Pini ServoMotor******************/

#define PortServoMotor						PORTA->PCR[12] //TPM1_CH0

#define PortServoMux							3

#define ServoMaxCount							0xEA60
#define	ServoMinVal								0x5DC
#define	ServoMaxVal								0x1D4C

/********************Valori Servomotor****************/

#define SERVOMOTOR_STRAIGHT_ERR		-0.07f //-0.07f
#define SERVOMOTOR_MAX_SIGNAL			0.4L
#define SERVOMOTOR_THRESHOLD			12

/*********************Valori TPM**********************/

#define TPM_DIVIDER_SERVO					4
#define TPM_DIVIDER_TURATIE				7
#define TPM_DIVIDER_MOTOARE				5
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

/******************Valori pentru camera***************/

#define NUMBER_OF_CLOCKS					256
#define PIT_HALF_CLOCK						0x8FF
#define PIT_QUARTER_CLOCK					PIT_HALF_CLOCK/2
#define PIT_SI_CLOCK							PIT_HALF_CLOCK*(256+8)
#define CAMERA_START							0
#define	CAMERA_SET_CLK						1
#define CAMERA_CLEAR_SI						2
#define CAMERA_FINAL							3
#define CAMERA_IGNORE_EDGE_VAL		12
#define LINE_MAX_ERROR_FOR_SPEED	5

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

/************************PID**************************/

#define PID_TS										COEFFICIENT_MEASURE_TIME
#define PID_KP										0.67f//0.66f
#define PID_KI										0.0025f//0.0025f
#define PID_KD										0.0067f//0.0065f

/**********************Pini UART**********************/

#define PortUartRX								PORTA->PCR[1]
#define PortUartTX								PORTA->PCR[2]
#define PortUartRXMux							2
#define PortUartTXMux							2

/********************Valori UART**********************/

#define BUS_CLOCK									DEFAULT_SYSTEM_CLOCK

/***********************Debug*************************/

#define CAMERA_DEBUG_LINE_SCAN		0
#define SENZOR_TUR_SEMNAL_DEBUG		0
#define SENZOR_DISTANTA_DEBUG_S		0
#define SENZOR_DISTANTA_DEBUG_D		0
#define SENZOR_DISTANTA_DEBUG_C		0
#define	DEZACTIVARE_PID_DEBUG			0
#define DEZACTIVARE_MODUL_DIST		0

#define CAMERA_EDGE_VAL						0xFF

/***********************Stari************************/

#define STATE_DRUM_FARA_OBSTACOL	0
#define STATE_DRUM_OBSTACOL				1

