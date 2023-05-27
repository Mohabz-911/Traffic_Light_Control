/*
 * DIO.h
 *
 *  Created on: Aug 22, 2022
 *      Author: loppy
 */

#ifndef DIO_H
#define DIO_H

#include "..\..\UTILS\STD_TYPES.h"

typedef enum{
	DIO_OK,
	DIO_ERROR
}DIO_STATE;

// This function shall set the direction of any pin
DIO_STATE setPinDir(u8 PORT_NAME, u8 PIN_NUMBER, u8 PIN_DIR);

// This function shall set the value of any pin
DIO_STATE setPinValue(u8 PORT_NAME, u8 PIN_NUMBER, u8 PIN_VALUE);

// This function shall read the value of any pin
DIO_STATE readPinValue(u8 PORT_NAME, u8 PIN_NUMBER, u8 * rt_value);

// This function shall set the direction of any port
DIO_STATE setPortDir(u8 PORT_NAME, u8 PORT_DIR);

// This function shall set the value of any port
DIO_STATE setPortValue(u8 PORT_NAME, u8 PORT_VALUE);

// This function shall read the value of any port
DIO_STATE readPortValue(u8 PORT_NAME, u8 * rt_value);

#endif
