#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "esp.h"
#include "usart.h"


typedef struct _cb_data_t
{
    uint8_t buf[MAX_ESP_RX_BUFFER];
    uint16_t length;
}cb_data_t;

static char ip_addr[16];
static char response[MAX_ESP_RX_BUFFER];

static uint8_t is_run;
static uint8_t client_list[MAX_ESP_CLIENT_NUM];

static uint8_t data;
static cb_data_t cb_data;
UART_HandleTypeDef huart3;

static int esp_at_command(uint8_t *cmd, uint8_t *resp, uint16_t *length, int16_t time_out)
{
    *length = 0;
    memset(resp, 0x00, MAX_UART_RX_BUFFER);
    memset(&cb_data, 0x00, sizeof(cb_data_t));
    if(HAL_UART_Transmit(&huart3, cmd, strlen((char *)cmd), 100) != HAL_OK)
        return -1;

    while(time_out > 0)
    {
        if(cb_data.length >= MAX_UART_RX_BUFFER)
            return -2;
        else if(strstr((char *)cb_data.buf, "ERROR") != NULL)
            return -3;
        else if(strstr((char *)cb_data.buf, "OK") != NULL)
        {
            memcpy(resp, cb_data.buf, cb_data.length);
            *length = cb_data.length;
            break;
        }

        time_out -= 10;
        HAL_Delay(10);
    }

    HAL_Delay(500);
    return 0;
}

static int esp_reset(void)
{
    uint16_t length = 0;


    return esp_at_command((uint8_t *)"AT\r\n", (uint8_t *)response, &length, 1000);
}

static int esp_get_ip_addr(uint8_t is_debug)
{
    if(strlen(ip_addr) != 0)
    {
        if(strcmp(ip_addr, "0.0.0.0") == 0)
            return -1;
    }
    else
    {
        uint16_t length;
        if(esp_at_command((uint8_t *)"AT+CIPSTA?\r\n", (uint8_t *)response, &length, 1000) != 0)
            printf("ip_state command fail\r\n");
        else
        {
            char *line = strtok(response, "\r\n");

            if(is_debug)
            {
                for(int i = 0 ; i < length ; i++)
                    printf("%c", response[i]);
            }

            while(line != NULL)
            {
                if(strstr(line, "ip:") != NULL)
                {
                    char *ip;

                    strtok(line, "\"");
                    ip = strtok(NULL, "\"");
                    if(strcmp(ip, "0.0.0.0") != 0)
                    {
                        memset(ip_addr, 0x00, sizeof(ip_addr));
                        memcpy(ip_addr, ip, strlen(ip));
                        return 0;
                    }
                }
                line = strtok(NULL, "\r\n");
            }
        }

        return -1;
    }

    return 0;
}

static int request_ip_addr(uint8_t is_debug)
{
    uint16_t length = 0;

    if(esp_at_command((uint8_t *)"AT+CIFSR\r\n", (uint8_t *)response, &length, 1000) != 0)
        printf("request ip_addr command fail\r\n");
    else
    {
        char *line = strtok(response, "\r\n");

        if(is_debug)
        {
            for(int i = 0 ; i < length ; i++)
                printf("%c", response[i]);
        }

        while(line != NULL)
        {
            if(strstr(line, "CIFSR:STAIP") != NULL)
            {
                char *ip;

                strtok(line, "\"");
                ip = strtok(NULL, "\"");
                if(strcmp(ip, "0.0.0.0") != 0)
                {
                    memset(ip_addr, 0x00, sizeof(ip_addr));
                    memcpy(ip_addr, ip, strlen(ip));
                    return 0;
                }
            }
            line = strtok(NULL, "\r\n");
        }
    }

    return -1;
}


static int esp_send_messge(int client_id, char *message, char *response, uint16_t *length)
{
    char at_cmd[32] = {0, };

    sprintf(at_cmd, "AT+CIPSEND=%d,%d\r\n", client_id, strlen(message));
    if(esp_at_command((uint8_t *)at_cmd, (uint8_t *)response, length, 1000) == 0)
    {
        esp_at_command((uint8_t *)message, (uint8_t *)response, length, 1000);
        // printf("message = %s\r\n", message);
    }
    return 0;
}


int drv_esp_init(void)
{
    huart3.Instance = USART3;
    huart3.Init.BaudRate = 9600;
    huart3.Init.WordLength = UART_WORDLENGTH_8B;
    huart3.Init.StopBits = UART_STOPBITS_1;
    huart3.Init.Parity = UART_PARITY_NONE;
    huart3.Init.Mode = UART_MODE_TX_RX;
    huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart3.Init.OverSampling = UART_OVERSAMPLING_16;
    if(HAL_UART_Init(&huart3) != HAL_OK)
        return -1;

    memset(ip_addr, 0x00, sizeof(ip_addr));
    HAL_UART_Receive_IT(&huart3, &data, 1);

    return esp_reset();
}

int drv_esp_test_command(void)
{
    char command[MAX_UART_COMMAND_LEN];
    uint16_t length = 0;

    while(1)
    {
		drv_uart_tx_buffer((uint8_t *)"esp>", 4);

        memset(command, 0x00, sizeof(command));
		if(drv_uart_rx_buffer((uint8_t *)command, MAX_UART_COMMAND_LEN) == 0)
			continue;

        if(strcmp(command, "help") == 0)
        {
            printf("============================================================\r\n");
            printf("* help                    : help\r\n");
            printf("* quit                    : esp test exit\r\n");
            printf("* reset                   : esp restart\r\n");
            printf("* version                 : esp firmware version\r\n");
            printf("* ap_scan                 : scan ap list\r\n");
            printf("* ap_conn <ssid> <passwd> : connect ap & obtain ip addr\r\n");
            printf("* ap_disconnect           : disconnect ap\r\n");
            printf("* ip_state                : display ip addr\r\n");
            printf("* request_ip              : obtain ip address\r\n");
            printf("* esp_server              : esp server start\r\n");
            printf("* AT+<XXXX>               : AT COMMAND\r\n");
            printf("*\r\n");
            printf("* More <AT COMMAND> information is available on the following website\r\n");
            printf("*  - https://docs.espressif.com/projects/esp-at/en/latest/AT_Command_Set\r\n");
            printf("============================================================\r\n");
        }
        else if(strcmp(command, "quit") == 0)
        {
            printf("esp test exit\r\n");
            break;
        }
        else if(strcmp(command, "reset") == 0)
        {
            printf("esp reset... ");
            if(esp_reset() == 0)
                printf("OK\r\n");
            else
                printf("fail\r\n");
        }
        else if(strcmp(command, "version") == 0)
        {
            printf("esp firmware version\r\n");
            if(esp_at_command((uint8_t *)"AT+GMR\r\n", (uint8_t *)response, &length, 1000) != 0)
                printf("ap scan command fail\r\n");
            else
            {
                for(int i = 0 ; i < length ; i++)
                    printf("%c", response[i]);
            }
        }
        else if(strcmp(command, "ap_scan") == 0)
        {
            printf("ap scan...\r\n");
            if(esp_at_command((uint8_t *)"AT+CWLAP\r\n", (uint8_t *)response, &length, 5000) != 0)
                printf("ap scan command fail\r\n");
            else
            {
                for(int i = 0 ; i < length ; i++)
                    printf("%c", response[i]);
            }
        }
        else if(strncmp(command, "ap_conn", strlen("ap_conn")) == 0)
        {
            char at_cmd[MAX_UART_COMMAND_LEN];
            char *ssid   = strtok(&command[strlen("ap_conn")+1], " ");
            char *passwd = strtok(NULL, " ");

            if(ssid == NULL || passwd == NULL)
            {
                printf("invalid command : ap_conn <ssid> <passwd>\r\n");
                continue;
            }

            memset(at_cmd, 0x00, sizeof(at_cmd));
            sprintf(at_cmd, "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid,passwd);
            if(esp_at_command((uint8_t *)at_cmd, (uint8_t *)response, &length, 5000) != 0)
                printf("ap scan command fail\r\n");
            else
            {
                for(int i = 0 ; i < length ; i++)
                    printf("%c", response[i]);
            }
        }
        else if(strcmp(command, "ap_disconnect") == 0)
        {
            if(esp_at_command((uint8_t *)"AT+CWQAP\r\n", (uint8_t *)response, &length, 1000) != 0)
                printf("ap connected info command fail\r\n");
            else
            {
                for(int i = 0 ; i < length ; i++)
                    printf("%c", response[i]);

                memset(ip_addr, 0x00, sizeof(ip_addr));
            }
        }
        else if(strcmp(command, "ip_state") == 0)
        {
            if(esp_at_command((uint8_t *)"AT+CWJAP?\r\n", (uint8_t *)response, &length, 1000) != 0)
                printf("ap connected info command fail\r\n");
            else
            {
                for(int i = 0 ; i < length ; i++)
                    printf("%c", response[i]);
            }
            printf("\r\n");

            if(esp_get_ip_addr(1) == 0)
                printf("ip_addr = [%s]\r\n", ip_addr);
        }
        else if(strcmp(command, "request_ip") == 0)
        {
            request_ip_addr(1);
        }
        else if(strcmp(command, "esp_server") == 0)
        {
            if(start_esp_server() != 0)
                printf("esp server start fail\r\n");
        }
        else if(strncmp(command, "AT+", 3) == 0)
        {
            uint8_t at_cmd[MAX_UART_COMMAND_LEN];

            memset(at_cmd, 0x00, sizeof(at_cmd));
            sprintf((char *)at_cmd, "%s\r\n", command);
            if(esp_at_command(at_cmd, (uint8_t *)response, &length, 1000) != 0)
                printf("AT+ command fail\r\n");
            else
            {
                for(int i = 0 ; i < length ; i++)
                    printf("%c", response[i]);
            }
        }
        else
        {
            printf("unkwon command\r\n");
        }
    }

    return 0;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART3)
    {
        if(cb_data.length < MAX_ESP_RX_BUFFER)
            cb_data.buf[cb_data.length++] = data;
        else
            HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
        HAL_UART_Receive_IT(huart, &data, 1);
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == GPIO_PIN_0)
    {
        if(is_run)
        {
            printf("ISR :: %s() : esp server stop...\r\n", __func__);
            is_run = 0;
        }
    }
}
