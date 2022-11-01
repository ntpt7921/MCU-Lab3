/*
 * fsm_traffic_light.c
 *
 *  Created on: Nov 1, 2022
 *      Author: ntpt
 */

#include "User/fsm_traffic_light.h"
#include "User/global_object.h"

FSM_state_t FSM_traffic_light_get_next_state(FSM_state_t current_state)
{
	FSM_state_t next_state = current_state;

	switch (current_state)
	{
	case STATE_NORMAL:
		if (button_is_hold_activated(&button_mode_select)
				|| button_is_pressed_activated(&button_mode_select))
		{
			button_clear_activation(&button_mode_select);
			next_state = STATE_UPDATE_RED;
		}
		break;
	case STATE_UPDATE_RED:
		if (button_is_hold_activated(&button_mode_select)
				|| button_is_pressed_activated(&button_mode_select))
		{
			button_clear_activation(&button_mode_select);
			next_state = STATE_UPDATE_YELLOW;
		}
		else if (button_is_hold_activated(&button_mode_set)
				|| button_is_pressed_activated(&button_mode_set))
		{
			button_clear_activation(&button_mode_set);
			next_state = STATE_NORMAL;
		}
		break;
	case STATE_UPDATE_YELLOW:
		if (button_is_hold_activated(&button_mode_select)
				|| button_is_pressed_activated(&button_mode_select))
		{
			button_clear_activation(&button_mode_select);
			next_state = STATE_UPDATE_GREEN;
		}
		else if (button_is_hold_activated(&button_mode_set)
				|| button_is_pressed_activated(&button_mode_set))
		{
			button_clear_activation(&button_mode_set);
			next_state = STATE_NORMAL;
		}
		break;
	case STATE_UPDATE_GREEN:
		if (button_is_hold_activated(&button_mode_select)
				|| button_is_pressed_activated(&button_mode_select))
		{
			button_clear_activation(&button_mode_select);
			next_state = STATE_NORMAL;
		}
		else if (button_is_hold_activated(&button_mode_set)
				|| button_is_pressed_activated(&button_mode_set))
		{
			button_clear_activation(&button_mode_set);
			next_state = STATE_NORMAL;
		}
		break;

	default:
		next_state = STATE_NORMAL;
		break;
	}

	return next_state;
}

void FSM_traffic_light_set_to_next_state(FSM_t *fsm, FSM_state_t next_state)
{
	if (fsm->current_state == next_state)
	{
		return;
	}

	fsm->current_state = next_state;

	switch (next_state)
	{
	case STATE_NORMAL:
		traffic_light_0_current_color = TRAFFIC_LIGHT_COLOR_RED;
		traffic_light_1_current_color = TRAFFIC_LIGHT_COLOR_GREEN;

		traffic_light_turn_on_one_color(&traffic_light_0,
				traffic_light_0_current_color);
		traffic_light_turn_on_one_color(&traffic_light_1,
				traffic_light_1_current_color);

		traffic_light_0_time_left =
				traffic_light_duration[traffic_light_0_current_color];
		traffic_light_1_time_left =
				traffic_light_duration[traffic_light_1_current_color];
		two_digit_7seg_update_value(&two_digit_7seg_0,
				traffic_light_0_time_left);
		two_digit_7seg_update_value(&two_digit_7seg_1,
				traffic_light_1_time_left);
		traffic_light_7seg_current = 0;

		update_7seg();

		software_timer_set_duration_ms(&timer_traffic_light, 1000);
		software_timer_set_duration_ms(&timer_update_7seg,
				SEG7_UPDATE_PERIOD_MS);

		break;

	case STATE_UPDATE_RED:
		change_state_to_update_state(TRAFFIC_LIGHT_COLOR_RED);
		break;

	case STATE_UPDATE_YELLOW:
		change_state_to_update_state(TRAFFIC_LIGHT_COLOR_YELLOW);
		break;

	case STATE_UPDATE_GREEN:
		change_state_to_update_state(TRAFFIC_LIGHT_COLOR_GREEN);
		break;

	default:
		// do nothing, the next_state is invalid
		break;
	}
}

void FSM_traffic_light_do_action_within_state(FSM_t *fsm)
{
	switch (fsm->current_state)
	{
	case STATE_NORMAL:
		// update time left, and change color if time left is now 0
		if (software_timer_is_set(&timer_traffic_light))
		{
			software_timer_set_duration_ms(&timer_traffic_light, 1000);
			traffic_light_0_time_left--;
			traffic_light_1_time_left--;

			// change color
			if (traffic_light_0_time_left <= 0)
			{
				// change color of traffic light 0
				traffic_light_0_current_color =
						traffic_light_next_color_from_current(
								traffic_light_0_current_color);

				traffic_light_turn_on_one_color(&traffic_light_0,
						traffic_light_0_current_color);

				traffic_light_0_time_left =
						traffic_light_duration[traffic_light_0_current_color];
			}
			if (traffic_light_1_time_left <= 0)
			{
				// change color of traffic light 1
				traffic_light_1_current_color =
						traffic_light_next_color_from_current(
								traffic_light_1_current_color);

				traffic_light_turn_on_one_color(&traffic_light_1,
						traffic_light_1_current_color);

				traffic_light_1_time_left =
						traffic_light_duration[traffic_light_1_current_color];
			}

			two_digit_7seg_update_value(&two_digit_7seg_0,
					traffic_light_0_time_left);
			two_digit_7seg_update_value(&two_digit_7seg_1,
					traffic_light_1_time_left);
		}

		// update seg7 display
		if (software_timer_is_set(&timer_update_7seg))
		{
			software_timer_set_duration_ms(&timer_update_7seg,
					SEG7_UPDATE_PERIOD_MS);

			update_7seg();
		}
		break;

	case STATE_UPDATE_RED:
		perform_update_state_funtionality(TRAFFIC_LIGHT_COLOR_RED);
		break;

	case STATE_UPDATE_YELLOW:
		perform_update_state_funtionality(TRAFFIC_LIGHT_COLOR_YELLOW);
		break;

	case STATE_UPDATE_GREEN:
		perform_update_state_funtionality(TRAFFIC_LIGHT_COLOR_GREEN);
		break;

	default:
		// do nothing, current state of fsm is invalid
		break;
	}
}

void change_state_to_update_state(Traffic_light_color_t color)
{
	traffic_light_turn_on_one_color(&traffic_light_0, color);
	traffic_light_turn_on_one_color(&traffic_light_1, color);

	uint8_t current_mode_number;
	switch (color)
	{
	case TRAFFIC_LIGHT_COLOR_RED:
		current_mode_number = 2;
		break;
	case TRAFFIC_LIGHT_COLOR_YELLOW:
		current_mode_number = 3;
		break;
	case TRAFFIC_LIGHT_COLOR_GREEN:
		current_mode_number = 4;
		break;
	default:
		current_mode_number = 99; // should not reach this
		break;
	}

	two_digit_7seg_update_value(&two_digit_7seg_0, traffic_light_duration[color]);
	two_digit_7seg_update_value(&two_digit_7seg_1, current_mode_number);
	update_7seg();

	software_timer_set_duration_ms(&timer_traffic_light, TRAFFIC_LIGHT_BLINK_PERIOD_MS);
	software_timer_set_duration_ms(&timer_update_7seg, SEG7_UPDATE_PERIOD_MS);

}

void perform_update_state_funtionality(Traffic_light_color_t current_color)
{
	if (software_timer_is_set(&timer_traffic_light))
	{
		software_timer_set_duration_ms(&timer_traffic_light,
				TRAFFIC_LIGHT_BLINK_PERIOD_MS);
		traffic_light_toggle_color(&traffic_light_0, current_color);
		traffic_light_toggle_color(&traffic_light_1, current_color);
	}

	if (software_timer_is_set(&timer_update_7seg))
	{
		software_timer_set_duration_ms(&timer_update_7seg,
				SEG7_UPDATE_PERIOD_MS);
		update_7seg();
	}

	if (button_is_pressed_activated(&button_time_change)
			|| button_is_hold_activated(&button_time_change))
	{
		button_clear_activation(&button_time_change);

		traffic_light_duration[current_color]++;
		if (traffic_light_duration[current_color] > 99)
		{
			traffic_light_duration[current_color] = 1;
		}

		two_digit_7seg_update_value(&two_digit_7seg_0,
				traffic_light_duration[current_color]);
	}
}

void update_7seg()
{
	uint8_t traffic_light_number = traffic_light_7seg_current / 2;
	uint8_t digit_number = traffic_light_7seg_current % 2;

	if (traffic_light_number == 0)
	{
		if (digit_number == 0)
		{
			two_digit_7seg_turn_off_all_digit(&two_digit_7seg_1);
		}
		two_digit_7seg_display_digit(&two_digit_7seg_0, digit_number);
	}
	else
	{
		if (digit_number == 0)
		{
			two_digit_7seg_turn_off_all_digit(&two_digit_7seg_0);
		}
		two_digit_7seg_display_digit(&two_digit_7seg_1, digit_number);
	}

	traffic_light_7seg_current = (traffic_light_7seg_current + 1) % 4;
}
