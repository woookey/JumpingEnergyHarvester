#ifndef TARGET_LED_TYPE_H
#define TARGET_LED_TYPE_H

#include <stm32f407xx.h>
#include <stm32f4xx_hal_gpio.h>

struct LEDType
{
	GPIO_TypeDef* GPIOTypeDef_t;
	GPIO_InitTypeDef GPIOInitTypeDef_t;
};

#endif
