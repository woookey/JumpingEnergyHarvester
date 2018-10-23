#ifndef CP_HD_LEDDRIVER_H
#define CP_HD_LEDDRIVER_H

/**
 * Definition of a reference to a LED structures
 */
typedef struct LEDStructure LEDStructure_t;
typedef LEDStructure_t *const LEDReference;

/**
 * References to actual LEDs
 */
LEDReference CP_HD_CPUActivityLED;
LEDReference CP_HD_powerOnIndicationLED;
LEDReference CP_HD_executingIndicationLED;
LEDReference CP_HD_safetyStopIndicationLED;

/**
 * Initialises an LED structure
 */
void CP_HD_LED_initialiseLED(LEDReference ledRef);

/**
 * Switches the LED off
 */
void CP_HD_LED_switchLEDOff(LEDReference ledRef);

/**
 * Switches the LED on
 */
void CP_HD_LED_switchLEDOn(LEDReference ledRef);

#endif
