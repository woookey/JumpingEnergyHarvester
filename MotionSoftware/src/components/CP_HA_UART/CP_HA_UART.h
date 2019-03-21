#ifndef CP_HA_UART_H
#define CP_HA_UART_H

#include <stdint.h>

void CP_HA_UART_initialise(void);
void CP_HA_UART_sendMessage(uint8_t* data, uint8_t length);

#endif
