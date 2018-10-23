#ifndef CP_HA_DIGITAL_INPUT_TYPE_TARGET_H
#define CP_HA_DIGITAL_INPUT_TYPE_TARGET_H

#include <stm32f407xx.h>
#include <stm32f4xx_hal_gpio.h>

struct DigitalInputType
{
	GPIO_TypeDef* GPIOTypeDef_t;
	GPIO_InitTypeDef GPIOInitTypeDef_t;
};

#endif
