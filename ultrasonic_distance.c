/******************************************************************************
 *
 * Module: Ultrasonic Distance Main
 *
 * File Name: ultrasonic_distance.c
 *
 * Description: Main Function file for Ultrasonic Distance
 *
 * Author: Mazen Hekal
 *
 *******************************************************************************/

#include "lcd.h"
#include "ultrasonic.h"
#include <util/delay.h>

/*******************************************************************************
 *                                Main Function                                *
 *******************************************************************************/

int main(void)
{
	uint16 distance;
	/* initialize LCD */
	LCD_init();
	LCD_displayString("Distance = ");
	/* initialize Ultrasonic sensor */
	ULTRASONIC_init();
	while(1)
	{
		_delay_us(10);
		/* get distance value and print on screen */
		distance = ULTRASONIC_readDistance();
		LCD_moveCursor(0, 11);
		LCD_displayInteger(distance);
		LCD_displayString("cm  ");
	}
}
