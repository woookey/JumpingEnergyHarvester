#include <CP_HA_LED.h>
#include <LEDType.h>
#include <stdio.h>
#include <string.h>

#define CPU_ACTIVITY_LED_PORT 12
#define POWER_ON_INDICATION_LED_PORT 15
#define EXECUTING_INDICATION_LED_PORT 14
#define SAFETY_STOP_INDICATION_LED_PORT 2

static struct LEDType CPUActivityLEDInstance = { .pin = (uint8_t)CPU_ACTIVITY_LED_PORT, .port = 'D' };
static struct LEDType powerOnIndicationLEDInstance = { .pin = (uint8_t)POWER_ON_INDICATION_LED_PORT, .port = 'C' };
static struct LEDType executingIndicationLEDInstance = { .pin = (uint8_t)EXECUTING_INDICATION_LED_PORT, .port = 'D' };
static struct LEDType safetyStopIndicationLEDInstance = { .pin = (uint8_t)SAFETY_STOP_INDICATION_LED_PORT, .port = 'C' };


CP_HA_LEDStruct CPUActivityLED = &CPUActivityLEDInstance;
CP_HA_LEDStruct powerOnIndicationLED = &powerOnIndicationLEDInstance;
CP_HA_LEDStruct executingIndicationLED = &executingIndicationLEDInstance;
CP_HA_LEDStruct safetyStopIndicationLED = &safetyStopIndicationLEDInstance;

void CP_HA_LEDConstruct(CP_HA_LEDStruct LEDInstance)
{
	printf("LED connected to port %c%d constructed\n", LEDInstance->port, LEDInstance->pin);
}

void CP_HA_LEDSwitchOn(CP_HA_LEDStruct LEDInstance)
{
	printf("LED connected to port %c%d switched on\n", LEDInstance->port, LEDInstance->pin);
}

void CP_HA_LEDSwitchOff(CP_HA_LEDStruct LEDInstance)
{
	printf("LED connected to port %c%d switched off\n", LEDInstance->port, LEDInstance->pin);
}
