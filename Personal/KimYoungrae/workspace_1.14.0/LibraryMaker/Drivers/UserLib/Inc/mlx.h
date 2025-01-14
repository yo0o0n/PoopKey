/*
 * mlx90614.h
 *
 *  Created on: Jan 23, 2024
 *      Author: Kim YR
 */

#ifndef USERLIB_INC_MLX_H_
#define USERLIB_INC_MLX_H_

#include "stm32f1xx_hal.h"

#define MLX90614_I2C_ADDR 0x5A << 1  // mlx90614 I2C 주소

float MLX90614_ReadTemperature(void);

#endif /* USERLIB_INC_MLX_H_ */

#ifndef MLX_H_
#define MLX_H_



#endif /* MLX_H_ */
