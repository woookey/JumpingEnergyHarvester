#include <LEDManager.h>
#include <CP_HD_LEDDriver.h>
#include <RF_timers.h>
#include <systemSignals.h>
#include <assert.h>

typedef struct
{
	RFAgent baseAgent;
	RF_Timer flashingPeriodTimer;
} LEDManagerAgent;

typedef enum
{
	LED_MANAGER_FLASHING_TIMEOUT_SIGNAL = SS_END_OF_SIGNAL_SPACE,
} PrivateSignals;

typedef enum
{
	LED_MANAGER_FLASHING_TIMEOUT_IN_MS = 500U,
} PrivateDefinitions;

static LEDManagerAgent LEDManagerInstance;
RFAgent * const LEDManager = (RFAgent* const)&LEDManagerInstance.baseAgent;

static RFHandle initialState(LEDManagerAgent* const me, RFEvent *const evt);
static RFHandle LEDOnState(LEDManagerAgent* const me, RFEvent *const evt);
static RFHandle LEDOffState(LEDManagerAgent* const me, RFEvent *const evt);

void LEDManagerConstructor(RFAgent * const self)
{
	assert(self == LEDManager);
	LEDManagerAgent *const me = (LEDManagerAgent* const)self;
	RFBaseAgentConstructor((RFAgent*)me, &initialState);
	RFTimerConstructor(self, &((LEDManagerAgent*)self)->flashingPeriodTimer, LED_MANAGER_FLASHING_TIMEOUT_SIGNAL);
}

RFHandle initialState(LEDManagerAgent* const me, RFEvent *const evt)
{
	(void)evt;
	(void)me;
	//CP_HD_LED_initialiseLED(CP_HD_powerOnIndicationLED);
	CP_HD_LED_initialiseLED(CP_HD_CPUActivityLED);

	//CP_HD_LED_switchLEDOn(CP_HD_powerOnIndicationLED);
	INITIAL_TRANSITION((RFAgent*)me, &LEDOnState);
}

RFHandle LEDOnState(LEDManagerAgent* const me, RFEvent *const evt)
{
	switch (evt->signalValue)
	{
		case RF_INITIAL_SIGNAL:
		{
			CP_HD_LED_switchLEDOn(CP_HD_CPUActivityLED);
			RFTimer_armTimer(&me->flashingPeriodTimer, LED_MANAGER_FLASHING_TIMEOUT_IN_MS);
			return RF_HANDLED;
		}
		case LED_MANAGER_FLASHING_TIMEOUT_SIGNAL:
		{
			// return RF_HANDLED inside
			EXECUTE_TRANSITION((RFAgent*)me, &LEDOffState);
		}
		case RF_ENTRY_SIGNAL:
		{
			CP_HD_LED_switchLEDOn(CP_HD_CPUActivityLED);
			RFTimer_armTimer(&me->flashingPeriodTimer, LED_MANAGER_FLASHING_TIMEOUT_IN_MS);
			return RF_HANDLED;
		}
		case RF_EXIT_SIGNAL:
		{
			RFTimer_disarmTimer(&me->flashingPeriodTimer);
			return RF_HANDLED;
		}
	}
	return RF_UNHANDLED;
}

RFHandle LEDOffState(LEDManagerAgent* const me, RFEvent *const evt)
{
	switch (evt->signalValue)
	{
	case RF_ENTRY_SIGNAL:
	{
		CP_HD_LED_switchLEDOff(CP_HD_CPUActivityLED);
		RFTimer_armTimer(&me->flashingPeriodTimer, LED_MANAGER_FLASHING_TIMEOUT_IN_MS);
		return RF_HANDLED;
	}
	case RF_EXIT_SIGNAL:
	{
		RFTimer_disarmTimer(&me->flashingPeriodTimer);
		return RF_HANDLED;
	}
	case LED_MANAGER_FLASHING_TIMEOUT_SIGNAL:
	{
		// return RF_HANDLED inside
		EXECUTE_TRANSITION((RFAgent*)me, &LEDOnState);
	}
	}
	return RF_UNHANDLED;
}
