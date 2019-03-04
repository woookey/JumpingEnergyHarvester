#include <CP_HA_GPIO.h>
#include <stdio.h>
#include <string.h>
#include "GPIODefinition.h"

/**
 * Port D
 */
#define PRETENSION_MOTOR_CLOCKWISE_DIRECTION_GPIO_PORT 0
#define PRETENSION_MOTOR_ANTICLOCKWISE_DIRECTION_GPIO_PORT 2
#define PRETENSION_MOTOR_ENABLE_GPIO_PORT 4

/**
 * PORT B
 */
#define PRETENSION_MOTOR_PWM_GPIO_PORT 5
#define JOINT1_SENSOR_GPIO_PORT 2

/**
 * PORT C
 */
#define LOGGER_RX_GPIO_PORT 11
#define LOGGER_TX_GPIO_PORT 10


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

struct GPIOStruct pretensionMotorPWMInstance =
{
		.pin = (uint8_t)PRETENSION_MOTOR_PWM_GPIO_PORT,
		.port = 'C',
};

struct GPIOStruct LoggerRxInstance =
{
		.pin = (uint8_t)LOGGER_RX_GPIO_PORT,
		.port = 'C',
};

struct GPIOStruct LoggerTxInstance =
{
		.pin = (uint8_t)LOGGER_TX_GPIO_PORT,
		.port = 'C',
};

struct GPIOStruct Joint1SensorInstance =
{
		.pin = (uint8_t)JOINT1_SENSOR_GPIO_PORT,
		.port = 'B',
};

CP_HA_GPIO CP_HA_GPIO_pretensionMotorClockwiseDirection = &pretensionMotorClockwiseDirectionInstance;
CP_HA_GPIO CP_HA_GPIO_pretensionMotorAnticlockwiseDirection = &pretensionMotorAnticlockwiseDirectionInstance;
CP_HA_GPIO CP_HA_GPIO_pretensionMotorEnable = &pretensionMotorEnableInstance;
CP_HA_GPIO CP_HA_GPIO_pretensionMotorPWM = &pretensionMotorPWMInstance;
CP_HA_GPIO CP_HA_GPIO_LoggerRx = &LoggerRxInstance;
CP_HA_GPIO CP_HA_GPIO_LoggerTx = &LoggerTxInstance;
CP_HA_GPIO CP_HA_GPIO_Joint1Sensor = &Joint1SensorInstance;

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
