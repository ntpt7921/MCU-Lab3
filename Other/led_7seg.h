/*
 * led_7seg.h
 *
 *  Created on: Oct 26, 2022
 *      Author: ntpt
 */

#ifndef INC_LED_7SEG_H_
#define INC_LED_7SEG_H_

#include "main.h"

/**
 * NOTE:
 * We assume that all the 7 seg led pattern will be controlled from a fix set of pin
 * and that those pin is in the same gpio port
 */
const uint16_t SEG7_PATTERN_0;
const uint16_t SEG7_PATTERN_1;
const uint16_t SEG7_PATTERN_2;
const uint16_t SEG7_PATTERN_3;
const uint16_t SEG7_PATTERN_4;
const uint16_t SEG7_PATTERN_5;
const uint16_t SEG7_PATTERN_6;
const uint16_t SEG7_PATTERN_7;
const uint16_t SEG7_PATTERN_8;
const uint16_t SEG7_PATTERN_9;
// assume all seg pattern line is in the same port
GPIO_TypeDef * const COMMON_SEG7_PATTERN_PORT;
const uint16_t SEG7_PATTERN_LIST[];


/**
 * NOTE:
 * We assume that each 2 digit 7 seg led can be set to display any value from 00 -> 99
 * Each 2 digit 7 seg led will store the required control pin and port
 * It will also have buffer to store value of each digit within the two 7 seg led
 */
typedef struct
{
    const uint16_t CONTROL_PIN[2];
    GPIO_TypeDef * const CONTROL_PORT;

    uint8_t digit_value[2];
} Two_digit_7seg;


void two_digit_7seg_update_digit_value(Two_digit_7seg *display, uint8_t digit, uint8_t value);
void two_digit_7seg_display_digit(Two_digit_7seg *display, uint8_t digit);
void led_7seg_change_pattern(uint8_t num);


#endif /* INC_LED_7SEG_H_ */