/**
 * Defines the most basic events
 */
#ifndef ROBOTIC_FRAMEWORK_EVENTS_H
#define ROBOTIC_FRAMEWORK_EVENTS_H

#include <stdint.h>
#include <stddef.h>

/**
 * This is a structure defining the most basic
 * event as part of Robotic Framework. Each event
 * is constructed dynamically during the program
 * and is dispatched to subscribed agents in order
 * to be processed by them
 *
 * @param signalValue, value of the signal
 * @param pendingConsumers, number of agents that still
 * need to consume this event
 *
 * TODO: pendingConsumers should be deleted - not needed really
 */
typedef struct
{
	uint32_t signalValue;
	uint32_t pendingConsumers;
	size_t eventSize;
}RFEvent;

#define RFEVENT_SIZE sizeof(RFEvent)

/**
 * Define some universal signals that will be used
 * thorough the framework application
 *
 * Note: Application signal space has to start with
 * signal equal to 3
 */
enum
{
	RF_INITIAL_SIGNAL = 0,
	RF_ENTRY_SIGNAL = 1,
	RF_EXIT_SIGNAL = 2,
	RF_LAST_SIGNAL = 3
};

extern RFEvent RFEvent_InitialSignal;
extern RFEvent RFEvent_EntrySignal;
extern RFEvent RFEvent_ExitSignal;

#endif
