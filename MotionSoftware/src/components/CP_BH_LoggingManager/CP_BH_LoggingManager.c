#include <RF_agents.h>
#include <RF_events.h>
#include <RF_timers.h>
#include <systemSignals.h>
#include <assert.h>
#include <CP_BH_LoggingManager.h>
#include <CP_HD_Logger.h>


typedef struct LoggingManager
{
	RFAgent baseAgent;
	RF_Timer loggingTimer;
} LoggingManagerAgent;

typedef enum
{
	LOGGING_SIGNAL = SS_END_OF_SIGNAL_SPACE,
} PrivateSignals;

typedef enum
{
	LOGGING_TIMEOUT_IN_MS = 500U,
} PrivateDefinitions;

static LoggingManagerAgent LoggingManagerInstance;
RFAgent * const LoggingManager = (RFAgent* const)&LoggingManagerInstance.baseAgent;


static RFHandle initialState(LoggingManagerAgent* const self, RFEvent *const evt);
static RFHandle loggingState(LoggingManagerAgent* const self, RFEvent *const evt);


void CP_BH_LoggingManagerConstructor(RFAgent * const self)
{
	assert(self == LoggingManager);
	LoggingManagerAgent* const me = (LoggingManagerAgent* const)self;
	RFBaseAgentConstructor((RFAgent* const) me, &initialState);
	RFTimerConstructor((RFAgent* const) me, (RF_Timer*) &me->loggingTimer, LOGGING_SIGNAL);
}

RFHandle initialState(LoggingManagerAgent* const self, RFEvent *const evt)
{
	(void)self;
	(void)evt;
	/**
	 * Subscribe to signals here
	 */

	// Initialise logger hardware
	CP_HD_Logger_initialise();
	INITIAL_TRANSITION((RFAgent*) self, &loggingState);
}

RFHandle loggingState(LoggingManagerAgent* const self, RFEvent *const evt)
{
	switch(evt->signalValue)
	{
	case RF_INITIAL_SIGNAL:
	case LOGGING_SIGNAL:
	{
		// Send data to UART
		CP_HD_Logger_sendData();
		RFTimer_armTimer((RF_Timer*) &self->loggingTimer, LOGGING_TIMEOUT_IN_MS);
		return RF_HANDLED;
	}

	case RF_EXIT_SIGNAL:
	{
		return RF_HANDLED;
	}
	}
	return RF_UNHANDLED;
}
