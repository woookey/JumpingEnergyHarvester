#ifndef CP_HA_HARDWARE_SETUP_H
#define CP_HA_HARDWARE_SETUP_H

/**
 * Sets up clocks, initialises all ports
 */
void setupHardware(void);

/**
 * Starts 'hardware' - it is mainly used for synthetic version
 * TODO: perhaps should be moved to RF_scheduler as 'startScheduler'
 */
void startHardware(void);

#endif
