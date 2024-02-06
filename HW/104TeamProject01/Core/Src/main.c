/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include"toilet.h"
//#include"esp_control.h"
#include"module_control.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
int _write(int fd, char *ptr, int len)
{
	HAL_UART_Transmit(&huart2, (unsigned char*)ptr, len, HAL_MAX_DELAY);
	return len;
}

int _read(int file, char *ptr, int len)
{
	HAL_UART_Receive(&huart2, (unsigned char*)ptr, len, HAL_MAX_DELAY);
	return len;
}

int __io_putchar(int ch)
{
	HAL_UART_Transmit(&huart2, (unsigned char*)&ch, 1, HAL_MAX_DELAY);
	return ch;
}

int __io_getchar(void)
{
	uint8_t ch = 0;
	HAL_UART_Receive(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
	return ch;
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */




// kyr Init 2 for full occupied test
volatile uint8_t OCCUPIED_STALL_CNT = 2;
// kyr add before occupied stall  and kyr Init 2 for full occupied test
uint8_t BEFORE_OCCUPIED_STALL_CNT;

// --------------------------------

// -----------------------------------

extern uint16_t Rx_Head;
extern uint16_t Rx_Tail;


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	/* USER CODE BEGIN 1 */
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);


	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_USART2_UART_Init();
	MX_TIM1_Init();
	MX_TIM2_Init();
	MX_USART1_UART_Init();
	MX_I2C1_Init();
	/* USER CODE BEGIN 2 */

	TS stall;
	initStalls(&stall);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	HAL_TIM_Base_Init(&htim1);         // ?��?��?��?��?�� ?��?��
	__HAL_TIM_SET_COUNTER(&htim1, 0);  // ?��?��?��?��?�� ?��?��
	HAL_TIM_Base_Start_IT(&htim1);     // ?��?��?��?��?�� ?��?��


	printf("start STM32F103Rb\r\n");

  // Wait for Interrupt
	setInterrupt();

	SendAT();
	HAL_Delay(100);

	WifiAccess();

	HAL_Delay(5000);


	RaspiTCPSocketAccess();

	HAL_Delay(100);

	// SendData(uint8_t size, uint8_t is_MUX, uint8_t target, uint8_t * data)

	SendData(strlen((char *)"ABCDEFG\r\n"), 0, 0, (uint8_t *)"ABCDEFG\r\n");

	uint8_t checkArr[1024];

	HAL_Delay(5000);

	EspResponseCheck();
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


//	  printf("Second : %5lu\t", (HAL_GetTick() / 1000));
//	  checkMagnetic(&stall);
//	  checkTissueAmount(&stall);
//	  checkWaterTissue(&stall);
//	  untactIR(&stall);
//	  flushToilet(&stall);
//
//	  // ----- kyr 02 06 START --------
//
//	  checkBroken(&stall);
//	  printf("how many use stalls: %u\r\n", OCCUPIED_STALL_CNT);
//	  if(OCCUPIED_STALL_CNT == MAX_STALL && BEFORE_OCCUPIED_STALL_CNT < MAX_STALL)
//		  //SEND(Raspi);
//		  printf("STALL be MAX \r\n");
//	  else if(BEFORE_OCCUPIED_STALL_CNT == MAX_STALL)
//		  //SEND(Raspi);
//		  printf("STALL still MAX \r\n");
//	  else if(OCCUPIED_STALL_CNT < MAX_STALL) // add kyr
//		  printf("STALL Empty \r\n");
//	  BEFORE_OCCUPIED_STALL_CNT = OCCUPIED_STALL_CNT;



	  // TODO 라즈베리파이에게 받아오기
	  // 1. 쌓이는게 읽는거 보다 훨씬 빠르다.
	  // 2. 쌓이는게 더 느리다. 이 경우 IPD에서 IP까지만 오는 경우가 생길거다.

	  memset(checkArr, 0, sizeof(checkArr));
	  uint8_t data = ReadBuffer();
	  uint16_t CheckArr_count = 0;
	  uint8_t msgSize = 0;
	  if(data == '+') {
		  printf("+ get in \r\n");
		  for(uint8_t i = 0; i < 4; i++) {
			  data = ReadBuffer();
			  checkArr[CheckArr_count++] = data;
		  }
		  printf("%s\r\n", checkArr);



		  if(strstr(checkArr, "IPD,") != 0) { // 찾음
			  printf("found IPD\r\n");

			  memset(checkArr, 0, sizeof(checkArr));
			  CheckArr_count = 0;

			  do {
				  data = ReadBuffer();
				  checkArr[CheckArr_count++] = data;
			  }while(data >= '0' && data <= '9');
		  } // 마지막으로 숫자가 아닌걸 하나 받음

		  printf("%s\r\n", checkArr);
		  msgSize = atoi(checkArr);

		  memset(checkArr, 0, sizeof(checkArr));
		  CheckArr_count = 0;


		  for(uint8_t i = 0; i < msgSize; i++) {
			  data = ReadBuffer();
			  checkArr[CheckArr_count++] = data;
		  }

		  printf("%s\r\n", checkArr);

	  }

//	  HAL_Delay(5000);

//	  HAL_Delay(5000);
//	  SendData(strlen((char *)"ABCDEFG\r\n"), 0, 0, (uint8_t *)"ABCDEFG\r\n");

//	  printf("\r\n");

//	  uint8_t data = ReadBuffer();
//	  	if(data != 0)
//	  		printf("%c", data);
//
	  // ----- kyr 02 06 END -------------

//	  uint8_t mag = sensing(magnetic);
//	  float water_dist = getDistance(water_sonar);
//	  HAL_Delay(100);
//	  float tissue_dist = getDistance(tissue_sonar);
//	  float temperature = getIRTemperature(ir); // hand is 40C
//	  uint8_t is_horizon = sensing(tilt);
//	  float dung_dist = getDistance(cover_sonar);
//
//	  turnLED(RED, 1);
//	  turnLED(YELLOW, 1);
//	  turnLED(GREEN, 1);
//
//
//	  runMotor(servo_water_tissue, 500);
//	  HAL_Delay(1000);
//
//	  runMotor(servo_water_tissue, 1000);
//	  HAL_Delay(1000);
//
//
//	  runMotor(servo_cover, 200);
//	  HAL_Delay(1000);
//
//
//	  runMotor(servo_cover, 800);
//	  HAL_Delay(1000);
//
//
//	  runMotor(sonar_cove_servo, 200);
//	  HAL_Delay(1000);
//
//
//	  runMotor(sonar_cove_servo, 800);
//	  HAL_Delay(1000);
//
//
//	  turnLED(RED, 0);
//	  turnLED(YELLOW, 0);
//	  turnLED(GREEN, 0);

//	  printf("magnetic: %-5u, water_tissue_dist: %10.3f\r\n", mag, water_dist);
//	  printf("magnetic: %-5u, water_tissue_dist: %10.3f, tissue_dist: %10.3f\r\n", mag, water_dist, tissue_dist);
//	  printf("magnetic: %-5u, water_tissue_dist: %10.3f, tissue_dist: %10.3f, temperature: %10.3f\r\n", mag, water_dist, tissue_dist, temperature);
//	  printf("magnetic: %-5u, water_tissue_dist: %10.3f, tissue_dist: %10.3f, temperature: %10.3f tilt: %3u\r\n", mag, water_dist, tissue_dist, temperature, is_horizon);
//	  printf("magnetic: %-5u, water_tissue_dist: %10.3f, tissue_dist: %10.3f, temperature: %10.3f tilt: %3u, dung: %10.3f\r\n", mag, water_dist, tissue_dist, temperature, is_horizon, dung_dist);
	  HAL_Delay(100);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
