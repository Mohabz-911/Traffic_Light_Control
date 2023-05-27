#define __AVR_ATmega32A__
#include <avr/io.h>
#include <avr/delay.h>
#include "DIO.h"
#include "DIO_CFG.h"
#include "../../UTILS/BIT_MATH.h"
#include "../../UTILS/STD_TYPES.h"


DIO_STATE setPinDir(u8 PORT_NAME, u8 PIN_NUMBER, u8 PIN_DIR){
	if(PIN_DIR == OUTPUT){
		switch(PORT_NAME){
			case GROUP_A:
			SET_BIT(DDRA, PIN_NUMBER);
			break;
			case GROUP_B:
			SET_BIT(DDRB, PIN_NUMBER);
			break;
			case GROUP_C:
			SET_BIT(DDRC, PIN_NUMBER);
			break;
			case GROUP_D:
			SET_BIT(DDRD, PIN_NUMBER);
			break;
			default:
			return DIO_ERROR;
		}
	}
	else if(PIN_DIR == INPUT)
	{
		switch(PORT_NAME){
			case GROUP_A:
			CLEAR_BIT(DDRA, PIN_NUMBER);
			break;
			case GROUP_B:
			CLEAR_BIT(DDRB, PIN_NUMBER);
			break;
			case GROUP_C:
			CLEAR_BIT(DDRC, PIN_NUMBER);
			break;
			case GROUP_D:
			CLEAR_BIT(DDRD, PIN_NUMBER);
			break;
			default:
			return DIO_ERROR;
		}
	}
	else
		return DIO_ERROR;
		
	return DIO_OK;
}

DIO_STATE setPinValue(u8 PORT_NAME, u8 PIN_NUMBER, u8 PIN_VALUE){
	if(PIN_VALUE == HIGH){
		switch(PORT_NAME){
			case GROUP_A:
			SET_BIT(PORTA, PIN_NUMBER);
			break;
			case GROUP_B:
			SET_BIT(PORTB, PIN_NUMBER);
			break;
			case GROUP_C:
			SET_BIT(PORTC, PIN_NUMBER);
			break;
			case GROUP_D:
			SET_BIT(PORTD, PIN_NUMBER);
			break;
			default:
			return DIO_ERROR;
		}
	}
	else if(PIN_VALUE == LOW)
	{
		switch(PORT_NAME){
			case GROUP_A:
			CLEAR_BIT(PORTA, PIN_NUMBER);
			break;
			case GROUP_B:
			CLEAR_BIT(PORTB, PIN_NUMBER);
			break;
			case GROUP_C:
			CLEAR_BIT(PORTC, PIN_NUMBER);
			break;
			case GROUP_D:
			CLEAR_BIT(PORTD, PIN_NUMBER);
			break;
			default:
			return DIO_ERROR;
		}
	}
	else
		return DIO_ERROR;
	
	return DIO_OK;
}

DIO_STATE readPinValue(u8 PORT_NAME, u8 PIN_NUMBER, u8 * rt_value){
	u8 value;
	switch(PORT_NAME){
			case GROUP_A:
			value = READ_BIT(PINA, PIN_NUMBER);
			break;
			case GROUP_B:
			value = READ_BIT(PINB, PIN_NUMBER);
			break;
			case GROUP_C:
			value = READ_BIT(PINC, PIN_NUMBER);
			break;
			case GROUP_D:
			value = READ_BIT(PIND, PIN_NUMBER);
			break;
			default:
			return DIO_ERROR;
		}
	*rt_value = value;
	return DIO_OK;
}

DIO_STATE setPortDir(u8 PORT_NAME, u8 PORT_DIR)
{
	if (PORT_DIR != OUTPUT && PORT_DIR != INPUT)
		return DIO_ERROR;

	switch(PORT_NAME){
		case GROUP_A:
		DDRA = (PORT_DIR)? 0xFF:0;
		break;
		case GROUP_B:
		DDRB = (PORT_DIR)? 0xFF:0;
		break;
		case GROUP_C:
		DDRC = (PORT_DIR)? 0xFF:0;
		break;
		case GROUP_D:
		DDRD = (PORT_DIR)? 0xFF:0;
		break;
		default:
		return DIO_ERROR;
	}
	
	return DIO_OK;
}

DIO_STATE setPortValue(u8 PORT_NAME, u8 PORT_VALUE){
	switch(PORT_NAME){
		case GROUP_A:
		PORTA = (PORT_VALUE)? 0xFF:0;
		break;
		case GROUP_B:
		PORTB = (PORT_VALUE)? 0xFF:0;
		break;
		case GROUP_C:
		PORTC = (PORT_VALUE)? 0xFF:0;
		break;
		case GROUP_D:
		PORTD = (PORT_VALUE)? 0xFF:0;
		break;
		default:
		return DIO_ERROR;
	}
	
	return DIO_OK;
}

DIO_STATE readPortValue(u8 PORT_NAME, u8 * rt_value){
	u8 value;
	switch(PORT_NAME)
	{
		case GROUP_A:
		value = READ_PORT(PINA);
		break;
		case GROUP_B:
		value = READ_PORT(PINB);
		break;
		case GROUP_C:
		value = READ_PORT(PINC);
		break;
		case GROUP_D:
		value = READ_PORT(PIND);
		break;
		default:
		return DIO_ERROR;
	}
	
	*rt_value = value;
	return DIO_OK;
}


////////////////TESTING THE DRIVER///////////////////
/*
void blinkLED_A(u8 pin, u8 times)
{
	u8 x;
	for(x = 0; x < times; x++)
	{
		SET_BIT(PORTA, pin);
		_delay_ms(300);
		CLEAR_BIT(PORTA, pin);
		_delay_ms(300);
	}
}


void main(void)
{
	DIO_STATE responsePorts[5];
	DIO_STATE responsePins[5][8];
	uint8_t i, j;


	 // 1- Tries to set all ports as ouptuts using pin functions
	 // 2- Test their output by turning all ports on using pin functions
	 // 3- Repeat 1 and 2 using port functions
	 // 4- Repeat 1, 2 and 3 but testing input instead of output

	 // - Each step has false cases that is indicated by blinking LEDs


	//Setting pins of Port-A as output
	responsePins[0][0] = setPinDir(GROUP_A, 0, OUTPUT);
	responsePins[0][1] = setPinDir(GROUP_A, 1, OUTPUT);
	responsePins[0][2] = setPinDir(GROUP_A, 2, OUTPUT);
	responsePins[0][3] = setPinDir(GROUP_A, 3, OUTPUT);
	responsePins[0][4] = setPinDir(GROUP_A, 4, OUTPUT);
	responsePins[0][5] = setPinDir(GROUP_A, 5, OUTPUT);
	responsePins[0][6] = setPinDir(GROUP_A, 6, OUTPUT);
	responsePins[0][7] = setPinDir(GROUP_A, 7, OUTPUT);
	
	//Setting pins of Port-B as output
	responsePins[1][0] = setPinDir(GROUP_B, 0, OUTPUT);
	responsePins[1][1] = setPinDir(GROUP_B, 1, OUTPUT);
	responsePins[1][2] = setPinDir(GROUP_B, 2, OUTPUT);
	responsePins[1][3] = setPinDir(GROUP_B, 3, OUTPUT);
	responsePins[1][4] = setPinDir(GROUP_B, 4, OUTPUT);
	responsePins[1][5] = setPinDir(GROUP_B, 5, OUTPUT);
	responsePins[1][6] = setPinDir(GROUP_B, 6, OUTPUT);
	responsePins[1][7] = setPinDir(GROUP_B, 7, OUTPUT);
	
	//Setting pins of Port-C as output
	responsePins[2][0] = setPinDir(GROUP_C, 0, OUTPUT);
	responsePins[2][1] = setPinDir(GROUP_C, 1, OUTPUT);
	responsePins[2][2] = setPinDir(GROUP_C, 2, OUTPUT);
	responsePins[2][3] = setPinDir(GROUP_C, 3, OUTPUT);
	responsePins[2][4] = setPinDir(GROUP_C, 4, OUTPUT);
	responsePins[2][5] = setPinDir(GROUP_C, 5, OUTPUT);
	responsePins[2][6] = setPinDir(GROUP_C, 6, OUTPUT);
	responsePins[2][7] = setPinDir(GROUP_C, 7, OUTPUT);
	
	//Setting pins of Port-D as output
	responsePins[3][0] = setPinDir(GROUP_D, 0, OUTPUT);
	responsePins[3][1] = setPinDir(GROUP_D, 1, OUTPUT);
	responsePins[3][2] = setPinDir(GROUP_D, 2, OUTPUT);
	responsePins[3][3] = setPinDir(GROUP_D, 3, OUTPUT);
	responsePins[3][4] = setPinDir(GROUP_D, 4, OUTPUT);
	responsePins[3][5] = setPinDir(GROUP_D, 5, OUTPUT);
	responsePins[3][6] = setPinDir(GROUP_D, 6, OUTPUT);
	responsePins[3][7] = setPinDir(GROUP_D, 7, OUTPUT);
	
	//False cases
	responsePins[4][0] = setPinDir(4, 0, OUTPUT);
	responsePins[4][1] = setPinDir(4, 1, OUTPUT);
	responsePins[4][2] = setPinDir(4, 2, OUTPUT);
	responsePins[4][3] = setPinDir(4, 3, OUTPUT);
	responsePins[4][4] = setPinDir(0, 4, 3);
	responsePins[4][5] = setPinDir(1, 5, 3);
	responsePins[4][6] = setPinDir(2, 6, 3);
	responsePins[4][7] = setPinDir(3, 7, 3);
	

	for(i = 0; i < 5; i++)
		for (j = 0; j < 8; j++)
		{
			if (responsePins[i][j] == DIO_OK)
				setPinValue(i, j, HIGH);
			else
				blinkLED_A(j, 3);
		}

	//True cases
	responsePorts[0] = setPortDir(GROUP_A, OUTPUT);
	responsePorts[1] = setPortDir(GROUP_B, OUTPUT);
	responsePorts[2] = setPortDir(GROUP_C, OUTPUT);
	responsePorts[3] = setPortDir(GROUP_D, OUTPUT);

	//False Case
	responsePorts[4] = setPortDir(7, OUTPUT);

	for (j = 0; j < 5; j++)
	{
		if (responsePorts[j] == DIO_OK)
			setPortValue(j, HIGH);
		else
			blinkLED_A(j, 2);
	}


	/////////////INPUT/////////////////

	//Setting pins of Port-A as INPUT
	responsePins[0][0] = setPinDir(GROUP_A, 0, INPUT);
	responsePins[0][1] = setPinDir(GROUP_A, 1, INPUT);
	responsePins[0][2] = setPinDir(GROUP_A, 2, INPUT);
	responsePins[0][3] = setPinDir(GROUP_A, 3, INPUT);
	responsePins[0][4] = setPinDir(GROUP_A, 4, INPUT);
	responsePins[0][5] = setPinDir(GROUP_A, 5, INPUT);
	responsePins[0][6] = setPinDir(GROUP_A, 6, INPUT);
	responsePins[0][7] = setPinDir(GROUP_A, 7, INPUT);

	//Setting pins of Port-B as INPUT
	responsePins[1][0] = setPinDir(GROUP_B, 0, INPUT);
	responsePins[1][1] = setPinDir(GROUP_B, 1, INPUT);
	responsePins[1][2] = setPinDir(GROUP_B, 2, INPUT);
	responsePins[1][3] = setPinDir(GROUP_B, 3, INPUT);
	responsePins[1][4] = setPinDir(GROUP_B, 4, INPUT);
	responsePins[1][5] = setPinDir(GROUP_B, 5, INPUT);
	responsePins[1][6] = setPinDir(GROUP_B, 6, INPUT);
	responsePins[1][7] = setPinDir(GROUP_B, 7, INPUT);

	//Setting pins of Port-C as INPUT
	responsePins[2][0] = setPinDir(GROUP_C, 0, INPUT);
	responsePins[2][1] = setPinDir(GROUP_C, 1, INPUT);
	responsePins[2][2] = setPinDir(GROUP_C, 2, INPUT);
	responsePins[2][3] = setPinDir(GROUP_C, 3, INPUT);
	responsePins[2][4] = setPinDir(GROUP_C, 4, INPUT);
	responsePins[2][5] = setPinDir(GROUP_C, 5, INPUT);
	responsePins[2][6] = setPinDir(GROUP_C, 6, INPUT);
	responsePins[2][7] = setPinDir(GROUP_C, 7, INPUT);

	//Setting pins of Port-D as INPUT
	responsePins[3][0] = setPinDir(GROUP_D, 0, INPUT);
	responsePins[3][1] = setPinDir(GROUP_D, 1, INPUT);
	responsePins[3][2] = setPinDir(GROUP_D, 2, INPUT);
	responsePins[3][3] = setPinDir(GROUP_D, 3, INPUT);
	responsePins[3][4] = setPinDir(GROUP_D, 4, INPUT);
	responsePins[3][5] = setPinDir(GROUP_D, 5, INPUT);
	responsePins[3][6] = setPinDir(GROUP_D, 6, INPUT);
	responsePins[3][7] = setPinDir(GROUP_D, 7, INPUT);

	for(i = 0; i < 5; i++)
		for (j = 0; j < 8; j++)
			if (responsePins[i][j] == DIO_OK)
			{
				setPinDir(i, j, OUTPUT);
				setPinValue(i, j, LOW);
			}

	_delay_ms(5000);
	//True cases
	responsePorts[0] = setPortDir(GROUP_A, INPUT);
	responsePorts[1] = setPortDir(GROUP_B, INPUT);
	responsePorts[2] = setPortDir(GROUP_C, INPUT);
	responsePorts[3] = setPortDir(GROUP_D, INPUT);

	for (j = 0; j < 4; j++)
		if (responsePorts[j] == DIO_OK)
			{
				setPortDir(j, OUTPUT);
				setPortValue(j, HIGH);
			}

}
*/
