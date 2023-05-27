/*
 * LED.h
 *
 * Created: 9/15/2022 2:14:30 PM
 *  Author: Mohab Zaghloul
 */


#ifndef LED_H_
#define LED_H_

#include "../../UTILS/STD_TYPES.h"

typedef enum
{
	GROUP_A,
	GROUP_B,
	GROUP_C,
	GROUP_D
}LED_PORT;

typedef enum
{
	LED_OFF = 0,
	LED_ON
}LED_STATE;

typedef struct
{
	LED_PORT port;
	uint8_t pin;
	LED_STATE state;
}LED;

//Take the led configuration as input (obj) to set its pin and initial state
void LED_Init(LED * obj);

//Turns on the LED
void LED_turnOn(LED * obj);

//Turns off the LED
void LED_turnOff(LED * obj);

//Toggle the LED
void LED_toggle(LED * obj);

#endif /* LED_H_ */
