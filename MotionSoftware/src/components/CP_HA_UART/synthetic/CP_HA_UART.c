#include <CP_HA_UART.h>
#include <string.h>
#include <stdio.h>

void CP_HA_UART_initialise(void)
{
	printf("Logger - UART initialised\n");
}

void CP_HA_UART_sendMessage(void)
{
	char* x = "Hello World!\n";
	printf("Logger - UART: %s", x);
}
