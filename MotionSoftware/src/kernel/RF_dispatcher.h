/**
 * Dispatcher takes any published event, pushes it into its own queue
 * and dispenses the event to each and every agent that is subscribed
 * to that particular event
 *
 * Note: Dispatcher has to be created before the scheduler starts any agent
 */
#ifndef RF_DISPATCHER_H
#define RF_DISPATCHER_H

#include <RF_events.h>
#include <RF_agents.h>

/**
 * Constructs dispatcher with a fixed memory pool (at least now)
 */
void RF_DispatcherCtor(void);

/**
 * Registers number of expected events to improve performance
 */
void RF_Dispatcher_RegisterNumberOfEvents(uint16_t noOfExpectedEvents);

/**
 * Registers number of agents to improve performance
 */
void RF_Dispatcher_RegisterNumberOfAgents(uint16_t noOfExpectedAgents);

/**
 * Subscribes an agent to the signal
 */
void subscribeAgentToSignal(RFAgent* self, uint32_t signalValue);

/**
 * Unsubscribes an agent to the signal
 */
void unsubscribeAgentToSignal(RFAgent* self, uint32_t signalValue);

/**
 * Publishes an event and dispatches to all subscribed agents
 */
void publishEvent(RFEvent const* const evt);

#endif
