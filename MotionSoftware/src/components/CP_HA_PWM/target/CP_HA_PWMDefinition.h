#ifndef CP_HA_PWM_DEFINITION_H
#define CP_HA_PWM_DEFINITION_H

#include <stm32f4xx_hal_dma.h>
#include <stm32f4xx_hal_tim.h>

struct PWMStruct
{
	TIM_HandleTypeDef htim;
};

#endif
