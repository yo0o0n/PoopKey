/*
 * toilet.c
 *
 *  Created on: Feb 2, 2024
 *      Author: SSAFY
 */

#include "toilet.h"
// kyr add stdio for printf warning
#include <stdio.h>


extern volatile uint8_t OCCUPIED_STALL_CNT;
const uint8_t *ESP_MSG_OCCUPIED = "";
extern I2C_HandleTypeDef hi2c1;

void checkMagnetic(TS* stall)
{
    uint8_t current = sensing(stall->magnetic_door);



    if (current == true) {
        if (stall->is_occupied == true) {
            //nothing
        }
        else {
            OCCUPIED_STALL_CNT++;
            stall->is_occupied = true;
//            sendESP(stall.is_occupied, ESP_MSG_OCCUPIED);
//            SendData(strlen("stall occupied\r\n"), 1, 1, "stall occupied\r\n");
        }
    }
    else {
        if (stall->is_occupied == true) {
            if (stall->last_open_time != 0) {
                if ( (HAL_GetTick() - stall->last_open_time) >= TERM_CHANGE_OCCUPIED) { // GetTick()/(1000*60)%60 ms -> min
                	OCCUPIED_STALL_CNT--;
                	stall->is_occupied = false;
                    stall->last_open_time = 0;
                    //sendESP(stall.is_occupied, ESP_MSG_OCCUPIED);
//                    SendData(strlen("stall free\r\n"), 1, 1, "stall free\r\n");
                }
            }
            else {
                stall->last_open_time = HAL_GetTick();
            }
        }
        else {
            //nothing
        }
    }
    turnLED(stall->led_usable, !current);


#if DEBUG
    printf("magnetic: %u, ", current);
#endif


}

void checkTissueAmount(TS* stall) {
    float current_dist = getDistance(stall->sonar_tissue);
    float tissue_percentage = (MIN_TISSUE_DISTANCE - current_dist) / MAX_TISSUE_RADIUS * 100;
    if(tissue_percentage <= 0.0) tissue_percentage = 0.0f;

    if (HAL_GetTick() - stall->last_tissue_time > PERIOD_CHECK_TISSUE) { // 1분 == 60만 Tick
//        sendESP(tissue_percentage);
//    	SendData(strlen("Tissue Empty\r\n"), 1, 1, "Tissue Empty\r\n");
        stall->last_tissue_time = HAL_GetTick();
    }
    if (tissue_percentage <= THRESHOLD_MIN_TISSUE_PERCENTAGE) {
        turnLED(stall->led_tissue, true);
    }
    else {
        turnLED(stall->led_tissue, false);
    }
#if DEBUG
    printf("tissue dist: %.3f, percentage: %.3f, ", current_dist, tissue_percentage);
#endif
}

void checkWaterTissue(TS* stall)
{
    float distance = getDistance(stall->sonar_water_tissue);
    if (distance < THRESHOLD_WATER_TISSUE_HAND_DISTANCE) {
        runMotor(stall->servo_water_tissue, MOTOR_WATER_TISSUE_PUSH_ANGLE);
        HAL_Delay(1000);
        runMotor(stall->servo_water_tissue, MOTOR_WATER_TISSUE_BACK_ANGLE);
    }
#if DEBUG
    printf("water tissue dist: %.3f, ", distance);
#endif
}



void untactIR(TS* stall) {
    float ir_temperature = getIRTemperature(stall->ir_untact);
    if(ir_temperature >= THRESHOLD_IR_TEMPERATURE && (stall->last_ir_time == 0 || HAL_GetTick() - stall->last_ir_time >= TERM_PUSH_TOILET_COVER)) {
        stall->last_ir_time = HAL_GetTick();
        stall->is_flushed = false;
        if(stall->is_cover_down == false) {
            runMotor(stall->servo_toilet_cover, MOTOR_TOILET_COVER_PUSH_ANGLE);
            HAL_Delay(MOTOR_DELAY);
            runMotor(stall->servo_toilet_cover, MOTOR_TOILET_COVER_BACK_ANGLE);
        }
    }
#if DEBUG
	printf("IR : %.3f, ", ir_temperature);
#endif
}

void flushToilet(TS* stall) {
    stall->is_cover_down = sensing(stall->tilt_toilet_cover);
    if (stall->is_cover_down == true && stall->last_ir_time != 0) {
    	// < => >
        if (HAL_GetTick() - stall->last_ir_time < THRESHOLD_IR_CHECKED_TIME && stall->is_flushed == false) { // 10s == 10000ms
            /* Flush Toilet
            runMoter(stall.servo_toilet_cover, degree);
            HAL_Delay(MOTOR_DELAY)
            runMoter(stall.servo_toilet_cover, degree);
            */
            stall->last_flush_time = HAL_GetTick();
            stall->is_checked_broken = false;
            stall->is_flushed = true;
        }
    }
#if DEBUG
    printf("is_cover_down: %u, last_ir_time %lu, last_flush_time %lu, ", stall->is_cover_down, stall->last_ir_time, stall->last_flush_time);
#endif
}

void checkBroken(TS *stall) {
    if (stall->is_cover_down && stall->last_flush_time != 0) {
        if (WAIT_TOILET_FLUSH_DOWN <= HAL_GetTick() - stall->last_flush_time && stall->is_checked_broken == false) { //10s == 10000ms
//            printf("open cover")
        	stall->is_checked_broken = true; // false로 초기화 하는 부분 어딨지?
            runMotor(stall->servo_sonar_cover, MOTOR_CHECK_BROKEN_COVER_PUSH_ANGLE);
            HAL_Delay(MOTOR_DELAY);
            float toilet_water_dist = getDistance(stall->sonar_toilet_broken);
            runMotor(stall->servo_sonar_cover, MOTOR_CHECK_BROKEN_COVER_BACK_ANGLE);
            if (toilet_water_dist < NORMAL_TOILET_WATER_DISTANCE) {
                turnLED(stall->led_broken, true);
//                sendESP(stall., ESP_MSG_OCCUPIED);
//                SendData(strlen("broken\r\n"), 1, 1, "broken\r\n");
            }
            else {
                turnLED(stall->led_broken, false);
            }
        }
    }
#if DEBUG
    printf("Is broken LED ON: %u\r\n",HAL_GPIO_ReadPin(stall->led_broken.Port, stall->led_broken.PIN_out));
#endif
}


void initStalls(TS * stall) {
	stall->is_occupied = false;
	stall->last_open_time = 0;
	stall->tissue_amount = 100;
	stall->is_cover_down = false;
	stall->last_ir_time = 0;
	stall->last_flush_time = 0;
	stall->is_checked_broken = false;
	stall->last_tissue_time = 0;


	stall->magnetic_door = (GI){ GPIOB,GPIO_PIN_4, 0 };

	stall->sonar_water_tissue = (GI){ GPIOA, GPIO_PIN_12, GPIO_PIN_11 };
	stall->servo_water_tissue = (TI){ htim2, TIM_CHANNEL_2 };

	stall->sonar_tissue = (GI){ GPIOB, GPIO_PIN_2, GPIO_PIN_1 };

	stall->ir_untact = (II){ hi2c1 };
	stall->servo_toilet_cover = (TI){  htim2, TIM_CHANNEL_1 };


	stall->tilt_toilet_cover = (GI){ GPIOB, GPIO_PIN_5, 0 };
	stall->servo_sonar_cover = (TI){ htim2, TIM_CHANNEL_3 };
	stall->sonar_toilet_broken = (GI){ GPIOB, GPIO_PIN_12, GPIO_PIN_11 };

	stall->led_usable = (GI){ GPIOC, 0, GPIO_PIN_5 };
	stall->led_broken = (GI){ GPIOC, 0, GPIO_PIN_8 };
	stall->led_tissue = (GI){ GPIOC, 0, GPIO_PIN_6 };

	motor_start(stall->servo_water_tissue);
	motor_start(stall->servo_sonar_cover);
	motor_start(stall->servo_toilet_cover);

}

