#include <CP_HA_UART.h>
#include <string.h>
#include <stdio.h>

void CP_HA_UART_initialise(void)
{
	printf("Logger - UART initialised\n");
}

void CP_HA_UART_sendMessage(uint8_t* data, uint8_t length)
{
	//char* x = "Hello World!\n";
	printf("Logger - UART: [%d]\n", data[0]);
}
