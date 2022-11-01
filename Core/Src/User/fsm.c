/*
 * fsm.h
 *
 *  Created on: Nov 1, 2022
 *      Author: ntpt
 */

#include "User/fsm.h"

FSM_state_t FSM_get_next_state(FSM_t *fsm, FSM_get_next_state_function_t fp)
{
	return fp(fsm->current_state);
}

void FSM_set_to_next_state(FSM_t *fsm, FSM_state_t next_state,
		FSM_set_next_state_function_t fp)
{
	FSM_state_t current_state = fsm->current_state;
	if (current_state == next_state)
	{
		// do nothing, return
		return;
	}

	fp(fsm, next_state);
}

void FSM_do_action_within_state(FSM_t *fsm,
		FSM_do_action_within_state_function_t fp)
{
	fp(fsm);
}
