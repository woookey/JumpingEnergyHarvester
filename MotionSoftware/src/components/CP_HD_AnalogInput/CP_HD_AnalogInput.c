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

	CP_HA_initialiseGPIO(CP_HA_GPIO_angularSensorJoint2);
	CP_HA_initialiseADC(CP_HA_ADC_angularSensorJoint2);

	CP_HA_initialiseGPIO(CP_HA_GPIO_angularSensorPretensionMotor);
	CP_HA_initialiseADC(CP_HA_ADC_angularSensorPretensionMotor);

	/*CP_HA_initialiseGPIO(CP_HA_GPIO_angularSensorEquilibriumMotor);
	CP_HA_initialiseADC(CP_HA_ADC_angularSensorEquilibriumMotor);*/
	// TODO: Pretension motor ADC is swapped with equilibrium motor!!!! Fix by
	// using the DMA!
}

/**
 * Read data
 */
void CP_HD_AnalogInput_readData(void)
{
	uint8_t sensorData[3];
	sensorData[0] = CP_HA_readADC(CP_HA_ADC_angularSensorJoint1);
	sensorData[1] = CP_HA_readADC(CP_HA_ADC_angularSensorJoint2);
	sensorData[2] = CP_HA_readADC(CP_HA_ADC_angularSensorPretensionMotor);
	//sensorData[2] = CP_HA_readADC(CP_HA_ADC_angularSensorEquilibriumMotor);

	/*uint8_t data[2] = {0};
	CP_HA_readMultipleADC(CP_HA_ADC_angularSensorJoint2, data, 2);
	sensorData[1] = data[0];
	sensorData[3] = data[1];*/


	CP_HD_AnalogInput_readDataCallback(sensorData);
}
