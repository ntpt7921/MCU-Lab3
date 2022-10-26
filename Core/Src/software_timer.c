/*
 * software_timer.c
 *
 *  Created on: Oct 24, 2022
 *      Author: ntpt
 */

#include "software_timer.h"

int TIMER_CYCLE = TIMER_TICK_DURATION_MS;

int timer0_counter = 0;
int timer0_flag = 0;

int timer1_counter = 0;
int timer1_flag = 0;

int timer2_counter = 0;
int timer2_flag = 0;

int timer3_counter = 0;
int timer3_flag = 0;

int timer4_counter = 0;
int timer4_flag = 0;

void setTimer0(int duration)
{
    timer0_counter = duration / TIMER_CYCLE;
    timer0_flag = RESET;
}
void timer0_run()
{
    if (timer0_counter > 0)
    {
        timer0_counter--;
    }
    else if (timer0_counter <= 0)
    {
        timer0_flag = SET;
    }
}

void setTimer1(int duration)
{
    timer1_counter = duration / TIMER_CYCLE;
    timer1_flag = RESET;
}
void timer1_run()
{
    if (timer1_counter > 0)
    {
        timer1_counter--;
    }
    else if (timer1_counter <= 0)
    {
        timer1_flag = SET;
    }
}

void setTimer2(int duration)
{
    timer2_counter = duration / TIMER_CYCLE;
    timer2_flag = RESET;
}
void timer2_run()
{
    if (timer2_counter > 0)
    {
        timer2_counter--;
    }
    else if (timer2_counter <= 0)
    {
        timer2_flag = SET;
    }
}

void setTimer3(int duration)
{
    timer3_counter = duration / TIMER_CYCLE;
    timer3_flag = RESET;
}
void timer3_run()
{
    if (timer3_counter > 0)
    {
        timer3_counter--;
    }
    else if (timer3_counter <= 0)
    {
        timer3_flag = SET;
    }
}

void setTimer4(int duration)
{
    timer4_counter = duration / TIMER_CYCLE;
    timer4_flag = RESET;
}
void timer4_run()
{
    if (timer4_counter > 0)
    {
        timer4_counter--;
    }
    else if (timer4_counter <= 0)
    {
        timer4_flag = SET;
    }
}
