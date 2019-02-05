#include <LEDManager.h>
#include <CP_BH_PowerManager.h>
#include <CP_BH_LegControl.h>
#include <CP_BH_LoggingManager.h>
#include <CP_HA_HardwareSetup.h>
#include <RF_events.h>
#include <RF_scheduler.h>
#include <RF_dispatcher.h>
#include <RF_timers.h>
#include <systemSignals.h>
#include <stdbool.h>

int main()
{
	setupHardware();
	RFEvent LEDManagerPool[10];
	RFEvent PowerManagerPool[10];
	RFEvent LegControlModulePool[10];
	RFEvent LoggingManagerPool[10];

	RF_DispatcherCtor();
	RF_Dispatcher_RegisterNumberOfAgents(4);
	RF_Dispatcher_RegisterNumberOfEvents(SYSTEM_SIGNAL_NUMBER_OF_SIGNALS);

	startAgent(LEDManager, &LEDManagerConstructor, AGENT_PRIORITY_0,
						&LEDManagerPool[0], sizeof(RFEvent)*10);
	startAgent(PowerManager, &PowerManagerConstructor, AGENT_PRIORITY_0,
						&PowerManagerPool[0], sizeof(RFEvent)*10);
	startAgent(LegControlModule, &CP_BH_LegControlModuleConstructor, AGENT_PRIORITY_0,
							&LegControlModulePool[0], sizeof(RFEvent)*10);
	startAgent(LoggingManager, &CP_BH_LoggingManagerConstructor, AGENT_PRIORITY_0,
								&LoggingManagerPool[0], sizeof(RFEvent)*10);


	startHardware();
	/**
	 * TODO: Investigate if there should be a lock for starting the framework
	 * before all agents are initialised - just before while loop
	 */
	return 0;
}
