#include "LED.h"

#define LED_H

void LED_Init(LED_Handle* led, GPIO_TypeDef* port, uint16_t pin)
	{
	led->GPIO_Port = port;
	led->GPIO_Pin = pin;
	led->lastToggleTime = 0;
	led->blinkInterval = 0;
	led->blinking = 0;
	}

void LED_On(LED_Handle* led)
	{
		HAL_GPIO_WritePin(led->GPIO_Port, led->GPIO_Pin, GPIO_PIN_SET);
	}

void LED_Off(LED_Handle* led)
	{
		HAL_GPIO_WritePin(led->GPIO_Port, led->GPIO_Pin, GPIO_PIN_RESET);
	}

void LED_TogglePin(LED_Handle* led)
	{
		HAL_GPIO_TogglePin(led->GPIO_Port, led->GPIO_Pin);
	}

void LED_BlinkStart(LED_Handle* led, uint32_t interval_ms)
	{
		led->blinkInterval = interval_ms;
		led->lastToggleTime = HAL_GetTick();
		led->blinking = 1;
	}

void LED_BlinkStop(LED_Handle* led)
	{
		led->blinking = 0;
		LED_Off(led);
	}

void LED_Update(LED_Handle* led)
	{
		if(!led->blinking) return;

		uint32_t now = HAL_GetTick();
		if(now - led->lastToggleTime >= led->blinkInterval)
		{
			LED_TogglePin(led);
			led->lastToggleTime = now;
		}
	}













