#include <RF_queue.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static RFEvent * const popFromQueue(struct RF_BaseQueue* self);
static bool pushToQueue(struct RF_BaseQueue* self, RFEvent* evt, size_t sizeOfEvent);
static void removeGarbageFromQueue(struct RF_BaseQueue* self);


void createEmptyQueue(RF_Queue queue, RFEvent *memoryPoolAddress, size_t memoryPoolSize)
{
	assert(queue != NULL);
	assert(memoryPoolAddress != NULL);
	assert(memoryPoolSize > 0);
	queue->HEAD = &memoryPoolAddress[0];
	queue->TAIL = NULL;
	queue->noOfEvents = 0;
	queue->pop = popFromQueue;
	queue->push = pushToQueue;
	queue->spaceLeft = memoryPoolSize;
	queue->totalSize = memoryPoolSize;
	queue->removeGarbage = removeGarbageFromQueue;
}

/**
 * Returns the pointer to the next event to be dispatched (FIFO basis)
 * Event is removed from the queue by queue cleaner after it has been
 * successfully processed
 *
 * Note: Consumer has to reduce the consumption of event after consuming it, followed
 * by garbage collector cleaning the queue
 */
RFEvent * const popFromQueue(struct RF_BaseQueue* self)
{
	assert(self != NULL);
	assert(self->TAIL != NULL);
	assert(self->HEAD != NULL);
	return (RFEvent* const)self->HEAD;
}

bool pushToQueue(struct RF_BaseQueue* self, RFEvent* evt, size_t sizeOfEvent)
{
	assert(sizeOfEvent > 0);
	assert(evt != NULL);
	assert(self != NULL);
	if (evt->eventSize > self->spaceLeft)
	{
		return false;
	}

	if (self->TAIL == NULL)
	{
		memcpy(self->HEAD, evt, evt->eventSize);
		self->TAIL = self->HEAD;
	}
	else
	{
		self->TAIL = (RFEvent*)((uint64_t)self->TAIL+(uint64_t)self->TAIL->eventSize);
		memcpy(self->TAIL, evt, evt->eventSize);
	}
	self->spaceLeft = self->spaceLeft - evt->eventSize;
	self->noOfEvents++;
	return true;
}

void removeGarbageFromQueue(struct RF_BaseQueue* self)
{
	assert(self != NULL);
	assert(self->noOfEvents >= 1);
	if (self->HEAD->pendingConsumers == 0)
	{
		if (self->noOfEvents > 1)
		{
			uint64_t sizeToShiftTAILLeft = (uint64_t)self->HEAD->eventSize;
			size_t spaceToBeFreed = self->HEAD->eventSize;
			memmove((void*)self->HEAD, (void*)((uint64_t)self->HEAD+(uint64_t)self->HEAD->eventSize), self->totalSize - self->HEAD->eventSize);
			self->TAIL = (RFEvent *)((uint64_t)self->TAIL - (uint64_t)sizeToShiftTAILLeft);
			self->spaceLeft += spaceToBeFreed;
		}
		else if (self->noOfEvents == 1)
		{
			memset(self->HEAD, 0, self->totalSize);
			self->TAIL = NULL;
			self->spaceLeft = self->totalSize;
		}
		else
		{
			assert(false);
		}
		self->noOfEvents--;
	}
}

