/*
 * global_object.c
 *
 *  Created on: Nov 1, 2022
 *      Author: ntpt
 */

#include "User/global_object.h"

const uint32_t TRAFFIC_LIGHT_BLINK_PERIOD_MS = 500;
const uint32_t SEG7_UPDATE_PERIOD_MS = 100;

volatile Software_timer_t timer_update_7seg =
{ 0, TIMER_FLAG_RESET, };
volatile Software_timer_t timer_traffic_light =
{ 0, TIMER_FLAG_RESET, };

volatile Button_t button_mode_select =
{
	.FILTER_DELAY_COUNT_MAX = 3,
	.HOLD_STATE_DELAY_COUNT_MAX = 100,
	.HOLD_STATE_ACTIVATE_COUNT_MAX = 50,
	.READING_WHEN_PRESSED = GPIO_PIN_RESET,
	.PIN = BUTTON_MODE_SELECT_Pin,
	.PORT = BUTTON_MODE_SELECT_GPIO_Port,
};
volatile Button_t button_mode_set =
{
	.FILTER_DELAY_COUNT_MAX = 3,
	.HOLD_STATE_DELAY_COUNT_MAX = 100,
	.HOLD_STATE_ACTIVATE_COUNT_MAX = 50,
	.READING_WHEN_PRESSED = GPIO_PIN_RESET,
	.PIN = BUTTON_MODE_SET_Pin,
	.PORT = BUTTON_MODE_SET_GPIO_Port,
};
volatile Button_t button_time_change =
{
	.FILTER_DELAY_COUNT_MAX = 3,
	.HOLD_STATE_DELAY_COUNT_MAX = 100,
	.HOLD_STATE_ACTIVATE_COUNT_MAX = 50,
	.READING_WHEN_PRESSED = GPIO_PIN_RESET,
	.PIN = BUTTON_TIME_CHANGE_Pin,
	.PORT = BUTTON_TIME_CHANGE_GPIO_Port,
};

Two_digit_7seg_t two_digit_7seg_0 =
{
	.CONTROL_PIN = { CONTROL_7SEG_0_0_Pin, CONTROL_7SEG_0_1_Pin },
	.CONTROL_PORT = { CONTROL_7SEG_0_0_GPIO_Port, CONTROL_7SEG_0_1_GPIO_Port },
};
Two_digit_7seg_t two_digit_7seg_1 =
{
	.CONTROL_PIN = { CONTROL_7SEG_1_0_Pin, CONTROL_7SEG_1_1_Pin },
	.CONTROL_PORT = { CONTROL_7SEG_1_0_GPIO_Port, CONTROL_7SEG_1_1_GPIO_Port },
};

Traffic_light_t traffic_light_0 =
{
	.TRAFFIC_LIGHT_PIN =
	{ TRAFFIC_LIGHT_0_RED_Pin, TRAFFIC_LIGHT_0_YELLOW_Pin, TRAFFIC_LIGHT_0_GREEN_Pin },
	.TRAFFIC_LIGHT_PORT =
	{ TRAFFIC_LIGHT_0_RED_GPIO_Port, TRAFFIC_LIGHT_0_YELLOW_GPIO_Port, TRAFFIC_LIGHT_0_GREEN_GPIO_Port },
};
Traffic_light_t traffic_light_1 =
{
	.TRAFFIC_LIGHT_PIN =
	{ TRAFFIC_LIGHT_1_RED_Pin, TRAFFIC_LIGHT_1_YELLOW_Pin, TRAFFIC_LIGHT_1_GREEN_Pin },
	.TRAFFIC_LIGHT_PORT =
	{ TRAFFIC_LIGHT_1_RED_GPIO_Port, TRAFFIC_LIGHT_1_YELLOW_GPIO_Port, TRAFFIC_LIGHT_1_GREEN_GPIO_Port },
};
uint8_t traffic_light_7seg_current = 0;

FSM_t fsm_traffic_light_system =
{ .current_state = STATE_RESET, };

uint8_t traffic_light_duration[TRAFFIC_LIGHT_COLOR_NUMBER] =
{
	2, // red
	2, // yellow
	2, // green
};

Traffic_light_color_t traffic_light_0_current_color = TRAFFIC_LIGHT_COLOR_RED;
Traffic_light_color_t traffic_light_1_current_color = TRAFFIC_LIGHT_COLOR_GREEN;

uint8_t traffic_light_0_time_left = 0;
uint8_t traffic_light_1_time_left = 0;
