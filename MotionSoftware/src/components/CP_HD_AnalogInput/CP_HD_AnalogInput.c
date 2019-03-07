#include <CP_HA_GPIO.h>
#include <CP_HD_AnalogInput.h>
#include <CP_HA_ADC.h>

/**
 * Initialises specific analog inputs
 */
void CP_HD_AnalogInput_initialise(void)
{
	CP_HA_initialiseGPIO(CP_HA_GPIO_angularSensorJoint1);
	CP_HA_initialiseADC(CP_HA_ADC_angularSensorJoint1);
}

/**
 * Read data
 */
void CP_HD_AnalogInput_readData(void)
{
	uint8_t data;
	data = CP_HA_readADC(CP_HA_ADC_angularSensorJoint1);
	CP_HD_AnalogInput_readDataCallback(data);
}
