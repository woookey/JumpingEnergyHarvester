#include <CP_HA_GPIO.h>
#include <GPIODefinition.h>
#include <stdint.h>

static struct GPIOStruct pretensionMotorClockwiseDirectionInstance =
{
		.GPIOTypeDef_t = GPIOD,
		.GPIOInitTypeDef_t =
		{
				.Pin = 0,
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
				.Pin = 2,
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
				.Pin = 4,
				.Mode = GPIO_MODE_OUTPUT_PP,
				.Pull = GPIO_PULLDOWN,
				.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
		},

};

static struct GPIOStruct pretensionMotorPWMInstance =
{
		.GPIOTypeDef_t = GPIOB,
		.GPIOInitTypeDef_t =
		{
			.Pin = 5,
			.Mode = GPIO_MODE_AF_PP,
			.Pull = GPIO_PULLDOWN,
			.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
			.Alternate = GPIO_AF2_TIM3,
		},
};



CP_HA_GPIO CP_HA_GPIO_pretensionMotorClockwiseDirection = &pretensionMotorClockwiseDirectionInstance;
CP_HA_GPIO CP_HA_GPIO_pretensionMotorAnticlockwiseDirection = &pretensionMotorAnticlockwiseDirectionInstance;
CP_HA_GPIO CP_HA_GPIO_pretensionMotorEnable = &pretensionMotorEnableInstance;
CP_HA_GPIO CP_HA_GPIO_pretensionMotorPWM = &pretensionMotorPWMInstance;

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

