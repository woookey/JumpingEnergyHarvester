#include <LEDManager.h>
#include <CP_HD_LEDDriver_mock.h>
#include <CP_HD_LEDDriver.h>
#include <RF_scheduler.h>
#include <RF_dispatcher.h>
#include <systemSignals.h>
#include <unity.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <testing_utils.h>

struct LEDStructure LEDStructureInstance_CPUActivityLED =
{
		.isInitialised = false,
		.isOn = false,
		.noOfCalls = 0,
};
LEDReference CP_HD_CPUActivityLED = &LEDStructureInstance_CPUActivityLED;
struct LEDStructure LEDStructureInstance_powerOnIndicationLED =
{
		.isInitialised = false,
		.isOn = false,
		.noOfCalls = 0,
};
LEDReference CP_HD_powerOnIndicationLED = &LEDStructureInstance_powerOnIndicationLED;

void accelerateTimeByNTicks(uint32_t nTicks)
{
	uint32_t i;
	for (i = 0; i < nTicks; i++)
	{
		RFTimer_decreaseTimersByOneTick();
		runScheduler();
	}
}

static void createLEDManagerSucceedsAndRunsFine(void);

int main()
{
	UNITY_BEGIN();
	RUN_TEST(createLEDManagerSucceedsAndRunsFine);
	UNITY_END();
}

void createLEDManagerSucceedsAndRunsFine(void)
{
	RFEvent LEDManagerPool[10];
	RF_DispatcherCtor();
	startAgent(LEDManager, &LEDManagerConstructor, AGENT_PRIORITY_0,
					&LEDManagerPool[0], sizeof(RFEvent)*10);

	RF_Dispatcher_RegisterNumberOfAgents(1);
	RF_Dispatcher_RegisterNumberOfEvents(SYSTEM_SIGNAL_NUMBER_OF_SIGNALS);
	TEST_ASSERT(LEDManager->currentHandler != NULL);
	runScheduler();
	TEST_ASSERT(isLEDInitialised(&LEDStructureInstance_CPUActivityLED));
	TEST_ASSERT(isLEDSwitchedOn(&LEDStructureInstance_CPUActivityLED));
	TEST_ASSERT(wasLEDCalledNTimes(&LEDStructureInstance_CPUActivityLED, 1));

	uint8_t randomNumberOfPeriods;
	accelerateTimeByNTicks((uint32_t)500*(uint32_t)randomNumberOfPeriods);

	uint32_t expectedNumberOfCalls = (uint32_t)randomNumberOfPeriods+(uint32_t)1;
	if (randomNumberOfPeriods % 2 == 0)
	{
		TEST_ASSERT(isLEDSwitchedOn(&LEDStructureInstance_CPUActivityLED));
	}
	else
	{
		TEST_ASSERT(!isLEDSwitchedOn(&LEDStructureInstance_CPUActivityLED));
	}
}
