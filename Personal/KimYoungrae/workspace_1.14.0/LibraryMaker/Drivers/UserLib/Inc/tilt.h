/*
 * tilt.h
 *
 *  Created on: Jan 25, 2024
 *      Author: Kim YR
 */

#ifndef USERLIB_INC_TILT_H_
#define USERLIB_INC_TILT_H_


#include "stm32f1xx_hal.h"

#define HAL_HORIZON 1
#define HAL_VERTICAL 0

uint8_t is_tilt_horizon(void);

#endif /* USERLIB_INC_TILT_H_ */
