#include <CP_BH_LegControl.h>
#include <assert.h>
#include <RF_dispatcher.h>
#include <RF_timers.h>
#include <systemSignals.h>
#include <CP_HD_MotorControlBoard.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
	RFAgent baseAgent;
	RF_Timer oscillationTimer;
	bool clockwiseOscillationOn;
} LegControlModule_t;

typedef enum
{
	OSCILLATION_CHANGE_SIGNAL = SS_END_OF_SIGNAL_SPACE,
} PrivateSignals;

typedef enum
{
	OSCILLATION_CHANGE_TIMEOUT_IN_MS = 1000U,
} PrivateDefinitions;

static LegControlModule_t LegControlModuleInstance;
RFAgent * const LegControlModule = (RFAgent* const)&LegControlModuleInstance;

static RFHandle InitialState(LegControlModule_t* const me, RFEvent *const evt);
static RFHandle WaitForPower(LegControlModule_t* const me, RFEvent *const evt);
static RFHandle OscillatoryMotionState(LegControlModule_t* const me, RFEvent *const evt);

void CP_BH_LegControlModuleConstructor(RFAgent * const self)
{
	assert(self == LegControlModule);
	LegControlModule_t *const me = (LegControlModule_t* const)self;
	RFBaseAgentConstructor((RFAgent* const)me, &InitialState);
	RFTimerConstructor((RFAgent* const)me, (RF_Timer*)&me->oscillationTimer, OSCILLATION_CHANGE_SIGNAL);
	subscribeAgentToSignal((RFAgent* const)me, SS_CP_BH_POWER_MANAGER_POWER_IS_ON_SIGNAL);
}

RFHandle InitialState(LegControlModule_t* const me, RFEvent *const evt)
{
	(void)evt;
	(void)me;
	// initialise ports for motor drivers
	CP_HD_MotorControlBoard_initialiseMotor(pretensionMotor);
	INITIAL_TRANSITION((RFAgent*)me, &WaitForPower);
}

RFHandle WaitForPower(LegControlModule_t* const me, RFEvent *const evt)
{
	switch (evt->signalValue)
	{
	case RF_INITIAL_SIGNAL:
	case RF_ENTRY_SIGNAL:
	case RF_EXIT_SIGNAL:
	{
		return RF_HANDLED;
	}
	case SS_CP_BH_POWER_MANAGER_POWER_IS_ON_SIGNAL:
	{
		// enable motor driver for pre-tensioner
		CP_HD_MotorControlBoard_enableMotor(pretensionMotor);
		CP_HD_MotorControlBoard_setDirectionClockwise(pretensionMotor);
		EXECUTE_TRANSITION((RFAgent const*)me, &OscillatoryMotionState);
	}
	}
	return RF_UNHANDLED;
}

RFHandle OscillatoryMotionState(LegControlModule_t* const me, RFEvent *const evt)
{
	switch (evt->signalValue)
	{
		case RF_INITIAL_SIGNAL:
		{
			return RF_HANDLED;
		}
		case RF_ENTRY_SIGNAL:
		{
			me->clockwiseOscillationOn = true;
			CP_HD_MotorControlBoard_startPWM(pretensionMotor, (uint8_t)1);
			RFTimer_armTimer((RF_Timer*) &me->oscillationTimer, OSCILLATION_CHANGE_TIMEOUT_IN_MS);
			return RF_HANDLED;
		}
		case OSCILLATION_CHANGE_SIGNAL:
		{
			if (me->clockwiseOscillationOn)
			{
				CP_HD_MotorControlBoard_setDirectionAnticlockwise(pretensionMotor);
			}
			else
			{
				CP_HD_MotorControlBoard_setDirectionClockwise(pretensionMotor);
			}
			me->clockwiseOscillationOn = !me->clockwiseOscillationOn;
			RFTimer_armTimer((RF_Timer*) &me->oscillationTimer, 2U*OSCILLATION_CHANGE_TIMEOUT_IN_MS);
			return RF_HANDLED;
		}
		case RF_EXIT_SIGNAL:
		{
			return RF_HANDLED;
		}
	}
	return RF_UNHANDLED;
}

