#include <CP_BH_LegControl.h>
#include <assert.h>
#include <RF_timers.h>

typedef struct
{
	RFAgent* baseAgent;
	RF_Timer* LegControlWaitForPowerUpTimeout;
} LegControlModule_t;

static LegControlModule_t LegControlModuleInstance;
RFAgent * const LegControlModule = (RFAgent* const)&LegControlModuleInstance;

typedef enum
{
	LEG_CONTROL_WAIT_FOR_POWER_UP_SIGNAL = SS_END_OF_SIGNAL_SPACE,
} PrivateSignals;

typedef enum
{
	LEG_CONTROL_WAIT_FOR_POWER_UP_TIMEOUT_IN_MS = 1000U,
} PrivateDefinitions;


static RFHandle InitialState(LegControlModule_t* const me, RFEvent *const evt);
static RFHandle NoControlState(LegControlModule_t* const me, RFEvent *const evt);

void CP_BH_LegControlModuleConstructor(RFAgent * const self)
{
	assert(self == LegControlModule);
	LegControlModule_t *const me = (LegControlModule_t* const)self;
	RFBaseAgentConstructor((RFAgent*)me, &InitialState);
	RFTimerConstructor((RFAgent*) me, (RF_Timer*)&me->LegControlWaitForPowerUpTimeout, LEG_CONTROL_WAIT_FOR_POWER_UP_SIGNAL);
}

RFHandle InitialState(LegControlModule_t* const me, RFEvent *const evt)
{
	(void)evt;
	(void)me;

	// TODO: Initialise motor driver for preTensioning motor in
	// the following way:
	//CP_HD_LED_initialiseLED(CP_HD_CPUActivityLED);

	INITIAL_TRANSITION((RFAgent*)me, &NoControlState);
}

RFHandle NoControlState(LegControlModule_t* const me, RFEvent *const evt)
{
	switch (evt->signalValue)
	{
		case RF_INITIAL_SIGNAL:
		{
			RFTimer_armTimer(&me->LegControlWaitForPowerUpTimeout, LEG_CONTROL_WAIT_FOR_POWER_UP_TIMEOUT_IN_MS);
			return RF_HANDLED;
		}
		case LEG_CONTROL_WAIT_FOR_POWER_UP_SIGNAL:
		{
			// return RF_HANDLED inside
			//EXECUTE_TRANSITION((RFAgent*)me, &LEDOffState);
			RFTimer_disarmTimer(&me->LegControlWaitForPowerUpTimeout);
			return RF_HANDLED;
		}
		case RF_ENTRY_SIGNAL:
		{
			return RF_HANDLED;
		}
		case RF_EXIT_SIGNAL:
		{
			RFTimer_disarmTimer(&me->LegControlWaitForPowerUpTimeout);
			return RF_HANDLED;
		}
	}
	return RF_UNHANDLED;
}
