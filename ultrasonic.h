/******************************************************************************
 *
 * Module: Ultrasonic Sensor
 *
 * File Name: ultrasonic.h
 *
 * Description: Header file for Ultrasonic Sensot
 *
 * Author: Mazen Hekal
 *
 *******************************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

#define ULTRASONIC_TRIGGER_PORT_ID	PORTB_ID
#define ULTRASONIC_TRIGGER_PIN_ID	PIN5_ID

#define ULTRASONIC_ECHO_PORT_ID		PORTD_ID
#define ULTRASONIC_ECHO_PIN_ID		PIN6_ID

#define ICU_F_CPU_PRESCALAR				F_CPU_8
#define ICU_F_CPU_PRESCALAR_VALUE		8
#define ICU_FIRST_DETECTION_EDGE		RISING
#define SPEED_SOUND_CM_S				34000

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * 1. Initialize the ICU driver as required.
 * 2.Setup the ICU call back function.
 * 3.Setup the direction for the trigger pin as output pin through the GPIO driver.
 */
void ULTRASONIC_init(void);

/*
 * Description :
 * Send the Trigger pulse to the ultrasonic.
 */
void ULTRASONIC_trigger(void);

/*
 * Description :
 * 1.Send the trigger pulse by using ULTRASONIC_trigger function.
 * 2.Start the measurements by the ICU from this moment.
 */
uint16 ULTRASONIC_readDistance(void);

/*
 * Description :
 * 1.This is the call back function called by the ICU driver.
 * 2.This is used to calculate the high time (pulse time) generated by the ultrasonic sensor.
 */
void ULTRASONIC_edgeProcessing(void);


#endif /* ULTRASONIC_H_ */