#include <RF_timers.h>
#include <RF_definitions.h>
#include <RF_porting.h>
#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>

static struct
{
	RF_Timer* registeredTimers[RF_MAX_NUMBER_OF_TIMERS];
	uint16_t noOfRegisteredTimers;
} RFRegisteredTimers = {{NULL}, 0};

static bool add_timer(RF_Timer* timerPtr);
#define REGISTER_TIMER(timer) add_timer(timer)

void RFTimerConstructor(RFAgent* agentSubscribed, RF_Timer* timer, uint32_t signal)
{
	assert(agentSubscribed != NULL);
	assert(timer != NULL);
	assert(signal >= 0); // TODO: might need an upper band
	memset(timer, (uint64_t)0, sizeof(RF_Timer));

	timer->agent = agentSubscribed;

	timer->baseEvt.eventSize = sizeof(RFEvent);
	timer->baseEvt.pendingConsumers = 0;
	timer->baseEvt.signalValue = signal;

	timer->isArmed = false;
	timer->ticks = 0;
	assert(REGISTER_TIMER(timer));
}

void RFTimer_armTimer(RF_Timer *timer, uint32_t timeoutInTicks)
{
	assert(timer != NULL);
	assert(timeoutInTicks > 0);
	timer->ticks = timeoutInTicks;
	timer->isArmed = true;
}

void RFTimer_disarmTimer(RF_Timer *timer)
{
	assert(timer != NULL);
	timer->ticks = 0;
	timer->isArmed = false;
}

void RFTimer_decreaseTimersByOneTick(void)
{
	/**
	 * Updating timer has to be an atomic action
	 */
	RF_enterCriticalSection();
	uint16_t timer_i = 0;
	while(timer_i < RFRegisteredTimers.noOfRegisteredTimers)
	{
		RF_Timer* currentTimer = RFRegisteredTimers.registeredTimers[timer_i];
		if (currentTimer->isArmed)
		{
			if (--currentTimer->ticks == 0)
			{
				currentTimer->agent->FIFOQueue.push(&currentTimer->agent->FIFOQueue,
						&currentTimer->baseEvt, currentTimer->baseEvt.eventSize);
				currentTimer->isArmed = false;
			}
		}
		timer_i++;
	}
	RF_exitCriticalSection();
}

bool add_timer(RF_Timer* timerPtr)
{
	if ((RFRegisteredTimers.registeredTimers[RFRegisteredTimers.noOfRegisteredTimers] == NULL)
			&& (RFRegisteredTimers.noOfRegisteredTimers < RF_MAX_NUMBER_OF_TIMERS))
	{
		RFRegisteredTimers.registeredTimers[RFRegisteredTimers.noOfRegisteredTimers] = timerPtr;
		RFRegisteredTimers.noOfRegisteredTimers++;
		return true;
	}
	return false;
}

void RFTimer_clearAllTimers(void)
{
	memset(&RFRegisteredTimers.registeredTimers, (uint64_t)NULL, sizeof(RF_Timer*)*RF_MAX_NUMBER_OF_TIMERS);
	RFRegisteredTimers.noOfRegisteredTimers = 0;
}
