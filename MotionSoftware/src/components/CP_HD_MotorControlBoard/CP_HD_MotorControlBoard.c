#include <CP_HD_MotorControlBoard.h>
#include <stdbool.h>
#include <CP_HA_GPIO.h>
#include <CP_HA_PWM.h>
#include <assert.h>

struct MotorControlBoardStruct
{
	bool isInitialised;
	bool isDirectionClockwise;
	CP_HA_GPIO * enableMotorGPIO;
	CP_HA_GPIO * clockwiseDirectionGPIO;
	CP_HA_GPIO * anticlockwiseDirectionGPIO;
	CP_HA_GPIO * PWMSignalGPIO;
	CP_HA_PWM * PWMSignal;
};

static struct MotorControlBoardStruct pretensionMotorInstance =
{
		.isInitialised = false,
		.isDirectionClockwise = false,
		.enableMotorGPIO = &CP_HA_GPIO_pretensionMotorEnable,
		.clockwiseDirectionGPIO = &CP_HA_GPIO_pretensionMotorClockwiseDirection,
		.anticlockwiseDirectionGPIO = &CP_HA_GPIO_pretensionMotorAnticlockwiseDirection,
		.PWMSignalGPIO = &CP_HA_GPIO_pretensionMotorPWM,
		.PWMSignal = &CP_HA_PWM_pretensionMotorPWM,
};

CP_HD_MotorControlBoard pretensionMotor = &pretensionMotorInstance;

void CP_HD_MotorControlBoard_initialiseMotor(CP_HD_MotorControlBoard MotorControlInstance)
{
	assert(!MotorControlInstance->isInitialised);
	CP_HA_initialiseGPIO((CP_HA_GPIO)*MotorControlInstance->enableMotorGPIO);
	CP_HA_initialiseGPIO((CP_HA_GPIO)*MotorControlInstance->clockwiseDirectionGPIO);
	CP_HA_initialiseGPIO((CP_HA_GPIO)*MotorControlInstance->anticlockwiseDirectionGPIO);

	CP_HA_initialiseGPIO((CP_HA_GPIO)*MotorControlInstance->PWMSignalGPIO);
	CP_HA_initialisePWM((CP_HA_PWM)*MotorControlInstance->PWMSignal);
	//CP_HA_startPWM((CP_HA_PWM)*MotorControlInstance->PWMSignal);
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


void CP_HD_MotorControlBoard_startPWM(CP_HD_MotorControlBoard MotorControlInstance, uint8_t pwm)
{
	assert(MotorControlInstance->isInitialised);
	(void)pwm;
	CP_HA_startPWM((CP_HA_PWM)*MotorControlInstance->PWMSignal);
}
