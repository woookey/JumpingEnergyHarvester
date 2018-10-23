#include <CP_HA_HardwareSetup.h>
#include <time.h>
#include <stdbool.h>

#define MS_PER_SEC 1000

void setupHardware(void) {}
void startHardware(void)
{
	// Initiate synthetic timing
		clock_t t;
		t = clock();
		/**
		 * Run scheduler and decrease timers every 1ms
		 */
		while(true)
		{
			if ((float)(clock()-t)/((float)CLOCKS_PER_SEC/(float)MS_PER_SEC) >= (float)1)
			{
				RFTimer_decreaseTimersByOneTick();
				runScheduler();
				t = clock();
			}
		}
}
