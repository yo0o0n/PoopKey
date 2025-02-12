/*
 * servo.c
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

#include "servo.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;

// must be called at main
void servo_init(void) {
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
}



// must be called at main while
void servo_cover_push(void) {
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, PUSH);
}


// must be called at main while
void servo_cover_pull(void) {
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, PULL);
}


// must be called at main while
void servo_water_push(void) {
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, PUSH);
}


// must be called at main while
void servo_water_pull(void){
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, PULL);
}
