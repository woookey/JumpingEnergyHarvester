#include <CP_HD_Logger.h>
#include <CP_HA_UART.h>
#include <CP_HA_GPIO.h>

/**
 * Initialises the logger
 */
void CP_HD_Logger_initialise(void)
{
	CP_HA_initialiseGPIO(CP_HA_GPIO_LoggerRx);
	CP_HA_initialiseGPIO(CP_HA_GPIO_LoggerTx);
	CP_HA_UART_initialise();
}

/**
 * Send any message packet
 */
void CP_HD_Logger_sendData(void)
{
	CP_HA_UART_sendMessage();
}
