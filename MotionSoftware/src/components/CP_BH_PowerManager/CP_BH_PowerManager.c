#include <CP_BH_PowerManager.h>
#include <RF_agents.h>
#include <RF_events.h>
#include <CP_HD_LEDDriver.h>
#include <assert.h>


typedef struct PowerManager
{
	RFAgent baseAgent;
} PowerManagerAgent;


static PowerManagerAgent PowerManagerInstance;
RFAgent * const PowerManager = (RFAgent* const)&PowerManagerInstance.baseAgent;

static RFHandle initialState(PowerManagerAgent* const self, RFEvent *const evt);
static RFHandle powerOnState(PowerManagerAgent* const self, RFEvent *const evt);


void PowerManagerConstructor(RFAgent * const self)
{
	assert(self == PowerManager);
	PowerManagerAgent* const me = (PowerManagerAgent* const)self;
	RFBaseAgentConstructor((RFAgent* const) me, &initialState);
}

RFHandle initialState(PowerManagerAgent* const self, RFEvent *const evt)
{
	(void)self;
	(void)evt;

	CP_HD_LED_initialiseLED(CP_HD_powerOnIndicationLED);
	CP_HD_LED_initialiseLED(CP_HD_safetyStopIndicationLED);
	INITIAL_TRANSITION((RFAgent*) self, &powerOnState);
}

RFHandle powerOnState(PowerManagerAgent* const self, RFEvent *const evt)
{
	switch(evt->signalValue)
	{
	case RF_INITIAL_SIGNAL:
	{
		CP_HD_LED_switchLEDOn(CP_HD_safetyStopIndicationLED);
		CP_HD_LED_switchLEDOn(CP_HD_powerOnIndicationLED);
		return RF_HANDLED;
	}
	}
	return RF_UNHANDLED;
}
