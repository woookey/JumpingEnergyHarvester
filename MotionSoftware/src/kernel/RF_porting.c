#include <RF_porting.h>
#include <stdint.h>
#include <assert.h>

#define LOCKED 0
#define UNLOCKED 1

static uint8_t criticalMutex = 1;

void RF_enterCriticalSection(void)
{
	assert(criticalMutex == 1 || criticalMutex == 0);
	while(criticalMutex == LOCKED);
	criticalMutex = LOCKED;
}


void RF_exitCriticalSection(void)
{
	assert(criticalMutex == 0);
	criticalMutex = UNLOCKED;
}

/**
 * TODO: To be unit tested
 */
