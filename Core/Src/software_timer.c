/*
 * software_timer.c
 *
 *  Created on: Oct 24, 2022
 *      Author: ntpt
 */

#include "software_timer.h"

// since timer will be update every tick duration, it can only register
// event with the smallest time scale of tick duration (in this case TIMER_TICK_DURATION_MS)
const int TIMER_TICK_DURATION_MS = 10;

void software_timer_set_duration_ms(Software_timer_t *tm, uint32_t ms)
{
    tm->timer_counter = (ms / TIMER_TICK_DURATION_MS) - 1;
    tm->timer_flag = TIMER_FLAG_RESET;
}

void software_timer_update_after_tick(Software_timer_t *tm)
{
    if (tm->timer_counter > 0)
    {
        tm->timer_counter--;
    }
    else
    {
        tm->timer_flag = TIMER_FLAG_SET;
    }
}

uint8_t software_timer_is_set(Software_timer_t *tm)
{
    return (tm->timer_flag == TIMER_FLAG_SET);
}
