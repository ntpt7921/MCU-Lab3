/*
 * fsm.h
 *
 *  Created on: Nov 1, 2022
 *      Author: ntpt
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "main.h"
#include "User/fsm_state_list.h"

/**
 * NOTE:
 * The finite state machine (FSM) module is written for general use
 * The FSM contains the current state
 * We have separate function for determining the next state, set current state to
 * next state, and do action within a state
 * All those function is passed a FSM struct and a function pointer of what to do
 *
 * FSM_state_t is declared in fsm_state_list.h
 */

typedef struct
{
	FSM_state_t current_state;
} FSM_t;

typedef FSM_state_t (*FSM_get_next_state_function_t)(FSM_state_t current_state);
typedef void (*FSM_set_next_state_function_t)(FSM_t *fsm,
		FSM_state_t next_state);
typedef void (*FSM_do_action_within_state_function_t)(FSM_t *fsm);

/**
 * NOTE:
 * These 3 function represent the changing of state of the FSM
 *   - FSM_get_next_state will get the next state from the current state
 *   - FSM_set_to_next_state will do the necessary action on state change
 *   - FSM_do_action_within_state will perform what a specific state entails
 */

FSM_state_t FSM_get_next_state(FSM_t *fsm, FSM_get_next_state_function_t fp);
void FSM_set_to_next_state(FSM_t *fsm, FSM_state_t next_state,
		FSM_set_next_state_function_t fp);
void FSM_do_action_within_state(FSM_t *fsm,
		FSM_do_action_within_state_function_t fp);

#endif /* INC_FSM_H_ */
