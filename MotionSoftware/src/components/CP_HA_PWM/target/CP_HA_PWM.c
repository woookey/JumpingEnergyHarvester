#include <CP_HA_PWMDefinition.h>
#include <CP_HA_PWM.h>
#include <stm32f4xx_hal_rcc.h>

static struct PWMStruct pretensionMotorPWMInstance =
{
	.htim =
	{
		.Instance = TIM3,
		.Init =
		{
			.Prescaler = (uint32_t)0,
			.CounterMode = TIM_COUNTERMODE_UP,
			.Period = (uint32_t)0, // TODO: Shouldnt period be non-zero?
			.ClockDivision = TIM_CLOCKDIVISION_DIV1,
			.RepetitionCounter = (uint32_t)0,
		},
		//DMA_HandleTypeDef - ignore DMA
		.Channel = HAL_TIM_ACTIVE_CHANNEL_2,
		.Lock = HAL_UNLOCKED,
		.State = HAL_TIM_STATE_RESET,
	},

	.clockConfig =
	{
			.ClockSource = TIM_CLOCKSOURCE_INTERNAL,
			.ClockPolarity = TIM_CLOCKPOLARITY_RISING,
			.ClockPrescaler = TIM_CLOCKPRESCALER_DIV1,
			.ClockFilter = TIM_CLEARINPUTSOURCE_NONE,
	},

	.outputCompareConfig =
	{
			.OCMode = TIM_OCMODE_PWM1,
			.Pulse = (uint32_t)50000, // TODO: How is Pulse related to Period of the timer?
			.OCPolarity = TIM_OCPOLARITY_HIGH,
			//.OCNPolarity = , not valid for TIM3
			.OCFastMode = TIM_OCFAST_ENABLE,
			//.OCIdleState = , not valid for TIM3
			//.OCNIdleState = , not valid for TIM3
	}
};


CP_HA_PWM CP_HA_PWM_pretensionMotorPWM = &pretensionMotorPWMInstance;

void CP_HA_initialisePWM(CP_HA_PWM PWMInstance)
{
	HAL_StatusTypeDef result;
	result = HAL_TIM_PWM_Init(&PWMInstance->htim);
	__HAL_RCC_TIM3_CLK_ENABLE();
	HAL_TIM_ConfigClockSource(&PWMInstance->htim, &PWMInstance->clockConfig);
	HAL_TIM_PWM_ConfigChannel(&PWMInstance->htim, &PWMInstance->outputCompareConfig, TIM_CHANNEL_2);
}

void CP_HA_startPWM(CP_HA_PWM PWMInstance)
{
	HAL_TIM_PWM_Start(&PWMInstance->htim, TIM_CHANNEL_2);
}
