#ifndef GPIO_DEFINITION_TARGET_H
#define GPIO_DEFINITION_TARGET_H

#include <stm32f4xx_hal_gpio.h>

struct GPIOStruct
{
	GPIO_TypeDef* GPIOTypeDef_t;
	GPIO_InitTypeDef GPIOInitTypeDef_t;
};

#endif
