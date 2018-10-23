/**
 * Agents are the core elements of the Robotic Framework
 * which correspond to state machines executing the program
 * and transmitting information between each other
 */
#ifndef ROBOTIC_FRAMEWORK_AGENTS_H
#define ROBOTIC_FRAMEWORK_AGENTS_H

#include <RF_events.h>
#include <RF_queue.h>

typedef enum
{
	RF_HANDLED = 0,
	RF_UNHANDLED = 1,
} RFHandle;

struct RFBaseAgent
{
	struct RF_BaseQueue FIFOQueue;
	RFHandle (*currentHandler)(struct RFBaseAgent* const self, RFEvent *const evt);
};

typedef struct RFBaseAgent RFAgent;

void RFBaseAgentConstructor(RFAgent* const self, RFHandle (*initialTransition)(RFAgent* const self, RFEvent *const evt));

/**
 * Posts event directly to the agent's queue
 *
 * Note: This should only be used to post an event to itself
 */
void postEventToAgent(RFAgent* self, RFEvent const * const evt);

#define INITIAL_TRANSITION(me, state) \
	((RFAgent*)me)->currentHandler = state; \
	(void)((RFAgent*)me)->currentHandler(me, &RFEvent_InitialSignal);

#define ENTRY_TRANSITION(me, state) \
	((RFAgent*)me)->currentHandler = state; \
	(void)((RFAgent*)me)->currentHandler(me, &RFEvent_EntrySignal);

#define EXIT_TRANSITION(me) \
	(void)((RFAgent*)me)->currentHandler(me, &RFEvent_ExitSignal);

/**
 * TODO: Execute transition does not work
 * To be unit tested!
 */
#define EXECUTE_TRANSITION(me, state) \
	EXIT_TRANSITION(me) \
	ENTRY_TRANSITION(me, state) \
	return RF_HANDLED;

#endif
