#ifndef ROBOTIC_FRAMEWORK_QUEUE_H
#define ROBOTIC_FRAMEWORK_QUEUE_H

#include <RF_events.h>
#include <stdbool.h>

/**
 * FIFO Queue
 */
struct RF_BaseQueue
{
	RFEvent *HEAD;
	RFEvent * TAIL;
	size_t totalSize;
	size_t spaceLeft;
	uint32_t noOfEvents;
	bool (*push)(struct RF_BaseQueue* self, RFEvent* evt, size_t sizeOfEvent);
	RFEvent * const (*pop)(struct RF_BaseQueue* self);
	void (*removeGarbage)(struct RF_BaseQueue* self);
};

typedef struct RF_BaseQueue RF_Queue_t;
typedef RF_Queue_t *const RF_Queue;

void createEmptyQueue(RF_Queue queue, RFEvent *memoryPoolAddress, size_t memoryPoolSize);

#endif
