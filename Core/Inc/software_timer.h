/*
 * software_timer.h
 *
 *  Created on: Oct 24, 2022
 *      Author: ntpt
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "main.h"

typedef enum
{
    TIMER_FLAG_RESET = RESET,
    TIMER_FLAG_SET = SET,
} Timer_flag_state_t;

extern const int TIMER_TICK_DURATION_MS;

typedef struct
{
    uint32_t timer_counter;
    Timer_flag_state_t timer_flag;
} Software_timer_t;

void software_timer_set_duration_ms(Software_timer_t *tm, uint32_t ms);
void software_timer_update_after_tick(Software_timer_t *tm);
uint8_t software_timer_is_set(Software_timer_t *tm);

#endif /* INC_SOFTWARE_TIMER_H_ */
