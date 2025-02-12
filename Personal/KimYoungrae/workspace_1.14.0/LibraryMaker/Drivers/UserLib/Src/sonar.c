/*
 * sonar.c
 *
 *  Created on: Jan 25, 2024
 *      Author: Kim YR
 */



#include "sonar.h"

extern TIM_HandleTypeDef htim1;





uint32_t overflows = 0U;


void sonar_timer_init(void) {
	HAL_TIM_Base_Init(&htim1);
	__HAL_TIM_SET_COUNTER(&htim1, 0);
	HAL_TIM_Base_Start_IT(&htim1);
}


// OverWrite
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) { // 제네레이트 없음
	if(htim->Instance == TIM1) {
		overflows++;
	}
}


uint32_t GetMicroSec(void){ // 제네레이트 없음
	uint32_t count = __HAL_TIM_GET_COUNTER(&htim1);
	uint32_t overflow = overflows;
	if (__HAL_TIM_GET_FLAG(&htim1, TIM_FLAG_UPDATE) && (count < 0x8000)) {
	        overflow++;
	}

	return(overflow << 16) + count;
}




GPIO_PIN gpio_pin[3] = {
		{GPIO_PIN_8, GPIO_PIN_9},
		{GPIO_PIN_7, GPIO_PIN_6},
		{GPIO_PIN_12, GPIO_PIN_11}
};

// 0, 1, 2
float get_distance(uint8_t select) {
	uint32_t st = 0U;
	uint32_t ed = 0U;
	uint32_t diff = 0U;
	float distance = 0.0;



	HAL_GPIO_WritePin(GPIOA, gpio_pin[select].trig, RESET);
	HAL_Delay(5);
	HAL_GPIO_WritePin(GPIOA, gpio_pin[select].trig, SET);
	HAL_Delay(20);
	HAL_GPIO_WritePin(GPIOA, gpio_pin[select].trig, RESET);


	while(HAL_GPIO_ReadPin(GPIOA, gpio_pin[select].echo)==GPIO_PIN_RESET);
	st = GetMicroSec();
	while(HAL_GPIO_ReadPin(GPIOA, gpio_pin[select].echo)==GPIO_PIN_SET);
	ed = GetMicroSec();

	diff = ed - st;
	distance = diff * 0.034 / 2;

	return distance;
}


/*
float get_distance_A(void) {
	uint32_t st = 0U;
	uint32_t ed = 0U;
	uint32_t diff = 0U;
	float distance = 0.0;



	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, RESET);
	HAL_Delay(5);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, SET);
	HAL_Delay(20);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, RESET);


	while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)==GPIO_PIN_RESET);
	st = GetMicroSec();
	while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)==GPIO_PIN_SET);
	ed = GetMicroSec();

	diff = ed -st;
	distance = diff * 0.034 / 2;

	return ret;
}


float get_distance_B(void) {
	uint32_t st = 0U;
	uint32_t ed = 0U;
	uint32_t diff = 0U;
	float distance = 0.0;



	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, RESET);
	HAL_Delay(5);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, SET);
	HAL_Delay(20);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, RESET);


	while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)==GPIO_PIN_RESET);
	st = GetMicroSec();
	while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)==GPIO_PIN_SET);
	ed = GetMicroSec();

	diff = ed -st;
	distance = diff * 0.034 / 2;

	return ret;
}


float get_distance_C(void) {
	uint32_t st = 0U;
	uint32_t ed = 0U;
	uint32_t diff = 0U;
	float distance = 0.0;



	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, RESET);
	HAL_Delay(5);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, SET);
	HAL_Delay(20);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, RESET);


	while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11)==GPIO_PIN_RESET);
	st = GetMicroSec();
	while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11)==GPIO_PIN_SET);
	ed = GetMicroSec();

	diff = ed -st;
	distance = diff * 0.034 / 2;

	return ret;
}
*/
