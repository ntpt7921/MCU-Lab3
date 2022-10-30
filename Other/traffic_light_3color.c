/*
 * traffic_light_3color.c
 *
 *  Created on: Oct 29, 2022
 *      Author: ntpt
 */

#include "traffic_light_3color.h"

void traffic_light_change_color(Traffic_light_t *tl, Trafic_light_color_t color, GPIO_PinState state)
{
    HAL_GPIO_WritePin(tl->TRAFFIC_LIGHT_PORT[color], tl->TRAFFIC_LIGHT_PIN[color], state);
    tl->current_state[color] = state;
}

void traffic_light_toggle_color(Traffic_light_t *tl, Trafic_light_color_t color)
{
    HAL_GPIO_TogglePin(tl->TRAFFIC_LIGHT_PORT[color], tl->TRAFFIC_LIGHT_PIN[color]);

    // invert the current_state of the color
    tl->current_state[color] = !(tl->current_state[color]);
}


