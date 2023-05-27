/*
 * LED.c
 *
 * Created: 9/15/2022 2:15:15 PM
 *  Author: Mohab Zaghloul
 */ 

#include "LED.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/DIO/DIO_CFG.h"

void LED_Init(LED * obj)
{
	setPinDir(obj->port, obj->pin, OUTPUT);
	setPinValue(obj->port, obj->pin, obj->state);
}

void LED_turnOn(LED * obj)
{
	obj->state = HIGH;
	setPinValue(obj->port, obj->pin, obj->state);
}

void LED_turnOff(LED * obj)
{
	obj->state = LOW;
	setPinValue(obj->port, obj->pin, obj->state);
}

void LED_toggle(LED * obj)
{
	obj->state = !(obj->state);
	setPinValue(obj->port, obj->pin, obj->state);
}
