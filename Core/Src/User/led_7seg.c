/*
 * led_7seg.c
 *
 *  Created on: Oct 26, 2022
 *      Author: ntpt
 */

#include "User/led_7seg.h"

const uint16_t SEG7_PATTERN_0 = SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin
		| SEG4_Pin | SEG5_Pin;
const uint16_t SEG7_PATTERN_1 = SEG1_Pin | SEG2_Pin;
const uint16_t SEG7_PATTERN_2 = SEG0_Pin | SEG1_Pin | SEG3_Pin | SEG4_Pin
		| SEG6_Pin;
const uint16_t SEG7_PATTERN_3 = SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin
		| SEG6_Pin;
const uint16_t SEG7_PATTERN_4 = SEG1_Pin | SEG2_Pin | SEG5_Pin | SEG6_Pin;
const uint16_t SEG7_PATTERN_5 = SEG0_Pin | SEG2_Pin | SEG3_Pin | SEG5_Pin
		| SEG6_Pin;
const uint16_t SEG7_PATTERN_6 = SEG0_Pin | SEG2_Pin | SEG3_Pin | SEG4_Pin
		| SEG5_Pin | SEG6_Pin;
const uint16_t SEG7_PATTERN_7 = SEG0_Pin | SEG1_Pin | SEG2_Pin;
const uint16_t SEG7_PATTERN_8 = SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin
		| SEG4_Pin | SEG5_Pin | SEG6_Pin;
const uint16_t SEG7_PATTERN_9 = SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin
		| SEG5_Pin | SEG6_Pin;

GPIO_TypeDef *const COMMON_SEG7_PATTERN_PORT = SEG0_GPIO_Port;

const uint16_t SEG7_PATTERN_LIST[] =
{ SEG7_PATTERN_0, SEG7_PATTERN_1, SEG7_PATTERN_2, SEG7_PATTERN_3,
		SEG7_PATTERN_4, SEG7_PATTERN_5, SEG7_PATTERN_6, SEG7_PATTERN_7,
		SEG7_PATTERN_8, SEG7_PATTERN_9, };

void two_digit_7seg_update_digit_value(Two_digit_7seg_t *display, uint8_t digit,
		uint8_t value)
{
	display->digit_value[digit] = value;
}

void two_digit_7seg_update_value(Two_digit_7seg_t *display, uint8_t value)
{
	// assume that value inputed is from 00 -> 99
	if (value > 99)
	{
		return;
	}

	two_digit_7seg_update_digit_value(display, 0, value % 10);
	two_digit_7seg_update_digit_value(display, 1, value / 10);
}

void two_digit_7seg_turn_off_all_digit(Two_digit_7seg_t *display)
{
	for (uint8_t i = 0; i < 2; i++)
	{
		HAL_GPIO_WritePin(display->CONTROL_PORT[i], display->CONTROL_PIN[i],
				GPIO_PIN_SET);
	}
}

void two_digit_7seg_display_digit(Two_digit_7seg_t *display, uint8_t digit)
{
	// we assume digit can only be 0 or 1
	uint8_t other_digit = (digit == 0) ? 1 : 0;
	uint16_t other_7seg_control_pin = display->CONTROL_PIN[other_digit];
	GPIO_TypeDef *other_7seg_control_port = display->CONTROL_PORT[other_digit];

	// disable the other digit control line
	HAL_GPIO_WritePin(other_7seg_control_port, other_7seg_control_pin,
			GPIO_PIN_SET);

	// set new pattern and enable digit control line
	led_7seg_change_pattern(display->digit_value[digit]);
	HAL_GPIO_WritePin(display->CONTROL_PORT[digit], display->CONTROL_PIN[digit],
			GPIO_PIN_RESET);
}

void led_7seg_change_pattern(uint8_t num)
{
	// SEG7_PATTERN_8 will be used as a mask since it have all pin or'ed together
	gpio_parallel_write(COMMON_SEG7_PATTERN_PORT, SEG7_PATTERN_8,
			~SEG7_PATTERN_LIST[num]);
}
