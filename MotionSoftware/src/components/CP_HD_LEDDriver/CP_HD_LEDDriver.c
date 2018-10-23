#include <CP_HD_LEDDriver.h>
#include <CP_HA_LED.h>
#include <stdbool.h>

/**
 * Definition of a reference to a LED structures
 */
struct LEDStructure
{
	CP_HA_LEDStruct* led;
	bool isInitialised;
	bool isOn;
};

/**
 * Static definitions
 */
static struct LEDStructure CPUActivityLED_t =
{
		.led = &CPUActivityLED,
		.isInitialised = false,
		.isOn = false,
};

static struct LEDStructure powerOnIndicationLED_t =
{
		.led = &powerOnIndicationLED,
		.isInitialised = false,
		.isOn = false,
};

static struct LEDStructure executingIndicationLED_t =
{
		.led = &executingIndicationLED,
		.isInitialised = false,
		.isOn = false,
};

static struct LEDStructure safeyStopIndicationLED_t =
{
		.led = &safetyStopIndicationLED,
		.isInitialised = false,
		.isOn = false,
};

LEDReference CP_HD_CPUActivityLED = &CPUActivityLED_t;
LEDReference CP_HD_powerOnIndicationLED = &powerOnIndicationLED_t;
LEDReference CP_HD_executingIndicationLED = &executingIndicationLED_t;
LEDReference CP_HD_safetyStopIndicationLED = &safeyStopIndicationLED_t;


void CP_HD_LED_initialiseLED(LEDReference ledRef)
{
	if (!ledRef->isInitialised)
	{
		CP_HA_LEDConstruct((CP_HA_LEDStruct)*ledRef->led);
	}
	ledRef->isInitialised = true;
}

void CP_HD_LED_switchLEDOff(LEDReference ledRef)
{
	if (ledRef->isOn)
	{
		CP_HA_LEDSwitchOff((CP_HA_LEDStruct)*ledRef->led);
		ledRef->isOn = false;
	}
}

void CP_HD_LED_switchLEDOn(LEDReference ledRef)
{
	if (!ledRef->isOn)
	{
		CP_HA_LEDSwitchOn((CP_HA_LEDStruct)*ledRef->led);
		ledRef->isOn = true;
	}
}
