# STM32 

## 목차



## printf()

디버깅을 위해서 출력은 필수이다.

하지만 기본적으로 ST사에서 제공하는 STM32CubeIDE에선 기능이 없다.

따라서 1학기 처럼 USB uart device를 통해 확인을 하기도 했다.
다만, 현재 USB uart device가 없으므로 다른 방안을 찾아야 했다.

[참고자료] https://forum.digikey.com/t/stm32-printf/31174

[준비물] Tera Term
기본적으로 ST보드의 경우 uart1을 자동 on해놓음

<stdio.h>를 통해 printf()를 하면 주변 기기(uart 또는 usart)로 문자열을 전송함.
현재 ST-link(혹은 USB COM포트의 가상 ST-Link)과 연결된 시리얼을 통해 uart를 생성함
따라서 시리얼 모니터(tera term)로 출력을 확인한다.

[다음과 같은 진행을 한다]
- 프로젝트를 생성한다.

- device configuration tool(MX아이콘)을 누른다.

- 좌측 하단에 USART_TX와 USART_RX가 초록색으로 활성화 된 것이 보인다.

- Connectivity에서 USART2를 선택한다.

- Parameter Settings에서 baud rate와 Paraty, Stop Bits, Word Length를 확인한다.(향후 tera term 설정시 같게 해주어야 함)

- 이제 코드를 generate시킨다.

- main.c에서 
```
/* USER CODE BEGIN Includes */
#include<stdio.h>
/* USER CODE END Includes */

(중략)


/* USER CODE BEGIN PFP */
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}
/* USER CODE END PFP */

(중략)

  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  printf("hello\r\n");
	  HAL_Delay(500);
  }
  /* USER CODE END 3 */



```

- 이제 tera term에서 사진과 같이 진행한다.

ST보드와 연결된 포트를 선택한다.

<img src='./img/tera_term_01.PNG'>

Setup > Serial Port

아까 Parameter Settings에서 확인한 세팅으로 바꾼다. 

<img src='./img/tera_term_02.PNG'>

결과

<img src='./img/tera_term_03.PNG'>
