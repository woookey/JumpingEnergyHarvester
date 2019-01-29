#include <CP_HA_LED.h>
#include <LEDType.h>

struct LEDType CPUActivityLEDInstance =
{
		.GPIOTypeDef_t = GPIOD,
		.GPIOInitTypeDef_t =
		{
				.Pin = GPIO_PIN_12,
				.Mode = GPIO_MODE_OUTPUT_PP,
				.Pull = GPIO_PULLUP,
				.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
		},
};

struct LEDType powerOnIndicationLEDInstance =
{
		.GPIOTypeDef_t = GPIOC,
		.GPIOInitTypeDef_t =
		{
				.Pin = GPIO_PIN_15,
				.Mode = GPIO_MODE_OUTPUT_PP,
				.Pull = GPIO_PULLUP,
				.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
		},
};

struct LEDType executingIndicationLEDInstance =
{
		.GPIOTypeDef_t = GPIOC,
		.GPIOInitTypeDef_t =
		{
				.Pin = GPIO_PIN_1,
				.Mode = GPIO_MODE_OUTPUT_PP,
				.Pull = GPIO_PULLUP,
				.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
		},
};

struct LEDType safetyStopIndicationLEDInstance =
{
		.GPIOTypeDef_t = GPIOC,
		.GPIOInitTypeDef_t =
		{
				.Pin = GPIO_PIN_2,
				.Mode = GPIO_MODE_OUTPUT_PP,
				.Pull = GPIO_PULLUP,
				.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
		},
};

CP_HA_LEDStruct CPUActivityLED = &CPUActivityLEDInstance;
CP_HA_LEDStruct powerOnIndicationLED = &powerOnIndicationLEDInstance;
CP_HA_LEDStruct executingIndicationLED = &executingIndicationLEDInstance;
CP_HA_LEDStruct safetyStopIndicationLED = &safetyStopIndicationLEDInstance;

void CP_HA_LEDConstruct(CP_HA_LEDStruct LEDInstance)
{

	HAL_GPIO_Init((GPIO_TypeDef*)LEDInstance->GPIOTypeDef_t,
			(GPIO_InitTypeDef*)&LEDInstance->GPIOInitTypeDef_t);
}

void CP_HA_LEDSwitchOn(CP_HA_LEDStruct LEDInstance)
{
	HAL_GPIO_WritePin((GPIO_TypeDef*)LEDInstance->GPIOTypeDef_t,
			LEDInstance->GPIOInitTypeDef_t.Pin, GPIO_PIN_SET);
}

void CP_HA_LEDSwitchOff(CP_HA_LEDStruct LEDInstance)
{
	HAL_GPIO_WritePin((GPIO_TypeDef*)LEDInstance->GPIOTypeDef_t,
				LEDInstance->GPIOInitTypeDef_t.Pin, GPIO_PIN_RESET);
}

