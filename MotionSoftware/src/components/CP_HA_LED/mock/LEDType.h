#ifndef MOCK_LED_TYPE_H
#define MOCK_LED_TYPE_H

#include <stdint.h>
#include <stdbool.h>

struct LEDType
{
	uint8_t portNumber;
	bool isInitialised;
	bool isSwitchedOn;
	uint32_t noOfCalls;
};

#endif
