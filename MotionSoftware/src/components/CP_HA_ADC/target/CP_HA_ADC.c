#include <stdint.h>
#include <CP_HA_ADC.h>
#include "ADCDefinition.h"

/**
 * ==============================================================================
  [..]
  (#)Initialize the ADC low level resources by implementing the HAL_ADC_MspInit():
       (##) Enable the ADC interface clock using __HAL_RCC_ADC_CLK_ENABLE()
       (##) ADC pins configuration
             (+++) Enable the clock for the ADC GPIOs using the following function:
                   __HAL_RCC_GPIOx_CLK_ENABLE()
             (+++) Configure these ADC pins in analog mode using HAL_GPIO_Init()
       (##) In case of using interrupts (e.g. HAL_ADC_Start_IT())
             (+++) Configure the ADC interrupt priority using HAL_NVIC_SetPriority()
             (+++) Enable the ADC IRQ handler using HAL_NVIC_EnableIRQ()
             (+++) In ADC IRQ handler, call HAL_ADC_IRQHandler()
       (##) In case of using DMA to control data transfer (e.g. HAL_ADC_Start_DMA())
             (+++) Enable the DMAx interface clock using __HAL_RCC_DMAx_CLK_ENABLE()
             (+++) Configure and enable two DMA streams stream for managing data
                 transfer from peripheral to memory (output stream)
             (+++) Associate the initialized DMA handle to the CRYP DMA handle
                 using  __HAL_LINKDMA()
             (+++) Configure the priority and enable the NVIC for the transfer complete
                 interrupt on the two DMA Streams. The output stream should have higher
                 priority than the input stream.

    *** Configuration of ADC, groups regular/injected, channels parameters ***
  ==============================================================================
  [..]
  (#) Configure the ADC parameters (resolution, data alignment, ...)
      and regular group parameters (conversion trigger, sequencer, ...)
      using function HAL_ADC_Init().

  (#) Configure the channels for regular group parameters (channel number,
      channel rank into sequencer, ..., into regular group)
      using function HAL_ADC_ConfigChannel().

  (#) Optionally, configure the injected group parameters (conversion trigger,
      sequencer, ..., of injected group)
      and the channels for injected group parameters (channel number,
      channel rank into sequencer, ..., into injected group)
      using function HAL_ADCEx_InjectedConfigChannel().

  (#) Optionally, configure the analog watchdog parameters (channels
      monitored, thresholds, ...) using function HAL_ADC_AnalogWDGConfig().

  (#) Optionally, for devices with several ADC instances: configure the
      multimode parameters using function HAL_ADCEx_MultiModeConfigChannel().

                       *** Execution of ADC conversions ***
  ==============================================================================
  [..]
  (#) ADC driver can be used among three modes: polling, interruption,
      transfer by DMA.

     *** Polling mode IO operation ***
     =================================
     [..]
       (+) Start the ADC peripheral using HAL_ADC_Start()
       (+) Wait for end of conversion using HAL_ADC_PollForConversion(), at this stage
           user can specify the value of timeout according to his end application
       (+) To read the ADC converted values, use the HAL_ADC_GetValue() function.
       (+) Stop the ADC peripheral using HAL_ADC_Stop()

 */


/*
struct ADCStruct AngularSensorJoint1 =
{
		.GPIOTypeDef_t = GPIOA,
		.GPIOInitTypeDef_t =
		{
			.Pin = GPIO_PIN_2,
			.Mode = GPIO_MODE_ANALOG,
			.Pull = GPIO_PULLDOWN,
			.Speed = GPIO_SPEED_FREQ_VERY_HIGH,
		},
};

CP_HA_GPIO CP_HA_GPIO_pretensionMotorClockwiseDirection = &pretensionMotorClockwiseDirectionInstance;
*/
static struct ADCStruct AngularSensorJoint1Instance;
CP_HA_ADC CP_HA_ADC_angularSensorJoint1 = &AngularSensorJoint1Instance;


void CP_HA_initialiseADC(CP_HA_ADC ADCInstance)
{
}

uint8_t CP_HA_readADC(CP_HA_ADC ADCInstance)
{
	return (uint8_t)100;
}
