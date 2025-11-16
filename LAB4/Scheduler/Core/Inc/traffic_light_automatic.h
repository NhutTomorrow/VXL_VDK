/*
 * traffic_light.h
 *
 *  Created on: Sep 26, 2025
 *      Author: ASUS
 */

#ifndef INC_TRAFFIC_LIGHT_AUTOMATIC_H_
#define INC_TRAFFIC_LIGHT_AUTOMATIC_H_

#include <global.h>
#include "button.h"



void traffic_light_automatic();


void init_red0_gre1();
void init_red0_yel1();
void init_gre0_red1();
void init_yel0_red1();

void turn_off_all_led();

void traffic_red0_gre1();
void traffic_red0_yel1();
void traffic_gre0_red1();
void traffic_yel0_red1();




#endif /* INC_TRAFFIC_LIGHT_AUTOMATIC_H_ */
