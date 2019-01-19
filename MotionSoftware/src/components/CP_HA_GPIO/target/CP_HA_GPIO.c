#include <CP_HA_GPIO.h>
#include <GPIODefinition.h>
#include <stm32f4xx_hal_gpio.h>
#include <stdint.h>

struct GPIOStruct pretensionMotorClockwiseDirectionInstance =
{
		.GPIOTypeDef_t = GPIOD,
		.GPIOInitTypeDef_t =
		{
				.Pin = 0,
				.Mode = GPIO_MODE_OUTPUT_PP,
				.Pull = GPIO_PULLUP,
				.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
		},
};

struct GPIOStruct pretensionMotorAnticlockwiseDirectionInstance =
{
		.GPIOTypeDef_t = GPIOD,
		.GPIOInitTypeDef_t =
		{
				.Pin = 1,
				.Mode = GPIO_MODE_OUTPUT_PP,
				.Pull = GPIO_PULLUP,
				.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
		},
};

struct GPIOStruct pretensionMotorEnableInstance =
{
		.GPIOTypeDef_t = GPIOD,
		.GPIOInitTypeDef_t =
		{
				.Pin = 2,
				.Mode = GPIO_MODE_OUTPUT_PP,
				.Pull = GPIO_PULLUP,
				.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
		},

};

CP_HA_GPIO pretensionMotorClockwiseDirection = &pretensionMotorClockwiseDirectionInstance;
CP_HA_GPIO pretensionMotorAnticlockwiseDirection = &pretensionMotorAnticlockwiseDirectionInstance;
CP_HA_GPIO pretensionMotorEnable = &pretensionMotorEnableInstance;


void CP_HA_initialiseGPIO(CP_HA_GPIO GPIOInstance)
{
	GPIOInstance->GPIOTypeDef_t->MODER |= (1 << (GPIOInstance->GPIOInitTypeDef_t.Pin << 1));
	GPIOInstance->GPIOTypeDef_t->OSPEEDR |= (3 << (GPIOInstance->GPIOInitTypeDef_t.Pin << 1));
}

void CP_HA_turnGPIOOn(CP_HA_GPIO GPIOInstance)
{
	GPIOInstance->GPIOTypeDef_t->BSRR |= (1 << GPIOInstance->GPIOInitTypeDef_t.Pin);
}

void CP_HA_turnGPIOOff(CP_HA_GPIO GPIOInstance)
{
	GPIOInstance->GPIOTypeDef_t->BSRR |= (1 << (GPIOInstance->GPIOInitTypeDef_t.Pin+(uint16_t)16));
}

