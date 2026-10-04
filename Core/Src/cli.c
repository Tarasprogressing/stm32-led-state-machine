#include "cli.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


extern UART_HandleTypeDef huart2;
extern uint8_t ledMode;
extern uint32_t blinkTarget;
extern uint32_t blinkCurrent;
extern uint32_t blinkDelay;


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
	else if(strcmp(cmd, "mode 4") == 0)
			{
				ledMode = 4;
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
		sprintf(msg, "\r\nCurrent mode: %d\r\n" "UART: Interrupt mode\r\n" "Baud rate: 38400\r\n", ledMode);

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
	else if(ledMode == 4)
	{
	uart_send("ENTER MODE 4\r\n");
	char msg[64];

	sprintf(msg, "target=%lu delay=%lu\r\n", blinkTarget, blinkDelay);

	uart_send(msg);
	}

	else if(strncmp(cmd, "blink ", 6) == 0)
	{
	char *arg1;
	char *arg2;

	arg1 = strtok(cmd + 6, " ");
	arg2 = strtok(NULL, " ");

	if(arg1 == NULL || arg2 == NULL)
	{
	uart_send("Usage: blink N DELAY\r\n");
	return;
	}

	int cnt = atoi(arg1);
	int delay = atoi(arg2);

	if(cnt < 1 || cnt > 10)
	{
	uart_send("Error: invalid count\r\n");
	return;
	}

	if(delay < 10 || delay > 5000)
	{
	uart_send("Error: invalid delay\r\n");
	return;
	}

	blinkTarget = cnt;
	blinkCurrent = 0;
	blinkDelay = delay;

	ledMode = 4;

	uart_send("Blink mode started\r\n");
	}
	}










