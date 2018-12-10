#include <CP_BH_PowerManager.h>
#include <RF_agents.h>
#include <RF_events.h>
#include <RF_timers.h>
#include <systemSignals.h>
#include <CP_HD_LEDDriver.h>
#include <assert.h>


typedef struct PowerManager
{
	RFAgent baseAgent;
	RF_Timer waitForPowerUpTimer;
} PowerManagerAgent;


static PowerManagerAgent PowerManagerInstance;
RFAgent * const PowerManager = (RFAgent* const)&PowerManagerInstance.baseAgent;

typedef enum
{
	WAIT_FOR_POWER_UP_SIGNAL = SS_END_OF_SIGNAL_SPACE,
} PrivateSignals;

typedef enum
{
	WAIT_FOR_POWER_UP_TIMEOUT_IN_MS = 1000U,
} PrivateDefinitions;

static RFHandle initialState(PowerManagerAgent* const self, RFEvent *const evt);
static RFHandle powerOnState(PowerManagerAgent* const self, RFEvent *const evt);
static RFHandle waitForPowerUpState(PowerManagerAgent* const self, RFEvent *const evt);


void PowerManagerConstructor(RFAgent * const self)
{
	assert(self == PowerManager);
	PowerManagerAgent* const me = (PowerManagerAgent* const)self;
	RFBaseAgentConstructor((RFAgent* const) me, &initialState);
	RFTimerConstructor((RFAgent* const) me, (RF_Timer*) &me->waitForPowerUpTimer, WAIT_FOR_POWER_UP_SIGNAL);
}

RFHandle initialState(PowerManagerAgent* const self, RFEvent *const evt)
{
	(void)self;
	(void)evt;

	CP_HD_LED_initialiseLED(CP_HD_powerOnIndicationLED);
	CP_HD_LED_initialiseLED(CP_HD_safetyStopIndicationLED);
	CP_HD_LED_switchLEDOff(CP_HD_powerOnIndicationLED);
	CP_HD_LED_switchLEDOff(CP_HD_safetyStopIndicationLED);
	INITIAL_TRANSITION((RFAgent*) self, &waitForPowerUpState);
}

RFHandle waitForPowerUpState(PowerManagerAgent* const self, RFEvent *const evt)
{
	switch(evt->signalValue)
	{
	case RF_INITIAL_SIGNAL:
	{
		CP_HD_LED_switchLEDOn(CP_HD_safetyStopIndicationLED);
		RFTimer_armTimer((RF_Timer*) &self->waitForPowerUpTimer, WAIT_FOR_POWER_UP_TIMEOUT_IN_MS);
		return RF_HANDLED;
	}
	case WAIT_FOR_POWER_UP_SIGNAL:
	{
		RFTimer_disarmTimer((RF_Timer*) &self->waitForPowerUpTimer);
		EXECUTE_TRANSITION((RFAgent const*)&self->baseAgent, &powerOnState);
	}
	case RF_EXIT_SIGNAL:
	{
		CP_HD_LED_switchLEDOff(CP_HD_safetyStopIndicationLED);
		return RF_HANDLED;
	}
	}
	return RF_UNHANDLED;
}

RFHandle powerOnState(PowerManagerAgent* const self, RFEvent *const evt)
{
	switch(evt->signalValue)
	{
	case RF_ENTRY_SIGNAL:
	{
		CP_HD_LED_switchLEDOn(CP_HD_powerOnIndicationLED);
		return RF_HANDLED;
	}
	}
	return RF_UNHANDLED;
}
