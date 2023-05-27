/*
 * TIMER_CFG.h
 *
 *  Created on: Sep 6, 2022
 *      Author: loppy
 */

#ifndef MCAL_TIMER_TIMER_CFG_H_
#define MCAL_TIMER_TIMER_CFG_H_

/************** TIMER MODES **************/

#define TIMER_OVF_MODE			0
#define TIMER_PHASE_PWM_MODE	1
#define TIMER_CTC_MODE 			2
#define TIMER_FAST_PWM_MODE		3
//#define TIMER_FAST_PWM_MODE_ICR1 14
#define TIMER1_ICU_MODE			20

/************** COMPARE OUTPUT MODE - NON PWM **************/
#define COM_NON_PWM_DISCONNECT_OC		0
#define COM_NON_PWM_TOGGLE_OC			1
#define COM_NON_PWM_CLEAR_OC			2
#define COM_NON_PWM_SET_OC				3

/************** COMPARE OUTPUT MODE - PWM **************/
#define COM_PWM_DISCONNECT_OC		0
#define COM_PWM_RESERVED			1
#define COM_PWM_CLEAR_OC			2
#define COM_PWM_SET_OC				3


/************** TIMER1 WAVEFORM GENERATION MODES **************/
#define T1_MODE_NORMAL					0		//Supported
#define T1_MODE_PHASE_PWM_8_BIT			1
#define T1_MODE_PHASE_PWM_9_BIT			2
#define T1_MODE_PHASE_PWM_10_BIT		3
#define T1_MODE_CTC_TOP_OCR1A			4
#define T1_MODE_FAST_PWM_8_BIT			5
#define T1_MODE_FAST_PWM_9_BIT			6
#define T1_MODE_FAST_PWM_10_BIT			7
#define T1_MODE_FREQ_PWM_TOP_ICR1		8
#define T1_MODE_FREQ_PWM_TOP_OCCR1A		9
#define T1_MODE_PHASE_PWM_TOP_ICR1		10
#define T1_MODE_PHASE_PWM_TOP_OCR1A		11
#define T1_MODE_CTC_TOP_ICR1			12		//Supported
#define T1_MODE_RESERVED				13
#define T1_MODE_FAST_PWM_TOP_ICR1		14		//Supported
#define T1_MODE_FAST_PWM_TOP_OCR1A		15


/************** TIMER1 OUTPUT COMPARE PIN **************/
#define OC1A	0
#define OC1B	1

#endif /* MCAL_TIMER_TIMER_CFG_H_ */
