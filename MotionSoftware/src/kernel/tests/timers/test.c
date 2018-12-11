#include <unity.h>
#include <RF_events.h>
#include <RF_timers.h>
#include <RF_agents.h>
#include <RF_queue.h>
#include <testing_utils.h>
#include <string.h>
#include <stdbool.h>

/**
 * TODO: Eliminate making objects in src/kernel when building timers tests
 */

typedef struct
{
	RFAgent baseAgent;
	RF_Timer sampleTimer;
	RF_Timer sampleTimer1;
} timerAgent;
static timerAgent timerAgentInstance;
static timerAgent timerAgent1Instance;

static void timerAgentEventHandler(RFAgent* const self, RFEvent *const evt);
static void timerAgent1EventHandler(RFAgent* const self, RFEvent *const evt);

static void accelerateTimeByNTicksAndHandleGeneratedEvents(uint32_t n);

#define SAMPLE_EVENT_SIG 150
#define SAMPLE_EVENT_1_SIG 95
#define MEMORY_POOL_SIZE_IN_EVENTS 10
#define TIMEOUT_OF_SAMPLE_TIMER_0_IN_MS 20
#define TIMEOUT_OF_SAMPLE_TIMER_1_IN_MS 30

static RFEvent sampleMemoryPool[MEMORY_POOL_SIZE_IN_EVENTS];
static RFEvent sampleMemoryPool1[MEMORY_POOL_SIZE_IN_EVENTS];

static uint32_t noOfTimerGeneratedEvents = 0;
static uint32_t noOfTimer1GeneratedEvents = 0;
static uint32_t noOfTimerGeneratedEvents_agent1 = 0;
static uint32_t noOfTimer1GeneratedEvents_agent1 = 0;

static bool agentCreated = false;
static bool agent1Created = false;

static void resetVariables(void);

static void run_sampleTimerCanBeArmedWithGivenTimeout(void);
static void run_sampleTimerShouldGenerateTimeoutAfterGivenTimeoutPasses(void);
static void run_twoSampleTimersShouldGenerateTimeoutAfterDiferentTimeouts(void);
static void run_twoSampleTimersShouldGenerateTimeoutAfterSameTimeout(void);
static void run_firstSampleTimerIsDisarmedBeforeTimingOutAndSecondShouldTimeoutOnly(void);
static void run_twoTimersRegisteredForDifferentAgentsGenerateTimeout(void);

void RF_enterCriticalSection() {}
void RF_exitCriticalSection() {}

int main()
{
	UNITY_BEGIN();
	initiateTestingUtilities();
	RUN_TEST(run_sampleTimerCanBeArmedWithGivenTimeout);
	RUN_TEST(run_sampleTimerShouldGenerateTimeoutAfterGivenTimeoutPasses);
	RUN_TEST(run_twoSampleTimersShouldGenerateTimeoutAfterDiferentTimeouts);
	RUN_TEST(run_twoSampleTimersShouldGenerateTimeoutAfterSameTimeout);
	RUN_TEST(run_firstSampleTimerIsDisarmedBeforeTimingOutAndSecondShouldTimeoutOnly);
	RUN_TEST(run_twoTimersRegisteredForDifferentAgentsGenerateTimeout);
	return UNITY_END();
}

void run_twoTimersRegisteredForDifferentAgentsGenerateTimeout(void)
{
	resetVariables();
	RFBaseAgentConstructor(&timerAgentInstance.baseAgent, timerAgentEventHandler);
	RFTimerConstructor(&timerAgentInstance.baseAgent, &timerAgentInstance.sampleTimer, SAMPLE_EVENT_SIG);
	RFTimerConstructor(&timerAgentInstance.baseAgent, &timerAgentInstance.sampleTimer1, SAMPLE_EVENT_1_SIG);
	RFBaseAgentConstructor(&timerAgent1Instance.baseAgent, timerAgent1EventHandler);
	RFTimerConstructor(&timerAgent1Instance.baseAgent, &timerAgent1Instance.sampleTimer, SAMPLE_EVENT_SIG);
	RFTimerConstructor(&timerAgent1Instance.baseAgent, &timerAgent1Instance.sampleTimer1, SAMPLE_EVENT_1_SIG);
	agentCreated = true;
	agent1Created = true;

	uint32_t givenTimeoutInTicks = (uint32_t)TIMEOUT_OF_SAMPLE_TIMER_0_IN_MS;
	uint32_t givenTimeout1InTicks = (uint32_t)TIMEOUT_OF_SAMPLE_TIMER_1_IN_MS;
	RFTimer_armTimer(&timerAgentInstance.sampleTimer, givenTimeoutInTicks);
	RFTimer_armTimer(&timerAgentInstance.sampleTimer1, givenTimeout1InTicks);
	RFTimer_armTimer(&timerAgent1Instance.sampleTimer, givenTimeoutInTicks);
	RFTimer_armTimer(&timerAgent1Instance.sampleTimer1, givenTimeout1InTicks);

	accelerateTimeByNTicksAndHandleGeneratedEvents(givenTimeoutInTicks);
	TEST_ASSERT(noOfTimerGeneratedEvents == 1);
	TEST_ASSERT(noOfTimerGeneratedEvents_agent1 == 1);

	accelerateTimeByNTicksAndHandleGeneratedEvents(givenTimeout1InTicks-givenTimeoutInTicks);
	TEST_ASSERT(noOfTimerGeneratedEvents == 1);
	TEST_ASSERT(noOfTimer1GeneratedEvents == 1);
	TEST_ASSERT(noOfTimerGeneratedEvents_agent1 == 1);
	TEST_ASSERT(noOfTimer1GeneratedEvents_agent1 == 1);
}

void run_firstSampleTimerIsDisarmedBeforeTimingOutAndSecondShouldTimeoutOnly(void)
{
	resetVariables();
	RFBaseAgentConstructor(&timerAgentInstance.baseAgent, timerAgentEventHandler);
	RFTimerConstructor(&timerAgentInstance.baseAgent, &timerAgentInstance.sampleTimer, SAMPLE_EVENT_SIG);
	RFTimerConstructor(&timerAgentInstance.baseAgent, &timerAgentInstance.sampleTimer1, SAMPLE_EVENT_1_SIG);
	agentCreated = true;

	uint32_t givenTimeoutInTicks = (uint32_t)TIMEOUT_OF_SAMPLE_TIMER_0_IN_MS;
	uint32_t givenTimeout1InTicks = (uint32_t)TIMEOUT_OF_SAMPLE_TIMER_1_IN_MS;
	RFTimer_armTimer(&timerAgentInstance.sampleTimer, givenTimeoutInTicks);
	RFTimer_armTimer(&timerAgentInstance.sampleTimer1, givenTimeout1InTicks);

	accelerateTimeByNTicksAndHandleGeneratedEvents(givenTimeoutInTicks-1);
	TEST_ASSERT(noOfTimerGeneratedEvents == 0);
	TEST_ASSERT(noOfTimer1GeneratedEvents == 0);

	RFTimer_disarmTimer(&timerAgentInstance.sampleTimer);
	accelerateTimeByNTicksAndHandleGeneratedEvents((uint32_t)1);
	TEST_ASSERT(noOfTimerGeneratedEvents == 0);
	TEST_ASSERT(noOfTimer1GeneratedEvents == 0);

	accelerateTimeByNTicksAndHandleGeneratedEvents(givenTimeout1InTicks-givenTimeoutInTicks);
	TEST_ASSERT(noOfTimerGeneratedEvents == 0);
	TEST_ASSERT(noOfTimer1GeneratedEvents == 1);
}

void run_twoSampleTimersShouldGenerateTimeoutAfterSameTimeout(void)
{
	resetVariables();
	RFBaseAgentConstructor(&timerAgentInstance.baseAgent, timerAgentEventHandler);
	RFTimerConstructor(&timerAgentInstance.baseAgent, &timerAgentInstance.sampleTimer, SAMPLE_EVENT_SIG);
	RFTimerConstructor(&timerAgentInstance.baseAgent, &timerAgentInstance.sampleTimer1, SAMPLE_EVENT_1_SIG);
	agentCreated = true;

	uint32_t givenTimeoutInTicks = (uint32_t)TIMEOUT_OF_SAMPLE_TIMER_0_IN_MS;
	RFTimer_armTimer(&timerAgentInstance.sampleTimer, givenTimeoutInTicks);
	RFTimer_armTimer(&timerAgentInstance.sampleTimer1, givenTimeoutInTicks);

	accelerateTimeByNTicksAndHandleGeneratedEvents(givenTimeoutInTicks);
	TEST_ASSERT(noOfTimerGeneratedEvents == 1);
	TEST_ASSERT(noOfTimer1GeneratedEvents == 1);
}

void run_twoSampleTimersShouldGenerateTimeoutAfterDiferentTimeouts(void)
{
	resetVariables();
	RFBaseAgentConstructor(&timerAgentInstance.baseAgent, timerAgentEventHandler);
	RFTimerConstructor(&timerAgentInstance.baseAgent, &timerAgentInstance.sampleTimer, SAMPLE_EVENT_SIG);
	RFTimerConstructor(&timerAgentInstance.baseAgent, &timerAgentInstance.sampleTimer1, SAMPLE_EVENT_1_SIG);
	agentCreated = true;

	uint32_t givenTimeoutInTicks = (uint32_t)TIMEOUT_OF_SAMPLE_TIMER_0_IN_MS;
	uint32_t givenTimeout1InTicks = (uint32_t)TIMEOUT_OF_SAMPLE_TIMER_1_IN_MS;
	RFTimer_armTimer(&timerAgentInstance.sampleTimer, givenTimeoutInTicks);
	RFTimer_armTimer(&timerAgentInstance.sampleTimer1, givenTimeout1InTicks);

	accelerateTimeByNTicksAndHandleGeneratedEvents(givenTimeoutInTicks);
	TEST_ASSERT(noOfTimerGeneratedEvents == 1);

	accelerateTimeByNTicksAndHandleGeneratedEvents(givenTimeout1InTicks-givenTimeoutInTicks);
	TEST_ASSERT(noOfTimerGeneratedEvents == 1);
	TEST_ASSERT(noOfTimer1GeneratedEvents == 1);
}

void run_sampleTimerShouldGenerateTimeoutAfterGivenTimeoutPasses(void)
{
	resetVariables();
	RFBaseAgentConstructor(&timerAgentInstance.baseAgent, timerAgentEventHandler);
		RFTimerConstructor(&timerAgentInstance.baseAgent, &timerAgentInstance.sampleTimer, SAMPLE_EVENT_SIG);
	agentCreated = true;
	uint32_t givenTimeoutInTicks = (uint32_t)TIMEOUT_OF_SAMPLE_TIMER_0_IN_MS;

	RFTimer_armTimer(&timerAgentInstance.sampleTimer, givenTimeoutInTicks);
	accelerateTimeByNTicksAndHandleGeneratedEvents(givenTimeoutInTicks);
	TEST_ASSERT(noOfTimerGeneratedEvents == 1);
}

void run_sampleTimerCanBeArmedWithGivenTimeout(void)
{
	resetVariables();
	RFBaseAgentConstructor(&timerAgentInstance.baseAgent, timerAgentEventHandler);
		RFTimerConstructor(&timerAgentInstance.baseAgent, &timerAgentInstance.sampleTimer, SAMPLE_EVENT_SIG);
		agentCreated = true;
	uint32_t givenTimeoutInTicks = (uint32_t)TIMEOUT_OF_SAMPLE_TIMER_0_IN_MS;

	RFTimer_armTimer(&timerAgentInstance.sampleTimer, givenTimeoutInTicks);
	TEST_ASSERT(timerAgentInstance.sampleTimer.isArmed);
	TEST_ASSERT(timerAgentInstance.sampleTimer.ticks == givenTimeoutInTicks);
}

void resetVariables()
{
	agentCreated = false;
	agent1Created = false;

	RFTimer_clearAllTimers();
	noOfTimerGeneratedEvents = 0;
	noOfTimer1GeneratedEvents = 0;
	noOfTimerGeneratedEvents_agent1 = 0;
	noOfTimer1GeneratedEvents_agent1 = 0;

	memset(&timerAgentInstance, 0, sizeof(timerAgent));
	memset(&sampleMemoryPool[0], 0 , sizeof(RFEvent)*MEMORY_POOL_SIZE_IN_EVENTS);
	createEmptyQueue(&timerAgentInstance.baseAgent.FIFOQueue , sampleMemoryPool, sizeof(RFEvent)*MEMORY_POOL_SIZE_IN_EVENTS);

	memset(&timerAgent1Instance, 0, sizeof(timerAgent));
	memset(&sampleMemoryPool1[0], 0 , sizeof(RFEvent)*MEMORY_POOL_SIZE_IN_EVENTS);
	createEmptyQueue(&timerAgent1Instance.baseAgent.FIFOQueue , sampleMemoryPool1, sizeof(RFEvent)*MEMORY_POOL_SIZE_IN_EVENTS);
}

void timerAgentEventHandler(RFAgent* const self, RFEvent *const evt)
{
	switch(evt->signalValue)
	{
	case SAMPLE_EVENT_SIG:
	{
		noOfTimerGeneratedEvents++;
		break;
	}
	case SAMPLE_EVENT_1_SIG:
	{
		noOfTimer1GeneratedEvents++;
		break;
	}
	}
}

void timerAgent1EventHandler(RFAgent* const self, RFEvent *const evt)
{
	switch(evt->signalValue)
	{
	case SAMPLE_EVENT_SIG:
	{
		noOfTimerGeneratedEvents_agent1++;
		break;
	}
	case SAMPLE_EVENT_1_SIG:
	{
		noOfTimer1GeneratedEvents_agent1++;
		break;
	}
	}
}

void accelerateTimeByNTicksAndHandleGeneratedEvents(uint32_t n)
{
	while (n > 0)
	{
		//printf("Current ticks = %d\n", n);
		RFTimer_decreaseTimersByOneTick();
		if (agentCreated)
		{
			while (timerAgentInstance.baseAgent.FIFOQueue.noOfEvents > 0)
					{
						timerAgentInstance.baseAgent.currentHandler(
								&timerAgentInstance.baseAgent,
								timerAgentInstance.baseAgent.FIFOQueue.pop(&timerAgentInstance.baseAgent.FIFOQueue));
						timerAgentInstance.baseAgent.FIFOQueue.removeGarbage(&timerAgentInstance.baseAgent.FIFOQueue);
					}
		}
		if (agent1Created)
				{
					while (timerAgent1Instance.baseAgent.FIFOQueue.noOfEvents > 0)
							{
								timerAgent1Instance.baseAgent.currentHandler(
										&timerAgent1Instance.baseAgent,
										timerAgent1Instance.baseAgent.FIFOQueue.pop(&timerAgent1Instance.baseAgent.FIFOQueue));
								timerAgent1Instance.baseAgent.FIFOQueue.removeGarbage(&timerAgent1Instance.baseAgent.FIFOQueue);
							}
				}
		n--;
	}
}
