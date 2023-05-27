/*
 * App.h
 *
 * Created: 9/16/2022 8:45:16 PM
 *  Author: Mohab Zaghloul
 */ 


#ifndef APP_H_
#define APP_H_

typedef enum{
	NORMAL,
	PEDESTRIAN
}Traffic_mode;

typedef enum{
	RED = 0,
	YELLOW = 1,
	GREEN = 2,
	OFF = 3
}Traffic_light;

typedef struct{
	Traffic_light light;
	Traffic_mode mode;
}Traffic;

void appInit(void);				//Initializer function for all the peripherals
void tickTackNormal(void);			//Callback function for the timer in the normal mode
void switchCarsColors(void);
void carsTrafficHandler(void);	//Controls the traffic light

void changeMode(void);
void tickTack(void);
void setPedColors(void);
void switchColors(void);
void TrafficHandler();

#endif /* APP_H_ */