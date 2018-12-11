#ifndef CP_HA_DIGITAL_INPUT_H
#define CP_HA_DIGITAL_INPUT_H

#include <stdint.h>

typedef struct DigitalInputType DigitalInputType_t;
typedef DigitalInputType_t* const CP_HA_DigitalInput;

extern CP_HA_DigitalInput safetySwitchInput;

uint8_t CP_HA_DigitalInput_readInput(CP_HA_DigitalInput digitalInput);
void CP_HA_DigitalInput_constructInput(CP_HA_DigitalInput digitalInput);

#endif
