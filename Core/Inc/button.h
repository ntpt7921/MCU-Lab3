/*
 * button.h
 *
 *  Created on: Oct 26, 2022
 *      Author: ntpt
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

/**
 * NOTE:
 * Each button can have 3 seperate state: released, pressed and hold
 *
 * hold state will be entered after being in pressed state for a certain duration
 *
 * each state is treated as mutually exclusive, meaing that state can not overlap
 * so button in hold state is not considerd to be in pressed state (even if common
 * sense tell you otherwise)
 */
typedef enum
{
    BUTTON_IS_RELEASED,
    BUTTON_IS_PRESSED,
    BUTTON_IS_HOLD
} Button_state_t;


/**
 * NOTE:
 * button read can have two reading value: GPIO_PIN_RESET and GPIO_PIN_SET
 */
typedef GPIO_PinState Button_read_value_t;

/**
 * NOTE:
 * since this code is written to accomodate both type of pressed state
 * (low when pressed, high when pressed), the associated pressed state
 * will be store for each button
 *
 * button will be software debounched by waiting for some N stable
 * continuous read value of the button pin
 */
typedef struct
{
    // variable for configuration of the button
    const uint8_t FILTER_DELAY_COUNT_MAX;
    const uint16_t HOLD_STATE_DELAY_COUNT_MAX;
    const Button_read_value_t READING_WHEN_PRESSED;
    const uint16_t PIN;
    GPIO_TypeDef * const PORT; // const pointer to GPIO_TypeDef


    Button_state_t current_state;

    // varibles for internal state of button
    Button_read_value_t last_reading;
    uint8_t filter_delay_count;
    uint16_t hold_state_delay_count;
} Button_t;

void button_poll_and_update_state(Button_t *bt);
uint8_t button_is_pressed(Button_t *bt);
uint8_t button_is_hold(Button_t *bt);

#endif /* INC_BUTTON_H_ */
