/*
 * timer.h
 *
 *  Created on: Sep 18, 2025
 *      Author: ASUS
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "main.h"
#include "tim.h"
struct TimerStruct{
	int counter;
	int flag ;
};

extern struct TimerStruct timer[10];

void setTimer(int index, int duration);
void timer_run();
int isFlag(int idx);
void timer_Init();
#endif /* INC_SOFTWARE_TIMER_H_ */
