/*
 * fsm_state_list.h
 *
 *  Created on: Nov 1, 2022
 *      Author: ntpt
 */

#ifndef INC_USER_FSM_STATE_LIST_H_
#define INC_USER_FSM_STATE_LIST_H_

typedef enum
{
	STATE_RESET,
	STATE_NORMAL,
	STATE_UPDATE_RED,
	STATE_UPDATE_YELLOW,
	STATE_UPDATE_GREEN,
} FSM_state_t;

#endif /* INC_USER_FSM_STATE_LIST_H_ */
