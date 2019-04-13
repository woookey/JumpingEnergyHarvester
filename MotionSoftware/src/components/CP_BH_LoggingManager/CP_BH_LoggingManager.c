#include <RF_agents.h>
#include <RF_events.h>
#include <RF_timers.h>
#include <systemSignals.h>
#include <assert.h>
#include <CP_BH_LoggingManager.h>
#include <CP_HD_Logger.h>
#include <CP_HD_AnalogInput.h>


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
	LOGGING_TIMEOUT_IN_MS = 1U,
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
	CP_HD_AnalogInput_initialise();
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
		//CP_HD_Logger_sendData();
		CP_HD_AnalogInput_readData();
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

/**
 * Data Logging
 */
void CP_HD_AnalogInput_readDataCallback(uint8_t analogReading)
{
	static uint8_t payload[3];
	static uint8_t secondSensor = 0;
	payload[0] = 0xAA;
	payload[1] = analogReading;
	payload[2] = (uint8_t)100;
	//payload[3] = (uint8_t)100;
	//payload[4] = (uint8_t)255;
	CP_HD_Logger_sendData(&payload[0], (uint8_t)1);
	CP_HD_Logger_sendData(&payload[1], (uint8_t)1);
	CP_HD_Logger_sendData(&payload[2], (uint8_t)1);
}
