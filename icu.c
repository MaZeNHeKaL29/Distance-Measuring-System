/******************************************************************************
 *
 * Module: Input Capture Unit
 *
 * File Name: icu.c
 *
 * Description: Source file for Input Capture Unit
 *
 * Author: Mazen Hekal
 *
 *******************************************************************************/

#include "icu.h"
#include "common_macros.h"
#include "gpio.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBack_Ptr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER1_CAPT_vect)
{
	if(g_callBack_Ptr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBack_Ptr)();
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 */
void ICU_init(const ICU_ConfigType *configType_Ptr)
{
	/* Configure ICP1/PD6 as i/p pin */
	GPIO_setupPinDirection(PORTD_ID, PD6, PIN_INPUT);

	/*initialize Timer1 with Normal Mode */
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);
	CLEAR_BIT(TCCR1B, WGM12);
	CLEAR_BIT(TCCR1B, WGM13);

	/* Setup which edge on the Input Capture Pin (ICP1) that is used to trigger a capture
	 * event
	 * ICES1 = 0 -> Falling
	 * ICES1 = 1 -> Rising
	 */
	TCCR1B = (TCCR1B & ~(1<<6)) | (configType_Ptr->edgeSelect << 6);

	/* Setup clock source to be used by the Timer/Counter */
	TCCR1B = (TCCR1B & ~(0x07)) | (configType_Ptr->prescaler);

	/* Initial Value for Timer1 */
	TCNT1 = 0;

	/* Initial Value for the input capture register */
	ICR1 = 0;

	/*Enable Interrupts for Input Capture Unit */
	SET_BIT(TIMSK, TICIE1);
}


/*
 * Description: Function to set the Call Back function address.
 */
void ICU_setCallBack(void (*a_function_Ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBack_Ptr = a_function_Ptr;
}

/*
 * Description: Function to set the required edge detection.
 */
void ICU_setEdgeDetectionType(const ICU_EdgeSelect edgeSelect)
{
	/* Setup which edge on the Input Capture Pin (ICP1) that is used to trigger a capture
	 * event
	 * ICES1 = 0 -> Falling
	 * ICES1 = 1 -> Rising
	 */
	TCCR1B = (TCCR1B & ~(1<<6)) | (edgeSelect << 6);
}

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 ICU_getInputCaptureValue(void)
{
	return ICR1;
}

/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void ICU_clearTimerValue(void)
{
	TCNT1 = 0;
}

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void ICU_DeInit(void)
{
	/* Clear All Timer1 Registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;

	/* Clear Interrupts for Input Capture Unit */
	CLEAR_BIT(TIMSK, TICIE1);
}


