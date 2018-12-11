#include <RF_scheduler.h>
#include <RF_queue.h>
#include <RF_porting.h>
#include <stdlib.h>
#include <assert.h>
#include <RF_definitions.h>

static bool areThereAnyEventsToBeConsumedForAgent(struct RFBaseAgent* currentAgent);

typedef struct
{
	RFAgent** agentsList;
	uint32_t numberOfAgents;
}RFScheduler;

RFAgent* listOfAgentsForSchedulingInstance [RF_MAX_NUMBER_OF_AGENTS] = {NULL};

static RFScheduler RFSchedulerObject =
{
		.agentsList = listOfAgentsForSchedulingInstance,
		.numberOfAgents = 0,
};

void startAgent(struct RFBaseAgent* newAgent, void (*agentCtor)(struct RFBaseAgent* const self),
		RF_SchedulerPriority agentPrio, RFEvent* memoryPool, size_t memoryPoolSize)
{
	assert(newAgent != NULL);
	assert(agentCtor != NULL);
	assert(agentPrio >= 0 && agentPrio < AGENT_PRIORITY_END_OF_PRIORITY_SPACE);

	RFSchedulerObject.agentsList[RFSchedulerObject.numberOfAgents] = newAgent;
	RFSchedulerObject.numberOfAgents++;
	createEmptyQueue(&newAgent->FIFOQueue, memoryPool, memoryPoolSize);
	agentCtor(newAgent);
}

void runScheduler(void)
{
	/**
	 * Superloop(to be added) based on scheduling policy
	 * At the moment each agent is equally important and
	 * they are executed in the same order they were started
	 */
	//while(1)
	//{
	assert(RFSchedulerObject.numberOfAgents > 0 && RFSchedulerObject.numberOfAgents <= RF_MAX_NUMBER_OF_AGENTS);
	uint32_t agentNumber;
	for(agentNumber = 0; agentNumber < RFSchedulerObject.numberOfAgents; agentNumber++)
	{
		RFAgent* currentAgent = RFSchedulerObject.agentsList[agentNumber];
		while (areThereAnyEventsToBeConsumedForAgent(currentAgent))
		{
			RFHandle returnHandle;
			returnHandle = currentAgent->currentHandler
			(currentAgent,(RFEvent *const)currentAgent->FIFOQueue.pop(&currentAgent->FIFOQueue));
			assert(returnHandle == RF_HANDLED || returnHandle == RF_UNHANDLED);

			/**
			 * removing garbage has to be an atomic action
			 */
			RF_enterCriticalSection();
			currentAgent->FIFOQueue.removeGarbage(&currentAgent->FIFOQueue);
			RF_exitCriticalSection();
		}
	}
	//}
}

bool areThereAnyEventsToBeConsumedForAgent(struct RFBaseAgent* currentAgent)
{
	return (currentAgent->FIFOQueue.noOfEvents > 0);
}
