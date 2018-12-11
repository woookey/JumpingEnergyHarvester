#include <RF_dispatcher.h>
#include <RF_definitions.h>
#include <RF_queue.h>
#include <RF_porting.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>

#define NUMBER_OF_SIGNALS_REQUIRED_BY_FRAMEWORK RF_LAST_SIGNAL

typedef struct
{
	uint16_t noOfRegisteredAgents;
	uint16_t noOfRegisteredSignals;
} RF_Dispatcher;

static RFAgent* subscribersInstance[RF_MAX_NUMBER_OF_SIGNALS][RF_MAX_NUMBER_OF_AGENTS] = {NULL};
static RF_Dispatcher dispatcherInstance;

void RF_DispatcherCtor(void)
{
	memset(subscribersInstance, (uint64_t)NULL,
			sizeof(RFAgent*)*RF_MAX_NUMBER_OF_SIGNALS*RF_MAX_NUMBER_OF_AGENTS);
	memset(&dispatcherInstance, 0, sizeof(RF_Dispatcher));
	dispatcherInstance.noOfRegisteredAgents = 0;
	dispatcherInstance.noOfRegisteredSignals = NUMBER_OF_SIGNALS_REQUIRED_BY_FRAMEWORK;
}

void RF_Dispatcher_RegisterNumberOfEvents(uint16_t noOfExpectedEvents)
{
	assert(noOfExpectedEvents > 0 && noOfExpectedEvents <= RF_MAX_NUMBER_OF_SIGNALS);
	dispatcherInstance.noOfRegisteredSignals = noOfExpectedEvents;
}

void RF_Dispatcher_RegisterNumberOfAgents(uint16_t noOfExpectedAgents)
{
	assert(noOfExpectedAgents > 0 && noOfExpectedAgents <= RF_MAX_NUMBER_OF_AGENTS);
	dispatcherInstance.noOfRegisteredAgents = noOfExpectedAgents;
}

/**
 * Subscribes an agent to the signal
 */
void subscribeAgentToSignal(RFAgent* agent, uint32_t signalValue)
{
	assert(agent != NULL);
	assert(signalValue >= 0 && signalValue <= dispatcherInstance.noOfRegisteredSignals);
	uint16_t agentSlot;
	/**
	 * Do not add the agent if it is already subscribed
	 */
	for (agentSlot = 0; agentSlot < dispatcherInstance.noOfRegisteredAgents; agentSlot++)
	{
		if (subscribersInstance[signalValue][agentSlot] == agent)
		{
			return;
		}
	}
	for (agentSlot = 0; agentSlot < dispatcherInstance.noOfRegisteredAgents; agentSlot++)
	{
		if (subscribersInstance[signalValue][agentSlot] == NULL)
		{
			subscribersInstance[signalValue][agentSlot] = agent;
			return;
		}
	}
	assert(false);
}

void unsubscribeAgentToSignal(RFAgent* self, uint32_t signalValue)
{
	assert(self != NULL);
	assert(signalValue >= 0 && signalValue <= dispatcherInstance.noOfRegisteredSignals);
	uint16_t agentSlot;
	for (agentSlot = 0; agentSlot < dispatcherInstance.noOfRegisteredAgents; agentSlot++)
	{
		if (subscribersInstance[signalValue][agentSlot] == self)
		{
			subscribersInstance[signalValue][agentSlot] = NULL;
			/**
			 * TODO:
			 * Shift the memory to the left by one agent to align with subscribed agents
			 */
		}
	}
}

void publishEvent(RFEvent const* const evt)
{
	assert(evt != NULL);
	uint16_t agentSlot;
	/**
	 * Publishing an event has to be an atomic action
	 */
	RF_enterCriticalSection();
	for (agentSlot = 0; agentSlot < dispatcherInstance.noOfRegisteredAgents; agentSlot++)
	{
		if (subscribersInstance[evt->signalValue][agentSlot] != NULL)
		{
			RFAgent* subscribedAgent = subscribersInstance[evt->signalValue][agentSlot];
			subscribedAgent->FIFOQueue.push(&subscribedAgent->FIFOQueue, (RFEvent*)evt, evt->eventSize);
		}
	}
	RF_exitCriticalSection();
}
