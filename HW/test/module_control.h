typedef (unsigned char) uint8_t;
typedef (unsigned short) uint16_t;
typedef (unsigned int) uint32_t;

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

void turnLED(GI led, uint8_t onOff);
void runMotor(TI motor, int degree);
float getDistance(GI sonar);
void sendESP(uint8_t target, (char *)msg);
void getIRTemperature(II ir);
uint8_t sensing(GI sensor);