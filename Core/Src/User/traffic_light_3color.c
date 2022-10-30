/*
 * traffic_light_3color.c
 *
 *  Created on: Oct 29, 2022
 *      Author: ntpt
 */

#include "User/traffic_light_3color.h"


void traffic_light_change_color(Traffic_light_t *tl, Traffic_light_color_t color, Traffic_light_color_state_t state)
{
    HAL_GPIO_WritePin(tl->TRAFFIC_LIGHT_PORT[color], tl->TRAFFIC_LIGHT_PIN[color], state);
    tl->current_state[color] = state;
}

void traffic_light_toggle_color(Traffic_light_t *tl, Traffic_light_color_t color)
{
    HAL_GPIO_TogglePin(tl->TRAFFIC_LIGHT_PORT[color], tl->TRAFFIC_LIGHT_PIN[color]);

    // invert the current_state of the color
    tl->current_state[color] = (tl->current_state[color] == TRAFFIC_LIGHT_COLOR_OFF_STATE) ?
    		TRAFFIC_LIGHT_COLOR_ON_STATE : TRAFFIC_LIGHT_COLOR_OFF_STATE;
}


void traffic_light_turn_on_one_color(Traffic_light_t *tl, Traffic_light_color_t color)
{
	// turn off all color
	for (Traffic_light_color_t i = 0; i < TRAFFIC_LIGHT_COLOR_NUMBER; i++)
	{
		traffic_light_change_color(tl, i, TRAFFIC_LIGHT_COLOR_OFF_STATE);
	}

	// turn on only one color afterward
	traffic_light_change_color(tl, color, TRAFFIC_LIGHT_COLOR_ON_STATE);
}
