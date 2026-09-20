#ifndef LED_H
#define LED_H

#include "main.h"

typedef struct{
GPIO_TypeDef* GPIO_Port;
uint16_t GPIO_Pin;
uint32_t lastToggleTime;
uint32_t blinkInterval;
uint8_t blinking;
} LED_Handle;

void LED_Init(LED_Handle* led, GPIO_TypeDef* port, uint16_t pin);

void LED_On(LED_Handle* led);

void LED_Off(LED_Handle* led);

void LED_TogglePin(LED_Handle* led);

void LED_BlinkStart(LED_Handle* led, uint32_t interval_ms);

void LED_BlinkStop(LED_Handle* led);

void LED_Update(LED_Handle* led);

#endif
