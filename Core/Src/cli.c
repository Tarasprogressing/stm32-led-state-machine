#include "cli.h"
#include <string.h>
#include <stdio.h>


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
				"mode 3 \r\n");
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
	else
	{
		uart_send("\r\nUnknown command\r\n");
	}
	}
