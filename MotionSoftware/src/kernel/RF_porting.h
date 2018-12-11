/**
 * Includes functions for critical sections and increasing timers
 * Functions are to be ran from the application using the framework
 */
#ifndef RF_PORTING_H
#define RF_PORTING_H

/**
 * Entering critical sections should disable
 * asynchronous reception of events such as interrupts
 *
 * Note: entering critical section is to be implemented
 * in application code
 */
void RF_enterCriticalSection(void);

/**
 * Exiting critical sections should enable
 * asynchronous reception of events such as interrupts
 *
 * Note: exiting critical section is to be implemented
 * in application code
 */
void RF_exitCriticalSection(void);

#endif
