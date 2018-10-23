#ifndef SYSTEM_SIGNALS_H
#define SYSTEM_SIGNALS_H

#include <RF_events.h>

typedef enum systemSignalSpace
{
	SS_START_OF_SIGNAL_SPACE = RF_LAST_SIGNAL,

	SS_END_OF_SIGNAL_SPACE,
	SYSTEM_SIGNAL_NUMBER_OF_SIGNALS = SS_END_OF_SIGNAL_SPACE,
} systemSignalSpace;

#endif
