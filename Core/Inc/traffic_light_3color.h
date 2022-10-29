/*
 * traffic_light_3color.h
 *
 *  Created on: Oct 29, 2022
 *      Author: ntpt
 */

#ifndef INC_TRAFFIC_LIGHT_3COLOR_H_
#define INC_TRAFFIC_LIGHT_3COLOR_H_

#include "main.h"

enum Trafic_light_color_t
{
    TRAFFIC_LIGHT_COLOR_RED = 0,
    TRAFFIC_LIGHT_COLOR_YELLOW = 1,
    TRAFFIC_LIGHT_COLOR_GREEN = 2,
    TRAFFIC_LIGHT_COLOR_NUMBER,
};

/* NOTE:
 * We create a traffic light type, which will store the associated pin and port to
 * control each color (assuming that there is only TRAFFIC_LIGHT_COLOR_NUMBER color)
 * is_set store the current state of each traffic light
 */
typedef struct
{
    const uint16_t TRAFFIC_LIGHT_PIN[TRAFFIC_LIGHT_COLOR_NUMBER];
    GPIO_TypeDef * const TRAFFIC_LIGHT_PORT[TRAFFIC_LIGHT_COLOR_NUMBER];

    GPIO_PinState current_state[TRAFFIC_LIGHT_COLOR_NUMBER];
} Traffic_light_t;



void traffic_light_change_color(Traffic_light_t *tl, Trafic_light_color_t color, GPIO_PinState state);
void traffic_light_toggle_color(Traffic_light_t *tl, Trafic_light_color_t color);

#endif /* INC_TRAFFIC_LIGHT_3COLOR_H_ */
