#ifndef RF_TIMERS_H
#define RF_TIMERS_H

#include <RF_events.h>
#include <RF_agents.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * All Timer events are based on sysTick with
 * a pre-defined frequency. By default 1ms is
 * the lowest resolution
 */
typedef struct
{
	RFEvent baseEvt;
	RFAgent* agent;
	uint32_t ticks;
	bool isArmed;
} RF_Timer;

/**
 * Constructs a timer event for a given subscribed agent
 */
void RFTimerConstructor(RFAgent* agentSubscribed, RF_Timer* timer, uint32_t signal);

/**
 * Arms the timer to a specified timeout in construction
 */
void RFTimer_armTimer(RF_Timer *timer, uint32_t timeoutInTicks);

/**
 * Disarms the timer
 */
void RFTimer_disarmTimer(RF_Timer *timer);

/**
 * Decreases all registered and armed timers by one tick
 */
void RFTimer_decreaseTimersByOneTick(void);

/**
 * Clears all timers
 * TODO: For future destruct specific timers instead all of them
 */
void RFTimer_clearAllTimers(void);

#endif
