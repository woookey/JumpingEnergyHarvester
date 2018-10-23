#include <CP_HD_LEDDriver.h>
#include <CP_HD_LEDDriver_mock.h>

void CP_HD_LED_initialiseLED(LEDReference ledRef)
{
	ledRef->isInitialised = true;
}

void CP_HD_LED_switchLEDOff(LEDReference ledRef)
{
	ledRef->isOn = false;
	ledRef->noOfCalls++;
}

void CP_HD_LED_switchLEDOn(LEDReference ledRef)
{
	ledRef->isOn = true;
	ledRef->noOfCalls++;
}

bool isLEDSwitchedOn(struct LEDStructure* led)
{
	return led->isOn;
}

bool isLEDInitialised(struct LEDStructure* led)
{
	return led->isInitialised;
}

bool wasLEDCalledNTimes(struct LEDStructure* led, uint32_t nCalls)
{
	return (led->noOfCalls==nCalls);
}
