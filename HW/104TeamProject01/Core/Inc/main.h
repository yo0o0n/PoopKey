/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI15_10_IRQn
#define Servo_Cover_Pin GPIO_PIN_0
#define Servo_Cover_GPIO_Port GPIOA
#define Servo_Water_Tissue_Pin GPIO_PIN_1
#define Servo_Water_Tissue_GPIO_Port GPIOA
#define COM_TX_Pin GPIO_PIN_2
#define COM_TX_GPIO_Port GPIOA
#define COM_RX_Pin GPIO_PIN_3
#define COM_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define LED_Green_Pin GPIO_PIN_5
#define LED_Green_GPIO_Port GPIOC
#define Sonar_Tissue_Trig_Pin GPIO_PIN_1
#define Sonar_Tissue_Trig_GPIO_Port GPIOB
#define Sonar_Tissue_Echo_Pin GPIO_PIN_2
#define Sonar_Tissue_Echo_GPIO_Port GPIOB
#define Servo_Sonar_Cover_Pin GPIO_PIN_10
#define Servo_Sonar_Cover_GPIO_Port GPIOB
#define Sonar_Cover_Trig_Pin GPIO_PIN_11
#define Sonar_Cover_Trig_GPIO_Port GPIOB
#define Sonar_Cover_Echo_Pin GPIO_PIN_12
#define Sonar_Cover_Echo_GPIO_Port GPIOB
#define LED_Yellow_Pin GPIO_PIN_6
#define LED_Yellow_GPIO_Port GPIOC
#define LED_RED_Pin GPIO_PIN_8
#define LED_RED_GPIO_Port GPIOC
#define ESP_TX_Pin GPIO_PIN_9
#define ESP_TX_GPIO_Port GPIOA
#define ESP_RX_Pin GPIO_PIN_10
#define ESP_RX_GPIO_Port GPIOA
#define Sonar_Water_Tissue_Trig_Pin GPIO_PIN_11
#define Sonar_Water_Tissue_Trig_GPIO_Port GPIOA
#define Sonar_Water_Tissue_Echo_Pin GPIO_PIN_12
#define Sonar_Water_Tissue_Echo_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define Magnetic_Pin GPIO_PIN_4
#define Magnetic_GPIO_Port GPIOB
#define Tilt_Pin GPIO_PIN_5
#define Tilt_GPIO_Port GPIOB
#define IR_SCL_Pin GPIO_PIN_8
#define IR_SCL_GPIO_Port GPIOB
#define IR_SDA_Pin GPIO_PIN_9
#define IR_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
