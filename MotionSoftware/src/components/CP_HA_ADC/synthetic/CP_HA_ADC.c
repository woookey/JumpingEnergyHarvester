#include <stdio.h>
#include <string.h>

#include <CP_HA_ADC.h>
#include "ADCDefinition.h"



static struct ADCStruct AngularSensorJoint1 =
{
		.name = "AngularSensorJoint1",
		.value = (uint8_t)100,
};

static struct ADCStruct AngularSensorJoint2 =
{
		.name = "AngularSensorJoint2",
		.value = (uint8_t)50,
};

static struct ADCStruct AngularSensorPretensionMotor =
{
		.name = "AngularSensorPretensionMotor",
		.value = (uint8_t)20,
};

static struct ADCStruct AngularSensorEquilibriumMotor =
{
		.name = "AngularSensorEquilibriumMotor",
		.value = (uint8_t)30,
};

CP_HA_ADC CP_HA_ADC_angularSensorJoint1 = &AngularSensorJoint1;
CP_HA_ADC CP_HA_ADC_angularSensorJoint2 = &AngularSensorJoint2;
CP_HA_ADC CP_HA_ADC_angularSensorPretensionMotor = &AngularSensorPretensionMotor;
CP_HA_ADC CP_HA_ADC_angularSensorEquilibriumMotor = &AngularSensorEquilibriumMotor;

void CP_HA_initialiseADC(CP_HA_ADC ADCInstance)
{
	printf("%s initialised\n", ADCInstance->name);
}

uint8_t CP_HA_readADC(CP_HA_ADC ADCInstance)
{
	//printf("%s value = %d\n", ADCInstance->name, ADCInstance->value);
	return ADCInstance->value;
}
