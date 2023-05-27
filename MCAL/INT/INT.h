/*
 * INT.h
 *
 *  Created on: Aug 31, 2022
 *      Author: loppy
 */

#ifndef MCAL_INT_INT_H_
#define MCAL_INT_INT_H_

#include <avr/interrupt.h>
#include "../../UTILS/STD_TYPES.h"
#include "../../UTILS/BIT_MATH.h"

#define INT_EDGE 0
/*
 * 0- FALLING EDGE
 * 1- RISING EDGE
 * 2- SENSE ANY EDGE
 * 3- LOW LEVEL*/
#define INT2_EDGE 0
/*
 * 0- FALLING EDGE
 * 1- RISING EDGE
 * */


void setCallBack(void(*ptrToFunc)(void), u8 i);

void __vector_1(void) __attribute__((signal));

void __vector_2(void) __attribute__((signal));

void __vector_3(void) __attribute__((signal));

void INT0_Enable();
void INT0_ON();
void INT0_OFF();

void INT1_Enable();

void INT2_Enable();

/*************** Timer-0 Interrupt **************/

void setCallBackTimer0(void(*ptrToFunc)(void));

void TIMER0_OVF_vect(void) __attribute__((signal));

void TIMER0_COMP_vect(void) __attribute__((signal));

/*************** Timer-2 Interrupt **************/

void setCallBackTimer2(void(*ptrToFunc)(void));

void TIMER2_OVF_vect(void) __attribute__((signal));

void TIMER2_COMP_vect(void) __attribute__((signal));


/*************** Timer-1 Interrupt **************/

void setCallBackTimer1(void(*ptrToFunc)(void));

void __vector_6(void) __attribute__((signal));

#endif /* MCAL_INT_INT_H_ */
