/*
 * button.c
 *
 *  Created on: Oct 26, 2022
 *      Author: ntpt
 */

#include "button.h"

void button_poll_and_update_state(Button_t *bt)
{
    Button_read_value_t current_reading = HAL_GPIO_ReadPin(bt->PORT, bt->PIN);

    // filter input and update to pressed or released state
    if (bt->last_reading == current_reading)
    {
        bt->filter_delay_count++;

        if (bt->filter_delay_count == bt->FILTER_DELAY_COUNT_MAX)
        {
            if (current_reading == bt->READING_WHEN_PRESSED)
            {
                // only update state to pressed if not already in hold state
                if (bt->current_state != BUTTON_IS_HOLD)
                    bt->current_state = BUTTON_IS_PRESSED;
            }
            else
            {
                bt->current_state = BUTTON_IS_RELEASED;
            }
            bt->filter_delay_count = 0;
        }
    }
    else
    {
        bt->filter_delay_count = 0;
    }

    // within pressed state, after a delay has passed, change to hold state
    if (bt->current_state == BUTTON_IS_PRESSED)
    {
        bt->hold_state_delay_count++;

        if (bt->hold_state_delay_count == bt->HOLD_STATE_DELAY_COUNT_MAX)
        {
            bt->current_state = BUTTON_IS_HOLD;
            bt->hold_state_delay_count = 0;
        }
    }

    bt->last_reading = current_reading;
}

uint8_t button_is_pressed(Button_t *bt)
{
    return (bt->current_state == BUTTON_IS_PRESSED);
}

uint8_t button_is_hold(Button_t *bt)
{
    return (bt->current_state == BUTTON_IS_HOLD);
}
