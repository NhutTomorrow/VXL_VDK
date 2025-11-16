/*
 * button.h
 *
 *  Created on: Sep 25, 2025
 *      Author: ASUS
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_
#include "main.h"

#define NORMAL_STATE SET
#define PRESSED_STATE RESET
#define NUM_BUTTONS 5
struct ButtonStruct{
	int keyButton[4]; // keyButton[0] is current state, keyButton[3] is previous state
	int isPressed;
	int isLongPressed;
	int timeOutLongPressed;
	GPIO_TypeDef* PORT;
	uint16_t PIN;
};

extern struct ButtonStruct BTN[NUM_BUTTONS];

int isButtonPressed(struct ButtonStruct* button);
int isLongPressed(struct ButtonStruct* button);
void getKeyInput(struct ButtonStruct* button);
void resetButton(struct ButtonStruct* button);
void button_scan_all();
#endif /* INC_BUTTON_H_ */
