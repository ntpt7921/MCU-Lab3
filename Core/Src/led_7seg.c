/*
 * led_7seg.c
 *
 *  Created on: Oct 26, 2022
 *      Author: ntpt
 */

#include "led_7seg.h"

const uint16_t SEG7_PATTERN_0 = SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin | SEG4_Pin | SEG5_Pin;
const uint16_t SEG7_PATTERN_1 = SEG1_Pin | SEG2_Pin;
const uint16_t SEG7_PATTERN_2 = SEG0_Pin | SEG1_Pin | SEG3_Pin | SEG4_Pin | SEG6_Pin;
const uint16_t SEG7_PATTERN_3 = SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin | SEG6_Pin;
const uint16_t SEG7_PATTERN_4 = SEG1_Pin | SEG2_Pin | SEG5_Pin | SEG6_Pin;
const uint16_t SEG7_PATTERN_5 = SEG0_Pin | SEG2_Pin | SEG3_Pin | SEG5_Pin | SEG6_Pin;
const uint16_t SEG7_PATTERN_6 = SEG0_Pin | SEG2_Pin | SEG3_Pin | SEG4_Pin | SEG5_Pin | SEG6_Pin;
const uint16_t SEG7_PATTERN_7 = SEG0_Pin | SEG1_Pin | SEG2_Pin;
const uint16_t SEG7_PATTERN_8 = SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin | SEG4_Pin | SEG5_Pin | SEG6_Pin;
const uint16_t SEG7_PATTERN_9 = SEG0_Pin | SEG1_Pin | SEG2_Pin | SEG3_Pin | SEG5_Pin | SEG6_Pin;

GPIO_TypeDef * const COMMON_SEG7_PATTERN_PORT = SEG0_GPIO_Port;

const uint16_t SEG7_PATTERN_LIST[] = {
    SEG7_PATTERN_0, SEG7_PATTERN_1, SEG7_PATTERN_2, SEG7_PATTERN_3,
    SEG7_PATTERN_4, SEG7_PATTERN_5, SEG7_PATTERN_6, SEG7_PATTERN_7,
    SEG7_PATTERN_8, SEG7_PATTERN_9,
};


void two_digit_7seg_update_digit_value(Two_digit_7seg *display, uint8_t digit, uint8_t value)
{
    display->digit_value[digit] = value;
}

void two_digit_7seg_display_digit(Two_digit_7seg *display, uint8_t digit)
{
    // we assume digit can only be 0 or 1
    uint8_t other_7seg_control_pin = display->CONTROL_PIN[!digit];

    HAL_GPIO_WritePin(display->CONTROL_PORT, display->CONTROL_PIN[digit], SET);
    HAL_GPIO_WritePin(display->CONTROL_PORT, other_7seg_control_pin, SET);
}

void led_7seg_change_pattern(uint8_t num)
{
    uint16_t set_pattern = SEG7_PATTERN_LIST[num];
    uint16_t reset_patern = ~set_pattern;
    uint32_t set_reset_pattern = ((uint32_t) reset_patern << 16) | ((uint32_t) set_pattern);

    COMMON_SEG7_PATTERN_PORT->BSRR = set_reset_pattern;
}
