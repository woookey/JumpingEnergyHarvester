#ifndef ADC_DEFINITION_TARGET_H
#define ADC_DEFINITION_TARGET_H

#include <stm32f4xx_hal_dma.h>
#include <stm32f4xx_hal_adc.h>

struct ADCStruct
{
	ADC_HandleTypeDef ADCHandle;
	ADC_ChannelConfTypeDef ADCChannelConfig;
};

#endif
