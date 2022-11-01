/*
 * gpio_parallel.c
 *
 *  Created on: Oct 30, 2022
 *      Author: N.T.P.Thanh
 */

#include "User/gpio_parallel.h"

void gpio_parallel_write(GPIO_TypeDef *const port, uint16_t mask,
		uint16_t value)
{
	uint16_t set_pattern = value & mask;
	uint16_t reset_pattern = (~set_pattern) & mask;

	uint32_t reset_set_pattern = (((uint32_t) reset_pattern) << 16u)
			| (uint32_t) set_pattern;

	port->BSRR = reset_set_pattern;
}
