#ifndef CP_HA_PWM_H
#define CP_HA_PWM_H

typedef struct PWMStruct PWMStruct_t;
typedef PWMStruct_t *const CP_HA_PWM;


extern CP_HA_PWM CP_HA_PWM_pretensionMotorPWM;

void CP_HA_initialisePWM(CP_HA_PWM PWMInstance);
void CP_HA_startPWM(CP_HA_PWM PWMInstance);

#endif
