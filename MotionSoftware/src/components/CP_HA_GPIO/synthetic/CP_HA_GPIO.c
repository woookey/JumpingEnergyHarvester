#include <CP_HA_GPIO.h>
#include <stdio.h>
#include <string.h>
#include "GPIODefinition.h"

#define PRETENSION_MOTOR_CLOCKWISE_DIRECTION_GPIO_PORT 0
#define PRETENSION_MOTOR_ANTICLOCKWISE_DIRECTION_GPIO_PORT 2
#define PRETENSION_MOTOR_ENABLE_GPIO_PORT 4


static struct GPIOStruct pretensionMotorClockwiseDirectionInstance =
{
		.pin = (uint8_t)PRETENSION_MOTOR_CLOCKWISE_DIRECTION_GPIO_PORT,
		.port = 'D',
};

struct GPIOStruct pretensionMotorAnticlockwiseDirectionInstance =
{
		.pin = (uint8_t)PRETENSION_MOTOR_ANTICLOCKWISE_DIRECTION_GPIO_PORT,
		.port = 'D',
};

struct GPIOStruct pretensionMotorEnableInstance =
{
		.pin = (uint8_t)PRETENSION_MOTOR_ENABLE_GPIO_PORT,
		.port = 'D',

};

CP_HA_GPIO pretensionMotorClockwiseDirection = &pretensionMotorClockwiseDirectionInstance;
CP_HA_GPIO pretensionMotorAnticlockwiseDirection = &pretensionMotorAnticlockwiseDirectionInstance;
CP_HA_GPIO pretensionMotorEnable = &pretensionMotorEnableInstance;



void CP_HA_initialiseGPIO(CP_HA_GPIO GPIOInstance)
{
	printf("GPIO %c%d constructed\n", GPIOInstance->port, GPIOInstance->pin);
}

void CP_HA_turnGPIOOn(CP_HA_GPIO GPIOInstance)
{
	printf("GPIO %c%d switched on\n", GPIOInstance->port, GPIOInstance->pin);
}

void CP_HA_turnGPIOOff(CP_HA_GPIO GPIOInstance)
{
	printf("GPIO %c%d switched off\n", GPIOInstance->port, GPIOInstance->pin);
}
