/*
 * INT.c
 *
 *  Created on: Aug 31, 2022
 *      Author: loppy
 */
#define __AVR_ATmega32A__
#include <avr/io.h>
#include "INT.h"

static volatile void (*ptrToFunc1)(void) = ((void*)0);
static volatile void (*ptrToFunc2)(void) = ((void*)0);
static volatile void (*ptrToFunc3)(void) = ((void*)0);

static volatile void (*ptrToFuncTimer0)(void) = ((void*)0);
static volatile void (*ptrToFuncTimer2)(void) = ((void*)0);
static volatile void (*ptrToFuncTimer1)(void) = ((void*)0);

void setCallBack(void(*ptrToFunc)(void), u8 i)
{
	switch(i)
	{
	case 1:
		ptrToFunc1 = ptrToFunc;
		break;
	case 2:
		ptrToFunc2 = ptrToFunc;
		break;
	case 3:
		ptrToFunc3 = ptrToFunc;
		break;
	}
}

void __vector_1(void)
{
	ptrToFunc1();
}

void __vector_2(void)
{
	ptrToFunc2();
}

void __vector_3(void)
{
	ptrToFunc3();
}

void INT0_Enable()
{
	CLEAR_BIT(DDRD, 2);	//set PD2 as input
	SET_BIT(PORTD, 2);	//Activate pull-up for PD2

#if INT_EDGE == 0
	SET_BIT(MCUCR, 1);	//sense falling edge for INT1
	CLEAR_BIT(MCUCR, 0);
#elif INT_EDGE == 1
	SET_BIT(MCUCR, 1);	//sense rising edge for INT1
	SET_BIT(MCUCR, 0);
#elif INT_EDGE == 2
	CLEAR_BIT(MCUCR, 1);	//sense any change for INT1
	SET_BIT(MCUCR, 0);
#elif INT_EDGE == 3
	CLEAR_BIT(MCUCR, 1);	//sense low level for INT1
	CLEAR_BIT(MCUCR, 0);
#else
	#error Unsupported configuration of INT0
#endif
	SET_BIT(SREG, 7);	//enable GIE
	SET_BIT(GICR, 6);	//Enable PIE for INT1
}

void INT0_ON()
{
	SET_BIT(GICR, 6);
}

void INT0_OFF()
{
	CLEAR_BIT(GICR, 6);
}

void INT1_Enable()
{
	CLEAR_BIT(DDRD, 3);	//set PD2 as input
	SET_BIT(PORTD, 3);	//Activate pull-up for PD2

#if INT_EDGE == 0
	SET_BIT(MCUCR, 3);	//sense falling edge for INT1
	CLEAR_BIT(MCUCR, 2);
#elif INT_EDGE == 1
	SET_BIT(MCUCR, 3);	//sense rising edge for INT1
	SET_BIT(MCUCR, 2);
#elif INT_EDGE == 2
	CLEAR_BIT(MCUCR, 3);	//sense any edge for INT1
	SET_BIT(MCUCR, 2);
#elif INT_EDGE == 3
	CLEAR_BIT(MCUCR, 3);	//sense low level for INT1
	SET_BIT(MCUCR, 2);
#else
	#error Unsupported configuration of INT1
#endif
	SET_BIT(SREG, 7);	//enable GIE
	SET_BIT(GICR, 7);	//Enable PIE for INT1
}

void INT2_Enable()
{
	CLEAR_BIT(DDRB, 2);	//set PD2 as input
	SET_BIT(PORTB, 2);	//Activate pull-up for PD2

#if INT2_EDGE == 0
	CLEAR_BIT(MCUCSR, 6);	//sense falling edge for INT1
#elif INT2_EDGE == 1
	SET_BIT(MCUCSR, 6);	//sense rising edge for INT1
#else
	#error Unsupported configuration of INT2
#endif

	SET_BIT(SREG, 7);	//enable GIE
	SET_BIT(GICR, 5);	//Enable PIE for INT1
}


/*************** Timer-0 Interrupt **************/

void setCallBackTimer0(void(*ptrToFunc)(void))
{
	ptrToFuncTimer0 = ptrToFunc;
}

void TIMER0_OVF_vect(void)
{
	ptrToFuncTimer0();
}

void TIMER0_COMP_vect(void)
{
	ptrToFuncTimer0();
}

/*************** Timer-2 Interrupt **************/

void setCallBackTimer2(void(*ptrToFunc)(void))
{
	ptrToFuncTimer2 = ptrToFunc;
}

void TIMER2_OVF_vect(void)
{
	ptrToFuncTimer2();
}

void TIMER2_COMP_vect(void)
{
	ptrToFuncTimer2();
}


/*************** Timer-1 Interrupt **************/

void setCallBackTimer1(void(*ptrToFunc)(void))
{
	ptrToFuncTimer1 = ptrToFunc;
}


void __vector_6(void)
{
	ptrToFuncTimer1();
}
