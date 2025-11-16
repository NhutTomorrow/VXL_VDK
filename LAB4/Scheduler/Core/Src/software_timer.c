/*
 * timer.c
 *
 *  Created on: Sep 18, 2025
 *      Author: ASUS
 */
#include <software_timer.h>

#define MAX_TIMER 10
#define TIME_CYCLE 1
struct TimerStruct timer[MAX_TIMER];


void setTimer(int index, int duration){
		timer[index].counter = duration / TIME_CYCLE;
		timer[index].flag = 0;
}
void timer_run(){
	for(int i = 0; i < MAX_TIMER; ++i){
		if(timer[i].counter > 0){
			timer[i].counter --;
			if(timer[i].counter <= 0 ){
				timer[i].flag = 1;
			}
		}
	}
}
int isFlag(int idx){
	if(timer[idx].flag){
		return 1;
	}
	return 0;
}
void timer_Init(){
	HAL_TIM_Base_Start_IT(&htim2);
}
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//  if (htim -> Instance == TIM2)
//  {
//
//    timer_run();
//
//  }
//}
