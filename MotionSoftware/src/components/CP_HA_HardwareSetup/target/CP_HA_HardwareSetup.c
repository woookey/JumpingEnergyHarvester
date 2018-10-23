#include <CP_HA_HardwareSetup.h>
#include <stm32f4xx.h>
#include <stm32f4xx_hal_conf.h>
#include <stm32f4xx_hal_rcc.h>
#include <stm32f4xx_hal_rcc_ex.h>
#include <stm32f4xx_hal.h>
#include <RF_timers.h>
#include <RF_scheduler.h>
#include <assert.h>
#include <stdbool.h>

static void initClocks(void)
{
	// TODO: Verify the speed of clock
    HAL_RCC_DeInit();
    RCC_OscInitTypeDef rccOscInstance =
    {
    		.OscillatorType = RCC_OSCILLATORTYPE_HSE,
			.HSEState = RCC_HSE_ON,
			.LSEState = RCC_LSE_OFF,
			.HSIState = RCC_HSI_OFF,
			.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT,
			.LSIState = RCC_LSI_OFF,
			.PLL =
			{
					.PLLState = RCC_PLL_ON,
					.PLLSource = RCC_PLLSOURCE_HSE,
					.PLLM = 8,
					.PLLN = 336,
					.PLLP = RCC_PLLP_DIV2,
					.PLLQ = 7,
			},
    };
    assert(HAL_RCC_OscConfig(&rccOscInstance) == HAL_OK);

    RCC_ClkInitTypeDef rccClkInstance =
    {
    		  .ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK,
    		  .SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK,
    		  .AHBCLKDivider = RCC_SYSCLK_DIV1,
    		  .APB1CLKDivider = RCC_HCLK_DIV4,
    		  .APB2CLKDivider = RCC_HCLK_DIV2,
    };

    assert(HAL_RCC_ClockConfig(&rccClkInstance, FLASH_ACR_LATENCY_5WS) == HAL_OK);
}

static void initPorts(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
}

void setupHardware(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	initClocks();
	initPorts();
}
void startHardware(void)
{
	while(true) {}
}

/**
 * Interrupt Handlers
 */
void SysTick_Handler(void)
{
	HAL_IncTick();
	RFTimer_decreaseTimersByOneTick();
	runScheduler();
}
