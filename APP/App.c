/*
 * App.c
 *
 * Created: 9/16/2022 8:43:15 PM
 *  Author: Mohab Zaghloul
 */
#define __AVR_ATmega32A__
#include <avr/io.h>

#include "../UTILS/STD_TYPES.h"
#include "../HAL/LED/LED.h"
#include "../MCAL/TIMER/TIMER_CFG.h"
#include "../MCAL/TIMER/TIMER.h"
#include "../MCAL/INT/INT.h"
#include "App.h"

#include "../UTILS/BIT_MATH.h"

Traffic cars;
Traffic peds;

u8 prevCarLight = 0;
u8 prevPedLight = 0;

LED carsLight[3];
LED pedsLight[3];


void appInit(void)
{
	u8 i;
	
	//setting the ports for both traffic lights
	for(i = 0; i < 3; i++)
	{
		carsLight[i].port = GROUP_A;
		pedsLight[i].port = GROUP_B;
	}

	//setting the pins for the leds
	for (i = 0; i < 3; i++)
	{
		carsLight[i].pin = i;
		pedsLight[i].pin = i;
	}

	//Setting the leds to be low
	for (i = 0; i < 3; i++)
	{
		carsLight[0].state = LED_OFF;
		pedsLight[0].state = LED_OFF;
	}

	//Initializing the leds by the settings we did above
	for(i = 0; i < 3; i++)
	{
		LED_Init(carsLight + i);
		LED_Init(pedsLight + i);
	}
	
	cars.mode = NORMAL;
	cars.light = OFF;
	switchCarsColors();
	carsTrafficHandler();
	
	peds.mode = NORMAL;
	peds.light = OFF;
	
	//Callback function of the button
	setCallBack(changeMode,1);
	INT0_Enable();
	
	//Starting timer 0 in normal mode
	setCallBackTimer0(tickTackNormal);
	Timer0_vInit();
	setTCNT0(238);
}

void tickTackNormal(void)
{
	volatile static u8 ticks = 0;
	volatile static u8 time = 0;

	if (ticks == 122)
	{
		setTCNT0(238);
		ticks = 0;
		time++;
		if(cars.light == YELLOW)
			LED_toggle(carsLight+YELLOW);
	}
	else
		ticks++;

	if(time == 5)
	{
		time = 0;
		switchCarsColors();
		carsTrafficHandler();
	}
}

void switchCarsColors(void)
{
	switch(cars.light)
	{
		case OFF:
		cars.light = RED;
		break;
		case RED:
		prevCarLight = RED;
		cars.light = YELLOW;
		break;
		case YELLOW:
		(prevCarLight == RED)?(cars.light = GREEN):(cars.light = RED);
		break;
		case GREEN:
		prevCarLight = GREEN;
		cars.light = YELLOW;
	}
}

void carsTrafficHandler(void)
{
	switch(cars.light)
	{
		case RED:
			LED_turnOff(carsLight + YELLOW);
			LED_turnOff(carsLight + GREEN);
			LED_turnOn(carsLight + RED);
			break;
		case YELLOW:
			LED_turnOff(carsLight + RED);
			LED_turnOff(carsLight + GREEN);
			LED_turnOn(carsLight + YELLOW);
			break;
		case GREEN:
			LED_turnOff(carsLight + YELLOW);
			LED_turnOff(carsLight + RED);
			LED_turnOn(carsLight + GREEN);
	}
}





void changeMode(void)
{
	//Timer0_vClosePIE();
	

	switch(cars.mode)
	{
	case NORMAL:
		INT0_OFF();
		cars.mode = PEDESTRIAN;
		peds.mode = PEDESTRIAN;
	
		setPedColors();
		TrafficHandler();
	
		//Starting timer 0 in pedestrian mode
		setCallBackTimer0(tickTack);
		break;
	
	case PEDESTRIAN:
		cars.mode = NORMAL;
		peds.mode = NORMAL;
	
		setPedColors();					//To set peds light to OFF
		TrafficHandler();				//To turn peds light off
		carsTrafficHandler();			//To turn on cars green light
	
		//Starting timer 0 in normal mode
		setCallBackTimer0(tickTackNormal);
		INT0_ON();
	}
	
	//setTCNT0(238);
	//Timer0_vOpenPIE();
}

void tickTack(void)
{
	volatile static u8 ticks = 0;
	volatile static u8 time = 0;

	if (ticks == 122)
	{
		setTCNT0(238);
		ticks = 0;
		time++;
		if(peds.light == YELLOW)
		{
			LED_toggle(carsLight+YELLOW);
			LED_toggle(pedsLight+YELLOW);
		}
	}
	else
	ticks++;

	if(time == 5)
	{
		time = 0;
		switchColors();
		TrafficHandler();
	}
}

void setPedColors(void)
{
	if (prevPedLight == GREEN)
	{
		prevPedLight = 0;
		peds.light = OFF;
		cars.light = GREEN;
		return;
	}
	
	switch(cars.light)
	{
		case RED:
		peds.light = GREEN;
		break;
		case YELLOW:
		//(prevCarLight == RED)?(prevPedLight = GREEN):(prevPedLight = RED);
		peds.light = YELLOW;
		break;
		case GREEN:
		peds.light = YELLOW;
		cars.light = YELLOW;
		prevCarLight = GREEN;
	}
}

void switchColors(void)
{
	switch(cars.light)
	{
		case OFF:
		cars.light = RED;
		peds.light = GREEN;
		break;
		
		case RED:
		prevCarLight = RED;
		prevPedLight = GREEN;
		cars.light = YELLOW;
		peds.light = YELLOW;
		break;
		
		case YELLOW:
		if (prevPedLight == GREEN)
		{
			changeMode();
			return;
		}

		cars.light = RED;
		peds.light = GREEN;

		/*
		else
		{
			cars.light = GREEN;
			peds.light = RED;
		}
		*/
		break;
		
		case GREEN:
		prevCarLight = GREEN;
		cars.light = YELLOW;
		peds.light = YELLOW;
	}
}


void TrafficHandler(void)
{
	switch(peds.light)
	{
		case OFF:
		LED_turnOff(pedsLight + YELLOW);
		LED_turnOff(pedsLight + RED);
		LED_turnOff(pedsLight + GREEN);
		break;
		
		case GREEN:
		LED_turnOff(carsLight + YELLOW);
		LED_turnOff(carsLight + GREEN);
		LED_turnOn(carsLight + RED);
		
		LED_turnOff(pedsLight + YELLOW);
		LED_turnOff(pedsLight + RED);
		LED_turnOn(pedsLight + GREEN);
		break;
		case YELLOW:
		LED_turnOff(carsLight + RED);
		LED_turnOff(carsLight + GREEN);
		LED_turnOn(carsLight + YELLOW);
		
		LED_turnOff(pedsLight + RED);
		(prevPedLight == GREEN)? LED_turnOn(pedsLight+GREEN):LED_turnOff(pedsLight + GREEN);
		LED_turnOn(pedsLight + YELLOW);
		break;
		case RED:
		LED_turnOff(carsLight + YELLOW);
		LED_turnOff(carsLight + RED);
		LED_turnOn(carsLight + GREEN);
		
		LED_turnOff(pedsLight + YELLOW);
		LED_turnOff(pedsLight + GREEN);
		LED_turnOn(pedsLight + RED);
	}
}
