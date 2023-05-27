/*
 * TIMER.c
 *
 *  Created on: Sep 6, 2022
 *      Author: loppy
 */
#define __AVR_ATmega32A__
#include <avr/io.h>
#include "TIMER.h"
#include "../../UTILS/BIT_MATH.h"


/*************************************************************************/
/******************************** Timer 0 ********************************/

void Timer0_vInit(void)
{
	//Disable all interrupts until we init
	CLEAR_BIT(SREG, 7);

	#if TIMER0_MODE == TIMER_OVF_MODE

	//Overflow mode
	CLEAR_BIT(TCCR0, 3);
	CLEAR_BIT(TCCR0, 6);

	//disable OC0
	TCCR0 |= (0x30 & (COM_NON_PWM_DISCONNECT_OC<<4));

	//Enable PIE of the Normal mode
	SET_BIT(TIMSK, 0);


	#elif TIMER0_MODE == TIMER_CTC_MODE

	//Force out compare (for CTC)
	SET_BIT(TCCR0, 7);

	//Clear Timer on Compare mode
	SET_BIT(TCCR0, 3);
	CLEAR_BIT(TCCR0, 6);

	//disable OC0
	TCCR0 |= (0x30 & (COM_NON_PWM_DISCONNECT_OC<<4));

	//Set OCR0 Value
	setOCR0(250);

	//Enable PIE of the CTC mode
	SET_BIT(TIMSK, 1);


	#elif TIMER0_MODE == TIMER_FAST_PWM_MODE

	//Fast-PWM Mode
	SET_BIT(TCCR0, 3);
	SET_BIT(TCCR0, 6);

	//Compare Output Mode
	TCCR0 |= (0x30 & (COM_PWM_CLEAR_OC<<4));

	//Set OCR0 Value
	setOCR0(128);


	#elif TIMER0_MODE == TIMER_PHASE_PWM_MODE

	//Fast-PWM Mode
	CLEAR_BIT(TCCR0, 3);
	SET_BIT(TCCR0, 6);

	//Compare Output Mode
	TCCR0 |= (0x30 & (COM_PWM_CLEAR_OC<<4));

	//Set OCR0 Value
	setOCR0(128);

	#endif

	//Enable GIE
	SET_BIT(SREG, 7);

	//Choosing prescaler (Starting timer)
	TCCR0 |= (TIMER0_PRESCALER & 0x07);
}

void setTCNT0(u8 preload_value)
{
	TCNT0 = preload_value;
}

void clearTCNT0(void)
{
	TCNT0 = 0;
}

void setOCR0(u8 value)
{
	OCR0 = value;
}

void Timer0_vClosePIE()
{
	#if TIMER0_MODE == TIMER_OVF_MODE
	CLEAR_BIT(TIMSK, 0);
	#elif TIMER0_MODE == TIMER_CTC_MODE
	CLEAR_BIT(TIMSK, 1);
	#endif
}

void Timer0_vOpenPIE()
{
	#if TIMER0_MODE == TIMER_OVF_MODE
	SET_BIT(TIMSK, 0);
	#elif TIMER0_MODE == TIMER_CTC_MODE
	SET_BIT(TIMSK, 1);
	#endif
}


/*************************************************************************/
/******************************** Timer 2 ********************************/

void Timer2_vInit(void)
{
	//Disable all interrupts until we init
	CLEAR_BIT(SREG, 7);

	#if TIMER2_MODE == TIMER_OVF_MODE

	//Overflow mode
	CLEAR_BIT(TCCR2, 3);
	CLEAR_BIT(TCCR2, 6);

	//disable OC0
	TCCR2 |= (0x30 & (COM_NON_PWM_DISCONNECT_OC<<4));

	//Enable PIE of the Normal mode
	SET_BIT(TIMSK, 6);


	#elif TIMER2_MODE == TIMER_CTC_MODE

	//Force out compare (for CTC)
	SET_BIT(TCCR2, 7);

	//Clear Timer on Compare mode
	SET_BIT(TCCR2, 3);
	CLEAR_BIT(TCCR2, 6);

	//disable OC0
	TCCR2 |= (0x30 & (COM_NON_PWM_DISCONNECT_OC<<4));

	//Set OCR0 Value
	setOCR2(250);

	//Enable PIE of the CTC mode
	SET_BIT(TIMSK, 7);


	#elif TIMER2_MODE == TIMER_FAST_PWM_MODE

	//Fast-PWM Mode
	SET_BIT(TCCR2, 3);
	SET_BIT(TCCR2, 6);

	//Compare Output Mode
	TCCR2 |= (0x30 & (COM_PWM_CLEAR_OC<<4));

	//Set OCR0 Value
	setOCR2(128);


	#elif TIMER2_MODE == TIMER_PHASE_PWM_MODE

	//Fast-PWM Mode
	CLEAR_BIT(TCCR2, 3);
	SET_BIT(TCCR2, 6);

	//Compare Output Mode
	TCCR2 |= (0x30 & (COM_PWM_CLEAR_OC<<4));

	//Set OCR0 Value
	setOCR2(128);

	#endif

	//Enable GIE
	SET_BIT(SREG, 7);

	//Choosing prescaler (Starting timer)
	TCCR2 |= (TIMER2_PRESCALER & 0x07);
}

void setTCNT2(u8 preload_value)
{
	TCNT2 = preload_value;
}

void clearTCNT2(void)
{
	TCNT2 = 0;
}

void setOCR2(u8 value)
{
	OCR2 = value;
}

void Timer2_vClosePIE()
{
	#if TIMER2_MODE == TIMER_OVF_MODE
	CLEAR_BIT(TIMSK, 6);
	#elif TIMER2_MODE == TIMER_CTC_MODE
	CLEAR_BIT(TIMSK, 7);
	#endif
}

void Timer2_vOpenPIE()
{
	#if TIMER2_MODE == TIMER_OVF_MODE
	SET_BIT(TIMSK, 6);
	#elif TIMER2_MODE == TIMER_CTC_MODE
	SET_BIT(TIMSK, 7);
	#endif
}




/*************************************************************************/
/******************************** Timer 1 ********************************/

void Timer1_vInit()
{
	//Disable all interrupts until we init
	CLEAR_BIT(SREG, 7);

	#if TIMER1_MODE == T1_MODE_FAST_PWM_TOP_ICR1

	//Choose non-inverting mode
	TCCR1A |= (0xC0 & (COM_PWM_CLEAR_OC<<6));
	TCCR1A |= (0x30 & (COM_PWM_CLEAR_OC<<4));

	//Choose Waveform Generation Mode no. 14
	TCCR1B |= (0x18 & (T1_MODE_FAST_PWM_TOP_ICR1<<1));
	TCCR1A |= (0x03 & T1_MODE_FAST_PWM_TOP_ICR1);

	//Disable output compare
	CLEAR_BIT(TCCR1A, 3);
	CLEAR_BIT(TCCR1A, 2);

	//Set Default Top Value
	ICR1 = ICR1_DEFAULT_TOP_VALUE;

			//Set Default Compare Value
			#if TIMER1_OC_PIN == OC1A
			OCR1A = OCR1_DEFAULT_VALUE;
			#elif TIMER1_OC_PIN == OC1B
			OCR1B = OCR1_DEFAULT_VALUE;
			#endif

	//Initialize counter by zero
	TCNT1 = 0;


	#elif TIMER1_MODE == TIMER1_ICU_MODE

	//Choose Waveform Generation Mode no. 0
	TCCR1B |= (0x18 & (T1_MODE_NORMAL<<1));
	TCCR1A |= (0x03 & T1_MODE_NORMAL);

	//Set the Input capture edge select (falling edge)
	CLEAR_BIT(TCCR1B, 6);

	//Enable PIE of the ICU
	SET_BIT(TIMSK,5);

	#elif TIMER1_MODE == T1_MODE_CTC_TOP_ICR1

	//Set compare output mode
	TCCR1A |= (0xC0 & (COM_NON_PWM_DISCONNECT_OC<<6));
	TCCR1A |= (0x30 & (COM_NON_PWM_DISCONNECT_OC<<4));

	//Choose Waveform Generation Mode no. 12
	TCCR1B |= (0x18 & (T1_MODE_CTC_TOP_ICR1<<1));
	TCCR1A |= (0x03 & T1_MODE_CTC_TOP_ICR1);

		//Force Output Compare and Default compare value and PIE
		#if TIMER1_OC_PIN == OC1A
		OCR1A = OCR1_DEFAULT_VALUE;
		SET_BIT(TCCR1A, 3);
		SET_BIT(TIMSK, 4);
		#elif TIMER1_OC_PIN == OC1B
		OCR1B = OCR1_DEFAULT_VALUE;
		SET_BIT(TCCR1A, 2);
		SET_BIT(TIMSK, 3);
		#endif

	//Set Default Top Value
	ICR1 = ICR1_DEFAULT_TOP_VALUE;

	#endif

	//Enable GIE
	SET_BIT(SREG, 7);

	//Set prescaler
	TCCR1B |= (TIMER1_PRESCALER & 0x07);
}

void setTopValue(u16 top)
{
	ICR1 = top;
}

void setOCR1A_Value(u16 duty)
{
	OCR1A = duty;
}


/*
////////////TESTING THE DRIVER/////////////////
#include "../INT/INT.h"

void toggleLED()
{
	volatile static u8 ticks = 0;

	if (ticks == 122)
	{
		setTCNT0(238);
		TOGGLE_BIT(PORTA, 0);
		ticks = 0;
	}

	ticks++;

}

int main(void)
{
	SET_BIT(DDRA,0);
	//Starting timer 0 in normal mode
	setCallBackTimer0(toggleLED);
	Timer0_vInit();
	setTCNT0(238);

	while(1);

	return 0;
}
*/
