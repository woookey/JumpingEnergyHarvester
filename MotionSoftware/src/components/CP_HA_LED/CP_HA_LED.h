#ifndef CP_HA_LED_H
#define CP_HA_LED_H

#include <LEDType.h>

typedef struct LEDType LEDType_t;
typedef LEDType_t *const CP_HA_LEDStruct;

extern CP_HA_LEDStruct CPUActivityLED;

extern CP_HA_LEDStruct powerOnIndicationLED;
extern CP_HA_LEDStruct executingIndicationLED;
extern CP_HA_LEDStruct safetyStopIndicationLED;

void CP_HA_LEDConstruct(CP_HA_LEDStruct LEDInstance);
void CP_HA_LEDSwitchOn(CP_HA_LEDStruct LEDInstance);
void CP_HA_LEDSwitchOff(CP_HA_LEDStruct LEDInstance);

#endif
