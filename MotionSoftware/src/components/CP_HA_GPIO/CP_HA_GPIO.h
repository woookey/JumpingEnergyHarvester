#ifndef CP_HA_GPIO_H
#define CP_HA_GPIO_H

typedef struct GPIOStruct GPIOStruct_t;
typedef GPIOStruct_t *const CP_HA_GPIO;

/**
 * Pretension Motor Pins
 */
extern CP_HA_GPIO CP_HA_GPIO_pretensionMotorClockwiseDirection;
extern CP_HA_GPIO CP_HA_GPIO_pretensionMotorAnticlockwiseDirection;
extern CP_HA_GPIO CP_HA_GPIO_pretensionMotorEnable;
extern CP_HA_GPIO CP_HA_GPIO_pretensionMotorPWM;

/**
 * Logger GPIOs (UART4)
 */
extern CP_HA_GPIO CP_HA_GPIO_LoggerRx;
extern CP_HA_GPIO CP_HA_GPIO_LoggerTx;

/**
 * Angular position sensors
 */
extern CP_HA_GPIO CP_HA_GPIO_angularSensorJoint1;

void CP_HA_initialiseGPIO(CP_HA_GPIO GPIOInstance);
void CP_HA_turnGPIOOn(CP_HA_GPIO GPIOInstance);
void CP_HA_turnGPIOOff(CP_HA_GPIO GPIOInstance);

#endif
