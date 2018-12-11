#include <stdint.h>
#include <stdbool.h>
#include <CP_HA_LED.h>
#include <LEDType.h>
#include <string.h>

struct LEDType mockCPUActivityLED =
{
		.portNumber = 12,
		.isInitialised = false,
		.isSwitchedOn = false,
		.noOfCalls = 0,
};
CP_HA_LEDStruct CPUActivityLED = &mockCPUActivityLED;

static struct LEDType mockpowerOnIndicationLED =
{
		.portNumber = 13,
		.isInitialised = false,
		.isSwitchedOn = false,
		.noOfCalls = 0,
};
CP_HA_LEDStruct powerOnIndicationLED = &mockpowerOnIndicationLED;

static struct LEDType mockexecutingIndicationLED =
{
		.portNumber = 14,
		.isInitialised = false,
		.isSwitchedOn = false,
		.noOfCalls = 0,
};
CP_HA_LEDStruct executingIndicationLED = &mockexecutingIndicationLED;

static struct LEDType mocksafetyStopIndicationLED =
{
		.portNumber = 15,
		.isInitialised = false,
		.isSwitchedOn = false,
		.noOfCalls = 0,
};
CP_HA_LEDStruct safetyStopIndicationLED = &mocksafetyStopIndicationLED;

static struct LEDType mockLEDTypeSample =
{
		.portNumber = 1,
		.isInitialised = false,
		.isSwitchedOn = false,
		.noOfCalls = 0,
};
CP_HA_LEDStruct LEDTypeSample = &mockLEDTypeSample;


void CP_HA_LEDConstruct(CP_HA_LEDStruct LEDInstance)
{
	LEDInstance->isInitialised = true;
	LEDInstance->noOfCalls++;
}

void CP_HA_LEDSwitchOn(CP_HA_LEDStruct LEDInstance)
{
	LEDInstance->isSwitchedOn = true;
	LEDInstance->noOfCalls++;
}

void CP_HA_LEDSwitchOff(CP_HA_LEDStruct LEDInstance)
{
	LEDInstance->isSwitchedOn = false;
	LEDInstance->noOfCalls++;
}

static uint32_t numberOfCallsToLED(CP_HA_LEDStruct ledRef)
{
	return ledRef->noOfCalls;
}

static bool isLEDInitialised(CP_HA_LEDStruct ledRef)
{
	return ledRef->isInitialised;
}

bool isCPUActivityLEDInitialised(void) {return isLEDInitialised(CPUActivityLED);}
bool ispowerOnIndicationLEDInitialised(void) {return isLEDInitialised(powerOnIndicationLED);}
bool isexecutingIndicationLEDInitialised(void) {return isLEDInitialised(executingIndicationLED);};
bool issafetyStopIndicationLEDInitialised(void) {return isLEDInitialised(safetyStopIndicationLED);};

uint32_t numberOfCallsToCPUActivityLED(void) {return numberOfCallsToLED(CPUActivityLED);};
uint32_t numberOfCallsTopowerOnIndicationLED(void) {return numberOfCallsToLED(powerOnIndicationLED);};
uint32_t numberOfCallsToexecutingIndicationLED(void) {return numberOfCallsToLED(executingIndicationLED);};
uint32_t numberOfCallsTosafetyStopIndicationLED(void) {return numberOfCallsToLED(safetyStopIndicationLED);};

void resetLEDs(void)
{
	mockCPUActivityLED.portNumber = 12;
	mockCPUActivityLED.noOfCalls = 0;
	mockCPUActivityLED.isInitialised = false;
	mockCPUActivityLED.isSwitchedOn = false;

	mockpowerOnIndicationLED.portNumber = 13;
	mockpowerOnIndicationLED.isInitialised = false;
	mockpowerOnIndicationLED.isSwitchedOn = false;
	mockpowerOnIndicationLED.noOfCalls = 0;

	mockexecutingIndicationLED.portNumber = 14;
	mockexecutingIndicationLED.isInitialised = false;
	mockexecutingIndicationLED.isSwitchedOn = false;
	mockexecutingIndicationLED.noOfCalls = 0;

	mocksafetyStopIndicationLED.portNumber = 15;
	mocksafetyStopIndicationLED.isInitialised = false;
	mocksafetyStopIndicationLED.isSwitchedOn = false;
	mocksafetyStopIndicationLED.noOfCalls = 0;

	mockLEDTypeSample.portNumber = 1;
	mockLEDTypeSample.isInitialised = false;
	mockLEDTypeSample.isSwitchedOn = false;
	mockLEDTypeSample.noOfCalls = 0;
}
