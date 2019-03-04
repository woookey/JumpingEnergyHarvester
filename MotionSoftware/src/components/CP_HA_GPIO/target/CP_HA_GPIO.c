#include <CP_HA_GPIO.h>
#include <GPIODefinition.h>
#include <stdint.h>

static struct GPIOStruct pretensionMotorClockwiseDirectionInstance =
{
		.GPIOTypeDef_t = GPIOD,
		.GPIOInitTypeDef_t =
		{
				.Pin = GPIO_PIN_0,
				.Mode = GPIO_MODE_OUTPUT_PP,
				.Pull = GPIO_PULLDOWN,
				.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
		},
};

static struct GPIOStruct pretensionMotorAnticlockwiseDirectionInstance =
{
		.GPIOTypeDef_t = GPIOD,
		.GPIOInitTypeDef_t =
		{
				.Pin = GPIO_PIN_2,
				.Mode = GPIO_MODE_OUTPUT_PP,
				.Pull = GPIO_PULLDOWN,
				.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
		},
};

static struct GPIOStruct pretensionMotorEnableInstance =
{
		.GPIOTypeDef_t = GPIOD,
		.GPIOInitTypeDef_t =
		{
				.Pin = GPIO_PIN_4,
				.Mode = GPIO_MODE_OUTPUT_PP,
				.Pull = GPIO_PULLDOWN,
				.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
		},

};

struct GPIOStruct pretensionMotorPWMInstance =
{
		.GPIOTypeDef_t = GPIOB,
		.GPIOInitTypeDef_t =
		{
			.Pin = GPIO_PIN_5,
			.Mode = GPIO_MODE_AF_PP,
			.Pull = GPIO_PULLDOWN,
			.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
			.Alternate = GPIO_AF2_TIM3,
		},
};

struct GPIOStruct LoggerRxInstance =
{
		.GPIOTypeDef_t = GPIOC,
		.GPIOInitTypeDef_t =
		{
			.Pin = GPIO_PIN_11,
			.Mode = GPIO_MODE_AF_PP,
			.Pull = GPIO_PULLUP,
			.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
			.Alternate = GPIO_AF8_UART4,
		},
};

struct GPIOStruct LoggerTxInstance =
{
		.GPIOTypeDef_t = GPIOC,
		.GPIOInitTypeDef_t =
		{
			.Pin = GPIO_PIN_10,
			.Mode = GPIO_MODE_AF_PP,
			.Pull = GPIO_PULLUP,
			.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
			.Alternate = GPIO_AF8_UART4,
		},
};

CP_HA_GPIO CP_HA_GPIO_pretensionMotorClockwiseDirection = &pretensionMotorClockwiseDirectionInstance;
CP_HA_GPIO CP_HA_GPIO_pretensionMotorAnticlockwiseDirection = &pretensionMotorAnticlockwiseDirectionInstance;
CP_HA_GPIO CP_HA_GPIO_pretensionMotorEnable = &pretensionMotorEnableInstance;
CP_HA_GPIO CP_HA_GPIO_pretensionMotorPWM = &pretensionMotorPWMInstance;
CP_HA_GPIO CP_HA_GPIO_LoggerRx = &LoggerRxInstance;
CP_HA_GPIO CP_HA_GPIO_LoggerTx = &LoggerTxInstance;

void CP_HA_initialiseGPIO(CP_HA_GPIO GPIOInstance)
{
	HAL_GPIO_Init((GPIO_TypeDef*)GPIOInstance->GPIOTypeDef_t,
				(GPIO_InitTypeDef*)&GPIOInstance->GPIOInitTypeDef_t);
}

void CP_HA_turnGPIOOn(CP_HA_GPIO GPIOInstance)
{
	HAL_GPIO_WritePin((GPIO_TypeDef*)GPIOInstance->GPIOTypeDef_t,
			GPIOInstance->GPIOInitTypeDef_t.Pin, GPIO_PIN_SET);
}

void CP_HA_turnGPIOOff(CP_HA_GPIO GPIOInstance)
{
	HAL_GPIO_WritePin((GPIO_TypeDef*)GPIOInstance->GPIOTypeDef_t,
			GPIOInstance->GPIOInitTypeDef_t.Pin, GPIO_PIN_RESET);
}

