#include <CP_HD_LEDDriver.h>
#include <unity.h>
#include <mock.h>
#include <stdio.h>

static void initialisingLEDsTest(void);
static void switchingLEDsOnAndOffTest(void);
/*static void togglingLEDsTest(void);
static void toggleLEDNTimes(LEDReference led);*/

// Testing variables
struct LEDStructure
{
	CP_HA_LEDStruct* led;
	bool isInitialised;
	bool isOn;
};
static struct LEDStructure LED_t =
{
		.led = &LEDTypeSample,
		.isInitialised = false,
		.isOn = false,
};
LEDReference CP_HD_LED_t = &LED_t;


static void resetVariables()
{
	CP_HD_LED_t->isInitialised = false;
	CP_HD_LED_t->isOn = false;
}

int main()
{
	UNITY_BEGIN();
	RUN_TEST(initialisingLEDsTest);
	RUN_TEST(switchingLEDsOnAndOffTest);
	return UNITY_END();
}

void initialisingLEDsTest(void)
{
	resetVariables();
	resetLEDs();

	// Testing CPUActivityLED initialisation
	CP_HD_LED_initialiseLED(CP_HD_CPUActivityLED);
	TEST_ASSERT(isCPUActivityLEDInitialised());
	TEST_ASSERT(!ispowerOnIndicationLEDInitialised());
	TEST_ASSERT(!isexecutingIndicationLEDInitialised());
	TEST_ASSERT(!issafetyStopIndicationLEDInitialised());

	TEST_ASSERT(numberOfCallsToCPUActivityLED() == 1);
	TEST_ASSERT(numberOfCallsTopowerOnIndicationLED() == 0);
	TEST_ASSERT(numberOfCallsToexecutingIndicationLED() == 0);
	TEST_ASSERT(numberOfCallsTosafetyStopIndicationLED() == 0);

	// Testing powerOnIndicationLED initialisation
	CP_HD_LED_initialiseLED(CP_HD_powerOnIndicationLED);
	TEST_ASSERT(isCPUActivityLEDInitialised());
	TEST_ASSERT(ispowerOnIndicationLEDInitialised());
	TEST_ASSERT(!isexecutingIndicationLEDInitialised());
	TEST_ASSERT(!issafetyStopIndicationLEDInitialised());

	TEST_ASSERT(numberOfCallsToCPUActivityLED() == 1);
	TEST_ASSERT(numberOfCallsTopowerOnIndicationLED() == 1);
	TEST_ASSERT(numberOfCallsToexecutingIndicationLED() == 0);
	TEST_ASSERT(numberOfCallsTosafetyStopIndicationLED() == 0);

	// Testing executingIndicationLED initialisation
	CP_HD_LED_initialiseLED(CP_HD_executingIndicationLED);
	TEST_ASSERT(isCPUActivityLEDInitialised());
	TEST_ASSERT(ispowerOnIndicationLEDInitialised());
	TEST_ASSERT(isexecutingIndicationLEDInitialised());
	TEST_ASSERT(!issafetyStopIndicationLEDInitialised());

	TEST_ASSERT(numberOfCallsToCPUActivityLED() == 1);
	TEST_ASSERT(numberOfCallsTopowerOnIndicationLED() == 1);
	TEST_ASSERT(numberOfCallsToexecutingIndicationLED() == 1);
	TEST_ASSERT(numberOfCallsTosafetyStopIndicationLED() == 0);

	// Testing safetyStopIndicationLED initialisation
	CP_HD_LED_initialiseLED(CP_HD_safetyStopIndicationLED);
	TEST_ASSERT(isCPUActivityLEDInitialised());
	TEST_ASSERT(ispowerOnIndicationLEDInitialised());
	TEST_ASSERT(isexecutingIndicationLEDInitialised());
	TEST_ASSERT(issafetyStopIndicationLEDInitialised());

	TEST_ASSERT(numberOfCallsToCPUActivityLED() == 1);
	TEST_ASSERT(numberOfCallsTopowerOnIndicationLED() == 1);
	TEST_ASSERT(numberOfCallsToexecutingIndicationLED() == 1);
	TEST_ASSERT(numberOfCallsTosafetyStopIndicationLED() == 1);
}

void switchingLEDsOnAndOffTest(void)
{
	resetVariables();
	resetLEDs();
	CP_HD_LED_initialiseLED(CP_HD_LED_t);
	printf("%d\n", isCPUActivityLEDInitialised());
	//TEST_ASSERT(isCPUActivityLEDInitialised());
	//TEST_ASSERT(numberOfCallsToCPUActivityLED() == 1);
}

/*void togglingLEDsTest(void)
{
	resetLEDs();
	CP_HD_LED_initialiseLED(CP_HD_powerOnIndicationLED);
	uint32_t noOfToggles
}*/

/*void toggleLEDNTimes(LEDReference led, uint32_t N)
{
	bool switchOn = true;
	uint32_t i;
	for (i = 0; i < N; i++)
	{
		if (switchOn)
		{
			CP_HD_LED_switchLEDOn()
		}
	}

}*/
/*
 * bool isLEDInitialised(CP_HA_LEDStruct ledRef);
uint32_t numberOfCallsToLED(CP_HA_LEDStruct ledRef);

void CP_HD_LED_switchLEDOn(LEDReference ledRef);
void CP_HD_LED_switchLEDOff(LEDReference ledRef);

LEDReference CP_HD_CPUActivityLED;
LEDReference CP_HD_powerOnIndicationLED;
LEDReference CP_HD_executingIndicationLED;
LEDReference CP_HD_safetyStopIndicationLED;


bool isCPUActivityLEDInitialised(void) {return isLEDInitialised(CPUActivityLED);}
bool ispowerOnIndicationLEDInitialised(void) {return isLEDInitialised(powerOnIndicationLED);}
bool isexecutingIndicationLEDInitialised(void) {return isLEDInitialised(executingIndicationLED);};
bool issafetyStopIndicationLEDInitialised(void) {return isLEDInitialised(safetyStopIndicationLED);};


uint32_t numberOfCallsToCPUActivityLED(void) {return numberOfCallsToLED(CPUActivityLED);};
uint32_t numberOfCallsTopowerOnIndicationLED(void) {return numberOfCallsToLED(powerOnIndicationLED);};
uint32_t numberOfCallsToexecutingIndicationLED(void) {return numberOfCallsToLED(executingIndicationLED);};
uint32_t numberOfCallsTosafetyStopIndicationLED(void) {return numberOfCallsToLED(safetyStopIndicationLED);};

 */
