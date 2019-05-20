#ifndef CP_HD_ANALOG_INPUT_H
#define CP_HD_ANALOG_INPUT_H

#include <stdint.h>

/**
 * Initialises specific analog inputs
 */
void CP_HD_AnalogInput_initialise(void);

/**
 * Receive data
 */
void CP_HD_AnalogInput_readData(void);

/**
 * Application layer implementation
 */
extern void CP_HD_AnalogInput_readDataCallback(uint8_t* analogReadings);

#endif
