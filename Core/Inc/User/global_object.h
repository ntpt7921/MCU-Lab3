/*
 * global_object.h
 *
 *  Created on: Nov 1, 2022
 *      Author: ntpt
 */

#ifndef INC_USER_GLOBAL_OBJECT_H_
#define INC_USER_GLOBAL_OBJECT_H_

#include "main.h"
#include "User/button.h"
#include "User/software_timer.h"
#include "User/led_7seg.h"
#include "User/traffic_light_3color.h"
#include "User/fsm.h"

// constant configuration
extern const uint32_t TRAFFIC_LIGHT_BLINK_PERIOD_MS;
extern const uint32_t SEG7_UPDATE_PERIOD_MS;

// Physical device object
extern volatile Software_timer_t timer_update_7seg;
extern volatile Software_timer_t timer_traffic_light;

extern volatile Button_t button_mode_select;
extern volatile Button_t button_mode_set;
extern volatile Button_t button_time_change;

extern Two_digit_7seg_t two_digit_7seg_0; // will be used for showing time
extern Two_digit_7seg_t two_digit_7seg_1; // will be used for showing state

extern Traffic_light_t traffic_light_0;
extern Traffic_light_t traffic_light_1;

// From here onward is the internal traffic light system variable and state machine
extern uint8_t traffic_light_0_current_digit;
extern uint8_t traffic_light_1_current_digit;

extern FSM_t fsm_traffic_light_system;

extern uint8_t traffic_light_duration[TRAFFIC_LIGHT_COLOR_NUMBER];

extern Traffic_light_color_t traffic_light_0_current_color;
extern Traffic_light_color_t traffic_light_1_current_color;

extern uint8_t traffic_light_0_time_left;
extern uint8_t traffic_light_1_time_left;

#endif /* INC_USER_GLOBAL_OBJECT_H_ */
