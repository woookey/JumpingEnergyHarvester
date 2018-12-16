#ifndef GPIO_DEFINITION_H_
#define GPIO_DEFINITION_H_

#include <stm32f407xx.h>
#include <stm32f4xx_hal_gpio.h>

struct GPIOStruct
{
	GPIO_TypeDef* GPIOTypeDef_t;
	GPIO_InitTypeDef GPIOInitTypeDef_t;
};

#endif
