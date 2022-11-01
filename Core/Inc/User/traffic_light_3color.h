/*
 * traffic_light_3color.h
 *
 *  Created on: Oct 29, 2022
 *      Author: ntpt
 */

#ifndef INC_TRAFFIC_LIGHT_3COLOR_H_
#define INC_TRAFFIC_LIGHT_3COLOR_H_

#include "main.h"

typedef enum
{
	TRAFFIC_LIGHT_COLOR_RED = 0,
	TRAFFIC_LIGHT_COLOR_YELLOW = 1,
	TRAFFIC_LIGHT_COLOR_GREEN = 2,
	TRAFFIC_LIGHT_COLOR_NUMBER,
} Traffic_light_color_t;

typedef enum
{
	TRAFFIC_LIGHT_COLOR_OFF_STATE = GPIO_PIN_SET,
	TRAFFIC_LIGHT_COLOR_ON_STATE = GPIO_PIN_RESET,
} Traffic_light_color_state_t;

/* NOTE:
 * We create a traffic light type, which will store the associated pin and port to
 * control each color (assuming that there is only TRAFFIC_LIGHT_COLOR_NUMBER color)
 * is_set store the current state of each traffic light
 */
typedef struct
{
	const uint16_t TRAFFIC_LIGHT_PIN[TRAFFIC_LIGHT_COLOR_NUMBER];
	GPIO_TypeDef *const TRAFFIC_LIGHT_PORT[TRAFFIC_LIGHT_COLOR_NUMBER];

	Traffic_light_color_state_t current_state[TRAFFIC_LIGHT_COLOR_NUMBER];
} Traffic_light_t;

// change state of individual color
void traffic_light_change_color(Traffic_light_t *tl,
		Traffic_light_color_t color, Traffic_light_color_state_t state);
// toggle state of individual color
void traffic_light_toggle_color(Traffic_light_t *tl,
		Traffic_light_color_t color);
// turn on only one color
void traffic_light_turn_on_one_color(Traffic_light_t *tl,
		Traffic_light_color_t color);
// get next color from current color
Traffic_light_color_t traffic_light_next_color_from_current(
		Traffic_light_color_t current_color);

#endif /* INC_TRAFFIC_LIGHT_3COLOR_H_ */
