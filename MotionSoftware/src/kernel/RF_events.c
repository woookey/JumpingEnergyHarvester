#include <RF_events.h>

RFEvent RFEvent_InitialSignal = {.pendingConsumers = 0, .signalValue = RF_INITIAL_SIGNAL, .eventSize = RFEVENT_SIZE};
RFEvent RFEvent_EntrySignal = {.pendingConsumers = 0, .signalValue = RF_ENTRY_SIGNAL, .eventSize = RFEVENT_SIZE};
RFEvent RFEvent_ExitSignal = {.pendingConsumers = 0, .signalValue = RF_EXIT_SIGNAL, .eventSize = RFEVENT_SIZE};
