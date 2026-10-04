#include "cli.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


extern UART_HandleTypeDef huart2;
extern uint8_t ledMode;

void uart_send(char *msg)
  {
  HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
  }

void CommandProcessor(char *cmd)
	{

	if(strcmp(cmd, "mode 0") == 0)
				{
					ledMode = 0;
				}
	else if(strcmp(cmd, "mode 1") == 0)
				{
					ledMode = 1;
				}
	else if(strcmp(cmd, "mode 2") == 0)
				{
					ledMode = 2;
				}
	else if(strcmp(cmd, "mode 3") == 0)
				{
					ledMode = 3;
				}
	else if(strcmp(cmd, "help") == 0)
	{
		uart_send(
				"\r\n Available commands: \r\n "
				"help \r\n"
				"status \r\n"
				"mode 0 \r\n"
				"mode 1 \r\n"
				"mode 2 \r\n"
				"mode 3 \r\n"
				"blink N DELALY");
	}

	else if(strcmp(cmd, "status") == 0)
	{
		char msg[64];
		sprintf(msg, "\r\nCurrent mode: %d\r\n" "UART: Interrupt mode\r\n" "Baudrate: 38400\r\n", ledMode);

		uart_send(msg);
	}

	else if(strcmp(cmd, "mode") == 0)
	{
		if(ledMode == 0)
		{
			uart_send("Current mode: 0 \r\n");
		}
		if(ledMode == 1)
				{
					uart_send("Current mode: 1 \r\n");
				}
		if(ledMode == 2)
				{
					uart_send("Current mode: 2 \r\n");
				}
		if(ledMode == 3)
				{
					uart_send("Current mode: 3 \r\n");
				}
	}
	else if(strncmp(cmd, "blink", 5) == 0)
	{
		// шукаємо перший пробіл після "блінк"

		char *space1 = strchr(cmd, ' ');
		if(space1 == NULL)
		{
			uart_send("error: missing parameters\r\n");
			return;
		}

		// перший аргумент (кількість блимів)
		char *arg1 = space1 + 1;
		while(*arg1 == ' ')
		{
			arg1++;
		}

		if(*arg1 == '\0')
		{
			uart_send("error: missing first parameter \r\n");
			return;
		}

		// шукаємопробіл між першим і другим параметром

		char *space2 = strchr(arg1, ' ');
		if(space2 == NULL)
		{
			uart_send("error: missing second parameter\r\n");
			return;
		}

		*space2 = '\0';

		// другий аргумент (затримка)

		char *arg2 = space2 + 1;
		while(*arg2 == ' ')
		{
			arg2++;
		}

		if(*arg2 == '\0')
		{
			uart_send("error: missing second parameter\r\n");
			return;
		}

		// перевірка, що перший параметр - тільки цифри
		for(int i = 0; arg1[i] != '\0'; i++)
		{

		if(arg1[i] < '0' || arg1[i] > '9')
		{
			uart_send("error: invalid the first number\r\n");
			return;
		}
		}

		// перевірка, що другий параметр - тільки цифри

		for(int i = 0; arg2[i] != '\0'; i++)
				{

				if(arg2[i] < '0' || arg2[i] > '9')
				{
					uart_send("error: invalid the second number\r\n");
					return;
				}
				}

		int cnt = atoi(arg1);
		int delay = atoi(arg2);

		if(cnt < 1 || cnt > 5)
		{
			uart_send("error: count is out of range\r\n");
			return;
		}

		if(delay < 10 || delay > 2000)
		{
			uart_send("error: delay is out of range\r\n");
			return;
		}

		for(int blk = 0; blk < cnt; blk++)
		{
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);
			HAL_Delay(delay);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);
			HAL_Delay(delay);

			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);
		}

		uart_send("Blink is done\r\n");
	}

	else
	{
		uart_send("\r\nUnknown command\r\n");
	}
	}










