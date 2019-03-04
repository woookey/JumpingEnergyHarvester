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
}
