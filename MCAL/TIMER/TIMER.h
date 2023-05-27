/*
 * TIMER.h
 *
 *  Created on: Sep 6, 2022
 *      Author: loppy
 */

#ifndef MCAL_TIMER_TIMER_H_
#define MCAL_TIMER_TIMER_H_

#include <avr/io.h>
#include "../../UTILS/STD_TYPES.h"
#include "TIMER_CFG.h"

/************** TIMER PRESCALER **************/
#define TIMER0_PRESCALER			4
#define TIMER1_PRESCALER			4
#define TIMER2_PRESCALER			4

/************ MODE CONFIGURATION ***********/
#define TIMER0_MODE TIMER_OVF_MODE
#define TIMER1_MODE T1_MODE_FAST_PWM_TOP_ICR1
#define TIMER2_MODE TIMER_CTC_MODE

/************ PIN CONFIGURATION ************/
#define TIMER1_OC_PIN	OC1A

/************ Timer 0 ***********/
void Timer0_vInit(void);

void setTCNT0(u8 preload_value);

void clearTCNT0(void);

void setOCR0(u8 value);

void Timer0_vClosePIE();

void Timer0_vOpenPIE();

/************ Timer 2 ***********/
void Timer2_vInit(void);

void setTCNT2(u8 preload_value);

void clearTCNT2(void);

void setOCR2(u8 value);

void Timer2_vClosePIE();

void Timer2_vOpenPIE();

/************ Timer 1 ***********/
#define ICR1_DEFAULT_TOP_VALUE	20000
#define OCR1_DEFAULT_VALUE		1000

void Timer1_vInit();

void setTopValue(u16 top);

void setOCR1A_Value(u16 duty);


#endif /* MCAL_TIMER_TIMER_H_ */
