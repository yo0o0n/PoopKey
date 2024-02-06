/*
 * toilet.h
 *
 *  Created on: Feb 2, 2024
 *      Author: SSAFY
 */

#ifndef USERLIB_INC_TOILET_H_
#define USERLIB_INC_TOILET_H_
#include "stm32f1xx_hal.h"
#include "module_control.h"
#include "gpio.h"
#include "i2c.h"
#include "tim.h"

// ---------------------------------
#include "global_define.h"

// ---------------------------------


typedef struct ToiletStall {
    uint8_t is_occupied; // 원래 bool
    uint32_t last_open_time; // 원래 int
    float tissue_amount;
    uint8_t is_cover_down;  // 원래 bool
    uint32_t last_ir_time;  // 원래 int
    uint32_t last_flush_time;  // 원래 int
    uint8_t is_checked_broken; // 원래 bool
    uint32_t last_tissue_time; // 원래 int
    uint8_t is_flushed;

    GI magnetic_door;
    GI sonar_tissue;
    GI sonar_water_tissue;
    GI sonar_toilet_broken;
    II ir_untact;
    GI led_usable;
    GI led_broken;
    GI led_tissue;
    TI servo_water_tissue;
    TI servo_toilet_cover;
    TI servo_sonar_cover;
    GI tilt_toilet_cover;
}TS;

void checkMagnetic(TS* stall);
void checkTissueAmount(TS* stall);
void checkWaterTissue(TS* stall);
void untactIR(TS* stall);
void flushToilet(TS* stall);
void checkBroken(TS* stall);


void initStalls(TS *stall);
#endif /* USERLIB_INC_TOILET_H_ */
