#ifndef CP_HD_LEDDRIVER_MOCK_H
#define CP_HD_LEDDRIVER_MOCK_H

#include <stdint.h>
#include <stdbool.h>

struct LEDStructure
{
	bool isInitialised;
	uint32_t noOfCalls;
	bool isOn;
};

bool isLEDSwitchedOn(struct LEDStructure* led);
bool isLEDInitialised(struct LEDStructure* led);
bool wasLEDCalledNTimes(struct LEDStructure* led, uint32_t nCalls);

#endif
