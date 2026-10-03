#include "button.h"

#define DEBOUNCE_TIME 30
#define LONG_PRESS_TIME 1000

static GPIO_TypeDef *buttonPort;
static uint16_t buttonPin;

static uint8_t previousState;
static uint8_t currentState;

static uint32_t pressTime;
static uint32_t releaseTime;
static uint32_t pressDuration;

static ButtonEvent_t buttonEvent;

void Button_Init(GPIO_TypeDef *port, uint16_t pin)
{
	buttonPort = port;
	buttonPin = pin;

	currentState = HAL_GPIO_ReadPin(buttonPort, buttonPin);

	previousState = currentState;
}

void Button_Update(void)
{
	 previousState = currentState;
	 currentState = HAL_GPIO_ReadPin(buttonPort, buttonPin);


	  if(previousState && !currentState)
	  {
		  HAL_Delay(DEBOUNCE_TIME);

		  currentState = HAL_GPIO_ReadPin(buttonPort, buttonPin);

		  if(!currentState)
		  {
		  pressTime = HAL_GetTick();
		  }
	  }

		  if(!previousState && currentState)
		  {

			  HAL_Delay(DEBOUNCE_TIME);

			  currentState = HAL_GPIO_ReadPin(buttonPort, buttonPin);

			  if(currentState)
			  {

			  releaseTime = HAL_GetTick();

			  pressDuration = releaseTime - pressTime;

			  }


		  if(pressDuration < LONG_PRESS_TIME)
		  {
				  buttonEvent = BUTTON_EVENT_SHORT_PRESS;
		  }

		  else
		  {
			  buttonEvent = BUTTON_EVENT_LONG_PRESS;
		  }
		  }
}

ButtonEvent_t Button_GetEvent(void)
{
	ButtonEvent_t event = buttonEvent;

	buttonEvent = BUTTON_EVENT_NONE;

	return event;
}
