#include <RF_agents.h>
#include <RF_events.h>
#include <RF_timers.h>
#include <systemSignals.h>
#include <assert.h>
#include "CP_BH_LoggingManager.h"


typedef struct LoggingManager
{
	RFAgent baseAgent;
} LoggingManagerAgent;

static LoggingManagerAgent LoggingManagerInstance;
RFAgent * const LoggingManager = (RFAgent* const)&LoggingManagerInstance.baseAgent;


static RFHandle initialState(LoggingManagerAgent* const self, RFEvent *const evt);
static RFHandle loggingState(LoggingManagerAgent* const self, RFEvent *const evt);


void LoggingManagerConstructor(RFAgent * const self)
{
	assert(self == PowerManager);
	LoggingManagerAgent* const me = (LoggingManagerAgent* const)self;
	RFBaseAgentConstructor((RFAgent* const) me, &initialState);
}

RFHandle initialState(LoggingManagerAgent* const self, RFEvent *const evt)
{
	(void)self;
	(void)evt;
	/**
	 * Subscribe to signals here
	 */
	INITIAL_TRANSITION((RFAgent*) self, &loggingState);
}

RFHandle loggingState(LoggingManagerAgent* const self, RFEvent *const evt)
{
	switch(evt->signalValue)
	{
	case RF_INITIAL_SIGNAL:
	{
		// Send data to UART
		return RF_HANDLED;
	}
	case RF_EXIT_SIGNAL:
	{
		return RF_HANDLED;
	}
	}
	return RF_UNHANDLED;
}
