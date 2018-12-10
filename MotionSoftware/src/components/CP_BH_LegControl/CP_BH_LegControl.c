#include <CP_BH_LegControl.h>
#include <assert.h>
#include <RF_dispatcher.h>
#include <RF_timers.h>
#include <systemSignals.h>

typedef struct
{
	RFAgent baseAgent;
} LegControlModule_t;

static LegControlModule_t LegControlModuleInstance;
RFAgent * const LegControlModule = (RFAgent* const)&LegControlModuleInstance;

static RFHandle InitialState(LegControlModule_t* const me, RFEvent *const evt);
static RFHandle WaitForPower(LegControlModule_t* const me, RFEvent *const evt);
static RFHandle NoMotionState(LegControlModule_t* const me, RFEvent *const evt);

static void doNothing(void);

void CP_BH_LegControlModuleConstructor(RFAgent * const self)
{
	assert(self == LegControlModule);
	LegControlModule_t *const me = (LegControlModule_t* const)self;
	RFBaseAgentConstructor((RFAgent*)&me, &InitialState);
	subscribeAgentToSignal((RFAgent*)&me, SS_CP_BH_POWER_MANAGER_POWER_IS_ON_SIGNAL);
}

RFHandle InitialState(LegControlModule_t* const me, RFEvent *const evt)
{
	(void)evt;
	(void)me;
	// initialise ports for motor drivers

	INITIAL_TRANSITION((RFAgent*)me, &WaitForPower);
}

RFHandle WaitForPower(LegControlModule_t* const me, RFEvent *const evt)
{
	switch (evt->signalValue)
	{
	case RF_INITIAL_SIGNAL:
	case RF_ENTRY_SIGNAL:
	case RF_EXIT_SIGNAL:
	{
		return RF_HANDLED;
	}
	case SS_CP_BH_POWER_MANAGER_POWER_IS_ON_SIGNAL:
	{
		// enable motor driver for pre-tensioner
		doNothing();
		EXECUTE_TRANSITION((RFAgent const*)me, &NoMotionState);
	}
	}
	return RF_UNHANDLED;
}

RFHandle NoMotionState(LegControlModule_t* const me, RFEvent *const evt)
{
	switch (evt->signalValue)
	{
		case RF_INITIAL_SIGNAL:
		{
			return RF_HANDLED;
		}
		case RF_ENTRY_SIGNAL:
		{
			return RF_HANDLED;
		}
		case RF_EXIT_SIGNAL:
		{
			return RF_HANDLED;
		}
	}
	return RF_UNHANDLED;
}

void doNothing(void){};
