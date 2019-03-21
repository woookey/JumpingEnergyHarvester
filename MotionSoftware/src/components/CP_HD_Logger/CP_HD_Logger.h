#ifndef CP_HD_LOGGER_H
#define CP_HD_LOGGER_H

#include <stdint.h>

/**
 * Initialises the logger
 */
void CP_HD_Logger_initialise(void);

/**
 * Send any message packet
 */
void CP_HD_Logger_sendData(uint8_t* data, uint8_t length);

#endif
