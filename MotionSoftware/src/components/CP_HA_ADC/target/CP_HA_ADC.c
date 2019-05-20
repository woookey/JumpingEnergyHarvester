#include <stdint.h>
#include <CP_HA_ADC.h>
#include "ADCDefinition.h"

static struct ADCStruct AngularSensorJoint1Instance =
{
		.ADCHandle =
		{
				.Instance = ADC1,
				.Init =
				{
						.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4,
						.Resolution = ADC_RESOLUTION_8B,
						.DataAlign = ADC_DATAALIGN_RIGHT,
						.ScanConvMode = DISABLE, // from here changed
						.EOCSelection = DISABLE,
						.ContinuousConvMode = DISABLE,
						.NbrOfConversion = (uint32_t)1,
						.DiscontinuousConvMode = DISABLE,
						.NbrOfDiscConversion = (uint32_t)0,
						.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1,
						.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE,
						.DMAContinuousRequests = DISABLE,
				},
		},
		.ADCChannelConfig =
		{
				.Channel = ADC_CHANNEL_2,
				.Rank = (uint32_t)1,
				.SamplingTime = ADC_SAMPLETIME_480CYCLES,
				.Offset = (uint32_t)0,
		},
};

static struct ADCStruct AngularSensorJoint2Instance =
{
		.ADCHandle =
		{
				.Instance = ADC2,
				.Init =
				{
						.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4,
						.Resolution = ADC_RESOLUTION_8B,
						.DataAlign = ADC_DATAALIGN_RIGHT,
						.ScanConvMode = ENABLE, // from here changed
						.EOCSelection = DISABLE,
						.ContinuousConvMode = ENABLE,
						.NbrOfConversion = (uint32_t)2,
						.DiscontinuousConvMode = DISABLE,
						.NbrOfDiscConversion = (uint32_t)0,
						.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1,
						.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE,
						.DMAContinuousRequests = DISABLE,
				},
		},
		.ADCChannelConfig =
		{
				.Channel = ADC_CHANNEL_4,
				.Rank = (uint32_t)1,
				.SamplingTime = ADC_SAMPLETIME_480CYCLES,
				.Offset = (uint32_t)0,
		},
};

static struct ADCStruct AngularSensorEquilibriumMotor =
{
		.ADCHandle =
		{
				.Instance = ADC2,
				.Init =
				{
						.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4,
						.Resolution = ADC_RESOLUTION_8B,
						.DataAlign = ADC_DATAALIGN_RIGHT,
						.ScanConvMode = ENABLE, // from here changed
						.EOCSelection = DISABLE,
						.ContinuousConvMode = ENABLE,
						.NbrOfConversion = (uint32_t)2,
						.DiscontinuousConvMode = DISABLE,
						.NbrOfDiscConversion = (uint32_t)0,
						.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1,
						.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE,
						.DMAContinuousRequests = DISABLE,
				},
		},
		.ADCChannelConfig =
		{
				.Channel = ADC_CHANNEL_6,
				.Rank = (uint32_t)2,
				.SamplingTime = ADC_SAMPLETIME_480CYCLES,
				.Offset = (uint32_t)0,
		},
};

static struct ADCStruct AngularSensorPretensionMotor =
{
		.ADCHandle =
		{
				.Instance = ADC3,
				.Init =
				{
						.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4,
						.Resolution = ADC_RESOLUTION_8B,
						.DataAlign = ADC_DATAALIGN_RIGHT,
						.ScanConvMode = DISABLE, // from here changed
						.EOCSelection = DISABLE,
						.ContinuousConvMode = DISABLE,
						.NbrOfConversion = (uint32_t)1,
						.DiscontinuousConvMode = DISABLE,
						.NbrOfDiscConversion = (uint32_t)0,
						.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1,
						.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE,
						.DMAContinuousRequests = DISABLE,
				},
		},
		.ADCChannelConfig =
		{
				.Channel = ADC_CHANNEL_10,
				.Rank = (uint32_t)1,
				.SamplingTime = ADC_SAMPLETIME_480CYCLES,
				.Offset = (uint32_t)0,
		},
};

CP_HA_ADC CP_HA_ADC_angularSensorJoint1 = &AngularSensorJoint1Instance;
CP_HA_ADC CP_HA_ADC_angularSensorJoint2 = &AngularSensorJoint2Instance;
CP_HA_ADC CP_HA_ADC_angularSensorPretensionMotor = &AngularSensorPretensionMotor;
CP_HA_ADC CP_HA_ADC_angularSensorEquilibriumMotor = &AngularSensorEquilibriumMotor;

void CP_HA_initialiseADC(CP_HA_ADC ADCInstance)
{
	HAL_ADC_Init(&ADCInstance->ADCHandle);
	HAL_ADC_ConfigChannel(&ADCInstance->ADCHandle, &ADCInstance->ADCChannelConfig);//ADC_HandleTypeDef* hadc, ADC_ChannelConfTypeDef* sConfig
}

uint8_t CP_HA_readADC(CP_HA_ADC ADCInstance)
{
	uint32_t ADCValue;
	/**
	 * *** Polling mode IO operation ***
     =================================
     [..]
       (+) Start the ADC peripheral using HAL_ADC_Start()
       (+) Wait for end of conversion using HAL_ADC_PollForConversion(), at this stage
           user can specify the value of timeout according to his end application
       (+) To read the ADC converted values, use the HAL_ADC_GetValue() function.
       (+) Stop the ADC peripheral using HAL_ADC_Stop()
	 */
	HAL_ADC_Start(&ADCInstance->ADCHandle);
	if(HAL_ADC_PollForConversion(&ADCInstance->ADCHandle, 1000000)==HAL_OK) // timeout 3
	{
		ADCValue = HAL_ADC_GetValue(&ADCInstance->ADCHandle);
	}
	HAL_ADC_Stop(&ADCInstance->ADCHandle);
	return (uint8_t)ADCValue;
}

/*void CP_HA_readMultipleADC(CP_HA_ADC ADCInstance, uint8_t* returns, uint8_t conversion_number)
{
	HAL_ADC_Start(&ADCInstance->ADCHandle);
	for (uint8_t i = 0; i < conversion_number; i++)
	{
		if(HAL_ADC_PollForConversion(&ADCInstance->ADCHandle, 1000000)==HAL_OK) // timeout 3
		{
			returns[i] = HAL_ADC_GetValue(&ADCInstance->ADCHandle);
		}
	}
	HAL_ADC_Stop(&ADCInstance->ADCHandle);
}*/
