#include <CP_HA_UART.h>
#include <stm32f4xx_hal_dma.h>
#include <stm32f4xx_hal_uart.h>
#include <stm32f4xx_hal_rcc.h>

static UART_HandleTypeDef LoggerUART4 =
{
	.Instance = UART4,
	.Init =
	{
			.BaudRate = 115200,
			.WordLength = UART_WORDLENGTH_8B,
			.StopBits = UART_STOPBITS_1,
			.Parity = UART_PARITY_NONE,
			.Mode = UART_MODE_TX_RX,
			.HwFlowCtl = UART_HWCONTROL_NONE,
			//.OverSampling =
	},
};

void CP_HA_UART_sendMessage(void)
{
	char* x = "\rHello World!\n";
	uint8_t data[1] = {88};
	HAL_UART_Transmit(&LoggerUART4, x, (uint16_t)strlen(x), (uint32_t)1);
}

void CP_HA_UART_initialise(void)
{
	__HAL_RCC_UART4_CLK_ENABLE();

	HAL_UART_Init(&LoggerUART4);
/**
 * The UART HAL driver can be used as follows:


    (#) Initialize the UART low level resources by implementing the HAL_UART_MspInit() API:
        (##) NVIC configuration if you need to use interrupt process (HAL_UART_Transmit_IT()
             and HAL_UART_Receive_IT() APIs):
            (+++) Configure the USARTx interrupt priority.
            (+++) Enable the NVIC USART IRQ handle.

    (#) Program the Baud Rate, Word Length, Stop Bit, Parity, Hardware
        flow control and Mode(Receiver/Transmitter) in the Init structure.

    (#) For the UART asynchronous mode, initialize the UART registers by calling
        the HAL_UART_Init() API.

    (#) For the UART Half duplex mode, initialize the UART registers by calling
        the HAL_HalfDuplex_Init() API.

    (#) For the LIN mode, initialize the UART registers by calling the HAL_LIN_Init() API.

    (#) For the Multi-Processor mode, initialize the UART registers by calling
        the HAL_MultiProcessor_Init() API.

     [..]
       (@) The specific UART interrupts (Transmission complete interrupt,
            RXNE interrupt and Error Interr
 */
}
