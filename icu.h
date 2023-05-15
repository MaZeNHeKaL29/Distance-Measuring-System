/******************************************************************************
 *
 * Module: Input Capture Unit
 *
 * File Name: icu.c
 *
 * Description: Header file for Input Capture Unit
 *
 * Author: Mazen Hekal
 *
 *******************************************************************************/



#ifndef ICU_H_
#define ICU_H_

#include "std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}ICU_Prescaler;

typedef enum{
	FALLING,RISING
}ICU_EdgeSelect;

typedef struct{
	ICU_Prescaler prescaler;
	ICU_EdgeSelect edgeSelect;
}ICU_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 */
void ICU_init(const ICU_ConfigType *configType_Ptr);

/*
 * Description: Function to set the Call Back function address.
 */
void ICU_setCallBack(void (*a_function_Ptr)(void));

/*
 * Description: Function to set the required edge detection.
 */
void ICU_setEdgeDetectionType(const ICU_EdgeSelect edgeSelect);

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 ICU_getInputCaptureValue(void);

/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void ICU_clearTimerValue(void);

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void ICU_DeInit(void);



#endif /* ICU_H_ */
