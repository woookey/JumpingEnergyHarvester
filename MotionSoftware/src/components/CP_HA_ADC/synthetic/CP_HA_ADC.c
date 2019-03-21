#include <stdio.h>
#include <string.h>

#include <CP_HA_ADC.h>
#include "ADCDefinition.h"



static struct ADCStruct AngularSensorJoint1 =
{
		.name = "AngularSensorJoint1",
		.value = (uint8_t)100,
};

CP_HA_ADC CP_HA_ADC_angularSensorJoint1 = &AngularSensorJoint1;

void CP_HA_initialiseADC(CP_HA_ADC ADCInstance)
{
	printf("%s initialised\n", ADCInstance->name);
}

uint8_t CP_HA_readADC(CP_HA_ADC ADCInstance)
{
	//printf("%s value = %d\n", ADCInstance->name, ADCInstance->value);
	return ADCInstance->value;
}
