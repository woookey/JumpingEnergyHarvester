#include <RF_agents.h>
#include <stdlib.h>
#include <assert.h>

void postEventToAgent(RFAgent* self, RFEvent const * const evt)
{
	assert(self != NULL);
	assert(evt != NULL);
	self->FIFOQueue.push(&self->FIFOQueue, (RFEvent*)evt, evt->eventSize);
}

void RFBaseAgentConstructor(RFAgent* const self, RFHandle (*initialTransition)(RFAgent* const self, RFEvent *const evt))
{
	assert(self != NULL);
	self->currentHandler = initialTransition;
	postEventToAgent(self, (RFEvent const * const) &RFEvent_InitialSignal);
}
