#include <stdint.h>
#include <LEDType.h>
#include <CP_HA_LED.h>

extern CP_HA_LEDStruct LEDTypeSample;

bool isCPUActivityLEDInitialised(void);
bool ispowerOnIndicationLEDInitialised(void);
bool isexecutingIndicationLEDInitialised(void);
bool issafetyStopIndicationLEDInitialised(void);

uint32_t numberOfCallsToCPUActivityLED(void);
uint32_t numberOfCallsTopowerOnIndicationLED(void);
uint32_t numberOfCallsToexecutingIndicationLED(void);
uint32_t numberOfCallsTosafetyStopIndicationLED(void);

void resetLEDs(void);

