#include <unity.h>
#include <testing_utils.h>
#include <stdbool.h>
#include <RF_dispatcher.h>
#include <RF_agents.h>
#include <string.h>

#define SIZE_OF_MEMORY_POOL_IN_EVENTS 10
#define REGISTERED_SIGNALS 151

static RFEvent sampleEvt =
{
	.eventSize = sizeof(RFEvent),
	.pendingConsumers = 0,
	.signalValue = 150,
};

static RFEvent sampleEvtTwo =
{
	.eventSize = sizeof(RFEvent),
	.pendingConsumers = 0,
	.signalValue = 130,
};

static uint16_t noOfCallsToSampleAgent;
static uint16_t noOfCallsToSampleAgentTwo;
static RFAgent agentSample;
static RFAgent agentSampleTwo;
static RFEvent memoryPool[SIZE_OF_MEMORY_POOL_IN_EVENTS];
static RFEvent memoryPoolTwo[SIZE_OF_MEMORY_POOL_IN_EVENTS];
static void agentSampleCurrentHandler(struct RFBaseAgent* const self, RFEvent *const evt);
static void agentSampleCurrentHandlerTwo(struct RFBaseAgent* const self, RFEvent *const evt);

static void run_SampleAgentIsSubscribedToSampleEventAndSampleEventIsPublished(void);
static void run_SampleAgentIsSubscribedToSampleEventsAndTwoDifferentSampleEventsArePublished(void);
static void run_SampleAgentUnsubscribesToSampleEvent(void);
static void run_TwoAgentsAreSubscribedToSampleEventsWhichAreBeingPublishedAndOneUnsubscribes(void);
static void run_TwoAgentAreUnsubscribedToEventAndEventIsPublished(void);

static void clearVariables(void);
static void consumeEventsBySampleAgent(void);
static void consumeEventsBySampleAgentTwo(void);

void RF_enterCriticalSection() {}
void RF_exitCriticalSection() {}

int main() {
	UNITY_BEGIN();
	RUN_TEST(run_SampleAgentIsSubscribedToSampleEventAndSampleEventIsPublished);
	RUN_TEST(run_SampleAgentIsSubscribedToSampleEventsAndTwoDifferentSampleEventsArePublished);
	RUN_TEST(run_SampleAgentUnsubscribesToSampleEvent);
	RUN_TEST(run_TwoAgentsAreSubscribedToSampleEventsWhichAreBeingPublishedAndOneUnsubscribes);
	RUN_TEST(run_TwoAgentAreUnsubscribedToEventAndEventIsPublished);
	return UNITY_END();
}

void run_SampleAgentUnsubscribesToSampleEvent(void)
{
	clearVariables();
	RF_Dispatcher_RegisterNumberOfEvents(REGISTERED_SIGNALS);
	RF_Dispatcher_RegisterNumberOfAgents(1);
	subscribeAgentToSignal(&agentSample, sampleEvtTwo.signalValue);
	publishEvent(&sampleEvtTwo);
	consumeEventsBySampleAgent();
	TEST_ASSERT(noOfCallsToSampleAgent == 1);
	unsubscribeAgentToSignal(&agentSample, sampleEvtTwo.signalValue);
	publishEvent(&sampleEvtTwo);
	consumeEventsBySampleAgent();
	TEST_ASSERT(noOfCallsToSampleAgent == 1);
}

void run_TwoAgentAreUnsubscribedToEventAndEventIsPublished(void)
{
	clearVariables();
	RF_Dispatcher_RegisterNumberOfEvents(REGISTERED_SIGNALS);
	RF_Dispatcher_RegisterNumberOfAgents(2);
	subscribeAgentToSignal(&agentSample, sampleEvt.signalValue);
	subscribeAgentToSignal(&agentSampleTwo, sampleEvt.signalValue);
	publishEvent(&sampleEvt);
	consumeEventsBySampleAgent();
	consumeEventsBySampleAgentTwo();
	TEST_ASSERT(noOfCallsToSampleAgent == 1);
	TEST_ASSERT(noOfCallsToSampleAgentTwo == 1);
	unsubscribeAgentToSignal(&agentSample, sampleEvt.signalValue);
	unsubscribeAgentToSignal(&agentSampleTwo, sampleEvt.signalValue);
	publishEvent(&sampleEvt);
	consumeEventsBySampleAgent();
	consumeEventsBySampleAgentTwo();
	TEST_ASSERT(noOfCallsToSampleAgent == 1);
	TEST_ASSERT(noOfCallsToSampleAgentTwo == 1);
}

void run_TwoAgentsAreSubscribedToSampleEventsWhichAreBeingPublishedAndOneUnsubscribes(void)
{
	clearVariables();
	RF_Dispatcher_RegisterNumberOfEvents(REGISTERED_SIGNALS);
	RF_Dispatcher_RegisterNumberOfAgents(2);
	subscribeAgentToSignal(&agentSample, sampleEvt.signalValue);
	subscribeAgentToSignal(&agentSampleTwo, sampleEvtTwo.signalValue);
	publishEvent(&sampleEvt);
	publishEvent(&sampleEvtTwo);
	consumeEventsBySampleAgent();
	consumeEventsBySampleAgentTwo();
	TEST_ASSERT(noOfCallsToSampleAgent == 1);
	TEST_ASSERT(noOfCallsToSampleAgentTwo == 1);
	subscribeAgentToSignal(&agentSample, sampleEvtTwo.signalValue);
	publishEvent(&sampleEvtTwo);
	consumeEventsBySampleAgent();
	consumeEventsBySampleAgentTwo();
	TEST_ASSERT(noOfCallsToSampleAgent == 2);
	TEST_ASSERT(noOfCallsToSampleAgentTwo == 2);
	unsubscribeAgentToSignal(&agentSampleTwo, sampleEvtTwo.signalValue);
	publishEvent(&sampleEvtTwo);
	consumeEventsBySampleAgent();
	consumeEventsBySampleAgentTwo();
	TEST_ASSERT(noOfCallsToSampleAgent == 3);
	TEST_ASSERT(noOfCallsToSampleAgentTwo == 2);
}

void run_SampleAgentIsSubscribedToSampleEventsAndTwoDifferentSampleEventsArePublished(void)
{
	clearVariables();
	RF_Dispatcher_RegisterNumberOfEvents(REGISTERED_SIGNALS);
	RF_Dispatcher_RegisterNumberOfAgents(1);
	subscribeAgentToSignal(&agentSample, sampleEvt.signalValue);
	subscribeAgentToSignal(&agentSample, sampleEvtTwo.signalValue);
	publishEvent(&sampleEvt);
	publishEvent(&sampleEvtTwo);
	consumeEventsBySampleAgent();
	consumeEventsBySampleAgent();
	TEST_ASSERT(noOfCallsToSampleAgent == 2);
}

void run_SampleAgentIsSubscribedToSampleEventAndSampleEventIsPublished(void)
{
	clearVariables();
	RF_Dispatcher_RegisterNumberOfEvents(REGISTERED_SIGNALS);
	RF_Dispatcher_RegisterNumberOfAgents(1);
	subscribeAgentToSignal(&agentSample, sampleEvt.signalValue);
	publishEvent(&sampleEvt);
	consumeEventsBySampleAgent();
	TEST_ASSERT(noOfCallsToSampleAgent == 1);
}

void clearVariables(void)
{
	initiateTestingUtilities();
	memset(&agentSample, 0, sizeof(RFAgent));
	memset(&agentSampleTwo, 0 , sizeof(RFAgent));
	createEmptyQueue(&agentSample.FIFOQueue, memoryPool, sizeof(RFEvent)*SIZE_OF_MEMORY_POOL_IN_EVENTS);
	RFBaseAgentConstructor((RFAgent *const)&agentSample, &agentSampleCurrentHandler);
	consumeEventsBySampleAgent();
	createEmptyQueue(&agentSampleTwo.FIFOQueue, memoryPoolTwo, sizeof(RFEvent)*SIZE_OF_MEMORY_POOL_IN_EVENTS);
	RFBaseAgentConstructor((RFAgent *const)&agentSampleTwo, &agentSampleCurrentHandlerTwo);
	consumeEventsBySampleAgentTwo();
	RF_DispatcherCtor();
	noOfCallsToSampleAgent = 0;
	noOfCallsToSampleAgentTwo = 0;
}

void agentSampleCurrentHandler(struct RFBaseAgent* const self, RFEvent *const evt)
{
	(void)self;
	(void)evt;
	noOfCallsToSampleAgent++;
}

void agentSampleCurrentHandlerTwo(struct RFBaseAgent* const self, RFEvent *const evt)
{
	(void)self;
	(void)evt;
	noOfCallsToSampleAgentTwo++;
}

void consumeEventsBySampleAgent(void)
{
	if (agentSample.FIFOQueue.noOfEvents > 0)
	{
		RFEvent* const evt = agentSample.FIFOQueue.pop(&agentSample.FIFOQueue);
		agentSample.currentHandler(&agentSample, evt);
		agentSample.FIFOQueue.removeGarbage(&agentSample.FIFOQueue);
	}
}

void consumeEventsBySampleAgentTwo(void)
{
	if (agentSampleTwo.FIFOQueue.noOfEvents > 0)
	{
		RFEvent* const evt = agentSampleTwo.FIFOQueue.pop(&agentSampleTwo.FIFOQueue);
		agentSampleTwo.currentHandler(&agentSampleTwo, evt);
		agentSampleTwo.FIFOQueue.removeGarbage(&agentSampleTwo.FIFOQueue);
	}
}
