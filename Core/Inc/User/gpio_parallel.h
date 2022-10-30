/*
 * gpio_parallel.h
 *
 *  Created on: Oct 30, 2022
 *      Author: N.T.P.Thanh
 */

#ifndef INC_USER_GPIO_PARALLEL_H_
#define INC_USER_GPIO_PARALLEL_H_

#include "main.h"

/* NOTE:
 * all function within this file is intended to ultilize the BSRR register of
 * output port to set/reset all available pin at the same time
 *
 * mask uint16_t parameter means that any where there is a 1 bit in the mask,
 * the associated pin will be affected by the function, all pin associated with
 * bit 0 will be spared *evil laugh*
 */

// output for each pin will be the associated bit in the value parameter
// all pin with bit 0 in mask will not be affected
void gpio_parallel_write(GPIO_TypeDef * const port, uint16_t mask, uint16_t value);


#endif /* INC_USER_GPIO_PARALLEL_H_ */
