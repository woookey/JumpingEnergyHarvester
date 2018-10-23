/**
 * Schedules all agents depending on their priorities.
 *
 * Scheduler's is responsible for the following actions:
 * - agents construction
 * - scheduling agents
 */
#ifndef ROBOTIC_FRAMEWORK_SCHEDULER_H
#define ROBOTIC_FRAMEWORK_SCHEDULER_H

#include <RF_agents.h>

/**
 * Priority has to be assigned during agents construction
 * TODO: At the moment the priority does not matter - the order
 * in which agents are created matters!
 */
typedef enum
{
	AGENT_PRIORITY_0 = 0,
	AGENT_PRIORITY_END_OF_PRIORITY_SPACE,
}RF_SchedulerPriority;


/**
 * Initialises each agent
 *
 * TODO: It lacks few parameters such as memory block for events, memory block for events size
 * and ...?What else?
 */
void startAgent(struct RFBaseAgent* newAgent, void (*agentCtor)(struct RFBaseAgent* const self),
		RF_SchedulerPriority agentPrio, RFEvent* memoryPool, size_t memoryPoolSize);

/**
 * Runs the scheduler on its scheduling policy
 */
void runScheduler(void);

#endif
