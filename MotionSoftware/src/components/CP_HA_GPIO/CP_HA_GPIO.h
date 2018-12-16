#ifndef CP_HA_GPIO_H
#define CP_HA_GPIO_H

typedef struct GPIOStruct GPIOStruct_t;
typedef GPIOStruct_t *const CP_HA_GPIO;

extern CP_HA_GPIO pretensionMotorClockwiseDirection;
extern CP_HA_GPIO pretensionMotorAnticlockwiseDirection;
extern CP_HA_GPIO pretensionMotorEnable;

void CP_HA_initialiseGPIO(CP_HA_GPIO GPIOInstance);
void CP_HA_turnGPIOOn(CP_HA_GPIO GPIOInstance);
void CP_HA_turnGPIOOff(CP_HA_GPIO GPIOInstance);

#endif
