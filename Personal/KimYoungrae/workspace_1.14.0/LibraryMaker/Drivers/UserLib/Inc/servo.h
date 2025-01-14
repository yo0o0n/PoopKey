/*
 * servo.h
 *
 *  Created on: Jan 25, 2024
 *      Author: Kim YR
 */

/*
 * servo motor 1 / 2
 * TIM2_ch1 and TIM2_ch2
 *
 *
 * Function
 *
 * void servo_cover_push(void)
 * void servo_cover_pull(void)
 *
 * void servo_water_push(void)
 * void servo_water_pull(void)
 *
 */



#ifndef USERLIB_INC_SERVO_H_
#define USERLIB_INC_SERVO_H_

#include "stm32f1xx_hal.h"
// #include "stm32f1xx_hal_tim.h"

#define PUSH 1000
#define PULL 500


void servo_init(void);

void servo_cover_push(void);
void servo_cover_pull(void);

void servo_water_push(void);
void servo_water_pull(void);


#endif /* USERLIB_INC_SERVO_H_ */

