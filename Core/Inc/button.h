#ifndef BUTTON_H
#define BUTTON_H

#include "main.h"

typedef enum
{
	BUTTON_EVENT_NONE,
	BUTTON_EVENT_SHORT_PRESS,
	BUTTON_EVENT_LONG_PRESS
} ButtonEvent_t;

void Button_Init(GPIO_TypeDef *port, uint16_t pin);

void Button_Update(void);

ButtonEvent_t Button_GetEvent(void);

#endif
