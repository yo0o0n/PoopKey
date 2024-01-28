# ESP01 AT명령어 통신

## 진수 제안
stm32의 시스템과 아두이노 시스템과 ESP01의 시스템이 달라서
보내는거랑 받는데 있어서 같은 "OK"여도 다르게 인식하는거 아닌가?


### 테스트
먼저 ESP01이 망가진건 아닌지 다시 테스트 해보았다.

<img src='./img/망가진건없음.PNG'>

일단 망가진건 없었다.

이번엔 AT을 입력해보면서, 숫자로 바꾸어보자.

<img src='./img/AT입력시.PNG'>

ESP01과 아두이노는 ASCII를 따른다.

AT+RST도 동일함.
<img src='./img/AT+RST.PNG'>

이번엔 stm과 ESP01로 테스트 해보자

<img src='./img/stm도똑같다.PNG'>

stm도 동일하게 ASCII이다.

혹시나 해서 uint8_t로도 해보았다.

<img src='./img/uint도동일.PNG'>

마찬가지로 ASCII이다.

특이사항은 HAL_UART_Transmit()은 아래 사진과 같이 c2에 65를 넣고 출력하면 문자로 나온다.

<img src='./img/무조건문자로나오네.PNG'>

### 결론
셋 모두 ASCII를 따른다. 동일한 환경임

그때 본 숫자들은 쓰레기값이다.




# 계속 인터럽트 방식을 파고 들자.

## 결론 AT를 보내서 OK를 받는건 성공했다. 다만 쓰레기도 같이 출력된다.
따라서 strstr()을 사용해야 할듯하다.

피곤하니 내일하자...


```c

/* USER CODE BEGIN Includes */
#include<stdio.h>
#include<string.h>
/* USER CODE END Includes */

(중략)

/* USER CODE BEGIN 0 */
uint8_t BBOX[50];
uint8_t BBOX_count = 0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if(huart == &huart1) {
		HAL_UART_Receive_IT(&huart1, &BBOX[BBOX_count++], 1);
	}
}

/* USER CODE END 0 */



(중략)


/* USER CODE BEGIN 2 */
  HAL_UART_RxCpltCallback(&huart1);
  HAL_UART_Transmit(&huart2, (uint8_t *)("HI\r\n"), strlen("HI\r\n"), 100);
/* USER CODE END 2 */


(중략)


  /* USER CODE BEGIN WHILE */

  uint8_t send_AT[] = "AT\r\n";

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  for(int i = 0; i < sizeof(send_AT); i++) {
		  HAL_UART_Transmit_IT(&huart1, send_AT, sizeof(send_AT));
		  HAL_Delay(100);
	  }



	  HAL_Delay(100);
	  HAL_UART_Transmit(&huart2, BBOX, strlen(BBOX), 100);

	  HAL_Delay(1000);
  }
  /* USER CODE END 3 */

```

<img src='./img/uart1_baud.PNG'>
<img src='./img/uart2_baud.PNG'>

<img src='./img/uart1_NVIC.PNG'>
<img src='./img/uart2_NVIC.PNG'>

<img src='./img/뭔지는모르겠는데성공은얼추한듯.PNG'>

AT를 넣으니 OK가 나왔다.


일단 예상되는 의견은 지금까지 멍청하게 Init()하기 전에 콜백을 선언했었나 보다.

아니면 콜백 함수를 만들고 호출을 안했거나.

사용한 serial tool은 moba X term이다.


근데 AT는 내쪽에서 왜 출력되는걸까??

그리고 c는 어디서 나온거지??

피곤하니까 내일해얏겠다.