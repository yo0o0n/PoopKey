
typedef (unsigned char) uint8_t;
typedef (unsigned short) uint16_t;
typedef (unsigned int) uint32_t;

#include<stdlib.h>



#define MAX_TISSUE_RADIUS
#define MIN_TISSUE_DISTANCE
#define NORMAL_TOILET_WATER_DISTANCE
#define THRESHOLD_MIN_TISSUE_PERCENTAGE
#define THRESHOLD_WATER_TISSUE_HAND_DISTANCE
#define THRESHOLD_IR_TEMPERATURE
#define THRESHOLD_FLUSHED_TIME
#define THRESHOLD_IR_CHECKED_TIME
#define TERM_CHANGE_OCCUPIED
#define WAIT_TOILET_COVER_CLOSED
#define MOTOR_WATER_TISSUE_PUSH_ANGLE
#define MOTOR_WATER_TISSUE_BACK_ANGLE
#define MOTOR_TOILET_COVER_PUSH_ANGLE
#define MOTOR_TOILET_COVER_BACK_ANGLE
#define MOTOR_CHECK_BROKEN_COVER_PUSH_ANGLE
#define MOTOR_CHECK_BROKEN_COVER_BACK_ANGLE
#define MOTOR_CHECK_BROKEN_COVER_DELAY
#define MOTOR_DELAY
#define PERIOD_CHECK_TISSUE
#define ESP_MUX_ID_RASPI
#define ESP_MUX_ID_BACKEND

uint8_t OCCUPIED_STALL_CNT = 0;

typedef struct GPIOInfo {
    GPIO_TypeDef* Port;
    uint16_t PIN;
    uint16_t PIN_out;
}GI;


typedef struct TIMInfo {
    TIM_HandleTypeDef htim;
    uint32_t channel; // 이거 원래 #define문이라 이슈 가능성 있어요.
}TI;

typedef struct I2CInfo {
    I2C_HandleTypeDef hi2c1;
}II;



typedef struct ToiletStall {
    uint8_t is_occupied; // 원래 bool
    uint32_t last_open_time; // 원래 int
    float tissue_amount;
    uint8_t is_cover_down;  // 원래 bool
    uint32_t last_ir_time;  // 원래 int
    uint32_t last_flush_time;  // 원래 int
    uint8_t is_checked_broken; // 원래 bool
    uint32_t last_tissue_time; // 원래 int

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
    GI tilt_toilet_cover;
}TS;

void turnLED(GI led, uint8_t onOff);
void runMotor(TI motor, int degree);
float getDistance(GI sonar);
void sendESP(uint8_t target, (char *)msg);
void getIRTemperature(II ir);
uint8_t sensing(GI sensor);

void checkMagnetic(TS stall);
void untactIR(TS stall);
void flushToilet(TS stall);
void checkBroken(TS stall);
void checkTissueAmount(TS stall);
void checkWaterTissue(TS stall);


void checkMagnetic(TS stall)
{
    uint8_t current = sensing(stall.magnetic_door);
    if (current == true) {        
        if (stall.is_occupied == true) {
            //nothing
        }
        else {
            OCCUPIED_STALL_CNT++;
            stall.is_occupied = true;
            sendESP(stall.is_occupied);             
        }
    }
    else {
        if (stall.is_occupied == true) {
            OCCUPIED_STALL_CNT--;
            if (stall.last_open_time != -1) {
                if ( (HAL_GetTick() - stall.last_open_time) >= TERM_CHANGE_OCCUPIED) { // GetTick()/(1000*60)%60 ms -> min
                    stall.is_occupied = false;                    
                    stall.last_open_time = -1;
                    sendESP(stall.is_occupied);
                }
            }
            else {
                stall.last_open_Time = GetTick();
            }
        }
        else {
            //nothing
        }
    }
    turnLED(stall.led_usable, !current);
}

void untactIR(TS stall) {
    float ir_temperature = getIRTemperature(stall.ir_untact);
    if(ir_temperature >= THRESHOLD_IR_TEMPERATURE) {
        stall.last_ir_time = HAL_GetTick();
        if(stall.is_cover_down == false) {
            runMotor(stall.servo_toilet_cover, MOTOR_TOILET_COVER_PUSH_ANGLE);
            HAL_Delay(MOTOR_DELAY);
            runMotor(stall.servo_toilet_cover, MOTOR_TOILET_COVER_BACK_ANGLE);
        }
    }
}

void flushToilet(TS stall) {
    stall.is_cover_down = sensing(stall.tilt_toilet_cover);
    if (stall.is_cover_down == true) {
        if (HAL_GetTick() - stall.last_ir_time < THRESHOLD_IR_CHECKED_TIME && HAL_GetTick() - stall.last_flush_time < THRESHOLD_FLUSHED_TIME) { // 10s == 10000ms
            /* Flush Toilet
            runMoter(stall.servo_toilet_cover, degree);
            HAL_Delay(MOTOR_DELAY)
            runMoter(stall.servo_toilet_cover, degree);
            */
            stall.last_flush_time = HAL_GetTick();
            stall.is_checked_broken = false;
        }
    }
}

void checkBroken(TS stall) {
    if (stall.is_cover_down) {
        if (WAIT_TOILET_COVER_CLOSED <= HAL_GetTick() - stall.last_flush_time && stall.is_checked_broken == false) { //10s == 10000ms
            stall.is_checked_broken = true;
            runMotor(stall.servo_toilet_cover, MOTOR_CHECK_BROKEN_COVER_PUSH_ANGLE);
            HAL_Delay(MOTOR_DELAY);
            float toilet_water_dist = getDistance(stall.sonar_toilet_broken);
            runMotor(stall.servo_toilet_cover, MOTOR_CHECK_BROKEN_COVER_BACK_ANGLE);
            if (toilet_water_dist < NORMAL_TOILET_WATER_DISTANCE) {                
                turnLED(stall.led_broken, true);
                sendESP(stall.led_broken, true);
            }
            else {
                turnLED(stall.led_broken, false);
            }
        }
    }
}

void checkTissueAmount(TS stall) {
    float current_dist = getDistance(stall.sonar_tissue);
    float tissue_percentage = (MIN_TISSUE_DISTANCE - current_dist) / MAX_TISSUE_RADIUS;

    if (HAL_GetTick() - stall.last_tissue_time > PERIOD_CHECK_TISSUE) { // 1분 == 60만 Tick
        sendESP(tissue_percentage);
        stall.last_tissue_time = HAL_GetTick();
    }
    if (tissue_percentage <= THRESHOLD_MIN_TISSUE_PERCENTAGE) {
        turnLED(stall.LED_tissue, true);
    }
    else {
        turnLED(stall.LED_tissue, false);
    }
}

void checkWaterTissue(TS stall)
{
    float distance = Get_Distance(stall.sonar_water_tissue);
    if (distance < THRESHOLD_WATER_TISSUE_HAND_DISTANCE) {
        runMotor(stall.servo_water_tissue, MOTOR_WATER_TISSUE_PUSH_ANGLE);
        HAL_Delay(1000);
        runMotor(stall.servo_water_tissue, MOTOR_WATER_TISSUE_BACK_ANGLE);
    }
}



uint8_t sensing(GI sensor) { // 마그네틱 같은거
    uint8_t ret = HAL_GPIO_ReadPin(sensor.Port, sensor.PIN);
}

void turnLED(GI led, uint8_t is_ON) { // bool 을 uint8_t로 바꾸었습니다.
    HAL_GPIO_WritePin(led.Port, led.PIN_out, is_ON);
}


void motor_start(MI motor) { // 우리는 모터가 두 개라서 두개를 스타트 해야합니다.
    HAL_TIM_PWM_Start(&(motor.htim), MI.channel);
}

void motor(MI motor, uint16_t degree) { // 근데 이거 조금 생각해봐야 할거에요. g
    __HAL_TIM_SET_COMPARE(&(motor.htim), MI.channel, degree);

    // degree는 500이 0도 // 1000 이 90도 
    // main문을 하면서 다시 검증해볼 필요 있음 (MG996R이랑 SG90이랑 Duty 같음)
}

float getDistance(GI Sensor) { // 초음파
    HAL_GPIO_WritePin(Sensor.Port, Sensor.PIN_out, RESET);
    HAL_Delay(5);
    HAL_GPIO_WritePin(Sensor.Port, Sensor.PIN_out, SET);
    HAL_Delay(20);
    HAL_GPIO_WritePin(Sensor.Port, Sensor.PIN_out, RESET);

    //printf("right after : %lu\r\n", HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9));

    while (HAL_GPIO_ReadPin(Sensor.Port, Sensor.PIN) == GPIO_PIN_RESET);
    uint32_t st = GetMicroSec();
    while (HAL_GPIO_ReadPin(Sensor.Port, Sensor.PIN) == GPIO_PIN_SET);
    uint32_t ed = GetMicroSec();

    uint32_t diff = ed - st;
    float ret = diff * 0.034 / 2;

    return ret;
}

float getIRTemperature(II ir) {
    // 이건 "mlx90614.h" 와 "mlx90614.c" 가 있어용.
    // 복사해서 쓰면 함수 쓸 수 있어용.
    // 함수 : float MLX90614_ReadTemperature(void);
    // 앤 그외에 적을거 없어요.

    uint8_t data[3] = { 0, };
    HAL_I2C_Mem_Read(&(ir.hi2c1), 0x5A << 1, 0x07, 0x00000001U, data, 3, HAL_MAX_DELAY);
    //HAL_I2C_Mem_Read(&hi2c1, MLX90614_I2C_ADDR, 0x07, I2C_MEMADD_SIZE_8BIT, data, 3, HAL_MAX_DELAY);

    int16_t rawTemperature = (data[1] << 8) | data[0];
    float temperature = rawTemperature * 0.02 - 273.15;

    return temperature;
}
