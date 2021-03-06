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

/**
 * PORT C
 */
#define LOGGER_RX_GPIO_PORT 11
#define LOGGER_TX_GPIO_PORT 10
#define ANGULAR_SENSOR_PRETENSION_MOTOR_GPIO_PORT 0

/**
 * PORT A
 */
#define ANGULAR_SENSOR_JOINT_1_GPIO_PORT 2
#define ANGULAR_SENSOR_JOINT_2_GPIO_PORT 4
#define ANGULAR_SENSOR_EQUILIBRIUM_MOTOR_GPIO_PORT 6


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

static struct GPIOStruct AngularSensorJoint1 =
{
		.pin = (uint8_t)ANGULAR_SENSOR_JOINT_1_GPIO_PORT,
		.port = 'A',
};

static struct GPIOStruct AngularSensorJoint2 =
{
		.pin = (uint8_t)ANGULAR_SENSOR_JOINT_2_GPIO_PORT,
		.port = 'A',
};

static struct GPIOStruct AngularSensorPretensionMotor =
{
		.pin = (uint8_t)ANGULAR_SENSOR_PRETENSION_MOTOR_GPIO_PORT,
		.port = 'C',
};

static struct GPIOStruct AngularSensorEquilibriumMotor =
{
		.pin = (uint8_t)ANGULAR_SENSOR_EQUILIBRIUM_MOTOR_GPIO_PORT,
		.port = 'A',
};

CP_HA_GPIO CP_HA_GPIO_pretensionMotorClockwiseDirection = &pretensionMotorClockwiseDirectionInstance;
CP_HA_GPIO CP_HA_GPIO_pretensionMotorAnticlockwiseDirection = &pretensionMotorAnticlockwiseDirectionInstance;
CP_HA_GPIO CP_HA_GPIO_pretensionMotorEnable = &pretensionMotorEnableInstance;
CP_HA_GPIO CP_HA_GPIO_pretensionMotorPWM = &pretensionMotorPWMInstance;
CP_HA_GPIO CP_HA_GPIO_LoggerRx = &LoggerRxInstance;
CP_HA_GPIO CP_HA_GPIO_LoggerTx = &LoggerTxInstance;
CP_HA_GPIO CP_HA_GPIO_angularSensorJoint1 = &AngularSensorJoint1;
CP_HA_GPIO CP_HA_GPIO_angularSensorJoint2 = &AngularSensorJoint2;
CP_HA_GPIO CP_HA_GPIO_angularSensorPretensionMotor = &AngularSensorPretensionMotor;
CP_HA_GPIO CP_HA_GPIO_angularSensorEquilibriumMotor = &AngularSensorEquilibriumMotor;

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
