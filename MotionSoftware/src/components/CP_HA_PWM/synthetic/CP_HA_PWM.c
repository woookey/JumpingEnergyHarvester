#include <CP_HA_PWMDefinition.h>
#include <CP_HA_PWM.h>
#include <stdio.h>

#define CP_HA_PWM_PRETENSION_MOTOR_PWM_PIN 5

static struct PWMStruct pretensionMotorPWMInstance =
{
	.pin = (uint8_t)CP_HA_PWM_PRETENSION_MOTOR_PWM_PIN,
	.port = 'B',
};

CP_HA_PWM CP_HA_PWM_pretensionMotorPWM = &pretensionMotorPWMInstance;

void CP_HA_initialisePWM(CP_HA_PWM PWMInstance)
{
	printf("PWM %c%d constructed\n", PWMInstance->port, PWMInstance->pin);
}

void CP_HA_startPWM(CP_HA_PWM PWMInstance)
{
	printf("PWM %c%d started\n", PWMInstance->port, PWMInstance->pin);
}
