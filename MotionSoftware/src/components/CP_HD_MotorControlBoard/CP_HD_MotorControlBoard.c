#include <CP_HD_MotorControlBoard.h>
#include <stdbool.h>
#include <CP_HA_GPIO.h>
#include <assert.h>

struct MotorControlBoardStruct
{
	bool isInitialised;
	bool isDirectionClockwise;
	CP_HA_GPIO * enableMotorGPIO;
	CP_HA_GPIO * clockwiseDirectionGPIO;
	CP_HA_GPIO * anticlockwiseDirectionGPIO;
};

static struct MotorControlBoardStruct pretensionMotorInstance =
{
		.isInitialised = false,
		.isDirectionClockwise = false,
		.enableMotorGPIO = &pretensionMotorEnable,
		.clockwiseDirectionGPIO = &pretensionMotorClockwiseDirection,
		.anticlockwiseDirectionGPIO = &pretensionMotorAnticlockwiseDirection,
};

CP_HD_MotorControlBoard pretensionMotor = &pretensionMotorInstance;

void CP_HD_MotorControlBoard_initialiseMotor(CP_HD_MotorControlBoard MotorControlInstance)
{
	assert(!MotorControlInstance->isInitialised);
	CP_HA_initialiseGPIO((CP_HA_GPIO)*MotorControlInstance->enableMotorGPIO);
	CP_HA_initialiseGPIO((CP_HA_GPIO)*MotorControlInstance->clockwiseDirectionGPIO);
	CP_HA_initialiseGPIO((CP_HA_GPIO)*MotorControlInstance->anticlockwiseDirectionGPIO);
	MotorControlInstance->isInitialised = true;
}

void CP_HD_MotorControlBoard_setDirectionClockwise(CP_HD_MotorControlBoard MotorControlInstance)
{
	assert(MotorControlInstance->isInitialised);
	CP_HA_turnGPIOOn((CP_HA_GPIO)*MotorControlInstance->clockwiseDirectionGPIO);
	CP_HA_turnGPIOOff((CP_HA_GPIO)*MotorControlInstance->anticlockwiseDirectionGPIO);
	MotorControlInstance->isDirectionClockwise = true;
}

void CP_HD_MotorControlBoard_setDirectionAnticlockwise(CP_HD_MotorControlBoard MotorControlInstance)
{
	assert(MotorControlInstance->isInitialised);
	CP_HA_turnGPIOOff((CP_HA_GPIO)*MotorControlInstance->clockwiseDirectionGPIO);
	CP_HA_turnGPIOOn((CP_HA_GPIO)*MotorControlInstance->anticlockwiseDirectionGPIO);
	MotorControlInstance->isDirectionClockwise = false;
}

void CP_HD_MotorControlBoard_enableMotor(CP_HD_MotorControlBoard MotorControlInstance)
{
	assert(MotorControlInstance->isInitialised);
	CP_HA_turnGPIOOn((CP_HA_GPIO)*MotorControlInstance->enableMotorGPIO);
}

void CP_HD_MotorControlBoard_disableMotor(CP_HD_MotorControlBoard MotorControlInstance)
{
	assert(MotorControlInstance->isInitialised);
	CP_HA_turnGPIOOff((CP_HA_GPIO)*MotorControlInstance->enableMotorGPIO);
}
