#ifndef CP_HA_ADC_H
#define CP_HA_ADC_H

#include <stdint.h>

typedef struct ADCStruct ADCStruct_t;
typedef ADCStruct_t *const CP_HA_ADC;

/**
 * Angular position sensors
 */
extern CP_HA_ADC CP_HA_ADC_angularSensorJoint1;
extern CP_HA_ADC CP_HA_ADC_angularSensorJoint2;
extern CP_HA_ADC CP_HA_ADC_angularSensorPretensionMotor;
extern CP_HA_ADC CP_HA_ADC_angularSensorEquilibriumMotor;

void CP_HA_initialiseADC(CP_HA_ADC ADCInstance);
uint8_t CP_HA_readADC(CP_HA_ADC ADCInstance);

void CP_HA_readMultipleADC(CP_HA_ADC ADCInstance, uint8_t* returns, uint8_t conversion_number);

#endif
